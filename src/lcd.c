/*
 * lcd.c
 *
 *  Created on: 2013.09.24
 *      Author: Graþvidas
 */

#include "lcd.h"
#include <avr/io.h>

void LCD_SendCommand(uint8_t size, uint8_t cmd) {

	if (size == 4) {
		LCD_Interface.DataFlow.ProcessData(cmd & 0x0F);
		LCD_Interface.Com.ExecuteCMD();
	} else if (size == 8) {
		// temporary delay, until "WaitIfBusy" function is completed
		_delay_ms(2);
	//	LCD_Interface.Comm.WaitIfBusy();
		LCD_Interface.DataFlow.ProcessData(cmd >> 4);
		LCD_Interface.Com.ExecuteCMD();
		LCD_Interface.DataFlow.ProcessData(cmd & 0x0F);
		LCD_Interface.Com.ExecuteCMD();
	}
}

static void LCD_ExecuteCMD() {

	LCD_Interface.Regs.PORT_E_set();
	asm volatile("nop");
	asm volatile("nop");
	LCD_Interface.Regs.PORT_E_clear();
}

static void LCD_WaitIfBusy() {

	volatile uint8_t data;
	uint8_t busy_f = 1;

	LCD_Interface.Regs.PORT_RW_set();
	DATA_DIR &= ~(1<<LCD_DATA0) | ~(1<<LCD_DATA1) | ~(1<<LCD_DATA2) | ~(1<<LCD_DATA3);

	while (busy_f) {

		LCD_Interface.Regs.PORT_E_set();
		_delay_us(1);
		data = DATA_PIN  << 4;
		LCD_Interface.Regs.PORT_E_clear();
		_delay_us(1);
		LCD_Interface.Regs.PORT_E_set();
		_delay_us(1);
		data |= (DATA_PIN & 0x0F);
		LCD_Interface.Regs.PORT_E_clear();
		_delay_us(1);

		if (data & 0x80) { } else { busy_f = 0; }
	}
	DATA_DIR |= (1<<LCD_DATA0) | (1<<LCD_DATA1) | (1<<LCD_DATA2) | (1<<LCD_DATA3);
	LCD_Interface.Regs.PORT_RW_clear();
}

void LCD_SendCharacter(uint8_t character) {

	_delay_us(50);
	//LCD_Interface.Comm.WaitIfBusy();
	LCD_Interface.Regs.PORT_RS_set();
	LCD_Interface.DataFlow.SendCommand(8, character);
	LCD_Interface.Regs.PORT_RS_clear();
}

void LCD_SendNumber(uint16_t number) {

	char* convNumber = NULL;

	itoa(number, convNumber, 10);

	LCD_Interface.DataFlow.SendString(convNumber);

}

void LCD_SendString(char* charString) {

	while(*charString != '\0') {
		LCD_Interface.DataFlow.SendCharacter(*charString++);
	}
}

static void LCD_ProcessData(int8_t data) {

	if (data & 0x01) {
		DATA_PORT |=  (1<<LCD_DATA0);
	} else { DATA_PORT &= ~(1<<LCD_DATA0); }

	if (data & 0x02) {
		DATA_PORT |=  (1<<LCD_DATA1);
	} else { DATA_PORT &= ~(1<<LCD_DATA1); }

	if (data & 0x04) {
		DATA_PORT |=  (1<<LCD_DATA2);
	} else { DATA_PORT &= ~(1<<LCD_DATA2); }

	if (data & 0x08) {
		DATA_PORT |=  (1<<LCD_DATA3);
	} else { DATA_PORT &= ~(1<<LCD_DATA3); }
}

void LCD_Initialize() {

	DATA_DIR |= (1<<LCD_DATA0) | (1<<LCD_DATA1) | (1<<LCD_DATA2) | (1<<LCD_DATA3);
	LCD_Interface.Regs.DDR_E_set();
	LCD_Interface.Regs.DDR_RS_set();
	LCD_Interface.Regs.DDR_RW_set();
	LCD_Interface.Regs.PORT_E_clear();
	LCD_Interface.Regs.PORT_RS_clear();
	LCD_Interface.Regs.PORT_RW_clear();

	_delay_ms(20);
	LCD_Interface.DataFlow.SendCommand(4, 0x03);	_delay_ms(5);
	LCD_Interface.DataFlow.SendCommand(4, 0x03);	_delay_ms(2);
	LCD_Interface.DataFlow.SendCommand(4, 0x03);	_delay_ms(2);
	LCD_Interface.DataFlow.SendCommand(4, 0x02);	_delay_ms(2);
	// 4-bit mode, 2 lines
	LCD_Interface.DataFlow.SendCommand(4, 0x2); 	_delay_ms(2);
	LCD_Interface.DataFlow.SendCommand(4, 0x8); 	_delay_ms(2);

	// display on
	LCD_Interface.DataFlow.SendCommand(8, 0x0C);
	//LCD_Interface.Comm.WaitIfBusy();

	// clear display, return position
	LCD_Interface.DataFlow.SendCommand(8, 0x01);
	//LCD_Interface.Comm.WaitIfBusy();
	LCD_Interface.DataFlow.SendString("Initialization");_delay_ms(500);
	//LCD_Interface.Comm.WaitIfBusy();
	LCD_Interface.Position(2, 1);
	//LCD_Interface.Comm.WaitIfBusy();
	LCD_Interface.DataFlow.SendString("COMPLETED");	_delay_ms(1000);
	LCD_Interface.DataFlow.SendCommand(8, 0x01);
	LCD_Interface.Position(1, 1);
}

void LCD_Position(uint8_t pos_y, uint8_t pos_x) {

	uint8_t pos;
	uint8_t LCD_Rows[4] = {0, 64, LCD_ROW_LENGTH, LCD_ROW_LENGTH+64};

	pos = LCD_SIZE + LCD_Rows[pos_y - 1] + (pos_x - 1);
	LCD_Interface.DataFlow.SendCommand(8, pos);
}

static void LCD_DDR_E_set() 		{ CMD_DIR |= (1<<LCD_E); }
static void LCD_DDR_RS_set() 		{ CMD_DIR |= (1<<LCD_RS); }
static void LCD_DDR_RW_set() 		{ CMD_DIR |= (1<<LCD_RW); }
static void LCD_DDR_E_clear() 		{ CMD_DIR &= ~(1<<LCD_E); }
static void LCD_DDR_RS_clear() 	{ CMD_DIR &= ~(1<<LCD_RS); }
static void LCD_DDR_RW_clear()		{ CMD_DIR &= ~(1<<LCD_RW); }
static void LCD_PORT_E_set() 		{ CMD_PORT |= (1<<LCD_E); }
static void LCD_PORT_RS_set() 		{ CMD_PORT |= (1<<LCD_RS); }
static void LCD_PORT_RW_set()		{ CMD_PORT |= (1<<LCD_RW); }
static void LCD_PORT_E_clear() 	{ CMD_PORT &= ~(1<<LCD_E); }
static void LCD_PORT_RS_clear() 	{ CMD_PORT &= ~(1<<LCD_RS); }
static void LCD_PORT_RW_clear() 	{ CMD_PORT &= ~(1<<LCD_RW); }

LCD_Interface_t LCD_Interface = {LCD_Initialize,
								 LCD_Position,
								{LCD_DDR_E_set,
								 LCD_DDR_RS_set,
								 LCD_DDR_RW_set,
								 LCD_DDR_E_clear,
								 LCD_DDR_RS_clear,
								 LCD_DDR_RW_clear,
								 LCD_PORT_E_set,
								 LCD_PORT_RS_set,
								 LCD_PORT_RW_set,
								 LCD_PORT_E_clear,
								 LCD_PORT_RS_clear,
								 LCD_PORT_RW_clear},
								{LCD_SendCommand, LCD_SendCharacter, LCD_SendString, LCD_SendNumber, LCD_ProcessData},
								{LCD_ExecuteCMD,
								 LCD_WaitIfBusy}
								};
