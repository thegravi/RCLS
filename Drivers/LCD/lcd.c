/*
 * lcd.c
 *
 *  Created on: 2013.09.24
 *      Author: Graþvidas
 */

#include "lcd.h"

static void LCD_DDR_E(uint8_t sc)
{
	if (sc)
		CMD_DIR |= (1<<LCD_E);
	else
		CMD_DIR &= ~(1<<LCD_E);
}

static void LCD_DDR_RS(uint8_t sc)
{
	if (sc)
		CMD_DIR |= (1<<LCD_RS);
	else
		CMD_DIR &= ~(1<<LCD_RS);
}

static void LCD_PORT_E(uint8_t sc)
{
	if (sc)
		CMD_PORT |= (1<<LCD_E);
	else
		CMD_PORT &= ~(1<<LCD_E);
}

static void LCD_PORT_RS(uint8_t sc)
{
	if (sc)
		CMD_PORT |= (1<<LCD_RS);
	else
		CMD_PORT &= ~(1<<LCD_RS);
}

static void LCD_ExecuteCMD()
{
	LCD_PORT_E(SET);
	asm("nop");
	asm("nop");
	LCD_PORT_E(RESET);
}

static void LCD_ProcessData(int8_t data)
{
	if (data & 0x01)
		DATA_PORT |=  (1<<LCD_DATA0);
	else
		DATA_PORT &= ~(1<<LCD_DATA0);

	if (data & 0x02)
		DATA_PORT |=  (1<<LCD_DATA1);
	else
		DATA_PORT &= ~(1<<LCD_DATA1);

	if (data & 0x04)
		DATA_PORT |=  (1<<LCD_DATA2);
	else
		DATA_PORT &= ~(1<<LCD_DATA2);

	if (data & 0x08)
		DATA_PORT |=  (1<<LCD_DATA3);
	else
		DATA_PORT &= ~(1<<LCD_DATA3);
}

void LCD_SendCommand(uint8_t size, uint8_t cmd)
{
	if (size == 4) {
		LCD_ProcessData(cmd & 0x0F);
		LCD_ExecuteCMD();
	}
	else if (size == 8)	{
		_delay_ms(2);
		LCD_ProcessData(cmd >> 4);
		LCD_ExecuteCMD();
		LCD_ProcessData(cmd & 0x0F);
		LCD_ExecuteCMD();
	}
}

void LCD_SendCharacter(uint8_t character)
{
	static uint8_t f_customLetter = 0;

	if (character == '_') {
		f_customLetter = 1;
		return;
	}

	if (f_customLetter)
	{
		switch (character)
		{
			case 'z':
				character = Z_pauksciukas;
				break;
			case 's':
				character = S_pauksciukas;
				break;

			case 'e':
				character = E_taskas;
				break;

			case 'u':
				character = U_nosine;
				break;

			default:
				break;
		}
		f_customLetter = 0;
	}

	_delay_us(40);
	LCD_PORT_RS(SET);
	LCD_SendCommand(8, character);
	LCD_PORT_RS(RESET);
}

void LCD_SendNumber(int16_t number)
{
	char convNum[8];

	ltoa(number, convNum, 10);
	LCD_SendString(convNum);
}

void LCD_SendString(char* charString)
{
	while(*charString > 0)
		LCD_SendCharacter(*charString++);
}

static void LCD_BuildCustomCharacters()
{
	// add progmem support
	uint8_t letters[Raides_cnt][8] = {
										{0x0A, 0x04, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00},
										{0x0A, 0x04, 0x0F, 0x10, 0x0E, 0x01, 0x1E, 0x00},
										{0x04, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00},
										{0x00, 0x00, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x03}
									};
	uint8_t idx_letter, idx_pos;

	for (idx_letter = 0; idx_letter < Raides_cnt; idx_letter++)
	{
		LCD.SendCommand(8, 0x40 + (idx_letter<<3));
		for (idx_pos = 0; idx_pos < 8; idx_pos++)
			LCD.SendCharacter(letters[idx_letter][idx_pos]);

	}

}

void LCD_Init()
{
	DATA_DIR |= (1<<LCD_DATA0) | (1<<LCD_DATA1) | (1<<LCD_DATA2) | (1<<LCD_DATA3);

	LCD_DDR_E(SET);
	LCD_DDR_RS(SET);
	LCD_PORT_E(RESET);
	LCD_PORT_RS(RESET);

	_delay_ms(20);
	LCD_SendCommand(4, 0x03);	_delay_ms(5);
	LCD_SendCommand(4, 0x03);	_delay_ms(2);
	LCD_SendCommand(4, 0x03);	_delay_ms(2);
	LCD_SendCommand(4, 0x02);	_delay_ms(5);
	// 4-bit mode, 2 lines
	LCD_SendCommand(4, 0x02); _delay_ms(2);
	LCD_SendCommand(4, 0x08); _delay_ms(2);
	// display on
	LCD_SendCommand(8, 0x0C);
	// 5x7, 2 lines
	LCD_SendCommand(8, 0x28);
	// clear display, return position
	LCD_SendCommand(8, 0x01);

	LCD_BuildCustomCharacters();
}

void LCD_Position(uint8_t pos_y, uint8_t pos_x) {

	uint8_t pos;
	uint8_t LCD_Rows[4] = {0x80+0, 0x80+0x40, 0x80+0x14, 0x80+0x54};

	if ((!pos_y || pos_y > 4) || (!pos_x || pos_x > LCD_LINE_LENGTH)) {
			pos_y = 1;
			pos_x = 1;
	}

	pos = LCD_Rows[pos_y-1] + (pos_x - 1);
	LCD_SendCommand(8, pos);
}

const LCD_Interface_t LCD = {
		LCD_Init,
		LCD_Position,
		LCD_SendCommand,
		LCD_SendCharacter,
		LCD_SendString,
		LCD_SendNumber
};
