/*
 *  ======== main.c ========
 */

#include <string.h>

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
//SRIO

#include "../init/init.h"
#include <core_2_core_interface.h>

String const core_name = "CORE0";
UInt16 const core_id = 0;

uint8_t data[10*128] = {0};
uint32_t dataLen = 10*128;

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    Int status;
    Int i;
    Int re;

    System_printf("enter taskFxn()\n");
    status = sysInit();
    if(status < 0){
        System_printf("Core %d sysInit error\n", core_id);
        System_exit(-1);
    }

    for(i = 0; i < dataLen; i++){
        data[i] = i;
    }

    re = sendDataToCoreN(1, data, dataLen);
    if(re < 0){
        System_printf("sendDataToCoreN eror\n");
    }

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

    System_printf("enter main()\n");

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
