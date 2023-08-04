#ifndef __LCD16x2_
#define __LCD16x2_
#include "main.h"
void LCD_Enable(void);
void LCD_Send4bit(unsigned char data);
void LCD_SendCommand(unsigned cmd);
void LCD_Clear();
void LCD_Init();
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar(unsigned char text);
void LCD_WriteString(char*s);
#endif