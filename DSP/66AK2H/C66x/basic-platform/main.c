/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>
//SRIO

String core_name = "CORE0";
UInt16 core_id = 0;



/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    System_printf("enter taskFxn()\n");

    Task_sleep(10);

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */
}

Int ipcInit(Void)
{
    Int status;

    status = Ipc_start();
    if(status < 0){
        System_printf("Core %d Ipc start error, code: %d\n", core_id, status);
        return -1;
    }
    System_printf("Core %d IPC ready\n", core_id);
    return 0;
}


Int srioInit(Void)
{
    return 0;
}

Int sysInit(Void)
{
    Int ret;

    ret = ipcInit();
    if(ret < 0){
        System_printf("ipcInit eeror\n");
        return -1;
    }


    return 0;
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
