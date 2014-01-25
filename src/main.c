/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Gražvidas
 */

#include <avr/io.h>
#include "Drivers/LCD/lcd.h"
#include "Drivers/UART/uart.h"
#include "Drivers/ADC/ADC.h"
#include "Drivers/PWM/pwm.h"
#include "Modules/Menu/lcd_menu.h"
#include "Modules/PushButtons/buttons_push.h"
#include "Modules/RotaryButtons/buttons_rotary.h"
#include "common.h"

#define F_CPU 8000000UL

void Init(void);

int8_t status = -1;
int i = 0, j = 0;
int main()
{
	DDRC |= 1<<PC5;

	Init();

//	while(1)
//	{
//		for (i=0;i<256;i++)
//		{
//			Pwm.SetIntensity(j, i);
//			_delay_ms(50);
//		}
//
//		if (j==2)
//			j=0;
//		else
//			j++;
//	}

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
//	Pwm.Init();
	Menu.Init();
	Buttons.Init();
	sei();
}
