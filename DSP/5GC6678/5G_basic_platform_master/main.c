/*
 *  ======== main.c ========
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Memory.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/heaps/HeapBuf.h>
#include <ti/sysbios/knl/Task.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/src/UART_osal.h>
#include <ti/drv/uart/soc/UART_soc.h>

/* CSL RL includes */
#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_cacheAux.h>

//SRIO

#include <ti/platform/platform.h>
#include <ti/board/board.h>


#include "../init/init.h"
#include <core_2_core_interface.h>
#include <bb_interface.h>
#include <common.h>

#include <c6x.h>


#define swap16(s) ((((s) & 0xff) << 8) | (((s) >> 8) & 0xff))
#define swap32(l) (((l) >> 24) | \
          (((l) & 0x00ff0000) >> 8)  | \
          (((l) & 0x0000ff00) << 8)  | \
          ((l) << 24))

String const core_name = "CORE0";
UInt16 const core_id = 0;

#define SEND_DATA_LEN      (8*1024 - 20)

#pragma DATA_ALIGN(data, 64);
uint8_t data[SEND_DATA_LEN] = {0};

uint32_t dataLen = SEND_DATA_LEN;


UART_Handle uart_handle;

/* UART parameters structure polled mode*/
const UART_Params user_params = {
    UART_MODE_BLOCKING,     /* readMode */
    UART_MODE_BLOCKING,     /* writeMode */
    0U,                     /* readTimeout */
    0U,                     /* writeTimeout */
    NULL,                  /* readCallback */
    NULL,                 /* writeCallback */
    UART_RETURN_NEWLINE,  /* readReturnMode */
    UART_DATA_TEXT,       /* readDataMode */
    UART_DATA_TEXT,       /* writeDataMode */
    UART_ECHO_ON,         /* readEcho */
    115200,               /* baudRate */
    UART_LEN_8,           /* dataLength */
    UART_STOP_ONE,        /* stopBits */
    UART_PAR_NONE         /* parityType */
};


#define TEST_TIME_1MIN  60000000000UL
#define TEST_TIME_1S    1000000000UL

uint64_t TEST_TIME   =  60*60000000000;

#pragma DATA_SECTION(rxbuf, ".L2RAM")
#pragma DATA_ALIGN (rxbuf, 64)
uint8_t *rxbuf;
/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    UART_Params      params;
    UART_HwAttrs uart_cfg;
    Int status;
    Int i;
    Int re;
    char printbuf[128] = "hello world\n";

   PLATFORM_LED_OP  ledOp;
   LED_CLASS_E led_class;

   uint32_t rxlen;
   //UART_stdioDeInit();
   //UART_stdioInit(0);

   //UART_printf("core 0 uart init over!\n");

#if 0
   Platform_STATUS platstatus;
   platform_init_flags init_flag;
   platform_init_config init_config;

   led_class = PLATFORM_USER_LED_CLASS;

   init_flag.pll = 0;
   init_flag.ddr = 1;
   init_flag.phy = 0;
   init_flag.ecc = 0;
   init_flag.tcsl = 0;

   init_config.plld = 0;
   init_config.pllm = 0;
   init_config.postdiv = 0;
   init_config.prediv = 0;

   memset((uint32_t *)0x80000000, 0 , 2*1024);
   memset((uint32_t *)0x80000800, 0 , 20*1024*1024);

   rxbuf = malloc(16*1024);

   for(i = 0; i < dataLen; i++){
       data[i] = i;
   }

   platstatus = platform_init(&init_flag, &init_config);
   if(platstatus != Platform_EOK){
       printf("platform_init Error: %d\n", platstatus);
   }
   printf("platform_init OK!\n");

  // UART_socGetInitCfg(0, &uart_cfg);

  // UART_socSetInitCfg(0, &uart_cfg);

   UART_init();
   UART_Params_init(&params);
   params = user_params;
   uart_handle = UART_open(0, &params);
   if(uart_handle == NULL)
       ;

   UART_write(uart_handle,printbuf,20);
#endif

    System_printf("enter taskFxn()\n");
    status = sysInit();
    if(status < 0){
        System_printf("Core %d sysInit error\n", core_id);
        System_exit(-1);
    }



#if 1
    re = configSrioParameterToFPGA(BB_FPGA_NO_0);
   // re = configSrioParameterToFPGA(BB_FPGA_NO_1);
    if(re < 0){
        System_printf("configSrioParameterToFPGA eror\n");
    }

    uint64_t prv = 0, cur = 0, prvPktend = 0;;
    uint64_t get_count = 0;
    uint32_t err_count = 0;
    uint32_t get_err_count = 0;
    uint32_t rx_err_count_pkt = 0;
    uint64_t start_time, end_time;
    uint8_t * pbuf;

    uint64_t s_count = 0;
    uint32_t send_err_count = 0;
    uint64_t send_count = 0;
    uint64_t wst = 0, wst1 = 0, wst2 = 0;
#endif


    double sen_size = 0, get_size = 0;
    double speed = 0;
    double test_time = 0;
    double overhead_time = 0;
    double use_time = 0;
#if 0
    wst1 = _itoll(TSCH, TSCL);

    end_time = _itoll(TSCH, TSCL);
    if((end_time - start_time) > TEST_TIME)
            ;
    if(re < 0){
        ;
    }
    i ++;

    wst2 = _itoll(TSCH, TSCL);
    wst = wst2 - wst1;
    System_printf("wst time %ld cycle\n", wst);

    start_time = _itoll(TSCH, TSCL);
    while(1){
        end_time = _itoll(TSCH, TSCL);
        if((end_time - start_time) > TEST_TIME)
                    break;
        re = getBbData(BB_FPGA_NO_0, rxbuf,&rxlen);
        if(re < 0){
            System_printf("get data error");
            get_err_count ++;
            continue;
        }
        if(re == 0)
            continue;

        get_count++;
        get_size +=  rxlen;

        //CACHE_invL1d ((void *) rxbuf, rxlen, CACHE_WAIT);
        pbuf = rxbuf;
        //CACHE_wbL1d ((void *) pbuf, 8, CACHE_WAIT);

        prv = *(uint64_t *)pbuf;
        if(get_count != 1){
            //CACHE_wbL1d ((void *) &get_count, 4, CACHE_WAIT);
            //CACHE_wbL1d ((void *) &prvPktend, 8, CACHE_WAIT);
            //CACHE_wbL1d ((void *) rxbuf, 8, CACHE_WAIT);
            //CACHE_invL1d ((void *) &prv, 8, CACHE_WAIT);
            //CACHE_invL1d ((void *) &get_count, 4, CACHE_WAIT);
            //System_printf("prvPktend %ld, prv %ld, n %d\n", prvPktend, prv, get_count);
            if(prv != (prvPktend +1)){
                rx_err_count_pkt ++;
            }
        }
        for(i = 8; i < 256; i+=8)
        {
            cur = *(uint64_t *)(pbuf + i);
            if(cur != (prv + 1)){
                err_count ++;
                prv = cur;
                continue;
            }
            prv = cur;
        }
        prvPktend = prv;
        //if(get_count == 50)
          //  break;
    }

    get_size = (get_size)/(1024.0*1024.0);
    test_time = (end_time - start_time)/1000000000.0;
    overhead_time = get_count * wst/1000000000.0;
    use_time = test_time - overhead_time;
    speed = get_size/use_time;
    System_printf("get data error count %d \n", get_err_count);
    System_printf("get data count %ld \n", get_count);
    System_printf("get data size %f MB\n", get_size);
    System_printf("test_time  %f s\n", test_time);
    System_printf("overhead_time  %f s\n", overhead_time);
    System_printf("use_time  %f s\n", use_time);
    System_printf("speed  %f MB/s\n", speed);
    System_flush();
#endif

#if 0
    char tz[128];
    snprintf(tz, sizeof(tz), "Recive %d Packet\n start_time : %llu , end_time : %llu\n trans time is : %f m\n", get_count, start_time, end_time, (float) (end_time - start_time)/TEST_TIME_1MIN);
    UART_write(uart_handle,tz,sizeof(tz));
    System_printf("%s", tz);
    snprintf(tz, sizeof(tz),"error count %d\n", err_count);
    UART_write(uart_handle,tz,sizeof(tz));
    System_printf("error count %d\n", err_count);

    snprintf(tz, sizeof(tz),"rx err count count %d\n", rx_err_count_pkt);
    UART_write(uart_handle,tz,sizeof(tz));
    System_printf("rx err count pkt %d\n", rx_err_count_pkt);

    snprintf(tz, sizeof(tz),"get error count %d\n", get_err_count);
    UART_write(uart_handle,tz,sizeof(tz));
    System_printf("get error count %d\n", get_err_count);

    snprintf(tz, "get_count coullnt %d\n", get_count);
    UART_write(uart_handle,tz,sizeof(tz));
    System_printf("get_count count %ld\n", get_count);

    snprintf(tz, sizeof(tz),"get data size %d MB\n", (get_count*256)/(1024*1024));
    UART_write(uart_handle,tz,sizeof(tz));
    System_printf("get data size %d MB\n", (get_count*256)/(1024*1024));

    System_flush();
#endif


#if 1
    wst1 = _itoll(TSCH, TSCL);

    //end_time = _itoll(TSCH, TSCL);
    //if((end_time - start_time) > TEST_TIME)
            //;

    ((FpkH_t *)data)->mark = 0xBADC;
    ((FpkH_t *)data)->flen = swap16(dataLen);
    ((FpkH_t *)data)->type = swap16(0x1009);
    ((FpkH_t *)data)->bdinfo.src_adr = 1;
    ((FpkH_t *)data)->bdinfo.dst_adr = 0;


    for(i = 0; i < (dataLen - sizeof(FpkH_t)); i++)
    {
        data[i + sizeof(FpkH_t)] = i;
    }
    s_count += i;
    //CACHE_wbL1d ((void *) data, dataLen*8, CACHE_WAIT);
    if(re < 0){
        ;//send_err_count ++;
    }
    //i ++;
    wst2 = _itoll(TSCH, TSCL);
    wst = wst2 - wst1;
    System_printf("wst time %ld cycle\n", wst);

    start_time = _itoll(TSCH, TSCL);
    while(1){
        end_time = _itoll(TSCH, TSCL);
        if((end_time - start_time) > TEST_TIME)
                    break;
        //CACHE_invL1d ((void *) data, dataLen*8, CACHE_WAIT);

        //for(i = 0; i < (dataLen - sizeof(FpkH_t)); i++)
       // {
       //     data[i + sizeof(FpkH_t)] = i;
       // }
        //for(i = 0; i < dataLen; i++)
        //{
        //    data[i] = s_count + i;
       // }
        s_count += i;
        CACHE_wbL1d ((void *) data, dataLen, CACHE_WAIT);
        re = sendDataToBb(BB_FPGA_NO_0, data, dataLen);
        if(re < 0){
            send_err_count ++;
        }
        send_count ++;
    }


    sen_size = (send_count*dataLen*8)/(1024.0*1024.0);
    test_time = (end_time - start_time)/1000000000.0;
    overhead_time = send_count * wst/1000000000.0;
    use_time = test_time - overhead_time;
    speed = sen_size/use_time;
    System_printf("sen data error count %d \n", send_err_count);
    System_printf("sen data count %ld \n", send_count);
    System_printf("sen data size %f MB\n", sen_size);
    System_printf("test_time  %f s\n", test_time);
    System_printf("overhead_time  %f s\n", overhead_time);
    System_printf("use_time  %f s\n", use_time);
    System_printf("speed  %f MB/s\n", speed);


    System_flush();



    re = sendDataToCoreN(1, data, dataLen);
    if(re < 0){
        System_printf("sendDataToCoreN eror\n");
    }
#endif
    Task_sleep(10);

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */
    while(1);

}


/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;

#if 0
    Board_STATUS stats;
    Board_initCfg cfg = 0;
    Board_SoCInfo socInfo;
    Board_IDInfo  idInfo;

    cfg = BOARD_INIT_PLL | BOARD_INIT_DDR | BOARD_INIT_UART_STDIO | BOARD_INIT_ECC;

    System_printf("enter main()\n");

    stats = Board_init(cfg);
    if(stats != BOARD_SOK)
        System_printf("Board_init error %d \n", stats);

    stats = Board_getSoCInfo(&socInfo);
    if(stats != BOARD_SOK)
        System_printf("Board_getSoCInfo error %d \n", stats);

    System_printf("Board sysClock is : %d\n",socInfo.sysClock);

    stats =  Board_getIDInfo(&idInfo);
    if(stats != BOARD_SOK)
        System_printf("Board_getIDInfo error %d \n", stats);

    System_printf("Board Name is : %s\n",idInfo.boardName);
    System_printf("Board sysClock is : %s\n",idInfo.configCodes);
    System_printf("Board sysClock is : %s\n",idInfo.header);
    System_printf("Board sysClock is : %s\n",idInfo.indEthMacID0);
    System_printf("Board sysClock is : %s\n",idInfo.serialNum);
    System_printf("Board sysClock is : %s\n",idInfo.version);
    System_flush();
#endif

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
