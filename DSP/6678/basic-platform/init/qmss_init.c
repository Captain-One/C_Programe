/*
 * qmss_init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: pu
 */

#include "qmss_init.h"
#include <string.h>

#include <ti/csl/csl_cacheAux.h>

#include <xdc/runtime/System.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/GateMP.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>

#define INTERRUPT_LINE      0
#define EVENT_ID            10

extern Qmss_GlobalConfigParams qmssGblCfgParams;
extern Cppi_GlobalConfigParams cppiGblCfgParams;
extern UInt16 core_id;

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


uint8_t qmssInitDone = 0;


Void cbFxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg, UInt32 payload)
{
    System_printf("cbfxn, payload is: %d!\n", payload);
    qmssInitDone ++;
    CACHE_wbL1d ((void *) &qmssInitDone, 4, CACHE_WAIT);
}

Int cppiInit(Void)
{
    Qmss_Result  re_qmss;
    Cppi_Result  re_cppi;
    Qmss_InitCfg cfg;

    Int re;
    Int i;


    memset ((void *) &cfg, 0, sizeof (Qmss_InitCfg));

    cfg.linkingRAM0Base = 0;
    cfg.linkingRAM0Size = 0;
    cfg.linkingRAM1Base = 0;
    cfg.maxDescNum = 64;
    //cfg.mode = 0;
    //cfg.pdspFirmware = NULL;
    //cfg.qmssHwStatus = 0;
    //cfg.splitLinkingRAMs = 1;

    for(i = 1; i < 2; i++)
    {
        re = Notify_registerEvent(i, INTERRUPT_LINE, EVENT_ID, (Notify_FnNotifyCbck)cbFxn, NULL);
        if(re != Notify_S_SUCCESS){
            System_printf("Notify_registerEvent for core %d error\n", i);
            return -1;
        }
    }

    re_qmss = Qmss_init(&cfg, &qmssGblCfgParams);
    if(re_qmss != QMSS_SOK){
        System_printf("Qmss init error\n");
        return re_qmss;
    }

    re_qmss = Qmss_start();
    if(re_qmss != QMSS_SOK){
        System_printf("core %d Qmss start error\n", core_id);
        return re_qmss;
    }

    re_cppi = Cppi_init(&cppiGblCfgParams);
    if(re_cppi != CPPI_SOK){
        System_printf("Cppi init error\n");
        return re_cppi;
    }

    for(i = 1; i < 2; i++)
    {
        re = Notify_sendEvent(i, INTERRUPT_LINE, EVENT_ID, 0, TRUE);
        if(re != Notify_S_SUCCESS){
            System_printf("Notify_sendEvent for core %d error\n", i);
            return -1;
        }
    }

    do{
        CACHE_invL1d ((void *) &qmssInitDone, 4, CACHE_WAIT);
    }while(qmssInitDone != 1);

    for(i = 1; i < 2; i++)
    {
        re = Notify_sendEvent(i, INTERRUPT_LINE, EVENT_ID, 8, TRUE);  //
        if(re != Notify_S_SUCCESS){
            System_printf("Notify_sendEvent for core %d error\n", i);
            return -1;
        }
    }

    System_printf("core %d qmss init done!\n", core_id);

    return 0;
}
