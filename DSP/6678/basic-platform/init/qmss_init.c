/*
 * qmss_init.c
 *
 *  Created on: 2019年4月24日
 *      Author: pu
 */

#include "qmss_init.h"
#include <string.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/csl/csl_cacheAux.h>

#include <xdc/runtime/System.h>

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
extern UInt16 const core_id;

/* linking RAM */
//#pragma DATA_ALIGN (linkingRAM0, 16)
//uint64_t            linkingRAM0[NUM_HOST_DESC + NUM_MONOLITHIC_DESC];
//#pragma DATA_ALIGN (monolithicDesc, 16)
//uint8_t             monolithicDesc[SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC];
//#pragma DATA_ALIGN (dataBuff, 16)
//uint8_t             dataBuff[SIZE_DATA_BUFFER * NUM_DATA_BUFFER];

#pragma DATA_SECTION(ps_info, ".L2RAM")
Ps_Info  ps_info = {0};

/* Descriptor pool [Size of descriptor * Number of descriptors] */
#pragma DATA_SECTION(hostDesc, ".L2RAM")
#pragma DATA_ALIGN (hostDesc, 16)
uint8_t             hostDesc[SIZE_HOST_DESC * NUM_HOST_DESC];  //128 * 64 = 8k;

#pragma DATA_SECTION(rxDataBuff, ".L2RAM")
#pragma DATA_ALIGN (rxDataBuff, 16)
uint8_t             rxDataBuff[SIZE_RX_DATA_BUFFER * NUM_RX_DATA_BUFFER];

int32_t const rxQueNum[8] = {-1, 704, 705, 706, 832, 833, 834, 835};
int16_t const flowIdNum[8] = {-1, 1, 2, 3, 4, 5, 6, 7};  //id 1--7 核零接收其他七个核的数据

Qmss_QueueHnd freeQueHnd;
Qmss_QueueHnd rxQueHnd[CORE_NUM - 1];
Qmss_QueueHnd txQueHnd;
Cppi_ChHnd    txChHnd;
Cppi_ChHnd    rxChHnd;
Cppi_Handle   cppiHnd;
Cppi_FlowHnd  rx_flowhnd;

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

static uint32_t l2_global_address (uint32_t addr)
{
    if(addr > 0x87FFFF){
        return addr;
    }

    return (addr + (0x10000000 + (core_id * 0x1000000)));
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

    String masterMsgQName = MASTER_MSGQ_NAME;

    memset ((void *) &cfg, 0, sizeof (Qmss_InitCfg));

    cfg.linkingRAM0Base = 0;
    cfg.linkingRAM0Size = 0;
    cfg.linkingRAM1Base = 0;
    cfg.maxDescNum = CORE_NUM * NUM_HOST_DESC;
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

    //all core init done
    System_printf("core %d cppi init done! \n", core_id);

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
    descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_BUFFER;//Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;//;//
    descCfg.cfg.host.psLocation = Cppi_PSLoc_PS_IN_DESC;


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

    memset ((void *) &rxFlowCfg, 0, sizeof (Cppi_RxFlowCfg));
    rxFlowCfg.rx_sop_offset = 0;
    rxFlowCfg.rx_desc_type = Cppi_DescType_HOST;

    queInfo = Qmss_getQueueNumber (freeQueHnd);
    rxFlowCfg.rx_fdq0_sz0_qnum = queInfo.qNum;
    rxFlowCfg.rx_fdq0_sz0_qmgr = queInfo.qMgr;
    rxFlowCfg.rx_psinfo_present = 1;
    rxFlowCfg.rx_ps_location = 0;
    rxFlowCfg.rx_error_handling = 1;

    for(i = 0; i < CORE_NUM; i++)
    {
        if(i == core_id)
            continue;

        if((rxQueHnd[i] = Qmss_queueOpen (Qmss_QueueType_GENERAL_PURPOSE_QUEUE, rxQueNum[i], &isAllocated)) < 0)
        {
            System_printf ("Error Core %d : Opening Queue Number\n", core_id);
            return -1;
        }
        Qmss_queueEmpty (rxQueHnd[i]);

        rxFlowCfg.flowIdNum = flowIdNum[i];
        queInfo = Qmss_getQueueNumber (rxQueHnd[i]);
        rxFlowCfg.rx_dest_qnum = queInfo.qNum;
        rxFlowCfg.rx_dest_qmgr = queInfo.qMgr;

        rx_flowhnd = Cppi_configureRxFlow(cppiHnd, &rxFlowCfg, &isAllocated);
        if(rx_flowhnd == NULL){
           System_printf("Cppi_configureRxFlow error !!!!\n");
           return -1;
        }
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

    ps_info.src_core = core_id;

    for(i = 0; i < NUM_HOST_DESC; i++)
    {
        if((rxPkt = (Cppi_Desc *)Qmss_queuePop(freeQueHnd)) == NULL){
            System_printf("Qmss_queuePop rx free Pkt %d is NULL !!!!!\n", i);
              continue;
        }
        rxPkt = (Cppi_Desc *) QMSS_DESC_PTR (rxPkt);
        Cppi_setPSData (Cppi_DescType_HOST, (Cppi_Desc*)rxPkt, (uint8_t *) &ps_info, sizeof(Ps_Info));
        Cppi_setData (Cppi_DescType_HOST, rxPkt, (uint8_t *)l2_global_address((uint32_t)(rxDataBuff + SIZE_RX_DATA_BUFFER * i)), SIZE_RX_DATA_BUFFER);
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, rxPkt, (uint8_t *)l2_global_address ((uint32_t) (rxDataBuff +  SIZE_RX_DATA_BUFFER * i)), SIZE_RX_DATA_BUFFER);
        Cppi_setPacketLen (Cppi_DescType_HOST, rxPkt, SIZE_RX_DATA_BUFFER);
        Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
    }

    Qmss_queueEmpty (txQueHnd);

    System_flush();

    return 0;
}
