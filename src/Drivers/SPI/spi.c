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
	DDR_SPI |= 1<<DD_MOSI | 1<<DD_SCK;
	DDR_SPI &= ~(1<<DD_MISO) & ~(1<<DD_SCK);

	#if IS_MASTER
		SPCR |= 1<<MSTR;
	#else
		SPCR &= ~(1<<MSTR);
	#endif

	// prescaler Fclk/64 = 125 kHz
	SPCR |= 1<<SPR1;
	SPCR |= 1<<SPE;
}

uint8_t SPI_Transmit(uint8_t data, uint8_t *ok)
{

	return SUCC;
}

uint8_t SPI_MISOStatus(void)
{

	return SUCC;
}

