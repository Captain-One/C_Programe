################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driver-interface/%.obj: ../driver-interface/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" --include_path="D:/pxqwork/project/app-n/basic-platform" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/include" --include_path="D:/pxqwork/project/app-n/basic-platform/init" --include_path="D:/pxqwork/project/app-n/basic-platform/driver-interface" --define=SOC_K2H --define=DEVICE_K2H --define=evm_K2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="driver-interface/$(basename $(<F)).d_raw" --obj_directory="driver-interface" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


