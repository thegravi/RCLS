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


void LCD_Menu_Initialize() {

	// LED Object
	LCD_Menu.Options.LED.CurrentFunction[0] = LCD_Menu_Preset_colors;
	LCD_Menu.Options.LED.CurrentFunction[1] = LCD_Menu_Custom_color;
	LCD_Menu.Options.LED.CurrentFunction[2] = LCD_Menu_ChooseChannel;

	LCD_Menu.Options.LED.CurrentFunctionName[0] = "Preset colors";
	LCD_Menu.Options.LED.CurrentFunctionName[1] = "Custom color";
	LCD_Menu.Options.LED.CurrentFunctionName[2] = "Choose a channel";

	LCD_Menu.Options.LED.PresetColors 	 = LCD_Menu_Preset_colors;
	LCD_Menu.Options.LED.CustomColor	 = LCD_Menu_Custom_color;
	LCD_Menu.Options.LED.ChooseChannel	 = LCD_Menu_ChooseChannel;

	LCD_Menu.Options.LED.CurrentSubFunctionName[0] 	= "ChannelDetails";
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
	LCD_Menu.bottomThreshold 		= 0;
	LCD_Menu.topThreshold			= 2;

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

	char* functionName;
	DDRC |= 1<<PC5;
	LCD_Interface.DataFlow.SendCommand(8, 0x01);
	LCD_Interface.Position(1, 1);
	LCD_Interface.DataFlow.SendString("Menu");
	LCD_Interface.Position(2, 1);
	LCD_Interface.DataFlow.SendCharacter(S_BULLET);
	LCD_Interface.DataFlow.SendCharacter(S_BLANK);
	LCD_Interface.Position(2, 3);
	functionName = LCD_Menu.Options.CurrentFunctionName[0];
	LCD_Interface.DataFlow.SendString(functionName);

	while(1) {

		LCD_Menu_Option_Selection();

			while(1)
			{
				asm("nop");
				if (LCD_Menu.optionSelected != OPT_VOID) { break;}
			}
	}

}

void LCD_Menu_LED_color() {

}

void LCD_Menu_Preset_colors(uint8_t random) {

}

void LCD_Menu_Custom_color(uint8_t preview) {

}

void LCD_Menu_ChooseChannel(uint8_t io) {

}

void LCD_Menu_Preferences() {

}

void LCD_Menu_Channels() {

}

void LCD_Menu_Profiles() {

}
/*
 * fLevel (main commands) - 0-3 [x][]
 * fQueue (sub commands)  - 1-3 [][x]
 */
void LCD_Menu_Option_Selection() {

	char* functionName;
	//uint8_t levelDepth = LCD_Menu.getFuncLevelDepth();
	//uint8_t subLevelDepth = LCD_Menu.getSubFuncLevelDepth();


			switch(LCD_Menu.optionSelected)
			{
				case OPT_NEXT:

					if ((LCD_Menu.getSubFuncLevelDepth() >= LCD_Menu.bottomThreshold) && (LCD_Menu.getSubFuncLevelDepth() < LCD_Menu.topThreshold))
					{
						LCD_Menu.setSubFuncLevelDepth(1);
					}
					else if (LCD_Menu.getSubFuncLevelDepth() == LCD_Menu.topThreshold)
					{
						LCD_Menu.setSubFuncLevelDepth(LCD_Menu.bottomThreshold-LCD_Menu.topThreshold);
					}

					LCD_Interface.Position(2, 1);
					LCD_Interface.DataFlow.SendCharacter(S_BULLET);
					LCD_Interface.DataFlow.SendCharacter(S_BLANK);
					LCD_Interface.Position(2, 3);
					LCD_Interface.DataFlow.SendString("              ");
					LCD_Interface.Position(2, 3);

					functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.getSubFuncLevelDepth()];
					LCD_Interface.DataFlow.SendString(functionName);
					break;

				case OPT_PREV:

					if ((LCD_Menu.getSubFuncLevelDepth() > LCD_Menu.bottomThreshold) && (LCD_Menu.getSubFuncLevelDepth() <= LCD_Menu.topThreshold))
					{
						LCD_Menu.setSubFuncLevelDepth(-1);
					}
					else if (LCD_Menu.getSubFuncLevelDepth() == LCD_Menu.bottomThreshold)
					{
						LCD_Menu.setSubFuncLevelDepth(LCD_Menu.topThreshold);
					}

					LCD_Interface.Position(2, 1);
					LCD_Interface.DataFlow.SendCharacter(S_BULLET);
					LCD_Interface.DataFlow.SendCharacter(S_BLANK);
					LCD_Interface.Position(2, 3);
					LCD_Interface.DataFlow.SendString("              ");
					LCD_Interface.Position(2, 3);

					functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.getSubFuncLevelDepth()];
					LCD_Interface.DataFlow.SendString(functionName);
					break;

				case OPT_SELECT:
					//LCD_Menu.Options.CurrentFunction[LCD_Menu.fQueue][LCD_Menu.subfQueue]();
					break;

				case OPT_RETURN:
					break;

				default:
					break;
			}

			LCD_Interface.Position(1, 6);
			LCD_Interface.DataFlow.SendNumber(LCD_Menu.topThreshold);
			LCD_Interface.Position(1, 8);
			LCD_Interface.DataFlow.SendNumber(LCD_Menu.getFuncLevelDepth());
			LCD_Interface.Position(1, 10);
			LCD_Interface.DataFlow.SendNumber(LCD_Menu.getSubFuncLevelDepth());
			LCD_Interface.Position(1, 12);
			LCD_Interface.DataFlow.SendNumber(LCD_Menu.bottomThreshold);


	LCD_Menu.optionSelected = OPT_VOID;
}
