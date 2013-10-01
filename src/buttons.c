/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#include "buttons.h"
#include "lcd_menu.h"

BUTTONS_Interface_t BUTTONS_Interface = {
											BUTTONS_Initialize
									   };

void BUTTONS_Initialize() {

	DDRC |= 1<<PC5;
	BUTTON_DDR &= ~(1<<BUTTON_NEXT) | ~(1<<BUTTON_PREV) | ~(1<<BUTTON_SELECT) | ~(1<<BUTTON_RETURN);
	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupts on low level
	MCUCR &= ~(1<<ISC11) | ~(1<<ISC01) | ~(1<<ISC00) | ~(1<<ISC10);
	GICR |= (1<<INT0) | (1<<INT1);
	__asm__ __volatile__ ("sei" ::);
}

ISR(INT0_vect) {

	while(bit_is_clear(BUTTON_PIN, BUTTON_NEXT)) { }
	LCD_Menu.functionSelected = OPT_NEXT;
	GIFR |= (1<<INTF0);
}

ISR(INT1_vect) {

	while(bit_is_clear(BUTTON_PIN, BUTTON_PREV)) { }
	LCD_Menu.functionSelected = OPT_PREV;
	GIFR |= (1<<INTF1);
}
