/**
 * main.c
 *
 * Created: 2024-03-05T21:34:28.675Z
 * Author: Dedinside
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"

#include <util\delay.h>

int main(void)
{
    LCD_VidInit();

    while (1)
    {
        // LTR
        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 1);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 2);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 3);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 4);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 5);

        // RTL
        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 4);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 3);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 2);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 1);

        LCD_VidSendString("Hello");
        _delay_ms(1000);
        LCD_VidClear();
        LCD_VidSetPosition(0, 0);
    }
}
