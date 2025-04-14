#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

#define EEPROM_CS_LOW()  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET)
#define EEPROM_CS_HIGH() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET)

void EEPROM_WriteByte(uint8_t addr, uint8_t data);
uint8_t EEPROM_ReadByte(uint8_t addr);
void EEPROM_WriteEnable(void);
uint8_t EEPROM_ReadStatus(void);

int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI3_Init();
    MX_USART2_UART_Init();

    HAL_Delay(100);

    uint8_t addr = 0x00;
    uint8_t writeData = 0xAB;

    EEPROM_WriteEnable();
    EEPROM_WriteByte(addr, writeData);

    while (EEPROM_ReadStatus() & 0x01);

    uint8_t readData = EEPROM_ReadByte(addr);

    printf("Wrote 0x%02X to EEPROM, read back: 0x%02X\r\n", writeData, readData);

    while (1) {}
}

void EEPROM_WriteEnable(void) {
    uint8_t cmd = 0x06;
    EEPROM_CS_LOW();
    HAL_SPI_Transmit(&hspi3, &cmd, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
}

void EEPROM_WriteByte(uint8_t addr, uint8_t data) {
    uint8_t buf[3] = {0x02, addr, data};
    EEPROM_CS_LOW();
    HAL_SPI_Transmit(&hspi3, buf, 3, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
}

uint8_t EEPROM_ReadByte(uint8_t addr) {
    uint8_t cmd[2] = {0x03, addr};
    uint8_t data = 0;
    EEPROM_CS_LOW();
    HAL_SPI_Transmit(&hspi3, cmd, 2, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi3, &data, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    return data;
}

uint8_t EEPROM_ReadStatus(void) {
    uint8_t cmd = 0x05;
    uint8_t status = 0;
    EEPROM_CS_LOW();
    HAL_SPI_Transmit(&hspi3, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi3, &status, 1, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
    return status;
}