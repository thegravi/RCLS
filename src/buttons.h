/*
 * buttons.h
 *
 *  Created on: 2013.09.30
 *      Author: Graþvidas
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_DDR				DDRB
#define BUTTON_PORT				PORTB
#define BUTTON_PIN				PINB
#define BUTTON_PREV				PB7
#define BUTTON_NEXT				PB6
#define BUTTON_RETURN			PB5
#define BUTTON_SELECT			PB4

void (BUTTONS_Initialize)(void);

typedef struct {
	void (*Initialize)(void);

}BUTTONS_Interface_t;

extern BUTTONS_Interface_t BUTTONS_Interface;

#endif /* BUTTONS_H_ */
