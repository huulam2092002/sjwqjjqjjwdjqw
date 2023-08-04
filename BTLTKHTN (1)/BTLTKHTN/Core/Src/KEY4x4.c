#include "main.h"
#include "KEY4x4.h"
uint8_t KEY4x4_Push(void){									// Kiem tra xem co nut duoc nhan hay khong
	HAL_GPIO_WritePin(GPIOB,A,0);
	HAL_GPIO_WritePin(GPIOB,B,0);
	HAL_GPIO_WritePin(GPIOB,C,0);						
	HAL_GPIO_WritePin(GPIOB,D,0);
	if(HAL_GPIO_ReadPin(GPIOB,C1)==0|HAL_GPIO_ReadPin(GPIOB,C2)==0|HAL_GPIO_ReadPin(GPIOB,C3)==0|HAL_GPIO_ReadPin(GPIOB,C4)==0)
		return 1;
	 else return 0;
	}
void KEY4x4_ScanRow(uint8_t row){						// Quet hang
	HAL_GPIO_WritePin(GPIOB,A,1);
	HAL_GPIO_WritePin(GPIOB,B,1);						
	HAL_GPIO_WritePin(GPIOB,C,1);
	HAL_GPIO_WritePin(GPIOB,D,1);
	if(row==0) HAL_GPIO_WritePin(GPIOB,A,0);
	else if (row==1) HAL_GPIO_WritePin(GPIOB,B,0);
	else if (row==2) HAL_GPIO_WritePin(GPIOB,C,0);
	else if (row==3) HAL_GPIO_WritePin(GPIOB,D,0);}
uint8_t KEY4x4_CheckCol(void){			 // Quet cot
	uint8_t col;
	if(HAL_GPIO_ReadPin(GPIOB,C1)==0)						return col=0;
	else if(HAL_GPIO_ReadPin(GPIOB,C2)==0) 			return col=1;
	else if(HAL_GPIO_ReadPin(GPIOB,C3)==0) 			return col=2;
	else if(HAL_GPIO_ReadPin(GPIOB,C4)==0)			return col=3;
	return 4;
}
char KEY4x4_GetKey(void){	// Tra ve ki tu tren ban phim
	uint8_t i,t;
		if(KEY4x4_Push()) {
			HAL_Delay(150);
	for(i=0;i<4;i++){
		KEY4x4_ScanRow(i);
		t= KEY4x4_CheckCol();
		if(t!=4) return keypad[i][t] ;
			}
		} 	
	return 'n';         // Ki tu cho biet khong co su kien nhan xay ra
}