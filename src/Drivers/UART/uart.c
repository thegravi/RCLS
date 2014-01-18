/*
 * uart.c
 *
 *  Created on: 2013.11.23
 *      Author: Graþvidas
 */

#include "uart.h"

static void uart_init(void)
{
  UCSR0B  |= 1<<TXEN0; 	//Enable  Transmit
  UCSR0C |= 1<<UCSZ01 | 1<<UCSZ00; //8 bit data character size
  UBRR0H = 0;
  UBRR0L = 12; 					// 38400 baud rate for a 8MHz Clock
}

static void send_uart_char(char c)
{
	uint16_t timeout = 10000;

	while (!(UCSR0A & (1<<UDRE0)) && timeout--);
	UDR0 = c;

}

static void send_uart_byte(uint8_t byte)
{
	char* convByte = NULL;
	uint16_t timeout = 10000;

	itoa(byte, convByte, 10);

	while (!(UCSR0A & (1<<UDRE0)) && timeout--) { }
	UDR0 = *convByte;
}


static void send_uart_string(char* buffer, uint8_t len)
{
	while(len > 0) {
			send_uart_char(*buffer++);
			len--;
	}
}

static void send_uart_data(uint8_t* buffer, uint8_t bytes)
{
	for (;bytes > 0; bytes--)
		send_uart_byte(*buffer++);
}


UART_t UART = {uart_init,
			   send_uart_byte,
			   send_uart_char,
			   send_uart_data,
			   send_uart_string};
