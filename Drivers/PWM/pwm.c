/*
 * pwm.c
 *
 *  Created on: 2014 saus. 24
 *      Author: Gražvidas
 */

#include "pwm.h"

const uint8_t Color_TABLE[8][3] = {
		{255,   0,   0},	// Red    *
		{255, 165,   0},	// Orange
		{255, 215,   0},	// Yellow
		{  0, 255,   0},	// Green  *
		{  0,   0, 255},	// Blue   *
		{ 75,   0, 130},	// Indigo
		{143,   0, 255},	// Violet
		{255, 255, 255}		// White
};

Pwm_Interface_t Pwm = {
		PWM_Init,
		PWM_Enable,
		PWM_SetIntensity,
		FALSE,
		FALSE
};

void PWM_Init()
{

//--------------- Red, Green channels --------------//
	// clock source
	TCCR0B = 1<<CS02;

	// Fast PWM
	TCCR0A = 1<<WGM01 | 1<<WGM00;

	// non-inverting mode
	TCCR0A |= 1<<COM0A1 | 1<<COM0B1;

	// default 0
	OCR0A = OCR0B = 0;

//--------------- Blue channels --------------//
	// clock source
	TCCR2B = 1<<CS22 | 1<<CS21;

	// Fast PWM
	TCCR2A = 1<<WGM21 | 1<<WGM20;

	// non-inverting mode
	TCCR2A |= 1<<COM2B1;

	// default zero
	OCR2B = 0;

//--------------- Brightness channel --------------//


	LED_RGB_DDR  |= 1<<LED_R_PIN | 1<<LED_B_PIN | 1<<LED_G_PIN;
	Pwm.initSUCC  = SUCC;
	Pwm.f_enable  = TRUE;

//	PWM_Enable(DISABLE);
}

void PWM_Enable(uint8_t state)
{
	if (!Pwm.initSUCC)
		return;

	if (state == Enable)
	{
		// For Red, Green channels
		TCCR0B |= 1<<CS02;
		TCCR0A |= 1<<COM0B1 | 1<<COM0A1 | 1<<WGM01 | 1<<WGM00;

		// For Blue channel
		TCCR2B |= 1<<CS02;
		TCCR2A |= 1<<COM2B1 | 1<<WGM21 | 1<<WGM20;
		//For Brightness channel
	}
	else if (state == Disable)
	{
		// For Red, Green channels
		TCCR0B &= ~(1<<CS02);
		TCCR0A &= ~(1<<COM0B1) & ~(1<<COM0A1) & ~(1<<WGM01) & ~(1<<WGM00);

		// For Blue channel
		TCCR2B &= ~(1<<CS02);
		TCCR2A &= ~(1<<COM2B1) & ~(1<<WGM21) & ~(1<<WGM20);
		//For Brightness channel

		Pwm.initSUCC = Disable;
	}
}

void PWM_SetIntensity(uint8_t obj, uint8_t value)
{
	switch(obj)
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

	case Brightness:
		break;

	default:
		break;
	}
}
