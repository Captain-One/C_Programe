#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/platform/platform.h>

#define MAGIC_ADDR                      0x0087FFFC
#define BIN_FILE_START_ADDR             0x4000
#define NAND_BUS_WIDTH                  8
#define NAND_PAGE_SIZE                  512
#define NAND_ONE_BLOCK_PAGE_COUNT       32
#define NAND_BLOCK_SIZE                 NAND_PAGE_SIZE*NAND_ONE_BLOCK_PAGE_COUNT

#define X32(x)                          (((x) & 0x000000FF) << 24) | (((x) & 0x0000FF00) << 8) |\
                                        (((x) & 0x00FF0000) >> 8) | (((x) & 0xFF000000) >> 24)

typedef struct boottble{
    uint32_t    len;
    uint32_t    addr;
    uint8_t     data[0];
}Boot_table_s;


int Boot_Table_Parse(uint8_t *data_buf, uint32_t data_size)
{
    Boot_table_s *boot_table;

    boot_table = (Boot_table_s *)(data_buf);
    boot_table->len = X32(boot_table->len);
    boot_table->addr = X32(boot_table->addr);

    if(boot_table->len == 0){
        printf("read boot table over\n");
        return 0;
    }

    data_buf += 4;

    if((boot_table->len) < data_size)
    {
        memcpy((void *)boot_table->addr, (void *)data_buf, boot_table->len);
        data_buf += boot_table->len;
        data_size -= boot_table->len;
        if(Boot_Table_Parse(data_buf, data_size) == 0){
            return 0;
        }
    }else{
        memcpy((void *)boot_table->addr, (void *)data_buf, data_size);
        return 0;
    }
}

int Data_Parse(PLATFORM_DEVHANDLE handle)
{
    uint8_t *nand_data_buf;
    uint32_t c_int00_addr;
    Platform_STATUS status;
    uint32_t offset = 0;
    Boot_table_s  *boot_table;
    uint32_t remain_block_count;
    uint32_t remian_data_size;

    nand_data_buf = (uint8_t *)malloc(NAND_BLOCK_SIZE);
    if(nand_data_buf == NULL){
        printf("malloc nand_data_buf error\n");
        return -1;
    }

    status = platform_device_read(handle, BIN_FILE_START_ADDR + offset, nand_data_buf, NAND_BLOCK_SIZE);
    if(status != Platform_EOK){
       printf("platform_device_read Error: %d\n", status);
       return -1;
    }

    c_int00_addr = X32(*(uint32_t *)nand_data_buf);

    boot_table = (Boot_table_s *)(nand_data_buf + 4);
    boot_table->len = X32(boot_table->len);
    boot_table->addr = X32(boot_table->addr);

    remian_data_size = NAND_BLOCK_SIZE -12;

    if(boot_table->len < remian_data_size)
    {
        x

        boot_table = (Boot_table_s *)(nand_data_buf + boot_table->len);
        boot_table->len = X32(boot_table->len);
        boot_table->addr = X32(boot_table->addr);
    }

    if(boot_table->len > (NAND_BLOCK_SIZE - 12)){
        memcpy((void *)boot_table->addr, (void *)(nand_data_buf + 12), NAND_BLOCK_SIZE - 12);

        while(remain_block_count){
            status = platform_device_read(handle, BIN_FILE_START_ADDR + NAND_BLOCK_SIZE, nand_data_buf, NAND_BLOCK_SIZE);
            if(status != Platform_EOK){
               printf("platform_device_read Error: %d\n", status);
               return -1;
            }

            remain_block_count --;
        }

        memcpy((void *)boot_table->addr + NAND_BLOCK_SIZE - 12, (void *)nand_data_buf, NAND_BLOCK_SIZE - 12);
    }else{

    }

    remain_block_count = 1;
    if((boot_table->len + 12)/NAND_BLOCK_SIZE > 1){
        remain_block_count += (boot_table->len + 12)/NAND_BLOCK_SIZE + 1;
    }

 boot_table = (Boot_table_s *)malloc(sizeof(Boot_table_s) + boot_table->len);
    if(boot_table == NULL){
        printf("malloc boot table buf error\n");
        return -1;
    }

    return 0;
}

int main(void)
{
    Platform_STATUS status;
    platform_init_flags init_flag;
    platform_init_config init_config;
    platform_info  platform_info;
    CPU_info  *cpu_info;
    PLATFORM_DEVICE_info *device_info;
    //uint8_t nand_data_buf[1024] = {0};
    //int i;
    int re;

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
    printf("Open NAND device OK!\nDevice info:\n");
    printf("    Device ID: %u\n", device_info->device_id);
    printf("    Manufacturer ID: %u\n", device_info->manufacturer_id);
    printf("    Width: %u\n", device_info->width);
    printf("    Block Count: %d\n", device_info->block_count);
    printf("    Page Count: %d\n", device_info->page_count);
    printf("    Page Size: %d\n", device_info->page_size);
    printf("    Spare Size: %d\n", device_info->spare_size);


    re = Data_Parse(device_info->handle);
    if(re < 0){
        printf("Data_Parse error\n");
    }

    status = platform_device_close(device_info->handle);
    if(status != Platform_EOK){
        printf("platform_device_close Error: %d\n", status);
    }
    printf("platform_device_close OK!\n");


	return 0;
}
