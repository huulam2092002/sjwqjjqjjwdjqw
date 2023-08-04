/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "LCD16x2.h"
#include "KEY4x4.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int t;
int t1 ,t2 ;
void shiftOut(int data){
	for(int i= 0;i<8;i++){
		HAL_GPIO_WritePin (GPIOA,GPIO_PIN_6, data << i & 0x80);
		HAL_GPIO_WritePin (GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
		HAL_GPIO_WritePin (GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
	}    
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void hienthi(int so1, int so2){
	unsigned char ma7doan[] =
{// 0 1 2 3 4 5 6 7 8 9 A B C D E F - 
0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0x8F 
};
 shiftOut(ma7doan[so2 % 10]);
 shiftOut(ma7doan[so2 / 10]);
 shiftOut(ma7doan[so1 % 10]);
 shiftOut(ma7doan[so1 / 10]);
 HAL_GPIO_WritePin (GPIOA, GPIO_PIN_8,GPIO_PIN_SET);
 HAL_GPIO_WritePin (GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);
}

void shiftCot( int data1){
	for ( int i =0; i<8 ;i++){
	  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_1,data1 << i & 0x80);
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_0,GPIO_PIN_RESET);
	}
}
void shiftHang( int data2){
	for ( int i =0; i<8 ;i++){
	  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_4,data2 << i & 0x80);
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_3,GPIO_PIN_SET);
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
	}
}
char nguoi[]={0xf6,0xec,0xd9,0x03,0x03,0xd9,0xec,0xf6};
void hienthinguoi(int so){
     if(so==0){
	   for (so=0;so<8;so++){
			HAL_GPIO_WritePin (GPIOB, GPIO_PIN_2,GPIO_PIN_SET);
       shiftHang(nguoi[so]);
			 shiftCot(0x01 << so);
			 HAL_Delay(1);
			HAL_GPIO_WritePin (GPIOB, GPIO_PIN_2,GPIO_PIN_RESET);
		}
	}

	}
int DD,DX,DV;
/* USER CODE END 0 */
int getValueFromKeypad() {
  int value = 0;
  char key = KEY4x4_GetKey();
  while (key != '=') { 
    if (key >= '0' && key <= '9') { 
      value = value * 10 + (key - '0'); 
      LCD_PutChar(key); 
    }
    key = KEY4x4_GetKey(); 
  }
  return value; 
}
void checkInput() {
  do {
    LCD_Clear();
    LCD_WriteString("Nhap den do:"); 
    DD = getValueFromKeypad(); 
    LCD_Clear();
    LCD_WriteString("Nhap den xanh:"); 
    DX = getValueFromKeypad(); 
    LCD_Clear(); 
    LCD_WriteString("Nhap den vang:"); 
    DV = getValueFromKeypad();
  } while (DD != DX + DV); 
}
void displayValues() {
  LCD_Clear(); 
  LCD_WriteString("Bat dau chay"); 
  LCD_Gotoxy(1,0);
	LCD_WriteString("Chuong trinh");
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  HAL_Delay(500);
  checkInput();
  displayValues();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)== SET){
		if(t>=0 && t < DX){
			// X1 D2 ON
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_9,GPIO_PIN_SET);
			t1=DX;
			t2=DD;
			t=t+1;
			t1=t1-t;
			t2=t2-t;
			hienthi(t1,t2);
			hienthinguoi(0);
      HAL_Delay(1000);
		}
		if(t>=DX && t < DD){
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_9,GPIO_PIN_RESET);
			t1=DV;
			t2=DV;
			t=t+1;
			t1=t1-t+DX;
			t2=t2-t+DX;
			hienthi(t1,t2);
			hienthinguoi(0);
			HAL_Delay(1000);
		}
		if(t>=DD && t < (DD+DX)){
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
			t1=DD;
			t2=DX;
			t=t+1;
			t1=t1-t+DD;
			t2=t2-t+DD;
			hienthi(t1,t2);
			HAL_Delay(1000);
		}
		if(t >=(DD + DX) && t < (DD + DX + DV)){
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4,GPIO_PIN_SET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
			t1=DV;
			t2=DV;
			t=t+1;
			t1=t1-t+DX+DD;
			t2=t2-t+DX+DD;
			hienthi(t1,t2);
			HAL_Delay(1000);
		}
		if(t >=(DD + DX + DV))t=0;
	}
		else 
		{
			HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_1);
			HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_4);			
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
			hienthi(0,0);
			HAL_Delay(1000);
		}
	
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|D4_Pin|D5_Pin|D6_Pin
                          |D7_Pin|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 D4_Pin D5_Pin D6_Pin
                           D7_Pin PB5 PB6 PB7
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|D4_Pin|D5_Pin|D6_Pin
                          |D7_Pin|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
