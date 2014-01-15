/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#include "buttons.h"

BUTTONS_Interface_t Buttons = { BUTTONS_Init };

void BUTTONS_Init() {

	BUTTON_DDR &= ~(1<<BUTTON_NEXT);
	BUTTON_DDR &= ~(1<<BUTTON_PREV);
	BUTTON_DDR &= ~(1<<BUTTON_SELECT);
	BUTTON_DDR &= ~(1<<BUTTON_RETURN);

	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupts on pin change
	_delay_ms(5);
	PCMSK0 |= (1<<PCINT4) | (1<<PCINT5) | (1<<PCINT6) | (1<<PCINT7);
	_delay_ms(5);
	PCICR |= (1<<PCIE0);
}

ISR(PCINT0_vect)
{
        volatile uint8_t temp = 0;
        _delay_ms(110);

        Buttons.readStates = BUTTON_PIN & 0xF0;
        Menu.setOpt(0);
        Menu.optSelected = B_VOID;

        if (!(Buttons.readStates & 0x40)) {
                        temp = 0x40;
                        Buttons.pressed = BUTTON_NEXT;
                        Menu.setOpt(B_NEXT);
        }
        else if (!(Buttons.readStates & 0x80)){
                        temp = 0x80;
                        Buttons.pressed = BUTTON_PREV;
                        Menu.setOpt(B_PREV);
        }
        else if (!(Buttons.readStates & 0x10)) {
                        temp = 0x10;
                        Buttons.pressed = BUTTON_SELECT;
                        Menu.setOpt(B_SELECT);
        }
        else if (!(Buttons.readStates & 0x20)) {
                        temp = 0x20;
                        Buttons.pressed = BUTTON_RETURN;
                        Menu.setOpt(B_RETURN);
        }
        else {
                        temp = 0;
        }

//        if (temp)
//                while(!(BUTTON_PIN & temp));

//        _delay_ms(110);
}
