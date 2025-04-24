



#include <main.h> //all GPIO assignments found here
#include "stdio.h"
#include <stdbool.h>
#include "gpio.h"
#include "tim.h"


void microDelay(uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  while (__HAL_TIM_GET_COUNTER(&htim2) < delay);
}

int32_t getHX711(void)
{
  uint32_t data = 0;
  uint32_t startTime = HAL_GetTick();
  while(HAL_GPIO_ReadPin(DAT_IN_GPIO_Port, DAT_IN_Pin) == GPIO_PIN_SET)
  {
    if(HAL_GetTick() - startTime > 200)
      return 0;
  }
  for(int8_t len=0; len<24 ; len++)
  {
    HAL_GPIO_WritePin(SCK_DRW_GPIO_Port, SCK_DRW_Pin, GPIO_PIN_SET);
    microDelay(1);
    data = data << 1;
    HAL_GPIO_WritePin(SCK_DRW_GPIO_Port, SCK_DRW_Pin, GPIO_PIN_RESET);
    microDelay(1);
    if(HAL_GPIO_ReadPin(DAT_IN_GPIO_Port, DAT_IN_Pin) == GPIO_PIN_SET)
      data ++;
  }
  data = data ^ 0x800000;
  HAL_GPIO_WritePin(SCK_DRW_GPIO_Port, SCK_DRW_Pin, GPIO_PIN_SET);
  microDelay(1);
  HAL_GPIO_WritePin(SCK_DRW_GPIO_Port, SCK_DRW_Pin, GPIO_PIN_RESET);
  microDelay(1);
  return data;
}

int weigh(uint32_t tare, float calFactor)
{
  int64_t  total = 0;
  int32_t  samples = 50;

  int milligram = 0;
  int32_t average = 0;

  for(uint16_t i=0 ; i<samples ; i++)
  {
      total += getHX711();
  }
  average = (int32_t)(total / samples);
  milligram = (int)(average - tare)*calFactor;
  return milligram;
}

int32_t weighRaw()
{
  int64_t  	total = 0;
  int32_t  	samples = 50;
  int32_t 	average = 0;

  for(uint16_t i=0 ; i<samples ; i++)
  {
      total += getHX711();
  }
  average = (int32_t)(total / samples);
  return average;
}

int32_t weighRawTare(uint32_t tare)
{

  int64_t  	total = 0;
  int32_t  	samples = 50;
  int32_t 	average = 0;
  int32_t 	avgTare = 0;

  for(uint16_t i=0 ; i<samples ; i++)
  {
      total += getHX711();
  }
  average = (int32_t)(total / samples);
  avgTare = average - tare;
  return avgTare;
}

float getCalFactor(uint32_t knownHX711){
	float cal = 20000.0 / knownHX711;
	return cal;
}
