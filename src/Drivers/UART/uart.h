/*
 * uart.h
 *
 *  Created on: 2013.11.23
 *      Author: Gražvidas
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdlib.h>

typedef struct {
	void (*init)(void);
	void (*sendByte)(uint8_t data);
	void (*sendChar)(char c);
	void (*sendData)(uint8_t* buffer, uint8_t bytes);
	void (*sendString)(char* buffer, uint8_t len);

}UART_t;

extern const UART_t UART;

#endif /* UART_H_ */
