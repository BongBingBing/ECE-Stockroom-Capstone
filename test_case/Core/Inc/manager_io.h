/*
 * io_manager.h
 *
 *  Created on: Nov 20, 2024
 *      Author: andyb
 */

#ifndef INC_MANAGER_IO_H_
#define INC_MANAGER_IO_H_

int _write(int file, char *data, int len);

void doublePress(GPIO_TypeDef* port,uint16_t pin);

void singlePress(GPIO_TypeDef* port,uint16_t pin);

#endif /* INC_MANAGER_IO_H_ */
