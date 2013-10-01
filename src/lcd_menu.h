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

#define OPT_SELECT			0x10
#define OPT_RETURN			0x20
#define OPT_NEXT			0x30
#define OPT_PREV			0x40
#define OPT_VOID			0x50
#define OPT_EXIT			0xF0

// minus 1, starting with index of 0
#define OPT_QUANTITY		4

typedef struct {
	char* name;

}LED_t;

typedef struct {
	char* name;

}Settings_t;

typedef struct {
	char* name;

}Channels_t;

typedef struct {
	char* name;

}Profiles_t;

typedef struct {
	void (*CurrentFunction[OPT_QUANTITY])(void);
	void (*LED_color)(void);
	void (*Preferences)(void);
	void (*Channels)(void);
	void (*Profiles)(void);

	char* CurrentFunctionName[OPT_QUANTITY];

	LED_t LED;
	Settings_t Prefs;
	Channels_t Ch;
	Profiles_t Profs;

}Options_t;

typedef struct {
	void (*Initialize)(void);
	void (*Enter)(void);

	uint8_t functionSelected;

	Options_t Options;
}LCD_Menu_t;

extern LCD_Menu_t LCD_Menu;

#endif /* LCD_MENIU_H_ */
