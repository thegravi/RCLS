/*
 * lcd_meniu.c
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#include "lcd_menu.h"
#include "lcd.h"
#include <avr/io.h>

LCD_Menu_t LCD_Menu = {
						LCD_Menu_Initialize,
						LCD_Menu_Enter,
						OPT_VOID,
							// Options obj
						  {
								  {
									  LCD_Menu_LED_color,
									  LCD_Menu_Preferences,
									  LCD_Menu_Channels,
									  LCD_Menu_Profiles,
								  },
								  LCD_Menu_LED_color,
								  LCD_Menu_Preferences,
								  LCD_Menu_Channels,
								  LCD_Menu_Profiles,
								  {"","","",""},
								  	  	  // LED obj
									  {
											  "Etalon LED"
									  },
										  // Settings obj
									  {
											  "Preferences"
									  },
										  // Channels obj
									  {
											  "Channels"
									  },
										  // Profiles obj
									  {
											  "Profiles"
									  }
						  }
					  };

void LCD_Menu_Initialize() {

	LCD_Menu.Options.CurrentFunctionName[0] = LCD_Menu.Options.LED.name;
	LCD_Menu.Options.CurrentFunctionName[1] = LCD_Menu.Options.Prefs.name;
	LCD_Menu.Options.CurrentFunctionName[2] = LCD_Menu.Options.Ch.name;
	LCD_Menu.Options.CurrentFunctionName[3] = LCD_Menu.Options.Profs.name;
}

void LCD_Menu_Enter() {

	char* functionName = "";
	uint8_t functionQueue = 0;

//	LCD_Menu.Options.CurrentFunction[functionQueue]();

	LCD_Interface.Position(1, 1);
	LCD_Interface.DataFlow.SendString("----- Menu -----");
	LCD_Interface.Position(2, 1);
	LCD_Interface.DataFlow.SendCharacter(S_ARROW_RIGHT);
	LCD_Interface.DataFlow.SendCharacter(S_BLANK);

	functionName = LCD_Menu.Options.CurrentFunctionName[functionQueue];
	LCD_Interface.DataFlow.SendString(functionName);

	while(1) {

		while(LCD_Menu.functionSelected == OPT_VOID) { if (LCD_Menu.functionSelected != OPT_VOID) { break;} }

		LCD_Interface.Position(2, 1);
		LCD_Interface.DataFlow.SendString("                ");

		switch(LCD_Menu.functionSelected)
		{
			case OPT_NEXT:
				if (functionQueue >= 0 && functionQueue < OPT_QUANTITY-1) {
					functionQueue++;
				} else if (functionQueue == OPT_QUANTITY-1) {
					functionQueue = 0;
				}

				LCD_Interface.Position(2, 1);
				LCD_Interface.DataFlow.SendCharacter(S_ARROW_RIGHT);
				LCD_Interface.DataFlow.SendCharacter(S_BLANK);
				functionName = LCD_Menu.Options.CurrentFunctionName[functionQueue];
				LCD_Interface.DataFlow.SendString(functionName);
				LCD_Menu.functionSelected = OPT_VOID;
				break;

			case OPT_PREV:
				if (functionQueue > 0 && functionQueue < OPT_QUANTITY) {
					functionQueue--;
				} else if (functionQueue == 0) {
					functionQueue = OPT_QUANTITY-1;
				}

				LCD_Interface.Position(2, 1);
				LCD_Interface.DataFlow.SendCharacter(S_ARROW_RIGHT);
				LCD_Interface.DataFlow.SendCharacter(S_BLANK);
				functionName = LCD_Menu.Options.CurrentFunctionName[functionQueue];
				LCD_Interface.DataFlow.SendString(functionName);
				LCD_Menu.functionSelected = OPT_VOID;
				break;

			case OPT_SELECT:
				break;

			case OPT_RETURN:
				break;

				default:
					break;
		}

	}

}

void LCD_Menu_LED_color() {

}

void LCD_Menu_Preferences() {

}

void LCD_Menu_Channels() {

}

void LCD_Menu_Profiles() {

}
