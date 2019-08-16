################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/device/lmx2594/subdir.mk
-include src/device/dac8550/subdir.mk
-include src/device/common/subdir.mk
-include src/device/cdcm6208/subdir.mk
-include src/device/adrv9009/subdir.mk
-include src/device/adi_hal/subdir.mk
-include src/device/ad9528/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
test_ucos.elf.size \


# All Target
all: test_ucos.elf secondary-outputs

# Tool invocations
test_ucos.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v8 gcc linker'
	aarch64-none-elf-gcc -Wl,-T -Wl,../src/lscript.ld -L../../ucos_bsp/psu_cortexa53_0/lib -o "test_ucos.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

test_ucos.elf.size: test_ucos.elf
	@echo 'Invoking: ARM v8 Print Size'
	aarch64-none-elf-size test_ucos.elf  |tee "test_ucos.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) test_ucos.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
