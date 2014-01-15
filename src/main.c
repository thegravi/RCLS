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

#define F_CPU 8000000UL

void Init(void);

int main()
{
	volatile int i;
	char* funcName = NULL;
	DDRC |= 1<<PC5;

	Init();

	while(1)
	{
		UART.sendByte(Menu.optSelected);
		PORTC |= 1<<PC5;

		while (!Menu.getOpt())
		{
			_delay_ms(10);

			if (Menu.getOpt() != B_VOID)
				break;
		}

		PORTC &= ~(1<<PC5);
		cli();

		switch(Menu.getOpt())
		{
			case B_NEXT:
				if (Menu.pos_1L < MAX_1L-1)
					Menu.pos_1L++;
				else
					Menu.pos_1L = 0;
			break;

			case B_PREV:
				if (Menu.pos_1L > 0)
					Menu.pos_1L--;
				else
					Menu.pos_1L = MAX_1L-1;
			break;

			case B_SELECT:
			break;

			case B_RETURN:
			break;
		}
		funcName = Menu.funcNames[Menu.pos_1L];
		LCD.DataFlow->SendCommand(8, 0x01);
		LCD.DataFlow->SendString(funcName);
		Menu.setOpt(B_VOID);
		sei();
	}

	return 0;
}

void Init()
{
	cli();
	UART.Init();
	LCD.Init();
	Menu.Init();
	Buttons.Init();
	sei();
}
