/*
 * qmss_init.c
 *
 *  Created on: 2019年4月24日
 *      Author: pu
 */

#include "qmss_init.h"
#include <string.h>
#include <common.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/cslr_pa_ss.h>
#include <ti/csl/tistdtypes.h>

/* CSL CHIP, SEM Functional layer includes */
#include <ti/csl/csl_chip.h>

#include <xdc/runtime/System.h>

//CPPI & QMSS
#include <ti/drv/QMSS/QMSS_drv.h>
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>
#include <ti/drv/cppi/cppi_osal.h>
#include <ti/drv/qmss/qmss_firmware.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/SharedRegion.h>

#include <nimu_cppi_qmss_iface.h>

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
uint8_t             rxDataBuff[SIZE_RX_DATA_BUFFER * NUM_HOST_DESC];

int32_t const rxQueNum[8] = {-1, 704, 705, 706, 832, 833, 834, 835};
int16_t const flowIdNum[8] = {-1, 1, 2, 3, 4, 5, 6, 7};  //id 1--7 核零接收其他七个核的数据

Qmss_QueueHnd freeQueHnd;
Qmss_QueueHnd rxQueHnd[CORE_NUM - 1];
Qmss_QueueHnd txQueHnd;
Cppi_ChHnd    txChHnd;
Cppi_ChHnd    rxChHnd;
Cppi_Handle   cppiHnd;
Cppi_FlowHnd  rx_flowhnd;

extern uint8_t     gHostDesc[MAX_DESC_SIZE * MAX_NUM_NIMU_DESC];

#if 0
/* This is the global free queue for QMSS. It holds all free descriptors which can be used */
#pragma DATA_SECTION(PafreeQueHnd, ".resmgr_handles");

/* Channels handles for CPPI DMA support of the Packet Accelerator (PA) */
#pragma DATA_SECTION(paTxChHnd, ".resmgr_handles");
#pragma DATA_SECTION(paRxChHnd, ".resmgr_handles");
#pragma DATA_SECTION(paCppiHandle,       ".resmgr_handles");

Qmss_QueueHnd PafreeQueHnd;  //以太网用
Cppi_ChHnd    paTxChHnd[NUM_PA_TX_QUEUES]; //以太网用
Cppi_ChHnd    paRxChHnd[NUM_PA_RX_CHANNELS]; //以太网用
Cppi_Handle   paCppiHandle;  //以太网用


/** ============================================================================
 *   @n@b res_mgr_qmss_freeq
 *
 *   @b Description
 *   @n This API returns the handle to the global free queue for QMSS. The global free
 *   queue maintains all usable descriptors for anyone using QMSS.
 *
 *   @param[in]  None
 *
 *   @return
 * =============================================================================
 */
Qmss_QueueHnd
NIMU_qmssGetFreeQ (void)
{
    return PafreeQueHnd;
}

/** ============================================================================
 *   @n@b NIMU_convertCoreLocal2GlobalAddr
 *
 *   @b Description
 *   @n This API converts a core local L2 address to a global L2 address.
 *
 *   @param[in]
 *   @n addr            L2 address to be converted to global.
 *
 *   @return    uint32_t
 *   @n >0              Global L2 address
 * =============================================================================
 */
uint32_t NIMU_convertCoreLocal2GlobalAddr (uint32_t  addr)
{

#if 1
    /* Get the core number. */
#ifdef _TMS320C6X
    uint32_t coreNum = CSL_chipReadReg (CSL_CHIP_DNUM);
#else
    uint32_t coreNum = 0;
#endif
    /* Check if the address is a valid Local L2 address to convert */

    if ( (addr >= (uint32_t) 0x800000) &&
         (addr <  (uint32_t) 0x900000) ) {
         /* Compute the global address. */
         return ((1 << 28) | (coreNum << 24) | (addr & 0x00ffffff));
    }
    else {
        return (addr);
        }
#endif

#if 0
#ifdef _TMS320C6X
    uint32_t coreNum;

    /* Get the core number. */
    coreNum = CSL_chipReadReg(CSL_CHIP_DNUM);

    /* Compute the global address. */
    return ((1 << 28) | (coreNum << 24) | (addr & 0x00ffffff));
#else
    return (addr);
#endif
#endif
}

/** ============================================================================
 *   @n@b NIMU_stopQmss
 *
 *   @b Description
 *   @n This API de-initializes the QMSS LLD.
 *
 *   @param[in]
 *   @n None
 *
 *   @return    int32_t
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
int32_t
NIMU_stopQmss (void)
{
    Qmss_queueClose (PafreeQueHnd);

    return 0;
}

/** ============================================================================
 *   @n@b NIMU_qmssQPushDescSize
 *
 *   @b Description
 *   @n This API implements a the queue push logic with the Cache Management
 *
 *   @param[in]  handler
 *        Queue handler
 *   @param[in]  descAddr
 *        Descriptor address
 *   @param[in]  descSize
 *        descriptor Size
 *   @return
 *   @n None
 * =============================================================================
 */
void
NIMU_qmssQPushDescSize
(
    Qmss_QueueHnd          handler,
    void                   *descAddr,
    uint32_t               descSize
)
{

    Cppi_HostDesc*         pHostDesc = (Cppi_HostDesc *) descAddr;

    if ( descAddr == NULL ) {
        //gQPushErrorCounter++;
        return;
    }
#ifdef _TMS320C6X
    /* Wb data cache */
    CACHE_wbL1d((void *)pHostDesc->buffPtr, pHostDesc->buffLen, CACHE_WAIT);
    CACHE_wbL2((void *) pHostDesc->buffPtr, pHostDesc->buffLen, CACHE_WAIT);
    CACHE_wbL1d((void *)pHostDesc, sizeof(Cppi_HostDesc), CACHE_WAIT);
    CACHE_wbL2((void *) pHostDesc, sizeof(Cppi_HostDesc), CACHE_WAIT);

    asm (" MFENCE " );
#endif
    Qmss_queuePushDescSize (handler,
                    //pHostDesc,
                    descAddr,
                    descSize
                   );
}


/** ============================================================================
 *   @n@b res_mgr_cppi_get_passhandle
 *
 *   @b Description
 *   @n This API returns the handle to the the CPPI DMA for the Packet Accelerator (PA).
 *
 *   @param[in]  None
 *
 *   @return  Cppi_Handle
 * =============================================================================
 */
Cppi_Handle
NIMU_cppiGetPASSHandle (void){
    return paCppiHandle;
}

/** ============================================================================
 *   @n@b NIMU_stopCppi
 *
 *   @b Description
 *   @n This API de-initializes the CPPI LLD.
 *
 *   @param[in]
 *   @n None
 *
 *   @return    int32_t
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
int32_t
NIMU_stopCppi
(
    NIMU_CPPI_CFG_TYPE       cfg_type
)
{
    uint32_t i;

    if (cfg_type == CPPI_CFG_PASS)
    {
        for (i = 0; i < NUM_PA_RX_CHANNELS; i++)
            Cppi_channelClose (paRxChHnd[i]);

        for (i = 0; i < NUM_PA_RX_CHANNELS; i++)
            Cppi_channelClose (paRxChHnd[i]);
    }

    return 0;
}
#endif

/*******************************/
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

    String masterMsgQName = MASTER_MSGQ_NAME;

    memset ((void *) &cfg, 0, sizeof (Qmss_InitCfg));

    //设置linkram
    cfg.linkingRAM0Base = 0;
    cfg.linkingRAM0Size = 0;
    cfg.linkingRAM1Base = 0;
    cfg.maxDescNum = (CORE_NUM * CORE_TO_CORE_NUM_DESC) + MAX_NUM_NIMU_DESC; //最大描述符数量为8个核用于核间通信的描述总合加上以太网用到的描述符总数
//19.10.14添加，网络通信用
    cfg.pdspFirmware[0].pdspId = Qmss_PdspId_PDSP1;
    cfg.pdspFirmware[0].firmware = (void *) &acc48_le;
    cfg.pdspFirmware[0].size = sizeof (acc48_le);
//!
    MessageQ_Params_init(&msgQ_params);
    msg = MessageQ_create(masterMsgQName, &msgQ_params);
    //CACHE_wbL1d(msg, 128, CACHE_WAIT);
    if(msg == NULL){
        System_printf("MessageQ_create Error\n");
        System_flush();
        return -1;
    }

    //初始化qmss
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
#if RUN_MULTI_CORE
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
#endif
    //all core init done
    System_printf("core %d cppi init done! \n", core_id);

    //设置qmss的cpdma
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

    //设置描述符存储区域
    memset(&memInfo, 0, sizeof(memInfo));
    memInfo.descBase = (uint32_t *) l2_global_address ((uint32_t)hostDesc);
    memInfo.descNum = NUM_HOST_DESC;   // calculate
    memInfo.startIndex = core_id * NUM_HOST_DESC;   //添加以太网后，从核此处的设置需要加上以太网用到的描述符数量
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
#if 0
    //以太网描述区域设置
    memset(&memInfo, 0, sizeof(memInfo));
    memInfo.descBase = (uint32_t *) l2_global_address ((uint32_t)gHostDesc);
    memInfo.descNum = NUM_HOST_DESC;   // calculate
    memInfo.startIndex = core_id * NUM_HOST_DESC;   //添加以太网后，从核此处的设置需要加上以太网用到的描述符数量
    memInfo.descSize = SIZE_HOST_DESC;
    memInfo.manageDescFlag = Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    memInfo.memRegion = (Qmss_MemRegion)Qmss_MemRegion_MEMORY_REGION8;

    re_qmss = Qmss_insertMemoryRegion (&memInfo);
    if (re_qmss == QMSS_MEMREGION_ALREADY_INITIALIZED)
    {
        System_printf ("Core %d : Memory region is configured\n", core_id);
    }else if (re_qmss < QMSS_SOK)
    {
        System_printf ("Error Core %d : Inserting memory region %d error code : %d\n", core_id, memInfo.memRegion, re_qmss);
        return -1;
    }
#endif
    //分配核间数据传输用到的描述符及队列
    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion = (Qmss_MemRegion) core_id;
    descCfg.descNum = CORE_TO_CORE_NUM_DESC;
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

    //设置接收流
    memset ((void *) &rxFlowCfg, 0, sizeof (Cppi_RxFlowCfg));
    rxFlowCfg.rx_sop_offset = 0;
    rxFlowCfg.rx_desc_type = Cppi_DescType_HOST;

    queInfo = Qmss_getQueueNumber (freeQueHnd);
    rxFlowCfg.rx_fdq0_sz0_qnum = queInfo.qNum;
    rxFlowCfg.rx_fdq0_sz0_qmgr = queInfo.qMgr;
    rxFlowCfg.rx_psinfo_present = 1;
    rxFlowCfg.rx_ps_location = 0;
    rxFlowCfg.rx_error_handling = 1;

    //打开接收队列
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

    //打开发送队列
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

//设置接收通道
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

    //打开发送通道
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
//绑定主机包描述符缓冲区
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

    //以太网QMSS初始化
#if 0
    //分配初始化以太网PA用到的描述符及指定队列号
    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion = (Qmss_MemRegion) core_id;
    descCfg.descNum = NIMU_MAX_NUM_DESC;
    descCfg.destQueueNum = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.returnQueue.qMgr = 0;
    descCfg.returnQueue.qNum = QMSS_PARAM_NOT_SPECIFIED;//QMSS_PARAM_NOT_SPECIFIED;

    descCfg.queueType = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType = Cppi_DescType_HOST;
    descCfg.epibPresent = Cppi_EPIB_EPIB_PRESENT;
    /* Descriptor should be recycled back to freeQue allocated since destQueueNum is < 0 */

    descCfg.returnPushPolicy = Qmss_Location_TAIL;
    descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;//Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;//;//
    descCfg.cfg.host.psLocation = Cppi_PSLoc_PS_IN_DESC;


    if ((PafreeQueHnd = Cppi_initDescriptor (&descCfg, &numAllocated)) < 0)
    {
        System_printf ("Error Core %d : Initializing descriptor error code: %d \n", core_id, PafreeQueHnd);
        return -1;
    }

    //设置CPDMA
    memset ((void *) &cpdmaCfg, 0, sizeof (Cppi_CpDmaInitCfg));
    cpdmaCfg.dmaNum = Cppi_CpDma_PASS_CPDMA;
    paCppiHandle = (Cppi_Handle) Cppi_open (&cpdmaCfg);
    if (paCppiHandle == NULL)
    {
        System_printf ("Error Core %d : Initializing QMSS CPPI CPDMA %d\n", core_id, cpdmaCfg.dmaNum);
    }

    /* Open all CPPI Tx Channels. These will be used to send data to PASS/CPSW */
    for (i = 0; i < NUM_PA_TX_QUEUES; i ++)
    {
        txChCfg.channelNum      =   i;       /* CPPI channels are mapped one-one to the PA Tx queues */
        txChCfg.txEnable        =   Cppi_ChState_CHANNEL_DISABLE;  /* Disable the channel for now. */
        txChCfg.filterEPIB      =   0;
        txChCfg.filterPS        =   0;
        txChCfg.aifMonoMode     =   0;
        txChCfg.priority        =   2;

        if ((paTxChHnd[i] = Cppi_txChannelOpen (paCppiHandle, &txChCfg, &isAllocated)) == NULL)
        {
            System_printf ("Error opening Tx channel %d\n", txChCfg.channelNum);
            return -1;
        }

        Cppi_channelEnable (paTxChHnd[i]);
    }

    /* Open all CPPI Rx channels. These will be used by PA to stream data out. */
    for (i = 0; i < NUM_PA_RX_CHANNELS; i++)
    {
        /* Open a CPPI Rx channel that will be used by PA to stream data out. */
        rxChCfg.channelNum  =   i;
        rxChCfg.rxEnable    =   Cppi_ChState_CHANNEL_DISABLE;
        if ((paRxChHnd[i] = Cppi_rxChannelOpen (paCppiHandle, &rxChCfg, &isAllocated)) == NULL)
        {
            System_printf("Error opening Rx channel: %d \n", rxChCfg.channelNum);
            return -1;
        }

        /* Also enable Rx Channel */
        Cppi_channelEnable (paRxChHnd[i]);
    }

    /* Clear CPPI Loobpack bit in PASS CDMA Global Emulation Control Register */
    Cppi_setCpdmaLoopback(paCppiHandle, 0);
#endif

    System_flush();

    return 0;
}
