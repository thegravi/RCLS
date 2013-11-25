/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Graþvidas
 */


#include <avr/io.h>
#include "lcd.h"
#include "lcd_menu.h"
#include "buttons.h"
#include "uart.h"

#define F_CPU 8000000UL

int main() {

	UART.Init();

	LCD_Interface.Initialize();
	LCD_Menu.Initialize();
	BUTTONS_Interface.Initialize();
	LCD_Menu.Enter();

	while(1) {	}

	return 0;
}
