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
void LCD_Menu_Preferences(void);
void LCD_Menu_Channels(void);
void LCD_Menu_Profiles(void);
void LCD_Menu_PresetColors(uint8_t random);
void LCD_Menu_CustomColor(uint8_t preview);
void LCD_Menu_SelectCh(uint8_t io);
void LCD_setSubFuncLevelDepth(int8_t pos);
void LCD_setFuncLevelDepth(int8_t pos);
uint8_t LCD_getSubFuncLevelDepth(void);
uint8_t LCD_getFuncLevelDepth(void);
void LCD_Menu_OptionSelection(void);
void LCD_Menu_BottomLineDeclaration(void);

#define B_VOID		0x00
#define B_SELECT	0x10
#define B_RETURN	0x20
#define B_NEXT		0x30
#define B_PREV		0x40

typedef enum ColorTable_t {
	RED=0,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	INDIGO,
	VIOLET,
	WHITE,

	NUM_OF_COLORS
}ColorTable_t;

extern ColorTable_t ColorTable;

typedef struct MAP_t {
	void (*level1objFunc[3])(uint8_t);
	uint8_t funcQuantity;
	char* level1objName[3];

}MAP_t;

typedef struct Channels_t {
	uint8_t (*getData)(uint8_t* data, uint8_t* ok);
	uint8_t (*setData)(uint8_t* data, uint8_t* ok);
	uint8_t (*selectCh)(uint8_t ch, uint8_t io, uint8_t* ok);

}Channels_t;

typedef struct LEDs_t {
	uint8_t (*color_custom)(uint8_t io);
	uint8_t (*color_present)(uint8_t io);

	Channels_t* ch;
}LEDs_t;

extern LEDs_t LEDs;

typedef struct Settings_t {

}Settings_t;

extern Settings_t Set;

typedef struct Profiles_t {

}Profiles_t;

extern Profiles_t Prof;

typedef struct Options_t {
	void (*LED_color)(void);
	void (*Preferences)(void);
	void (*Profiles)(void);
	void (*CurrentFunction[3])(void);

	char* CurrentFunctionName[3];

//	LED_t LED;
//	Settings_t Prefs;
//	Profiles_t Profs;

}Options_t;

typedef struct LCD_Menu_t{
	void (*Initialize)(void);
	LEDs_t* leds;
	Settings_t* set;
	Profiles_t* prof;

	void (*Enter)(void);
	void (*setSubFuncLevelDepth)(int8_t posDirection);
	void (*setFuncLevelDepth)(int8_t posDirection);
	uint8_t (*getSubFuncLevelDepth)(void);
	uint8_t (*getFuncLevelDepth)(void);

	uint8_t optSelected;
	uint8_t funcPos;
	uint8_t subFuncPos;
	uint8_t selectedBranch;


	Options_t Options;
	MAP_t MAP[3];
}LCD_Menu_t;

extern LCD_Menu_t Menu;

#endif /* LCD_MENIU_H_ */
