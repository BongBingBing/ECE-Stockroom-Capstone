/*
 * Manager.c
 *
 *  Created on: Nov 18, 2024
 *      Author: andyb
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <usart.h>
#include <tim.h>


#include <function_refill.h>
#include <manager_file.h>
#include <manager_io.h>
#include <manager_mux.h>
#include <manager_weight.h>
#include <manager_relay.h>
#include <manager_EEPROM.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"



void main_function(){


	struct drawerInfo drawerInst;
	uint32_t tare = 0;
	float calFactor = 1;
	int thresh;
	uint8_t fileID = 0;
	uint8_t realID = 0;

	uint32_t sum;
	uint16_t normalizedWeight;

	for(uint16_t i = 1; i <= 4; i++){
			printf("Row %d", i);

			uint16_t A_mast = MuxCombos[i-1].A;
			uint16_t B_mast = MuxCombos[i-1].B;
			uint16_t C_mast = MuxCombos[i-1].C;

			muxSET(A_mast, B_mast, C_mast, 1);

			setRelay(i);

			if(i == 1){
				for(uint16_t j = 1; j <= 4; j++){

					sum = 0;
					normalizedWeight = 0;

					uint16_t A_slave = MuxCombos[j-1].A;
					uint16_t B_slave = MuxCombos[j-1].B;
					uint16_t C_slave = MuxCombos[j-1].C;

					muxSET(A_slave, B_slave, C_slave, 0);

					printf("Drawer %d\n", j);

					realID = 0;
					realID = EEPROM_ReadByte(0x00);

					drawerInst = getFileInfo(i, j, 0, 0);

					tare = drawerInst.Tare;
					calFactor = drawerInst.calFactor;
					thresh = drawerInst.thresh;
					fileID = drawerInst.ID;



					if(fileID != realID){
						printf("ID Mismatch, replacing drawer location...");

						struct drawerInfo tempInst;
						tempInst =  getFileInfo(i , j, realID, 1);

						uint32_t tempTare = tempInst.Tare;
						float tempCalFactor = tempInst.calFactor;
						int tempThresh = tempInst.thresh;
						uint8_t tempRow = tempInst.row;
						uint8_t tempDrawer = tempInst.drawer;

						updateDrawerConfig(i, j, tempCalFactor, tempTare, tempThresh, realID);

						updateDrawerConfig(tempRow, tempDrawer, calFactor, tare, thresh, fileID);

						tare = tempTare;
						calFactor = tempCalFactor;
						thresh = tempThresh;
						fileID = realID;



					}

					for(int p = 0; p < 4; p++){

						int weight = weigh(tare, calFactor);
						sum += weight;
						HAL_Delay(400);
					}

					normalizedWeight = sum / 4;

					if((thresh + 100) > normalizedWeight){

						thresh = refillDrawer(tare, calFactor);
						updateDrawerConfig(i, j, calFactor, tare, thresh, fileID);
					}



				}
			}
			else{
				for(int k = 1; k <= 7; k++){

					sum = 0;
					normalizedWeight = 0;

					uint16_t A_slave = MuxCombos[k-1].A;
					uint16_t B_slave = MuxCombos[k-1].B;
					uint16_t C_slave = MuxCombos[k-1].C;

					muxSET(A_slave, B_slave, C_slave, 0);

					printf("Drawer %d", k);

					realID = 0;
					realID = EEPROM_ReadByte(0x00);

					drawerInst = getFileInfo(i, k, realID, 0);

					tare = drawerInst.Tare;
					calFactor = drawerInst.calFactor;
					thresh = drawerInst.thresh;
					fileID = drawerInst.ID;

					if(fileID != realID){
							printf("ID Mismatch, replacing drawer location...");

							struct drawerInfo tempInst;
							tempInst =  getFileInfo(i , k, realID, 1);

							uint32_t tempTare = tempInst.Tare;
							float tempCalFactor = tempInst.calFactor;
							int tempThresh = tempInst.thresh;
							uint8_t tempRow = tempInst.row;
							uint8_t tempDrawer = tempInst.drawer;

							updateDrawerConfig(i, k, tempCalFactor, tempTare, tempThresh, realID);

							updateDrawerConfig(tempRow, tempDrawer, calFactor, tare, thresh, fileID);

							tare = tempTare;
							calFactor = tempCalFactor;
							thresh = tempThresh;
							fileID = realID;



					}

					for(int p = 0; p < 4; p++){

						int weight = weigh(tare, calFactor);
						sum += weight;
						HAL_Delay(400);
					}

					normalizedWeight = sum / 4;

					if((thresh + 100) > normalizedWeight){
						printf("This drawer is low on components\n\rPlease refill the drawer");
						printf("Press the selector button ONCE to continue\n\r");

						thresh = refillDrawer(tare, calFactor);
						updateDrawerConfig(i, k, calFactor, tare, thresh, fileID);
					}



				}
			}
	}

}
