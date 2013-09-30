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

/*	uint8_t option = 0;

	switch(option)
	{


	default:
		break;

	}*/

}

void LCD_Menu_LED_color() {

}

void LCD_Menu_Preferences() {

}

void LCD_Menu_Channels() {

}

void LCD_Menu_Profiles() {

}
