#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/platform/platform.h>
//#include <ti/board/src/flash/include/platform.h>
#include <ti/csl/csl_bootcfgAux.h>
#include <ti/csl/csl_ipcAux.h>
#include <ti/csl/csl_cacheAux.h>

#define MAGIC_ADDR                      0x0087FFFC
#define BIN_FILE_START_ADDR             0x0000
#define NAND_BUS_WIDTH                  8
#define NAND_PAGE_SIZE                  2048
#define NAND_ONE_BLOCK_PAGE_COUNT       64
#define NAND_BLOCK_SIZE                 NAND_PAGE_SIZE*NAND_ONE_BLOCK_PAGE_COUNT

#define BOOT_TABLE_OK                   -1
#define CORE_NUM                        8

#define X32(x)                          (((x) & 0x000000FF) << 24) | (((x) & 0x0000FF00) << 8) |\
                                        (((x) & 0x00FF0000) >> 8) | (((x) & 0xFF000000) >> 24)

#define ALIGN(x, a)                     (((x) + ((a) - 1)) & (~((a) - 1)))


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

Boot_table_s boot_table;

int ext_buf_flag = 0;
uint8_t ext_buf[8] = {0};


void Copy_To_DDR(void *dst, void *src, int len)
{
    int i;
    uint8_t *i_dst = (uint8_t *)dst;
    uint8_t *i_src = (uint8_t *)src;

    for(i = 0; i < len; i++)
    {
        i_dst[i] = i_src[i];
    }
    CACHE_wbL1d ((void *)i_dst, len, CACHE_WAIT);
}


int Boot_Table_Parse(uint8_t *data_buf, int data_size, int *const isheader, int *const remain_section_size)
{
    int section_size;
    int copy_size;
    int boot_table_head_size;
    int i;
    uint32_t *dst_addr;

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
            boot_table.addr = ((Boot_table_s *)ext_buf)->addr;
            boot_table.len = ((Boot_table_s *)ext_buf)->len;
            data_buf += (8 - ext_buf_flag);
            boot_table_head_size = 8 - ext_buf_flag;
            ext_buf_flag = 0;
        }else{
            boot_table.addr = ((Boot_table_s *)data_buf)->addr;
            boot_table.len = ((Boot_table_s *)data_buf)->len;
            data_buf += 8;
            boot_table_head_size = 8;
        }

        if(boot_table.len == 0){
            platform_write("read boot table over\n");
            return BOOT_TABLE_OK;
        }
        section_size = ALIGN(boot_table.len, 4);

    }else{
        boot_table_head_size = 0;
        section_size = *remain_section_size;
    }

    data_size -= boot_table_head_size;
    dst_addr = (uint32_t *)(boot_table.addr + (boot_table.len - section_size));

    if(section_size <= data_size)
    {

        memcpy((void *)dst_addr, (void *)data_buf, section_size);
        //CACHE_wbL1d ((void *)dst_addr, section_size, CACHE_WAIT);
#if 0
        Copy_To_DDR((void *)dst_addr, (void *)data_buf, section_size);
#endif
        copy_size = section_size;
        *isheader = 1;
    }else{
        memcpy((void *)dst_addr, (void *)data_buf, data_size);
        //CACHE_wbL1d ((void *)dst_addr, data_size, CACHE_WAIT);
#if 0
        Copy_To_DDR((void *)dst_addr, (void *)data_buf, data_size);
#endif
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

    nand_data_buf = (uint8_t *)malloc(NAND_BLOCK_SIZE + 512);
    if(nand_data_buf == NULL){
        platform_write("malloc nand_data_buf error\n");
        return -1;
    }

    status = platform_device_read(handle, BIN_FILE_START_ADDR + read_block_count * NAND_BLOCK_SIZE, nand_data_buf, NAND_BLOCK_SIZE);
    if(status != Platform_EOK){
        platform_write("platform_device_read Error: %d\n", status);
       return -1;
    }

    remian_data_size = NAND_BLOCK_SIZE;
    my_boot_head = (My_Boot_Head_s *)nand_data_buf;
    core_count = my_boot_head->core_count;

    my_boot_head = (My_Boot_Head_s *)malloc(sizeof(My_Boot_Head_s) + core_count * sizeof(Core_info_s));
    if(my_boot_head == NULL){
        platform_write("malloc my_boot_head error\n");
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
                platform_write("platform_device_read Error: %d\n", status);
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
    WRITE_info print_write_type;

    int re;
    int i;
    void   (*exit)();
    uint32_t * maigic_addr;


    memset(&platform_info, 0, sizeof(platform_info));

    init_flag.pll = 1;
    init_flag.ddr = 1;
    init_flag.phy = 0;
    init_flag.ecc = 1;
    init_flag.tcsl = 0;

    init_config.plld = 0;
    init_config.pllm = 0;
    init_config.postdiv = 0;
    init_config.prediv = 0;

    status = platform_init(&init_flag, &init_config);
    if(status != Platform_EOK){
        return -1;
    }

    status = platform_uart_init();
    if(status != Platform_EOK){
       return -2;
    }

    print_write_type = PLATFORM_WRITE_UART;
    print_write_type = platform_write_configure (print_write_type);
    if(print_write_type != PLATFORM_WRITE_UART){
        return -3;
    }

    platform_write("platform_init OK!\n");

    platform_get_info(&platform_info);
    cpu_info = &platform_info.cpu;

    platform_write("/************platform info************/\n");
    platform_write("board name: %s\n", platform_info.board_name);
    platform_write("board rev: %u\n", platform_info.board_rev);
    platform_write("platform lib version: %s\n", platform_info.version);
    platform_write("frequency: %u\n", platform_info.frequency);
    platform_write("CPU info:\n    core count: %u\n    cpu revision ID: %u\n", cpu_info->core_count, cpu_info->revision_id);
    platform_write("    Major Megamodule Revision ID: %u\n    Minor Megamodule Revision ID: %u\n", cpu_info->megamodule_revision_major, cpu_info->megamodule_revision_minor);
    platform_write("    Major Silicon Revision ID: %u\n    Minor Silicon Revision ID: %u\n", cpu_info->silicon_revision_major, cpu_info->silicon_revision_minor);
    if(cpu_info->endian == PLATFORM_LE){
        platform_write("    Endian: LE\n");
    }else{
        platform_write("    Endian: BE\n");
    }
    platform_write("/************************************/\n");

    device_info = platform_device_open(PLATFORM_DEVID_MT29F2G08ABBEAH, 0);
    if(device_info == NULL){
        platform_write("Open NAND device Error\n");
        return 0;
    }
    platform_write("Open NAND device OK!\nDevice info:\n");
    platform_write("    Device ID: %u\n", device_info->device_id);
    platform_write("    Manufacturer ID: %u\n", device_info->manufacturer_id);
    platform_write("    Width: %u\n", device_info->width);
    platform_write("    Block Count: %d\n", device_info->block_count);
    platform_write("    Page Count: %d\n", device_info->page_count);
    platform_write("    Page Size: %d\n", device_info->page_size);
    platform_write("    Spare Size: %d\n", device_info->spare_size);


    re = Data_Parse(device_info->handle);
    if(re < 0){
        platform_write("Data_Parse error\n");
    }

    status = platform_device_close(device_info->handle);
    if(status != Platform_EOK){
        platform_write("platform_device_close Error: %d\n", status);
    }
    platform_write("platform_device_close OK!\n");

    CSL_BootCfgUnlockKicker();

    platform_write("Have %d cores need wake up\n",my_boot_head->core_count);
    platform_write("Start wake up......\n");

    for(i = 1; i < my_boot_head->core_count; i++){
#if 0
        CSL_BootCfgSetDSPBootAddress(i, my_boot_head->core_info[i].entry_point);
       // maigic_addr =  (uint32_t *)(Magic_Addr[i]);
        //*maigic_addr = X32();
        CSL_BootCfgGenerateInterDSPInterrupt(i,1);
        //ipgr_reg = (uint32_t *)(IPCGR[i]);
        //*ipgr_reg = (*ipgr_reg) | 0x00000001;
        platform_delay(100000);
#endif
#if 1
        CSL_IPC_clearGEMInterruptSource(i, 0);
        maigic_addr = (uint32_t *)(0x1087FFFC + (i * 0x01000000));
        //set the boot magic address of the slave cores
        while(1)
        {
            *maigic_addr = my_boot_head->core_info[i].entry_point;
            //platform_delaycycles(1000000);
            //CACHE_wbL1d ((void *) maigic_addr,4, CACHE_WAIT);
            if((*maigic_addr) == my_boot_head->core_info[i].entry_point)
                break;
        }
        //interrupt the cores to wake them up
        CSL_IPC_genGEMInterrupt(i, 0);
        //platform_delay(5000000);
        platform_write("Wake up core %d Done, entry point 0x%08x!\n", i,  my_boot_head->core_info[i].entry_point);
#endif
    }

    CSL_BootCfgLockKicker();

    platform_write("All slave core wake up Done!\n");
   // platform_write("Core 0 entry_point 0x%08x\n", my_boot_head->core_info[0].entry_point);
    platform_write("Core 0 Start Work......\n");
    if(my_boot_head->core_info[0].entry_point != 0){
        exit = (void (*)())(my_boot_head->core_info[0].entry_point);
        (*exit)();
    }else{
        platform_write("core 0 entry point is null\n");
    }
    return 0;
}
