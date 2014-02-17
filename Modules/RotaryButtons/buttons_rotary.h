/*
 * buttons_rotary.h
 *
 *  Created on: 2014 saus. 21
 *      Author: Gražvidas
 */

#ifndef BUTTONS_ROTARY_H_
#define BUTTONS_ROTARY_H_

#include "../../Drivers/ADC/ADC.h"

#define DDR_ROT		 	DDRC
#define ROT_CH_R	 	PC5
#define ROT_CH_G	 	PC4
#define ROT_CH_B	 	PC5
#define ROT_CH_BRIGH	PC5

typedef struct {
	void (*Init)(void);

}Rotary_Interface_t;

extern const Rotary_Interface_t Rotary;

void ROTARY_Init(void);

#endif /* BUTTONS_ROTARY_H_ */
