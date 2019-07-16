################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
common/%.obj: ../common/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master" --include_path="C:/ti/pdk/6678/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/init" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/driver-interface" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/common" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/utils" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/yaffs2" --define=SOC_C6678 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="common/$(basename $(<F)).d_raw" --obj_directory="common" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


