/*
 * io_manager.h
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#ifndef INC_MANAGER_IO_H_
#define INC_MANAGER_IO_H_
#include <stdbool.h>

int _write(int file, char *data, int len);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

void button_output(int button_num);


extern bool confirm_button;
extern bool reset_button;


#endif /* INC_MANAGER_IO_H_ */
