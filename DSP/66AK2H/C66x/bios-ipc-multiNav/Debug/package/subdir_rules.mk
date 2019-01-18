################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
package/%.obj: ../package/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/app-n/bios-ipc-multiNav" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/include" --define=DEVICE_K2H --define=SOC_K2H --define=evmK2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="package/$(basename $(<F)).d_raw" --obj_directory="package" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


