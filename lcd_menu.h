/*
 * lcd_meniu.h
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#ifndef LCD_MENIU_H_
#define LCD_MENIU_H_

void LCD_Menu_enter(void);
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
	void (*Opt_LED_color)(void);
	void (*Opt_Preferences)(void);
	void (*Opt_Channels)(void);
	void (*Opt_Profiles)(void);

	LED_t LED;
	Settings_t Prefs;
	Channels_t Ch;
	Profiles_t Profiles;

}Options_t;

typedef struct {
	void (*Enter)(void);

	Options_t Options;
}LCD_Menu_t;

extern LCD_Menu_t LCD_Menu;

#endif /* LCD_MENIU_H_ */
