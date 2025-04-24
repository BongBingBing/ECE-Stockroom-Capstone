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
	uint8_t ID;
};

void  SD_init();

void saveDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, uint32_t thresh, uint8_t ID);

void updateDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, uint32_t thresh, uint8_t ID);

uint32_t getData(char* token);

uint16_t getLineMarker(uint16_t row, uint16_t drawer);

struct drawerInfo getFileInfo(uint16_t row, uint16_t drawer, uint8_t ID, uint8_t control);

#endif /* INC_MANAGER_FILE_H_ */
