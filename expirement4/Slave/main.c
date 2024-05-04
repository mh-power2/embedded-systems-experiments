#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include <avr/io.h>
#include <util/delay.h>
int main()
{
	LCD_VidInitilization();
	DDRB&=~(1<<5);
	DDRB&=~(1<<4);
	DDRB&=~(1<<7);
	DDRB|=(1<<6);
	SPCR |= (1<<SPE)|(1<<SPR0);
	u8 x;
	while(1)
	{


		while(!(SPSR & (1<<SPIF) ));
		x=SPDR;
		LCD_VidClear();
		LCD_VidSendChar(x);
		_delay_ms(200);

	}
}
