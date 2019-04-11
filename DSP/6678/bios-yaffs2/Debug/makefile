################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"configPkg/linker.cmd"

ORDERED_OBJS += \
"./main.obj" \
"./platform_osal_function.obj" \
"./yaffs2/yaffs_allocator.obj" \
"./yaffs2/yaffs_attribs.obj" \
"./yaffs2/yaffs_bitmap.obj" \
"./yaffs2/yaffs_checkptrw.obj" \
"./yaffs2/yaffs_ecc.obj" \
"./yaffs2/yaffs_endian.obj" \
"./yaffs2/yaffs_error.obj" \
"./yaffs2/yaffs_guts.obj" \
"./yaffs2/yaffs_hweight.obj" \
"./yaffs2/yaffs_nameval.obj" \
"./yaffs2/yaffs_nand.obj" \
"./yaffs2/yaffs_nand_drv.obj" \
"./yaffs2/yaffs_nandsim_file.obj" \
"./yaffs2/yaffs_osglue.obj" \
"./yaffs2/yaffs_packedtags1.obj" \
"./yaffs2/yaffs_packedtags2.obj" \
"./yaffs2/yaffs_summary.obj" \
"./yaffs2/yaffs_tagscompat.obj" \
"./yaffs2/yaffs_tagsmarshall.obj" \
"./yaffs2/yaffs_verify.obj" \
"./yaffs2/yaffs_yaffs1.obj" \
"./yaffs2/yaffs_yaffs2.obj" \
"./yaffs2/yaffscfg2k.obj" \
"./yaffs2/yaffsfs.obj" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/platform/evmk2h/platform_lib/lib/release/ti.platform.evmk2h.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/csl/lib/k2h/c66/release/ti.csl.intc.ae66" \
-l"C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages/ti/csl/lib/k2h/c66/release/ti.csl.ae66" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include yaffs2/subdir_vars.mk
-include subdir_rules.mk
-include yaffs2/subdir_rules.mk
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
bios-yaffs2.out \

EXE_OUTPUTS__QUOTED += \
"bios-yaffs2.out" \

BIN_OUTPUTS += \
bios-yaffs2.hex \

BIN_OUTPUTS__QUOTED += \
"bios-yaffs2.hex" \


# All Target
all: $(OBJS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "bios-yaffs2.out"

# Tool invocations
bios-yaffs2.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" --define=YAFFS_CURRENT --define=CONFIG_YAFFS_DIRECT --define=CONFIG_YAFFS_DEFINES_TYPES --define=CONFIG_YAFFS_PROVIDE_DEFS --define=CONFIG_YAFFSFS_PROVIDE_VALUES --define=CONFIG_YAFFS_YAFFS2 --define=SOC_K2H --define=DEVICE_K2H --define=evmK2H -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"bios-yaffs2.map" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="bios-yaffs2_linkInfo.xml" --rom_model -o "bios-yaffs2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

bios-yaffs2.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C6000 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/hex6x"  -o "bios-yaffs2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "platform_osal_function.obj" "yaffs2\yaffs_allocator.obj" "yaffs2\yaffs_attribs.obj" "yaffs2\yaffs_bitmap.obj" "yaffs2\yaffs_checkptrw.obj" "yaffs2\yaffs_ecc.obj" "yaffs2\yaffs_endian.obj" "yaffs2\yaffs_error.obj" "yaffs2\yaffs_guts.obj" "yaffs2\yaffs_hweight.obj" "yaffs2\yaffs_nameval.obj" "yaffs2\yaffs_nand.obj" "yaffs2\yaffs_nand_drv.obj" "yaffs2\yaffs_nandsim_file.obj" "yaffs2\yaffs_osglue.obj" "yaffs2\yaffs_packedtags1.obj" "yaffs2\yaffs_packedtags2.obj" "yaffs2\yaffs_summary.obj" "yaffs2\yaffs_tagscompat.obj" "yaffs2\yaffs_tagsmarshall.obj" "yaffs2\yaffs_verify.obj" "yaffs2\yaffs_yaffs1.obj" "yaffs2\yaffs_yaffs2.obj" "yaffs2\yaffscfg2k.obj" "yaffs2\yaffsfs.obj" 
	-$(RM) "main.d" "platform_osal_function.d" "yaffs2\yaffs_allocator.d" "yaffs2\yaffs_attribs.d" "yaffs2\yaffs_bitmap.d" "yaffs2\yaffs_checkptrw.d" "yaffs2\yaffs_ecc.d" "yaffs2\yaffs_endian.d" "yaffs2\yaffs_error.d" "yaffs2\yaffs_guts.d" "yaffs2\yaffs_hweight.d" "yaffs2\yaffs_nameval.d" "yaffs2\yaffs_nand.d" "yaffs2\yaffs_nand_drv.d" "yaffs2\yaffs_nandsim_file.d" "yaffs2\yaffs_osglue.d" "yaffs2\yaffs_packedtags1.d" "yaffs2\yaffs_packedtags2.d" "yaffs2\yaffs_summary.d" "yaffs2\yaffs_tagscompat.d" "yaffs2\yaffs_tagsmarshall.d" "yaffs2\yaffs_verify.d" "yaffs2\yaffs_yaffs1.d" "yaffs2\yaffs_yaffs2.d" "yaffs2\yaffscfg2k.d" "yaffs2\yaffsfs.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

