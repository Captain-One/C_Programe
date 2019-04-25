/*
 * qmss_init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: lin
 */

#include "qmss_init.h"

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

typedef struct mymsg{
    MessageQ_MsgHeader header;
    uint32_t masterInitDone;
    uint32_t allCoreInitDone;
}notify_Mymsg;

static notify_Mymsg *notMymsg;

Int cppiInit(Void)
{
    Qmss_Result  re_qmss;
    Cppi_Result  re_cppi;
    Qmss_InitCfg cfg;
    MessageQ_QueueId  queId;
    Ptr  heap;
    Int  re;

    char msgName[] = "qmssInitMsg";

    MessageQ_Params params;
    MessageQ_Handle msg;

    MessageQ_Params_init(&params);
    msg = MessageQ_create(msgName, &params);
    if(msg == NULL){
        System_printf("MessageQ create error\n");
        return -1;
    }

    heap = SharedRegion_getHeap(0);

    re = MessageQ_registerHeap(heap, 0);
    if(re != MessageQ_S_SUCCESS){
        System_printf("MessageQ_registerHeap error\n");
        return re;
    }

    notMymsg = (notify_Mymsg *)MessageQ_alloc(0, sizeof(notify_Mymsg));
    if(notMymsg == NULL){
        System_printf("MessageQ_alloc error\n");
        return -1;
    }

    notMymsg->allCoreInitDone = 0;
    notMymsg->masterInitDone = 0;

    cfg.linkingRAM0Base = 0;
    cfg.linkingRAM0Size = 0;
    cfg.linkingRAM1Base = 0;
    cfg.maxDescNum = 0;
    //cfg.mode = 0;
    //cfg.pdspFirmware = NULL;
    cfg.qmssHwStatus = 0;
    //cfg.splitLinkingRAMs = 1;

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

    notMymsg->masterInitDone = 1;
    notMymsg->allCoreInitDone = 1;

    do{
        re = MessageQ_open(msgName, &queId);
    }while(re != MessageQ_S_SUCCESS);

    re = MessageQ_put(queId, (MessageQ_Msg)notMymsg);
    if(re != MessageQ_S_SUCCESS){
        System_printf("MessageQ_put error\n");
        return -1;
    }

    while(notMymsg->allCoreInitDone ==  2)
    {
        re = MessageQ_get(msg, (MessageQ_Msg *)notMymsg, MessageQ_FOREVER);
        if(re != MessageQ_S_SUCCESS){
            System_printf("MessageQ_get erro \n");
            return -1;
        }
    }

    return 0;
}
