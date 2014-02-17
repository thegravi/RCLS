/*
 * buttons_rotary.c
 *
 *  Created on: 2014 saus. 21
 *      Author: Gražvidas
 */

#include "buttons_rotary.h"

Rotary_Interface_t Rotary = {
		ROTARY_Init
};

void ROTARY_Init()
{
	DDR_ROT &= ~(1<<ROT_CH_R) & ~(1<<ROT_CH_G) & ~(1<<ROT_CH_B) & ~(1<<ROT_CH_BRIGH);
	Adc.Init();
}
