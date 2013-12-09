/*
 * lcd_meniu.h
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#ifndef LCD_MENIU_H_
#define LCD_MENIU_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

void LCD_Menu_Initialize(void);
void LCD_Menu_Enter(void);
void LCD_Menu_LED_color(void);
void LCD_Menu_Preferences(void);
void LCD_Menu_Channels(void);
void LCD_Menu_Profiles(void);
void LCD_Menu_Preset_colors(uint8_t random);
void LCD_Menu_Custom_color(uint8_t preview);
void LCD_Menu_ChooseChannel(uint8_t io);
void LCD_setSubFuncLevelDepth(int8_t pos);
void LCD_setFuncLevelDepth(int8_t pos);
uint8_t LCD_getSubFuncLevelDepth(void);
uint8_t LCD_getFuncLevelDepth(void);
void LCD_Menu_Option_Selection(uint8_t subFuncQuantity);

#define OPT_LEVEL_GROUND	0x00
#define OPT_LEVEL_SURFACE	0x02

#define OPT_SELECT			0x10
#define OPT_RETURN			0x20
#define OPT_NEXT			0x30
#define OPT_PREV			0x40
#define OPT_VOID			0x50

// minus 1, starting with index of 0
#define OPT_QUANTITY		4

typedef struct MAP_t {
	uint8_t funcQuantity;
	char* level1objName[3];

}MAP_t;

typedef struct LED_t {
	void (*CurrentFunction[3])(uint8_t);

	void (*PresetColors)(uint8_t random);	// 8 different colors
	void (*CustomColor)(uint8_t preview); 	// setting-up RGB and brightness
	void (*ChooseChannel)(uint8_t io);	// select a channel

	// sub functions of main ones
	void (*ChannelDetails)(void);

	char* CurrentFunctionName[3];
	char* CurrentSubFunctionName[1];
	uint8_t funcQuantity;
	char* objName;
}LED_t;

typedef struct Settings_t {
	void (*CurrentFunction[2])(void);

	char* CurrentSubFunctionName[2];
	char* objName;

}Settings_t;

typedef struct Profiles_t {
	void (*CurrentFunction[1])(void);

	char* CurrentSubFunctionName[1];
	char* objName;

}Profiles_t;

typedef struct Options_t {
	void (*LED_color)(void);
	void (*Preferences)(void);
	void (*Profiles)(void);
	void (*CurrentFunction[3])(void);

	char* CurrentFunctionName[3];

	LED_t LED;
	Settings_t Prefs;
	Profiles_t Profs;

}Options_t;

typedef struct LCD_Menu_t{
	void (*Initialize)(void);
	void (*Enter)(void);
	void (*setSubFuncLevelDepth)(int8_t posDirection);
	void (*setFuncLevelDepth)(int8_t posDirection);
	uint8_t (*getSubFuncLevelDepth)(void);
	uint8_t (*getFuncLevelDepth)(void);

	uint8_t optionSelected;
	uint8_t funcPos;
	uint8_t subFuncPos;
	uint8_t selectedBranch;

	Options_t Options;
	MAP_t MAP[3];
}LCD_Menu_t;

extern LCD_Menu_t LCD_Menu;

#endif /* LCD_MENIU_H_ */
