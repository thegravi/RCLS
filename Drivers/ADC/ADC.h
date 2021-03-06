/*
 * ADC.h
 *
 *  Created on: 2014 saus. 21
 *      Author: Gra�vidas
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../common.h"

void ADC_Init(void);
void ADC_Enable(uint8_t state);
int16_t ADC_MeasVolt(uint8_t ch);
int16_t ADC_MeasTemp(void);

typedef struct {
	void (*init)(void);
	void (*enable)(uint8_t state);
	int16_t (*measVolt)(uint8_t ch);
	int16_t (*measTemp)(void);

}Adc_Interface_t;

extern const Adc_Interface_t Adc;

#endif /* ADC_H_ */
