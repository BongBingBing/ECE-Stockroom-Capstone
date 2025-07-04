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
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include <stdbool.h>

//code to enable scanf redirection functions
#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

/*Global Variables*/
uint32_t tare = 0;
float knownOriginal = 1;  // in milli-gram
float knownHX711 = 1;
int weight = 0;

uint16_t A_mast;
uint16_t B_mast;
uint16_t C_mast;

uint16_t A_slave;
uint16_t B_slave;
uint16_t C_slave;

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// change these GPIO to the peripherals and pins we are using for project
#define DT_PIN GPIO_PIN_8
#define DT_PORT GPIOA
#define SCK_PIN GPIO_PIN_5
#define SCK_PORT GPIOB

//Code to enable printf statements
int _write(int file, char *data, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY); // Replace &huart2 with your UART instance
    return len;
}

GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;

  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart2);

  /* Wait for reception of a character on the USART RX line and echo this
   * character on console */
  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

void microDelay(uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  while (__HAL_TIM_GET_COUNTER(&htim2) < delay);
}

int32_t getHX711(void)
{
  uint32_t data = 0;
  uint32_t startTime = HAL_GetTick();
  while(HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_SET)
  {
    if(HAL_GetTick() - startTime > 200)
      return 0;
  }
  for(int8_t len=0; len<24 ; len++)
  {
    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
    microDelay(1);
    data = data << 1;
    HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
    microDelay(1);
    if(HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_SET)
      data ++;
  }
  data = data ^ 0x800000;
  HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
  microDelay(1);
  HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
  microDelay(1);
  return data;
}

/*########################################################################################################*/

int weigh()
{
  int64_t  total = 0;
  int32_t  samples = 150;
  int milligram;
  float coefficient;
  for(uint16_t i=0 ; i<samples ; i++)
  {
      total += getHX711();
  }
  int32_t average = (int32_t)(total / samples);
  coefficient = knownOriginal / knownHX711;
  milligram = (int)((average - tare)*1000)*coefficient;
  return milligram;
}

int32_t weighRaw()
{
  int64_t  total = 0;
  int32_t  samples = 150;

  for(uint16_t i=0 ; i<samples ; i++)
  {
      total += getHX711();
  }
  int32_t average = (int32_t)(total / samples);
  return average;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

void setTare(){
	printf("Gathering initial Tare of Load Cell...\n\r");

	for(uint16_t i = 0; i < 4; i++){
		int weight_temp = weighRaw();
		printf("%d\n\r", weight_temp);
		HAL_Delay(10);
	}

	HAL_Delay(100);
	int weight_tare = weighRaw();

	tare = weight_tare;

	printf("Tare Set: %d\n\r", weight_tare);
}

void setOffset(){
	printf("Input the weight of the object in miligrams\n\r");
	float tempOffsetWeight = 0;
	scanf("%f", &tempOffsetWeight);

	knownOriginal = tempOffsetWeight;

	printf("Setting weight of the HX711 readable weight...\n\r");

	HAL_Delay(10);
	int weight_offset = weighRaw();
	HAL_Delay(10);

	printf("Read weight: %d\n\r", weight_offset);
	knownHX711 = weight_offset;

}

void muxSET(uint16_t A, uint16_t B, uint16_t C, bool control){
  if(control){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, A);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, B);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, C);
  } 
  else{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, A);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, B);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, C);
  }
}

/*########################################################################################################*/

struct MuxCombo {
  unsigned char A;
  unsigned char B;
  unsigned char C;
};

const struct MuxCombo MuxCombos[] = {
  {0, 0, 0},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0}
};


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

	printf("Hello from STM32 UART!\n\r");

	HAL_TIM_Base_Start(&htim2);
	HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);
	/* USER CODE END 1 */

	/* USER CODE BEGIN Init */
	/* USER CODE END Init */

	/* USER CODE BEGIN SysInit */
	/* USER CODE END SysInit */


	/* USER CODE BEGIN 2 */
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while(1){


	for(uint16_t i = 0; i <= 3; i++){
		A_mast = MuxCombos[i].A;
		B_mast = MuxCombos[i].B;
		C_mast = MuxCombos[i].C;

    muxSET(A_mast, B_mast, C_mast, 1);

		for(uint16_t k = 0; k <= 6; k++){

			/* Reset Initial Variables */
			tare = 0;
		  knownOriginal = 1;  // in milli-gram
		  knownHX711 = 1;
		  weight = 0;

		  A_slave = MuxCombos[k].A;
		  B_slave = MuxCombos[k].B;
		  C_slave = MuxCombos[k].C;

		  muxSET(A_slave, B_slave, C_slave, 0);

		  setTare();
		  setOffset();

		  uint16_t count = 0;

	  	printf("Row: %d, Drawer: %d\n\r", i, k);

		  while(count <= 9){
		  	weight = weigh();

		  	printf("Weight: %d", weight);

        HAL_Delay(100);

		  	count++;
		  }

		}
	}

	}
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
