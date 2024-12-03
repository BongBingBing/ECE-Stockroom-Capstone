/*
 * io_manager.c
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#include "stdio.h"
#include "usart.h"
#include <stdbool.h>

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

void doublePress(GPIO_TypeDef* port,uint16_t pin){
  GPIO_PinState last_state = GPIO_PIN_RESET;
  GPIO_PinState button_state;

  uint32_t DP_Threshold = 2000; // 2 second threshold
  uint32_t press_time = 0;         // Timestamp of the first press
  uint8_t press_count = 0;  // A Flag that's used for indicating a second press

	while(true){
		button_state = HAL_GPIO_ReadPin( port, pin);

		if (button_state != last_state) { // Button state changed
			HAL_Delay(50); // Debounce delay

			if (button_state == GPIO_PIN_SET) { // Button pressed
				if (press_count == 0) {

				}
					// Reads First press
					printf("Button press\n");
					press_time = HAL_GetTick(); // saves the time of the first press
					press_count = 1;    // proof of first button press

				}
					else if ((HAL_GetTick() - press_time) <= DP_Threshold){	// if the press_count = 1 and the button is pressed again, it is a double press
						printf("Double press\n");
						press_count = 0; // Reset state
						break;
				}
			}
	}
}


void singlePress(GPIO_TypeDef* port,uint16_t pin){
  GPIO_PinState button_state;

	while(true){
		button_state = HAL_GPIO_ReadPin(port, pin);
		if (button_state == GPIO_PIN_SET) { // Button pressed

			printf("Button press\n");
			break;
		}
	}
}
