/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Startup.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/sysbios/hal/Timer.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ti/ipc/Ipc.h>

#include <myStartConfig.h>

extern Timer_Handle myTimer;

volatile Bool myEnd2Flag = FALSE;
Int myHookSetId1, myHookSetId2;
Error_Block eb;

Void myRegist1(Int hookSetId)
{
    System_printf("myRegister1: assigned hookset Id = %d\n",hookSetId);
    myHookSetId1 = hookSetId;
}

Void myCreate1(Hwi_Handle hwi, Error_Block *eb)
{
    Ptr pEnv;

    pEnv = Hwi_getHookContext(hwi, myHookSetId1);

    System_printf("myCreate1: pEnv = 0x%x, time = %d\n", pEnv, Timestamp_get32());
    Hwi_setHookContext(hwi, myHookSetId1, (Ptr)0xdead1);
}

Void myBegin1(Hwi_Handle hwi)
{
    Ptr pEnv;

    pEnv = Hwi_getHookContext(hwi, myHookSetId1);

    System_printf("myBegin1: pEnv = 0x%x, time = %d\n", pEnv, Timestamp_get32());
    Hwi_setHookContext(hwi, myHookSetId1, (Ptr)0xbeef1);
}

Void myEnd1(Hwi_Handle hwi)
{
    Ptr pEnv;

    pEnv = Hwi_getHookContext(hwi, myHookSetId1);

    System_printf("End1: pEnv = 0x%x, time = %d\n", pEnv, Timestamp_get32());
    Hwi_setHookContext(hwi, myHookSetId1, (Ptr)0xc0de1);
}

Void myRegist2(Int hookSetId)
{
    System_printf("myRegister2: assigned hookset Id = %d\n",hookSetId);
    myHookSetId2 = hookSetId;
}

Void myCreate2(Hwi_Handle hwi, Error_Block *eb)
{
    Ptr pEnv;

    pEnv = Hwi_getHookContext(hwi, myHookSetId2);

    System_printf("myCreate2: pEnv = 0x%x, time = %d\n", pEnv, Timestamp_get32());
    Hwi_setHookContext(hwi, myHookSetId2, (Ptr)0xdead2);
}

Void myBegin2(Hwi_Handle hwi)
{
    Ptr pEnv;

    pEnv = Hwi_getHookContext(hwi, myHookSetId2);

    System_printf("myBegin2: pEnv = 0x%x, time = %d\n", pEnv, Timestamp_get32());
    Hwi_setHookContext(hwi, myHookSetId2, (Ptr)0xbeef2);
}

Void myEnd2(Hwi_Handle hwi)
{
    Ptr pEnv;

    pEnv = Hwi_getHookContext(hwi, myHookSetId2);

    System_printf("End2: pEnv = 0x%x, time = %d\n", pEnv, Timestamp_get32());
    Hwi_setHookContext(hwi, myHookSetId2, (Ptr)0xc0de2);
    myEnd2Flag = TRUE;
}

Void myTimerFunc(UArg arg)
{
    System_printf("Entering myTimerHwi\n");
}


/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
    System_printf("enter taskFxn()\n");

    Timer_start(myTimer);

    while(!myEnd2Flag){
        ;
    }

    //Task_sleep(10);

    System_printf("exit taskFxn()\n");

   // System_flush(); /* force SysMin output to console */
}

Void myIdleFunc()
{
    System_printf("enter myIdleFunc()\n");
    System_exit(0);
}

Void myInit(Void)
{

}

/*
 *  ======== main ========
 */
Int main()
{ 
    //Task_Handle task;
    //Error_Block eb;
    myPLLInit(MAIN_PLL_REF_CLK_MHZ, MAIN_PLL_MULTIPLIER, MAIN_PLL_DIVISOR);
    //myDDRInit();
    TSC_init();


    System_printf("enter main(),start HwiHookExample...\n");

    Error_init(&eb);
    //task = Task_create(taskFxn, NULL, &eb);
    //if (task == NULL) {
     //   System_printf("Task_create() failed!\n");
      //  BIOS_exit(0);
   // }

    BIOS_start();    /* does not return */
    return(0);
}
