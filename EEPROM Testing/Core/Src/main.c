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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "spi.h"
//#include "usart.h"
//#include "gpio.h"
#include <stdio.h>
#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define EEPROM_CS_LOW()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET)
#define EEPROM_CS_HIGH() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET)

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void EEPROM_WriteEnable(void) {
    uint8_t cmd = 0x06;
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, &cmd, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);

}

void EEPROM_WriteByte(uint8_t addr, uint8_t data) {
    uint8_t buf[3] = {0x02, addr, data}; // WRITE instruction
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, buf, 3, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);

}

uint8_t EEPROM_ReadByte(uint8_t addr) {
    uint8_t cmd[2] = {0x03, addr}; // READ instruction
    uint8_t data = 0;
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, cmd, 2, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi3, &data, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);
    return data;
}

uint8_t EEPROM_ReadStatus(void) {
    uint8_t cmd = 0x05;
    uint8_t status = 0;
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi3, &status, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);
    return status;
}

struct MuxCombo {
  unsigned char C;
  unsigned char B;
  unsigned char A;
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

void muxSET(uint16_t A, uint16_t B, uint16_t C, bool control){
  if(control){
    HAL_GPIO_WritePin(MAST_A_GPIO_Port, MAST_A_Pin, A);
    HAL_GPIO_WritePin(MAST_B_GPIO_Port, MAST_B_Pin, B);
    HAL_GPIO_WritePin(MAST_C_GPIO_Port, MAST_C_Pin, C);
  }
  else{
    HAL_GPIO_WritePin(SLAVE_A_GPIO_Port, SLAVE_A_Pin, A);
    HAL_GPIO_WritePin(SLAVE_B_GPIO_Port, SLAVE_B_Pin, B);
    HAL_GPIO_WritePin(SLAVE_C_GPIO_Port, SLAVE_C_Pin, C);
  }
}

void EEPROM_Write(uint8_t addr, uint8_t writeData){
	printf("Status before write: 0x%02X \r\n", EEPROM_ReadStatus());
	EEPROM_WriteEnable();
	printf("Status after WREN: 0x%02X \r\n", EEPROM_ReadStatus());
	EEPROM_WriteByte(addr, writeData);

	// Wait until write complete
	while (EEPROM_ReadStatus() & 0x01){
		if (EEPROM_ReadStatus() == 0xFF){
			break;
		}
	}
}

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
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


	HAL_Delay(100);

	uint8_t addr = 0x00;
	uint8_t writeData[] = {0xCA, 0xAD, 0xCF, 0xAE, 0xBD, 0xBF, 0xFA, 0xEA};

	uint8_t A;
	uint8_t B;
	uint8_t C;
//	A = MuxCombos[0].A;
//	B = MuxCombos[0].B;
//	C = MuxCombos[0].C;
//
//	muxSET(A, B, C, 1);
//
//	EEPROM_Write(addr, writeData[0]);
//
//	printf("Completed writing to EEPROM, Data: 0x%02X\r\n", writeData[0]);
//
//	uint8_t readData = EEPROM_ReadByte(addr);
//	printf("EEPROM %d, Read back: 0x%02X\r\n", 1, readData);
//	while(1){
//		HAL_Delay(1000);
//	  EEPROM_CS_HIGH();
//	  HAL_Delay(1000);
//	  EEPROM_CS_LOW();
//	}

	for (uint8_t j = 0; j <= 1; j++){

		A = MuxCombos[j].A;
		B = MuxCombos[j].B;
		C = MuxCombos[j].C;

		muxSET(A, B, C, 1);

		for(uint8_t i = 0; i <= 1; i++){
			EEPROM_CS_HIGH();
			A = MuxCombos[i].A;
			B = MuxCombos[i].B;
			C = MuxCombos[i].C;

			muxSET(A, B, C, 0);
			//printf("A: %d, B: %d, C: %d\n\r", A, B, C);
			HAL_Delay(10); // delay to allow muxxes to set
			//EEPROM_CS_LOW();

			EEPROM_Write(addr, writeData[i]);
			HAL_Delay(100);
			uint8_t readData = 0;
			readData = EEPROM_ReadByte(addr);
			printf("EEPROM %d, Read back: 0x%02X\r\n", i + 1, readData);

		}
	}
	printf("Completed writing to all EEPROMs\n\r");

	int index = 0;
	while(1){
		index = index % 2;

		EEPROM_CS_HIGH(); // Deselect EEPROM before switching MUX
		HAL_Delay(10);    // Tiny delay for CS settling


		A = MuxCombos[index].A;
		B = MuxCombos[index].B;
		C = MuxCombos[index].C;

		muxSET(A, B, C, 1);

		HAL_Delay(10);

		// Optional debug:
		uint8_t status = EEPROM_ReadStatus();
		printf("EEPROM %d status: 0x%02X\r\n", index + 1, status);

		uint8_t readData2 = 0;
		readData2 = EEPROM_ReadByte(addr);
		printf("EEPROM %d, Read back: 0x%02X\r\n", index + 1, readData2);

		index += 1;

		HAL_Delay(1000);

	}
//	for(uint8_t i = 0; i <= 1; i++){
//		A = MuxCombos[i].A;
//		B = MuxCombos[i].B;
//		C = MuxCombos[i].C;
//
//		muxSET(A, B, C, 1);
//		printf("A: %d, B: %d, C: %d\n\r", A, B, C);
//		HAL_Delay(100);
//
//		uint8_t readData = EEPROM_ReadByte(addr);
//
//		//EEPROM_CS_HIGH();
//		printf("EEPROM %d, Read back: 0x%02X\r\n", i + 1, readData);
//	}



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

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
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SLAVE_C_Pin|SLAVE_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MAST_A_Pin|MAST_B_Pin|MAST_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SLAVE_A_GPIO_Port, SLAVE_A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SLAVE_C_Pin SLAVE_B_Pin */
  GPIO_InitStruct.Pin = SLAVE_C_Pin|SLAVE_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MAST_A_Pin MAST_B_Pin MAST_C_Pin */
  GPIO_InitStruct.Pin = MAST_A_Pin|MAST_B_Pin|MAST_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SLAVE_A_Pin */
  GPIO_InitStruct.Pin = SLAVE_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SLAVE_A_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EEPROM_CS_Pin */
  GPIO_InitStruct.Pin = EEPROM_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EEPROM_CS_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// Optional: if using `printf()` from stdio without semihosting
int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}
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
