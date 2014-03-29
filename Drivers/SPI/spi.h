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
#include "../UART/uart.h"

#define DDR_SPI     DDRB
#define PIN_SPI     PINB
#define PORT_SPI    PORTB
#define PIN_MISO    PB4
#define PIN_MOSI    PB3
#define PIN_SCK     PB5
#define PIN_CS      PB2

typedef struct {
	void (*init)(void);
	uint8_t (*transmit)(uint8_t data, uint8_t *ok);
	uint8_t (*MISOStatus)(void);
	void (*CSLine)(uint8_t state);

}SPI_Interface_t;

extern SPI_Interface_t Spi;

void SPI_Init(void);
uint8_t SPI_Transmit(uint8_t data, uint8_t *ok);
uint8_t SPI_MISOStatus(void);
void SPI_CSLine(uint8_t state);

#endif /* SPI_H_ */
