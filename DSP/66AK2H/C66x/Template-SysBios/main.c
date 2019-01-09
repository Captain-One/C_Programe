/**
 *   @file  sample.c
 *
 *   @brief
 *      This is the CPPI Low Level Driver example file.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2009-2014, Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  \par
*/

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

#define RM 0

#define SYSINIT                     0
#ifndef NUM_CORES
#define NUM_CORES                   4
#endif

#define MAPPED_VIRTUAL_ADDRESS      0x81000000

/* MPAX segment 2 registers */
#define XMPAXL2                     0x08000010
#define XMPAXH2                     0x08000014

/************************ GLOBAL VARIABLES ********************/
/* Tx channel configuration */
Cppi_TxChInitCfg        txChCfg;
/* Rx channel configuration */
Cppi_RxChInitCfg        rxChCfg;
/* Memory region configuration information */
Qmss_MemRegInfo         memInfo;

/* linking RAM */
#pragma DATA_ALIGN (linkingRAM0, 16)
uint64_t                linkingRAM0[(NUM_HOST_DESC + NUM_MONOLITHIC_DESC) * NUM_CORES];
/* Descriptor pool [Size of descriptor * Number of descriptors] */
#pragma DATA_ALIGN (hostDesc, 16)
uint8_t                 hostDesc[SIZE_HOST_DESC * NUM_HOST_DESC];
#pragma DATA_ALIGN (monolithicDesc, 16)
uint8_t                 monolithicDesc[SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC];
#pragma DATA_ALIGN (dataBuff, 16)
uint8_t                 dataBuff[SIZE_DATA_BUFFER * NUM_DATA_BUFFER];
/* CPDMA configuration */
Cppi_CpDmaInitCfg       cpdmaCfg;

/* Rx flow configuration */
Cppi_RxFlowCfg          rxFlowCfg;
/* QMSS configuration */
Qmss_InitCfg            qmssInitConfig;

#pragma DATA_SECTION (isSysInitialized, ".qmss");
volatile uint32_t       isSysInitialized = 0;

#pragma DATA_SECTION (isLocInitDone, ".qmss");
volatile uint32_t       isLocInitDone = 0;

#pragma DATA_SECTION (isTestDone, ".qmss");
volatile uint32_t       isTestDone = 0;


/************************ EXTERN VARIABLES ********************/

/* QMSS device specific configuration */
extern Qmss_GlobalConfigParams  qmssGblCfgParams;
/* CPPI device specific configuration */
extern Cppi_GlobalConfigParams  cppiGblCfgParams;


/*************************** FUNCTIONS ************************/

/**
 *  @b Description
 *  @n
 *      Utility function which converts a local GEM L2 memory address
 *      to global memory address.
 *
 *  @param[in]  addr
 *      Local address to be converted
 *
 *  @retval
 *      Computed L2 global Address
 */
static uint32_t l2_global_address (uint32_t addr)
{
    uint32_t corenum;

    /* Get the core number. */
    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    /* Compute the global address. */
    return (addr + (0x10000000 + (corenum * 0x1000000)));
}

/**
 *  @b Description
 *  @n
 *      Utility function that is required by the IPC module to set the proc Id.
 *      The proc Id is set via this function instead of hard coding it in the .cfg file
 *
 *  @retval
 *      Not Applicable.
 */
Void myStartupFxn (Void)
{
    uint32_t corenum;
    /* Get the core number. */
    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    MultiProc_setLocalId (corenum);
}

void usageTsk(UArg arg0, UArg arg1);

/**
 *  @b Description
 *  @n
 *      Entry point for the test code.
 *      This is an example code that shows CPPI LLD API usage.
 *
 *      It performs the following
 *          - Initializes the Resource Manager.
 *          - Invokes the test task/function
 *
 *  @retval
 *      Not Applicable.
 */
void main (void)
{
    Task_Params             taskParams;

    uint32_t                corenum = 0; // Not used on linux

    System_printf ("**************************************************\n");
    System_printf ("*************** CPPI LLD usage example ***********\n");
    System_printf ("**************************************************\n");

    /* Get the core number. */
    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    /* Initialize the heap in shared memory. Using IPC module to do that */
    Ipc_start();

    System_printf ("*******Test running on Core %d *******************\n", corenum);

    if (corenum == SYSINIT)
    {
        System_printf ("Core %d : L1D cache size %d. L2 cache size %d.\n", corenum, CACHE_getL1DSize(), CACHE_getL2Size());
    }

    /* Create the RM transport configuration task */
    Task_Params_init (&taskParams);
    taskParams.priority = 1;
    Task_create (usageTsk, &taskParams, NULL);

    System_printf("Core %d : Starting BIOS...\n", corenum);
    BIOS_start();
}

/**
 *  @b Description
 *  @n
 *      CPPI usage test code.
 *
 *      It performs the following
 *          - Initializes the Queue Manager low level driver.
 *          - Initializes the CPPI low level driver.
 *          - Opens the CPPI CPDMA in queue manager
 *          - Initializes descriptors and pushes to free queue
 *          - Opens Rx and Tx channel
 *          - Pushes packet on Tx channel. Diverts the packet to Tx channel.
 *          - Process the Rx packet
 *          - Closes Rx and Tx channel
 *          - Closes all open queues
 *          - Closes CPDMA instance
 *          - Deinitializes CPPI LLD
 *
 *  @retval
 *      Not Applicable.
 */
void usageTsk(UArg arg0, UArg arg1)
{
    int32_t                 result;
    uint32_t                corenum = 0; // Not used on linux
    uint32_t                numAllocated, i, destLen, runCount = 0;
    uint8_t                 *dataBuffPtr, *destDataPtr;
    uint8_t                 isAllocated;

    Cppi_Handle             cppiHnd;

    Cppi_ChHnd              rxChHnd, txChHnd;
    Qmss_QueueHnd           txQueHnd, rxQueHnd, freeQueHnd;
    Cppi_DescCfg            descCfg;
    Cppi_Desc               *hostDescPtr, *rxPkt;
    uint8_t                 srcData[4];
    Qmss_Result             region = -1;

    /* Get the core number. */
    corenum = CSL_chipReadReg (CSL_CHIP_DNUM);

    if (corenum == SYSINIT)
    {
        /* Reset the variable to indicate to other cores system init is not yet done */

        memset ((void *) &linkingRAM0, 0, sizeof (linkingRAM0));
        memset ((void *) &qmssInitConfig, 0, sizeof (Qmss_InitCfg));

        /* Set up the linking RAM. Use the internal Linking RAM.
         * LLD will configure the internal linking RAM address and default size if a value of zero is specified.
         * Linking RAM1 is not used */
        qmssInitConfig.linkingRAM0Base = l2_global_address ((uint32_t) linkingRAM0);
        qmssInitConfig.linkingRAM0Size = (NUM_HOST_DESC + NUM_MONOLITHIC_DESC) * NUM_CORES;
        qmssInitConfig.linkingRAM1Base = 0;
        qmssInitConfig.maxDescNum      = (NUM_HOST_DESC + NUM_MONOLITHIC_DESC) * NUM_CORES;

        /* Initialize Queue Manager SubSystem */
        result = Qmss_init (&qmssInitConfig, &qmssGblCfgParams);
        if (result != QMSS_SOK)
        {
            System_printf ("Error Core %d : Initializing Queue Manager SubSystem error code : %d\n", corenum, result);
            return;
        }

        /* Start Queue Manager SubSystem */
        result = Qmss_start ();
        if (result != QMSS_SOK)
        {
            System_printf ("Core %d : Error starting Queue Manager error code : %d\n", corenum, result);
        }
        else
            System_printf ("\nCore %d : QMSS initialization done\n", corenum);

        /* Initialize CPPI LLD */
        result = Cppi_init (&cppiGblCfgParams);
        if (result != CPPI_SOK)
        {
            System_printf ("Error Core %d : Initializing CPPI LLD error code : %d\n", corenum, result);
        }

        /* Indicate to other cores Loc init is done */
        isLocInitDone = 1;

        /* Writeback L1D */
        CACHE_wbL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);

        /* Indicate to other cores system init is done */
        isSysInitialized = 1;

        /* Writeback L1D */
        CACHE_wbL1d ((void *) &isSysInitialized, 4, CACHE_WAIT);
    }
    else
    {
        /* Start Queue Manager SubSystem */
        System_printf ("Core %d : Waiting for QMSS to be initialized...\n\n", corenum);

        /* Synchronize all consumer cores. They must wait for the producer core to finish initialization. */

        do{
            CACHE_invL1d ((void *) &isSysInitialized, 4, CACHE_WAIT);
        } while (isSysInitialized == 0);

        /* Start Queue Manager SubSystem */
        result = Qmss_start ();

        if (result != QMSS_SOK)
        {
            System_printf ("Core %d : Error starting Queue Manager error code : %d\n", corenum, result);
        }
        else
            System_printf ("\nCore %d : QMSS initialization done\n", corenum);

        /* Mark that the local initialization is complete */
        Osal_cppiCsEnter();
        CACHE_invL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);
        isLocInitDone += 1;
        /* Writeback L1D */
        CACHE_wbL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);
        Osal_cppiCsExit(NULL);
    }


    /* Synchronize all consumer cores. They must wait for the producer core to finish initialization. */

    do{
        CACHE_invL1d ((void *) &isLocInitDone, 4, CACHE_WAIT);
    } while (isLocInitDone < NUM_CORES);

    /* Set up QMSS CPDMA configuration */
    memset ((void *) &cpdmaCfg, 0, sizeof (Cppi_CpDmaInitCfg));
    cpdmaCfg.dmaNum = Cppi_CpDma_QMSS_CPDMA;


    /* Open QMSS CPDMA */
    cppiHnd = (Cppi_Handle) Cppi_open (&cpdmaCfg);
    if (cppiHnd == NULL)
    {
        System_printf ("Error Core %d : Initializing QMSS CPPI CPDMA %d\n", corenum, cpdmaCfg.dmaNum);
    }
    else
        System_printf ("\nCore %d : QMSS CPDMA Opened\n\n", corenum);

    memset ((void *) hostDesc, 0, SIZE_HOST_DESC * NUM_HOST_DESC);
    memset ((void *) monolithicDesc, 0, SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC);

    /* Setup memory region */
    memset(&memInfo, 0, sizeof(memInfo));
    memInfo.descBase = (uint32_t *) l2_global_address ((uint32_t)hostDesc);
    memInfo.descSize = SIZE_HOST_DESC;
    memInfo.descNum = NUM_HOST_DESC;
    memInfo.manageDescFlag = Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    memInfo.memRegion = (Qmss_MemRegion) corenum;
    memInfo.startIndex = corenum * NUM_HOST_DESC;

    result = Qmss_insertMemoryRegion (&memInfo);
    if (result == QMSS_MEMREGION_ALREADY_INITIALIZED)
    {
        System_printf ("Core %d : Memory region is configured\n", corenum);
    }
    else if (result < QMSS_SOK)
    {
        System_printf ("Error Core %d : Inserting memory region %d error code : %d\n", corenum, memInfo.memRegion, result);
        return;
    }
    else
    {
        System_printf ("Core %d : Memory region %d inserted\n", corenum, result);
    region = result;
    }


    /* Setup the descriptors */
    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion = (Qmss_MemRegion) corenum;
    descCfg.descNum = NUM_HOST_DESC/4;
    descCfg.destQueueNum = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.queueType = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType = Cppi_DescType_HOST;
    descCfg.epibPresent = Cppi_EPIB_NO_EPIB_PRESENT;
    /* Descriptor should be recycled back to freeQue allocated since destQueueNum is < 0 */
    descCfg.returnQueue.qMgr = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.returnQueue.qNum = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.returnPushPolicy = Qmss_Location_HEAD;
    descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;
    descCfg.cfg.host.psLocation = Cppi_PSLoc_PS_IN_DESC;

    /* Initialize the descriptors and push to free Queue */
    if ((freeQueHnd = Cppi_initDescriptor (&descCfg, &numAllocated)) < 0)
    {
        System_printf ("Error Core %d : Initializing descriptor error code: %d \n", corenum, freeQueHnd);
        return;
    }
    else
        System_printf ("Core %d : Number of descriptors requested : %d. Number of descriptors allocated : %d \n",
            corenum, descCfg.descNum, numAllocated);

    /* Set up Rx Channel parameters */
    rxChCfg.channelNum = CPPI_PARAM_NOT_SPECIFIED;
    rxChCfg.rxEnable = Cppi_ChState_CHANNEL_ENABLE;

    /* Open Rx Channel */
    rxChHnd = (Cppi_ChHnd) Cppi_rxChannelOpen (cppiHnd, &rxChCfg, &isAllocated);
    if (rxChHnd == NULL)
    {
        System_printf ("Error Core %d : Opening Rx channel : %d\n", corenum, rxChCfg.channelNum);
        return;
    }
    else
        System_printf ("Core %d : Opened Rx channel : %d\n", corenum, Cppi_getChannelNumber (rxChHnd));


    /* Set up Tx Channel parameters */
    txChCfg.channelNum = CPPI_PARAM_NOT_SPECIFIED;
    txChCfg.priority = 2;
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

    /* Opens transmit queue */
    if ((txQueHnd = Qmss_queueOpen (Qmss_QueueType_LOW_PRIORITY_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
    {
        System_printf ("Error Core %d : Opening Queue Number\n", corenum);
        return;
    }
    else
        System_printf ("Core %d : Queue Number : %d opened\n", corenum, txQueHnd);

    /* Opens receive queue in same group as tx queue, so diversion can take palce */
    if ((rxQueHnd = Qmss_queueOpenInGroup (Qmss_getQueueGroup (txQueHnd), Qmss_QueueType_LOW_PRIORITY_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
    {
        System_printf ("Error Core %d : Opening Queue Number\n", corenum);
    }
    else
        System_printf ("Core %d : Queue Number : %d opened\n", corenum, rxQueHnd);

    /* Set transmit queue threshold to high and when there is atleast one packet */
    /* Setting threshold on transmit queue is not required anymore. tx pending queue is not hooked to threshold.
     * Qmss_setQueueThreshold (txQueHnd, 1, 1);
     */

    /* Fill in some data */
    for (i = 0; i < SIZE_DATA_BUFFER; i++)
        dataBuff[i] = i;

    /* Get a free descriptor */
    while ((hostDescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd)) != NULL)
    {
        /* Add data buffer */
        Cppi_setData (Cppi_DescType_HOST, hostDescPtr, (uint8_t *) l2_global_address ((uint32_t) dataBuff), SIZE_DATA_BUFFER);

        /* Save original buffer information */
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, hostDescPtr, (uint8_t *) l2_global_address ((uint32_t) dataBuff), SIZE_DATA_BUFFER);

        /* Set packet length */
        Cppi_setPacketLen (Cppi_DescType_HOST, hostDescPtr, SIZE_DATA_BUFFER);

        /* Fill in some data */
        srcData[0] = 0xAB;
        srcData[1] = 0xCD;
        srcData[2] = 0xEF;
        srcData[3] = 0xDC;

        /* Add PS data */
        Cppi_setPSData (Cppi_DescType_HOST, hostDescPtr, (uint8_t *) srcData, 4);

        /* Push descriptor to Tx queue */
        Qmss_queuePushDescSize (txQueHnd, (Ptr) hostDescPtr, SIZE_HOST_DESC);

        result = Qmss_getQueueEntryCount (txQueHnd);
        System_printf ("Transmit Queue %d Entry Count : %d Tx descriptor 0x%p\n", txQueHnd, result, hostDescPtr);

        /* Here the packets are diverted to the destination queue.
         * Can also configure flow to transfer packets to destination queue.
         * */

        if ((result = Qmss_queueDivert (txQueHnd, rxQueHnd, Qmss_Location_TAIL)) != QMSS_SOK)
        {
            System_printf ("Error Core %d : queue divert from %d to %d failed: %d\n", corenum, txQueHnd, rxQueHnd, result);
            break;
        }

        result = Qmss_getQueueEntryCount (rxQueHnd);

        /* Wait for receive packet */
        while (Qmss_getQueueEntryCount (rxQueHnd) == 0);

        /* Get the rx packet */
        if ((rxPkt = (Cppi_Desc *) Qmss_queuePop (rxQueHnd)) == NULL)
        {
            return;
        }

        /* The lower 4 bits of the descriptor address contain the size of the descriptor
        that was specified during the queue push operation. Clear it */

        rxPkt = (Cppi_Desc *) QMSS_DESC_PTR (rxPkt);

        System_printf ("Receive Queue %d Entry Count : %d Rx descriptor 0x%p\n", rxQueHnd, result, rxPkt);

        /* Get PS data */
        Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, rxPkt, &destDataPtr, &destLen);

        /* Compare */
        for (i=0; i < destLen; i++)
        {
            if (srcData[i] != destDataPtr[i])
            {
                System_printf ("Error Core %d : In PS data Tx: %02x - Rx: %02x \n", corenum, srcData[i], destDataPtr[i]);
                break;
            }
        }

        /* Get data buffer */

        Cppi_getData (Cppi_DescType_HOST, rxPkt, &dataBuffPtr, &destLen);

        /* Compare */
        for (i=0; i < destLen; i++)
        {
            if (dataBuff[i] != dataBuffPtr[i])
            {
                System_printf ("Error Core %d : In data buffer Tx: %02x - Rx: %02x \n", corenum, dataBuff[i], dataBuffPtr[i]);
                break;
            }
        }
        runCount++;

    }
    if ((runCount == 0) && (runCount != NUM_HOST_DESC))
    {
        System_printf ("Core %d : Getting host descriptor from Queue : %d \n", corenum, freeQueHnd);
    }
    else
        System_printf ("Core %d : Received host descriptor from Queue %d Sucessfully\n", corenum, freeQueHnd);

    /* Close Tx channel */
    if ((result = Cppi_channelClose (txChHnd)) < 0)
        System_printf ("Error Core %d : Closing Tx channel error code: %d\n", corenum, result);
    else
        System_printf ("Core %d : Tx Channel closed successfully. Ref count :%d\n", corenum, result);

    /* Close Rx channel */
    if ((result = Cppi_channelClose (rxChHnd)) < 0)
        System_printf ("Error Core %d : Closing Rx channel error code: %d\n", corenum, result);
    else
        System_printf ("Core %d : Rx Channel closed successfully. Ref count :%d\n", corenum, result);

    /* Empty the queues */
    Qmss_queueEmpty (rxQueHnd);
    Qmss_queueEmpty (txQueHnd);
    Qmss_queueEmpty (freeQueHnd);

    /* Close the queues */
    if ((result = Qmss_queueClose (rxQueHnd)) < 0)
        System_printf ("Error Core %d : Closing Rx queue error code: %d\n", corenum, result);
    else
        System_printf ("Core %d : Rx queue closed successfully. Ref count :%d\n", corenum, result);

    if ((result = Qmss_queueClose (txQueHnd)) < 0)
        System_printf ("Error Core %d : Closing tx queue error code: %d\n", corenum, result);
    else
        System_printf ("Core %d : Tx queue closed successfully. Ref count :%d\n", corenum, result);

    if ((result = Qmss_queueClose (freeQueHnd)) < 0)
        System_printf ("Error Core %d : Closing free queue error code: %d\n", corenum, result);
    else
        System_printf ("Core %d : Free queue closed successfully. Ref count :%d\n", corenum, result);

    /* Close CPPI CPDMA instance */
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

    System_printf ("*******************************************************\n");
    System_printf ("*************** CPPI LLD usage example Done ***********\n");
    System_printf ("*******************************************************\n");
    System_flush();

    BIOS_exit(0);

}

