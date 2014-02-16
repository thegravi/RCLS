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

}

uint8_t SPI_Transmit(uint8_t data, uint8_t *ok)
{

	return SUCC;
}

uint8_t SPI_MISOStatus(void)
{

	return SUCC;
}

