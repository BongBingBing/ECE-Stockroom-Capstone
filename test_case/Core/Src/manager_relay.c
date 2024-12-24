/*
 * manager_relay.c
 *
 *  Created on: Dec 3, 2024
 *      Author: andyb
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <usart.h>
#include <tim.h>
#include <gpio.h>


#include <function_refill.h>
#include <manager_file.h>
#include <manager_io.h>
#include <manager_mux.h>
#include <manager_weight.h>


void setRelay(uint8_t rowNum){

	switch (rowNum){
		case 1:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);
			break;

		case 2:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);
			break;

		case 3:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);
			break;

		case 4:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);
			break;

		default:
			return;
	}
}
