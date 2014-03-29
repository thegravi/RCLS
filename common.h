/*
 * common.h
 *
 *  Created on: 2014 saus. 14
 *      Author: Gražvidas
 */

#ifndef COMMON_H_
#define COMMON_H_

#define TRUE		1
#define FALSE		0
#define SUCC		1
#define FAIL		0
#define ERR			-1

#define send 0
#define recv 1 - send

enum {
	Disable=0,
	Enable
};

enum {
	Low=0,
	High
};

#define LED_ON() 	DDRC |= 1<<PC5; PORTC |= 1<<PC5;
#define LED_OFF() 	DDRC &= ~(1<<PC5); PORTC &= ~(1<<PC5);

#define CH_SIZE	16
#define NULL    ((void *)0)
extern char* funcName;
extern int8_t status;
extern uint8_t ch[CH_SIZE];

char* funcName;
uint8_t ch[CH_SIZE];

#endif /* COMMON_H_ */
