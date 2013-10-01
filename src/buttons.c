/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#include "buttons.h"


BUTTONS_Interface_t BUTTONS_Interface = {
											BUTTONS_Initialize
									   };

void BUTTONS_Initialize() {

	DDRC |= 1<<PC5;
	BUTTON_DDR &= ~(1<<BUTTON_NEXT) | ~(1<<BUTTON_PREV) | ~(1<<BUTTON_SELECT) | ~(1<<BUTTON_RETURN);
	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupt on low level
	MCUCR &= ~(1<<ISC01);
	MCUCR &= ~(1<<ISC00);
	GICR |= (1<<INT0);
	sei();
}

ISR(INT0_vect) {

	PORTC ^= (1<<PC5);_delay_ms(100);
	while(bit_is_clear(BUTTON_PIN, BUTTON_NEXT)) { }
	GIFR |= (1<<INTF0);
}
