/*
 * drawer_table.c
 *
 *  Created on: Mar 22, 2025
 *      Author: Joel
 */

#include "drawer_table.h"
#include <stdio.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "stm32f4xx_hal.h"
#include "fonts.h"

/*
 * ROW 1: (202.525,108.125),(234.725,108.125),(266.825,108.125),(298.975,108.125)
 * ROW 2: (106.075,144.375),(138.225,144.375),(170.375,144.375),(202.525,144.375),(234.725,144.375),(266.825,144.375),(298.975,144.375)
 * ROW 3: (106.075,180.625),(138.225,180.625),(170.375,180.625),(202.525,180.625),(234.725,180.625),(266.825,180.625),(298.975,180.625)
 * ROW 4: (106.075,216.875),(138.225,216.875),(170.375,216.875),(202.525,216.875),(234.725,216.875),(266.825,216.875),(298.975,216.875)
 *
 * */

//LCD COORDINATES

double LCD_X;
double LCD_Y;


typedef struct {
	double x;
	double y;
} Coordinates;


typedef struct {
	Coordinates coord[7];
} Location;


typedef struct {
	const char *key;
	Location info;
} Dictonary;


const Dictonary dict[4] = {

//{ "stationA", {.coords = { {0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0} },.count = 3 }},
		{"ROW 1", {.coord = {{202.525,108.125},{234.725,108.125},{266.825,108.125},{298.975,108.125}} } },

		{"ROW 2", {.coord = {{106.075,144.375},{138.225,144.375},{170.375,144.375},{202.525,144.375},{234.725,144.375},{266.825,144.375},{298.975,144.375}} } },

		{"ROW 3", {.coord = {{106.075,180.625},{138.225,180.625},{170.375,180.625},{202.525,180.625},{234.725,180.625},{266.825,180.625},{298.975,180.625}} } },

		{"ROW 4", {.coord = {{106.075,216.875},{138.225,216.875},{170.375,216.875},{202.525,216.875},{234.725,216.875},{266.825,216.875},{298.975,216.875}} } }

};


const Location* find_coord(const char *key){
	for (int i = 0; i < 4; i++){
		if (strcmp(dict[i].key, key) == 0)
			return &dict[i].info;
	}
	return 0;
}


/**/
void drawer_lookup(uint16_t rows, uint16_t drawer, char colors){
	//printf("%d\n\r", rows);
	//printf("%d\n\r", drawer);
	switch (rows){
		case 1:
			const Location *info = find_coord("ROW 1");
			if (info != NULL){
				for (int i = 0; i < 4; i++){
					if (i == (drawer - 1)){
						LCD_X = info->coord[i].x;
						LCD_Y = info->coord[i].y;
						//printf("X: %lf\n\r", LCD_X);
						//printf("Y: %lf\n\r", LCD_Y);
						break;
					}
				}
				if (colors == 'B')
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,BLUE);
				else if (colors == 'R'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,RED);
				}
				else if (colors == 'W'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,WHITE);
				}
			}
			break;

	 	case 2:
			const Location *info_sec = find_coord("ROW 2");
			if (info_sec != NULL){
				for (int i = 0; i < 7; i++){
					if (i == (drawer - 1)){
						LCD_X = info_sec->coord[i].x;
						LCD_Y = info_sec->coord[i].y;
						break;
					}
				}
				if (colors == 'B')
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,BLUE);
				else if (colors == 'R'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,RED);
				}
				else if (colors == 'W'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,WHITE);
				}
			}
			break;

		case 3:
			const Location *info_th = find_coord("ROW 3");
			if (info_th != NULL){
				for (int i = 0; i < 7; i++){
					if (i == (drawer - 1)){
						LCD_X = info_th->coord[i].x;
						LCD_Y = info_th->coord[i].y;
						break;
					}
				}
				if (colors == 'B')
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,BLUE);
				else if (colors == 'R'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,RED);
				}
				else if (colors == 'W'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,WHITE);
				}
			}
			break;

		case 4:
			const Location *info_f = find_coord("ROW 4");
			if (info_f != NULL){
				for (int i = 0; i < 7; i++){
					if (i == (drawer - 1)){
						LCD_X = info_f->coord[i].x;
						LCD_Y = info_f->coord[i].y;
						break;
					}
				}
				if (colors == 'B')
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,BLUE);
				else if (colors == 'R'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,RED);
				}
				else if (colors == 'W'){
					ILI9341_DrawFilledCircle(LCD_X, LCD_Y,5,WHITE);
				}
			}
			break;
			/**/
	}
}


void drawer_table() {

	 // ILI9341_Init();

	  int columns = 90;
	  int rows = 90;

	  double circlex = 106.075;
	  double circley = 108.125;

	  // Hollow Rectangle (Start X, Start Y, End X, End Y)
	  ILI9341_FillScreen(BLACK);
	  ILI9341_DrawHollowRectangleCoord(90, 90, 315, 235, WHITE);
	  HAL_Delay(2000);


	  // creating the seven columns
	  for (int i = 0; i <= 5; i++){
		  columns += 32.15;
		  if ( i < 2){
			 // Vertical Line (X, Y, Length, Color)
			  ILI9341_DrawVLine(columns, 126.25, 108.75, WHITE);
			  HAL_Delay(1000);
		  }
		  else {
			 // Vertical Line (X, Y, Length, Color)
			  ILI9341_DrawVLine(columns, 90, 145, WHITE);
			  HAL_Delay(1000);
		  }

	  }

	  // creating the four rows
	  for (int i = 0; i <= 2; i++){
		  rows += 36.25;
	     // Horizontal Line (X, Y, Length, Color)
		  ILI9341_DrawHLine(90, rows, 225, WHITE);
		  HAL_Delay(1000);

	  }

	  // Filling in each slot of the table shown on the screen
	      for (int i = 1; i <= 4; i++){
	    	  if ( i == 1){
	    		  // we use this value since the first row has less drawers
	    		  int row1x = 202.575;
	    		  for (int j = 1; j <= 4; j++){
	    			 ILI9341_DrawFilledCircle(row1x, circley, 5, WHITE);
	    			 HAL_Delay(500);
	    			 row1x += 32.15;
	    		  }
	    	  }

	    	  else  {
	    		  for (int j = 1; j <= 7; j++){
		    		  ILI9341_DrawFilledCircle(circlex, circley, 5, WHITE);
		    		  HAL_Delay(500);
		    		  circlex += 32.15;
	    		  }

	    	  }

    		  circley += 36.25;
    		  circlex = 106.075;

	      }


}
