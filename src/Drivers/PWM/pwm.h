/*
 * pwm.h
 *
 *  Created on: 2014 saus. 24
 *      Author: Gražvidas
 */

#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include "../../common.h"

#define LED_R_PIN			PD6
#define LED_G_PIN			PD5
#define LED_B_PIN			PD3
#define LED_RGB_PORT		DDRD

#define LED_BRIGHT_PIN		PB1
#define LED_BRIGHT_PORT		DDRB

void PWM_Init(void);

typedef enum {
	Red=0,
	Green,
	Blue,

	NumOfColors
}Colors_t;

typedef struct {
	void (*Init)(void);
	void (*Enable)(uint8_t state);

	uint8_t initSUCC;

}Pwm_t;

extern Pwm_t Pwm;

#endif /* PWM_H_ */
