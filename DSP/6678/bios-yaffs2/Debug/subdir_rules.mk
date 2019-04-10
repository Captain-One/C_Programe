################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-654660399:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-654660399-inproc

build-654660399-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_51_01_18_core/xs" --xdcpath="C:/ti/sdk-k2h/bios_6_73_01_01/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.platforms.evm6670 -r release -c "C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-654660399 ../app.cfg
configPkg/compiler.opt: build-654660399
configPkg/: build-654660399

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" --include_path="D:/pxqwork/project/app-n/bios-yaffs2" --include_path="C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include" --include_path="C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages" --define=YAFFS_CURRENT --define=CONFIG_YAFFS_DIRECT --define=CONFIG_YAFFS_DEFINES_TYPES --define=CONFIG_YAFFS_PROVIDE_DEFS --define=CONFIG_YAFFSFS_PROVIDE_VALUES --define=SOC_K2H --define=DEVICE_K2H -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


