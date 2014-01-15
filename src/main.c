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

char* funcName;

int main()
{
	volatile int i;
//	char* funcName = NULL;
	DDRC |= 1<<PC5;

	Init();

	while(1)
	{
		LCD.Position(Menu.pos+2, 1);
		LCD.DataFlow->SendCharacter(S_ARROW_RIGHT);

		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------- Menu -------");
		funcName = Menu.funcNames[0];
		LCD.Position(2, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.funcNames[1];
		LCD.Position(3, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.funcNames[2];
		LCD.Position(4, 3);
		LCD.DataFlow->SendString(funcName);

		LED_ON();

		while (!Menu.getOpt())
		{
			_delay_ms(10);

			if (Menu.getOpt() != B_VOID)
				break;
		}

		LED_OFF();

		switch(Menu.getOpt())
		{
			case B_NEXT:
				LCD.Position(Menu.pos+2, 1);
				LCD.DataFlow->SendCharacter(S_BLANK);
				if (Menu.pos < MAX_1L-1)
					Menu.pos++;
				else
					Menu.pos = 0;
			break;

			case B_PREV:
				LCD.Position(Menu.pos+2, 1);
				LCD.DataFlow->SendCharacter(S_BLANK);
				if (Menu.pos > 0)
					Menu.pos--;
				else
					Menu.pos = MAX_1L-1;
			break;

			case B_SELECT:
				LCD.DataFlow->SendCommand(8, 0x01);
				Menu.setOpt(B_VOID);
				Menu.branch[Menu.pos]();
				LCD.DataFlow->SendCommand(8, 0x01);
			break;

			case B_RETURN:
				LCD.Position(2, 1);
				LCD.DataFlow->SendString("return");
			break;
		}

		Menu.setOpt(B_VOID);
		_delay_ms(50);
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
