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
#include "usart.h"
#include "gpio.h"
// this is pin D7 on STM32 Board
#define b_pin GPIO_PIN_8
#define b_port GPIOA
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//Code to enable printf statements
	int _write(int file, char *data, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY); // Replace &huart2 with your UART instance
    return len;
	}
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
//also for double press
          /*
           * we should try to do a while loop that or make a countdown function to wait a certain time for a double press to happen or not
           *
           * if (presscount == 1 && ((HAL_GetTick() - current_time) < DP_Threshold ) ) { // Check again
						 printf("double button pressed\n");
						 presscount = 0;
						 break;
			}if (button_state == GPIO_PIN_RESET && presscount == 1){
						printf("hi\n");
						presscount = 0;
				}
				if (button_state == GPIO_PIN_RESET && presscount == 1)
           * */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  GPIO_PinState button_state;

  /* USER CODE END 1 */

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
  GPIO_PinState last_state = GPIO_PIN_RESET;

  uint32_t DP_Threshold = 2000; // 2 second threshold
  uint32_t press_time = 0;         // Timestamp of the first press
  uint8_t press_count = 0;  // A Flag that's used for indicating a second press

  /* USER CODE END 2 */

  /* Infinite loop */
  while (1)
  {
    button_state = HAL_GPIO_ReadPin(b_port, b_pin);

    if (button_state != last_state) { // Button state changed
      HAL_Delay(50); // Debounce delay
      if (button_state == GPIO_PIN_SET) { // Button pressed
        if (press_count == 0) {
          // Reads First press
          printf("Button press\n");
          press_time = HAL_GetTick(); // saves the time of the first press
          press_count = 1;    // proof of first button press
        }
        // if the press_count = 1 and the button is pressed again, it is a double press
        	else if ((HAL_GetTick() - press_time) <= DP_Threshold){
        		printf("Double press\n");
        		press_count = 0; // Reset state
        }
      }
      // goes through the else statement once button is released
      else {
    	  // if press_count = 1, if is true
        if (press_count) {
        // if the button is pressed for a longer period than the DP_Threshold value
          if ((HAL_GetTick() - press_time) > DP_Threshold) {
        	  //it will be read as long press
            printf("Long Press\n");
            press_count = 0; // Reset state
            printf("Button released\n");
          }
        } else {
          // Always output "Button released"
          printf("Button released\n");
        }
      }

      last_state = button_state; // Update the last state
    }

    // if there is no double press within the time frame, this statement is printed for the single press
    /**/if (button_state != GPIO_PIN_SET && press_count && (HAL_GetTick() - press_time) > DP_Threshold) {
      printf("Button released 2\n");
      press_count = 0; // Reset state
    }
  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
