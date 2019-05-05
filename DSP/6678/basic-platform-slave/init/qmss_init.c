/*
 * qmss_init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: pu
 */

#include <string.h>

#include "qmss_init.h"

#include <ti/sysbios/knl/Task.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>

#include <ti/csl/csl_cacheAux.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>

extern Qmss_GlobalConfigParams qmssGblCfgParams;
extern Cppi_GlobalConfigParams cppiGblCfgParams;
extern UInt16 core_id ;

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
    Int re;

    MessageQ_Handle msg;
    MessageQ_QueueId qid;
    Notifye_Msg *notifyMsg;

    Ptr heap;

    String masterMsgQName = MASTER_MSGQ_NAME;


    core_id = MultiProc_self();

    heap = SharedRegion_getHeap(0);

    notifyMsg = (Notifye_Msg *)Memory_alloc(heap, sizeof(Notifye_Msg), 32, NULL);

    memset(notifyMsg, 0, sizeof(Notifye_Msg));

    do{
        re = MessageQ_open(masterMsgQName, &qid);
        Task_sleep(1);
    }while(re < 0);

    msg = MessageQ_create(NULL, NULL);
    if(msg == NULL){
        System_printf("MessageQ_create Error\n");
        System_flush();
        return -1;
    }

    MessageQ_staticMsgInit((MessageQ_Msg)notifyMsg, sizeof(Notifye_Msg));
    MessageQ_setReplyQueue(msg, (MessageQ_Msg)notifyMsg);

    notifyMsg->initDone = 0;

    while(1)
    {
        do{
            re = MessageQ_put(qid, (MessageQ_Msg)notifyMsg);
        }while(re < 0);

        re = MessageQ_get(msg, (MessageQ_Msg *)&notifyMsg, MessageQ_FOREVER);

        if((notifyMsg->initDone & ALL_CORE_INIT_DONE) == ALL_CORE_INIT_DONE)
            break;

        if(notifyMsg->initDone & MASTER_INIT_DONE)
        {
            //init qmss;
            re_qmss = Qmss_start();
            if(re_qmss != QMSS_SOK){
                System_printf("core %d Qmss start error\n", core_id);
                return re_qmss;
            }
            notifyMsg->initDone |= INIT_DONE;
        }
    }
    Memory_free(heap, notifyMsg, sizeof(Notifye_Msg));

    System_printf("core %d cppi init done\n", core_id);

    return 0;
}
