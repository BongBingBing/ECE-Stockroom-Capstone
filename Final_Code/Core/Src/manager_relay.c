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
#include <main.h> //all GPIO assignments found here


#include <function_refill.h>
#include <manager_file.h>
#include <manager_io.h>
#include <manager_mux.h>
#include <manager_weight.h>


void setRelay(uint8_t rowNum){

	switch (rowNum){
		case 1:
			HAL_GPIO_WritePin(REL_1_GPIO_Port, REL_1_Pin, 1);
			HAL_GPIO_WritePin(REL_2_GPIO_Port, REL_2_Pin, 0);
			HAL_GPIO_WritePin(REL_3_GPIO_Port, REL_3_Pin, 0);
			HAL_GPIO_WritePin(REL_4_GPIO_Port, REL_4_Pin, 0);
			break;

		case 2:
			HAL_GPIO_WritePin(REL_1_GPIO_Port, REL_1_Pin, 0);
			HAL_GPIO_WritePin(REL_2_GPIO_Port, REL_2_Pin, 1);
			HAL_GPIO_WritePin(REL_3_GPIO_Port, REL_3_Pin, 0);
			HAL_GPIO_WritePin(REL_4_GPIO_Port, REL_4_Pin, 0);
			break;

		case 3:
			HAL_GPIO_WritePin(REL_1_GPIO_Port, REL_1_Pin, 0);
			HAL_GPIO_WritePin(REL_2_GPIO_Port, REL_2_Pin, 0);
			HAL_GPIO_WritePin(REL_3_GPIO_Port, REL_3_Pin, 1);
			HAL_GPIO_WritePin(REL_4_GPIO_Port, REL_4_Pin, 0);
			break;

		case 4:
			HAL_GPIO_WritePin(REL_1_GPIO_Port, REL_1_Pin, 0);
			HAL_GPIO_WritePin(REL_2_GPIO_Port, REL_2_Pin, 0);
			HAL_GPIO_WritePin(REL_3_GPIO_Port, REL_3_Pin, 0);
			HAL_GPIO_WritePin(REL_4_GPIO_Port, REL_4_Pin, 1);
			break;

		default:
			return;
	}
}
