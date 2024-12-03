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
#include "stdio.h"
#include "stdio.h"
// this is pin D7 on STM32 Board
#define b_pin GPIO_PIN_8
#define b_port GPIOA

// this is pin D8 on STM32 Board
#define set_pin GPIO_PIN_10
#define set_port GPIOA
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
int x = 0;

GPIO_PinState button_state;
GPIO_PinState button_state_2;
GPIO_PinState last_state = GPIO_PIN_RESET;
GPIO_PinState last_state_2 = GPIO_PIN_RESET;

int incr_decr(void){
	uint32_t press_time;
	uint32_t count;
	uint32_t DP_Threshold = 1000;

	printf("We will add 5 to x\n\r");
	HAL_Delay(500);
	printf("Do you want to confirm? (Double press to confirm)\n\r");
	//button_state = HAL_GPIO_ReadPin(b_port, b_pin);
	HAL_Delay(500);
	// this is for reading a double press from button 1
	while( HAL_GPIO_ReadPin(b_port, b_pin) == GPIO_PIN_RESET){
		// stays turn until button 1 is pressed
	}
		printf("Button Pressed\n\r");
		count = 1;
		while( HAL_GPIO_ReadPin(b_port, b_pin) == GPIO_PIN_SET){
			// prevents the program from executing until button 1 is released
		}
		//HAL_Delay(500);
		 press_time = HAL_GetTick(); // the time when button 1 is pressed
		 //if the press_count = 1 and the button is pressed again, it is a double press
			while(count == 1 && (HAL_GetTick() - press_time) <= DP_Threshold ){
				//printf("In while loop\n\r");
				if (HAL_GPIO_ReadPin(b_port, b_pin) == GPIO_PIN_SET){
					printf("Double Press\n\r");
					x+=5;
					HAL_Delay(500);
					printf("User wants to confirm\n\r");
					HAL_Delay(500);
					count = 0; // reset count
					break;
			}
				/*else {
					count = 0;
				}*/
		}
			// restart count if button 1 is pressed only once
			if (count == 1){
				count = 0;
			}
			return x;
	}

// exact same code from the one above
int restart(void){
	uint32_t press_time;
	uint32_t count;
	uint32_t DP_Threshold = 1000;

	printf("We will reset the value of x\n\r");
	HAL_Delay(500);
	printf("Do you want to confirm? (Double press to confirm)\n\r");
	//button_state = HAL_GPIO_ReadPin(b_port, b_pin);
	HAL_Delay(500);
	// this is for reading a double press from button 1
	while( HAL_GPIO_ReadPin(set_port, set_pin) == GPIO_PIN_RESET){
		// stays turn until button 1 is pressed
	}
		printf("Button Pressed\n\r");
		count = 1;
		while( HAL_GPIO_ReadPin(set_port, set_pin) == GPIO_PIN_SET){
			// prevents the program from executing until button 1 is released
		}
		//HAL_Delay(500);
		 press_time = HAL_GetTick(); // the time when button 1 is pressed
		 //if the press_count = 1 and the button is pressed again, it is a double press
			while(count == 1 && (HAL_GetTick() - press_time) <= DP_Threshold ){
				//printf("In while loop\n\r");
				if (HAL_GPIO_ReadPin(set_port, set_pin) == GPIO_PIN_SET){
					printf("Double Press\n\r");
					x = 0;
					HAL_Delay(500);
					printf("User wants to confirm\n\r");
					HAL_Delay(500);
					count = 0; // reset count
					break;
			}
				/*else {
					count = 0;
				}*/
		}
			// restart count if button 1 is pressed only once
			if (count == 1){
				count = 0;
			}
			return x;
	}

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  uint8_t state = 0;
	  uint8_t state2 = 0;
	//button_state = HAL_GPIO_ReadPin(b_port, b_pin);
	 if (x < 25){
	  printf("x is less than 25 still\n\r");
	  HAL_Delay(100);
	  printf("Press either button 1 or 2 to configure it\n\r");

	  while(1){
		  // if button 1 is pressed
	  if (HAL_GPIO_ReadPin(b_port, b_pin) == GPIO_PIN_SET){
			 HAL_Delay(500);
			 // calls function and sets it to y
			  int y = incr_decr();
			  HAL_Delay(500);
			  // displays functions output and breaks from the if statement
				printf("%d\n\r",y);
				 HAL_Delay(500);
				  ++state;
				  break;
			  }
			  	 else{
			  		  state = 0;
			  	  }

		 // if button 2 is pressed
	  	  if (HAL_GPIO_ReadPin(set_port, set_pin) == GPIO_PIN_SET){
	  		  	  int z = restart();
	  		  	  HAL_Delay(500);
	  		  	  	printf("the value of x is now %d\n\r",z);
	  		  	  	 HAL_Delay(500);
	  		  	  	 ++state2;
	  		  	  	 break;
				 }
				 	 else	{
				 		state2 = 0;
			}
	 	 }
	  }


    /* USER CODE END WHILE */

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
