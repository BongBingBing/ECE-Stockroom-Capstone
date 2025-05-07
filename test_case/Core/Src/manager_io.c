/*
 * io_manager.c
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#include "stdio.h"
#include "usart.h"
#include <stdbool.h>
#include "tim.h"
#include "gpio.h"
#include <manager_io.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

//extern int tft_y;
//Code to enable printf statements
int _write(int file, char *data, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)data, len, HAL_MAX_DELAY); // Replace &huart2 with your UART instance
    return len;
}

//Code to enable scanf statements
GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;

  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart2);

  /* Wait for reception of a character on the USART RX line and echo this
   * character on console */
  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

// Global Variables
enum press_type {     IDLE,
    PRESS_DETECTED,
    WAIT_RELEASE,
   // LONG_PRESS,
    TIME_WINDOW_END };
volatile enum press_type button_press;

// button states flags
int LP_flag = 0; // Long Press Flag
int input_type; // Reads For Three Different Button Inputs

int count = 0; // counts button presses
volatile int timer_active = 0; // flag timer
volatile unsigned int time_start;  // Timestamp of the button press
unsigned int released_time; // Timestamp of the button released

volatile bool reset_confirm_window_active = false; // checks if reset button was pressed
volatile uint32_t reset_button_time_start = 0; // tracks the time when the reset button was pressed

// tracks which button is read and what state it is in
int num_button = 0;
volatile uint8_t previous_button_state = 0;

#define NVIC_RESET_KEY 0x5FA0000

// TFT
extern int tft_y;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

    //uint32_t current_time = HAL_GetTick();
	// D7
	/**/if (GPIO_Pin == RESET_BTN_Pin) {
		//printf("Reset button Pressed");
		num_button = 1;

	    HAL_NVIC_DisableIRQ(EXTI1_IRQn); // assuming EXTI1 used for RESET
	    __HAL_TIM_SET_COUNTER(&htim4, 0);
	    HAL_TIM_Base_Start_IT(&htim4);
	}


	//D8
		else if (GPIO_Pin == CONFIRM_BTN_Pin){
			num_button = 2;
	        HAL_NVIC_DisableIRQ(EXTI0_IRQn); // Disable EXTI
	        __HAL_TIM_SET_COUNTER(&htim4, 0);
	        HAL_TIM_Base_Start_IT(&htim4);
		}


}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// executes once the time runs out

	//Confirm Button Code
	if(htim -> Instance == TIM4 && num_button == 2){
		HAL_TIM_Base_Stop_IT(&htim4);

		 uint8_t current_button_state = HAL_GPIO_ReadPin(CONFIRM_BTN_GPIO_Port, CONFIRM_BTN_Pin);

			if(current_button_state == GPIO_PIN_SET && current_button_state != previous_button_state){
				time_start = HAL_GetTick();
				if (!timer_active){
					 HAL_TIM_Base_Start_IT(&htim3);
					 timer_active = 1;
					button_press = PRESS_DETECTED;
					//printf("%d\n\r", count);
					//printf("Detected\n\r");
				}
				else {
					button_press = WAIT_RELEASE;
					//printf("W R\n\r");
				}
			}

			else if (current_button_state == GPIO_PIN_RESET && current_button_state != previous_button_state){
				released_time = HAL_GetTick() - time_start;

				if (released_time >= 900){
					LP_flag = 1;
					//printf("LP\n\r");

				}
				else {
					count++;
					//printf("%d\n\r", count);
					button_press = PRESS_DETECTED;
					//printf("P D \n\r");
				}

			}

			previous_button_state = current_button_state;
			__HAL_GPIO_EXTI_CLEAR_IT(CONFIRM_BTN_Pin);
			HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

	//Reset Button Code
	else if (htim -> Instance == TIM4 && num_button == 1){
		HAL_TIM_Base_Stop_IT(&htim4);

		    uint8_t current_state = HAL_GPIO_ReadPin(RESET_BTN_GPIO_Port, RESET_BTN_Pin);

		    if (current_state == GPIO_PIN_SET) {
		        uint32_t now = HAL_GetTick();

		        if (!reset_confirm_window_active) {
		            // First press -> open confirmation window
		            reset_confirm_window_active = true;
		            reset_button_time_start = now;

		            printf("\n\rReset requested. Press again within 3 seconds to confirm.\n\r");

		            //TFT
		            ILI9341_DrawText("Reset requested. Press again within 3 seconds to confirm.", FONT4, 0, tft_y, WHITE, BLACK);
		            tft_y+=20;
		            __HAL_TIM_SET_COUNTER(&htim3, 0);
		            HAL_TIM_Base_Start_IT(&htim3); // Start 3s countdown
		        }

		        else {
		            // Second press within window -> reset
		            if ((now - reset_button_time_start) <= 3000) {
		                printf("\n\rReset confirmed. Performing system reset...\n\r");
		                //TFT
		                ILI9341_DrawText("Reset confirmed. Performing system reset...", FONT4, 0, tft_y, WHITE, BLACK);
		                HAL_NVIC_SystemReset();

		            }
		        }
		    }

		    __HAL_GPIO_EXTI_CLEAR_IT(RESET_BTN_Pin);
		    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	}

	if (htim->Instance == TIM3 && num_button == 2){
        HAL_TIM_Base_Stop_IT(&htim3);
        timer_active = 0;

        // Determine the result
        if (LP_flag == 1)
        {
        	input_type = 3; // LONG PRESS
           // printf("%d\n\r", input_type);
        }
        else if (count >= 2)
        {
        	input_type = 2; // DOUBLE PRESS
           // printf("%d\n\r", input_type);
        }
        else if (count == 1 && button_press == PRESS_DETECTED)
        {
        	input_type = 1; // SINGLE PRESS
           // printf("%d\n\r", input_type);
        }

        // Reset everything
        else {
    		count = 0;
    		LP_flag = 0;
    		button_press = IDLE;
			}
		count = 0;
		LP_flag = 0;
		button_press = IDLE;
		}

	else if (htim->Instance == TIM3 && num_button == 1 && reset_confirm_window_active){
	    HAL_TIM_Base_Stop_IT(&htim3);
	    reset_confirm_window_active = false;
	    printf("\n\rReset canceled. Returning to normal operation.\n\r");
	    //TFT
	    ILI9341_DrawText("Reset canceled. Returning to normal operation.", FONT4, 0, tft_y, WHITE, BLACK);
	    HAL_Delay(2500);
		ILI9341_TopScreen(BLACK);

		}

	}


void button_output(int button_num){
	  while (true){
		if(input_type == 1){
			printf("SINGLE PRESS\n\r");
			//TFT
			ILI9341_TopScreen(BLACK);
			ILI9341_DrawText("SINGLE PRESS", FONT4, 0, 0, WHITE, BLACK);
			HAL_Delay(2000);
			ILI9341_TopScreen(BLACK);
			input_type = 0;

	        // Reset everything
	        count = 0;
	        LP_flag = 0;
	        button_press = IDLE;
			break;
		}
		else if (input_type == 2){
			printf("DOUBLE PRESS\n\r");
			//TFT
			ILI9341_TopScreen(BLACK);
			ILI9341_DrawText("DOUBLE PRESS", FONT4, 0, 0, WHITE, BLACK);
			HAL_Delay(2000);
			ILI9341_TopScreen(BLACK);
			input_type = 0;

	        // Reset everything
	        count = 0;
	        LP_flag = 0;
	        button_press = IDLE;
			break;
		}
		else if (input_type == 3){
			printf("LONG PRESS\n\r");
			input_type = 0;
			//TFT
			ILI9341_TopScreen(BLACK);
			ILI9341_DrawText("LONG PRESS", FONT4, 0, 0, WHITE, BLACK);
			HAL_Delay(2000);
			ILI9341_TopScreen(BLACK);

	        // Reset everything
	        count = 0;
	        LP_flag = 0;
	        button_press = IDLE;
			break;
		}
	}
}

int button_refill(){
	int firstcall = HAL_GetTick();

	while(HAL_GetTick() - firstcall <= 15000){
		if (button_press != IDLE){
			return 1;
		}
	}

	return 0;

}
