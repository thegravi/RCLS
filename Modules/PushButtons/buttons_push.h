/*
 * buttons.h
 *
 *  Created on: 2013.09.30
 *      Author: Gražvidas
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/interrupt.h>
#include <util/delay.h>

#include "../Menu/lcd_menu.h"
#include "../../Drivers/UART/uart.h"

#define BUTTON_DDR				DDRB
#define BUTTON_PORT				PORTB
#define BUTTON_PIN				PINB

#define BUTTON_PREV				PB7
#define BUTTON_NEXT				PB6
#define BUTTON_RETURN			PB5
#define BUTTON_SELECT			PB4

void (BUTTONS_Init)(void);

typedef struct {
	void (*Init)(void);

	uint8_t readStates;

}BUTTONS_Interface_t;

extern BUTTONS_Interface_t Buttons;

#endif /* BUTTONS_H_ */
