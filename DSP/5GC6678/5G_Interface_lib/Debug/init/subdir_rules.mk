################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
init/%.obj: ../init/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/5G-DSP/5G_Interface_lib" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --include_path="C:/ti/pdk/6678/pdk_c667x_2_0_13/packages" --include_path="D:/pxqwork/project/5G-DSP/5G_Interface_lib/common" --include_path="D:/pxqwork/project/5G-DSP/5G_Interface_lib/driver-interface" --include_path="D:/pxqwork/project/5G-DSP/5G_Interface_lib/init" --include_path="C:/ti/ccs901/xdctools_3_55_00_11_core/packages" --include_path="yaffs2" --define=SOC_C6678 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="init/$(basename $(<F)).d_raw" --obj_directory="init" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


