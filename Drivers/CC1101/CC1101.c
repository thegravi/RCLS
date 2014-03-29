/*
 * CC1101.c
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#include "CC1101.h"

CC1101_Config_t RFCfgDefault = {
		41,
		{
			(CC_REG_IOCFG2   << 8)  | 0x29,
			(CC_REG_IOCFG1   << 8)  | 0x2E,
			(CC_REG_IOCFG0   << 8)  | 0x06,
			(CC_REG_FIFOTHR  << 8)  | 0x07,
			(CC_REG_SYNC1    << 8)  | 0xD3,
			(CC_REG_SYNC0    << 8)  | 0x91,
			(CC_REG_PKTLEN   << 8)  | 0x14,
			(CC_REG_PKTCTRL1 << 8)  | 0x04,
			(CC_REG_PKTCTRL0 << 8)  | 0x45,
			(CC_REG_ADDR	 << 8)  | 0x00,
			(CC_REG_CHANNR   << 8)  | 0x00,
			(CC_REG_FSCTRL1  << 8)  | 0x0C,
			(CC_REG_FSCTRL0  << 8)  | 0x00,
			(CC_REG_FREQ2    << 8)  | 0x10,
			(CC_REG_FREQ1    << 8)  | 0xB1,
			(CC_REG_FREQ0    << 8)  | 0x3B,
			(CC_REG_MDMCFG4  << 8)  | 0x2D,
			(CC_REG_MDMCFG3  << 8)  | 0x3B,
			(CC_REG_MDMCFG2  << 8)  | 0x0B,//0x1B
			(CC_REG_MDMCFG1  << 8)  | 0x22,
			(CC_REG_MDMCFG0  << 8)  | 0xF8,
			(CC_REG_DEVIATN  << 8)  | 0x62,
			(CC_REG_MCSM2    << 8)  | 0x07,
			(CC_REG_MCSM1    << 8)  | 0x30,
			(CC_REG_MCSM0    << 8)  | 0x18,
			(CC_REG_FOCCFG   << 8)  | 0x1D,
			(CC_REG_BSCFG    << 8)  | 0x1C,
			(CC_REG_AGCCTRL2 << 8)  | 0xC7,
			(CC_REG_AGCCTRL1 << 8)  | 0x00,
			(CC_REG_AGCCTRL0 << 8)  | 0xB0,
			(CC_REG_WOREVT1  << 8)  | 0x87,
			(CC_REG_WOREVT0  << 8)  | 0x6B,
			(CC_REG_WORCTRL  << 8)  | 0xFB,
			(CC_REG_FREND1   << 8)  | 0xB6,
			(CC_REG_FREND0   << 8)  | 0x10,
			(CC_REG_FSCAL3   << 8)  | 0xEA,
			(CC_REG_FSCAL2   << 8)  | 0x2A,
			(CC_REG_FSCAL1   << 8)  | 0x00,
			(CC_REG_FSCAL0   << 8)  | 0x1F,
			(CC_REG_RCCTRL1  << 8)  | 0x41,
			(CC_REG_RCCTRL0  << 8)  | 0x00,
		}
};

static uint8_t CC_StartTransmission(void)
{
	uint16_t timeout = 10000;

	RF.spi->CSLine(Low);
	while (RF.spi->MISOStatus() && timeout > 0)
		timeout--;

	if (timeout <= 0) {
		#if CC_LOG
		UART.sendString("Could not start transmitting\n");
		#endif
		return FAIL;
	}

	return SUCC;
}

static uint8_t CC_EndTransmission(void)
{
	RF.spi->CSLine(High);

	return SUCC;
}

static uint8_t CC_PowerOnWait(void)
{
	int i;

	RF.spi->CSLine(High);
	for (i = 0; i < 8; i++)
		asm("nop");

	RF.spi->CSLine(Low);
	for (i = 0; i < 8; i++)
		asm("nop");

	RF.spi->CSLine(High);
	for (i = 0; i < 328; i++)
		asm("nop");

	if (CC_StartTransmission() != SUCC) {
		UART.sendString("Power-on failed\n");
		return FAIL;
	}

	return SUCC;
}

static uint8_t CC_ReadRegister(uint8_t adr, uint8_t *ok)
{
	if (ok != NULL) *ok = FAIL;

	if (CC_StartTransmission() != SUCC) {
		CC_EndTransmission();
		return 0;
	}

	uint8_t sOK;
	RF.spi->transmit((uint8_t)(CC_READ_SINGLE | adr), &sOK);
	if (sOK != SUCC) {
		CC_EndTransmission();
		return 0;
	}

	uint8_t data = RF.spi->transmit(0, NULL);
	CC_EndTransmission();

	if (ok != NULL) *ok = SUCC;
	return data;
}

static void CC_WriteRegister(uint8_t adr, uint8_t data, uint8_t *ok)
{
	if (ok != NULL) *ok = FAIL;

	if (CC_StartTransmission() != SUCC) {
		CC_EndTransmission();
		return;
	}

	uint8_t sOK;
	RF.spi->transmit(adr, &sOK);

	if (sOK != SUCC) {
		CC_EndTransmission();
		return;
	}

	RF.spi->transmit(data, NULL);
	CC_EndTransmission();

	if (ok != NULL) *ok = SUCC;
	return;
}

static void CC_LoadConfig(CC1101_Config_t *cfg, uint8_t *ok)
{
	uint8_t idx;
	uint8_t data;

	if (ok != NULL) *ok = FAIL;

	for (idx = 0; idx < cfg->SPtr; idx++)
	{
		CC_WriteRegister((cfg->data[idx] >> 8) & 0xFF, cfg->data[idx] & 0xFF, NULL);
		data = CC_ReadRegister((cfg->data[idx] >> 8) & 0xFF, NULL);

		if (data != (cfg->data[idx] & 0xFF)) {
			*ok = FAIL;
			return;
		}
	}

	if (ok != NULL) *ok = SUCC;
	return;
}

static uint8_t CC_ReadStatus(uint8_t rw, uint8_t *ok)
{
	if(ok != NULL) *ok = FAIL;

	if (RF.initSucc != TRUE) {
		CC_EndTransmission();
		return 0;
	}

	if (CC_StartTransmission() != TRUE) {
		CC_EndTransmission();
		return 0;
	}

	uint8_t data;
	if (rw)
		data = RF.spi->transmit(0x80, NULL);
	else
		data = RF.spi->transmit(0x00, NULL);

	CC_EndTransmission();
	if (ok != NULL) *ok = SUCC;
	return data;
}

static void CC_WriteCmd(uint8_t cmd, uint8_t *ok)
{
	if (ok != NULL) *ok = FAIL;

	if (RF.initSucc != TRUE && cmd != CC_CMD_RESET) {
		CC_EndTransmission();
		return;
	}

	if (cmd < 0x30 || cmd >= 0x3D || cmd == 0x37) {
		CC_EndTransmission();
		return;
	}

	if (CC_StartTransmission() != TRUE) {
		CC_EndTransmission();
		return;
	}

	RF.spi->transmit(cmd, NULL);

	CC_EndTransmission();
	if (ok != NULL) *ok = SUCC;
	return;
}

static void CC_WritePATable(uint8_t *PAValues, uint8_t *ok)
{
	if (ok != NULL) *ok = FAIL;

	if (CC_StartTransmission() != TRUE) {
		CC_EndTransmission();
		return;
	}

	RF.spi->transmit(0x7E, NULL);

	uint8_t idx;
	for (idx = 0; idx < 8; idx++)
		RF.spi->transmit(PAValues[idx], NULL);

	CC_EndTransmission();
	_delay_us(10);

	if (CC_StartTransmission() != SUCC) {
		CC_EndTransmission();
		return;
	}

	RF.spi->transmit(0xFE, NULL);
	for (idx = 0; idx < 8; idx++)
		if (PAValues[idx] != RF.spi->transmit(0, NULL)) {
			CC_EndTransmission();
			return;
		}

	CC_EndTransmission();
	if (ok != NULL) *ok = SUCC;
	return;
}

static uint8_t CC_WriteFIFO(void *data, uint8_t size, uint8_t *ok)
{
	uint8_t idx = 0;

	if (ok != NULL) *ok = FAIL;

	if (size < 0 || size >= 64) {
		#if CC_LOG
		UART.sendString("Could not fit in FIFO\n");
		#endif
		CC_EndTransmission();
		return idx;
	}

	if (RF.initSucc != TRUE) {
		#if CC_LOG
		UART.sendString("Did not initiate successfully\n");
		#endif
		CC_EndTransmission();
		return idx;
	}

	if (CC_StartTransmission() != SUCC) {
		CC_EndTransmission();
		return idx;
	}

	uint8_t sOK, status;
	// Send register address
	if (size == 1)
		status = RF.spi->transmit(CC_REG_FIFO, &sOK);
	else
		status = RF.spi->transmit(CC_REG_FIFO | CC_WRITE_BURST, &sOK);

	if (sOK != SUCC) {
		#if CC_LOG
//		UART.sendString("Spi failure\n");
		#endif
		CC_EndTransmission();
		return idx;
	}

	if ((status & 0x0F) <= 0) {
		#if CC_LOG
		UART.sendString("FIFO is full\n");
		#endif
		CC_EndTransmission();
		return idx;
	}

	// Send values
	for (idx = 0; idx < size; idx++)
	{
		status = RF.spi->transmit(((uint8_t *)data)[idx], NULL);
		if ((status & 0x0F) <= 1) {
			#if CC_LOG
			UART.sendString("Could not fit all of the data\n");
			#endif
			idx++;
			CC_EndTransmission();
			return idx;
		}

	}

	CC_EndTransmission();
	if (ok != NULL) *ok = SUCC;
	return size;
}

uint8_t CC_ReadFIFO(uint8_t *data, uint8_t size, uint8_t *ok)
{
	uint8_t idx = 0;
	static uint16_t cnt = 0;

	if (ok != NULL) *ok = FAIL;

	// add size check

	uint8_t regOK = SUCC;

	// return number of received bytes in FIFO buffer
	uint8_t FIFODataCnt = CC_ReadRegister(CC_READ_BURST | CC_RXBYTES, &regOK) & 0x7F;

	if (regOK != SUCC) {
		CC_EndTransmission();
		return idx;
	} else if (FIFODataCnt <= 0 || FIFODataCnt > 64) {
		FIFODataCnt = 1;
	}

	if (CC_StartTransmission() != SUCC) {
		CC_EndTransmission();
		return idx;
	}

	// issue read FIFO command
	RF.spi->transmit(CC_READ_BURST | CC_REG_FIFO, &regOK);
	if (regOK != SUCC) {
		UART.sendString("Cannot read length\n");
		return 0;
	}

//	UART.sendString("Bytes: ");
//	LCD.SendCommand(8, 0x01);
	LCD.Position(1, 1);
	for (idx = 0; idx < FIFODataCnt; idx++)	{
		data[idx] = RF.spi->transmit(0x00, NULL);

		LCD.SendNumber(data[idx]);
		LCD.SendString("  ");
//		LCD.SendCharacter(S_BLANK);
//		UART.sendByte(data[idx]);
//		UART.sendString(" ");
	}

//	UART.sendString("\n");
	CC_EndTransmission();
	LCD.Position(4, 1);
	LCD.SendString("Packets received: ");
	LCD.SendNumber(++cnt);

	void (*rst)(void) = 0;
	if (cnt == 10)
		rst();

	if (ok != NULL) *ok = SUCC;
	return idx;
}

void CC_Init()
{
	uint8_t ok;

	memcpy(&RF.data, 0, sizeof(RF.data));

	RF.initSucc = FALSE;

	if (CC_PowerOnWait() != SUCC)
		return;

	RF.spi->transmit(CC_CMD_RESET, &ok);
	if (ok != SUCC) {
		UART.sendString("Reset cmd failed\n");
		return;
	}

	CC_EndTransmission();

	RF.initSucc = TRUE;

	CC_LoadConfig(&RFCfgDefault, &ok);
	if (ok != SUCC) {
		RF.initSucc = FAIL;
		UART.sendString("Failed to load config\n");
		return;
	}

	uint8_t PATable[] = {0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	CC_WritePATable(PATable, &ok);
	if (ok != SUCC) {
		RF.initSucc = FALSE;
		return;
	}

	CC_WriteCmd(CC_CMD_SIDLE, NULL);

	_delay_us(10);

	// flush FIFO`s
	CC_WriteCmd(CC_CMD_SFTX, NULL);
	CC_WriteCmd(CC_CMD_SFRX, NULL);

	// Enter RX
	CC_WriteCmd(CC_CMD_SRX, NULL);

	return;
}

void CC_SendData(uint8_t *data, uint8_t size, uint8_t *funcOK)
{
#if send == send
	if (funcOK != NULL) *funcOK = FAIL;

	// check packet size
	if (size < 0 || size >= 64) {
		#if CC_LOG
//		UART.sendString("Size parameter is just stupid\n");
		#endif
		return;
	}

    uint8_t ok = SUCC;
    uint8_t fifoBytes;
    uint16_t timeout = 100;
    uint8_t temp;
    int i;

	_delay_ms(1);
    CC_WriteCmd(CC_CMD_STX, &ok);

    do {
        fifoBytes = CC_ReadRegister(CC_READ_STATUS | CC_TXBYTES, &ok) & 0x7F;
        if(ok != SUCC){
            #if CC_LOG
            UART.sendString("Could not read fifo bytes\n");
            #endif
            if(funcOK != NULL) *funcOK = FAIL;
            return;
        }

        //request TX if we are in it
        if(CC_ReadStatus(TRUE, NULL) & 0x70 != 0x20)
            CC_WriteCmd(CC_CMD_STX, &ok);

		for(i = 0; i < 10000; i++)
			asm("nop");

        timeout--;
    } while((63 - fifoBytes < size + 1) && timeout > 0 && temp != 0x20);

    if(timeout <= 0){
        #if CC_LOG
        UART.sendString("Send FIFO TIMEOUT\n");
        #endif
        if(funcOK != NULL) *funcOK = FAIL;
        return;
    }

	// Write length of data
	CC_WriteFIFO(&size, 1, &ok);
	if (ok != SUCC) {
		#if CC_LOG
		UART.sendString("Could not write header\n");
		#endif
		CC_WriteCmd(CC_CMD_SFTX, NULL);
		return;
	}

	// Write data
	CC_WriteFIFO(data, size, &ok);
	if (ok != SUCC) {
		#if CC_LOG
		UART.sendString("Could not write FIFO\n");
		#endif
		CC_WriteCmd(CC_CMD_SFTX, NULL);
		return;
	}

	fifoBytes = CC_ReadRegister(CC_READ_STATUS | CC_TXBYTES, &ok) & 0x7F;
	UART.sendByte(fifoBytes);

	// Write TX strobe
	CC_WriteCmd(CC_CMD_STX, &ok);
	if (ok != SUCC) {
		#if CC_LOG
		UART.sendString("TX mode 0\n");
		#endif
		return;
	}

//	timeout = 1000;
//	while ((CC_ReadStatus(TRUE, NULL) & 0x70 ) == 0x20 && timeout-- > 0)
//		for (i = 0; i < 1000; i++)
//			asm("nop");
//
//	if (timeout <= 0) {
//		UART.sendChar('t');
//		return;
//	}

//	 wait for sync word to be transmitted
	while (!(PINC & 1<<PC5));
//	 wait for the end of the packet transmission
	while (PINC & 1<<PC5);

	fifoBytes = CC_ReadRegister(CC_READ_STATUS | CC_TXBYTES, &ok) & 0x7F;
	UART.sendByte(fifoBytes);

	if (funcOK != NULL) *funcOK = SUCC;
#endif
	return;
}

uint8_t CC_ReceivePacket(uint8_t *buffer, uint8_t *len, uint8_t *ok)
{
#if recv==recv
	CC_WriteCmd(CC_CMD_SRX, NULL);
	_delay_ms(1);

	while (!(PINC & 1<<PC5));
	while ((PINC & 1<<PC5));

	CC_ReadFIFO(buffer, *len, ok);
	if (*ok != SUCC) {
		UART.sendString("data read failed\n");
		*ok = FAIL;
		return FAIL;
	}

	CC_WriteCmd(CC_CMD_SIDLE, NULL);
	CC_WriteCmd(CC_CMD_SFRX, NULL);
	CC_WriteCmd(CC_CMD_SRX, NULL);

#endif
	return SUCC;
}

CC1101_Interface_t RF = {
		&Spi,
		CC_Init,
		CC_SendData,
		CC_ReceivePacket,
		FALSE
};





























