/*
 * lcd.h
 *
 *  Created on: 2013.09.24
 *      Author: Graþvidas
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

#define SET					1
#define RESET				0

#define CMD_DIR				DDRB
#define CMD_PORT			PORTB
#define LCD_E				PB0
#define LCD_RS				PB1
#define LCD_RW				PB2

#define DATA_DIR			DDRC
#define DATA_PORT			PORTC
#define DATA_PIN			PINC
#define LCD_DATA0			PC0
#define LCD_DATA1			PC1
#define LCD_DATA2			PC2
#define LCD_DATA3			PC3

#define LCD_LINE_LENGTH		20

enum {
	Z_pauksciukas = 0,
	S_pauksciukas,
	E_taskas,
	U_nosine,
	A_nosine,

	Raides_cnt
};

//____________________________________ CHARACTERS ________________________________________________/

#define S_CELSIUS			0xDF
#define S_BULLET			0xA5
#define S_BLANK				0x20
#define S_ARROW_RIGHT		0x7E
#define S_ARROW_LEFT		0x7F
#define S_FULL				0xFF

//____________________________________ FUNCTION PROTOTYPES ________________________________________/

void LCD_Init(void);
void LCD_Position(uint8_t pos_x, uint8_t pos_y);
void LCD_SendCommand(uint8_t size, uint8_t cmd);
void LCD_SendCharacter(uint8_t character);
void LCD_SendString(char* charString);
void LCD_SendNumber(int16_t number);

//_________________________________________________________________________________________________/

typedef struct {
	void (*Init)(void);
	void (*Position)(uint8_t pos_x, uint8_t pos_y);
	void (*SendCommand)(uint8_t size, uint8_t cmd);
	void (*SendCharacter)(uint8_t character);
	void (*SendString)(char* charString);
	void (*SendNumber)(int16_t number);

}LCD_Interface_t;

extern const LCD_Interface_t LCD;

#endif /* LCD_H_ */
