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

int main()
{
	volatile int i;
	char* funcName = NULL;
	DDRC |= 1<<PC5;

	Init();

	while(1)
	{
		LCD.DataFlow->SendCommand(8, 0x01);
		funcName = Menu.funcNames[Menu.pos_1L];
		LCD.Position(1, 1);
		LCD.DataFlow->SendString(funcName);
		LCD.Position(4, 1);
		LCD.DataFlow->SendNumber(Menu.pos_1L);

		LED_ON();

		while (!Menu.getOpt())
		{
			_delay_ms(10);

			if (Menu.getOpt() != B_VOID)
				break;
		}

		LED_OFF();
//		cli();
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
				Menu.setOpt(B_VOID);
				Menu.branch[Menu.pos_1L]();
			break;

			case B_RETURN:
				LCD.Position(2, 1);
				LCD.DataFlow->SendString("return");
			break;
		}

		Menu.setOpt(B_VOID);
		_delay_ms(50);
//		sei();
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
