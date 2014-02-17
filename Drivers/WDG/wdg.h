/*
 * wdg.h
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#ifndef WDG_H_
#define WDG_H_

#include <avr/io.h>
#include <avr/wdt.h>

typedef struct {
	void (*init)(void);
	void (*enable)(uint8_t newState);

}WDG_Interface_t;
extern const WDG_Interface_t WDG;

void WDG_Init(void);
void WDG_Enable(uint8_t newState);

#endif /* WDG_H_ */
