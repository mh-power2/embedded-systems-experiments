#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#define LCD_MODE 4

#define LCD_RS_PIN Pin1
#define LCD_E_PIN Pin2

#if LCD_MODE == 8

#define LCD_DATA_PORT Port_A
#define LCD_CTRL_PORT Port_C

#elif LCD_MODE == 4

#define LCD_DATA_PORT Port_A
#define LCD_CTRL_PORT Port_A
#define LCD_DATA_PIN0 Pin3
#define LCD_DATA_PIN1 Pin4
#define LCD_DATA_PIN2 Pin5
#define LCD_DATA_PIN3 Pin6

#endif

#define LCD_ROW1 0
#define LCD_ROW2 1

#define LCD_COLUMN1 0
#define LCD_COLUMN2 1
#define LCD_COLUMN3 2
#define LCD_COLUMN4 3
#define LCD_COLUMN5 4
#define LCD_COLUMN6 5
#define LCD_COLUMN7 6
#define LCD_COLUMN8 7
#define LCD_COLUMN9 10
#define LCD_COLUMN10 11
#define LCD_COLUMN11 12
#define LCD_COLUMN12 13
#define LCD_COLUMN13 14
#define LCD_COLUMN14 15
#define LCD_COLUMN15 16
#define LCD_COLUMN16 17

#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_EIGHT_BIT_MODE_TWO_LINES 0x38
#define LCD_FOUR_BIT_MODE_S1 0x33
#define LCD_FOUR_BIT_MODE_S2 0x32
#define LCD_FOUR_BIT_MODE_TWO_LINES 0x28
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_BLINK 0x0D
#define LCD_CURSOR_OFF_BLINK 0x0C
#define LCD_FORCE_START_LOCATION 0x80
#define LCD_SEGMENT_1_OF_ROW_1 0x40

#endif
