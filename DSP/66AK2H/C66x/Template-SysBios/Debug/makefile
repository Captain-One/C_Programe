################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"configPkg/linker.cmd"

ORDERED_OBJS += \
"./global-resource-list.obj" \
"./main.obj" \
"./policy_dsp-only.obj" \
"./rm_transport_setup.obj" \
"./sample_osal.obj" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/board/lib/evmK2H/c66/release/ti.board.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/drv/uart/lib/k2h/c66/release/ti.drv.uart.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/csl/lib/k2h/c66/release/ti.csl.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/csl/lib/k2h/c66/release/ti.csl.intc.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/osal/lib/tirtos/k2h/c66/release/ti.osal.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/platform/evmk2h/platform_lib/lib/release/ti.platform.evmk2h.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/drv/cppi/lib/k2h/c66/ti.drv.cppi.k2h.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/drv/qmss/lib/k2h/c66/ti.drv.qmss.k2h.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/drv/rm/lib/c66/ti.drv.rm.ae66" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
EXE_OUTPUTS += \
bios-temp.out \

EXE_OUTPUTS__QUOTED += \
"bios-temp.out" \

BIN_OUTPUTS += \
bios-temp.hex \

BIN_OUTPUTS__QUOTED += \
"bios-temp.hex" \


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "bios-temp.out"

# Tool invocations
bios-temp.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/bin/cl6x" -mv6500 --define=evmK2H --define=SOC_K2H -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"bios-temp.map" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="bios-temp_linkInfo.xml" --rom_model -o "bios-temp.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

bios-temp.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C6000 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/bin/hex6x"  -o "bios-temp.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "global-resource-list.obj" "main.obj" "policy_dsp-only.obj" "rm_transport_setup.obj" "sample_osal.obj" 
	-$(RM) "global-resource-list.d" "main.d" "policy_dsp-only.d" "rm_transport_setup.d" "sample_osal.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

