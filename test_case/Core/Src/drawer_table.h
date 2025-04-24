/*
 * drawer_table.h
 *
 *  Created on: Mar 22, 2025
 *      Author: Joel
 */

#ifndef INC_DRAWER_TABLE_H_
#define INC_DRAWER_TABLE_H_

#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include "stm32f4xx_hal.h"
#include "fonts.h"

void drawer_lookup(uint16_t rows, uint16_t drawer, char colors);

void drawer_table();

#endif /* INC_DRAWER_TABLE_H_ */
