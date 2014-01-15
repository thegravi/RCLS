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
int8_t status = -1;

int main()
{
	DDRC |= 1<<PC5;

	Init();

	while(1)
	{
		LCD.DataFlow->SendCommand(8, 0x01);
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------- Menu -------");

		LCD.Position(Menu.pos+2, 1);
		LCD.DataFlow->SendCharacter(S_ARROW_RIGHT);

		funcName = Menu.funcNames[0];
		LCD.Position(2, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.funcNames[1];
		LCD.Position(3, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.funcNames[2];
		LCD.Position(4, 3);
		LCD.DataFlow->SendString(funcName);

		status = LCD_Menu_Choice(3, TRUE, NULL);
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
