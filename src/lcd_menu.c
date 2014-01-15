/*
 * lcd_meniu.c
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#include "lcd_menu.h"
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

LEDs_t LEDs = {

};

Settings_t Set = {

};

Profiles_t Prof = {

};

LCD_Menu_t Menu = {
		&LEDs,
		&Set,
		&Prof,
		LCD_Menu_Init,
		LCD_Menu_setOpt,
		LCD_Menu_getOpt,
		{
				LCD_Menu_branch_LEDs,
				LCD_Menu_branch_Set,
				LCD_Menu_branch_Profs,
		},
		{
				"LEDs",
				"Settings",
				"Profiles"
		},
		0xFF,
		0
};

ColorTable_t ColorTable = RED;

void LCD_Menu_branch_LEDs(void)
{
	LCD.Position(1, 1);
	LCD.DataFlow->SendString("leds menu");
	while (1)
	{
		_delay_ms(10);

		if (Menu.getOpt() == B_RETURN)
			break;
	}
}
void LCD_Menu_branch_Set(void)
{
	LCD.Position(1, 1);
	LCD.DataFlow->SendString("set menu");
	while (1)
	{
		_delay_ms(10);

		if (Menu.getOpt() == B_RETURN)
			break;
	}
}

void LCD_Menu_branch_Profs(void)
{
	LCD.Position(1, 1);
	LCD.DataFlow->SendString("profs menu");
	while (1)
	{
		_delay_ms(10);

		if (Menu.getOpt() == B_RETURN)
			break;
	}
}

uint8_t LCD_Menu_getOpt(void)
{
	return Menu.optSelected;
}

void LCD_Menu_setOpt(uint8_t opt)
{
	Menu.optSelected = opt;
}

void LCD_Menu_Init()
{

	LCD.DataFlow->SendCommand(8, 0x01);
	LCD.DataFlow->SendString("Menu init.. SUCCESS");
	_delay_ms(300);
}

void LCD_Menu_PresetColors(uint8_t random) {

	while(1)
	{
		UART.sendByte(ColorTable);
		switch(ColorTable)
		{
			case RED:
//				UART.sendString("\nRed\r");
				LCD.DataFlow->SendString("Red");
				break;

			case ORANGE:
//				UART.sendString("\nOrange\r");
				LCD.DataFlow->SendString("Orange");
				break;

			case YELLOW:
//				UART.sendString("\nYellow\r");
				LCD.DataFlow->SendString("Yellow");
				break;

			case GREEN:
//				UART.sendString("\nGreen\r");
				LCD.DataFlow->SendString("Green");
				break;

			case BLUE:
//				UART.sendString("\nBlue\r");
				LCD.DataFlow->SendString("Blue");
				break;

			case INDIGO:
//				UART.sendString("\nIndigo\r");
				LCD.DataFlow->SendString("Indigo");
				break;

			case VIOLET:
//				UART.sendString("\nViolet\r");
				LCD.DataFlow->SendString("Violet");
				break;

			case WHITE:
//				UART.sendString("\nWhite\r");
				LCD.DataFlow->SendString("White");
				break;

			default:
//				UART.sendString("\nError : LCD_Menu_preset_colors; Default\r");
				break;
		}

		Menu.optSelected = B_VOID;
		PORTC |= 1<<PC5;
		sei();
		while(1)
		{
			asm("nop");
			UART.sendData(&Menu.optSelected, 1);
			UART.sendString(" ", 1);
			if (Menu.optSelected != B_VOID) { break; cli(); }
		}
		PORTC &= ~(1<<PC5);

		switch(Menu.optSelected)
		{
			case B_NEXT:
				ColorTable++;
				if (ColorTable == NUM_OF_COLORS) {
					ColorTable = 0;
				}
				break;

			case B_PREV:
				if (ColorTable > 0) {
					ColorTable--;
				} else {
					ColorTable = NUM_OF_COLORS - 1;
				}
				break;

			case B_SELECT:
				// TODO: add command selection
				//LCD_Menu.optionSelected = OPT_VOID;
				//return;
				break;

			case B_RETURN:
				Menu.optSelected = B_VOID;
				return;
				break;

			default:
				break;
		}


	}
}

void LCD_Menu_CustomColor(uint8_t preview) {

}

void LCD_Menu_SelectCh(uint8_t io) {

}
