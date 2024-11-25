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


float getThresh(uint32_t tare, float calFactor){
	uint32_t sum = 0;
	float avg = 0;

	for(uint16_t i = 0; i < 4; i++){
		uint16_t weight = weigh(tare, calFactor);
		sum += weight;
	}

	avg = sum / 4.0;

	return (avg * 0.1); //returns 10% of the normalized weight as the threshold

}

float refillDrawer(uint32_t tare, float calFactor){
	printf("Please refill the current drawer\n\rPress the button twice when ready\n\r");

	//function to wait for a double press then a confirmation press

	while(pressFlag){
		//detect double press and then set looping flag to false

	}

	return getThresh(tare, calFactor);


}
