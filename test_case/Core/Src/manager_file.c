/*
 * file_manager.c
 *
 *  Created on: Nov 24, 2024
 *      Author: andyb
 */


/*
 *
 * Edited ff.c by changing ff_wtoupper -> toupper (line 1693)
 * Edited ff.c by changing ff_convert -> commented out (line 2646 + 2698)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gpio.h>
#include <usart.h>
#include <fatfs.h>

#include <ctype.h> //this is added for only toupper

#include <manager_file.h>


#define FILENAME_SIZE 512
#define MAX_FILELINE 1024

FATFS FatFs; 	//Fatfs handle
FIL fil, fil_temp; 		//File handle
FRESULT fres; //Result after operations
FRESULT fres_temp;

//SPI_HandleTypeDef hspi1;
//
//UART_HandleTypeDef huart2;

FILE *drawerConfig, *temp;

const char* filename = "drawerConfig.txt";
const char* temp_filename = "temp_drawerConfig.txt";

static char buffer[MAX_FILELINE];
BYTE previousLine[MAX_FILELINE];


void  SD_init(){
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		printf("f_mount error (%i)\r\n", fres);
		while(1);
	}

	//Let's get some statistics from the SD card
	DWORD free_clusters;

	FATFS* getFreeFs;

	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
		printf("f_getfree error (%i)\r\n", fres);
		while(1);
	}

}

void saveDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, uint32_t thresh){

	UINT bytesWrote;

	//f_unlink((TCHAR*)filename); //deletes the original file

	fres = f_open(&fil, filename, FA_WRITE | FA_OPEN_APPEND | FA_CREATE_NEW);

	if(fres == FR_EXIST){
				fres = f_open(&fil, filename, FA_WRITE | FA_OPEN_APPEND);
				if(fres != FR_OK){
					printf("f_write error (%i) IN saveDrawerConfig\r\n", fres);
					while(1);
				}
	}
	else if(fres == FR_OK){
		printf("Created new file");
	}
	else {
		printf("f_open error (%i) IN saveDrawerConfig\r\n", fres);
		while(1);
	}

	snprintf((char*)buffer, sizeof(buffer),"Row:%d;Drawer:%d;CalFactor:%f;Tare:%lu;Thresh:%ld\n", row, drawer, calFactor, Tare, thresh);
	fres = f_write(&fil, buffer, strlen(buffer), &bytesWrote);
	printf("Wrote %i bytes to %s\r\n", bytesWrote,filename);


	f_close(&fil);

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

	fres = f_open(&fil, filename, FA_READ);
	uint16_t fileIndex = 1;
	static char array[2];

	if (fres != FR_OK){
		printf("f_open error (%i) IN getLineMarker\r\n", fres);
		while(1);
	}
	else{
		TCHAR* rres = 0;
		do{
			rres = f_gets((TCHAR*)buffer, MAX_FILELINE, &fil);

			//char* fileLine = fgets(buffer, MAX_FILELINE, drawerConfig);
			char* token = strtok(rres, ";");

				for(uint16_t i = 0; i <= 1 ; i++){
					array[i] = getData(token);
				}

			if(row == array[0] && drawer == array[1]){
					return fileIndex;
			}
			else{
				fileIndex++;

			}
		}while(rres != 0);
	}
	f_close(&fil);
	return 0;
}

void updateDrawerConfig(uint16_t row, uint16_t drawer, float calFactor, uint32_t Tare, uint32_t thresh){ //will need to add ID marker and compare if they are the same, if not then change both locations

	fres = f_open(&fil, filename, FA_READ);
	fres_temp = f_open(&fil_temp, temp_filename, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres != FR_OK){
		printf("f_open error (%i) IN updateDrawerConfig FOR filename\r\n", fres);
		while(1);
	}
	if (fres_temp != FR_OK){
		printf("f_open error (%i) IN updateDrawerConfig FOR temp_filename\r\n", fres_temp);
		while(1);
	}

	UINT bytesWrote;

	bool keep_reading = true;
	uint16_t lineMarker = getLineMarker(row, drawer);
	uint16_t currentLine = 1;
	do{

		TCHAR* rres = f_gets((TCHAR*)buffer, MAX_FILELINE, &fil);

		if(rres == 0) keep_reading = false;
		else if(currentLine == lineMarker){ //ID matching would go here, check if IDs match, if not then save previous line, update line, then search for original location of ID and replace that line
			snprintf((char*)buffer, MAX_FILELINE, "Row:%d;Drawer:%d;CalFactor:%f;Tare:%lu;Thresh:%ld", row, drawer, calFactor, Tare, thresh);
			//fputs(buffer, temp);

			fres = f_write(&fil_temp, buffer, strlen(buffer), &bytesWrote);
			if(fres != FR_OK){
				printf("f_write error (%i) IN updateDrawerConfig(1)\r\n", fres);
				while(1);
			}

		}
		else {
			fres = f_write(&fil_temp, buffer, strlen(buffer), &bytesWrote);
			if(fres != FR_OK){
				printf("f_write error (%i) IN updateDrawerConfig(2)\r\n", fres);
				while(1);
			}
		}


		currentLine++;

	}while(keep_reading);

	f_close(&fil);
	f_close(&fil_temp);

	f_unlink((TCHAR*)filename); //deletes the original file
	f_rename((TCHAR*)temp_filename, (TCHAR*)filename); //rename the temp file to be the new "orginal" file


}


struct drawerInfo getFileInfo(uint16_t row, uint16_t drawer){ //add ID parameter here later

	struct drawerInfo drawerInst = { 0 };
	static unsigned int array[5];

	uint16_t lineMarker = getLineMarker(row, drawer);
	uint16_t fileIndex = 1;

	fres = f_open(&fil, filename, FA_READ);
	if (fres != FR_OK){
			printf("f_open error (%i) IN getFileInfo\r\n", fres);
			while(1);
		}
	else {
		TCHAR* rres = 0;
		do {

				rres = f_gets((TCHAR*) buffer, MAX_FILELINE, &fil);

				if (fileIndex == lineMarker) {
						char* token = strtok(buffer, ";");
						unsigned int index = 0;

						while (token != NULL) {
								array[index] = getData(token);
								token = strtok(NULL, ";");
								index++;
						}
						f_close(&fil);

						drawerInst.row = array[0];
						drawerInst.drawer = array[1];
						drawerInst.calFactor = array[2];
						drawerInst.Tare = array[3];
						drawerInst.thresh = array[4];

						return drawerInst;
				}
				fileIndex++;
		}while(rres != 0);
	}

	f_close(&fil);
	printf("An error occurred during info extraction.");
	return drawerInst;
}

