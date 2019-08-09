#
_XDCBUILDCOUNT = 1
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/pdk/6678/libarch_1_0_0_0/packages;C:/ti/pdk/6678/xdais_7_24_00_04/packages;C:/ti/pdk/6678/xdais_7_24_00_04/examples;C:/ti/pdk/6678/ctoolslib_2_2_0_0/packages;C:/ti/pdk/6678/bios_6_75_02_00/packages;C:/ti/pdk/6678/ndk_3_40_01_01/packages;C:/ti/pdk/6678/linalg_1_2_0_0/packages;C:/ti/pdk/6678/edma3_lld_2_12_05_30D/packages;C:/ti/pdk/6678/openmp_dsp_c667x_2_06_03_00/packages;C:/ti/pdk/6678/pdk_c667x_2_0_13/packages;C:/ti/pdk/6678/imglib_c66x_3_1_1_0/packages;C:/ti/pdk/6678/framework_components_3_40_02_07/packages;C:/ti/pdk/6678/framework_components_3_40_02_07/examples;C:/ti/pdk/6678/ipc_3_50_03_05/packages;C:/ti/pdk/6678/uia_2_30_01_02/packages;C:/ti/ccs901/xdctools_3_55_00_11_core/packages
override XDCROOT = C:/ti/ccs901/xdctools_3_55_00_11_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/pdk/6678/libarch_1_0_0_0/packages;C:/ti/pdk/6678/xdais_7_24_00_04/packages;C:/ti/pdk/6678/xdais_7_24_00_04/examples;C:/ti/pdk/6678/ctoolslib_2_2_0_0/packages;C:/ti/pdk/6678/bios_6_75_02_00/packages;C:/ti/pdk/6678/ndk_3_40_01_01/packages;C:/ti/pdk/6678/linalg_1_2_0_0/packages;C:/ti/pdk/6678/edma3_lld_2_12_05_30D/packages;C:/ti/pdk/6678/openmp_dsp_c667x_2_06_03_00/packages;C:/ti/pdk/6678/pdk_c667x_2_0_13/packages;C:/ti/pdk/6678/imglib_c66x_3_1_1_0/packages;C:/ti/pdk/6678/framework_components_3_40_02_07/packages;C:/ti/pdk/6678/framework_components_3_40_02_07/examples;C:/ti/pdk/6678/ipc_3_50_03_05/packages;C:/ti/pdk/6678/uia_2_30_01_02/packages;C:/ti/ccs901/xdctools_3_55_00_11_core/packages;C:/ti/ccs901/xdctools_3_55_00_11_core/packages;../../..
HOSTOS = Windows
endif
