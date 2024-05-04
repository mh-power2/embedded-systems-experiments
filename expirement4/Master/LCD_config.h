

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_PORT	Port_A
#define LCD_RS		Pin1
#define LCD_E		Pin2

#define LCD_CLEAR	 0x01
#define LCD_HOME 	 0x02
#define LCD_INCREMENT_CURSOR 0x06
#define LCD_DECREMENT_CURSOR 0x04
#define LCD_DISPLAY_ON 0x0D
#define LCD_FUNCTION_SET 0x28
#define LCD_1ST_LINE 0x80
#define LCD_2ND_LINE 0xC0
#define SPACEBAR_KEY 0x20

#endif /* LCD_CONFIG_H_ */
