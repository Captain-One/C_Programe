################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-861293679:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-861293679-inproc

build-861293679-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_50_08_24_core/xs" --xdcpath="C:/ti/BIOS_Install/bios_6_73_01_01/packages;C:/ti/ipc_3_50_02_02/packages;C:/ti/66ak-rtos-sdk/pdk_k2hk_4_0_11/packages;D:/pxqwork/project/app-n/platforms;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.platform.myBoard -r release -c "C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-861293679 ../app.cfg
configPkg/compiler.opt: build-861293679
configPkg/: build-861293679

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/bin/cl6x" --include_path="D:/pxqwork/project/app-n/Template-SysBios" --include_path="C:/ti/BIOS_Install/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.1/include" --define=SOC_K2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


