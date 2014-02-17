/*
 * spi.h
 *
 *  Created on: 2014 vas. 16
 *      Author: Gra�vidas
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "../../common.h"

#define IS_MASTER TRUE

#define DDR_SPI	   DDRB
#define PIN_SPI		PINB
#define PIN_MISO    PB4
#define PIN_MOSI    PB3
#define PIN_SCK     PB5
#define PIN_CS      PB2

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