/*
 * common.h
 *
 *  Created on: 2014 saus. 14
 *      Author: Gra�vidas
 */

#ifndef COMMON_H_
#define COMMON_H_

#define TRUE	1
#define FALSE	0
#define SUCC	1
#define FAIL	0
#define ERR		-1

#define LED_ON() DDRC |= 1<<PC5; PORTC |= 1<<PC5;
#define LED_OFF()	DDRC &= ~(1<<PC5); PORTC &= ~(1<<PC5);

extern char* funcName;
extern int8_t status;

#endif /* COMMON_H_ */
