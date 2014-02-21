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
		{
			CC_REG_IOCFG2   << 8  | 0x07,
			CC_REG_IOCFG1   << 8  | 0x0E,
			CC_REG_IOCFG0   << 8  | 0x24,
			CC_REG_SYNC1    << 8  | 0x12,
			CC_REG_SYNC0    << 8  | 0x34,
			CC_REG_PKTLEN   << 8  | 0x40,
			CC_REG_PKTCTRL1 << 8  | 0x08,
			CC_REG_PKTCTRL0 << 8  | 0x45,
			CC_REG_FREQ2    << 8  | 0x10,
			CC_REG_FREQ1    << 8  | 0xA7,
			CC_REG_FREQ0    << 8  | 0x62,
			CC_REG_MDMCFG2  << 8  | 0x73,
			CC_REG_MDMCFG1  << 8  | 0x42,
			CC_REG_MCSM1    << 8  | 0x2F,
			CC_REG_MCSM0    << 8  | 0x1C,
			CC_REG_BSCFG    << 8  | 0x6D,
		}
};

static uint8_t CC_PowerOnWait(void)
{
	int i;
	int timeout = 10000;

	RF.spi->CSLine(Enable);
	for (i = 0; i < 20; i++)
		asm("nop");

	RF.spi->CSLine(Disable);
	for (i = 0; i < 200; i++)
		asm("nop");

	RF.spi->CSLine(Enable);

	while (RF.spi->MISOStatus() && timeout > 0)
		timeout--;

	if (timeout <= 0) {
		RF.spi->CSLine(Disable);
		return FAIL;
	}

	RF.spi->CSLine(Disable);
	return SUCC;
}

void CC_Init()
{
	uint8_t ok = SUCC;
	int timeout = 10000;

	RF.initSucc = FALSE;

	if (CC_PowerOnWait() != SUCC)
		return;

	RF.spi->transmit(CC_CMD_RESET, &ok);
	if (ok != SUCC)
		return;

	RF.spi->CSLine(Enable);
	while (RF.spi->MISOStatus() && timeout > 0)
		timeout--;
	RF.spi->CSLine(Disable);

	if (timeout <= 0)
		return;

	RF.initSucc = TRUE;

}

void CC_LoadConfig(CC1101_Config_t *cfg, uint8_t *ok)
{

}

static void CC_WriteRegister(uint8_t adr, uint8_t data)
{
	int timeout = 10000;

	RF.spi->CSLine(Disable);
	while (RF.spi->MISOStatus() && timeout > 0)
		timeout--;

	RF.spi->transmit(adr, NULL);
	RF.spi->transmit(data, NULL);
	RF.spi->CSLine(Enable);

}
