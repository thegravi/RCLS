/*
 * uart.h
 *
 *  Created on: 2013.11.23
 *      Author: Graþvidas
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdlib.h>

typedef struct {

	void (*Init)(void);
	void (*sendByte)(uint8_t data);
	void (*sendChar)(char c);
	void (*sendData)(uint8_t* buffer, uint8_t bytes);
	void (*sendString)(char* buffer);
}UART_t;

extern UART_t UART;


#endif /* UART_H_ */
