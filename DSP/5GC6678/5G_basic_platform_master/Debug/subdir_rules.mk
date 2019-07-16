################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-923553535:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-923553535-inproc

build-923553535-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/pdk/6678/xdctools_3_51_01_18_core/xs" --xdcpath="C:/ti/pdk/6678/bios_6_73_01_01/packages;C:/ti/pdk/6678/pdk_c667x_2_0_13/packages;C:/ti/pdk/6678/ipc_3_50_03_04/packages;C:/ti/pdk/6678/ndk_3_40_01_01/packages;F:/myPlatform;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p cyhc.dsp.core0 -r release -c "C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2" --compileOptions "-g" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-923553535 ../app.cfg
configPkg/compiler.opt: build-923553535
configPkg/: build-923553535

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master" --include_path="C:/ti/pdk/6678/bios_6_73_01_01/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/init" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/driver-interface" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/common" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/utils" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/yaffs2" --define=SOC_C6678 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


