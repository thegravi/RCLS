/*
 * spi.c
 *
 *  Created on: 2014 vas. 16
 *      Author: Gražvidas
 */

#include "spi.h"

SPI_Interface_t Spi = {
		SPI_Init,
		SPI_Transmit,
		SPI_MISOStatus
};

void SPI_Init()
{
	#if IS_MASTER
		DDR_SPI |= 1<<PIN_MOSI | 1<<PIN_SCK;
		DDR_SPI &= ~(1<<PIN_MISO);
		SPCR |= 1<<MSTR | 1<<SPR1; // prescaler Fclk/64 = 125 kHz
	#else
		DDR_SPI |= 1<<PIN_MISO;
		DDR_SPI &= ~(1<<PIN_MOSI) & ~(1<<PIN_SCK);
		SPCR &= ~(1<<MSTR);
	#endif

	SPCR |= 1<<SPE;
}

uint8_t SPI_Transmit(uint8_t data, uint8_t *ok)
{
	uint16_t timeout = 10000;

	SPDR = data;

	while (!(SPSR & (1<<SPIF)) && timeout)
		timeout--;

	if (timeout <= 0)
	{
		if (ok != NULL)
			*ok = FAIL;
		return 0;
	}

	return SPDR;
}

void SPI_CSLine(uint8_t state)
{
	DDR_SPI |= 1<<PIN_CS;
	if (state)
		PORT_SPI |= 1<<PIN_CS;
	else
		PORT_SPI &= ~(1<<PIN_CS);
}

#if IS_MASTER
uint8_t SPI_MISOStatus(void)
{
	DDR_SPI &= ~(1<<PIN_MISO);
	uint8_t status = (PINB & (1<<PIN_MISO)) ? TRUE : FALSE;
	DDR_SPI |= 1<<PIN_MISO;

	return status;
}
#endif
