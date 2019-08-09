################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6600 --abi=eabi -O3 -ms3 --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --include_path="D:/pxqwork/project/5G-DSP/platform_lib_evmc6678l/include" --include_path="C:/ti/pdk/6678/pdk_c667x_2_0_13/packages" --include_path="C:/ti/pdk/6678/pdk_c667x_2_0_13/packages/ti/csl" --include_path="C:/ti/pdk/6678/pdk_c667x_2_0_13/packages/ti/platform" --define=SOC_C6678 -g --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


