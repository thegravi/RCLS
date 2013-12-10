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

LCD_Menu_t LCD_Menu = {LCD_Menu_Initialize};
ColorTable_t ColorTable = Red;

void LCD_Menu_Initialize() {

	// LED Object
	LCD_Menu.Options.LED.CurrentFunction[0] = LCD_Menu_Preset_colors;
	LCD_Menu.Options.LED.CurrentFunction[1] = LCD_Menu_Custom_color;
	LCD_Menu.Options.LED.CurrentFunction[2] = LCD_Menu_ChooseChannel;

	LCD_Menu.Options.LED.CurrentFunctionName[0] = "Preset colors";
	LCD_Menu.Options.LED.CurrentFunctionName[1] = "Custom color";
	LCD_Menu.Options.LED.CurrentFunctionName[2] = "Select channel";

	LCD_Menu.Options.LED.PresetColors 		= LCD_Menu_Preset_colors;
	LCD_Menu.Options.LED.CustomColor 		= LCD_Menu_Custom_color;
	LCD_Menu.Options.LED.ChooseChannel 		= LCD_Menu_ChooseChannel;

//	LCD_Menu.Options.LED.cur
	LCD_Menu.Options.LED.CurrentSubFunctionName[0] = "ChannelDetails";
	LCD_Menu.Options.LED.objName = "LED";

	// Settings Object
	LCD_Menu.Options.Prefs.objName = "Preferences";

	// Profiles Object
	LCD_Menu.Options.Profs.objName = "Profiles";

	// Menu Object
	LCD_Menu.Enter 					= LCD_Menu_Enter;
	LCD_Menu.setFuncLevelDepth 		= LCD_setFuncLevelDepth;
	LCD_Menu.setSubFuncLevelDepth 	= LCD_setSubFuncLevelDepth;
	LCD_Menu.getFuncLevelDepth 		= LCD_getFuncLevelDepth;
	LCD_Menu.getSubFuncLevelDepth 	= LCD_getSubFuncLevelDepth;
	LCD_Menu.optionSelected 		= OPT_VOID;
	LCD_Menu.subFuncPos 			= 0;
	LCD_Menu.funcPos 				= 0;
	LCD_Menu.selectedBranch 		= 0;

	// Options Object
	LCD_Menu.Options.LED_color 		= LCD_Menu_LED_color;
	LCD_Menu.Options.Preferences 	= LCD_Menu_Preferences;
	LCD_Menu.Options.Profiles 		= LCD_Menu_Profiles;

	LCD_Menu.Options.CurrentFunctionName[0] = LCD_Menu.Options.LED.objName;
	LCD_Menu.Options.CurrentFunctionName[1] = LCD_Menu.Options.Prefs.objName;
	LCD_Menu.Options.CurrentFunctionName[2] = LCD_Menu.Options.Profs.objName;

	LCD_Menu.Options.CurrentFunction[0] = LCD_Menu.Options.LED_color;
	LCD_Menu.Options.CurrentFunction[1] = LCD_Menu.Options.Preferences;
	LCD_Menu.Options.CurrentFunction[2] = LCD_Menu.Options.Profiles;

	// MAP declarations
	LCD_Menu.MAP[0].funcQuantity = 3;
	LCD_Menu.MAP[0].level1objName[0] = LCD_Menu.Options.LED.CurrentFunctionName[0];
	LCD_Menu.MAP[0].level1objName[1] = LCD_Menu.Options.LED.CurrentFunctionName[1];
    LCD_Menu.MAP[0].level1objName[2] = LCD_Menu.Options.LED.CurrentFunctionName[2];

    LCD_Menu.MAP[0].level1objFunc[0] = LCD_Menu.Options.LED.CurrentFunction[0];
    LCD_Menu.MAP[0].level1objFunc[1] = LCD_Menu.Options.LED.CurrentFunction[1];
    LCD_Menu.MAP[0].level1objFunc[2] = LCD_Menu.Options.LED.CurrentFunction[2];

	LCD_Menu.MAP[1].funcQuantity = 0;
	LCD_Menu.MAP[2].funcQuantity = 0;
}


void LCD_setSubFuncLevelDepth(int8_t pos) {
	LCD_Menu.subFuncPos = LCD_Menu.subFuncPos + pos;
}

void LCD_setFuncLevelDepth(int8_t pos) {
	LCD_Menu.funcPos = LCD_Menu.funcPos + pos;
}

uint8_t LCD_getSubFuncLevelDepth(void) { return LCD_Menu.subFuncPos; }
uint8_t LCD_getFuncLevelDepth(void) { return LCD_Menu.funcPos; }

void LCD_Menu_Enter() {

	char* functionName = NULL;

	DDRC |= 1<<PC5;

	LCD_Menu_BottomLineDeclaration();
	functionName = LCD_Menu.Options.CurrentFunctionName[0];
	LCD_Interface.DataFlow.SendString(functionName);

	while(1) {

		LCD_Menu_Option_Selection(2);

			while(1)
			{
				asm("nop");
				if (LCD_Menu.optionSelected != OPT_VOID) { break;}
			}

	}

}

void LCD_Menu_LED_color() {

}

void LCD_Menu_ChannelDetails() {

}

void LCD_Menu_Preset_colors(uint8_t random) {

//	uint8_t color = White;
	while(1)
	{
		LCD_Menu_BottomLineDeclaration();



/*		if (random == 1 )
		{
			LCD_Interface.DataFlow.SendString("preset viduje!");
		}
		else if (random == 0)
		{

		}*/

		switch(ColorTable) {

		case Red:
			UART.sendString("\nRed\r");
			break;

		case Orange:
			UART.sendString("\nOrange\r");
			break;

		case Yellow:
			UART.sendString("\nYellow\r");
			break;

		case Green:
			UART.sendString("\nGreen\r");
			break;

		case Blue:
			UART.sendString("\nBlue\r");
			break;

		case Indigo:
			UART.sendString("\nIndigo\r");
			break;

		case Violet:
			UART.sendString("\nViolet\r");
			break;

		case White:
			UART.sendString("\nWhite\r");
			break;

		default:
			// should never happen
			UART.sendString("\nError : LCD_Menu_preset_colors; Default\r");
			break;
		}

		while(LCD_Menu.optionSelected == OPT_VOID) { }

		// TODO: add ColorTable check for boundaries
		if (LCD_Menu.optionSelected == OPT_NEXT)
		{
			ColorTable++;
		}
		else if (LCD_Menu.optionSelected == OPT_PREV)
		{
			ColorTable--;
		}

	}
}

void LCD_Menu_Custom_color(uint8_t preview) {

}

void LCD_Menu_ChooseChannel(uint8_t io) {

}

void LCD_Menu_Preferences() {

}

void LCD_Menu_Profiles() {

}

void LCD_Menu_Option_Selection(uint8_t subFuncQuantity) {

	cli();

	char* functionName = NULL;

	if (LCD_Menu.getFuncLevelDepth() == 1)
	{
		subFuncQuantity = LCD_Menu.MAP[LCD_Menu.selectedBranch].funcQuantity-1;
	}

	switch(LCD_Menu.optionSelected)
	{
		case OPT_NEXT:

			if ((LCD_Menu.getSubFuncLevelDepth() >= 0) && (LCD_Menu.getSubFuncLevelDepth() < subFuncQuantity))
			{
				LCD_Menu.setSubFuncLevelDepth(1);
			}
			else if (LCD_Menu.getSubFuncLevelDepth() == subFuncQuantity)
			{
				LCD_Menu.setSubFuncLevelDepth(0-subFuncQuantity);

			}

			LCD_Menu_BottomLineDeclaration();
			if (LCD_Menu.getFuncLevelDepth() == 0)
			{
				functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.getSubFuncLevelDepth()];
			}
			else if (LCD_Menu.getFuncLevelDepth() == 1)
			{
				functionName = LCD_Menu.MAP[LCD_Menu.selectedBranch].level1objName[LCD_Menu.getSubFuncLevelDepth()];
			}

			break;

		case OPT_PREV:

			if ((LCD_Menu.getSubFuncLevelDepth() > 0) && (LCD_Menu.getSubFuncLevelDepth() <= subFuncQuantity))
			{
				LCD_Menu.setSubFuncLevelDepth(-1);
			}
			else if (LCD_Menu.getSubFuncLevelDepth() == 0)
			{
				LCD_Menu.setSubFuncLevelDepth(subFuncQuantity);
			}

			LCD_Menu_BottomLineDeclaration();

			if (LCD_Menu.getFuncLevelDepth() == 0)
			{
				functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.getSubFuncLevelDepth()];
			}
			else if (LCD_Menu.getFuncLevelDepth() == 1)
			{
				functionName = LCD_Menu.MAP[LCD_Menu.selectedBranch].level1objName[LCD_Menu.getSubFuncLevelDepth()];
			}

			break;

		case OPT_SELECT:

			if (LCD_Menu.getFuncLevelDepth() == 0)
			{
				LCD_Menu.setFuncLevelDepth(1);
				LCD_Menu.selectedBranch = LCD_Menu.getSubFuncLevelDepth();
				LCD_Menu_BottomLineDeclaration();
				functionName = LCD_Menu.MAP[LCD_Menu.selectedBranch].level1objName[0];
			}
			else if (LCD_Menu.getFuncLevelDepth() == 1)
			{
				LCD_Menu.MAP[LCD_Menu.selectedBranch].level1objFunc[LCD_Menu.getSubFuncLevelDepth()](1);
			}

			break;

		case OPT_RETURN:

			LCD_Menu.setFuncLevelDepth(0-LCD_Menu.getFuncLevelDepth());
			LCD_Menu.setSubFuncLevelDepth(0-LCD_Menu.getSubFuncLevelDepth());

			LCD_Menu_BottomLineDeclaration();
			functionName = LCD_Menu.Options.CurrentFunctionName[0];
			break;

		case OPT_VOID:
			functionName = "";
			break;
		default:
			break;
	}

			UART.sendString("\r");
			UART.sendByte(subFuncQuantity);
			UART.sendString(" ");
			UART.sendByte(LCD_Menu.getSubFuncLevelDepth());
			UART.sendString(" ");
			UART.sendByte(LCD_Menu.getFuncLevelDepth());
			UART.sendString("\n\r");


	LCD_Interface.DataFlow.SendString(functionName);
	LCD_Menu.optionSelected = OPT_VOID;

	sei();
}

void LCD_Menu_BottomLineDeclaration(/*char* title*/) {

	LCD_Interface.DataFlow.SendCommand(8, 0x01);
	LCD_Interface.Position(1, 1);
	LCD_Interface.DataFlow.SendString("Menu");
	LCD_Interface.Position(2, 1);
	LCD_Interface.DataFlow.SendCharacter(S_BULLET);
	LCD_Interface.DataFlow.SendCharacter(S_BLANK);
	LCD_Interface.Position(2, 3);
	LCD_Interface.DataFlow.SendString("              ");
	LCD_Interface.Position(2, 3);
}
