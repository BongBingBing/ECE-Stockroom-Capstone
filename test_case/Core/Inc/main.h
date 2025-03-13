/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SLAVE_C_Pin GPIO_PIN_0
#define SLAVE_C_GPIO_Port GPIOC
#define SLAVE_B_Pin GPIO_PIN_1
#define SLAVE_B_GPIO_Port GPIOC
#define MAST_A_Pin GPIO_PIN_0
#define MAST_A_GPIO_Port GPIOA
#define MAST_B_Pin GPIO_PIN_1
#define MAST_B_GPIO_Port GPIOA
#define MAST_C_Pin GPIO_PIN_4
#define MAST_C_GPIO_Port GPIOA
#define SLAVE_A_Pin GPIO_PIN_0
#define SLAVE_A_GPIO_Port GPIOB
#define RESET_BTN_Pin GPIO_PIN_1
#define RESET_BTN_GPIO_Port GPIOB
#define RESET_BTN_EXTI_IRQn EXTI1_IRQn
#define CONFIRM_BTN_Pin GPIO_PIN_2
#define CONFIRM_BTN_GPIO_Port GPIOB
#define CONFIRM_BTN_EXTI_IRQn EXTI2_IRQn
#define SCK_DRW_Pin GPIO_PIN_10
#define SCK_DRW_GPIO_Port GPIOB
#define DAT_IN_Pin GPIO_PIN_8
#define DAT_IN_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_15
#define SPI1_CS_GPIO_Port GPIOA
#define REL_1_Pin GPIO_PIN_10
#define REL_1_GPIO_Port GPIOC
#define REL_3_Pin GPIO_PIN_11
#define REL_3_GPIO_Port GPIOC
#define REL_2_Pin GPIO_PIN_12
#define REL_2_GPIO_Port GPIOC
#define REL_4_Pin GPIO_PIN_8
#define REL_4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define SD_SPI_HANDLE hspi1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
