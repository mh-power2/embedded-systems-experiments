#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>
#include <avr/io.h>
#include<avr/interrupt.h>
u8 x=0x41;
int main()
{

	DDRD&=~(1<<2); 	//setting pinD2 as input to use it for INT0
	DDRD&=~(1<<4);
	DDRD&=~(1<<6);
	MCUCR|=(1<<ISC01) | (1<<ISC00); //applying rising edge mode
	GICR|=(1<<INT0);//enable INT0
	sei();
	DDRB|=(1<<5)|(1<<7);//setting PINB7/SCk PINB5/MOSI PINB4/SS as outputs
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);// enable SPi -- enable master -- making CLKcpu/16
while(1)
{

}


}

ISR(INT0_vect)
{
	SPDR=x++;
	while(!(SPSR & (1<<SPIF) ));

	if(x==0x7A)
	{
		x=0x41;
	}
	_delay_ms(200);

}
