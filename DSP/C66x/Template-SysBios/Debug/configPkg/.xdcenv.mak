#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/BIOS_Install/bios_6_73_01_01/packages;C:/ti/ipc_3_50_02_02/packages;C:/ti/66ak-rtos-sdk/pdk_k2hk_4_0_11/packages;D:/pxqwork/project/app-n/platforms
override XDCROOT = C:/ti/xdctools_3_50_08_24_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/BIOS_Install/bios_6_73_01_01/packages;C:/ti/ipc_3_50_02_02/packages;C:/ti/66ak-rtos-sdk/pdk_k2hk_4_0_11/packages;D:/pxqwork/project/app-n/platforms;C:/ti/xdctools_3_50_08_24_core/packages;..
HOSTOS = Windows
endif
