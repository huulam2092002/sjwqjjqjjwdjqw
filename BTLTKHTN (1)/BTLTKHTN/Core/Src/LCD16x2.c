#include "LCD16x2.h"
void LCD_Enable(void){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,0);
	HAL_Delay(1);
}
void LCD_Send4bit(unsigned char data){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,data&0x01);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,(data>>1)&0x01);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,(data>>2)&0x01);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,(data>>3)&0x01);
}
void LCD_SendCommand(unsigned cmd){
	LCD_Send4bit(cmd>>4);
	LCD_Enable();
	LCD_Send4bit(cmd);
	LCD_Enable();
}
void LCD_Clear(){
	LCD_SendCommand(0x01);
	HAL_Delay(2);
}
void LCD_Init(){
	LCD_Send4bit(0x00);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,0);
	LCD_Send4bit(0x03);
	LCD_Enable();
	LCD_Enable();
	LCD_Enable();
	LCD_Send4bit(0x02);
	LCD_Enable();
	LCD_SendCommand(0x28);
	LCD_SendCommand(0x0C);
	LCD_SendCommand(0x06);
	LCD_SendCommand(0x01);
}
void LCD_Gotoxy(unsigned char x, unsigned char y){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,0);
	if(x==0) LCD_SendCommand(0x80+y);
	else if(x==1) LCD_SendCommand(0xC0+y);
}
void LCD_PutChar(unsigned char text){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,1);
	LCD_SendCommand(text);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,0);
}
void LCD_WriteString(char*s){
	while(*s){
		LCD_PutChar(*s);
		s++;
	}
}