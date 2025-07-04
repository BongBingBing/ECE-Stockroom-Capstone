/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dma.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <function_calibration.h>
#include <function_main.h>
#include <manager_mux.h>
#include <manager_weight.h>
#include <stdio.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "drawer_table.h"

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// change these GPIO to the peripherals and pins we are using for project

int row_num;
int drawer_num;

extern volatile bool reset_requested;
extern volatile uint32_t reset_request_time;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

	//disables internal buffering for input stream for scanf
	setvbuf(stdin, NULL, _IONBF, 0);

	/* Configure the system clock */
	SystemClock_Config();

	/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_TIM2_Init();
	MX_FATFS_Init();
	MX_SPI1_Init();

	printf("Hello from STM32 UART!\n\r");

	HAL_TIM_Base_Start(&htim2);
	HAL_GPIO_WritePin(SCK_DRW_GPIO_Port, SCK_DRW_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(SCK_DRW_GPIO_Port, SCK_DRW_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();

//  int rectXStart = 80;
//  int rectYStart = 80;

  // Simple Text writing (Text, Font, X, Y, Color, BackColor)
  // Available Fonts are FONT1, FONT2, FONT3 and FONT4
  ILI9341_FillScreen(BLACK);
  ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
  ILI9341_DrawText("Hello from STM32 UART!", FONT4, 55, 110, WHITE, BLACK);
  HAL_Delay(3000);
  ILI9341_FillScreen(BLACK);
  drawer_table();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//  while(1){
//  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
//  	printf("ON");
//  	HAL_Delay(2000);
//
//  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
//  	printf("OFF");
//  	HAL_Delay(2000);
//
//  }

//  while(1){
//
//  	HAL_GPIO_WritePin(SLAVE_A_GPIO_Port, SLAVE_A_Pin, 1);
//		HAL_GPIO_WritePin(SLAVE_B_GPIO_Port, SLAVE_B_Pin, 1);
//		HAL_GPIO_WritePin(SLAVE_C_GPIO_Port, SLAVE_C_Pin, 1);
//
//		HAL_GPIO_WritePin(MAST_A_GPIO_Port, MAST_A_Pin, 1);
//		HAL_GPIO_WritePin(MAST_B_GPIO_Port, MAST_B_Pin, 1);
//		HAL_GPIO_WritePin(MAST_C_GPIO_Port, MAST_C_Pin, 1);
//
//		HAL_GPIO_WritePin(AUX_SLAVE_A_GPIO_Port, AUX_SLAVE_A_Pin, 1);
//		HAL_GPIO_WritePin(AUX_SLAVE_B_GPIO_Port, AUX_SLAVE_B_Pin, 1);
//		HAL_GPIO_WritePin(AUX_SLAVE_C_GPIO_Port, AUX_SLAVE_C_Pin, 1);
//
//		HAL_GPIO_WritePin(AUX_MAST_A_GPIO_Port, AUX_MAST_A_Pin, 1);
//		HAL_GPIO_WritePin(AUX_MAST_B_GPIO_Port, AUX_MAST_B_Pin, 1);
//		HAL_GPIO_WritePin(AUX_MAST_C_GPIO_Port, AUX_MAST_C_Pin, 1);
//
//		HAL_Delay(1000);
//
//  	HAL_GPIO_WritePin(SLAVE_A_GPIO_Port, SLAVE_A_Pin, 0);
//		HAL_GPIO_WritePin(SLAVE_B_GPIO_Port, SLAVE_B_Pin, 0);
//		HAL_GPIO_WritePin(SLAVE_C_GPIO_Port, SLAVE_C_Pin, 0);
//
//		HAL_GPIO_WritePin(MAST_A_GPIO_Port, MAST_A_Pin, 0);
//		HAL_GPIO_WritePin(MAST_B_GPIO_Port, MAST_B_Pin, 0);
//		HAL_GPIO_WritePin(MAST_C_GPIO_Port, MAST_C_Pin, 0);
//
//		HAL_GPIO_WritePin(AUX_SLAVE_A_GPIO_Port, AUX_SLAVE_A_Pin, 0);
//		HAL_GPIO_WritePin(AUX_SLAVE_B_GPIO_Port, AUX_SLAVE_B_Pin, 0);
//		HAL_GPIO_WritePin(AUX_SLAVE_C_GPIO_Port, AUX_SLAVE_C_Pin, 0);
//
//		HAL_GPIO_WritePin(AUX_MAST_A_GPIO_Port, AUX_MAST_A_Pin, 0);
//		HAL_GPIO_WritePin(AUX_MAST_B_GPIO_Port, AUX_MAST_B_Pin, 0);
//		HAL_GPIO_WritePin(AUX_MAST_C_GPIO_Port, AUX_MAST_C_Pin, 0);
//
//		HAL_Delay(1000);
//
//  }

  Calibrate();
  main_function();


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
