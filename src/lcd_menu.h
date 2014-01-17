/*
 * lcd_meniu.h
 *
 *  Created on: 2013.09.29
 *      Author: Graþvidas
 */

#ifndef LCD_MENIU_H_
#define LCD_MENIU_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "lcd.h"
#include "common.h"

void LCD_Menu_Init(void);
uint8_t LCD_Menu_PresetColors(uint8_t io, uint8_t* data);
uint8_t LCD_Menu_CustomColor(uint8_t io, uint8_t* data);
uint8_t LCD_Menu_SelectCh(uint8_t* ok);
void LCD_Menu_setOpt(uint8_t opt);
uint8_t LCD_Menu_getOpt(void);
void LCD_Menu_branch_LEDs(void);
void LCD_Menu_branch_Set(void);
void LCD_Menu_branch_Profs(void);
uint8_t LCD_Menu_ChGetData(uint8_t* data, uint8_t* ok);
uint8_t LCD_Menu_ChSetData(uint8_t* data, uint8_t* ok);
void LCD_Menu_Colors(void);
void LCD_Menu_Channels(void);
int8_t LCD_Menu_Choice(uint8_t lim, char** names);

#define B_VOID		0x00
#define B_SELECT	0x10
#define B_RETURN	0x20
#define B_NEXT		0x40
#define B_PREV		0x80

typedef enum {
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


typedef struct {
	uint8_t (*getData)(uint8_t* data, uint8_t* ok);
	uint8_t (*setData)(uint8_t* data, uint8_t* ok);
	uint8_t (*selectCh)(uint8_t* ok);
	uint8_t (*branch[2])(uint8_t* data, uint8_t* ok);

	char* funcNames[2];
	char* chList[16];

}Channels_t;

Channels_t Ch;


typedef struct {
	uint8_t (*color_custom)(uint8_t io, uint8_t* data);
	uint8_t (*color_present)(uint8_t io, uint8_t* data);
	uint8_t (*branch[2])(uint8_t io, uint8_t* data);

	char* funcNames[2];
	char* colorNames[NUM_OF_COLORS];

}Colors_t;

Colors_t Colors;


typedef struct {
	Colors_t* colors;
	Channels_t* ch;

	void (*branch[2])(void);

	char* funcNames[2];

}LEDs_t;

LEDs_t LEDs;


typedef struct {

}Settings_t;

Settings_t Set;


typedef struct {

}Profiles_t;

Profiles_t Prof;


typedef struct {
	LEDs_t* leds;
	Settings_t* set;
	Profiles_t* prof;

	void (*Init)(void);
	void (*setOpt)(uint8_t opt);
	uint8_t (*getOpt)(void);
	int8_t (*choice)(uint8_t lim, char** names);
	void (*branch[3])(void);

	char* funcNames[3];
	uint8_t optSelected;
	uint8_t pos;

}LCD_Menu_t;

extern LCD_Menu_t Menu;

#endif /* LCD_MENIU_H_ */
