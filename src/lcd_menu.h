/*
 * lcd_meniu.h
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#ifndef LCD_MENIU_H_
#define LCD_MENIU_H_

#define OPTIONS_QUANTITY		4

void LCD_Menu_Initialize(void);
void LCD_Menu_Enter(void);
void LCD_Menu_LED_color(void);
void LCD_Menu_Preferences(void);
void LCD_Menu_Channels(void);
void LCD_Menu_Profiles(void);

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
	void (*CurrentFunction[OPTIONS_QUANTITY])(void);
	void (*LED_color)(void);
	void (*Preferences)(void);
	void (*Channels)(void);
	void (*Profiles)(void);

	char* CurrentFunctionName[OPTIONS_QUANTITY];

	LED_t LED;
	Settings_t Prefs;
	Channels_t Ch;
	Profiles_t Profs;

}Options_t;

typedef struct {
	void (*Initialize)(void);
	void (*Enter)(void);

	Options_t Options;
}LCD_Menu_t;

extern LCD_Menu_t LCD_Menu;

#endif /* LCD_MENIU_H_ */
