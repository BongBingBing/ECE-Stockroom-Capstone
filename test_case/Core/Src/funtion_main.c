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



void main_function(){


	struct drawerInfo drawerInst;
	uint32_t tare = 0;
	float calFactor = 1;
	int thresh;

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

					uint16_t A_slave = MuxCombos[k-1].A;
					uint16_t B_slave = MuxCombos[k-1].B;
					uint16_t C_slave = MuxCombos[k-1].C;

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
