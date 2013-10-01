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

#define BUTTON_DDR				DDRD
#define BUTTON_PORT				PORTD
#define BUTTON_PIN				PIND
#define BUTTON_NEXT				PD2
#define BUTTON_PREV				PD5
#define BUTTON_SELECT			PD6
#define BUTTON_RETURN			PD7

void (BUTTONS_Initialize)(void);

typedef struct {
	void (*Initialize)(void);

}BUTTONS_Interface_t;

extern BUTTONS_Interface_t BUTTONS_Interface;

#endif /* BUTTONS_H_ */
