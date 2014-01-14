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
		LCD_Menu_Init,
		&LEDs,
		&Set,
		&Prof,
		B_VOID
};

ColorTable_t ColorTable = RED;

void LCD_Menu_Init() {

	// LED Object
//	LCD_Menu.Options.LED.CurrentFunction[0] = LCD_Menu_Preset_colors;
//	LCD_Menu.Options.LED.CurrentFunction[1] = LCD_Menu_Custom_color;
//	LCD_Menu.Options.LED.CurrentFunction[2] = LCD_Menu_ChooseChannel;
//
//	LCD_Menu.Options.LED.CurrentFunctionName[0] = "Preset colors";
//	LCD_Menu.Options.LED.CurrentFunctionName[1] = "Custom color";
//	LCD_Menu.Options.LED.CurrentFunctionName[2] = "Select channel";
//
//	LCD_Menu.Options.LED.PresetColors = LCD_Menu_Preset_colors;
//	LCD_Menu.Options.LED.CustomColor = LCD_Menu_Custom_color;
//	LCD_Menu.Options.LED.ChooseChannel = LCD_Menu_ChooseChannel;
//
////	LCD_Menu.Options.LED.cur
//	LCD_Menu.Options.LED.CurrentSubFunctionName[0] = "ChannelDetails";
//	LCD_Menu.Options.LED.objName = "LED";
//
//	// Settings Object
//	LCD_Menu.Options.Prefs.objName = "Preferences";
//
//	// Profiles Object
//	LCD_Menu.Options.Profs.objName = "Profiles";
//
//	// Menu Object
//	LCD_Menu.Enter 					= LCD_Menu_Enter;
//	LCD_Menu.setFuncLevelDepth 		= LCD_setFuncLevelDepth;
//	LCD_Menu.setSubFuncLevelDepth 	= LCD_setSubFuncLevelDepth;
//	LCD_Menu.getFuncLevelDepth 		= LCD_getFuncLevelDepth;
//	LCD_Menu.getSubFuncLevelDepth 	= LCD_getSubFuncLevelDepth;
//	LCD_Menu.optionSelected 		= B_VOID;
//	LCD_Menu.subFuncPos 			= 0;
//	LCD_Menu.funcPos 				= 0;
//	LCD_Menu.selectedBranch 		= 0;
//
//	// Options Object
//	LCD_Menu.Options.LED_color 		= LCD_Menu_LED_color;
//	LCD_Menu.Options.Preferences 	= LCD_Menu_Preferences;
//	LCD_Menu.Options.Profiles 		= LCD_Menu_Profiles;
//
//	LCD_Menu.Options.CurrentFunctionName[0] = LCD_Menu.Options.LED.objName;
//	LCD_Menu.Options.CurrentFunctionName[1] = LCD_Menu.Options.Prefs.objName;
//	LCD_Menu.Options.CurrentFunctionName[2] = LCD_Menu.Options.Profs.objName;
//
//	LCD_Menu.Options.CurrentFunction[0] = LCD_Menu.Options.LED_color;
//	LCD_Menu.Options.CurrentFunction[1] = LCD_Menu.Options.Preferences;
//	LCD_Menu.Options.CurrentFunction[2] = LCD_Menu.Options.Profiles;
//
//	// MAP declarations
//	LCD_Menu.MAP[0].funcQuantity = 3;
//	LCD_Menu.MAP[0].level1objName[0] = LCD_Menu.Options.LED.CurrentFunctionName[0];
//	LCD_Menu.MAP[0].level1objName[1] = LCD_Menu.Options.LED.CurrentFunctionName[1];
//    LCD_Menu.MAP[0].level1objName[2] = LCD_Menu.Options.LED.CurrentFunctionName[2];
//
//    LCD_Menu.MAP[0].level1objFunc[0] = LCD_Menu.Options.LED.CurrentFunction[0];
//    LCD_Menu.MAP[0].level1objFunc[1] = LCD_Menu.Options.LED.CurrentFunction[1];
//    LCD_Menu.MAP[0].level1objFunc[2] = LCD_Menu.Options.LED.CurrentFunction[2];
//
//	LCD_Menu.MAP[1].funcQuantity = 0;
//	LCD_Menu.MAP[2].funcQuantity = 0;

	LCD.DataFlow->SendCommand(8, 0x01);
	LCD.DataFlow->SendString("LCD Menu init");_delay_ms(400);
}


void LCD_setSubFuncLevelDepth(int8_t pos) {
	Menu.subFuncPos = Menu.subFuncPos + pos;
}

void LCD_setFuncLevelDepth(int8_t pos) {
	Menu.funcPos = Menu.funcPos + pos;
}

uint8_t LCD_getSubFuncLevelDepth(void) { return Menu.subFuncPos; }
uint8_t LCD_getFuncLevelDepth(void) { return Menu.funcPos; }

//void LCD_Menu_Enter() {
//
//	char* functionName = 0;
//
//	DDRC |= 1<<PC5;
//
//	LCD_Menu_BottomLineDeclaration();
//	functionName = LCD_Menu.Options.CurrentFunctionName[0];
//	LCD_Interface.DataFlow.SendString(functionName);
//
//	while(1) {
//
//		LCD_Menu_Option_Selection(2);
//		LCD_Menu.optionSelected = B_VOID;
//
//			while(1)
//			{
//				UART.sendString("i");
//				asm("nop");
////				PORTC |= 1<<PC5;
////				_delay_ms(50);
//				if (LCD_Menu.optionSelected != B_VOID) { break;}
//			}
//
//	}
//
//}

void LCD_Menu_PresetColors(uint8_t random) {

	while(1)
	{
		LCD_Menu_BottomLineDeclaration();
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
			UART.sendData(&Menu.optSelected, 1);UART.sendString(" ");
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

void LCD_Menu_Preferences() {

}

void LCD_Menu_Profiles() {

}

void LCD_Menu_OptionSelection() {

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
