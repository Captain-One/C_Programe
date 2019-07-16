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

#define UART_SEMAPHORE        0

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    uint8_t re;
    Uint32 semflag;
    uint32_t core_id;
    //platform_uart_init();
    core_id = platform_get_coreid();

#if 1
    CSL_semAcquireIndirect(UART_SEMAPHORE);

    while(1)
    {
        semflag = CSL_semGetFlags(core_id);
        if(semflag & (1 << UART_SEMAPHORE))
            break;
    }
#endif
#if 0
    while(CSL_semAcquireDirect(UART_SEMAPHORE) == 0);
#endif
    CSL_semClearFlags (core_id, semflag);

    re = CSL_semGetFlags(core_id);
    re = CSL_semIsFree(UART_SEMAPHORE);

    platform_write("hello core %d sdfasdfadsfa \n", core_id);

    CSL_semReleaseSemaphore(UART_SEMAPHORE);
    re = CSL_semIsFree(UART_SEMAPHORE);
    re = CSL_semGetErrorCode();
    System_printf("enter taskFxn()\n");

    Task_sleep(10);

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */
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

    BIOS_start();    /* does not return */
    return(0);
}
