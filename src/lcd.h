/*
 * lcd.h
 *
 *  Created on: 2013.09.24
 *      Author: Graþvidas
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#ifndef LCD_H_
#define LCD_H_

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
#define LCD_SIZE			128
#define LCD_ROW_LENGTH		16
//____________________________________ CHARACTERS ________________________________________________/

#define S_CELSIUS			0xDF
#define S_BULLET			0xA5
#define S_BLANK				0x20
#define S_ARROW_RIGHT		0x7E
#define S_ARROW_LEFT		0x7F
#define S_FULL				0xFF

//____________________________________ FUNCTION PROTOTYPES ________________________________________/

void LCD_Initialize(void);
void LCD_Position(uint8_t pos_x, uint8_t pos_y);
void LCD_SendCommand(uint8_t size, uint8_t cmd);
void LCD_SendCharacter(uint8_t character);
void LCD_SendString(char* charString);
void LCD_SendNumber(uint16_t number);
void LCD_ProcessData(int8_t data);
void LCD_ExecuteCMD(void);
void LCD_WaitIfBusy(void);
void LCD_WaitIfBusy(void);
void LCD_DDR_E_set(void);
void LCD_DDR_RS_set(void);
void LCD_DDR_RW_set(void);
void LCD_DDR_E_clear(void);
void LCD_DDR_RS_clear(void);
void LCD_DDR_RW_clear(void);
void LCD_PORT_E_set(void);
void LCD_PORT_RS_set(void);
void LCD_PORT_RW_set(void);
void LCD_PORT_E_clear(void);
void LCD_PORT_RS_clear(void);
void LCD_PORT_RW_clear(void);
//_____________________________________________________________________________________________________/

typedef struct {
	void (*DDR_E_set)(void);
	void (*DDR_RS_set)(void);
	void (*DDR_RW_set)(void);
	void (*DDR_E_clear)(void);
	void (*DDR_RS_clear)(void);
	void (*DDR_RW_clear)(void);

	void (*PORT_E_set)(void);
	void (*PORT_RS_set)(void);
	void (*PORT_RW_set)(void);
	void (*PORT_E_clear)(void);
	void (*PORT_RS_clear)(void);
	void (*PORT_RW_clear)(void);

}Regs_t;

typedef struct {
	void (*SendCommand)(uint8_t size, uint8_t cmd);
	void (*SendCharacter)(uint8_t character);
	void (*SendString)(char* charString);
	void (*SendNumber)(uint16_t number);
	void (*ProcessData)(int8_t data);

}DataFlow_t;

typedef struct {
	void (*ExecuteCMD)(void);
	void (*WaitIfBusy)(void);

}Communication_t;

typedef struct {
	void (*Initialize)(void);
	void (*Position)(uint8_t pos_x, uint8_t pos_y);

	Regs_t Regs;
	DataFlow_t DataFlow;
	Communication_t Com;

}LCD_Interface_t;

extern LCD_Interface_t LCD_Interface;

#endif /* LCD_H_ */
