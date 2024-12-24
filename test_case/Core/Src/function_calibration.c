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


#include <function_refill.h>
#include <manager_file.h>
#include <manager_io.h>
#include <manager_mux.h>
#include <manager_weight.h>
#include <manager_relay.h>


#define DT_PIN GPIO_PIN_8
#define DT_PORT GPIOA
#define SCK_PIN GPIO_PIN_5
#define SCK_PORT GPIOB

#define SELECT_PIN GPIO_PIN_2
#define RESET_PIN GPIO_PIN_1
#define BUTTON_PORT GPIOB


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
	float knownHX711 = 1;
	int thresh = 0;

	for(int i = 1; i <= 4; i++){
		printf("Row %d", i);

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

				printf("Drawer %d", j);
				tare = getTare();
				printf("Place the calibration weight on the drawer\n\rPress the button once when ready to calibrate\n\r");

				//single press confirmation here

				singlePress(BUTTON_PORT, SELECT_PIN);

				knownHX711 = weighRawTare(tare);
				printf("Read weight: %f", knownHX711);

				float calFactor = getCalFactor(knownHX711);

				for(int p = 0; p < 4; p++){
					int weight = weigh(tare, calFactor);
					printf("Weight: %d", weight);
					HAL_Delay(400);
				}

				thresh = refillDrawer(tare, calFactor);

				saveDrawerConfig(i, j, calFactor, tare, thresh);
			}
		}
		else{
			for(int k = 1; k <= 7; k++){

				uint16_t A_slave = MuxCombos[k-1].A;
				uint16_t B_slave = MuxCombos[k-1].B;
				uint16_t C_slave = MuxCombos[k-1].C;

				muxSET(A_slave, B_slave, C_slave, 0);

				printf("Drawer %d", k);
				tare = getTare();
				printf("Place the calibration weight on the drawer\n\rPress the button once when ready to calibrate\n\r");

				//single press confirmation here
				singlePress(BUTTON_PORT, SELECT_PIN);

				knownHX711 = weighRawTare(tare);
				printf("Read weight: %f", knownHX711);

				float calFactor = getCalFactor(knownHX711);

				for(int p = 0; p < 4; p++){
					int weight = weigh(tare, calFactor);
					printf("Weight: %d", weight);
					HAL_Delay(400);
				}

				int thresh = refillDrawer(tare, calFactor);

				saveDrawerConfig(i, k, calFactor, tare, thresh);

			}
		}
	}
}

