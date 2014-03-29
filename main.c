/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Gražvidas
 */
#include "main.h"
#include <stdlib.h>

int8_t status;

int main()
{
	Init();

	if (RF.initSucc)
		LCD.SendString("RF init success");
	else
		LCD.SendString("RF init failed");
	_delay_ms(1000);

#if send
	uint8_t funcOK;
	uint8_t data[6] = {0, 1, 2, 3, 4, 5};//, 6, 7, 8, 9};
	static uint16_t cnt = 0;

	while(1)
	{
		RF.sendData(data, sizeof(data), &funcOK);
		LCD.Position(2, 1);
		LCD.SendString("Packets send: ");
		LCD.SendNumber(cnt++);
		LCD.Position(1, 16);
		LCD.SendNumber(funcOK);
		_delay_ms(500);
		LCD.Position(1, 16);
		LCD.SendNumber(0);
		_delay_ms(500);
	}
#endif

#if recv
	uint8_t buffer[10];
	uint8_t len;
	uint8_t ok;
	uint8_t i = 0;

	uint8_t state;


	while(1)
	{
		CC_ReceivePacket(buffer, &len, &ok);
//		UART.sendByte(ok);
//		UART.sendString("bytes\n");
//		while (i < 4)
//			UART.sendByte(buffer[i++]);
	}
#endif
	while(1)
	{
//		asm("nop");
	}
//	while(1)
//	{
//		LCD.DataFlow->SendString("------- Menu -------");
//
//		status = Menu.choice(3, Menu.funcNames);
//
//		if (status > -1)
//			Menu.branch[status]();
//	}

	return 0;
}

void Init()
{
	UART.init();
	Init_GPIO();
	LCD.Init();
//	Menu.Init();
//	Buttons.init();
//	Rotary.init();
	Spi.init();
//	WDG.init();
	RF.init();
	__asm__ __volatile__ ("sei");
}

void Init_GPIO()
{
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;

	PORTB = 0;
	PORTC = 0;
	PORTD = 0;

	PORTC |= 1<<PC5;
}

// TODO: repair wdg
