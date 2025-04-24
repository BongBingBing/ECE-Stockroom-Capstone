/*
 * manager_EEPROM.h
 *
 *  Created on: Apr 22, 2025
 *      Author: soup
 */

#ifndef INC_MANAGER_EEPROM_H_
#define INC_MANAGER_EEPROM_H_



#endif /* INC_MANAGER_EEPROM_H_ */


void EEPROM_WriteEnable(void);
void EEPROM_WriteByte(uint8_t addr, uint8_t data);
uint8_t EEPROM_ReadByte(uint8_t addr);
uint8_t EEPROM_ReadStatus(void);
void EEPROM_Write(uint8_t addr, uint8_t writeData);
