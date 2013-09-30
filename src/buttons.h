/*
 * buttons.h
 *
 *  Created on: 2013.09.30
 *      Author: Gra�vidas
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#define BUTTON_NEXT				PD4
#define BUTTON_PREV				PD5
#define BUTTON_SELECT			PD6
#define BUTTON_RETURN			PD7

void (BUTTONS_Initialize)(void);

typedef struct {
	void (*Initialize)(void);
}BUTTONS_Interface_t;

extern BUTTONS_Interface_t BUTTONS_Interface;

#endif /* BUTTONS_H_ */
