/*
 * ADC.c
 *
 *  Created on: 2014 saus. 21
 *      Author: Gražvidas
 */

#include "ADC.h"

const Adc_Interface_t Adc = {
		ADC_Init,
		ADC_Enable,
		ADC_MeasVolt,
		ADC_MeasTemp
};

void ADC_Init()
{
	// prescaler clk/64 => 125 kHz
	ADCSRA |= 1<<ADPS2 | 1<<ADPS1;

	// voltage reference
	ADMUX |= 1<<REFS0;// | 1<<REFS1;

	// interrupt enable
	ADCSRA |= 1<<ADIE;

	// disable adc
	ADCSRA &= ~(1<<ADEN);
}

void ADC_Enable(uint8_t state)
{
	if (state)
		ADCSRA |= 1<<ADSC | 1<<ADEN;
	else
		ADCSRA &= ~(1<<ADEN);
}

int16_t ADC_MeasVolt(uint8_t ch)
{
	uint16_t timeout = 10000;

	if (ch < 0 || ch > 7)
		return ERR;

	while(!(ADCSRA & 1<<ADIF) && timeout--);

	if (!timeout)
		return ERR;

	// assign new channel to measure from
	ADMUX = (ADMUX & 0xF0) | ch;

	timeout = 10000;
	while(!(ADCSRA & 1<<ADIF) && timeout--);

	if (!timeout)
		return ERR;

	return (uint8_t)(ADC >> 2);
}

int16_t ADC_MeasTemp()
{
	uint16_t timeout = 10000;

	while(!(ADCSRA & 1<<ADIF) && timeout--);

	if (!timeout)
		return ERR;

	// assign new channel to measure from
	ADMUX = (ADMUX & 0xF0) | 0x08;

	timeout = 10000;
	while(!(ADCSRA & 1<<ADIF) && timeout--);

	if (!timeout)
		return ERR;

	return (uint8_t)(ADC >> 2);
}

ISR(ADC_vect)
{

}
