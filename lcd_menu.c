/*
 * lcd_meniu.c
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#include "lcd_menu.h"
#include <avr/io.h>

LCD_Menu_t LCD_Menu = {LCD_Menu_enter,
					  {LCD_Menu_LED_color,
					   LCD_Menu_Preferences,
					   LCD_Menu_Channels,
					   LCD_Menu_Profiles}
					  };

void LCD_Menu_enter() {

	//LCD_Menu.Options

	uint8_t option = 0;

	switch(option)
	{


	default:
		break;

	}

}

void LCD_Menu_LED_color() {

}

void LCD_Menu_Preferences() {

}

void LCD_Menu_Channels() {

}

void LCD_Menu_Profiles() {

}
