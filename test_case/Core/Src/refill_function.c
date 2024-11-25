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
	float avg = 0;

	for(uint16_t i = 0; i < 4; i++){
		uint16_t weight = weigh(tare, calFactor);
		avg += weight;
	}

	avg = avg / 4.0;

	return (avg * 0.1); //returns 10% of the normalized weight as the threshold

}

