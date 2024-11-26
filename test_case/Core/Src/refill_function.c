/*
 * refill_function.c
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <usart.h>
#include <tim.h>

#include <weight_manager.h>
#include <mux_manager.h>
#include <io_manager.h>
#include <file_manager.h>

#define GROUP GPIOA
#define PIN GPIO_PIN_10


GPIO_PinState last_state = GPIO_PIN_RESET;

uint32_t DP_Threshold = 2000; // 2 second threshold
uint32_t press_time = 0;  // Timestamp of the first press
uint8_t press_count = 0;  // A Flag that's used for indicating a second press

int getThresh(uint32_t tare, float calFactor){
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
	printf("Please refill the current drawer\n\rPress the button twice when ready\n\r");

	//function to wait for a double press then a confirmation press
	doublePress(GROUP, PIN);

	int thresh = getThresh(tare, calFactor);
	printf("Threshold set to %d", thresh);
	return thresh;


}
