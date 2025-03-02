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



int num = 2;

uint32_t getTare(){
	printf("Remove all weight from the drawer(5 seconds)\n\r");
	HAL_Delay(5000);
	printf("Gathering initial Tare of Load Cell...\n\r");
	int weight_temp = 0;

	for(uint16_t i = 1; i <= 4; i++){
			weight_temp = (int)weighRaw();
			printf("Tare attempt %d: %d\n\r", i, weight_temp);
			HAL_Delay(10);
		}
	printf("Tare Set: %d\n\r", weight_temp);
	return weight_temp;
}

void Calibrate(){
	printf("Beginning with Row: 1 Drawer: 1\n\r");

	uint32_t tare = 0;
	int knownHX711 = 1;
	uint32_t thresh = 0;

	f_unlink("drawerConfig.txt"); //deletes the original file
	f_unlink("temp_drawerConfig.txt"); //deletes the original file


	for(int i = 1; i <= 4; i++){

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
				tare = getTare();
				printf("Place the calibration weight on the drawer\n\rPress the button twice when ready to calibrate\n\r");

				//double press confirmation here
						button_output(num);


				knownHX711 = weighRawTare(tare);
				printf("Read weight: %d\n\r", knownHX711);

				float calFactor = getCalFactor(knownHX711);

				for(int p = 0; p < 4; p++){
					int weight = weigh(tare, calFactor);
					printf("Weight: %d\n\r", weight);
					HAL_Delay(400);
				}

				thresh = refillDrawer(tare, calFactor);

				SD_init();

				saveDrawerConfig(i, j, calFactor, tare, thresh);
			}
		}
		else{
			for(int k = 1; k <= 7; k++){

				uint16_t A_slave = MuxCombos[k-1].A;
				uint16_t B_slave = MuxCombos[k-1].B;
				uint16_t C_slave = MuxCombos[k-1].C;

				muxSET(A_slave, B_slave, C_slave, 0);

				printf("ROW %d | DRAWER %d\n\r", i, k);
				tare = getTare();
				printf("Place the calibration weight on the drawer\n\rPress the button twice when ready to calibrate\n\r");

				//double press confirmation here
				button_output(num);


				knownHX711 = weighRawTare(tare);
				printf("Read weight: %d\n\r", knownHX711);

				float calFactor = getCalFactor(knownHX711);

				for(int p = 0; p < 4; p++){
					int weight = weigh(tare, calFactor);
					printf("Weight: %d\n\r", weight);
					HAL_Delay(400);
				}

				thresh = refillDrawer(tare, calFactor);

				SD_init();

				saveDrawerConfig(i, k, calFactor, tare, thresh);

			}
		}
	}
}

