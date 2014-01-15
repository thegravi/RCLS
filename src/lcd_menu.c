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
#include "common.h"

LEDs_t LEDs = {
		LCD_Menu_CustomColor,
		LCD_Menu_PresetColors,
		&Ch,
		{
				"Channels",
				"Colors"
		}

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
	while(1)
	{
		LCD.Position(Menu.pos+2, 1);
		LCD.DataFlow->SendCharacter(S_ARROW_RIGHT);

		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------- Menu -------");
		funcName = Menu.leds->funcNames[0];
		LCD.Position(2, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.leds->funcNames[1];
		LCD.Position(3, 3);
		LCD.DataFlow->SendString(funcName);

		while (!Menu.getOpt())
		{
			_delay_ms(10);

			if (Menu.getOpt() == B_VOID)
				break;
		}

		switch (Menu.getOpt())
		{
			case B_NEXT:
				LCD.Position(Menu.pos+2, 1);
				LCD.DataFlow->SendCharacter(S_BLANK);
				if (Menu.pos < 1)
					Menu.pos++;
				else
					Menu.pos = 0;
			break;

			case B_PREV:
				LCD.Position(Menu.pos+2, 1);
				LCD.DataFlow->SendCharacter(S_BLANK);
				if (Menu.pos > 0)
					Menu.pos--;
				else
					Menu.pos = 1;
			break;

			case B_SELECT:
				Menu.setOpt(B_VOID);
	//			Menu.branch[Menu.pos]();
			break;

			case B_RETURN:
				return;
			break;
		}
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

uint8_t LCD_Menu_PresetColors(uint8_t random) {

	while(1)
	{
		UART.sendByte(ColorTable);
		switch(ColorTable)
		{
			case RED:
				LCD.DataFlow->SendString("Red");
				break;

			case ORANGE:
				LCD.DataFlow->SendString("Orange");
				break;

			case YELLOW:
				LCD.DataFlow->SendString("Yellow");
				break;

			case GREEN:
				LCD.DataFlow->SendString("Green");
				break;

			case BLUE:
				LCD.DataFlow->SendString("Blue");
				break;

			case INDIGO:
				LCD.DataFlow->SendString("Indigo");
				break;

			case VIOLET:
				LCD.DataFlow->SendString("Violet");
				break;

			case WHITE:
				LCD.DataFlow->SendString("White");
				break;

			default:
				LCD.DataFlow->SendString("Error color");
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
				return 0;
				break;

			default:
				break;
		}


	}
}

uint8_t LCD_Menu_CustomColor(uint8_t preview) {

}

void LCD_Menu_SelectCh(uint8_t io) {

}
