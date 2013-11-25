/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#include "buttons.h"
#include "lcd_menu.h"
#include "lcd.h"
#include <util/delay.h>
#include "uart.h"

BUTTONS_Interface_t BUTTONS_Interface = { BUTTONS_Initialize };

void BUTTONS_Initialize() {

	DDRC |= 1<<PC5;
	BUTTON_DDR &= ~(1<<BUTTON_NEXT);
	BUTTON_DDR &= ~(1<<BUTTON_PREV);
	BUTTON_DDR &= ~(1<<BUTTON_SELECT);
	BUTTON_DDR &= ~(1<<BUTTON_RETURN);

	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupts on low level
	PCICR |= 1<<PCIE0;
	PCMSK0 |= 1<<PCINT4 | 1<<PCINT5 | 1<<PCINT6 | 1<<PCINT7;
	sei();
}

ISR(PCINT0_vect, ISR_NAKED) {

	cli();
	_delay_ms(10);

	volatile uint8_t receivedButton;

		if (!(BUTTON_PIN & 0x40)) {
			receivedButton = BUTTON_NEXT;
			UART.sendString("\rNext->\n\r");
		}
		else if (!(BUTTON_PIN & 0x80)) {
			receivedButton = BUTTON_PREV;
			UART.sendString("\rPrevious->\n\r");
		}
		else if (!(BUTTON_PIN & 0x10)) {
			receivedButton = BUTTON_SELECT;
			UART.sendString("\rSelect->\n\r");
		}
		else if (!(BUTTON_PIN & 0x20)) {
			receivedButton = BUTTON_RETURN;
			UART.sendString("\rReturn->\n\r");
		}

		while(bit_is_clear(BUTTON_PIN, receivedButton)) { PORTC |= 1<<PC5; } PORTC &= ~(1<<PC5);

		switch(receivedButton)
		{
			case BUTTON_NEXT:

				LCD_Menu.optionSelected = OPT_NEXT;
				//LCD_Interface.Position(2, 1);
				//LCD_Interface.DataFlow.SendString("Next");
				break;

			case BUTTON_PREV:

				LCD_Menu.optionSelected = OPT_PREV;
				//LCD_Interface.Position(2, 1);
				//LCD_Interface.DataFlow.SendString("Previous");
				break;

			case BUTTON_SELECT:

				LCD_Menu.optionSelected = OPT_SELECT;
				//LCD_Interface.Position(2, 1);
				//LCD_Interface.DataFlow.SendString("Select");
				break;

			case BUTTON_RETURN:

				LCD_Menu.optionSelected = OPT_RETURN;
				//LCD_Interface.Position(2, 1);
				//LCD_Interface.DataFlow.SendString("Return");
				break;

			default:
				LCD_Menu.optionSelected = OPT_VOID;
				//LCD_Interface.Position(2, 1);
				//LCD_Interface.DataFlow.SendString("Void");
				break;

		}

	_delay_ms(500);
	PCIFR |= (1<<PCIF0);
	sei();
	reti();
}
