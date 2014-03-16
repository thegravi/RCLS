/*
 * CC1101.c
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#include "CC1101.h"

CC1101_Interface_t RF = {
		&Spi,
		CC_Init,
		CC_LoadConfig,
		FALSE
};

CC1101_Config_t RFCfgDefault = {
		17,
		{
			(CC_REG_IOCFG2   << 8)  | 0x29,
			(CC_REG_IOCFG1   << 8)  | 0x2E,
			(CC_REG_IOCFG0   << 8)  | 0x06,
			(CC_REG_FIFOTHR  << 8)  | 0x47,
			(CC_REG_SYNC1    << 8)  | 0xD3,
			(CC_REG_SYNC0    << 8)  | 0x91,
			(CC_REG_PKTLEN   << 8)  | 0xFF,
			(CC_REG_PKTCTRL1 << 8)  | 0x04,
			(CC_REG_PKTCTRL0 << 8)  | 0x45,
			(CC_REG_FREQ2    << 8)  | 0x10,
			(CC_REG_FREQ1    << 8)  | 0xA7,
			(CC_REG_FREQ0    << 8)  | 0x62,
			(CC_REG_MDMCFG2  << 8)  | 0x73,
			(CC_REG_MDMCFG1  << 8)  | 0x42,
			(CC_REG_MCSM1    << 8)  | 0x2F,
			(CC_REG_MCSM0    << 8)  | 0x1C,
			(CC_REG_BSCFG    << 8)  | 0x6D,
		}
};

static uint8_t CC_StartTransmission(void)
{
	int timeout = 10000;

	RF.spi->CSLine(Low);
	while (RF.spi->MISOStatus() && timeout > 0)
		timeout--;

	if (timeout <= 0)
		return FAIL;

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
	int timeout = 10000;

	RF.spi->CSLine(High);
	for (i = 0; i < 8; i++)
		asm("nop");

	RF.spi->CSLine(Low);
	for (i = 0; i < 8; i++)
		asm("nop");

	RF.spi->CSLine(High);
	for (i = 0; i < 328; i++)
		asm("nop");

	if (CC_StartTransmission() != SUCC)
		return FAIL;

//	RF.spi->CSLine(Disable);
//	while (RF.spi->MISOStatus() && timeout > 0)
//		timeout--;

//	if (timeout <= 0) {
//		RF.spi->CSLine(High);
//		return FAIL;
//	}

	return SUCC;
}

void CC_Init()
{
	uint8_t ok = SUCC;
	int timeout = 10000;

	RF.initSucc = FALSE;

	if (CC_PowerOnWait() != SUCC)
		return;

//	RF.spi->CSLine(Disable);
//	while (Spi.MISOStatus() && timeout > 0)
//		timeout--;

	RF.spi->transmit(CC_CMD_RESET, &ok);
	if (ok != SUCC)
		return;

//	RF.spi->CSLine(Enable);
//	while (RF.spi->MISOStatus() && timeout > 0)
//		timeout--;
	CC_EndTransmission();
//	RF.spi->CSLine(High);

//	if (timeout <= 0)
//		return;

	RF.initSucc = TRUE;

	CC_LoadConfig(&RFCfgDefault, &ok);
	if (ok != SUCC) {
		RF.initSucc = FAIL;
		return;
	}
}

void CC_LoadConfig(CC1101_Config_t *cfg, uint8_t *ok)
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

uint8_t CC_ReadRegister(uint8_t adr, uint8_t *ok)
{
	if (ok != NULL) *ok = FAIL;

	if (CC_StartTransmission() != SUCC) {
		CC_EndTransmission();
		return 0;
	}

	uint8_t sOK;
	RF.spi->transmit((uint8_t)(0x80 | adr), &sOK);
	if (sOK != SUCC) {
		CC_EndTransmission();
		return 0;
	}

	uint8_t data = RF.spi->transmit(0, NULL);
	CC_EndTransmission();

	if (ok != NULL) *ok = SUCC;
	return data;
}

void CC_WriteRegister(uint8_t adr, uint8_t data, uint8_t *ok)
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
