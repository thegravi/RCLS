/*
 * wdg.c
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#include "wdg.h"

const WDG_Interface_t WDG = {
		WDG_Init,
		WDG_Disable,
		WDT_ChangePrescaler
};

void WDG_Init()
{
	uint8_t prescaler = ms2000;

	WDTCSR |= 1<<WDIE | 1<<WDE;
	WDTCSR = (WDTCSR & 0xD8) | prescaler;
}

void WDG_Disable(uint8_t newState)
{
	if (newState == Disable)
	{
		__asm__ __volatile__ ("cli");
		__asm__ __volatile__ ("wdr");
		MCUSR &= ~(1<<WDRF);
		WDTCSR |= 1<<WDCE | 1<<WDE;
		WDTCSR = 0;
		__asm__ __volatile__("sei");
	}
	else if (newState == Enable)
	{
		// TODO: add enable functionality
	}
}

void WDT_ChangePrescaler(uint8_t prescaler)
{
	__asm__ __volatile__ ("cli");
	__asm__ __volatile__ ("wdr");
	WDTCSR |= 1<<WDCE | 1<<WDE;
	WDTCSR = (WDTCSR & 0xD8) | prescaler;
	WDTCSR |= 1<<WDE;
	__asm__ __volatile__ ("sei");
}

ISR(WDT_vect)
{

}
