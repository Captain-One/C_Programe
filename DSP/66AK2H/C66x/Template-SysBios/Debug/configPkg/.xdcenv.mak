#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/sdk-k2h/bios_6_73_01_01/packages;C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages;F:/myPlatform;C:/ti/sdk-k2h/ipc_3_50_03_04/packages
override XDCROOT = C:/ti/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/sdk-k2h/bios_6_73_01_01/packages;C:/ti/sdk-k2h/pdk_k2hk_4_0_12/packages;F:/myPlatform;C:/ti/sdk-k2h/ipc_3_50_03_04/packages;C:/ti/xdctools_3_51_01_18_core/packages;..
HOSTOS = Windows
endif
