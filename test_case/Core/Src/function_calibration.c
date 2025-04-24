/*
 * Calibration_Manager.c
 *
 *  Created on: Nov 18, 2024
 *      Author: andyb
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <usart.h>
#include <tim.h>
#include <fatfs.h>



#include <function_refill.h>
#include <manager_file.h>
#include <manager_io.h>
#include <manager_mux.h>
#include <manager_weight.h>
#include <manager_relay.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "drawer_table.h"


int num = 2;
extern int row_num;
extern int drawer_num;

//TFT Print Variables
int tft_y = 0;
char tft_row[50];
char tft_drawer[50];
char tft_knownHX711[50];
char tft_weights[50];

uint32_t getTare(){
	char tft_weight_temp[50];
	char tft_attempt_num[50];

	printf("Remove all weight from the drawer(5 seconds)\n\r");
	HAL_Delay(5000);
	printf("Gathering initial Tare of Load Cell...\n\r");
	int weight_temp = 0;

	//TFT
	ILI9341_DrawText("Remove all weight from the drawer(5 seconds)", FONT4, 0, tft_y, WHITE, BLACK);
	tft_y +=20;
	HAL_Delay(5000);
	ILI9341_DrawText("Gathering initial Tare of Load Cell...", FONT4, 0, tft_y, WHITE, BLACK);
	tft_y +=20;
	HAL_Delay(3500);
	ILI9341_TopScreen(BLACK);

	for(uint16_t i = 1; i <= 4; i++){
			weight_temp = (int)weighRaw();
			printf("Tare attempt %d: %d\n\r", i, weight_temp);
			HAL_Delay(10);

			//TFT
			ILI9341_DrawText("Tare attempt ", FONT4, 0, tft_y, WHITE, BLACK);
			snprintf(tft_weight_temp, sizeof(tft_weight_temp), "%d", tft_weight_temp);
			ILI9341_DrawText(tft_weight_temp, FONT4, 50, tft_y, WHITE, BLACK);
			HAL_Delay(10);

		}
	printf("Tare Set: %d\n\r", weight_temp);
	return weight_temp;
}

void Calibrate(){
	printf("Beginning with Row: 1 Drawer: 1\n\r");
// TFT
	ILI9341_DrawText("Beginning with Row: 1 Drawer: 1", FONT4, 0, tft_y, WHITE, BLACK);
	tft_y +=20;

	uint32_t tare = 0;
	int knownHX711 = 1;
	uint32_t thresh = 0;

	FRESULT res = f_unlink("drwConf.txt"); //deletes the original file

	if(res == FR_OK){
		printf("Removed old 'drwConf.txt'\n\r");
	}
	f_unlink("temp_drawerConfig.txt"); //deletes the original file


	for(int i = 2; i <= 4; i++){

		uint16_t A_mast = MuxCombos[i-1].A;
		uint16_t B_mast = MuxCombos[i-1].B;
		uint16_t C_mast = MuxCombos[i-1].C;

		muxSET(A_mast, B_mast, C_mast, 1);

		setRelay(i);

		if(i == 1){
			for(int j = 1; j <= 4; j++){

				uint16_t A_slave = MuxCombos[j-1].A;
				uint16_t B_slave = MuxCombos[j-1].B;
				uint16_t C_slave = MuxCombos[j-1].C;

				muxSET(A_slave, B_slave, C_slave, 0);

				printf("ROW %d | DRAWER %d\n\r", i, j);

				//TFT
				snprintf(tft_row, sizeof(tft_row), "%d", i);
				ILI9341_DrawText("ROW ", FONT4, 0, tft_y, WHITE, BLACK);
				ILI9341_DrawText(tft_row, FONT4, 55, tft_y, WHITE, BLACK);
				snprintf(tft_drawer, sizeof(tft_drawer), "%d", i);
				ILI9341_DrawText(" | DRAWER ",FONT4, 60, tft_y, WHITE, BLACK);
				ILI9341_DrawText(tft_drawer, FONT4, 175, tft_y, WHITE, BLACK);
				tft_y +=20;
				HAL_Delay(2000);
				ILI9341_TopScreen(BLACK);

				tare = getTare();
				printf("Place the calibration weight on the drawer\n\rPress the button once when ready to calibrate\n\r");

				//TFT
				ILI9341_DrawText("Place the calibration weight", FONT4, 0, tft_y, WHITE, BLACK);
				tft_y +=20;
				ILI9341_DrawText("on the drawer", FONT4, 0, tft_y, WHITE, BLACK);
				tft_y +=20;
				ILI9341_DrawText("Press the button once ", FONT4, 0, tft_y, WHITE, BLACK);
				tft_y +=20;
				ILI9341_DrawText("when ready to calibrate ", FONT4, 0, tft_y, WHITE, BLACK);
				drawer_lookup(i,j,'B');
				 row_num = i;
				 drawer_num = j;

				 //double press confirmation here
				button_output(num);

				knownHX711 = weighRawTare(tare);
				printf("Read weight: %d\n\r", knownHX711);

				//TFT
				HAL_Delay(2000);
				ILI9341_TopScreen(BLACK);
				ILI9341_DrawText("Read weight: ",FONT4, 0, tft_y, WHITE, BLACK);
				snprintf(tft_knownHX711, sizeof(tft_knownHX711), "%d", knownHX711);
				ILI9341_DrawText(tft_knownHX711,FONT4, 115, tft_y, WHITE, BLACK);
				HAL_Delay(3000);
				ILI9341_TopScreen(BLACK);

				float calFactor = getCalFactor(knownHX711);

				for(int p = 0; p < 4; p++){
					int weight = weigh(tare, calFactor);
					printf("Weight: %d\n\r", weight);
					HAL_Delay(400);
					//TFT
					snprintf(tft_weights, sizeof(tft_weights), "%d", weight);
					ILI9341_DrawText("Weight: ",FONT4, 0, tft_y, WHITE, BLACK);
					ILI9341_DrawText(tft_weights,FONT4, 65, tft_y, WHITE, BLACK);
					tft_y +=20;
					HAL_Delay(400);
				}

				thresh = refillDrawer(tare, calFactor);

				SD_init();

				saveDrawerConfig(i, j, calFactor, tare, thresh);
			}
		}

		else{
			for(int k = 7; k <= 7; k++){

				uint16_t A_slave = MuxCombos[k-1].A;
				uint16_t B_slave = MuxCombos[k-1].B;
				uint16_t C_slave = MuxCombos[k-1].C;

				muxSET(A_slave, B_slave, C_slave, 0);

				printf("ROW %d | DRAWER %d\n\r", i, k);

				//TFT
				snprintf(tft_row, sizeof(tft_row), "%d", i);
				ILI9341_DrawText("ROW ", FONT4, 0, tft_y, WHITE, BLACK);
				ILI9341_DrawText(tft_row, FONT4, 55, tft_y, WHITE, BLACK);
				snprintf(tft_drawer, sizeof(tft_drawer), "%d", i);
				ILI9341_DrawText(" | DRAWER ",FONT4, 60, tft_y, WHITE, BLACK);
				ILI9341_DrawText(tft_drawer, FONT4, 175, tft_y, WHITE, BLACK);
				tft_y +=20;
				HAL_Delay(2000);
				ILI9341_TopScreen(BLACK);

				tare = getTare();
				printf("Place the calibration weight on the drawer\n\rPress the button twice when ready to calibrate\n\r");

				//TFT
				ILI9341_DrawText("Place the calibration weight", FONT4, 0, tft_y, WHITE, BLACK);
				tft_y +=20;
				ILI9341_DrawText("on the drawer", FONT4, 0, tft_y, WHITE, BLACK);
				tft_y +=20;
				ILI9341_DrawText("Press the button once ", FONT4, 0, tft_y, WHITE, BLACK);
				tft_y +=20;
				ILI9341_DrawText("when ready to calibrate ", FONT4, 0, tft_y, WHITE, BLACK);

				//double press confirmation here
				button_output(num);


				knownHX711 = weighRawTare(tare);
				printf("Read weight: %d\n\r", knownHX711);

				//TFT
				HAL_Delay(2000);
				ILI9341_TopScreen(BLACK);
				ILI9341_DrawText("Read weight: ",FONT4, 0, tft_y, WHITE, BLACK);
				snprintf(tft_knownHX711, sizeof(tft_knownHX711), "%d", knownHX711);
				ILI9341_DrawText(tft_knownHX711,FONT4, 115, tft_y, WHITE, BLACK);
				HAL_Delay(3000);
				ILI9341_TopScreen(BLACK);

				float calFactor = getCalFactor(knownHX711);

				for(int p = 0; p < 4; p++){
					int weight = weigh(tare, calFactor);
					printf("Weight: %d\n\r", weight);
					HAL_Delay(400);

					//TFT
					snprintf(tft_weights, sizeof(tft_weights), "%d", weight);
					ILI9341_DrawText("Weight: ",FONT4, 0, tft_y, WHITE, BLACK);
					ILI9341_DrawText(tft_weights,FONT4, 65, tft_y, WHITE, BLACK);
					tft_y +=20;
					HAL_Delay(400);
				}

				thresh = refillDrawer(tare, calFactor);

				SD_init();

				saveDrawerConfig(i, k, calFactor, tare, thresh);

			}
		}
	}
}

