#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_VidInit(void);

void LCD_VidSendCommand(u8 u8Command);

void LCD_VidSendData(u8 Copy_u8Data);

void LCD_VidSendString(char *Copy_u8Data);

void LCD_VidSetPosition(u8 Copy_u8Row, u8 Copy_u8Columm);

void LCD_VidSendfloat(f32 Copy_u8Data);

void LCD_VidSendint(int Copy_u8Data);

void LCD_VidClear(void);

#endif
