#ifndef __KEY4x4_H
#define __KEY4x4_H
#include "main.h"
#define C1 GPIO_PIN_0
#define C2 GPIO_PIN_1
#define C3 GPIO_PIN_3
#define C4 GPIO_PIN_4
#define A GPIO_PIN_5
#define B GPIO_PIN_6
#define C GPIO_PIN_7
#define D GPIO_PIN_8
static char keypad[4][4]={{'7', '8' , '9' , '/'},
												 {'4' ,'5' , '6', '*'},
												 {'1' , '2' , '3', '-'},
												 {'C' , '0', '=' , '+'}};
uint8_t KEY4x4_Push(void);
void KEY4x4_ScanRow(uint8_t row);
uint8_t KEY4x4_CheckCol(void);
char KEY4x4_GetKey(void);
#endif