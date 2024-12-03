/*
 * refill_function.h
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gpio.h"
#include "usart.h"

#ifndef INC_FUNCTION_REFILL_H_
#define INC_FUNCTION_REFILL_H_

int getThresh(uint32_t tare, float calFactor);

int refillDrawer(uint32_t tare, float calFactor);

#endif /* INC_FUNCTION_REFILL_H_ */
