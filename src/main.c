/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Gražvidas
 */

#include <avr/io.h>
#include "lcd.h"
#include "lcd_menu.h"
#include "buttons.h"
#include "uart.h"
#include "common.h"

#define F_CPU 8000000UL

void Init(void);

int8_t status = -1;

int main()
{
	DDRC |= 1<<PC5;

	Init();

	while(1)
	{
		LCD.DataFlow->SendString("------- Menu -------");

		status = Menu.choice(3, Menu.funcNames);
		if (status > -1)
			Menu.branch[status]();
	}

	return 0;
}

void Init()
{
	cli();
//	UART.Init();
	LCD.Init();
	Menu.Init();
	Buttons.Init();
	sei();
}
