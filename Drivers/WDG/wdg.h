/*
 * wdg.h
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#ifndef WDG_H_
#define WDG_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../common.h"
#include <avr/wdt.h>

#define WDG_RESET() __asm__ __volatile__ ("wdr")

// Fosc = 128 kHz
enum {
	ms16=0,
	ms32,
	ms64,
	ms125,
	ms250,
	ms500,
	ms1000,
	ms2000,
	ms4000=10,
	ms8000
};

typedef struct {
	void (*init)(void);
	void (*disable)(uint8_t newState);
	void (*changePrescaler)(uint8_t prescaler);

}WDG_Interface_t;
extern const WDG_Interface_t WDG;

void WDG_Init(void);
void WDG_Disable(uint8_t newState);
void WDT_ChangePrescaler(uint8_t prescaler);

#endif /* WDG_H_ */
