/*
 * ADC.h
 *
 *  Created on: 2014 saus. 21
 *      Author: Gražvidas
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
	void (*Init)(void);
	void (*Enable)(uint8_t state);
	int16_t (*MeasVolt)(uint8_t ch);
	int16_t (*MeasTemp)(void);

}Adc_t;

#endif /* ADC_H_ */
