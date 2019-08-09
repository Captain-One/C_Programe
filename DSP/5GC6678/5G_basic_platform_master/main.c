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
#include <ti/csl/csl_semAux.h>

//SRIO

#include <ti/platform/platform.h>
#include <ti/board/board.h>

#include "../init/init.h"
#include <core_2_core_interface.h>
#include <bb_interface.h>
#include <common.h>

#include <uart_mutex.h>

#include <c6x.h>

#define swap16(s) ((((s) & 0xff) << 8) | (((s) >> 8) & 0xff))
#define swap32(l) (((l) >> 24) | \
          (((l) & 0x00ff0000) >> 8)  | \
          (((l) & 0x0000ff00) << 8)  | \
          ((l) << 24))

String const core_name = "CORE0";
UInt16 const core_id = 0;

#define SEND_DATA_LEN      (1024)

#pragma DATA_ALIGN(data, 64);
#ifdef SRIO_PERFORMANCE_TEST
uint64_t data[SEND_DATA_LEN] = {0};
#else
uint8_t data[SEND_DATA_LEN] = {0};
#endif

uint32_t dataLen = SEND_DATA_LEN;

uint8_t core_ID = 0;


#define TEST_TIME_1MIN  60000000000UL
#define TEST_TIME_1S    1000000000UL

uint64_t TEST_TIME   =  1*60000000000;

#pragma DATA_SECTION(rxbuf, ".L2RAM")
#pragma DATA_ALIGN (rxbuf, 64)
uint8_t *rxbuf;
/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    //UART_Params      params;
    //UART_HwAttrs     uartHwAttrsCfg;
    Int status;
    Int i;
    Int re;
    uint32_t rxlen;

    MYPRINTF("enter taskFxn()\n");
    MYPRINTF("enter taskFxn()\n");
    status = sysInit();
    if(status < 0){
        MYPRINTF("Core %d sysInit error\n", core_id);
        System_exit(-1);
    }

#ifdef SRIO_DEBUG_FPGA0
    re = configSrioParameterToFPGA(BB_FPGA_NO_0);
#elif defined SRIO_DEBUG_FPGA1
    re = configSrioParameterToFPGA(BB_FPGA_NO_1);
#else
    re = configSrioParameterToFPGA(BB_FPGA_NO_0);
    if(re < 0){
        MYPRINTF("configSrioParameterToFPGA eror\n");
    }
    re = configSrioParameterToFPGA(BB_FPGA_NO_1);
#endif
    if(re < 0){
        MYPRINTF("configSrioParameterToFPGA eror\n");
    }

#ifdef  SRIO_PERFORMANCE_TEST
    uint64_t wst = 0, wst1 = 0, wst2 = 0;
    uint64_t start_time = 0, end_time = 0;
    double speed = 0;
    double test_time = 0;
    double overhead_time = 0;
    double use_time = 0;
#endif

#ifdef SRIO_RECEIVE_PERFORMANCE_TEST
    uint64_t prv = 0, cur = 0, prvPktend = 0;;
    uint64_t get_count = 0;
    uint32_t err_count = 0;
    uint32_t get_err_count = 0;
    uint32_t rx_err_count_pkt = 0;
    double get_size = 0;

    uint8_t * pbuf;

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

    MYPRINTF("wst time %ld cycle\n", wst);

    start_time = _itoll(TSCH, TSCL);
    while(1){
        end_time = _itoll(TSCH, TSCL);
        if((end_time - start_time) > TEST_TIME)
                    break;
#ifdef SRIO_DEBUG_FPGA0
        re = getBbData(BB_FPGA_NO_0, rxbuf,&rxlen);
#elif defined SRIO_DEBUG_FPGA1
        re = getBbData(BB_FPGA_NO_1, rxbuf,&rxlen);
#else
        re = getBbData(BB_FPGA_NO_0, rxbuf,&rxlen);
#endif
        if(re < 0){
            MYPRINTF("get data error");
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
    }

    get_size = (get_size)/(1024.0*1024.0);
    test_time = (end_time - start_time)/1000000000.0;
    overhead_time = get_count * wst/1000000000.0;
    use_time = test_time - overhead_time;
    speed = get_size/use_time;
    MYPRINTF("get data error count %d \n", get_err_count);
    MYPRINTF("get data count %ld \n", get_count);
    MYPRINTF("get data size %f MB\n", get_size);
    MYPRINTF("test_time  %f s\n", test_time);
    MYPRINTF("overhead_time  %f s\n", overhead_time);
    MYPRINTF("use_time  %f s\n", use_time);
    MYPRINTF("speed  %f MB/s\n", speed);
#ifndef  USE_UART_PRINT
    System_flush();
#endif
#endif


#ifdef  SRIO_TRANSMIT_PERFORMANCE_TEST
    uint64_t s_count = 0;
    uint32_t send_err_count = 0;
    uint64_t send_count = 0;
    double sen_size = 0;

    wst1 = _itoll(TSCH, TSCL);

    end_time = _itoll(TSCH, TSCL);
    if((end_time - start_time) > TEST_TIME)
            ;
    for(i = 0; i < dataLen; i++)
    {
        data[i] = s_count + i;
    }
    s_count += i;
    CACHE_wbL1d ((void *) data, dataLen*8, CACHE_WAIT);

    if(re < 0){
        i ++;
    }
    i ++;
    wst2 = _itoll(TSCH, TSCL);
    wst = wst2 - wst1;
    MYPRINTF("wst time %ld cycle\n", wst);

    s_count = 0;
    MYPRINTF("start trans....\n");
    start_time = _itoll(TSCH, TSCL);
    while(1){
        end_time = _itoll(TSCH, TSCL);
        if((end_time - start_time) > TEST_TIME)
            break;

        for(i = 0; i < dataLen; i++)
        {
            data[i] = s_count + i;
        }
        s_count += i;
        CACHE_wbL1d ((void *) data, dataLen*8, CACHE_WAIT);

#ifdef SRIO_DEBUG_FPGA0
        re = sendDataToBb(BB_FPGA_NO_0, data, dataLen*8);
#elif defined SRIO_DEBUG_FPGA1
        re = sendDataToBb(BB_FPGA_NO_1, data, dataLen*8);
#else
        re = sendDataToBb(BB_FPGA_NO_0, data, dataLen*8);

#endif
        if(re < 0){
            send_err_count ++;
            continue;
        }
        send_count ++;
    }

    sen_size = (send_count*dataLen*8)/(1024.0*1024.0);
    test_time = (end_time - start_time)/1000000000.0;
    overhead_time = send_count * wst/1000000000.0;
    use_time = test_time - overhead_time;
    speed = sen_size/use_time;
    MYPRINTF("sen data error count %d \n", send_err_count);
    MYPRINTF("sen data count %ld \n", send_count);
    MYPRINTF("sen data size %f MB\n", sen_size);
    MYPRINTF("test_time  %f s\n", test_time);
    MYPRINTF("overhead_time  %f s\n", overhead_time);
    MYPRINTF("use_time  %f s\n", use_time);
    MYPRINTF("speed  %f MB/s\n", speed);

#ifndef  USE_UART_PRINT
    System_flush();
#endif

#endif

#ifdef  SRIO_PROTOCOL_TEST

    uint64_t prot_send_err_count = 0;
    uint64_t prot_get_err_count = 0;

    ((FpkH_t *)data)->mark = 0xBADC;
    ((FpkH_t *)data)->flen = swap16(dataLen);
    ((FpkH_t *)data)->type = swap16(0x1009);
    ((FpkH_t *)data)->bdinfo.src_adr = 1;
    ((FpkH_t *)data)->bdinfo.dst_adr = 0;

    while(1){
        for(i = 0; i < (dataLen - sizeof(FpkH_t)); i++)
        {
           data[i + sizeof(FpkH_t)] = i;
        }
#ifdef SRIO_DEBUG_FPGA0
        re = sendDataToBb(BB_FPGA_NO_0, data, dataLen);
#elif defined SRIO_DEBUG_FPGA1
        re = sendDataToBb(BB_FPGA_NO_1, data, dataLen);
#else
        re = sendDataToBb(BB_FPGA_NO_0, data, dataLen);
        if(re < 0){
            prot_send_err_count ++;
            continue;
        }
        re = sendDataToBb(BB_FPGA_NO_1, data, dataLen);
#endif
        if(re < 0){
            prot_send_err_count ++;
            continue;
        }

#ifdef SRIO_DEBUG_FPGA0
        re = getBbData(BB_FPGA_NO_0, rxbuf,&rxlen);
#elif defined SRIO_DEBUG_FPGA1
        re = getBbData(BB_FPGA_NO_1, rxbuf,&rxlen);
#else
        re = getBbData(BB_FPGA_NO_0, rxbuf,&rxlen);
        if(re < 0){
            prot_get_err_count ++;
        }
        re = getBbData(BB_FPGA_NO_1, rxbuf,&rxlen);
#endif
        if(re < 0){
            prot_get_err_count ++;
        }
        Task_sleep(100);
    }
#endif

#ifdef  CORE_TO_CORE_TEST
    re = sendDataToCoreN(1, data, dataLen);
    if(re < 0){
        MYPRINTF("sendDataToCoreN eror\n");
    }

    Task_sleep(10);
#endif

    MYPRINTF("exit taskFxn()\n");
#ifndef  USE_UART_PRINT
    System_flush(); /* force SysMin output to console */
#endif
    while(1);

}

void taskLed(UArg a0, UArg a1)
{
    PLATFORM_LED_OP  op;
    LED_CLASS_E  class;

    class = PLATFORM_USER_LED_CLASS;
    while(1)
    {
        op = PLATFORM_LED_ON;
        platform_led(15, op, class);
        Task_sleep(1000);
        op = PLATFORM_LED_OFF;
        platform_led(15, op, class);
        Task_sleep(1000);
    }

}


void delay_ms(uint32_t n)
{
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 1000; j++)
            ;
}


/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;
    UART_HwAttrs     uartHwAttrsCfg;

#if 1
    Board_STATUS stats;
    Board_initCfg cfg = 0;

    cfg = BOARD_INIT_UART_STDIO ;

    stats = Board_init(cfg);
    if(stats != BOARD_SOK)
        System_printf("Board_init error %d \n", stats);

#if 1
    UART_socGetInitCfg(0, &uartHwAttrsCfg);
    uartHwAttrsCfg.enableInterrupt = 0;
    UART_socSetInitCfg(0, &uartHwAttrsCfg);

    UART_stdioInit(0);
    CSL_semClearError();
    UART_mutex_printf("enter main()\n");
#endif
#endif

    Error_init(&eb);
   task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    task = Task_create(taskLed, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
