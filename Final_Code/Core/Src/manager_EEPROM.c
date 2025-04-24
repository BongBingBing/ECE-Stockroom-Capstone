/*
 * manager_EEPROM.c
 *
 *  Created on: Apr 22, 2025
 *      Author: soup
 */
#include "stdio.h"
#include "usart.h"
#include <stdbool.h>
#include "tim.h"
#include "gpio.h"
#include "spi.h"

#define EEPROM_CS_LOW()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET)
#define EEPROM_CS_HIGH() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET)




void EEPROM_WriteEnable(void) {
    uint8_t cmd = 0x06;
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, &cmd, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);

}

void EEPROM_WriteByte(uint8_t addr, uint8_t data) {
    uint8_t buf[3] = {0x02, addr, data}; // WRITE instruction
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, buf, 3, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);

}

uint8_t EEPROM_ReadByte(uint8_t addr) {
    uint8_t cmd[2] = {0x03, addr}; // READ instruction
    uint8_t data = 0;
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, cmd, 2, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi3, &data, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);
    return data;
}

uint8_t EEPROM_ReadStatus(void) {
    uint8_t cmd = 0x05;
    uint8_t status = 0;
    EEPROM_CS_LOW();
    HAL_Delay(100);
    HAL_SPI_Transmit(&hspi3, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi3, &status, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    HAL_Delay(100);
    return status;
}


void EEPROM_Write(uint8_t addr, uint8_t writeData){
	printf("Status before write: 0x%02X \r\n", EEPROM_ReadStatus());
	EEPROM_WriteEnable();
	printf("Status after WREN: 0x%02X \r\n", EEPROM_ReadStatus());
	EEPROM_WriteByte(addr, writeData);

	// Wait until write complete
	while (EEPROM_ReadStatus() & 0x01){
		if (EEPROM_ReadStatus() == 0xFF){
			break;
		}
	}
}




