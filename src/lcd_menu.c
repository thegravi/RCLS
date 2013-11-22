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

	//uint8_t index_Level;
	//uint8_t index_Queue;

	// LED Object
	LCD_Menu.Options.LED.CurrentFunction[0] 		= LCD_Menu_Preset_colors;
	LCD_Menu.Options.LED.CurrentFunction[1] 		= LCD_Menu_Custom_color;
	LCD_Menu.Options.LED.Preset_colors 				= LCD_Menu_Preset_colors;
	LCD_Menu.Options.LED.Custom_color 				= LCD_Menu_Custom_color;
	LCD_Menu.Options.LED.CurrentSubFunctionName[0] 	= "Preset colors";
	LCD_Menu.Options.LED.CurrentSubFunctionName[1] 	= "Custom color";
	LCD_Menu.Options.LED.name = "LED";

	// Settings Object
	LCD_Menu.Options.Prefs.name = "Preferences";

	// Profiles Object
	LCD_Menu.Options.Profs.name = "Profiles";

	// Channels Object
	LCD_Menu.Options.Ch.name = "Channels";

	// Menu Object
	LCD_Menu.Initialize 		= LCD_Menu_Initialize;
	LCD_Menu.Enter 				= LCD_Menu_Enter;
	LCD_Menu.optionSelected 	= OPT_VOID;
	LCD_Menu.subfQueue 			= 0;
	LCD_Menu.fQueue 			= 0;
	LCD_Menu.bottomThreshold 	= 0;
	LCD_Menu.topThreshold		= 3;

	// Options Object
	LCD_Menu.Options.LED_color 		= LCD_Menu_LED_color;
	LCD_Menu.Options.Preferences 	= LCD_Menu_Preferences;
	LCD_Menu.Options.Channels 		= LCD_Menu_Channels;
	LCD_Menu.Options.Profiles 		= LCD_Menu_Profiles;

	LCD_Menu.Options.CurrentFunctionName[0][0] = LCD_Menu.Options.LED.name;
	LCD_Menu.Options.CurrentFunctionName[0][1] = LCD_Menu.Options.Prefs.name;
	LCD_Menu.Options.CurrentFunctionName[0][2] = LCD_Menu.Options.Ch.name;
	LCD_Menu.Options.CurrentFunctionName[0][3] = LCD_Menu.Options.Profs.name;
	LCD_Menu.Options.CurrentFunctionName[1][0] = LCD_Menu.Options.LED.CurrentSubFunctionName[0];
	LCD_Menu.Options.CurrentFunctionName[1][1] = LCD_Menu.Options.LED.CurrentSubFunctionName[1];
	LCD_Menu.Options.CurrentFunctionName[1][2] = "";
	LCD_Menu.Options.CurrentFunctionName[1][3] = "";
	LCD_Menu.Options.CurrentFunctionName[2][0] = "";
	LCD_Menu.Options.CurrentFunctionName[2][1] = "";
	LCD_Menu.Options.CurrentFunctionName[2][2] = "";
	LCD_Menu.Options.CurrentFunctionName[2][3] = "";
	LCD_Menu.Options.CurrentFunctionName[3][0] = "";
	LCD_Menu.Options.CurrentFunctionName[3][1] = "";
	LCD_Menu.Options.CurrentFunctionName[3][2] = "";
	LCD_Menu.Options.CurrentFunctionName[3][3] = "";


	LCD_Menu.Options.CurrentFunction[0][0] = LCD_Menu.Options.LED_color;
	LCD_Menu.Options.CurrentFunction[0][1] = LCD_Menu.Options.Preferences;
	LCD_Menu.Options.CurrentFunction[0][2] = LCD_Menu.Options.Channels;
	LCD_Menu.Options.CurrentFunction[0][3] = LCD_Menu.Options.Profiles;
	LCD_Menu.Options.CurrentFunction[1][0] = LCD_Menu.Options.LED.Preset_colors;
	LCD_Menu.Options.CurrentFunction[1][1] = LCD_Menu.Options.LED.Custom_color;
/*	LCD_Menu.Options.CurrentFunction[1][2] =
	LCD_Menu.Options.CurrentFunction[1][3] =
	LCD_Menu.Options.CurrentFunction[2][0] =
	LCD_Menu.Options.CurrentFunction[2][1] =
	LCD_Menu.Options.CurrentFunction[2][2] =
	LCD_Menu.Options.CurrentFunction[2][3] =
	LCD_Menu.Options.CurrentFunction[3][0] =
	LCD_Menu.Options.CurrentFunction[3][1] =
	LCD_Menu.Options.CurrentFunction[3][2] =
	LCD_Menu.Options.CurrentFunction[3][3] =
*/

	/*for (index_Level = 0; index_Level < getfLevelDepth(); index_Level++) {
			for (index_Queue = 1; index_Queue < getfQueueDepth(); index_Queue++) {
				LCD_Menu.Options.CurrentFunctionName[index_Level][index_Queue];
			}
	}*/


}

void LCD_Menu_Enter() {

	char* functionName;
	DDRC |= 1<<PC5;
	LCD_Interface.DataFlow.SendCommand(8, 0x01);
	LCD_Interface.Position(1, 1);
	LCD_Interface.DataFlow.SendString("Menu");
	LCD_Interface.Position(2, 1);
	LCD_Interface.DataFlow.SendCharacter(S_ARROW_RIGHT);
	LCD_Interface.DataFlow.SendCharacter(S_BLANK);
	LCD_Interface.Position(2, 3);
	functionName = LCD_Menu.Options.CurrentFunctionName[0][0];
	LCD_Interface.DataFlow.SendString(functionName);

	while(1) {

		LCD_Menu_Option_Selection();

			while(1) {
				__asm__ __volatile__ ("nop" ::);
				if (LCD_Menu.optionSelected != OPT_VOID) { break;}
			}

	}

}

void LCD_Menu_LED_color() {

	LCD_Menu.bottomThreshold 	= 0;
	LCD_Menu.topThreshold		= 2;
	LCD_Menu.fQueue 			= 1;
}

void LCD_Menu_Preset_colors() {

}

void LCD_Menu_Custom_color() {

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
	//uint8_t fLevelPrev;

	/*	if ( (LCD_Menu.subfQueue - 1) < OPT_LEVEL_GROUND )
			fLevelPrev = OPT_LEVEL_SURFACE;
		else
			fLevelPrev = LCD_Menu.subfQueue - 1;

		if (LCD_Menu.subfQueue != OPT_LEVEL_GROUND) {
			LCD_Interface.Position(1, 1);
			functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.fQueue][fLevelPrev];
			LCD_Interface.DataFlow.SendString(functionName);
		}*/

			switch(LCD_Menu.optionSelected)
			{
				case OPT_NEXT:
					if ((LCD_Menu.subfQueue >= LCD_Menu.bottomThreshold) && (LCD_Menu.fQueue < LCD_Menu.topThreshold)) {
						LCD_Menu.subfQueue = LCD_Menu.subfQueue + 1;
					} else if (LCD_Menu.subfQueue == LCD_Menu.topThreshold) {
						LCD_Menu.subfQueue = LCD_Menu.bottomThreshold;
					}

					LCD_Interface.Position(2, 1);
					LCD_Interface.DataFlow.SendCharacter(S_ARROW_RIGHT);
					LCD_Interface.DataFlow.SendCharacter(S_BLANK);
					LCD_Interface.Position(2, 3);
					LCD_Interface.DataFlow.SendString("              ");
					LCD_Interface.Position(2, 3);

					functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.fQueue][LCD_Menu.subfQueue];
					LCD_Interface.DataFlow.SendString(functionName);
					break;

				case OPT_PREV:
					if ((LCD_Menu.subfQueue > LCD_Menu.bottomThreshold) && (LCD_Menu.subfQueue <= LCD_Menu.topThreshold)) {
						LCD_Menu.subfQueue--;
					} else if (LCD_Menu.subfQueue == LCD_Menu.bottomThreshold) {
						LCD_Menu.subfQueue = LCD_Menu.topThreshold;
					}

					LCD_Interface.Position(2, 1);
					LCD_Interface.DataFlow.SendCharacter(S_ARROW_RIGHT);
					LCD_Interface.DataFlow.SendCharacter(S_BLANK);
					LCD_Interface.Position(2, 3);
					LCD_Interface.DataFlow.SendString("              ");
					LCD_Interface.Position(2, 3);

					functionName = LCD_Menu.Options.CurrentFunctionName[LCD_Menu.fQueue][LCD_Menu.subfQueue];
					LCD_Interface.DataFlow.SendString(functionName);
					break;

				case OPT_SELECT:
					LCD_Menu.Options.CurrentFunction[LCD_Menu.fQueue][LCD_Menu.subfQueue]();
					break;

				case OPT_RETURN:
					break;

				default:
					break;
			}

	LCD_Menu.optionSelected = OPT_VOID;

}

uint8_t getfLevelDepth() { return OPT_LEVEL_SURFACE; }
uint8_t getfQuaueDepth(uint8_t func) { return 3; }
