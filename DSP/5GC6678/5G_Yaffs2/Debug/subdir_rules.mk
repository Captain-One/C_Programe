################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-390633537:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-390633537-inproc

build-390633537-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs901/xdctools_3_55_00_11_core/xs" --xdcpath="C:/ti/pdk/6678/bios_6_75_02_00/packages;C:/ti/pdk/6678/pdk_c667x_2_0_13/packages;C:/ti/pdk/6678/ipc_3_50_03_05/packages;C:/ti/pdk/6678/ndk_3_40_01_01/packages;F:/myPlatform;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p cyhc.dsp.core0 -r release -c "C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-390633537 ../app.cfg
configPkg/compiler.opt: build-390633537
configPkg/: build-390633537

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/5G-DSP/5G_Yaffs2" --include_path="C:/ti/pdk/6678/bios_6_75_02_00/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --define=YAFFS_CURRENT --define=CONFIG_YAFFS_DIRECT --define=CONFIG_YAFFS_DEFINES_TYPES --define=CONFIG_YAFFS_PROVIDE_DEFS --define=CONFIG_YAFFSFS_PROVIDE_VALUES --define=CONFIG_YAFFS_YAFFS2 --define=CONFIG_YAFFS_NO_YAFFS1 --define=SOC_C6678 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


