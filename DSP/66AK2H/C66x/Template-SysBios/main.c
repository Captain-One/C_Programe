/* XDC includes */
#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>
#include <xdc/cfg/global.h>
#include <string.h>

/* IPC includes */
#include <ti/ipc/GateMP.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/ListMP.h>
#include <ti/ipc/SharedRegion.h>
#include <ti/ipc/MultiProc.h>

/* sysbios includes */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


/* QMSS LLD include */
#include <ti/drv/qmss/qmss_drv.h>

/* CPPI LLD include */
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>
#include <ti/drv/cppi/cppi_osal.h>

/* RM include */
#include <ti/drv/rm/rm.h>
#include <ti/drv/rm/rm_services.h>

#include "cppi_test.h"

/* CSL RL includes */
#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_cacheAux.h>

#define SYSINIT                     0
#define SALVE1                      1
#define SALVE2                      2
#define SALVE3                      3

#ifndef NUM_CORES
#define NUM_CORES                   2
#endif

/************************ GLOBAL VARIABLES ********************/
Cppi_TxChInitCfg        txChCfg;
Cppi_RxChInitCfg        rxChCfg;
Qmss_MemRegInfo         memInfo;

//#pragma DATA_ALIGN (hostDesc, 16)
//uint8_t                 hostDesc[SIZE_HOST_DESC * NUM_HOST_DESC];
#pragma DATA_ALIGN (monolithicDesc, 16)
uint8_t                 monolithicDesc[SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC];

#pragma DATA_ALIGN (dataBuff, 16)
uint8_t                 dataBuff[SIZE_DATA_BUFFER * NUM_DATA_BUFFER];

Cppi_CpDmaInitCfg       cpdmaCfg;
Cppi_RxFlowCfg          rxFlowCfg;
Qmss_InitCfg            qmssInitConfig;

#pragma DATA_SECTION (isSysInitialized, ".qmss");
volatile uint32_t       isSysInitialized = 0;

#pragma DATA_SECTION (isLocInitDone, ".qmss");
volatile uint32_t       isLocInitDone = 0;

#pragma DATA_SECTION (isTestDone, ".qmss");
volatile uint32_t       isTestDone = 0;

#pragma DATA_SECTION (isRxflowSetDone, ".qmss");
volatile uint32_t       isRxflowSetDone = 0;

#pragma DATA_SECTION (isReciveDone, ".qmss");
volatile uint32_t       isReciveDone = 0;

#pragma DATA_SECTION (isCloseChannelDone, ".qmss");
volatile uint32_t       isCloseChannelDone = 0;

#pragma DATA_SECTION (startTeset, ".qmss");
volatile uint32_t       startTeset = 0;

#pragma DATA_SECTION (recive_ok, ".qmss");
volatile uint32_t       recive_ok = 0;

/************************ EXTERN VARIABLES ********************/
extern Qmss_GlobalConfigParams  qmssGblCfgParams;
extern Cppi_GlobalConfigParams  cppiGblCfgParams;


/*************************** FUNCTIONS ************************/
static uint32_t l2_global_address (uint32_t addr)
{
    uint32_t corenum;

    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    return (addr + (0x10000000 + (corenum * 0x1000000)));
}

Void myStartupFxn (Void)
{
    uint32_t corenum;
    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);
    MultiProc_setLocalId (corenum);
}

void usageTsk(UArg arg0, UArg arg1);

void main (void)
{
    Task_Params             taskParams;

    System_printf ("*************** CPPI LLD usage example ***********\n");

    Ipc_start();

    CSL_chipWriteReg(CSL_CHIP_TSCL, 0);
    CSL_chipWriteReg(CSL_CHIP_TSCH, 0);

    Task_Params_init (&taskParams);
    taskParams.priority = 1;
    Task_create (usageTsk, &taskParams, NULL);

    BIOS_start();
}

void usageTsk(UArg arg0, UArg arg1)
{
    int32_t                 result;
    uint32_t                corenum = 0;
    uint32_t                numAllocated, i, destLen;
    uint8_t                 *dataBuffPtr;// *destDataPtr;
    uint8_t                 isAllocated;

    Cppi_Handle             cppiHnd;

    Cppi_ChHnd              rxChHnd, rxChHnd1, rxChHnd2, rxChHnd3, rxChHnd4, rxChHnd5,  rxChHnd6,  rxChHnd7, txChHnd, txChHnd1, txChHnd2, txChHnd3, txChHnd4, txChHnd5, txChHnd6, txChHnd7;
    Qmss_QueueHnd           txQueHnd, txQueHnd1, txQueHnd2, txQueHnd3, txQueHnd4, txQueHnd5,  txQueHnd6,  txQueHnd7, rxQueHnd, freeQueHnd;
    Cppi_DescCfg            descCfg;
    Cppi_Desc               *hostDescPtr,  *hostDescPtr1, *hostDescPtr2, *hostDescPtr3,  *hostDescPtr4,  *hostDescPtr5, *hostDescPtr6, *hostDescPtr7, *rxPkt;

    Qmss_Result             region = -1;
    Qmss_Queue              queInfo;
    Cppi_FlowHnd            rx_flowhnd;
    Cppi_DescTag            Tag;

    uint32_t   start_time = 0;
    uint32_t   start_time_H = 0;
    uint32_t   end_time = 0;
    uint32_t   end_time_H = 0;

    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    if (corenum == SYSINIT)
    {
        memset ((void *) &qmssInitConfig, 0, sizeof (Qmss_InitCfg));

        qmssInitConfig.linkingRAM0Base = 0;
        qmssInitConfig.linkingRAM0Size = 0;
        qmssInitConfig.linkingRAM1Base = 0;
        qmssInitConfig.maxDescNum      = (NUM_HOST_DESC + NUM_MONOLITHIC_DESC) * NUM_CORES;

        result = Qmss_init (&qmssInitConfig, &qmssGblCfgParams);
        if (result != QMSS_SOK)
        {
            System_printf ("Error Core %d : Initializing Queue Manager SubSystem error code : %d\n", corenum, result);
            return;
        }

        result = Qmss_start ();
        if (result != QMSS_SOK)
        {
            System_printf ("Core %d : Error starting Queue Manager error code : %d\n", corenum, result);
        }
        else
            System_printf ("\nCore %d : QMSS initialization done\n", corenum);

        result = Cppi_init (&cppiGblCfgParams);
        if (result != CPPI_SOK)
        {
            System_printf ("Error Core %d : Initializing CPPI LLD error code : %d\n", corenum, result);
        }

        isLocInitDone = 1;
        CACHE_wbL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);

        isSysInitialized = 1;
        CACHE_wbL1d ((void *) &isSysInitialized, 4, CACHE_WAIT);
    }else{
        System_printf ("Core %d : Waiting for QMSS to be initialized...\n\n", corenum);
        do{
            CACHE_invL1d ((void *) &isSysInitialized, 4, CACHE_WAIT);
        } while (isSysInitialized == 0);

        result = Qmss_start ();
        if (result != QMSS_SOK)
        {
            System_printf ("Core %d : Error starting Queue Manager error code : %d\n", corenum, result);
        }
        else
            System_printf ("\nCore %d : QMSS initialization done\n", corenum);

        Osal_cppiCsEnter();
        CACHE_invL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);
        isLocInitDone += 1;

        CACHE_wbL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);
        Osal_cppiCsExit(NULL);
    }

    do{
        CACHE_invL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);
    } while (isLocInitDone < NUM_CORES);


    memset ((void *) &cpdmaCfg, 0, sizeof (Cppi_CpDmaInitCfg));
    cpdmaCfg.dmaNum = Cppi_CpDma_QMSS_CPDMA;
    cppiHnd = (Cppi_Handle) Cppi_open (&cpdmaCfg);
    if (cppiHnd == NULL)
    {
        System_printf ("Error Core %d : Initializing QMSS CPPI CPDMA %d\n", corenum, cpdmaCfg.dmaNum);
    }
    else
        System_printf ("\nCore %d : QMSS CPDMA Opened\n\n", corenum);

    memset ((void *) monolithicDesc, 0, SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC);

    memset(&memInfo, 0, sizeof(memInfo));
    memInfo.descBase = (uint32_t *) l2_global_address ((uint32_t)monolithicDesc);
    memInfo.descSize = SIZE_MONOLITHIC_DESC;
    memInfo.descNum = NUM_MONOLITHIC_DESC;
    memInfo.manageDescFlag = Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    memInfo.memRegion = (Qmss_MemRegion) corenum;
    memInfo.startIndex = corenum * NUM_MONOLITHIC_DESC;

    result = Qmss_insertMemoryRegion (&memInfo);
    if (result == QMSS_MEMREGION_ALREADY_INITIALIZED)
    {
        System_printf ("Core %d : Memory region is configured\n", corenum);
    }else if (result < QMSS_SOK)
    {
        System_printf ("Error Core %d : Inserting memory region %d error code : %d\n", corenum, memInfo.memRegion, result);
        return;
    }else{
        System_printf ("Core %d : Memory region %d inserted\n", corenum, result);
        region = result;
    }

    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion = (Qmss_MemRegion) corenum;
    descCfg.descNum = NUM_MONOLITHIC_DESC/4;
    if(corenum == 0){
        descCfg.destQueueNum = 500;
        descCfg.returnQueue.qMgr = 0;
        descCfg.returnQueue.qNum = 500;//QMSS_PARAM_NOT_SPECIFIED;
    }else{
        descCfg.destQueueNum = 501;
        descCfg.returnQueue.qMgr = 0;
        descCfg.returnQueue.qNum = 501;//QMSS_PARAM_NOT_SPECIFIED;
    }
    descCfg.queueType = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType = Cppi_DescType_MONOLITHIC;
    descCfg.epibPresent = Cppi_EPIB_NO_EPIB_PRESENT;
    /* Descriptor should be recycled back to freeQue allocated since destQueueNum is < 0 */

    descCfg.returnPushPolicy = Qmss_Location_TAIL;
    //descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;
    //descCfg.cfg.host.psLocation = Cppi_PSLoc_PS_IN_DESC;
    descCfg.cfg.mono.dataOffset = 12;//Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;

    if ((freeQueHnd = Cppi_initDescriptor (&descCfg, &numAllocated)) < 0)
    {
        System_printf ("Error Core %d : Initializing descriptor error code: %d \n", corenum, freeQueHnd);
        return;
    }
    else
        System_printf ("Core %d : Number of descriptors requested : %d. Number of descriptors allocated : %d \n",
            corenum, descCfg.descNum, numAllocated);

    if(corenum == SYSINIT){
        if ((rxQueHnd = Qmss_queueOpen (Qmss_QueueType_HIGH_PRIORITY_QUEUE , 712, &isAllocated)) < 0)
        {
            System_printf ("Error Core %d : Opening Queue Number\n", corenum);
            return;
        }
        else
            System_printf ("Core %d : Queue Number : %d opened\n", corenum, rxQueHnd);

        memset ((void *) &rxFlowCfg, 0, sizeof (Cppi_RxFlowCfg));
        rxFlowCfg.flowIdNum = 0;
        queInfo = Qmss_getQueueNumber (rxQueHnd);
        rxFlowCfg.rx_dest_qnum = queInfo.qNum;
        rxFlowCfg.rx_dest_qmgr = queInfo.qMgr;
        rxFlowCfg.rx_sop_offset = 12;
        rxFlowCfg.rx_desc_type = Cppi_DescType_MONOLITHIC;
        System_printf ("Core %d : Rx  Queue Number : %d opened£¬qmgr is %d\n", corenum, queInfo.qNum, queInfo.qMgr);
        queInfo = Qmss_getQueueNumber (freeQueHnd);
        rxFlowCfg.rx_fdq0_sz0_qnum = 500;//queInfo.qNum;
        rxFlowCfg.rx_fdq0_sz0_qmgr = 0;//queInfo.qMgr;
        rxFlowCfg.rx_psinfo_present = 0;
        rxFlowCfg.rx_ps_location = 0;
        System_printf ("Core %d : Free RX Queue Number : %d opened£¬qmgr is %d\n", corenum, queInfo.qNum, queInfo.qMgr);
        rx_flowhnd = Cppi_configureRxFlow(cppiHnd, &rxFlowCfg, &isAllocated);
        if(rx_flowhnd == NULL){
            System_printf("Cppi_configureRxFlow error !!!!\n");
        }else{
            System_printf("Cppi_configureRxFlow OKOKOK !!!!\n");
        }

        isRxflowSetDone = 1;
        CACHE_wbL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);

        rxChCfg.channelNum = 0;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        if (rxChHnd == NULL)
        {
            System_printf ("Error Core %d : Opening Rx channel : %d\n", corenum, rxChCfg.channelNum);
            return;
        }
        else
            System_printf ("Core %d : Opened Rx channel : %d\n", corenum, Cppi_getChannelNumber (rxChHnd));

        rxChCfg.channelNum = 1;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd1 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        if (rxChHnd1 == NULL)
        {
            System_printf ("Error Core %d : Opening Rx channel : %d\n", corenum, rxChCfg.channelNum);
            return;
        }
        else
            System_printf ("Core %d : Opened Rx channel : %d\n", corenum, Cppi_getChannelNumber (rxChHnd1));

        rxChCfg.channelNum = 2;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd2 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        if (rxChHnd2 == NULL)
        {
            System_printf ("Error Core %d : Opening Rx channel : %d\n", corenum, rxChCfg.channelNum);
            return;
        }
        else
            System_printf ("Core %d : Opened Rx channel : %d\n", corenum, Cppi_getChannelNumber (rxChHnd2));

        rxChCfg.channelNum = 3;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd3 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        if (rxChHnd3 == NULL)
        {
            System_printf ("Error Core %d : Opening Rx channel : %d\n", corenum, rxChCfg.channelNum);
            return;
        }
        else
            System_printf ("Core %d : Opened Rx channel : %d\n", corenum, Cppi_getChannelNumber (rxChHnd3));
        rxChCfg.channelNum = 4;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd4 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        rxChCfg.channelNum = 5;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd5 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        rxChCfg.channelNum = 6;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd6 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
        rxChCfg.channelNum = 7;
        rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;
        rxChHnd7 = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);

            startTeset = 1;
            CACHE_wbL1d ((void *) &startTeset, 4, CACHE_WAIT);
            //int re = 0;
            //for(i = 0; i< 4; i++)
            //{
            while (Qmss_getQueueEntryCount (rxQueHnd) != 8);

            //}
            //System_flush();
            recive_ok = 1;
            CACHE_wbL1d ((void *) &recive_ok, 4, CACHE_WAIT);
            int j;
            for(j = 0; j < 8; j++){
                if ((rxPkt = (Cppi_Desc *) Qmss_queuePop (rxQueHnd)) == NULL)
                {
                    System_printf("Qmss_queuePop rxPkt is NULL !!!!!\n");
                    return;
                }

                System_printf("rxPkt 0x%08x\n", rxPkt);
                rxPkt = (Cppi_Desc *) QMSS_DESC_PTR (rxPkt);
                //Cppi_getPSData (Cppi_DescType_MONOLITHIC, Cppi_PSLoc_PS_IN_DESC, rxPkt, &destDataPtr, &destLen);
                Cppi_getData (Cppi_DescType_MONOLITHIC, rxPkt, &dataBuffPtr, &destLen);
                System_printf("dataBuffPtr 0x%08x\n", dataBuffPtr);
                System_printf("destLen is %d, dataBuffPtr[0]: 0x%02x \n", destLen, dataBuffPtr[0]);
                //queInfo = Cppi_getReturnQueue (Cppi_DescType_HOST, rxPkt);
                Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
                System_printf ("get %d Entry Count\n", i);
            }


        if ((result = Cppi_channelClose (rxChHnd)) < 0)
            System_printf ("Error Core %d : Closing Rx channel error code: %d\n", corenum, result);
        if ((result = Cppi_channelClose (rxChHnd1)) < 0)
            System_printf ("Error Core %d : Closing Rx channel error code: %d\n", corenum, result);
        if ((result = Cppi_channelClose (rxChHnd2)) < 0)
                    System_printf ("Error Core %d : Closing Rx channel error code: %d\n", corenum, result);
        if ((result = Cppi_channelClose (rxChHnd3)) < 0)
                    System_printf ("Error Core %d : Closing Rx channel error code: %d\n", corenum, result);
        Cppi_channelClose (rxChHnd4);
        Cppi_channelClose (rxChHnd5);
        Cppi_channelClose (rxChHnd6);
        Cppi_channelClose (rxChHnd7);
        Qmss_queueEmpty (rxQueHnd);
        Qmss_queueEmpty (freeQueHnd);
        if ((result = Qmss_queueClose (rxQueHnd)) < 0)
            System_printf ("Error Core %d : Closing Rx queue error code: %d\n", corenum, result);
        if ((result = Qmss_queueClose (freeQueHnd)) < 0)
            System_printf ("Error Core %d : Closing free queue error code: %d\n", corenum, result);

        if((result = Cppi_closeRxFlow(rx_flowhnd)) < 0)
            System_printf ("Error Core %d : Closing Rx flow error code: %d\n", corenum, result);

        System_printf("core 0 queue close done!\n");
        isReciveDone = 1;
        CACHE_wbL1d ((void *) &isReciveDone, 4, CACHE_WAIT);
    }else{
            if ((txQueHnd = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 800, &isAllocated)) < 0)
            {
                System_printf ("Error Core %d : Opening Queue Number\n", corenum);
                return;
            }else{
                System_printf ("Core %d : Queue Number : %d opened\n", corenum, txQueHnd);
            }

            if ((txQueHnd1 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 801, &isAllocated)) < 0)
            {
                System_printf ("Error Core %d : Opening Queue Number\n", corenum);
                return;
            }else{
                System_printf ("Core %d : Queue Number : %d opened\n", corenum, txQueHnd1);
            }

            if ((txQueHnd2 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 802, &isAllocated)) < 0)
            {
                System_printf ("Error Core %d : Opening Queue Number\n", corenum);
                return;
            }else{
                System_printf ("Core %d : Queue Number : %d opened\n", corenum, txQueHnd2);
            }

            if ((txQueHnd3 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 803, &isAllocated)) < 0)
            {
                System_printf ("Error Core %d : Opening Queue Number\n", corenum);
                return;
            }else{
                System_printf ("Core %d : Queue Number : %d opened\n", corenum, txQueHnd3);
            }

            txQueHnd4 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 804, &isAllocated);
            txQueHnd5 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 805, &isAllocated);
            txQueHnd6 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 806, &isAllocated);
            txQueHnd7 = Qmss_queueOpen (Qmss_QueueType_INFRASTRUCTURE_QUEUE, 807, &isAllocated);

            //set data
            for (i = 0; i < SIZE_DATA_BUFFER/8; i++)
            {
                dataBuff[i] = 0xA5;
                dataBuff[SIZE_DATA_BUFFER/8 + i] = 0xB5;
                dataBuff[(SIZE_DATA_BUFFER*2)/8 + i] = 0xc5;
                dataBuff[(SIZE_DATA_BUFFER*3)/8 + i] = 0xD5;
                dataBuff[(SIZE_DATA_BUFFER*4)/8 + i] = 0xE5;
                dataBuff[(SIZE_DATA_BUFFER*5)/8 + i] = 0xF5;
                dataBuff[(SIZE_DATA_BUFFER*6)/8 + i] = 0x5A;
                dataBuff[(SIZE_DATA_BUFFER*7)/8 + i] = 0x5B;
            }

            System_printf("0x%02x, 0x%02x, 0x%02x, 0x%02x\n",dataBuff[0], dataBuff[SIZE_DATA_BUFFER/8], dataBuff[(SIZE_DATA_BUFFER*2)/8], dataBuff[(SIZE_DATA_BUFFER*3)/8]);

            do{
                CACHE_invL1d ((void *) &isRxflowSetDone, 4, CACHE_WAIT);
            } while (isRxflowSetDone == 0);

            txChCfg.channelNum = 0;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.priority = 0;
            txChCfg.filterEPIB = 0;
            txChCfg.filterPS = 0;
            txChCfg.aifMonoMode = 0;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            /* Open Tx Channel */
            txChHnd = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            if (txChHnd == NULL)
            {
                System_printf ("Error Core %d : Opening Tx channel : %d\n", corenum, txChCfg.channelNum);
                return;
            }
            else
                System_printf ("Core %d : Opened Tx channel : %d\n", corenum, Cppi_getChannelNumber (txChHnd));

            txChCfg.channelNum = 1;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd1 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            if (txChHnd1 == NULL)
            {
                System_printf ("Error Core %d : Opening Tx channel : %d\n", corenum, txChCfg.channelNum);
                return;
            }
            else
                System_printf ("Core %d : Opened Tx channel : %d\n", corenum, Cppi_getChannelNumber (txChHnd1));

            txChCfg.channelNum = 2;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd2 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            if (txChHnd2 == NULL)
            {
                System_printf ("Error Core %d : Opening Tx channel : %d\n", corenum, txChCfg.channelNum);
                return;
            }
            else
                System_printf ("Core %d : Opened Tx channel : %d\n", corenum, Cppi_getChannelNumber (txChHnd2));

            txChCfg.channelNum = 3;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd3 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            if (txChHnd3 == NULL)
            {
                System_printf ("Error Core %d : Opening Tx channel : %d\n", corenum, txChCfg.channelNum);
                return;
            }
            else
                System_printf ("Core %d : Opened Tx channel : %d\n", corenum, Cppi_getChannelNumber (txChHnd3));

            txChCfg.channelNum = 4;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd4 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            txChCfg.channelNum = 5;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd5 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            txChCfg.channelNum = 6;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd6 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);
            txChCfg.channelNum = 7;//CPPI_PARAM_NOT_SPECIFIED;
            txChCfg.txEnable = Cppi_ChState_CHANNEL_ENABLE;
            txChHnd7 = (Cppi_ChHnd) Cppi_txChannelOpen (cppiHnd, &txChCfg, &isAllocated);

            for(i = 0; i< 1; i++)
            {
                Tag.srcTagLo = 0;
                hostDescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr, (uint8_t *) l2_global_address ((uint32_t) dataBuff), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr, SIZE_DATA_BUFFER/8);

                hostDescPtr1 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr1, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + SIZE_DATA_BUFFER/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr1, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr1, SIZE_DATA_BUFFER/8);

                hostDescPtr2 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr2, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + (SIZE_DATA_BUFFER*2)/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr2, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr2, SIZE_DATA_BUFFER/8);

                hostDescPtr3 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr3, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + (SIZE_DATA_BUFFER*3)/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr3, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr3, SIZE_DATA_BUFFER/8);

                hostDescPtr4 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr4, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + (SIZE_DATA_BUFFER*4)/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr4, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr4, SIZE_DATA_BUFFER/8);

                hostDescPtr5 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr5, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + (SIZE_DATA_BUFFER*5)/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr5, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr5, SIZE_DATA_BUFFER/8);

                hostDescPtr6 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr6, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + (SIZE_DATA_BUFFER*6)/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr6, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr6, SIZE_DATA_BUFFER/8);

                hostDescPtr7 = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
                Cppi_setData (Cppi_DescType_MONOLITHIC, hostDescPtr7, (uint8_t *) l2_global_address ((uint32_t) (dataBuff + (SIZE_DATA_BUFFER*7)/8)), SIZE_DATA_BUFFER/8);
                Cppi_setTag(Cppi_DescType_MONOLITHIC, hostDescPtr7, &Tag);
                Cppi_setPacketLen (Cppi_DescType_MONOLITHIC, hostDescPtr7, SIZE_DATA_BUFFER/8);

                do{
                    CACHE_invL1d ((void *) &startTeset, 4, CACHE_WAIT);
                } while (startTeset == 0);

                start_time = CSL_chipReadReg(CSL_CHIP_TSCL);
                start_time_H = CSL_chipReadReg(CSL_CHIP_TSCH);
                Qmss_queuePushDescSize (txQueHnd, (Ptr) hostDescPtr, 256);
                Qmss_queuePushDescSize (txQueHnd1, (Ptr) hostDescPtr1, 256);
                Qmss_queuePushDescSize (txQueHnd2, (Ptr) hostDescPtr2, 256);
                Qmss_queuePushDescSize (txQueHnd3, (Ptr) hostDescPtr3, 256);
                Qmss_queuePushDescSize (txQueHnd4, (Ptr) hostDescPtr4, 256);
                Qmss_queuePushDescSize (txQueHnd5, (Ptr) hostDescPtr5, 256);
                Qmss_queuePushDescSize (txQueHnd6, (Ptr) hostDescPtr6, 256);
                Qmss_queuePushDescSize (txQueHnd7, (Ptr) hostDescPtr7, 256);
                //result = Qmss_getQueueEntryCount (txQueHnd);
                //if(result == 0){

                    do{
                        CACHE_invL1d ((void *) &recive_ok, 4, CACHE_WAIT);
                    } while (recive_ok == 0);
                    end_time = CSL_chipReadReg(CSL_CHIP_TSCL);
                    end_time_H = CSL_chipReadReg(CSL_CHIP_TSCH);
                //}
                System_printf ("Transmit Queue %d Entry Count : %d Tx descriptor 0x%p\n", txQueHnd, result, hostDescPtr);
                System_printf("****start_time : 0x%08x , H : 0x%08x, end_time : 0x%08x , H : 0x%08x\n",start_time, start_time_H, end_time, end_time_H);
                System_printf("****trans time is : %u\n", end_time - start_time);
            }
      }

    do{
        CACHE_invL1d ((void *) &isReciveDone, 4, CACHE_WAIT);
    } while (isReciveDone == 0);

    if(corenum != 0){
        if ((result = Cppi_channelClose (txChHnd)) < 0)
            System_printf ("Error Core %d : Closing Tx channel error code: %d\n", corenum, result);
        if ((result = Cppi_channelClose (txChHnd1)) < 0)
            System_printf ("Error Core %d : Closing Tx channel error code: %d\n", corenum, result);
        if ((result = Cppi_channelClose (txChHnd2)) < 0)
                    System_printf ("Error Core %d : Closing Tx channel error code: %d\n", corenum, result);
        if ((result = Cppi_channelClose (txChHnd3)) < 0)
                    System_printf ("Error Core %d : Closing Tx channel error code: %d\n", corenum, result);
        Cppi_channelClose (txChHnd4);
        Cppi_channelClose (txChHnd5);
        Cppi_channelClose (txChHnd6);
        Cppi_channelClose (txChHnd7);
        Qmss_queueEmpty (txQueHnd);
        Qmss_queueEmpty (txQueHnd1);
        Qmss_queueEmpty (txQueHnd2);
        Qmss_queueEmpty (txQueHnd3);
        Qmss_queueEmpty (txQueHnd4);
        Qmss_queueEmpty (txQueHnd5);
        Qmss_queueEmpty (txQueHnd6);
        Qmss_queueEmpty (txQueHnd7);
        Qmss_queueEmpty (freeQueHnd);
        if ((result = Qmss_queueClose (txQueHnd)) < 0)
            System_printf ("Error Core %d : Closing tx queue error code: %d\n", corenum, result);
        if ((result = Qmss_queueClose (txQueHnd1)) < 0)
            System_printf ("Error Core %d : Closing tx queue error code: %d\n", corenum, result);
        if ((result = Qmss_queueClose (txQueHnd2)) < 0)
                    System_printf ("Error Core %d : Closing tx queue error code: %d\n", corenum, result);
        if ((result = Qmss_queueClose (txQueHnd3)) < 0)
                    System_printf ("Error Core %d : Closing tx queue error code: %d\n", corenum, result);
        Qmss_queueClose (txQueHnd4);
        Qmss_queueClose (txQueHnd5);
        Qmss_queueClose (txQueHnd6);
        Qmss_queueClose (txQueHnd7);
        if ((result = Qmss_queueClose (freeQueHnd)) < 0)
            System_printf ("Error Core %d : Closing free queue error code: %d\n", corenum, result);

        Osal_cppiCsEnter();
        CACHE_invL1d ((void *) &isCloseChannelDone, 4, CACHE_WAIT);
        isCloseChannelDone += 1;

        CACHE_wbL1d ((void *) &isCloseChannelDone, 4, CACHE_WAIT);
        Osal_cppiCsExit(NULL);
        System_printf("core %d queue close done!\n", corenum);
    }

    do{
        CACHE_invL1d ((void *) &isCloseChannelDone, 4, CACHE_WAIT);
    } while (isCloseChannelDone < NUM_CORES - 1);

    if ((result = Cppi_close (cppiHnd)) != CPPI_SOK)
    {
        System_printf ("Core %d : Closing CPPI CPDMA Ref count : %d\n", corenum, result);
        while (result < CPPI_SOK)
            result = Cppi_close (cppiHnd);
        System_printf ("Core %d : CPPI CPDMA closed successfully\n", corenum);
    }
    else
        System_printf ("Core %d : CPPI CPDMA closed successfully\n", corenum);

    /* Now clear the regions */
    if (region >= 0)
    {
        if ( (result = Qmss_removeMemoryRegion (region, 0)) != QMSS_SOK)
        {
            System_printf ("Error removing memory region %d: %d\n", region, result);
        }
    }

    /* Indicate that the test is complete at this core */
    Osal_cppiCsEnter();
    CACHE_invL1d ((void *) &isTestDone, 4, CACHE_WAIT);
    isTestDone += 1;
    /* Writeback L1D */
    CACHE_wbL1d ((void *) &isTestDone, 4, CACHE_WAIT);
    Osal_cppiCsExit(NULL);

    /* Synchronize all consumer cores. They must wait for the producer core to finish test. */
    do{
        CACHE_invL1d ((void *) &isTestDone, 4, CACHE_WAIT);
    } while (isTestDone < NUM_CORES);

    /* Deinitialize CPPI LLD */
    if ((result = Cppi_exit ()) != CPPI_SOK)
    {
        System_printf ("Core %d : Exiting CPPI Ref count : %d\n", corenum, result);
        while (result < CPPI_SOK)
            result = Cppi_exit ();
        System_printf ("Core %d : CPPI exit successful\n", corenum);
    }
    else
        System_printf ("Core %d : CPPI exit successful\n", corenum);

    /* Exit QMSS */
    if (corenum == SYSINIT)
    {
        System_printf ("Core %d: exit QMSS\n", corenum);
        while ((result = Qmss_exit()) != QMSS_SOK);
    }

    System_printf ("*************** CPPI LLD usage example Done ***********\n");
    System_flush();

    BIOS_exit(0);
}

