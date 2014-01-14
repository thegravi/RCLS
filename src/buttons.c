/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Gra�vidas
 */

#include <avr/io.h>
#include "buttons.h"
#include "lcd_menu.h"
#include "lcd.h"
#include <util/delay.h>
#include "uart.h"

BUTTONS_Interface_t Buttons = { BUTTONS_Init };

void BUTTONS_Init() {

	BUTTON_DDR &= ~(1<<BUTTON_NEXT) & ~(1<<BUTTON_PREV) & ~(1<<BUTTON_SELECT) & ~(1<<BUTTON_RETURN);
	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupts on pin change
//	_delay_ms(5);
//	PCMSK0 |= (1<<PCINT4) | (1<<PCINT5) | (1<<PCINT6) | (1<<PCINT7);
//	_delay_ms(5);
//	PCICR |= (1<<PCIE0);
	sei();
}

#define BIT_IS_HIGH(port, bit) ((port & 1<<bit) && 1<<bit)
volatile uint8_t startUpTime_wait = 0x30;
volatile uint8_t checkStatesTime = 0x05;

ISR (TIMER0_OVF_vect)
{
	if (startUpTime_wait > 0 ) {
		startUpTime_wait--;
		return;
	}

	if (checkStatesTime > 0) {
		checkStatesTime--;
		return;
	} else {
		checkStatesTime = 0x05;
	}

	_delay_ms(20);
	Buttons.readStates = BUTTON_PIN & 0xF0;

//	if (receivedButton != receivedButton_prev)
//	{
//		return;
//	}
		//if (!(receivedButton & 0x40))
		if (!BIT_IS_HIGH(Buttons.readStates, BUTTON_NEXT))
		{
			Buttons.pressed = BUTTON_NEXT;
			UART.sendString("\rNext->\n\r");
//			LCD_Menu.optionSelected = OPT_NEXT;
		}
		//else if (!(receivedButton & 0x80))
		else if (!BIT_IS_HIGH(Buttons.readStates, BUTTON_PREV))
		{
			Buttons.pressed = BUTTON_PREV;
			UART.sendString("\rPrevious->\n\r");
//			LCD_Menu.optionSelected = OPT_PREV;
		}
		//else if (!(receivedButton & 0x10))
		else if (!BIT_IS_HIGH(Buttons.readStates, BUTTON_SELECT))
		{
			Buttons.pressed = BUTTON_SELECT;
			UART.sendString("\rSelect->\n\r");
//			LCD_Menu.optionSelected = OPT_SELECT;
		}
		//else if (!(receivedButton & 0x20))
		else if (!BIT_IS_HIGH(Buttons.readStates, BUTTON_RETURN))
		{
			Buttons.pressed = BUTTON_RETURN;
			UART.sendString("\rReturn->\n\r");
//			LCD_Menu.optionSelected = OPT_RETURN;
		}
		else
		{
			//UART.sendString("\rError->INT vector\n\r");
			//UART.sendByte(BUTTONS_Interface.readStates);
			Menu.optSelected = B_VOID;
		}

//		PORTC |= 1<<PC5;
		//while(bit_is_clear(BUTTONS_Interface.readStates, BUTTONS_Interface.buttonPressed)) { }
//		PORTC &= ~(1<<PC5);

		switch(Buttons.pressed)
		{
			case BUTTON_NEXT:
				Menu.optSelected = B_NEXT;
				break;

			case BUTTON_PREV:
				Menu.optSelected = B_PREV;
				break;

			case BUTTON_SELECT:
				Menu.optSelected = B_SELECT;
				break;

			case BUTTON_RETURN:
				Menu.optSelected = B_RETURN;
				break;

			default:
				Menu.optSelected = B_VOID;
				break;
		}
//
//		TIFR0 |= (1<<TOV0);
//	_delay_ms(200);
//	PCIFR |= (1<<PCIF0);
}
