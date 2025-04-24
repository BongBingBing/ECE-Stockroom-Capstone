/*
 * refill_function.c
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#include <manager_file.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <usart.h>
#include <tim.h>
#include <main.h> //all GPIO assignments found here

#include <manager_io.h>
#include <manager_mux.h>
#include <manager_weight.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "drawer_table.h"


GPIO_PinState last_state = GPIO_PIN_RESET;

uint32_t DP_Threshold = 2000; // 2 second threshold
uint32_t press_time = 0;  // Timestamp of the first press
uint8_t press_count = 0;  // A Flag that's used for indicating a second press

//int row_num;
//int drawer_num;

extern int row_num;
extern int drawer_num;

int num2 = 2;

uint32_t getThresh(uint32_t tare, float calFactor){
	uint32_t sum = 0;
	float avg = 0;

	for(uint16_t i = 0; i < 4; i++){
		uint16_t weight = weigh(tare, calFactor);
		sum += weight;
	}

	avg = sum / 4.0;

	return (avg * 0.1); //returns 10% of the normalized weight as the threshold

}



int refillDrawer(uint32_t tare, float calFactor){
	printf("Please refill the current drawer\n\rPress and Hold the button when ready\n\r");
	drawer_lookup(row_num,drawer_num,'R');
	//function to wait for a double press then a confirmation press
	button_output(num2);

	//doublePress(CONFIRM_BTN_GPIO_Port, CONFIRM_BTN_Pin);

	uint32_t thresh = getThresh(tare, calFactor);
	printf("Threshold set to %ld\n\r", thresh);
	//drawer_lookup(row_num,drawer_num,'W');
	return thresh;


}
