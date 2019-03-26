#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/platform/platform.h>

int main(void)
{
    Platform_STATUS status;
    platform_init_flags init_flag;
    platform_init_config init_config;
    platform_info  platform_info;
    CPU_info  *cpu_info;
    PLATFORM_DEVICE_info *device_info;
    uint8_t nand_data_buf[1024] = {0};
    int i;

    memset(&platform_info, 0, sizeof(platform_info));

    init_flag.pll = 1;
    init_flag.ddr = 1;
    init_flag.phy = 1;
    init_flag.ecc = 1;
    init_flag.tcsl = 0;

    init_config.plld = 0;
    init_config.pllm = 0;
    init_config.postdiv = 0;
    init_config.prediv = 0;

    status = platform_init(&init_flag, &init_config);
    if(status != Platform_EOK){
        printf("platform_init Error: %d\n", status);
    }
    printf("platform_init OK!\n");

    platform_get_info(&platform_info);
    cpu_info = &platform_info.cpu;

    printf("/************platform info************/\n");
    printf("board name: %s\n", platform_info.board_name);
    printf("board rev: %u\n", platform_info.board_rev);
    printf("platform lib version: %s\n", platform_info.version);
    printf("frequency: %u\n", platform_info.frequency);
    printf("CPU info:\n    core count: %u\n    cpu revision ID: %u\n", cpu_info->core_count, cpu_info->revision_id);
    printf("    Major Megamodule Revision ID: %u\n    Minor Megamodule Revision ID: %u\n", cpu_info->megamodule_revision_major, cpu_info->megamodule_revision_minor);
    printf("    Major Silicon Revision ID: %u\n    Minor Silicon Revision ID: %u\n", cpu_info->silicon_revision_major, cpu_info->silicon_revision_minor);
    if(cpu_info->endian == PLATFORM_LE){
        printf("    Endian: LE\n");
    }else{
        printf("    Endian: BE\n");
    }
    printf("/************************************/\n");

    device_info = platform_device_open(PLATFORM_DEVID_NAND512R3A2D, 0);
    if(device_info == NULL){
        printf("Open NAND device Error\n");
        return 0;
    }
    printf("Open NAND device OK!\n");

    status = platform_device_read(device_info->handle, 16384, nand_data_buf, 1024);
    if(status != Platform_EOK){
       printf("platform_device_read Error: %d\n", status);
    }
    printf("platform_device_read OK!\n");

    for(i = 1; i <= 1024; i++)
    {
        printf("0x%2x ",nand_data_buf[i-1]);
        if(i%16 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");

    status = platform_device_close(device_info->handle);
    if(status != Platform_EOK){
        printf("platform_device_close Error: %d\n", status);
    }
    printf("platform_device_close OK!\n");


	return 0;
}
