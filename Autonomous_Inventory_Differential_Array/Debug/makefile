################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Autonomous_Inventory_Differential_Array
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Autonomous_Inventory_Differential_Array.elf \

MAP_FILES += \
Autonomous_Inventory_Differential_Array.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Autonomous_Inventory_Differential_Array.list \


# All Target
all: main-build

# Main-build Target
main-build: Autonomous_Inventory_Differential_Array.elf secondary-outputs

# Tool invocations
Autonomous_Inventory_Differential_Array.elf Autonomous_Inventory_Differential_Array.map: $(OBJS) $(USER_OBJS) C:\Users\andyb\OneDrive\Desktop\School_Fall_24\Capstone\ECE-Stockroom-Capstone\Autonomous_Inventory_Differential_Array\STM32L152RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Autonomous_Inventory_Differential_Array.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\andyb\OneDrive\Desktop\School_Fall_24\Capstone\ECE-Stockroom-Capstone\Autonomous_Inventory_Differential_Array\STM32L152RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Autonomous_Inventory_Differential_Array.map" -Wl,--gc-sections -static -u _scanf_float -u _printf_float --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Autonomous_Inventory_Differential_Array.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Autonomous_Inventory_Differential_Array.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Autonomous_Inventory_Differential_Array.elf Autonomous_Inventory_Differential_Array.list Autonomous_Inventory_Differential_Array.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
