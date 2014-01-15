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

Colors_t Colors = {
		LCD_Menu_CustomColor,
		LCD_Menu_PresetColors,
		{
				"Custom color",
				"Preset Colors"
		},
		{
				"Red",
				"Orange",
				"Yellow",
				"Green",
				"Blue",
				"Indigo",
				"Violet",
				"White"
		},
		{
				LCD_Menu_CustomColor,
				LCD_Menu_PresetColors
		}
};

Channels_t Ch = {
		LCD_Menu_ChGetData,
		LCD_Menu_ChSetData,
		LCD_Menu_SelectCh
};

LEDs_t LEDs = {
		&Colors,
		&Ch,
		{
				"Channels",
				"Colors"
		},
		{
				LCD_Menu_Channels,
				LCD_Menu_Colors,
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
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------- LEDs -------");

		LCD.Position(Menu.pos+2, 1);
		LCD.DataFlow->SendCharacter(S_ARROW_RIGHT);

		funcName = Menu.leds->funcNames[0];
		LCD.Position(2, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.leds->funcNames[1];
		LCD.Position(3, 3);
		LCD.DataFlow->SendString(funcName);

		status = LCD_Menu_Choice(2, TRUE, NULL);
		if (status < 0)
			return;

		Menu.leds->branch[status]();
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

uint8_t LCD_Menu_PresetColors(uint8_t io)
{
	while(1)
	{
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("Choose a color:");

		status = LCD_Menu_Choice(NUM_OF_COLORS, FALSE, Menu.leds->colors->colorNames);
//		switch(ColorTable)
//		{
//			case RED:
//				LCD.DataFlow->SendString("Red");
//				break;
//
//			case ORANGE:
//				LCD.DataFlow->SendString("Orange");
//				break;
//
//			case YELLOW:
//				LCD.DataFlow->SendString("Yellow");
//				break;
//
//			case GREEN:
//				LCD.DataFlow->SendString("Green");
//				break;
//
//			case BLUE:
//				LCD.DataFlow->SendString("Blue");
//				break;
//
//			case INDIGO:
//				LCD.DataFlow->SendString("Indigo");
//				break;
//
//			case VIOLET:
//				LCD.DataFlow->SendString("Violet");
//				break;
//
//			case WHITE:
//				LCD.DataFlow->SendString("White");
//				break;
//
//			default:
//				LCD.DataFlow->SendString("Error color");
//				break;
//		}

		LCD.DataFlow->SendCommand(8, 0x01);
		funcName = Menu.leds->colors->colorNames[status];
		LCD.DataFlow->SendString(funcName);
		while(1);
		Menu.optSelected = B_VOID;
	}

	return FAIL;
}

uint8_t LCD_Menu_CustomColor(uint8_t preview)
{

	return FAIL;
}

uint8_t LCD_Menu_SelectCh(uint8_t ch, uint8_t io, uint8_t* ok)
{

	return FAIL;
}

uint8_t LCD_Menu_ChGetData(uint8_t* data, uint8_t* ok)
{

	return SUCC;
}

uint8_t LCD_Menu_ChSetData(uint8_t* data, uint8_t* ok)
{

	return SUCC;
}

void LCD_Menu_Colors(void)
{
	while(1)
	{
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------ Colors ------");

		LCD.Position(Menu.pos+2, 1);
		LCD.DataFlow->SendCharacter(S_ARROW_RIGHT);

		funcName = Menu.leds->colors->funcNames[0];
		LCD.Position(2, 3);
		LCD.DataFlow->SendString(funcName);
		funcName = Menu.leds->colors->funcNames[1];
		LCD.Position(3, 3);
		LCD.DataFlow->SendString(funcName);

		status = LCD_Menu_Choice(2, TRUE, NULL);
		if (status < 0)
			return;

		Menu.leds->colors->branch[status](0);
	}
}

void LCD_Menu_Channels(void)
{

}

int8_t LCD_Menu_Choice(uint8_t lim, uint8_t fixed, char** names)
{
	uint8_t i;
	Menu.setOpt(B_VOID);
	LCD.Position(Menu.pos+2, 1);
	LCD.DataFlow->SendCharacter(S_BLANK);
	Menu.pos = 0;
	while(1)
	{
		if (!fixed) {
			if (Menu.pos <= 2)
			{
					for (i = 0; i < 3; i++) {
							LCD.Position(i+2, 1);
							LCD.DataFlow->SendString("                  ");
							LCD.Position(i+2, 3);
							LCD.DataFlow->SendString(names[i]);
					}
			}
			else
			{
					for (i = 0; i < 3; i++) {
							LCD.Position(2+i, 3);
							LCD.DataFlow->SendString("                  ");
							LCD.Position(2+i, 3);
							LCD.DataFlow->SendString(names[Menu.pos-2+i]);
					}
			}
		}

		if (!fixed) {
				if (Menu.pos == 0)
					LCD.Position(2, 1);
				else if (Menu.pos > 0 && Menu.pos < 3)
					LCD.Position(Menu.pos + 2, 1);
				else
					LCD.Position(4, 1);
		}
		else {
				LCD.Position(Menu.pos+2, 1);
		}

		LCD.DataFlow->SendCharacter(S_ARROW_RIGHT);

		while (!Menu.getOpt())
		{
			_delay_ms(10);

			if (Menu.getOpt() != B_VOID)
				break;
		}

		switch (Menu.getOpt())
		{
			case B_NEXT:
				if(fixed)
					LCD.Position(Menu.pos + 2, 1);

				LCD.DataFlow->SendCharacter(S_BLANK);
				if (Menu.pos < lim-1)
					Menu.pos++;
				else
					Menu.pos = 0;
			break;

			case B_PREV:
				if(fixed)
					LCD.Position(Menu.pos + 2, 1);

				LCD.DataFlow->SendCharacter(S_BLANK);
				if (Menu.pos > 0)
					Menu.pos--;
				else
					Menu.pos = lim-1;
			break;

			case B_SELECT:
				LCD.DataFlow->SendCommand(8, 0x01);
				Menu.setOpt(B_VOID);
				return Menu.pos;
			break;

			case B_RETURN:
				LCD.DataFlow->SendCommand(8, 0x01);
				return -1;
			break;
		}


		Menu.setOpt(B_VOID);
	}

	return FAIL;
}
