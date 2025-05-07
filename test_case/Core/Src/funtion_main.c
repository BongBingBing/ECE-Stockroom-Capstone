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
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "drawer_table.h"

extern int row_num;
extern int drawer_num;
int selector_button = 2;

//TFT Code
extern int tft_y;
extern char tft_row[50];
extern char tft_drawer[50];
extern char tft_knownHX711[50];
extern char tft_weights[50];

void main_function(){


	struct drawerInfo drawerInst;
	uint32_t tare = 0;
	float calFactor = 1;
	int thresh;

	uint32_t sum;
	uint16_t normalizedWeight;

	for(uint16_t i = 1; i <= 4; i++){
			printf("Row %d ", i);

			//TFT
			ILI9341_DrawText("ROW ", FONT4, 0, tft_y, WHITE, BLACK);
			snprintf(tft_row, sizeof(tft_drawer), "%d", i);
			ILI9341_DrawText(tft_row, FONT4, 55, tft_y, WHITE, BLACK);

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

					printf("Drawer %d\n\r", j);

					//TFT
					snprintf(tft_drawer, sizeof(tft_drawer), "%d", j);
					ILI9341_DrawText(" DRAWER ",FONT4, 60, tft_y, WHITE, BLACK);
					ILI9341_DrawText(tft_drawer, FONT4, 175, tft_y, WHITE, BLACK);

					drawerInst = getFileInfo(i, j);

					tare = drawerInst.Tare;
					calFactor = drawerInst.calFactor;
					thresh = drawerInst.thresh;

					for(int p = 0; p < 4; p++){

						int weight = weigh(tare, calFactor);
						sum += weight;
						HAL_Delay(400);
					}

					normalizedWeight = sum / 4;

					if((thresh + 100) > normalizedWeight){
						//LCD CODE
								 row_num = i;
								 drawer_num = j;
								//drawer_lookup(i,j,'W');
						thresh = refillDrawer(tare, calFactor);
						updateDrawerConfig(i, j, calFactor, tare, thresh);
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

					printf("Drawer %d\n\r", k);

					drawerInst = getFileInfo(i, k);

					tare = drawerInst.Tare;
					calFactor = drawerInst.calFactor;
					thresh = drawerInst.thresh;

					for(int p = 0; p < 4; p++){

						int weight = weigh(tare, calFactor);
						sum += weight;
						HAL_Delay(400);
					}

					normalizedWeight = sum / 4;

					if((thresh + 100) > normalizedWeight){
						printf("This drawer is low on components\n\rPlease refill the drawer\n\r");
						printf("Press the selector button ONCE to continue\n\r");

						//TFT
						ILI9341_TopScreen(BLACK);
						ILI9341_DrawText("This drawer is low on components", FONT4, 0, tft_y, WHITE, BLACK);
						tft_y +=20;
						ILI9341_DrawText("Please refill the drawer", FONT4, 0, tft_y, WHITE, BLACK);
						tft_y +=20;
						ILI9341_DrawText("Press the selector button", FONT4, 0, tft_y, WHITE, BLACK);
						tft_y +=20;
						ILI9341_DrawText("ONCE to continue", FONT4, 0, tft_y, WHITE, BLACK);

						button_output(selector_button);
						//LCD CODE
						 row_num = i;
						 drawer_num = k;

						thresh = refillDrawer(tare, calFactor);
						updateDrawerConfig(i, k, calFactor, tare, thresh);
					}



				}
			}
	}

}
