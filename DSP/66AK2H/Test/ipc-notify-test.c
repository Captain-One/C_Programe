/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/ipc/Ipc.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/MultiProc.h>


#define EVENTID         10
#define LINEID          0


Void cbfxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg, UInt32 payload)
{
    System_printf("cbfxn, payload is: %d!\n", payload);
    System_flush(); /* force SysMin output to console */
}

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    UInt16 corenum;
    Int ret;

    System_printf("enter taskFxn()\n");
    System_flush(); /* force SysMin output to console */

    corenum = MultiProc_self();

    if(corenum == 0)
    {
        while(Ipc_attach(1)){
            Task_sleep(1);
        }
        while(Ipc_attach(2)){
            Task_sleep(1);
        }
        while(Ipc_attach(3)){
            Task_sleep(1);
        }
        System_printf("Ipc_attach Ok!\n");
        System_flush();

        /*
        ret = Notify_registerEvent(1, LINEID, EVENTID, (Notify_FnNotifyCbck)cbfxn, NULL);
        if(ret < 0){
            System_printf("Notify_registerEvent, failed code is: %d!\n", ret);
        }else{
            System_printf("Notify_registerEvent Ok!\n");
        }*/

        ret = Notify_sendEvent(1, LINEID, EVENTID, corenum, TRUE);
        if(ret < 0){
            System_printf("Notify_sendEvent, failed code is: %d!\n", ret);
        }else{
            System_printf("Notify_sendEvent Ok!\n");
        }
        System_flush(); /* force SysMin output to console */

    }else{
        while(Ipc_attach(0)){
            Task_sleep(1);
        }
        System_printf("Ipc_attach Ok!\n");
        System_flush(); /* force SysMin output to console */
        ret = Notify_registerEvent(0, LINEID, EVENTID, (Notify_FnNotifyCbck)cbfxn, NULL);
        if(ret < 0){
            System_printf("Notify_registerEvent, failed code is: %d!\n", ret);
        }else{
            System_printf("Notify_registerEvent Ok!\n");
        }

    }

    while(1){
        Task_sleep(10);
    }

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
    Int ipc_ret;
    //UInt16 corenum;

    System_printf("enter main()\n");

    ipc_ret = Ipc_start();
    if(ipc_ret < 0){
        System_printf("Ipc_start failed, failed code is: %d!\n",ipc_ret);
    }else{
        System_printf("Ipc_start Ok!\n");
    }
    //corenum = MultiProc_self();

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
