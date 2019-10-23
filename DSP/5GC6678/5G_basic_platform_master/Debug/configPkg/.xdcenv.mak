#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/pdk/6678/bios_6_75_02_00/packages;C:/ti/pdk/6678/pdk_c667x_2_0_13/packages;C:/ti/pdk/6678/ipc_3_50_03_04/packages;F:/myPlatform;C:/ti/pdk/6678/ndk_3_40_01_01/packages;C:/ti/pdk/6678/bios_6_75_02_00/packages/ti/posix/ccs
override XDCROOT = C:/ti/ccs901/xdctools_3_55_00_11_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/pdk/6678/bios_6_75_02_00/packages;C:/ti/pdk/6678/pdk_c667x_2_0_13/packages;C:/ti/pdk/6678/ipc_3_50_03_04/packages;F:/myPlatform;C:/ti/pdk/6678/ndk_3_40_01_01/packages;C:/ti/pdk/6678/bios_6_75_02_00/packages/ti/posix/ccs;C:/ti/ccs901/xdctools_3_55_00_11_core/packages;..
HOSTOS = Windows
endif
