################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/app-n/SBL" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include" --include_path="F:/66AK2H-EVM/pdk/mcsdk2.1/pdk_C6670_1_1_2_6/packages" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


