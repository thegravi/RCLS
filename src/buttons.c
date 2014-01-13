/*
 * buttons.c
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#include <avr/io.h>
#include "buttons.h"
#include "lcd_menu.h"
#include "lcd.h"
#include <util/delay.h>
#include "uart.h"

BUTTONS_Interface_t BUTTONS_Interface = { BUTTONS_Initialize };

void BUTTONS_Initialize() {

	BUTTON_DDR &= ~(1<<BUTTON_NEXT);
	BUTTON_DDR &= ~(1<<BUTTON_PREV);
	BUTTON_DDR &= ~(1<<BUTTON_SELECT);
	BUTTON_DDR &= ~(1<<BUTTON_RETURN);

	BUTTON_PORT |= (1<<BUTTON_NEXT) | (1<<BUTTON_PREV) | (1<<BUTTON_SELECT) | (1<<BUTTON_RETURN);

	// interrupts on pin change
//	_delay_ms(5);
//	PCMSK0 |= (1<<PCINT4) | (1<<PCINT5) | (1<<PCINT6) | (1<<PCINT7);
//	_delay_ms(5);
//	PCICR |= (1<<PCIE0);
	sei();
}

//volatile uint8_t receivedButtonsStates;
//uint8_t receivedButton_prev;

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
	BUTTONS_Interface.readStates = BUTTON_PIN & 0xF0;
	//receivedButton_prev &= 0xF0;
	//receivedButton_prev >>= 4;

//	UART.sendByte(BIT_IS_HIGH(BUTTONS_Interface.readStates, BUTTON_NEXT));
//	UART.sendString(" ");
//	UART.sendByte((BUTTONS_Interface.readStates & 1<<BUTTON_PREV) && 1<<BUTTON_PREV);
//	UART.sendString(" ");
//	UART.sendByte((BUTTONS_Interface.readStates & 1<<BUTTON_SELECT) && 1<<BUTTON_SELECT);
//	UART.sendString(" ");
//	UART.sendByte((BUTTONS_Interface.readStates & 1<<BUTTON_RETURN) && 1<<BUTTON_RETURN);
//	UART.sendString("\n\r");

//	_delay_ms(50);
//	receivedButton = BUTTON_PIN & 0xF0;
//
//	if (receivedButton != receivedButton_prev)
//	{
//		return;
//	}
		//if (!(receivedButton & 0x40))
		if (!BIT_IS_HIGH(BUTTONS_Interface.readStates, BUTTON_NEXT))
		{
			BUTTONS_Interface.buttonPressed = BUTTON_NEXT;
			UART.sendString("\rNext->\n\r");
//			LCD_Menu.optionSelected = OPT_NEXT;
		}
		//else if (!(receivedButton & 0x80))
		else if (!BIT_IS_HIGH(BUTTONS_Interface.readStates, BUTTON_PREV))
		{
			BUTTONS_Interface.buttonPressed = BUTTON_PREV;
			UART.sendString("\rPrevious->\n\r");
//			LCD_Menu.optionSelected = OPT_PREV;
		}
		//else if (!(receivedButton & 0x10))
		else if (!BIT_IS_HIGH(BUTTONS_Interface.readStates, BUTTON_SELECT))
		{
			BUTTONS_Interface.buttonPressed = BUTTON_SELECT;
			UART.sendString("\rSelect->\n\r");
//			LCD_Menu.optionSelected = OPT_SELECT;
		}
		//else if (!(receivedButton & 0x20))
		else if (!BIT_IS_HIGH(BUTTONS_Interface.readStates, BUTTON_RETURN))
		{
			BUTTONS_Interface.buttonPressed = BUTTON_RETURN;
			UART.sendString("\rReturn->\n\r");
//			LCD_Menu.optionSelected = OPT_RETURN;
		}
		else
		{
			//UART.sendString("\rError->INT vector\n\r");
			//UART.sendByte(BUTTONS_Interface.readStates);
			LCD_Menu.optionSelected = B_VOID;
		}

//		PORTC |= 1<<PC5;
		//while(bit_is_clear(BUTTONS_Interface.readStates, BUTTONS_Interface.buttonPressed)) { }
//		PORTC &= ~(1<<PC5);

		switch(BUTTONS_Interface.buttonPressed)
		{
			case BUTTON_NEXT:
				LCD_Menu.optionSelected = B_NEXT;
				break;

			case BUTTON_PREV:
				LCD_Menu.optionSelected = B_PREV;
				break;

			case BUTTON_SELECT:
				LCD_Menu.optionSelected = B_SELECT;
				break;

			case BUTTON_RETURN:
				LCD_Menu.optionSelected = B_RETURN;
				break;

			default:
				LCD_Menu.optionSelected = B_VOID;
				break;
		}
//
//		TIFR0 |= (1<<TOV0);
//	_delay_ms(200);
//	PCIFR |= (1<<PCIF0);
}
