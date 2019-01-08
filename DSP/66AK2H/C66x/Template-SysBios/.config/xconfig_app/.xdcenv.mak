#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_73_00_12/packages;C:/ti/pdk_k2hk_4_0_11/packages;C:/ti/uia_2_30_01_02/packages;D:/pxqwork/project/app-n/platforms;D:/pxqwork/project/app-n/bios-temp/.config
override XDCROOT = C:/ti/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_73_00_12/packages;C:/ti/pdk_k2hk_4_0_11/packages;C:/ti/uia_2_30_01_02/packages;D:/pxqwork/project/app-n/platforms;D:/pxqwork/project/app-n/bios-temp/.config;C:/ti/xdctools_3_51_01_18_core/packages;..
HOSTOS = Windows
endif
