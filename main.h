/*
 * main.h
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include "Drivers/LCD/lcd.h"
#include "Drivers/UART/uart.h"
#include "Drivers/ADC/ADC.h"
#include "Drivers/PWM/pwm.h"
#include "Drivers/WDG/wdg.h"
#include "Modules/Menu/lcd_menu.h"
#include "Modules/PushButtons/buttons_push.h"
#include "Modules/RotaryButtons/buttons_rotary.h"
#include "common.h"

#define F_CPU 8000000UL

void Init(void);
void Init_GPIO(void);

#endif /* MAIN_H_ */
