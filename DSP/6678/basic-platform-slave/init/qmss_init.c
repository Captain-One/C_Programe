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
#include <ti/drv/QMSS/QMSS_drv.h>
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>
#include <ti/drv/cppi/cppi_osal.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>

extern Qmss_GlobalConfigParams qmssGblCfgParams;
extern Cppi_GlobalConfigParams cppiGblCfgParams;
extern UInt16 core_id ;

/* linking RAM */
//#pragma DATA_ALIGN (linkingRAM0, 16)
//uint64_t            linkingRAM0[NUM_HOST_DESC + NUM_MONOLITHIC_DESC];
//#pragma DATA_ALIGN (monolithicDesc, 16)
//uint8_t             monolithicDesc[SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC];
//#pragma DATA_ALIGN (dataBuff, 16)
//uint8_t             dataBuff[SIZE_DATA_BUFFER * NUM_DATA_BUFFER];

/* Descriptor pool [Size of descriptor * Number of descriptors] */
#pragma DATA_SECTION(hostDesc, ".L2RAM")
#pragma DATA_ALIGN (hostDesc, 16)
uint8_t             hostDesc[SIZE_HOST_DESC * NUM_HOST_DESC];  //128 * 64 = 8k;

#pragma DATA_SECTION(rxDataBuff, ".L2RAM")
#pragma DATA_ALIGN (rxDataBuff, 16)
uint8_t             rxDataBuff[SIZE_RX_DATA_BUFFER * NUM_RX_DATA_BUFFER];

Qmss_QueueHnd freeQueHnd;
Qmss_QueueHnd rxQueHnd;
Qmss_QueueHnd txQueHnd;
Cppi_ChHnd    txChHnd;
Cppi_ChHnd    rxChHnd;
Cppi_Handle   cppiHnd;
Cppi_FlowHnd  rx_flowhnd;


static uint32_t l2_global_address (uint32_t addr)
{
    if(addr > 0x87FFFF){
        return addr;
    }

    return (addr + (0x10000000 + (core_id * 0x1000000)));
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


Int cppiInit(Void)
{
    Qmss_Result  re_qmss;
    Cppi_Result  re_cppi;
    Qmss_InitCfg cfg;
    Qmss_Queue   queInfo;

    MessageQ_QueueId qid;
    Notifye_Msg *notifyMsg;
    MessageQ_Params msgQ_params;
    MessageQ_Handle msg;

    Cppi_CpDmaInitCfg       cpdmaCfg;
    Cppi_RxFlowCfg          rxFlowCfg;

    Cppi_TxChInitCfg        txChCfg;
    Cppi_RxChInitCfg        rxChCfg;
    Qmss_MemRegInfo         memInfo;
    Cppi_DescCfg            descCfg;
    Cppi_Desc               *rxPkt;


    Int initDone;
    Int re;
    Int i;
    uint32_t numAllocated;
    uint8_t isAllocated;

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

    memset ((void *) &cpdmaCfg, 0, sizeof (Cppi_CpDmaInitCfg));
    cpdmaCfg.dmaNum = Cppi_CpDma_QMSS_CPDMA;
    cpdmaCfg.timeoutCount = 5000;
    cpdmaCfg.writeFifoDepth = 32;
    cppiHnd = (Cppi_Handle) Cppi_open (&cpdmaCfg);
    if (cppiHnd == NULL)
    {
        System_printf ("Error Core %d : Initializing QMSS CPPI CPDMA %d\n", core_id, cpdmaCfg.dmaNum);
    }

    memset ((void *) hostDesc, 0, SIZE_HOST_DESC * NUM_HOST_DESC);

    memset(&memInfo, 0, sizeof(memInfo));
    memInfo.descBase = (uint32_t *) l2_global_address ((uint32_t)hostDesc);
    memInfo.descNum = NUM_HOST_DESC;   // calculate
    memInfo.startIndex = core_id * NUM_HOST_DESC;
    memInfo.descSize = SIZE_HOST_DESC;
    memInfo.manageDescFlag = Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    memInfo.memRegion = (Qmss_MemRegion)core_id;

    re_qmss = Qmss_insertMemoryRegion (&memInfo);
    if (re_qmss == QMSS_MEMREGION_ALREADY_INITIALIZED)
    {
        System_printf ("Core %d : Memory region is configured\n", core_id);
    }else if (re_qmss < QMSS_SOK)
    {
        System_printf ("Error Core %d : Inserting memory region %d error code : %d\n", core_id, memInfo.memRegion, re_qmss);
        return -1;
    }

    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion = (Qmss_MemRegion) core_id;
    descCfg.descNum = NUM_HOST_DESC;
    descCfg.destQueueNum = FREE_DSC_QUEUE;
    descCfg.returnQueue.qMgr = 0;
    descCfg.returnQueue.qNum = FREE_DSC_QUEUE;//QMSS_PARAM_NOT_SPECIFIED;

    descCfg.queueType = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType = Cppi_DescType_HOST;
    descCfg.epibPresent = Cppi_EPIB_NO_EPIB_PRESENT;
    /* Descriptor should be recycled back to freeQue allocated since destQueueNum is < 0 */

    descCfg.returnPushPolicy = Qmss_Location_TAIL;
    descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;
    descCfg.cfg.host.psLocation = Cppi_PSLoc_PS_IN_DESC;
    //descCfg.cfg.mono.dataOffset = 12;//Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;

    if ((freeQueHnd = Cppi_initDescriptor (&descCfg, &numAllocated)) < 0)
    {
        System_printf ("Error Core %d : Initializing descriptor error code: %d \n", core_id, freeQueHnd);
        return -1;
    }else{
#if DEBUG
        System_printf ("Core %d : Number of descriptors requested : %d. Number of descriptors allocated : %d \n",
            corenum, descCfg.descNum, numAllocated);
#endif
    }

    if ((rxQueHnd = Qmss_queueOpen (Qmss_QueueType_HIGH_PRIORITY_QUEUE, RX_QUEUE, &isAllocated)) < 0)
    {
        System_printf ("Error Core %d : Opening Queue Number\n", core_id);
        return -1;
    }

    if ((txQueHnd = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, TX_QUEUE, &isAllocated)) < 0)
    {
        System_printf ("Error Core %d : Opening Queue Number\n", core_id);
        return -1;
    }

#if 0
    Qmss_AccCmdCfg accCmdCfg;

    accCmdCfg.channel = 8;
    accCmdCfg.command = Qmss_AccCmd_ENABLE_CHANNEL;
    accCmdCfg.interruptPacingMode = Qmss_AccPacingMode_NONE;
    accCmdCfg.listAddress = l2_global_address ((uint32_t) hiPrioList);
    accCmdCfg.listCountMode = Qmss_AccCountMode_ENTRY_COUNT;
    accCmdCfg.listEntrySize = Qmss_AccEntrySize_REG_D;
    accCmdCfg.maxPageEntries = 8 + 1;
    accCmdCfg.multiQueueMode = Qmss_AccQueueMode_SINGLE_QUEUE;
    accCmdCfg.queMgrIndex = 712;//Qmss_getQIDFromHandle (rxQueHnd);;
    accCmdCfg.queueEnMask = 0;
    accCmdCfg.timerLoadCount = 0;

    if((result = Qmss_programAccumulator(Qmss_PdspId_PDSP1, &accCmdCfg)) != QMSS_ACC_SOK){
        System_printf ("Error Core %d : Programming high priority accumulator for channel : %d queue : %d error code : %d\n",
                        corenum, accCmdCfg.channel, accCmdCfg.queMgrIndex, result);
        return  -1;
    }
#endif

    memset ((void *) &rxFlowCfg, 0, sizeof (Cppi_RxFlowCfg));
    rxFlowCfg.flowIdNum = 0;
    queInfo = Qmss_getQueueNumber (rxQueHnd);
    rxFlowCfg.rx_dest_qnum = queInfo.qNum;
    rxFlowCfg.rx_dest_qmgr = queInfo.qMgr;
    rxFlowCfg.rx_sop_offset = 0;
    rxFlowCfg.rx_desc_type = Cppi_DescType_HOST;

    queInfo = Qmss_getQueueNumber (freeQueHnd);
    rxFlowCfg.rx_fdq0_sz0_qnum = queInfo.qNum;
    rxFlowCfg.rx_fdq0_sz0_qmgr = queInfo.qMgr;
    rxFlowCfg.rx_psinfo_present = 0;
    rxFlowCfg.rx_ps_location = 0;
    rxFlowCfg.rx_error_handling = 1;

    rx_flowhnd = Cppi_configureRxFlow(cppiHnd, &rxFlowCfg, &isAllocated);
    if(rx_flowhnd == NULL){
        System_printf("Cppi_configureRxFlow error !!!!\n");
        return -1;
    }

    for(i = 0; i < CORE_NUM; i++)
    {
        if(i != core_id){
            rxChCfg.channelNum = i;
            rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
            rxChHnd = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
            if (rxChHnd == NULL)
            {
                System_printf ("Error Core %d : Opening Rx channel : %d\n", core_id, rxChCfg.channelNum);
                return -1;
            }else{
                System_printf ("Core %d : Opened Rx channel : %d\n", core_id, Cppi_getChannelNumber (rxChHnd));
            }
        }
    }

    txChCfg.channelNum = TX_CHANNEL;//CPPI_PARAM_NOT_SPECIFIED;
    txChCfg.priority = 0;
    txChCfg.filterEPIB = 0;
    txChCfg.filterPS = 0;
    txChCfg.aifMonoMode = 0;
    txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
    /* Open Tx Channel */
    txChHnd = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
    if (txChHnd == NULL)
    {
        System_printf ("Error Core %d : Opening Tx channel : %d\n", core_id, txChCfg.channelNum);
        return -1;
    }


    for(i = 0; i < NUM_HOST_DESC; i++)
    {
        if((rxPkt = (Cppi_Desc *)Qmss_queuePop(freeQueHnd)) == NULL){
            System_printf("Qmss_queuePop rx free Pkt %d is NULL !!!!!\n", i);
              continue;
        }
        rxPkt = (Cppi_Desc *) QMSS_DESC_PTR (rxPkt);
        Cppi_setData (Cppi_DescType_HOST, rxPkt, (uint8_t *)l2_global_address((uint32_t)(rxDataBuff + SIZE_RX_DATA_BUFFER * i)), SIZE_RX_DATA_BUFFER);
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, rxPkt, (uint8_t *)l2_global_address ((uint32_t) (rxDataBuff +  SIZE_RX_DATA_BUFFER * i)), SIZE_RX_DATA_BUFFER);
        Cppi_setPacketLen (Cppi_DescType_HOST, rxPkt, SIZE_RX_DATA_BUFFER);
        Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
    }

    Qmss_queueEmpty (rxQueHnd);
    Qmss_queueEmpty (txQueHnd);

    return 0;
}
