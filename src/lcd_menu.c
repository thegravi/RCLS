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
void LCD_Menu_setOpt(uint8_t opt);
uint8_t LCD_Menu_getOpt(void);
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
				"LEDs",
				"Settings",
				"Profiles"
		},
		B_VOID,
		0
};

ColorTable_t ColorTable = RED;

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

/*void LCD_Menu_OptionSelection() {

	cli();
	uint8_t subFuncQuantity = 2;
	char* functionName = 0;

	switch(Menu.optSelected)
	{
		case B_NEXT:

			if ((Menu.getSubFuncLevelDepth() >= 0) && (Menu.getSubFuncLevelDepth() < subFuncQuantity))
					Menu.setSubFuncLevelDepth(1);
			else if (Menu.getSubFuncLevelDepth() == subFuncQuantity)
					Menu.setSubFuncLevelDepth(0-subFuncQuantity);

			LCD_Menu_BottomLineDeclaration();
			if (Menu.getFuncLevelDepth() == 0)
			{
				functionName = Menu.Options.CurrentFunctionName[Menu.getSubFuncLevelDepth()];
			}
			else if (Menu.getFuncLevelDepth() == 1)
			{
				functionName = Menu.MAP[Menu.selectedBranch].level1objName[Menu.getSubFuncLevelDepth()];
			}

			break;

		case B_PREV:

			if ((Menu.getSubFuncLevelDepth() > 0) && (Menu.getSubFuncLevelDepth() <= subFuncQuantity))
			{
				Menu.setSubFuncLevelDepth(-1);
			}
			else if (Menu.getSubFuncLevelDepth() == 0)
			{
				Menu.setSubFuncLevelDepth(subFuncQuantity);
			}

			LCD_Menu_BottomLineDeclaration();

			if (Menu.getFuncLevelDepth() == 0)
			{
				functionName = Menu.Options.CurrentFunctionName[Menu.getSubFuncLevelDepth()];
			}
			else if (Menu.getFuncLevelDepth() == 1)
			{
				functionName = Menu.MAP[Menu.selectedBranch].level1objName[Menu.getSubFuncLevelDepth()];
			}

			break;

		case B_SELECT:

			if (Menu.getFuncLevelDepth() == 0)
			{
				Menu.setFuncLevelDepth(1);
				Menu.selectedBranch = Menu.getSubFuncLevelDepth();
				LCD_Menu_BottomLineDeclaration();
				functionName = Menu.MAP[Menu.selectedBranch].level1objName[0];
			}
			else if (Menu.getFuncLevelDepth() == 1)
			{
				Menu.MAP[Menu.selectedBranch].level1objFunc[Menu.getSubFuncLevelDepth()](1);
				LCD_Menu_BottomLineDeclaration();
				Menu.setFuncLevelDepth(0-Menu.getFuncLevelDepth());
				Menu.setSubFuncLevelDepth(0-Menu.getSubFuncLevelDepth());
				functionName = Menu.Options.CurrentFunctionName[0];
			}

			break;

		case B_RETURN:

			Menu.setFuncLevelDepth(0-Menu.getFuncLevelDepth());
			Menu.setSubFuncLevelDepth(0-Menu.getSubFuncLevelDepth());

			LCD_Menu_BottomLineDeclaration();
			functionName = Menu.Options.CurrentFunctionName[0];
			break;

		case B_VOID:
			functionName = "";
			break;
		default:
			break;
	}

			UART.sendString("\r");
			UART.sendByte(subFuncQuantity);
			UART.sendString(" ");
			UART.sendByte(Menu.getSubFuncLevelDepth());
			UART.sendString(" ");
			UART.sendByte(Menu.getFuncLevelDepth());
			UART.sendString("\n\r");


			LCD.DataFlow->SendString(functionName);
	Menu.optSelected = B_VOID;

	sei();
}

void LCD_Menu_BottomLineDeclaration() {

	LCD.DataFlow->SendCommand(8, 0x01);
	LCD.Position(1, 1);
	LCD.DataFlow->SendString("Menu");
	LCD.Position(2, 1);
	LCD.DataFlow->SendCharacter(S_BULLET);
	LCD.DataFlow->SendCharacter(S_BLANK);
	LCD.Position(2, 3);
	LCD.DataFlow->SendString("              ");
	LCD.Position(2, 3);
}
*/
