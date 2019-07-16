vpath % C:/ti/pdk/6678/ipc_3_50_03_04/packages/
vpath %.c C:/ti/pdk/6678/xdctools_3_51_01_18_core/packages/

XOPTS = -I"C:/ti/pdk/6678/xdctools_3_51_01_18_core/packages/" -Dxdc_target_types__=C:/ti/pdk/6678/bios_6_73_01_01/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

CCOPTS = -mv6600 --abi=eabi -q --opt_for_speed=2 -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110 --mem_model:const=data --mem_model:data=far  --program_level_compile -o3 -g --optimize_with_debug 

IPC_ROOT = C:/ti/pdk/6678/ipc_3_50_03_04/packages/

BUILD_DEFS =  -Dti_sdo_ipc_MessageQ_traceFlag__D=FALSE -Dti_sdo_ipc_family_ti81xx_InterruptDucati_videoProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_hostProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_vpssProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_dspProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_ducatiCtrlBaseAddr__D=1073745920 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_mailboxBaseAddr__D=1208778752

INCS = -IC:/ti/pdk/6678/ipc_3_50_03_04/packages -IC:/ti/pdk/6678/bios_6_73_01_01/packages -IC:/ti/pdk/6678/pdk_c667x_2_0_13/packages -IC:/ti/pdk/6678/ndk_3_40_01_01/packages -IF:/myPlatform

CC = C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x -c $(CCOPTS) --output_file=$@ -I C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include
ASM = C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/cl6x -c $(CCOPTS) -I C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/include
AR = C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.2/bin/ar6x rq

DEL = cmd.exe /q /c del /f
CP = cmd.exe /q /c copy /Y
MKDIR = mkdir

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asme66 $< ...
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(INCS) $<
endef


all: ipc.ae66


Ipc.obj: ti/sdo/utils/NameServer.c ti/sdo/utils/NameServerRemoteNull.c ti/sdo/utils/MultiProc.c ti/sdo/utils/List.c ti/sdo/ipc/GateMP.c ti/sdo/ipc/MessageQ.c ti/sdo/ipc/SharedRegion.c ti/sdo/ipc/ListMP.c ti/sdo/ipc/Ipc.c ti/sdo/ipc/Notify.c ti/sdo/ipc/transports/TransportShm.c ti/sdo/ipc/transports/TransportShmSetup.c ti/sdo/ipc/notifyDrivers/NotifySetupNull.c ti/sdo/ipc/nsremote/NameServerRemoteNotify.c ti/sdo/ipc/heaps/HeapMemMP.c ti/sdo/ipc/gates/GateHWSem.c ti/sdo/ipc/gates/GatePeterson.c ti/sdo/ipc/gates/GateMPSupportNull.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(INCS) \
	$(IPC_ROOT)ti/sdo/utils/NameServer.c \
	$(IPC_ROOT)ti/sdo/utils/NameServerRemoteNull.c \
	$(IPC_ROOT)ti/sdo/utils/MultiProc.c \
	$(IPC_ROOT)ti/sdo/utils/List.c \
	$(IPC_ROOT)ti/sdo/ipc/GateMP.c \
	$(IPC_ROOT)ti/sdo/ipc/MessageQ.c \
	$(IPC_ROOT)ti/sdo/ipc/SharedRegion.c \
	$(IPC_ROOT)ti/sdo/ipc/ListMP.c \
	$(IPC_ROOT)ti/sdo/ipc/Ipc.c \
	$(IPC_ROOT)ti/sdo/ipc/Notify.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShm.c \
	$(IPC_ROOT)ti/sdo/ipc/transports/TransportShmSetup.c \
	$(IPC_ROOT)ti/sdo/ipc/notifyDrivers/NotifySetupNull.c \
	$(IPC_ROOT)ti/sdo/ipc/nsremote/NameServerRemoteNotify.c \
	$(IPC_ROOT)ti/sdo/ipc/heaps/HeapMemMP.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GateHWSem.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GatePeterson.c \
	$(IPC_ROOT)ti/sdo/ipc/gates/GateMPSupportNull.c

ipc.ae66: Ipc.obj 
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, ipc.ae66)
	@-$(call RM, Ipc.obj)
