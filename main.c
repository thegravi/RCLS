/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Gražvidas
 */

#include "main.h"

int8_t status;

int main()
{
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
	Init_GPIO();
	LCD.Init();
	Menu.Init();
	Buttons.init();
	Rotary.init();
	sei();
}

void Init_GPIO()
{
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;

	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
}
