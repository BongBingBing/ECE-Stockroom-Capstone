################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/calibration_function.cpp \
../Core/Src/file_manager.cpp \
../Core/Src/gpio.cpp \
../Core/Src/io_manager.cpp \
../Core/Src/main.cpp \
../Core/Src/main_function.cpp \
../Core/Src/mux_manager.cpp \
../Core/Src/refill_function.cpp \
../Core/Src/stm32f4xx_hal_msp.cpp \
../Core/Src/stm32f4xx_it.cpp \
../Core/Src/syscalls.cpp \
../Core/Src/sysmem.cpp \
../Core/Src/system_stm32f4xx.cpp \
../Core/Src/tim.cpp \
../Core/Src/usart.cpp \
../Core/Src/weight_manager.cpp 

OBJS += \
./Core/Src/calibration_function.o \
./Core/Src/file_manager.o \
./Core/Src/gpio.o \
./Core/Src/io_manager.o \
./Core/Src/main.o \
./Core/Src/main_function.o \
./Core/Src/mux_manager.o \
./Core/Src/refill_function.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o \
./Core/Src/weight_manager.o 

CPP_DEPS += \
./Core/Src/calibration_function.d \
./Core/Src/file_manager.d \
./Core/Src/gpio.d \
./Core/Src/io_manager.d \
./Core/Src/main.d \
./Core/Src/main_function.d \
./Core/Src/mux_manager.d \
./Core/Src/refill_function.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/weight_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/calibration_function.cyclo ./Core/Src/calibration_function.d ./Core/Src/calibration_function.o ./Core/Src/calibration_function.su ./Core/Src/file_manager.cyclo ./Core/Src/file_manager.d ./Core/Src/file_manager.o ./Core/Src/file_manager.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/io_manager.cyclo ./Core/Src/io_manager.d ./Core/Src/io_manager.o ./Core/Src/io_manager.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/main_function.cyclo ./Core/Src/main_function.d ./Core/Src/main_function.o ./Core/Src/main_function.su ./Core/Src/mux_manager.cyclo ./Core/Src/mux_manager.d ./Core/Src/mux_manager.o ./Core/Src/mux_manager.su ./Core/Src/refill_function.cyclo ./Core/Src/refill_function.d ./Core/Src/refill_function.o ./Core/Src/refill_function.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/weight_manager.cyclo ./Core/Src/weight_manager.d ./Core/Src/weight_manager.o ./Core/Src/weight_manager.su

.PHONY: clean-Core-2f-Src

