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
		SPI_MISOStatus,
		SPI_CSLine
};

void SPI_Init()
{
//	DDRC |= 1 <<PC5;

	DDR_SPI |= 1<<PIN_MOSI | 1<<PIN_SCK | 1<<PIN_CS;
	SPI_CSLine(Enable);
	DDR_SPI &= ~(1<<PIN_MISO);
	SPCR |= 1<<SPE | 1<<MSTR | 1<<SPR0 | 1<<CPOL | 1<<CPHA;; // prescaler Fclk/64 = 125 kHz

//	PORT_SPI &= ~(1<<PIN_SCK);
	PORT_SPI |= 1 <<PIN_MISO;

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

	*ok = SUCC;
	return SPDR;
}

void SPI_CSLine(uint8_t state)
{
	if (state)
		PORT_SPI |= 1<<PIN_CS;
	else
		PORT_SPI &= ~(1<<PIN_CS);
}

uint8_t SPI_MISOStatus(void)
{
	return (PINB & (1<<PIN_MISO)) ? TRUE : FALSE;
}
