/*
 * lcd_meniu.h
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#ifndef LCD_MENIU_H_
#define LCD_MENIU_H_

#include <avr/io.h>

void LCD_Menu_Initialize(void);
void LCD_Menu_Enter(void);
void LCD_Menu_LED_color(void);
void LCD_Menu_Preferences(void);
void LCD_Menu_Channels(void);
void LCD_Menu_Profiles(void);
void LCD_Menu_Preset_colors(void);
void LCD_Menu_Custom_color(void);
/*
 * optLevel - has e.g. 3 sub levels, ground 0,..,3 surface
 */
void LCD_Menu_Option_Selection();
#define OPT_LEVEL_GROUND	0x00
#define OPT_LEVEL_SURFACE	0x02

#define OPT_SELECT			0x10
#define OPT_RETURN			0x20
#define OPT_NEXT			0x30
#define OPT_PREV			0x40
#define OPT_VOID			0x50

// minus 1, starting with index of 0
#define OPT_QUANTITY		4

typedef struct LED_t {
	void (*CurrentFunction[2])(void);
	void (*Preset_colors)(void);
	void (*Custom_color)(void);

	char* CurrentSubFunctionName[2];
	char* name;
}LED_t;

typedef struct Settings_t {
	void (*CurrentFunction[2])(void);

	char* CurrentSubFunctionName[2];
	char* name;

}Settings_t;

typedef struct Channels_t {
	void (*CurrentFunction[1])(void);

	char* CurrentSubFunctionName[1];
	char* name;

}Channels_t;

typedef struct Profiles_t {
	void (*CurrentFunction[1])(void);

	char* CurrentSubFunctionName[1];
	char* name;

}Profiles_t;

typedef struct Options_t {
	void (*LED_color)(void);
	void (*Preferences)(void);
	void (*Channels)(void);
	void (*Profiles)(void);
	void (*CurrentFunction[4][4])(void);

	char* CurrentFunctionName[4][4];

	LED_t LED;
	Settings_t Prefs;
	Channels_t Ch;
	Profiles_t Profs;

}Options_t;

typedef struct {
	void (*Initialize)(void);
	void (*Enter)(void);

	uint8_t optionSelected;
	uint8_t fQueue;
	uint8_t subfQueue;
	uint8_t bottomThreshold;
	uint8_t topThreshold;

	Options_t Options;
}LCD_Menu_t;

extern LCD_Menu_t LCD_Menu;

#endif /* LCD_MENIU_H_ */
