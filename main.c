/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Graþvidas
 */

#include <avr/io.h>
#include "lcd.h"

#define F_CPU 16000000UL

int main() {

	LCD_Interface.Initialize();

	while(1) {

	}

	return 0;
}
