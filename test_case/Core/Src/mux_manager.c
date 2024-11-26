/*
 * muxManager.c
 *
 *  Created on: Nov 18, 2024
 *      Author: andyb
 */


#include <mux_manager.h>
#include <stdbool.h>
#include "stdio.h"
#include "gpio.h"


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
