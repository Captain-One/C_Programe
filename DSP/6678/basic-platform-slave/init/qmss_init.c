/*
 * qmss_init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: pu
 */

#include "qmss_init.h"

#include <xdc/runtime/System.h>

#include <ti/csl/csl_cacheAux.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/GateMP.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>
#include <ti/ipc/HeapBufMP.h>

extern Qmss_GlobalConfigParams qmssGblCfgParams;
extern Cppi_GlobalConfigParams cppiGblCfgParams;
extern UInt16 core_id ;

#define MASTER_CORE         0
#define INTERRUPT_LINE      0
#define EVENT_ID            10

/* linking RAM */
#pragma DATA_ALIGN (linkingRAM0, 16)
uint64_t            linkingRAM0[NUM_HOST_DESC + NUM_MONOLITHIC_DESC];

/* Descriptor pool [Size of descriptor * Number of descriptors] */
#pragma DATA_ALIGN (hostDesc, 16)
uint8_t             hostDesc[SIZE_HOST_DESC * NUM_HOST_DESC];
#pragma DATA_ALIGN (monolithicDesc, 16)
uint8_t             monolithicDesc[SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC];
#pragma DATA_ALIGN (dataBuff, 16)
uint8_t             dataBuff[SIZE_DATA_BUFFER * NUM_DATA_BUFFER];

uint8_t masterInitDone = 0;
uint8_t allCoreInitDone = 0;

Void cbFxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg, UInt32 payload)
{
    System_printf("cbfxn, payload is: %d!\n", payload);
    masterInitDone = 1;
    allCoreInitDone = payload;
    CACHE_wbL1d ((void *) &masterInitDone, 4, CACHE_WAIT);
    CACHE_wbL1d ((void *) &allCoreInitDone, 4, CACHE_WAIT);
}


Int cppiInit(Void)
{
    Qmss_Result  re_qmss;
    Int re;

    re = Notify_registerEvent(MASTER_CORE, INTERRUPT_LINE, EVENT_ID, (Notify_FnNotifyCbck)cbFxn, NULL);
    if(re != Notify_S_SUCCESS){
        System_printf("Notify_registerEvent on MASTER CORE %derror\n");
        return -1;
    }

    do{
        CACHE_invL1d ((void *) &masterInitDone, 4, CACHE_WAIT);
    }while(masterInitDone == 0);  //wait master core init done;


    re_qmss = Qmss_start();
    if(re_qmss != QMSS_SOK){
        System_printf("core %d Qmss start error\n", core_id);
        return re_qmss;
    }

    do{
        CACHE_invL1d ((void *) &allCoreInitDone, 4, CACHE_WAIT);
    }while(allCoreInitDone != 8); //wait all core init done;


    System_printf("core %d cppi init done\n", core_id);

    return 0;
}
