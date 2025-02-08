################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Touch/Touch.c 

OBJS += \
./Touch/Touch.o 

C_DEPS += \
./Touch/Touch.d 


# Each subdirectory must supply rules for building sources it contributes
Touch/%.o Touch/%.su Touch/%.cyclo: ../Touch/%.c Touch/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Icons -I../Images -I../ILI9341 -I../Touch -I../UART -I../Display -Og -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Touch

clean-Touch:
	-$(RM) ./Touch/Touch.cyclo ./Touch/Touch.d ./Touch/Touch.o ./Touch/Touch.su

.PHONY: clean-Touch

