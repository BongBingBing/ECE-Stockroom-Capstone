/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include <stdio.h>

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

/* USER CODE END 0 */

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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();

  int rectXStart = 80;
  int rectYStart = 80;

    // Simple Text writing (Text, Font, X, Y, Color, BackColor)
    // Available Fonts are FONT1, FONT2, FONT3 and FONT4
    ILI9341_FillScreen(BLACK);
    ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
    ILI9341_DrawText("HELLO WORLD", FONT4, 90, 110, WHITE, BLACK);
    HAL_Delay(3000);
/*
    ILI9341_FillScreen(BLACK);
    ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
    ILI9341_DrawText("HOW ARE YOU", FONT3, 200, 220, BLACK, WHITE);
    HAL_Delay(1000);

    ILI9341_FillScreen(WHITE);
    ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
    ILI9341_DrawText("I Am Fine", FONT4, 50, 70, WHITE, BLACK);
    HAL_Delay(1000);
    ILI9341_DrawText("Thank You", FONT4, 130, 150, BLACK, WHITE);
*/
    HAL_Delay(1000);
    ILI9341_FillScreen(BLACK);
    ILI9341_DrawHollowRectangleCoord(50, 50, 220, 140, WHITE);
    HAL_Delay(1000);
    ILI9341_DrawText("Testing", FONT3, 95, 85, WHITE, BLACK);
    HAL_Delay(1000);
    ILI9341_DrawPixel(160, 95, WHITE);

    //Writing numbers
    //ILI9341_FillScreen(BLACK);
//    static char BufferText[30];
//    for(uint8_t i = 0; i <= 5; i++)
//    {
//      sprintf(BufferText, "COUNT : %d", i);
//      ILI9341_DrawText(BufferText, FONT3, 10, 10, BLACK, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 30, BLUE, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 50, RED, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 70, GREEN, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 90, YELLOW, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 110, PURPLE, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 130, ORANGE, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 150, MAROON, WHITE);
//      ILI9341_DrawText(BufferText, FONT3, 10, 170, WHITE, BLACK);
//      ILI9341_DrawText(BufferText, FONT3, 10, 190, BLUE, BLACK);
//    }

    // Horizontal Line (X, Y, Length, Color)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawHLine(50, 120, 200, NAVY);
//    HAL_Delay(1000);
//
//    // Vertical Line (X, Y, Length, Color)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawVLine(160, 40, 150, DARKGREEN);
//    HAL_Delay(1000);
//
//    // Hollow Circle (Centre X, Centre Y, Radius, Color)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawHollowCircle(160, 120, 80, PINK);
//    HAL_Delay(1000);
//
//    // Filled Circle (Centre X, Centre Y, Radius, Color)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawFilledCircle(160, 120, 50, CYAN);
//    HAL_Delay(1000);
//
//    // Filled Rectangle (Start X, Start Y, Length X, Length Y)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawRectangle(50, 50, 220, 140, GREENYELLOW);
//    HAL_Delay(1000);

    // Hollow Rectangle (Start X, Start Y, End X, End Y)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawHollowRectangleCoord(50, 50, 270, 190, WHITE);
//    HAL_Delay(1000);

//    // Simple Pixel Only (X, Y, Color)
//    ILI9341_FillScreen(WHITE);
//    ILI9341_DrawPixel(100, 100, BLACK);
//    HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //ILI9341_DrawHollowRectangleCoord(80, 80, 310, 230, WHITE);

  while(1){


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
  RCC_OscInitStruct.PLL.PLLN = 72;
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
