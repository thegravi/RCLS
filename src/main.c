/*
 * main.c
 *
 *  Created on: 2013.09.24
 *      Author: Gražvidas
 */


#include <avr/io.h>
#include "lcd.h"
#include "lcd_menu.h"
#include "buttons.h"
#include "uart.h"

#define F_CPU 8000000UL

void Init(void);

int main()
{

	Init();

//	LCD_Menu.Enter();
	char* functionName = 0;
	DDRC |= 1<<PC5;

	LCD_Menu_BottomLineDeclaration();
	functionName = LCD_Menu.Options.CurrentFunctionName[0];
	LCD_Interface.DataFlow.SendString(functionName);

	while(1)
	{

		LCD_Menu_Option_Selection(2);
		LCD_Menu.optionSelected = B_VOID;

		while(LCD_Menu.optionSelected)
		{
//					UART.sendString("i");
//					asm("nop");
//		//				PORTC |= 1<<PC5;
//		//				_delay_ms(50);
			//if (LCD_Menu.optionSelected != OPT_VOID) { break;}
		}

	}

	return 0;
}

void Init()
{
	UART.Init();
	TCCR0B |= (1<<CS02) | (1<<CS00);
	TIMSK0 |= (1<<TOIE0);

	LCD_Interface.Initialize();
	LCD_Menu.Initialize();
	BUTTONS_Interface.Initialize();

	LCD_Interface.DataFlow.SendCommand(8, 0x01);
	LCD_Interface.Position(2, 1);
	LCD_Interface.DataFlow.SendString("COMPLETED");	_delay_ms(500);
	LCD_Interface.DataFlow.SendCommand(8, 0x01);
}

// TODO: set INT0 for OPT_NEXT
// TODO: set INT1 for OPT_PREV
// TODO: set PCINT0 for OPT_SELECT
// TODO: set PCINT1 for OPT_RETURN



//ISR (TIMER0_OVF_vect){}
