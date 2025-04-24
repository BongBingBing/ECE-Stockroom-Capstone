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

#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

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
    LONG_PRESS,
    TIME_WINDOW_END };
volatile enum press_type button_press;
// button states flags
int i = 0;
int j;
int k = 0;
// counts button presses
int count = 0;
volatile int timer_active = 0; // flag timer
volatile unsigned int time_start;  // Timestamp of the button press
unsigned int released_time; // Timestamp of the button released
volatile bool reset_requested = false;
volatile uint32_t reset_request_time = 0;

volatile bool reset_debounce_pending = false;
volatile bool reset_confirm_window_active = false;
volatile uint32_t reset_button_time_start = 0;


int num_button = 0;
volatile uint8_t previous_button_state = 0;
volatile uint32_t confirm_last_edge = 0;

#define DEBOUNCE_DELAY 20
#define NVIC_RESET_KEY 0x5FA0000

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    //uint32_t current_time = HAL_GetTick();
	// D7
	/*if (GPIO_Pin == RESET_BTN_Pin) {
		//printf("Reset button Pressed");
		num_button = 1;

	    HAL_NVIC_DisableIRQ(EXTI1_IRQn); // assuming EXTI1 used for RESET
	    __HAL_TIM_SET_COUNTER(&htim4, 0);
	    HAL_TIM_Base_Start_IT(&htim4);
	}
*/
	//D8
		 if (GPIO_Pin == CONFIRM_BTN_Pin){
			//printf("Confirm button Pressed");
			num_button = 2;
	        HAL_NVIC_DisableIRQ(EXTI0_IRQn); // Disable EXTI
	        __HAL_TIM_SET_COUNTER(&htim4, 0);
	        HAL_TIM_Base_Start_IT(&htim4);
		}


}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// executes once the time runs out
	if(htim -> Instance == TIM4 && num_button == 2){
		HAL_TIM_Base_Stop_IT(&htim4);

		 uint8_t current_button_state = HAL_GPIO_ReadPin(CONFIRM_BTN_GPIO_Port, CONFIRM_BTN_Pin);

			if(current_button_state == GPIO_PIN_SET && current_button_state != previous_button_state/*&& i == 0*/){
				time_start = HAL_GetTick();
				if (!timer_active){
					 HAL_TIM_Base_Start_IT(&htim3);
					 timer_active = 1;
					button_press = PRESS_DETECTED;
					printf("%d\n\r", count);
					printf("Detected\n\r");
				}
				else {
					button_press = WAIT_RELEASE;
					printf("W R\n\r");
				}
			}

			else if (current_button_state == GPIO_PIN_RESET && current_button_state != previous_button_state){
				released_time = HAL_GetTick() - time_start;

				if (released_time >= 900){
					i = 1;
					button_press = LONG_PRESS;
					printf("LP\n\r");

				}
				else {
					count++;
					printf("%d\n\r", count);
					button_press = PRESS_DETECTED;
					printf("P D \n\r");
				}

			}

			previous_button_state = current_button_state;
			__HAL_GPIO_EXTI_CLEAR_IT(CONFIRM_BTN_Pin);
			HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}
	else if (htim -> Instance == TIM4 && num_button == 1){
		HAL_TIM_Base_Stop_IT(&htim4);

		    uint8_t current_state = HAL_GPIO_ReadPin(RESET_BTN_GPIO_Port, RESET_BTN_Pin);

		    if (current_state == GPIO_PIN_SET) {
		        uint32_t now = HAL_GetTick();

		        if (!reset_confirm_window_active) {
		            // First press → open confirmation window
		            reset_confirm_window_active = true;
		            reset_button_time_start = now;

		            printf("\n\rReset requested. Press again within 3 seconds to confirm.\n\r");

		            __HAL_TIM_SET_COUNTER(&htim3, 0);
		            HAL_TIM_Base_Start_IT(&htim3); // Start 3s countdown
		        } else {
		            // Second press within window → reset
		            if ((now - reset_button_time_start) <= 3000) {
		                printf("\n\rReset confirmed. Performing system reset...\n\r");
		                HAL_NVIC_SystemReset();

		            }
		        }
		    }

		    reset_debounce_pending = false;
		    __HAL_GPIO_EXTI_CLEAR_IT(RESET_BTN_Pin);
		    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	}

	if (htim->Instance == TIM3 && num_button == 2){
        HAL_TIM_Base_Stop_IT(&htim3);
        timer_active = 0;

        // Determine the result
        if (i == 1)
        {
            //printf("LONG PRESS\n");
            j = 3;
            printf("%d\n\r", j);
        }
        else if (count >= 2)
        {
           // printf("DOUBLE PRESS\n");
            j = 2;
            printf("%d\n\r", j);
        }
        else if (count == 1 && button_press == PRESS_DETECTED)
        {
            //printf("SINGLE PRESS\n");
            j = 1;
            printf("%d\n\r", j);
        }

        // Reset everything
        /**/else {
        	//printf("Nope\n\r");
    		count = 0;
    		//printf("%d\n\r", count);
    		i = 0;
    		button_press = IDLE;
			}
		count = 0;
		//printf("%d\n\r", count);
		i = 0;
		button_press = IDLE;
		}

	else if (htim->Instance == TIM3 && num_button == 1 && reset_confirm_window_active){
	    HAL_TIM_Base_Stop_IT(&htim3);
	    reset_confirm_window_active = false;

	    printf("\n\rReset canceled. Returning to normal operation.\n\r");
		}

	}


void button_output(int button_num){
	  while (true){
		if(j == 1){
			printf("SINGLE PRESS\n\r");
			j = 0;

	        // Reset everything
	        count = 0;
	        i = 0;
	        button_press = IDLE;
			break;
		}
		else if (j == 2){
			printf("DOUBLE PRESS\n\r");
			j = 0;

	        // Reset everything
	        count = 0;
	        i = 0;
	        button_press = IDLE;
			break;
		}
		else if (j == 3){
			printf("LONG PRESS\n\r");
			j = 0;

	        // Reset everything
	        count = 0;
	        i = 0;
	        button_press = IDLE;
			break;
		}
	}
}
