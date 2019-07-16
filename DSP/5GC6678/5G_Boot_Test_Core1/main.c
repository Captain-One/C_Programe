/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/board/board.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/src/UART_osal.h>
#include <ti/drv/uart/soc/UART_soc.h>
#include <ti/platform/platform.h>

#include <ti/csl/soc.h>
#include <ti/csl/csl_semAux.h>

#include "uart_mutex.h"

#define UART_SEMAPHORE        0
const uint8_t core_ID = 1;
/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    uint8_t re;
    Uint32 semflag;
    UART_HwAttrs uartHwAttrsCfg;
       //platform_uart_init();

       //CSL_semClearError();
       UART_socGetInitCfg(0, &uartHwAttrsCfg);
       uartHwAttrsCfg.enableInterrupt = 0;
       uartHwAttrsCfg.eventId = 109;
       uartHwAttrsCfg.intcMuxOutEvent = 25;//4 + 8*core_ID;
       UART_socSetInitCfg(0, &uartHwAttrsCfg);
       UART_stdioInit(0);
while(1){
       UART_mutex_printf("hello core 1 task 1\n");
       Task_sleep(10);
}


       System_printf("enter taskFxn()\n");

       Task_sleep(10);

       System_printf("exit taskFxn()\n");

       System_flush(); /* force SysMin output to console */
}

Void taskFxn2(UArg a0, UArg a1)
{
    UART_HwAttrs uartHwAttrsCfg;
        //UART_Params params;
        //UART_Handle uartHandle;
#if 0
        UART_socGetInitCfg(0, &uartHwAttrsCfg);
        uartHwAttrsCfg.enableInterrupt = 0;
        uartHwAttrsCfg.eventId = 109;
        uartHwAttrsCfg.intcMuxOutEvent = 25;//4 + 8*core_ID;
        UART_socSetInitCfg(0, &uartHwAttrsCfg);

        //UART_Params_init(&params);


        //uartHandle = UART_open(UART_INSTANCE, &params);

        UART_stdioInit(0);
#endif
    while(1){
        UART_mutex_printf("hello core 1 task 2\n");
    Task_sleep(10);
    //Task_yield();
    }
}


/*
 *  ======== main ========
 */
Int main()
{ 
    Task_Handle task;
    Error_Block eb;
    Board_STATUS board_status;
    Board_initCfg cfg;

    System_printf("enter main()\n");

    if(0){
    cfg = BOARD_INIT_UART_STDIO;
    board_status = Board_init(cfg);
    if(board_status != BOARD_SOK)
        return 0;
}
    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    task = Task_create(taskFxn2, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
