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
void LCD_Menu_Settings(void);
void LCD_Menu_Channels(void);
void LCD_Menu_Profiles(void);

typedef struct {
	void (*LED_color)(void);
	void (*Settings)(void);
	void (*Channels)(void);
	void (*Profiles)(void);
}Options_t;

typedef struct {
	void (*Enter)(void);

	Options_t Options;
}LCD_Menu_t;

extern LCD_Menu_t LCD_Menu;

#endif /* LCD_MENIU_H_ */
