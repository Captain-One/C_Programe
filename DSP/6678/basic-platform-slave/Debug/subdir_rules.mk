################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-813657793:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-813657793-inproc

build-813657793-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_51_01_18_core/xs" --xdcpath="C:/ti/sdk-k2h/bios_6_73_01_01/packages;C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages;C:/ti/sdk-k2h/ndk_3_40_01_01/packages;C:/ti/sdk-k2h/ipc_3_50_03_04/packages;F:/myPlatform;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p cyhc.dsp.core1 -r release -c "C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-813657793 ../app.cfg
configPkg/compiler.opt: build-813657793
configPkg/: build-813657793

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" --include_path="D:/pxqwork/project/app-n/basic-platform-slave" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include" --define=SOC_K2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


