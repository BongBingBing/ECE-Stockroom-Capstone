/*
 * file_manager.c
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

#include <file_manager.h>

#define FILENAME_SIZE 512
#define MAX_FILELINE 1024

FILE *drawerConfig, *temp;

const char filename[FILENAME_SIZE] = "drawerConfig.txt";
const char temp_filename[FILENAME_SIZE] = "temp.txt";

char buffer[MAX_FILELINE];
char previousLine[MAX_FILELINE];

void saveDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, float thresh){


	drawerConfig = fopen(filename, "w");
	if (drawerConfig == NULL){
		printf("Could not open file\n\r");
	}
	else{
		snprintf(buffer, sizeof(buffer),"Row:%d;Drawer:%d;CalFactor:%f;Tare:%lu;Thresh:%f", row, drawer, calFactor, Tare, thresh);
		fputs(buffer, drawerConfig);
	}
}

void updateDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, float thresh){ //will need to add ID marker and compare if they are the same, if not then change both locations

	drawerConfig = fopen(filename, "r");
	temp = fopen(temp_filename, "w");

	bool keep_reading = true;
	uint16_t lineMarker = getLineMarker(row, drawer);
	uint16_t currentLine = 1;
	do{

		fgets(buffer, MAX_FILELINE, drawerConfig);

		if(feof(drawerConfig)) keep_reading = false;
		else if(currentLine == lineMarker){ //ID matching would go here, check if IDs match, if not then save previous line, update line, then search for original location of ID and replace that line
			snprintf(buffer, sizeof(buffer), "Row:%d;Drawer:%d;CalFactor:%f;Tare:%lu;Thresh:%f", row, drawer, calFactor, Tare, thresh);
			fputs(buffer, temp);
		}
		else fputs(buffer, temp);

		currentLine++;

	}while(keep_reading);

	fclose(drawerConfig);
	fclose(temp);

	remove(filename);
	rename(temp_filename, filename);


}

uint32_t getData(char* token){
	for(uint16_t i = 0; i <= 1; i++){
		char* temp_token = strtok(token, ":");
		if(i == 1){

			return strtol(temp_token, NULL, 10);
		}
	}
	return 0;
}

uint16_t getLineMarker(uint16_t row, uint16_t drawer){
	drawerConfig = fopen(filename, "r");
	uint16_t fileIndex = 1;
	static char array[2];

	if (drawerConfig == NULL){
		printf("Could not open file\n\r");
	}
	else{

		while(fgets(buffer, MAX_FILELINE, drawerConfig)){

			char* fileLine = fgets(buffer, MAX_FILELINE, drawerConfig);
			char* token = strtok(fileLine, ";");

				for(uint16_t i = 0; i <= 1 ; i++){
					array[i] = getData(token);
				}

			if(row == array[0] && drawer == array[1]){
					return fileIndex;
			}
			else{
				fileIndex++;

			}
		}
	}
	return 0;
}

struct drawerInfo getFileInfo(uint16_t row, uint16_t drawer){ //add ID parameter here later

	struct drawerInfo drawerInst = { 0 };
	static unsigned int array[5];

	uint16_t lineMarker = getLineMarker(row, drawer);
	uint16_t fileIndex = 1;

	drawerConfig = fopen(filename, "r");
	if (drawerConfig == NULL) {
	        printf("Could not open file\n\r");
	        return drawerInst; // Error case
	}
	else {
		while (fgets(buffer, MAX_FILELINE, drawerConfig)) {
				fgets(buffer, MAX_FILELINE, drawerConfig);

				if (fileIndex == lineMarker) {
						char* token = strtok(buffer, ";");
						unsigned int index = 0;

						while (token != NULL) {
								array[index] = getData(token);
								token = strtok(NULL, ";");
								index++;
						}
						fclose(drawerConfig);

						drawerInst.row = array[0];
						drawerInst.drawer = array[1];
						drawerInst.calFactor = array[2];
						drawerInst.Tare = array[3];
						drawerInst.thresh = array[4];

						return drawerInst;
				}
				fileIndex++;
		}
	}

	fclose(drawerConfig);
	printf("An error occurred during info extraction.");
	return drawerInst;
}

