/*
 * file_manager.h
 *
 *  Created on: Nov 24, 2024
 *      Author: andyb
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gpio.h"
#include "usart.h"

#ifndef INC_MANAGER_FILE_H_
#define INC_MANAGER_FILE_H_

struct drawerInfo{
	uint16_t row;
	uint16_t drawer;
	float calFactor;
	uint32_t Tare;
	float thresh;
};

void  SD_init();

void saveDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, uint32_t thresh);

void updateDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, uint32_t thresh);

uint32_t getData(char* token);

uint16_t getLineMarker(uint16_t row, uint16_t drawer);

struct drawerInfo getFileInfo(uint16_t row, uint16_t drawer);

#endif /* INC_MANAGER_FILE_H_ */
