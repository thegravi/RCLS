/*
 * spi.c
 *
 *  Created on: 2014 vas. 16
 *      Author: Gražvidas
 */

#include "spi.h"

const SPI_Interface_t Spi = {
		SPI_Init,
		SPI_Transmit,
		SPI_MISOStatus
};

void SPI_Init()
{
	#if IS_MASTER
		DDR_SPI |= 1<<DD_MOSI | 1<<DD_SCK;
		DDR_SPI &= ~(1<<DD_MISO);
		SPCR |= 1<<MSTR | 1<<SPR1; // prescaler Fclk/64 = 125 kHz
	#else
		DDR_SPI |= 1<<DD_MISO;
		DDR_SPI &= ~(1<<DD_MOSI) & ~(1<<DD_SCK);
		SPCR &= ~(1<<MSTR);
	#endif

	SPCR |= 1<<SPE;
}

uint8_t SPI_Transmit(uint8_t data, uint8_t *ok)
{
	uint16_t timeout = 10000;

	*ok = SUCC;
	SPDR = data;

	while (!(SPSR & (1<<SPIF)) && timeout)
		timeout--;

	if (timeout <= 0)
	{
		if (ok != ((void *)0))
			*ok = FAIL;
		return 0;
	}

	return SPDR;
}

uint8_t SPI_MISOStatus(void)
{

	return SUCC;
}

