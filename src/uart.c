/*
 * uart.c
 *
 *  Created on: 2013.11.23
 *      Author: Graþvidas
 */

#include "uart.h"

static void uart_init(void)
{
  UCSR0B  |= 1<<TXEN0 | 1<<RXEN0; 	//Enable  Transmit,  Receive
  UCSR0C |= 1<<UCSZ01 | 1<<UCSZ00; //8 bit data character size
  UBRR0H = 0;
  UBRR0L = 51; 					// 9600 baud rate for a 8MHz Clock

  asm("sei");
}

static void send_uart_char(char c)
{
  while (!(UCSR0A & (1<<UDRE0))) { }
  UDR0 = c;
}

static void send_uart_byte(uint8_t byte)
{
	char* convByte = NULL;

	itoa(byte, convByte, 10);


	while (!(UCSR0A & (1<<UDRE0))) { }
	UDR0 = *convByte;
}


static void send_uart_string(char* buffer)
{
	while(*buffer != '\0'){
		send_uart_char(*buffer++);
	}
}

static void send_uart_data(uint8_t* buffer)
{
	while(*buffer != '\0'){
		send_uart_byte(*buffer++);
	}
}


UART_t UART = {uart_init,
			   send_uart_byte,
			   send_uart_char,
			   send_uart_data,
			   send_uart_string};
