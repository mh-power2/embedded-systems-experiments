
#include <avr/io.h>
#include <util\delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "LCD_interface.h"

void setup_interrupt()
{
    // Configure PD2 as input
    DDRD &= ~(1 << PD2);
    // Enable pull-up resistor on PD2
    PORTD |= (1 << PD2);
    // Enable INT0 interrupt
    GICR |= (1 << INT0);
    // Enable global interrupts
    sei();
}

void setupADC()
{
    // Select ADC0 channel
    ADMUX = (1 << REFS0);
    // Enable ADC, set prescaler to 128 (16MHz/128 = 125kHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int main(void)
{
    LCD_VidInit();
    setup_interrupt();
    setupADC();
    LCD_VidSendString("Press the button");

    while (1)
    {
        // Main loop
    }

    return 0;
}

ISR(INT0_vect)
{
    // Start ADC conversion
    ADCSRA |= (1 << ADSC);
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC))
        ;
    // Read ADC0
    uint16_t adcValue = ADC;

    float voltage_step_size = 5.0 / 1024 * 1000; // in mV

    int temp = adcValue * voltage_step_size; // Convert ADC reading to mV
    temp = temp / 10;

    // Clear LCD screen
    LCD_VidClear();

    // Display ADC0 reading on the first line of LCD screen
    char buffer[16];
    sprintf(buffer, "ADC0: %d", temp);
    LCD_VidSendString(buffer);

    // Wait for 2 seconds
    _delay_ms(2000);
    LCD_VidClear();
    LCD_VidSendString("Press the button");
}