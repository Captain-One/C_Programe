vpath % C:/ti/sdk-k2h/ipc_3_50_03_04/packages/ti/sdo/
vpath %.c C:/ti/xdctools_3_51_01_18_core/packages/

XOPTS = -I"C:/ti/xdctools_3_51_01_18_core/packages/" -Dxdc_target_types__=C:/ti/sdk-k2h/bios_6_73_01_01/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

CCOPTS = -mv6600 --abi=eabi -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110  --program_level_compile -o3 -g  -Dti_sysbios_family_c64p_Exception_enableExternalMPC__D=FALSE -Dti_sysbios_family_c64p_Exception_enablePrint__D=TRUE -Dti_sysbios_knl_Clock_stopCheckNext__D=FALSE -Dti_sysbios_knl_Task_minimizeLatency__D=FALSE

XDC_ROOT  = C:/ti/xdctools_3_51_01_18_core/packages/

IPC_ROOT = C:/ti/sdk-k2h/ipc_3_50_03_04/packages/ti/sdo/

BUILD_DEFS = 

SYSBIOS_INC  = -I"C:/ti/sdk-k2h/bios_6_73_01_01/packages"

IPC_INC    = -I"C:/ti/sdk-k2h/ipc_3_50_03_04/packages"

UTILS_INC    = -I"C:/ti/sdk-k2h/ipc_3_50_03_04/packages"

CC = C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x -c $(CCOPTS) -I C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include
ASM = C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x -c $(CCOPTS) -I C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/include
AR = C:/ti/ccsv8/tools/compiler/ti-cgt-c6000_8.3.3/bin/ar6x rq

DEL = cmd.exe /q /c del /f
CP = cmd.exe /q /c copy /Y
MKDIR = mkdir

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asme66 $< ...
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(UTILS_INC) $<
endef


all: utils.ae66


UTILS.obj: utils/UTILS.c utils/NameServer.c utils/NameServerRemoteNull.c utils/MultiProc.c utils/List.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(SYSBIOS_INC) \
	$(IPC_INC) $(UTILS_INC) \
	$(IPC_ROOT)utils/UTILS.c \
	$(IPC_ROOT)utils/NameServer.c \
	$(IPC_ROOT)utils/NameServerRemoteNull.c \
	$(IPC_ROOT)utils/MultiProc.c \
	$(IPC_ROOT)utils/List.c \

utils.ae66: UTILS.obj 
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, utils.ae66)
	@-$(call RM, UTILS.obj)
