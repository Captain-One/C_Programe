################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
yaffs2/%.obj: ../yaffs2/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" --include_path="D:/pxqwork/project/app-n/bios-yaffs2" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include" --include_path="C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages" --define=YAFFS_CURRENT --define=CONFIG_YAFFS_DIRECT --define=CONFIG_YAFFS_DEFINES_TYPES --define=CONFIG_YAFFS_PROVIDE_DEFS --define=CONFIG_YAFFSFS_PROVIDE_VALUES --define=CONFIG_YAFFS_YAFFS2 --define=SOC_K2H --define=DEVICE_K2H --define=evmK2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="yaffs2/$(basename $(<F)).d_raw" --obj_directory="yaffs2" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


