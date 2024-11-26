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

#include <weight_manager.h>
#include <mux_manager.h>
#include <io_manager.h>
#include <file_manager.h>

#include <refill_function.h>


#define DT_PIN GPIO_PIN_8
#define DT_PORT GPIOA
#define SCK_PIN GPIO_PIN_5
#define SCK_PORT GPIOB

void main_function(){


	struct drawerInfo drawerInst;
	uint32_t tare = 0;
	float calFactor = 1;
	int thresh;

	uint32_t sum;
	uint16_t normalizedWeight;

	for(uint16_t i = 1; i <= 4; i++){
			printf("Row %d", i);

			uint16_t A_mast = MuxCombos[i].A;
			uint16_t B_mast = MuxCombos[i].B;
			uint16_t C_mast = MuxCombos[i].C;

			muxSET(A_mast, B_mast, C_mast, 1);

			if(i == 1){
				for(uint16_t j = 1; j <= 4; j++){

					sum = 0;
					normalizedWeight = 0;

					uint16_t A_slave = MuxCombos[j].A;
					uint16_t B_slave = MuxCombos[j].B;
					uint16_t C_slave = MuxCombos[j].C;

					muxSET(A_slave, B_slave, C_slave, 0);

					printf("Drawer %d", j);

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
						printf("This drawer is low on components\n\rPlease refill the drawer");
						printf("Press the selector button ONCE to continue\n\r");

						thresh = refillDrawer(tare, calFactor);
						updateDrawerConfig(i, j, calFactor, tare, thresh);
					}



				}
			}
			else{
				for(int k = 1; k <= 7; k++){

					sum = 0;
					normalizedWeight = 0;

					uint16_t A_slave = MuxCombos[k].A;
					uint16_t B_slave = MuxCombos[k].B;
					uint16_t C_slave = MuxCombos[k].C;

					muxSET(A_slave, B_slave, C_slave, 0);

					printf("Drawer %d", k);

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
						printf("This drawer is low on components\n\rPlease refill the drawer");
						printf("Press the selector button ONCE to continue\n\r");

						thresh = refillDrawer(tare, calFactor);
						updateDrawerConfig(i, k, calFactor, tare, thresh);
					}



				}
			}
	}

}
