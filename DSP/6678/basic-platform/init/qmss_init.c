/*
 * qmss_init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: pu
 */

#include "qmss_init.h"
#include <string.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/csl/csl_cacheAux.h>

#include <xdc/runtime/System.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>

//IPC
#include <ti/ipc/Ipc.h>
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



Int cppiInit(Void)
{
    Qmss_Result  re_qmss;
    Cppi_Result  re_cppi;
    Qmss_InitCfg cfg;

    MessageQ_QueueId qid;
    Notifye_Msg *notifyMsg;
    MessageQ_Params msgQ_params;
    MessageQ_Handle msg;

    Int initDone;
    Int re;

    String masterMsgQName = MASTER_MSGQ_NAME;

    core_id = MultiProc_self();

    memset ((void *) &cfg, 0, sizeof (Qmss_InitCfg));

    cfg.linkingRAM0Base = 0;
    cfg.linkingRAM0Size = 0;
    cfg.linkingRAM1Base = 0;
    cfg.maxDescNum = 64;
    //cfg.mode = 0;
    //cfg.pdspFirmware = NULL;
    //cfg.qmssHwStatus = 0;
    //cfg.splitLinkingRAMs = 1;

    MessageQ_Params_init(&msgQ_params);
    msg = MessageQ_create(masterMsgQName, &msgQ_params);
    if(msg == NULL){
        System_printf("MessageQ_create Error\n");
        System_flush();
        return -1;
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

    initDone = MASTER_INIT_DONE;
    while(1)
    {
        re = MessageQ_get(msg, (MessageQ_Msg *)&notifyMsg, MessageQ_FOREVER);
        //set flag;
        initDone |= notifyMsg->initDone;
        notifyMsg->initDone = initDone;
        qid = MessageQ_getReplyQueue(notifyMsg);
        do{
            re = MessageQ_put(qid, (MessageQ_Msg)notifyMsg);
        }while(re < 0);

        //if all core init done break;
        if((initDone & ALL_CORE_INIT_DONE) == ALL_CORE_INIT_DONE)
            break;
    }

    System_printf("core %d cppi init done! \n", core_id);
    return 0;
}
