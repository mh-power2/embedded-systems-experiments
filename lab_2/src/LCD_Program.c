#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <util/delay.h>

int LOC = 0;

void LCD_VidPulse()
{
	/*Function to create a pulse*/

	DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, PinHigh);

	_delay_ms(2);

	DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, PinLow);
}

void LCD_VidSendCommand(u8 Copy_u8Command)
{
	/*Function to send command to LCD*/

	// set the mode to reading instructions
	DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, PinLow);

// in case of 8bit
#if LCD_MODE == 8

	// SET CONTROL PORT
	DIO_VidSetPortValue(LCD_DATA_PORT, Copy_u8Command);
	LCD_VidPulse();

#elif LCD_MODE == 4

	/* Send Higher nibble */
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, Get_bit(Copy_u8Command, 4));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, Get_bit(Copy_u8Command, 5));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, Get_bit(Copy_u8Command, 6));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, Get_bit(Copy_u8Command, 7));

	LCD_VidPulse();

	/* Send lower nibble */
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, Get_bit(Copy_u8Command, 0));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, Get_bit(Copy_u8Command, 1));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, Get_bit(Copy_u8Command, 2));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, Get_bit(Copy_u8Command, 3));

	LCD_VidPulse();

#endif
}

// SEND DATA FUNCTION
void LCD_VidSendData(u8 Copy_u8Data)
{

#if LCD_MODE == 8

	// set the mode to reading Data
	DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, PinHigh);

	if (LOC == 16)
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION + LCD_SEGMENT_1_OF_ROW_1);
	else if (LOC == 32)
	{
		_delay_ms(1000);
		LCD_VidClear();
		LOC = -1;
	}
	LOC++;

	// SET CONTROL PORT
	DIO_VidSetPortValue(LCD_DATA_PORT, Copy_u8Data);
	LCD_VidPulse();

#elif LCD_MODE == 4

	if (LOC == 16)

		// Set DDRAM address or coursor position on display	0x80+pos
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION | LCD_SEGMENT_1_OF_ROW_1);
	else if (LOC == 32)
	{
		_delay_ms(10000);
		LCD_VidClear();
		LOC = -1;
	}
	LOC++;

	// set the mode to reading Data
	DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, PinHigh);

	/* Send Higher nibble */
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, Get_bit(Copy_u8Data, 4));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, Get_bit(Copy_u8Data, 5));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, Get_bit(Copy_u8Data, 6));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, Get_bit(Copy_u8Data, 7));

	LCD_VidPulse();

	/* Send lower nibble */
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, Get_bit(Copy_u8Data, 0));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, Get_bit(Copy_u8Data, 1));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, Get_bit(Copy_u8Data, 2));
	DIO_VidSetPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, Get_bit(Copy_u8Data, 3));

	LCD_VidPulse();

#endif
}

// Initialization Function
void LCD_VidInit()
{

	// SET PIN RS DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, Output);

	// SET PIN E DIRECTION TO BE OUTPUT
	DIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_E_PIN, Output);

#if LCD_MODE == 8

	// SET PORT A DIRECTION TO BE OUTPUT
	DIO_VidSetPortDirection(LCD_DATA_PORT, Output);

	_delay_ms(40);

	// FUNCTION SET COMMAND: 8bit mode 2 LINES, 5*8 FONT SIZE
	LCD_VidSendCommand(LCD_EIGHT_BIT_MODE_TWO_LINES);

	// DISPLAY ON OFF CONTROL: DISPLAY ENABLE, DISPLAY CURSOR, ON BLINK CURSOR
	LCD_VidSendCommand(LCD_CURSOR_OFF_BLINK);

	// CLEAR DISPLAY
	LCD_VidSendCommand(LCD_CLEAR);

#elif LCD_MODE == 4

	// SET 4 pins as Output
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN0, Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN1, Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN2, Output);
	DIO_VidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN3, Output);

	_delay_ms(40);

	// FUNCTION SET COMMAND:set 4bit mode
	LCD_VidSendCommand(LCD_FOUR_BIT_MODE_S1); // 0x33
	LCD_VidSendCommand(LCD_FOUR_BIT_MODE_S2); // 0x32

	// FUNCTION SET COMMAND: 2 LINES, 5*8 FONT SIZE in 4bit mode
	LCD_VidSendCommand(LCD_FOUR_BIT_MODE_TWO_LINES);

	_delay_ms(40);
	// DISPLAY ON OFF CONTROL: DISPLAY ENABLE, DISPLAY CURSOR, ON BLINK CURSOR
	LCD_VidSendCommand(LCD_CURSOR_OFF_BLINK);

	// Increment cursor (shift cursor to right)
	LCD_VidSendCommand(0x06);

	// CLEAR DISPLAY
	LCD_VidSendCommand(LCD_CLEAR);

#endif
}

// SEND STRING FUNCTION
void LCD_VidSendString(char *Copy_u8Data)
{
	int Iterator = 0;
	while (Copy_u8Data[Iterator] != '\0')
	{
		LCD_VidSendData(Copy_u8Data[Iterator]);
		Iterator++;
	}
}

// SET POSITION FUNCTION
void LCD_VidSetPosition(u8 Copy_u8Row, u8 Copy_u8Columm)
{

	if (Copy_u8Row == LCD_ROW1)
	{
		LOC = Copy_u8Columm;
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION | Copy_u8Columm);
	}
	else if (Copy_u8Row == LCD_ROW2)
	{
		LOC = 16 + Copy_u8Columm;
		LCD_VidSendCommand(LCD_FORCE_START_LOCATION | LCD_SEGMENT_1_OF_ROW_1 | Copy_u8Columm);
	}
}

void LCD_VidClear()
{
	LOC = 0;
	LCD_VidSendCommand(LCD_CLEAR); /* Clear display */
	_delay_ms(2);
	LCD_VidSendCommand(LCD_FORCE_START_LOCATION); /* Cursor at home position */
}

/*************************************************************************/

// SEND NUMBER FUNCTION
void LCD_VidSendfloat(f32 Copy_u8Data)
{
	char floatStr[20]; // Adjust the size as needed
	int n = Copy_u8Data;
	int digit = 1;
	while (n != 0)
	{
		n = n / 10;
		digit++;
	}
	dtostrf(Copy_u8Data, digit + 2, 2, floatStr);
	LCD_VidSendString(floatStr);
}

void LCD_VidSendint(int Copy_u8Data)
{
	char intstr[20]; // Adjust the size as needed
	sprintf(intstr, "%d", Copy_u8Data);
	LCD_VidSendString(intstr);
}
