
-c
-heap  0x41000
-stack 0xa000

/* Memory Map 1 - the default */
MEMORY
{
    L1PSRAM (RWX)  : org = 0x0E00000, len = 0x7FFF
    L1DSRAM (RWX)  : org = 0x0F00000, len = 0x7FFF

    L2SRAM (RWX)   : org = 0x10800000, len = 0x100000
    MSMCSRAM (RWX) : org = 0xc000000, len = 0x200000
    DDR3 (RWX)     : org = 0x9C000000,len = 0x4000000
}

SECTIONS
{
    .csl_vect   >       DDR3
    .text       >       DDR3
    GROUP (NEAR_DP)
    {
    .neardata
    .rodata
    .bss
    } load > DDR3
    .stack      >       L2SRAM
    .cinit      >       DDR3
    .cio        >       L2SRAM
    .const      >       DDR3
    .data       >       DDR3
    .switch     >       DDR3
    .sysmem     >       DDR3
    .far        >       DDR3
    .testMem    >       DDR3
    .fardata    >       DDR3
    platform_lib > 		DDR3
    .ddr		>       DDR3
}
