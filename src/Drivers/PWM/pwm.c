/*
 * pwm.c
 *
 *  Created on: 2014 saus. 24
 *      Author: Gražvidas
 */

#include "pwm.h"

Pwm_t Pwm = {
		PWM_Init,
		PWM_Enable,
		FALSE
};

void PWM_Init()
{

	// clock source for Red, Green channels
	TCCR0B = 1<<CS02;

	// Fast PWM
	TCCR0A = 1<<WGM01 | 1<<WGM00;

	// non-inverting mode
	TCCR0A |= 1<<COM0A1 | 1<<COM0B1;

	Pwm.initSUCC = SUCC;
}

void PWM_Enable(uint8_t state)
{
	if (state == ENABLE)
	{

	}
	else
	{
		// For Red, Green channels
		TCCR0B &= ~(1<<CS02);
		TCCR0A &= ~(1<<COM0B1) & ~(1<<COM0A1) & ~(1<<WGM01) & ~(1<<WGM00);

		// For Blue channel

		//For Brightness channel

	}
}

void PWM_SetIntensity(uint8_t color, uint8_t value)
{
	switch(color)
	{
	case Red:
		OCR0A = value;
		break;

	case Green:
		OCR0B = value;
		break;

	case Blue:
		OCR2B = value;
		break;

	default:
		break;
	}
}
