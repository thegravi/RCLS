/*
 * spi.h
 *
 *  Created on: 2014 vas. 16
 *      Author: Gražvidas
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "../../common.h"

typedef struct {
	void (*init)(void);
	uint8_t (*transmit)(uint8_t data, uint8_t *ok);
	uint8_t (*MISOStatus)(void);

}SPI_Interface_t;

extern const SPI_Interface_t Spi;

void SPI_Init(void);
uint8_t SPI_Transmit(uint8_t data, uint8_t *ok);
uint8_t SPI_MISOStatus(void);

#endif /* SPI_H_ */
