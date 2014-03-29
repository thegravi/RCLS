 /*
 * lcd_meniu.c
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#include "lcd_menu.h"

Colors_t Colors = {
		LCD_Menu_CustomColor,
		LCD_Menu_PresetColors,
		{
			LCD_Menu_CustomColor,
			LCD_Menu_PresetColors
		},
		{
			"sukurti spalv_a",
			"pasirinkti spalv_a"
		},
		{
			"raudona",
			"oran_zin_e",
			"geltona",
			"_zalia",
			"m_elyna",
			"indigo",
			"violetin_e",
			"balta"
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
			"gauti duomenis",
			"si_usti duomenis"
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
			LCD_Menu_Channels,
			LCD_Menu_Colors,
		},
		{
			"kanalai",
			"spalvos"
		}
};

Settings_t Set = {

};

Profiles_t Prof = {

};

LCD_Menu_Interface_t Menu = {
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
			"_sviesa",
			"nustatymai",
			"profiliai"
		},
		0xFF,
		0
};

ColorTable_t ColorTable = RED;

void LCD_Menu_branch_LEDs(void)
{
//	Menu.pos = 0;
	while(1)
	{
		LCD.Position(1, 1);
		LCD.SendString("------ _sviesa ------");

		status = Menu.choice(2, Menu.leds->funcNames);
		if (status < 0)
			return;

		Menu.leds->branch[status]();
	}
}
void LCD_Menu_branch_Set(void)
{
	LCD.Position(1, 1);
	LCD.SendString("-- nustatymai --");

	while (Menu.getOpt() != B_RETURN)
	{
			_delay_ms(10);

			if (Menu.getOpt() == B_RETURN)
				break;
	}
	Menu.setOpt(B_VOID);
}

void LCD_Menu_branch_Profs(void)
{
	LCD.Position(1, 1);
	LCD.SendString("--- profiliai --");

	while (Menu.getOpt() != B_RETURN)
	{
		_delay_ms(10);

		if (Menu.getOpt() == B_RETURN)
			break;
	}
	Menu.setOpt(B_VOID);
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
	LCD.SendCommand(8, 0x01);
	_delay_ms(300);
}

uint8_t LCD_Menu_PresetColors(uint8_t io, uint8_t* data)
{
	Pwm.init();
	while(1)
	{
		LCD.Position(1, 1);
		LCD.SendString("pasirinkti spalv_a:");

		status = Menu.choice(NUM_OF_COLORS, Menu.leds->colors->colorNames);
		if (status < 0)
		{
			Pwm.enable(Disable);
			return SUCC;
		}

		if (io) {

		}

		Pwm.enable(Disable);
		return SUCC;
	}

	return FAIL;
}

uint8_t LCD_Menu_CustomColor(uint8_t io, uint8_t* data)
{
	uint8_t idx;
	uint8_t adcData[4];
	memset(adcData, 0, 4);

	LCD.Position(1, 1);
	LCD.SendString("nustatyti spalv_a:");
	LCD.Position(4, 1);
	LCD.SendString("R:     G:     B:");
	LCD.Position(3, 1);
	LCD.SendString("ry_skumas:    %");

	Pwm.init();
	while(1)
	{
		_delay_ms(100);
		for (idx = 0; idx < 2; idx++)
		{
			Adc.enable(Enable);
			adcData[idx] = Adc.measVolt(4+idx);

			LCD.Position(4, 4 + (idx * 7));
			LCD.SendNumber(adcData[idx]);

			Pwm.setIntensity(idx, adcData[idx]);

			if (adcData[idx] > 10 && adcData[idx] < 100)
				LCD.SendString(" ");
			else if (adcData[idx] < 10)
				LCD.SendString("  ");

			_delay_ms(20);
		}

		LCD.Position(3, 13);
		LCD.SendNumber(0);

		if (adcData[idx] > 10 && adcData[idx] < 100)
			LCD.SendString(" ");
		else if (adcData[idx] < 10)
			LCD.SendString("  ");

		if (Menu.getOpt() == B_RETURN)
		{
			Pwm.enable(Disable);
			Adc.enable(Disable);
			return SUCC;
		}

		if (Menu.getOpt() == B_SELECT)
			break;
	}

	if (io == 0) {
		// light LED
	}
	else {
		// send data
	}

	Pwm.enable(Disable);
	Adc.enable(Disable);
	return SUCC;

//	return FAIL;
}

uint8_t LCD_Menu_SelectCh(uint8_t* ok)
{
	while(1)
	{
		LCD.Position(1, 1);
		LCD.SendString("pasirinkti kanal_a:");

		status = Menu.choice(16, Menu.leds->ch->chList);
		LCD.SendCommand(8, 0x01);

		if (status < 0) {
			*ok = FAIL;
			return 0xFF;
		}

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
	LCD.SendString("kanalas ");
	LCD.SendNumber(ch);
	LCD.SendString(" info:");
	LCD.Position(4, 1);
	LCD.SendString("r:     _z:     b:");
	LCD.Position(3, 1);
	LCD.SendString("ry_skumas:    %");

	_delay_ms(5);
	for (idx = 0; idx < 3; idx++) {
			LCD.Position(4, 4 + (idx * 7));
			LCD.SendNumber(data[idx]);
	}

	LCD.Position(3, 13);
	LCD.SendNumber(data[3]);

	while(Menu.getOpt() != B_RETURN);

	return SUCC;
}

uint8_t LCD_Menu_ChSetData(uint8_t* data, uint8_t* ok)
{
	uint8_t ch = Menu.leds->ch->selectCh(ok);

	if (!*ok)
		return FAIL;

	while(1)
	{
		LCD.Position(1, 1);
		LCD.SendString("------ spalvos -----");

		status = Menu.choice(2, Menu.leds->colors->funcNames);
		if (status < 0)
			return FAIL;

		Menu.leds->colors->branch[status](1, data);
		LCD.SendCommand(8, 0x01);
	}

	return SUCC;
}

void LCD_Menu_Colors(void)
{
	while(1)
	{
		LCD.Position(1, 1);
		LCD.SendString("------ spalvos -----");

		status = Menu.choice(2, Menu.leds->colors->funcNames);
		if (status < 0)
			return;

		Menu.leds->colors->branch[status](0, NULL);
		LCD.SendCommand(8, 0x01);
	}
}

void LCD_Menu_Channels(void)
{
	uint8_t ok;
	uint8_t data[4];

	while(1)
	{
		LCD.Position(1, 1);
		LCD.SendString("------ kanalai -----");

		status = Menu.choice(2, Menu.leds->ch->funcNames);
		if (status < 0)
			return;

		Menu.leds->ch->branch[status](data, &ok);
		LCD.SendCommand(8, 0x01);
	}
}

int8_t LCD_Menu_Choice(uint8_t lim, char** names)
{
	uint8_t idx;
	uint8_t numOfRecords = (lim < 3)? lim : 3;
	uint8_t pos = 0;
	uint8_t pos_color = 0;

	Menu.setOpt(B_VOID);
	Menu.pos = 0;
	while(1)
	{
			for (idx = 0; idx < numOfRecords; idx++)
			{
				LCD.Position(idx + 2, 1);
				LCD.SendString("                  ");
				LCD.Position(idx + 2, 3);

				if (Menu.pos <=2 )
					pos = idx;
				else
					pos = Menu.pos-2 + idx;

				LCD.SendString(names[pos]);
			}

			if (Pwm.f_enable)
			{
				Pwm.setIntensity(Red, Color_TABLE[pos_color][0]);
				Pwm.setIntensity(Green, Color_TABLE[pos_color][1]);
				Pwm.setIntensity(Blue, Color_TABLE[pos_color][2]);
			}

			if (Menu.pos == 0)
				pos = 2;
			else if (Menu.pos > 0 && Menu.pos < numOfRecords)
				pos = Menu.pos + 2;
			else
				pos = 4;

			LCD.Position(pos, 1);

		LCD.SendCharacter(S_ARROW_RIGHT);

		while (!Menu.getOpt())
		{
			_delay_ms(10);
			WDG_RESET();

			if (Menu.getOpt() != B_VOID)
				break;
		}

		switch (Menu.getOpt())
		{
			case B_NEXT:
				Menu.pos = (Menu.pos < lim-1) ? Menu.pos+1 : 0;
				if (Pwm.f_enable)
					pos_color = (pos_color == NUM_OF_COLORS-1) ? 0 : pos_color+1;
			break;

			case B_PREV:
				Menu.pos = (Menu.pos > 0) ? Menu.pos-1 : (lim - 1);

				if (Pwm.f_enable)
					pos_color = (pos_color == 0) ? NUM_OF_COLORS-1 : pos_color-1;
			break;

			case B_SELECT:
				LCD.SendCommand(8, 0x01);
				Menu.setOpt(B_VOID);

				if (Pwm.f_enable)
					return pos_color;

				return (uint8_t)Menu.pos;
			break;

			case B_RETURN:
				LCD.SendCommand(8, 0x01);
				Menu.pos = 0;
				Menu.setOpt(B_VOID);
				return -1;
			break;
		}

		Menu.setOpt(B_VOID);
	}

	return FAIL;
}
