################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-19138785:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-19138785-inproc

build-19138785-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_51_01_18_core/xs" --xdcpath="C:/ti/sdk-k2h/bios_6_73_01_01/packages;C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages;F:/myPlatform;C:/ti/sdk-k2h/ipc_3_50_03_04/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p cyhc.k2h.myboard -r release -c "C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-19138785 ../app.cfg
configPkg/compiler.opt: build-19138785
configPkg/: build-19138785

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/bin/cl6x" -mv6500 --include_path="D:/pxqwork/project/app-n/bios-temp" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/include" --include_path="C:/ti/sdk-k2h/ipc_3_50_03_04/packages" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages" --define=evmK2H --define=SOC_K2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


