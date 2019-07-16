#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/platform/platform.h>
//#include <ti/board/src/flash/include/platform.h>
#include <ti/csl/csl_bootcfgAux.h>
#include <ti/csl/csl_ipcAux.h>
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/csl_chip.h>

#include <ti/csl/csl_gpio.h>
#include <ti/csl/csl_gpioAux.h>

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
uint8_t core_id = 0;

void delay_ms(uint32_t ms)
{
    int32_t delaycount, s;
    int32_t t_1ms = 1000000;

    delaycount = (int32_t)ms;
    while(delaycount != 0){
        s = TSCL;
        while((TSCL - s) < t_1ms);
        delaycount --;
    }


}

void mygpioSetOutput( uint32_t uiNumber)
{
   CSL_GpioHandle  hGpio;

   // Open the CSL GPIO Module 0
   hGpio = CSL_GPIO_open (0);

   CSL_GPIO_setOutputData(hGpio, uiNumber);
}

void mygpioClearOutput( uint32_t uiNumber)
{
    CSL_GpioHandle  hGpio;

    // Open the CSL GPIO Module 0
    hGpio = CSL_GPIO_open (0);

    CSL_GPIO_clearOutputData(hGpio, uiNumber);
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

    core_id = platform_get_coreid();

    TSCL = 0;
    TSCH = 0;
    memset(&platform_info, 0, sizeof(platform_info));

    init_flag.pll = 0;
    init_flag.ddr = 0;
    init_flag.phy = 0;
    init_flag.ecc = 0;
    init_flag.tcsl = 0;

    init_config.plld = 0;
    init_config.pllm = 0;
    init_config.postdiv = 0;
    init_config.prediv = 0;

    if(core_id == 0){
        status = platform_init(&init_flag, &init_config);
        if(status != Platform_EOK){
            return -1;
        }
    }

#if 0
    status = platform_uart_init();
    if(status != Platform_EOK){
       return -2;
    }

    status = platform_uart_set_baudrate(115200);
    if(status != Platform_EOK){
        return -3;
    }

    print_write_type = PLATFORM_WRITE_UART;
    print_write_type = platform_write_configure (print_write_type);
    if(print_write_type != PLATFORM_WRITE_UART){
        return -4;
    }
#endif


    PLATFORM_LED_OP operation;
        LED_CLASS_E led_class;
        operation = PLATFORM_LED_OFF;
        led_class = PLATFORM_USER_LED_CLASS;
    uint32_t j,x;

    delay_ms(12000);

        for(x = 0; x < 3; x++)
        {
            mygpioClearOutput(15); //on
           delay_ms(200);
           //platform_delay(1000000);
           //operation = PLATFORM_LED_ON;
          // platform_led(15, operation, led_class);
          // platform_delay(1000000);
           mygpioSetOutput(15); //off
           delay_ms(200);
        }

        while(1);






    return 0;
}
