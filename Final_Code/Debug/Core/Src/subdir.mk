################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ILI9341_GFX.c \
../Core/Src/ILI9341_STM32_Driver.c \
../Core/Src/dma.c \
../Core/Src/drawer_table.c \
../Core/Src/fonts.c \
../Core/Src/function_calibration.c \
../Core/Src/function_refill.c \
../Core/Src/funtion_main.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/manager_EEPROM.c \
../Core/Src/manager_file.c \
../Core/Src/manager_io.c \
../Core/Src/manager_mux.c \
../Core/Src/manager_relay.c \
../Core/Src/manager_weigt.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/ILI9341_GFX.o \
./Core/Src/ILI9341_STM32_Driver.o \
./Core/Src/dma.o \
./Core/Src/drawer_table.o \
./Core/Src/fonts.o \
./Core/Src/function_calibration.o \
./Core/Src/function_refill.o \
./Core/Src/funtion_main.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/manager_EEPROM.o \
./Core/Src/manager_file.o \
./Core/Src/manager_io.o \
./Core/Src/manager_mux.o \
./Core/Src/manager_relay.o \
./Core/Src/manager_weigt.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/ILI9341_GFX.d \
./Core/Src/ILI9341_STM32_Driver.d \
./Core/Src/dma.d \
./Core/Src/drawer_table.d \
./Core/Src/fonts.d \
./Core/Src/function_calibration.d \
./Core/Src/function_refill.d \
./Core/Src/funtion_main.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/manager_EEPROM.d \
./Core/Src/manager_file.d \
./Core/Src/manager_io.d \
./Core/Src/manager_mux.d \
./Core/Src/manager_relay.d \
./Core/Src/manager_weigt.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
<<<<<<< HEAD:Final_Code/Debug/Core/Src/subdir.mk
	-$(RM) ./Core/Src/ILI9341_GFX.cyclo ./Core/Src/ILI9341_GFX.d ./Core/Src/ILI9341_GFX.o ./Core/Src/ILI9341_GFX.su ./Core/Src/ILI9341_STM32_Driver.cyclo ./Core/Src/ILI9341_STM32_Driver.d ./Core/Src/ILI9341_STM32_Driver.o ./Core/Src/ILI9341_STM32_Driver.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/function_calibration.cyclo ./Core/Src/function_calibration.d ./Core/Src/function_calibration.o ./Core/Src/function_calibration.su ./Core/Src/function_refill.cyclo ./Core/Src/function_refill.d ./Core/Src/function_refill.o ./Core/Src/function_refill.su ./Core/Src/funtion_main.cyclo ./Core/Src/funtion_main.d ./Core/Src/funtion_main.o ./Core/Src/funtion_main.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/manager_EEPROM.cyclo ./Core/Src/manager_EEPROM.d ./Core/Src/manager_EEPROM.o ./Core/Src/manager_EEPROM.su ./Core/Src/manager_file.cyclo ./Core/Src/manager_file.d ./Core/Src/manager_file.o ./Core/Src/manager_file.su ./Core/Src/manager_io.cyclo ./Core/Src/manager_io.d ./Core/Src/manager_io.o ./Core/Src/manager_io.su ./Core/Src/manager_mux.cyclo ./Core/Src/manager_mux.d ./Core/Src/manager_mux.o ./Core/Src/manager_mux.su ./Core/Src/manager_relay.cyclo ./Core/Src/manager_relay.d ./Core/Src/manager_relay.o ./Core/Src/manager_relay.su ./Core/Src/manager_weigt.cyclo ./Core/Src/manager_weigt.d ./Core/Src/manager_weigt.o ./Core/Src/manager_weigt.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su
=======
	-$(RM) ./Core/Src/ILI9341_GFX.cyclo ./Core/Src/ILI9341_GFX.d ./Core/Src/ILI9341_GFX.o ./Core/Src/ILI9341_GFX.su ./Core/Src/ILI9341_STM32_Driver.cyclo ./Core/Src/ILI9341_STM32_Driver.d ./Core/Src/ILI9341_STM32_Driver.o ./Core/Src/ILI9341_STM32_Driver.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/drawer_table.cyclo ./Core/Src/drawer_table.d ./Core/Src/drawer_table.o ./Core/Src/drawer_table.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/function_calibration.cyclo ./Core/Src/function_calibration.d ./Core/Src/function_calibration.o ./Core/Src/function_calibration.su ./Core/Src/function_refill.cyclo ./Core/Src/function_refill.d ./Core/Src/function_refill.o ./Core/Src/function_refill.su ./Core/Src/funtion_main.cyclo ./Core/Src/funtion_main.d ./Core/Src/funtion_main.o ./Core/Src/funtion_main.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/manager_file.cyclo ./Core/Src/manager_file.d ./Core/Src/manager_file.o ./Core/Src/manager_file.su ./Core/Src/manager_io.cyclo ./Core/Src/manager_io.d ./Core/Src/manager_io.o ./Core/Src/manager_io.su ./Core/Src/manager_mux.cyclo ./Core/Src/manager_mux.d ./Core/Src/manager_mux.o ./Core/Src/manager_mux.su ./Core/Src/manager_relay.cyclo ./Core/Src/manager_relay.d ./Core/Src/manager_relay.o ./Core/Src/manager_relay.su ./Core/Src/manager_weigt.cyclo ./Core/Src/manager_weigt.d ./Core/Src/manager_weigt.o ./Core/Src/manager_weigt.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su
>>>>>>> origin/Joel's-Code:test_case/Debug/Core/Src/subdir.mk

.PHONY: clean-Core-2f-Src

