/*
 * uart.c
 *
 *  Created on: 2013.11.23
 *      Author: Gražvidas
 */

#include "uart.h"

static void UART_Init(void)
{
  UCSR0B  |= 1<<TXEN0; 		      // Enable  Transmit
  UCSR0C  |= 1<<UCSZ01 | 1<<UCSZ00;   // 8 bit data character size
  UBRR0H   = 0;
  UBRR0L   = 12; 		      // 38400 baud rate for a 8MHz Clock
}

static void UART_SendChar(char c)
{
	uint16_t timeout = 10000;

	while (!(UCSR0A & (1<<UDRE0)) && timeout--);
	UDR0 = c;
}

static void UART_SendByte(uint8_t byte)
{
	char*    convByte = NULL;
	uint16_t timeout  = 10000;

	itoa(byte, convByte, 10);

	while (!(UCSR0A & (1 << UDRE0)) && timeout--);
	UDR0 = *convByte;
}

static void UART_SendString(char* buffer, uint8_t len)
{
	while (len-- > 0)
		UART_SendChar(*buffer++);
}

static void UART_SendData(uint8_t* buffer, uint8_t bytes)
{
	for (;bytes > 0; bytes--)
		UART_SendByte(*buffer++);
}

const UART_t UART = {
	UART_Init,
	UART_SendByte,
	UART_SendChar,
	UART_SendData,
	UART_SendString
};
