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

#define F_CPU 16000000UL

int main() {

	LCD_Interface.Initialize();
	BUTTONS_Interface.Initialize();
	LCD_Menu.Initialize();
	LCD_Menu.Enter();

	while(1) {
		// TODO: set interrupts for buttons
		/*if(bit_is_clear(PIND,4)) {PORTC ^= 1<<PC5;} _delay_ms(100);
		if(bit_is_clear(PIND,5)) {PORTC ^= 1<<PC5;} _delay_ms(100);
		if(bit_is_clear(PIND,6)) {PORTC ^= 1<<PC5;} _delay_ms(100);
		if(bit_is_clear(PIND,7)) {PORTC ^= 1<<PC5;} _delay_ms(100);*/
	}

	return 0;
}
