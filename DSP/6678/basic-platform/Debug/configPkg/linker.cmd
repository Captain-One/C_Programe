/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.targets.elf package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"D:\pxqwork\project\app-n\basic-platform\Debug\configPkg\package\cfg\app_pe66.oe66"
-l"D:\pxqwork\project\app-n\basic-platform\src\ipc\ipc.ae66"
-l"D:\pxqwork\project\app-n\basic-platform\src\utils\utils.ae66"
-l"D:\pxqwork\project\app-n\basic-platform\src\sysbios\sysbios.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\csl\lib\k2h\c66\release\ti.csl.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\csl\lib\k2h\c66\release\ti.csl.intc.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\drv\uart\lib\c66\release\ti.drv.uart.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\drv\rm\lib\c66\ti.drv.rm.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\drv\srio\lib\c66\ti.drv.srio.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\drv\qmss\lib\c66\ti.drv.qmss.ae66"
-l"C:\ti\sdk-k2h\pdk_k2hk_4_0_12\packages\ti\drv\cppi\lib\c66\ti.drv.cppi.ae66"
-l"C:\ti\sdk-k2h\bios_6_73_01_01\packages\ti\targets\rts6000\lib\ti.targets.rts6000.ae66"
-l"C:\ti\sdk-k2h\bios_6_73_01_01\packages\ti\targets\rts6000\lib\boot.ae66"

--retain="*(xdc.meta)"


--args 0x0
-heap  0x0
-stack 0x2000

MEMORY
{
    L2SRAM (RWX) : org = 0x800000, len = 0x80000
    MSMCSRAM (RWX) : org = 0xc000000, len = 0x400000
    DDR (RWX) : org = 0x80000000, len = 0x8000000
}

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.elf (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from ti.targets.rts6000 (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from xdc.services.getset (null): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.sdo.ipc.interfaces (null): */

/* Content from ti.sdo.ipc.family (null): */

/* Content from ti.drv.cppi (null): */

/* Content from ti.drv.qmss (null): */

/* Content from ti.drv.srio (null): */

/* Content from ti.drv.rm (null): */

/* Content from ti.drv.uart (null): */

/* Content from ti.csl (null): */

/* Content from ti.sysbios.family.c62 (null): */

/* Content from ti.sysbios.family.c64p.tci6488 (null): */

/* Content from ti.catalog.c6000 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.platforms.generic (null): */

/* Content from cyhc.dsp.core0 (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios (null): */

/* Content from ti.sysbios.rts (ti/sysbios/rts/linkcmd.xdt): */

/* Content from ti.sysbios.rts.ti (ti/sysbios/rts/ti/linkcmd.xdt): */

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios.timers.timer64 (null): */

/* Content from ti.sysbios.family.c64p (ti/sysbios/family/c64p/linkcmd.xdt): */

/* Content from ti.sysbios.family.c66 (ti/sysbios/family/c66/linkcmd.xdt): */
ti_sysbios_family_c66_Cache_l1dSize = 32768;
ti_sysbios_family_c66_Cache_l1pSize = 32768;
ti_sysbios_family_c66_Cache_l2Size = 0;

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sdo.utils (null): */

/* Content from ti.sysbios.syncs (null): */

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from ti.sdo.ipc.notifyDrivers (null): */

/* Content from ti.sdo.ipc.gates (null): */

/* Content from ti.sdo.ipc (ti/sdo/ipc/linkcmd.xdt): */

SECTIONS
{
    ti.sdo.ipc.SharedRegion_0:  { . += 0x20000;} run > 0xc000000, type = NOLOAD
}

/* Content from ti.sdo.ipc.transports (null): */

/* Content from ti.sdo.ipc.family.c647x (null): */

/* Content from ti.sdo.ipc.nsremote (null): */

/* Content from ti.sdo.ipc.heaps (null): */

/* Content from configPkg (null): */

/* Content from xdc.services.io (null): */

/* Content from ti.sdo.ipc.family.ti81xx (null): */

/* Content from ti.ipc.remoteproc (ti/ipc/remoteproc/linkcmd.xdt): */




/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;

SECTIONS
{
    .text: load >> DDR
    .ti.decompress: load > DDR
    .stack: load > L2SRAM
    GROUP: load > DDR
    {
        .bss:
        .neardata:
        .rodata:
    }
    .cinit: load > DDR
    .pinit: load >> DDR
    .init_array: load > DDR
    .const: load >> DDR
    .data: load >> DDR
    .fardata: load >> DDR
    .switch: load >> DDR
    .sysmem: load > DDR
    .far: load >> DDR
    .args: load > DDR align = 0x4, fill = 0 {_argsize = 0x0; }
    .cio: load >> DDR
    .ti.handler_table: load > DDR
    .c6xabi.exidx: load > DDR
    .c6xabi.extab: load >> DDR
    .qmss: load > MSMCSRAM
    .cppi: load > MSMCSRAM
    .vecs: load > DDR
    xdc.meta: load > DDR, type = COPY

}
