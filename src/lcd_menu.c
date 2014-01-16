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
		LCD_Menu_SelectCh,
		{
			LCD_Menu_ChGetData,
			LCD_Menu_ChSetData
		},
		{
			"Get Data",
			"Set Data"
		},
		{
				"0",
				"1",
				"2",
				"3",
				"4",
				"5",
				"6",
				"7",
				"8",
				"9",
				"10",
				"11",
				"12",
				"13",
				"14",
				"15"
		}
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
		LCD_Menu_Choice,
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
	Menu.pos = 0;
	while(1)
	{
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------- LEDs -------");

		status = Menu.choice(2, Menu.leds->funcNames);
		if (status < 0)
			return;

		Menu.leds->branch[status]();
		LCD.DataFlow->SendCommand(8, 0x01);
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
		LCD.DataFlow->SendString("Choose color:");

		status = Menu.choice(NUM_OF_COLORS, Menu.leds->colors->colorNames);
		if (status < 0)
			return SUCC;

		if (io == 0) {
			// light LED
		}
		else {
			// send data
		}
		return SUCC;
	}

	return FAIL;
}

uint8_t LCD_Menu_CustomColor(uint8_t io)
{
	uint8_t idx;

	LCD.Position(1, 1);
	LCD.DataFlow->SendString("Adjust color:");
	LCD.Position(4, 1);
	LCD.DataFlow->SendString("R:     G:     B:");
	LCD.Position(3, 1);
	LCD.DataFlow->SendString("Brightness:    %");

	while(1)
	{
		_delay_ms(5);
		for (idx = 0; idx < 3; idx++) {
				LCD.Position(4, 4 + (idx * 7));
				LCD.DataFlow->SendNumber(0);
		}
		// TODO: add adc measuring function
		LCD.Position(3, 13);
		LCD.DataFlow->SendNumber(0);

		if (Menu.getOpt() == B_RETURN)
			return SUCC;

		if (Menu.getOpt() == B_SELECT)
			break;
	}

	if (io == 0) {
		// light LED
	}
	else {
		// send data
	}
	return SUCC;

//	return FAIL;
}

uint8_t LCD_Menu_SelectCh(uint8_t* ok)
{
	while(1)
	{
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("Select channel:");

		status = Menu.choice(16, Menu.leds->ch->chList);
		if (status < 0) {
			*ok = FAIL;
			return 0xFF;
		}
		LCD.DataFlow->SendCommand(8, 0x01);
		*ok = SUCC;
		break;
	}
	return status;
}

uint8_t LCD_Menu_ChGetData(uint8_t* data, uint8_t* ok)
{
	uint8_t idx;
	uint8_t ch = Menu.leds->ch->selectCh(ok);

	// dummy values for testing
	data[0] = 120;
	data[1] = 170;
	data[2] = 210;
	data[3] = 90;

	if (!*ok)
		return FAIL;

	LCD.Position(1, 1);
	LCD.DataFlow->SendString("Channel ");
	LCD.DataFlow->SendNumber(ch);
	LCD.DataFlow->SendString(" info:");
	LCD.Position(4, 1);
	LCD.DataFlow->SendString("R:     G:     B:");
	LCD.Position(3, 1);
	LCD.DataFlow->SendString("Brightness:    %");

	_delay_ms(5);
	for (idx = 0; idx < 3; idx++) {
			LCD.Position(4, 4 + (idx * 7));
			LCD.DataFlow->SendNumber(data[idx]);
	}

	LCD.Position(3, 13);
	LCD.DataFlow->SendNumber(data[3]);

	while(Menu.getOpt() != B_RETURN);

	return SUCC;
}

uint8_t LCD_Menu_ChSetData(uint8_t* data, uint8_t* ok)
{
	uint8_t ch = Menu.leds->ch->selectCh(ok);
	return SUCC;
}

void LCD_Menu_Colors(void)
{
	while(1)
	{
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("------ Colors ------");

		status = Menu.choice(2, Menu.leds->colors->funcNames);
		if (status < 0)
			return;

		Menu.leds->colors->branch[status](0);
		LCD.DataFlow->SendCommand(8, 0x01);
	}
}

void LCD_Menu_Channels(void)
{
	uint8_t ok;
	uint8_t data[4];

	while(1)
	{
		LCD.Position(1, 1);
		LCD.DataFlow->SendString("----- Channels -----");

		status = Menu.choice(2, Menu.leds->ch->funcNames);
		if (status < 0)
			return;

		Menu.leds->ch->branch[status](data, &ok);
		LCD.DataFlow->SendCommand(8, 0x01);
	}
}

int8_t LCD_Menu_Choice(uint8_t lim, char** names)
{
	uint8_t idx;
	uint8_t numOfRecords = (lim < 3)? lim : 3;

	Menu.setOpt(B_VOID);
	Menu.pos = 0;
	while(1)
	{
			for (idx = 0; idx < numOfRecords; idx++)
			{
				LCD.Position(idx+2, 1);
				LCD.DataFlow->SendString("                  ");
				LCD.Position(idx+2, 3);

				if (Menu.pos <=2 )
					LCD.DataFlow->SendString(names[idx]);
				else
					LCD.DataFlow->SendString(names[Menu.pos-2+idx]);
			}

			if (Menu.pos == 0)
				LCD.Position(2, 1);
			else if (Menu.pos > 0 && Menu.pos < numOfRecords)
				LCD.Position(Menu.pos + 2, 1);
			else
				LCD.Position(4, 1);

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
				if (Menu.pos < lim-1)
					Menu.pos++;
				else
					Menu.pos = 0;
			break;

			case B_PREV:
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
				Menu.pos = 0;
				Menu.setOpt(B_VOID);
				return -1;
			break;
		}

		Menu.setOpt(B_VOID);
	}

	return FAIL;
}
