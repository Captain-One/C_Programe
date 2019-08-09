################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./src/cyhc5g.obj" \
"./src/cyhc5g_gpio.obj" \
"./src/cyhc5g_i2c.obj" \
"./src/cyhc5g_i2c_eeprom.obj" \
"./src/cyhc5g_led.obj" \
"./src/cyhc5g_nand.obj" \
"./src/cyhc5g_nor.obj" \
"./src/cyhc5g_phy.obj" \
"./src/cyhc5g_spi.obj" \
"./src/cyhc5g_uart.obj" \
"./src/platform.obj" \
"../lib/debug/ti.platform.evm6678l.lite.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/debug/subdir_vars.mk
-include src/subdir_vars.mk
-include lib/debug/subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LIB_OUTPUTS += \
D:/pxqwork/project/5G-DSP/platform_lib_evmc6678l/lib/debug/ti.platform.evm6678l.ae66 \

LIB_OUTPUTS__QUOTED += \
"D:\pxqwork\project\5G-DSP\platform_lib_evmc6678l\lib\debug\ti.platform.evm6678l.ae66" \


# All Target
all: D:/pxqwork/project/5G-DSP/platform_lib_evmc6678l/lib/debug/ti.platform.evm6678l.ae66

# Tool invocations
D:/pxqwork/project/5G-DSP/platform_lib_evmc6678l/lib/debug/ti.platform.evm6678l.ae66: $(OBJS) $(LIB_SRCS)
ifneq ($(strip $(ORDERED_OBJS)),)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C6000 Archiver'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/ar6x" r "D:/pxqwork/project/5G-DSP/platform_lib_evmc6678l/lib/debug/ti.platform.evm6678l.ae66" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
endif

# Other Targets
clean:
	-$(RM) $(LIB_OUTPUTS__QUOTED)
	-$(RM) "src\cyhc5g.obj" "src\cyhc5g_gpio.obj" "src\cyhc5g_i2c.obj" "src\cyhc5g_i2c_eeprom.obj" "src\cyhc5g_led.obj" "src\cyhc5g_nand.obj" "src\cyhc5g_nor.obj" "src\cyhc5g_phy.obj" "src\cyhc5g_spi.obj" "src\cyhc5g_uart.obj" "src\platform.obj" 
	-$(RM) "src\cyhc5g.d" "src\cyhc5g_gpio.d" "src\cyhc5g_i2c.d" "src\cyhc5g_i2c_eeprom.d" "src\cyhc5g_led.d" "src\cyhc5g_nand.d" "src\cyhc5g_nor.d" "src\cyhc5g_phy.d" "src\cyhc5g_spi.d" "src\cyhc5g_uart.d" "src\platform.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

