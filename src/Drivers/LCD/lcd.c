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
static void LCD_DDR_RW(uint8_t sc)
{
	if (sc)
		CMD_DIR |= (1<<LCD_RW);
	else
		CMD_DIR &= ~(1<<LCD_RW);
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

static void LCD_PORT_RW(uint8_t sc)
{
	if (sc)
		CMD_PORT |= (1<<LCD_RW);
	else
		CMD_PORT &= ~(1<<LCD_RW);
}

static void LCD_ExecuteCMD()
{
	LCD_PORT_E(SET);

	asm("nop");
	asm("nop");
	LCD_PORT_E(RESET);
}

/*static void LCD_WaitIfBusy()
{
	volatile uint8_t data;
	uint8_t busy_f = SET;

	LCD.Regs->PORT_RW(SET);
	DATA_DIR &= ~(1<<LCD_DATA0) | ~(1<<LCD_DATA1) | ~(1<<LCD_DATA2) | ~(1<<LCD_DATA3);

	while (busy_f)
	{
		LCD.Regs->PORT_E(SET);
		_delay_us(1);
		data = DATA_PIN  << 4;
		LCD.Regs->PORT_E(RESET);
		_delay_us(1);
		LCD.Regs->PORT_E(SET);
		_delay_us(1);
		data |= (DATA_PIN & 0x0F);
		LCD.Regs->PORT_E(RESET);
		_delay_us(1);

		if (!(data & 0x80))
				busy_f = RESET;
	}
	DATA_DIR |= (1<<LCD_DATA0) | (1<<LCD_DATA1) | (1<<LCD_DATA2) | (1<<LCD_DATA3);
	LCD.Regs->PORT_RW(RESET);
}*/

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
	// temporary delay, until "WaitIfBusy" function is completed
		_delay_ms(5);
	//	LCD_Interface.Comm.WaitIfBusy();
		LCD_ProcessData(cmd >> 4);
		LCD_ExecuteCMD();
		LCD_ProcessData(cmd & 0x0F);
		LCD_ExecuteCMD();
	}
}

void LCD_SendCharacter(uint8_t character)
{
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

void LCD_Init()
{
	DATA_DIR |= (1<<LCD_DATA0) | (1<<LCD_DATA1) | (1<<LCD_DATA2) | (1<<LCD_DATA3);

	LCD_DDR_E(SET);
	LCD_DDR_RS(SET);
	LCD_DDR_RW(SET);
	LCD_PORT_E(RESET);
	LCD_PORT_RS(RESET);
	LCD_PORT_RW(RESET);

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
	// clear display, return position
	LCD_SendCommand(8, 0x01);
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

LCD_Interface_t LCD = {
		LCD_Init,
		LCD_Position,
		&Regs,
		&DataFlow
};

DataFlow_t DataFlow = {
		LCD_SendCommand,
		LCD_SendCharacter,
		LCD_SendString,
		LCD_SendNumber
};

Regs_t Regs = {
		LCD_DDR_E,
		LCD_DDR_RS,
		LCD_DDR_RW,
		LCD_PORT_E,
		LCD_PORT_RS,
		LCD_PORT_RW,
};
