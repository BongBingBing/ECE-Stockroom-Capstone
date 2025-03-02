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
enum press_type { press_none = 0, press_short, press_double, press_long };
volatile enum press_type button_press;
// button states flags
int i = 0;
int j = 0;
// counts button presses
int count = 0;
volatile int timer_active = 0; // flag timer
volatile unsigned int time_start;  // Timestamp of the button press
unsigned int released_time; // Timestamp of the button released

int num_button = 0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// D7
	if (GPIO_Pin == RESET_BTN_Pin) {
		num_button = 1;
		if 	(timer_active == 0){
			if(HAL_GPIO_ReadPin(RESET_BTN_GPIO_Port, RESET_BTN_Pin) == GPIO_PIN_SET && i == 0){
					i = 1; // states the button already been pressed to ignore interrupts
					//printf("%d i\n\r", i);
					time_start = HAL_GetTick(); // reads when button is pressed
				}

				else if (HAL_GPIO_ReadPin(RESET_BTN_GPIO_Port, RESET_BTN_Pin) == GPIO_PIN_RESET && j == 0){
					j = 1;
					count = 1;
					/*printf("%d j\n\r", j);*/
					released_time = HAL_GetTick();// reads when button is released
					HAL_TIM_Base_Start_IT(&htim3);
					timer_active = 1; // timer has active so button sequence is paused
				}
		}
	}

	//D8
		else if (GPIO_Pin == CONFIRM_BTN_Pin){
			//num_button = 2;
			if(count != 2){
				if ( count == 0){
					// starts general timer
				HAL_TIM_Base_Start_IT(&htim3);
				}
					if(HAL_GPIO_ReadPin(CONFIRM_BTN_GPIO_Port, CONFIRM_BTN_Pin) == GPIO_PIN_SET && i == 0){
						i = 1;
						time_start = HAL_GetTick(); // reads when button is pressed
					}

					else if(HAL_GPIO_ReadPin(CONFIRM_BTN_GPIO_Port, CONFIRM_BTN_Pin) == GPIO_PIN_RESET && j == 0) {
						j = 1;
						count++;

						released_time = HAL_GetTick();// reads when button is released
						HAL_TIM_Base_Start_IT(&htim4);// timer used to reset i and j values & handle debounce
						num_button = 2;
					}
				}
			}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// executes once the time runs out
	if(htim -> Instance == TIM3){
		if ( count == 1){
			// short press
			if (released_time - time_start <= 900){
				button_press = press_short;
			}
			// long press
			else if (released_time - time_start >= 1100){
				button_press = press_long;
			}
		}
		// double press
		else if ( count == 2){
			button_press = press_double;
		}

		HAL_TIM_Base_Stop_IT(&htim3); // stops timer interrupt
		//resets flags & press count
		i = 0;
		timer_active = 0;
		j = 0;
		count = 0;

	}

		else if (htim -> Instance == TIM4){
			printf("%d\n\r",count);
			HAL_TIM_Base_Stop_IT(&htim4); // stops timer interrupt
			// resets flags
			i = 0;
			j = 0;
		}

}

void button_output(int button_num){
	  while (true){
		  // checks if user presses the correct button
		  if(num_button != 0){
			 if (button_num == num_button){
// different button states
			  if (button_press == press_short){
				  printf("short %d\n\r",i);
				  num_button = 0;
				  button_press = press_none;
				  break;
			  }
				else if (button_press == press_long){
						  printf("long %d\n\r",i);
						  num_button = 0;
						  button_press = press_none;
						  break;
					  }

			else if (button_press == press_double) {
					printf("double %d\n\r",i);
					num_button = 0;
					button_press = press_none;
					break;
			}
		  }
			 // displays if user presses wrong button
			 else {
				 printf("Wrong Button, Please Wait Three Seconds To Try Again \n\r");
				 HAL_Delay(500);
				 num_button = 0;
				 count = 0;
				 button_press = press_none;
			 }
		}
	}
}

