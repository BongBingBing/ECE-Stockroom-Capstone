/*
 * file_manager.h
 *
 *  Created on: Nov 24, 2024
 *      Author: andyb
 */

#ifndef INC_FILE_MANAGER_H_
#define INC_FILE_MANAGER_H_

struct drawerInfo{
	uint16_t row;
	uint16_t drawer;
	float calFactor;
	uint32_t Tare;
	float thresh;
};


void saveDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, float thresh);

void updateDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, float thresh);

uint32_t getData(char* token);

uint16_t getLineMarker(uint16_t row, uint16_t drawer);

struct drawerInfo getFileInfo(uint16_t row, uint16_t drawer);

#endif /* INC_FILE_MANAGER_H_ */
