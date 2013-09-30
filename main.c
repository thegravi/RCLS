/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Gra�vidas
 */

#include <avr/io.h>
#include "lcd.h"
#include "lcd_menu.h"

#define F_CPU 16000000UL

int main() {

	LCD_Interface.Initialize();
	LCD_Menu.Initialize();
	LCD_Menu.Enter();
	while(1) {

	}

	return 0;
}
