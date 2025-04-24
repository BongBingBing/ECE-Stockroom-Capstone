/*
 * muxManager.c
 *
 *  Created on: Nov 18, 2024
 *      Author: andyb
 */

//#include <main.h>
#include <manager_mux.h>
#include <stdbool.h>
#include "stdio.h"
#include <gpio.h>

//#define MAST_A_Pin GPIO_PIN_7
//#define MAST_A_GPIO_Port GPIOB
//#define MAST_B_Pin GPIO_PIN_13
//#define MAST_B_GPIO_Port GPIOC
//#define MAST_C_Pin GPIO_PIN_14
//#define MAST_C_GPIO_Port GPIOC

//#define SLAVE_A_Pin GPIO_PIN_4
//#define SLAVE_A_GPIO_Port GPIOB
//#define SLAVE_B_Pin GPIO_PIN_5
//#define SLAVE_B_GPIO_Port GPIOB
//#define SLAVE_C_Pin GPIO_PIN_3
//#define SLAVE_C_GPIO_Port GPIOB

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
