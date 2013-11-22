/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#include "buttons.h"
#include "lcd_menu.h"
#include <util/delay.h>

BUTTONS_Interface_t BUTTONS_Interface = {
											BUTTONS_Initialize
									   };

void BUTTONS_Initialize() {

	DDRC |= 1<<PC5;
	BUTTON_DDR &= ~(1<<BUTTON_NEXT) | ~(1<<BUTTON_PREV) | ~(1<<BUTTON_SELECT) | ~(1<<BUTTON_RETURN);
	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupts on low level
	PCICR |= 1<<PCIE0;
	PCMSK0 |= 1<<PCINT3 | 1<<PCINT4 | 1<<PCINT6 | 1<<PCINT7;
	__asm__ __volatile__ ("sei" ::);
}

ISR(PCINT0_vect, ISR_NAKED) {

		if (!(BUTTON_PIN & BUTTON_NEXT))
		{
			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_NEXT;
			while(bit_is_clear(BUTTON_PIN, BUTTON_NEXT)) { }
		}
		else if (!(BUTTON_PIN & BUTTON_PREV))
		{
			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_PREV;
			while(bit_is_clear(BUTTON_PIN, BUTTON_PREV)) { }
		}
		else if (!(BUTTON_PIN & BUTTON_SELECT))
		{
			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_SELECT;
			while(bit_is_clear(BUTTON_PIN, BUTTON_SELECT)) { }
		}
		else if (!(BUTTON_PIN & BUTTON_RETURN))
		{
			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_RETURN;
			while(bit_is_clear(BUTTON_PIN, BUTTON_RETURN)) { }
		}
		else
		{
			PORTC &= ~(1<<PC5);
			LCD_Menu.optionSelected = OPT_VOID;
		}


	/*switch()
	{
		case BUTTON_NEXT:

			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_NEXT;
			break;

		case BUTTON_PREV:

			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_PREV;
			break;

		case BUTTON_SELECT:

			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_SELECT;
			break;

		case BUTTON_RETURN:

			PORTC ^= 1<<PC5;
			LCD_Menu.optionSelected = OPT_RETURN;
			break;

		default:
			break;

	}*/


//	while(bit_is_clear(BUTTON_PIN, BUTTON_NEXT)) { }
//	LCD_Menu.optionSelected = OPT_NEXT;
	_delay_ms(300);
	PCIFR |= (1<<PCIF0);
	reti();
}
