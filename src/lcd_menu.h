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

void LCD_Menu_Init(void);
uint8_t LCD_Menu_PresetColors(uint8_t random);
uint8_t LCD_Menu_CustomColor(uint8_t preview);
void LCD_Menu_SelectCh(uint8_t io);
void LCD_Menu_setOpt(uint8_t opt);
uint8_t LCD_Menu_getOpt(void);
void LCD_Menu_branch_LEDs(void);
void LCD_Menu_branch_Set(void);
void LCD_Menu_branch_Profs(void);

#define B_VOID		0x00
#define B_SELECT	0x10
#define B_RETURN	0x20
#define B_NEXT		0x30
#define B_PREV		0x40

#define MAX_1L		3

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
	uint8_t (*selectCh)(uint8_t ch, uint8_t io, uint8_t* ok);

}Channels_t;

Channels_t Ch;

typedef struct {
	uint8_t (*color_custom)(uint8_t io);
	uint8_t (*color_present)(uint8_t io);

	Channels_t* ch;
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
	void (*branch[MAX_1L])(void);

	char* funcNames[3];
	uint8_t optSelected;
	uint8_t pos;
}LCD_Menu_t;

extern LCD_Menu_t Menu;

#endif /* LCD_MENIU_H_ */
