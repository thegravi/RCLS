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
}
