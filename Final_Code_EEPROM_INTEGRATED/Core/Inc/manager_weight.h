/*
 * Weight_Manager.h
 *
 *  Created on: Nov 19, 2024
 *      Author: andyb
 */
#include <stdbool.h>
#include "stdio.h"
#include "gpio.h"


#ifndef INC_WEIGHT_MANAGER_H_
#define INC_WEIGHT_MANAGER_H_


void microDelay(uint16_t delay);

int32_t getHX711(void);

int weigh(uint32_t tare, float knownHX711);

int32_t weighRaw();

int32_t weighRawTare(uint32_t tare);

float getCalFactor(uint32_t knownHX711);

#endif /* INC_WEIGHT_MANAGER_H_ */
