################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
UTIL/MEM/%.obj: ../UTIL/MEM/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x" -mv6600 --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master" --include_path="C:/ti/pdk/6678/bios_6_75_02_00/packages/ti/posix/ccs" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/init" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/driver-interface" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/common" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/utils" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/yaffs2" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/UTIL" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/UTIL/hashtable" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/UTIL/LISTS" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/UTIL/MEM" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/simulate" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2/MAC" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2/PDCP" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2/RLC" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2/RLC/AM" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2/RLC/TM" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER2/RLC/UM" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER3" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER3/RRC/MESSAGE" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER3/RRC" --include_path="D:/pxqwork/project/5G-DSP/5G_basic_platform_master/LAYER3/RRC/MESSAGE/asn1c" --define=SOC_C6678 --define=YAFFS_CURRENT --define=CONFIG_YAFFS_DIRECT --define=CONFIG_YAFFS_DEFINES_TYPES --define=CONFIG_YAFFS_PROVIDE_DEFS --define=CONFIG_YAFFSFS_PROVIDE_VALUES --define=CONFIG_YAFFS_YAFFS2 --define=CONFIG_YAFFS_NO_YAFFS1 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="UTIL/MEM/$(basename $(<F)).d_raw" --obj_directory="UTIL/MEM" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


