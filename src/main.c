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

#define F_CPU 8000000UL

int main() {

	LCD_Interface.Initialize();
	BUTTONS_Interface.Initialize();
	LCD_Menu.Initialize();
	LCD_Menu.Enter();

	while(1) {	}

	return 0;
}
