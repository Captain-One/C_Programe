#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/platform/platform.h>
#include <ti/csl/csl_bootcfgAux.h>

#define MAGIC_ADDR                      0x0087FFFC
#define BIN_FILE_START_ADDR             0x4000
#define NAND_BUS_WIDTH                  8
#define NAND_PAGE_SIZE                  512
#define NAND_ONE_BLOCK_PAGE_COUNT       32
#define NAND_BLOCK_SIZE                 NAND_PAGE_SIZE*NAND_ONE_BLOCK_PAGE_COUNT

#define BOOT_TABLE_OK                   -1
#define CORE_NUM                        8

#define X32(x)                          (((x) & 0x000000FF) << 24) | (((x) & 0x0000FF00) << 8) |\
                                        (((x) & 0x00FF0000) >> 8) | (((x) & 0xFF000000) >> 24)

typedef struct boottble{
    uint32_t    len;
    uint32_t    addr;
    uint8_t     data[0];
}Boot_table_s;

typedef struct core_info{
    uint32_t    file_size;
    uint32_t    entry_point;
}Core_info_s;

typedef struct my_boot_head{
    uint32_t   all_size;
    uint32_t    core_count;
    Core_info_s core_info[0];
}My_Boot_Head_s;

My_Boot_Head_s *my_boot_head;

int ext_buf_flag = 0;
uint8_t ext_buf[8] = {0};
uint32_t Magic_Addr[8] = {0x108FFFFC, 0x118FFFFC, 0x128FFFFC, 0x138FFFFC, 0x148FFFFC, 0x158FFFFC, 0x168FFFFC, 0x178FFFFC};
uint32_t IPCGR[8] = {0x02620240, 0x02620244, 0x02620248, 0x0262024C, 0x02620250, 0x02620254, 0x02620258, 0x0262025C};

int Boot_Table_Parse(uint8_t *data_buf, int data_size, int *const isheader, int *const remain_section_size)
{
    Boot_table_s *boot_table;
    int section_size;
    int copy_size;
    int boot_table_head_size;
    int i;


    if(*isheader){
        if(data_size <= 8){
            for(i = 0; i < data_size; i++){
                ext_buf[i] = data_buf[NAND_BLOCK_SIZE - data_size + i];
            }
            ext_buf_flag = data_size;
            return 0;
        }

        if(ext_buf_flag){
            for(i = 0; i < (8 - ext_buf_flag); i++){
                ext_buf[ext_buf_flag + i] = data_buf[i];
            }
            boot_table = (Boot_table_s *)(ext_buf);
            data_buf += (8 - ext_buf_flag);
            boot_table_head_size = 8 - ext_buf_flag;
            ext_buf_flag = 0;
        }else{
            boot_table = (Boot_table_s *)(data_buf);
            data_buf += 8;
            boot_table_head_size = 8;
        }

        //boot_table->len = X32(boot_table->len);
        //boot_table->addr = X32(boot_table->addr);
        if(boot_table->len == 0){
            printf("read boot table over\n");
            return BOOT_TABLE_OK;
        }
        section_size = boot_table->len;
        if((section_size%4) != 0)
        {
            section_size += section_size%4;
        }
    }else{
        boot_table_head_size = 0;
        section_size = *remain_section_size;
    }

    data_size -= boot_table_head_size;

    if(section_size <= data_size)
    {
        memcpy((void *)boot_table->addr, (void *)data_buf, section_size);
        copy_size = section_size;
        *isheader = 1;
    }else{
        memcpy((void *)boot_table->addr, (void *)data_buf, data_size);
        copy_size = data_size;
        *remain_section_size = section_size - copy_size;
        *isheader = 0;
    }

    return copy_size + boot_table_head_size;
}

int Data_Parse(PLATFORM_DEVHANDLE handle)
{
    uint8_t *nand_data_buf;
    Platform_STATUS status;
    uint32_t offset = 0;
    int read_block_count = 0;
    int remian_data_size;
    int remain_section_size;
    int isheader;
    int data_copy_size = 0;;
    int total_copy_size = 0;
    int core_count;
    //int all_file_len;
    int i;

    nand_data_buf = (uint8_t *)malloc(NAND_BLOCK_SIZE + 8);
    if(nand_data_buf == NULL){
        printf("malloc nand_data_buf error\n");
        return -1;
    }

    status = platform_device_read(handle, BIN_FILE_START_ADDR + read_block_count * NAND_BLOCK_SIZE, nand_data_buf, NAND_BLOCK_SIZE);
    if(status != Platform_EOK){
       printf("platform_device_read Error: %d\n", status);
       return -1;
    }

    remian_data_size = NAND_BLOCK_SIZE;
    my_boot_head = (My_Boot_Head_s *)nand_data_buf;
    core_count = my_boot_head->core_count;

    my_boot_head = (My_Boot_Head_s *)malloc(sizeof(My_Boot_Head_s) + core_count * sizeof(Core_info_s));
    if(my_boot_head == NULL){
        printf("malloc my_boot_head error\n");
        return -1;
    }

    my_boot_head->all_size =  ((My_Boot_Head_s *)nand_data_buf)->all_size;
    my_boot_head->core_count = ((My_Boot_Head_s *)nand_data_buf)->core_count;
    for(i = 0; i < my_boot_head->core_count; i++)
    {
        my_boot_head->core_info[i].file_size = ((My_Boot_Head_s *)nand_data_buf)->core_info[i].file_size;
        my_boot_head->core_info[i].entry_point = ((My_Boot_Head_s *)nand_data_buf)->core_info[i].entry_point;
    }

    offset = sizeof(My_Boot_Head_s) + sizeof(Core_info_s) * (my_boot_head->core_count);
    read_block_count = 1;
    remain_section_size = 0;
    isheader = 1;
    remian_data_size -= offset;

    do
    {
        data_copy_size = Boot_Table_Parse(nand_data_buf + offset, remian_data_size, &isheader, &remain_section_size);
        offset += data_copy_size;
        remian_data_size -= data_copy_size;
        total_copy_size += data_copy_size;
        if((!isheader) || (offset == NAND_BLOCK_SIZE))
        {
            status = platform_device_read(handle, BIN_FILE_START_ADDR + read_block_count * NAND_BLOCK_SIZE, nand_data_buf, NAND_BLOCK_SIZE);
            if(status != Platform_EOK){
               printf("platform_device_read Error: %d\n", status);
               return -1;
            }
            read_block_count ++;
            remian_data_size = NAND_BLOCK_SIZE;
            offset = 0;
        }
    }while(data_copy_size != BOOT_TABLE_OK);

    free(nand_data_buf);
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

    int re;
    int i;
    void   (*exit)();
    uint32_t * maigic_addr;
    uint32_t * ipgr_reg;

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

    CSL_BootCfgUnlockKicker();

    for(i = 1; i < my_boot_head->core_count; i++){

        CSL_BootCfgSetDSPBootAddress(i, my_boot_head->core_info[i].entry_point);
       // maigic_addr =  (uint32_t *)(Magic_Addr[i]);
        //*maigic_addr = X32();
        CSL_BootCfgGenerateInterDSPInterrupt(i,1);
        //ipgr_reg = (uint32_t *)(IPCGR[i]);
        //*ipgr_reg = (*ipgr_reg) | 0x00000001;
        platform_delay(100000);
    }

    CSL_BootCfgLockKicker();

    exit = (void (*)())(my_boot_head->core_info[0].entry_point);
    (*exit)();
	return 0;
}
