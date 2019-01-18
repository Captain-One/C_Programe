/**
 * @file  bench_qmss.c
 *
 * @brief   
 *    Example application that uses the QMSS IPC transport to send
 *    MessageQ messages between two DSP cores.  Latency and
 *    throughput statistics are collected for the transmitted
 *    messages.
 *
 * Copyright (c) 2011-2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>

/* XDC include */
#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Error.h>

/* BIOS6 include */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* IPC include */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/GateMP.h>
#include <ti/ipc/HeapBufMP.h>
#include <ti/ipc/SharedRegion.h>

/* CSL include */
#include <ti/csl/csl_cacheAux.h>
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>
#include <ti/csl/csl_chip.h>

/* QMSS LLD */
#include <ti/drv/qmss/qmss_drv.h>
#include <ti/drv/qmss/qmss_firmware.h>

/* CPPI LLD */
#include <ti/drv/cppi/cppi_drv.h>

/* RM LLD */
#include <ti/drv/rm/rm.h>
#include <ti/drv/rm/rm_services.h>

/* Transport QMSS includes */
#include <ti/transport/ipc/c66/qmss/TransportQmss.h>

#include <ti/transport/ipc/c66/example/common_src/bench_common.h>

/************************ USER DEFINES ********************/

#define RM_PRINT_STATS          0
#define SYSINIT                 0
#define NUM_DSP_CORES           2
#define NUM_TEST_ITERATIONS     2
#if defined(DEVICE_C6657)
#define NUM_MSGS_TO_PREALLOC    16
#else
#define NUM_MSGS_TO_PREALLOC    64
#endif

#define HOST_DESC_SIZE_BYTES    128
#if defined(DEVICE_C6657)
#define HOST_DESC_NUM           64
#else
#define HOST_DESC_NUM           256
#endif
#define HOST_DESC_MEM_REGION    0

#define QMSS_MTU_SIZE_BYTES     4096

#define QMSS_MSGQ_HEAP_NAME     "qmssIpcHeapBuf"
#define QMSS_MSGQ_HEAP_ID       1

#define QMSS_TRANS_NET_ID       1

/* Number of times to run the loop */
#define NUMLOOPS                100
#define NUMIGNORED              5
#define NUM_MSGS                10

#define TEST_PASS               0
#define TEST_FAIL               1

/************************ GLOBAL VARIABLES ********************/

uint32_t testIterations;
uint32_t testFailed;

/* Queue parameters */
char localQueueName[6];
char nextQueueName[6];

/* Core definitions according to IPC */
uint16_t ipcCoreId = 0;
uint16_t ipcPrevCoreId = 0;
uint16_t ipcNumDspCores = 0;

/* Core number according to the device (DNUM) */
uint32_t coreNum;

Task_Handle initTskHandle = NULL;
Task_Handle testTskHandle = NULL;
Task_Handle cleanupTskHandle = NULL;

uint64_t     timeAdj = 0;
uint64_t     timeLength = 0;
Types_FreqHz timerFreq, cpuFreq;
float        cpuTimerFreqRatio;
Statistics   latencyStats;
uint32_t     rawtimestamps[NUMLOOPS];
uint32_t     latencies[NUMLOOPS - 1];

MessageQ_Handle      localMessageQ = NULL;
MessageQ_QueueId     nextQueueId, prevQueueId;
GateMP_Handle        gateMpHandle;
HeapBufMP_Handle     heapHandle;
TransportQmss_Handle qmssTransHandle = NULL;

/* Descriptors aligned and padded to cache line */
#pragma DATA_SECTION (hostDesc, ".desc");
#pragma DATA_ALIGN (hostDesc, 128)
/* Total size must be multiple of cache line */
uint8_t hostDesc[HOST_DESC_NUM * HOST_DESC_SIZE_BYTES];

/* Sync indices into the syncInit array */
#define SYNC_INDEX_SYS_INIT  0
#define SYNC_INDEX_RM_INIT   1
#define SYNC_INDEX_SHM_TPUT  2
#define SYNC_INDEX_QMSS_TPUT 3
/* Sync block for initialization barriers */
#pragma DATA_SECTION (syncInit, ".sync");
#pragma DATA_ALIGN (syncInit, 128)
volatile uint8_t syncInit[128];

/* Sync block for cleanup barriers */
#pragma DATA_SECTION (syncCleanup, ".sync");
#pragma DATA_ALIGN (syncCleanup, 128)
volatile uint8_t syncCleanup[NUM_DSP_CORES][128];

/* RM instance handle */
Rm_Handle         rmHandle = NULL;
Rm_ServiceHandle *rmServiceHandle = NULL;

/*************** EXTERN VARIABLES & FUNCTIONS *****************/
/* QMSS device specific configuration */
extern Qmss_GlobalConfigParams qmssGblCfgParams;
/* CPPI device specific configuration */
extern Cppi_GlobalConfigParams cppiGblCfgParams;

/* TransportQmss device specification configuration */
extern TransportQmss_DeviceConfigParams qmssTransCfgParams;

/* Global Resource List (GRL) */
extern const char rmGlobalResourceList[];

#if defined(LINUX_NO_BOOT) || (defined(DEVICE_C6657) || defined(DEVICE_C6678))
/* DSP only Policy provided to RM Server */
extern const char rmDspOnlyPolicy[];
#else
/* ARM+DSP Policy provided to RM Server */
extern const char rmDspPlusArmPolicy[];
#endif

/* RM instance transport code */
extern int setupRmTransConfig(uint32_t numTestCores, uint32_t systemInitCore,
                              Task_FuncPtr testTask);

/*************************** FUNCTIONS ************************/

void initTsk(UArg arg0, UArg arg1);
void proxyInitTsk(UArg arg0, UArg arg1);

static void wb(void *addr, uint32_t sizeBytes)
{
#ifdef L2_CACHE
    /* Writeback L2 */
    CACHE_wbL2(addr, sizeBytes, CACHE_WAIT);
#else
    /* Writeback L1D */
    CACHE_wbL1d(addr, sizeBytes, CACHE_WAIT);
#endif
}

static void inv(void *addr, uint32_t sizeBytes)
{
#ifdef L2_CACHE
    /* Invalidate L2 */
    CACHE_invL2(addr, sizeBytes, CACHE_WAIT);
#else
    CACHE_invL1d(addr, sizeBytes, CACHE_WAIT);
#endif
}

/**
 *  @b Description
 *  @n
 *      Configures the descriptor region and initializes CPPI and QMSS.
 *      This function should only be called once across all DSP cores.
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t systemInit(void)
{
    Qmss_InitCfg    qmssInitConfig; /* QMSS configuration */
    Qmss_MemRegInfo memInfo; /* Memory region configuration information */
    Qmss_Result     result;
    Cppi_StartCfg   cppiStartCfg;

    System_printf("Core %d : L1D cache size %d. L2 cache size %d.\n", coreNum,
                  CACHE_getL1DSize(), CACHE_getL2Size());

    /* Start the timestamp counter */
    TSCL = 0;

    memset((void *) &qmssInitConfig, 0, sizeof (Qmss_InitCfg));
    /* Set up the linking RAM. Use the internal Linking RAM. LLD will configure
     * the internal linking RAM address and maximum internal linking RAM size
     * if a value of zero is specified.  Linking RAM1 is not used */
    qmssInitConfig.linkingRAM0Base = 0;
    qmssInitConfig.linkingRAM0Size = 0;
    qmssInitConfig.linkingRAM1Base = 0;
    qmssInitConfig.maxDescNum      = HOST_DESC_NUM;
#if defined(LINUX_NO_BOOT) || (defined(DEVICE_C6657) || defined(DEVICE_C6678))
#ifdef xdc_target__bigEndian
    qmssInitConfig.pdspFirmware[0].pdspId = Qmss_PdspId_PDSP1;
    qmssInitConfig.pdspFirmware[0].firmware = (void *) &acc48_be;
    qmssInitConfig.pdspFirmware[0].size = sizeof (acc48_be);
#else
    qmssInitConfig.pdspFirmware[0].pdspId = Qmss_PdspId_PDSP1;
    qmssInitConfig.pdspFirmware[0].firmware = (void *) &acc48_le;
    qmssInitConfig.pdspFirmware[0].size = sizeof (acc48_le);
#endif
#else
    /* Download PDSP3 firmware.  PDSP1 will not be used to avoid potential
     * firmware lockup caused by usage contention with Linux */
#ifdef xdc_target__bigEndian
    qmssInitConfig.pdspFirmware[0].pdspId = Qmss_PdspId_PDSP3;
    qmssInitConfig.pdspFirmware[0].firmware = (void *) &acc48_be;
    qmssInitConfig.pdspFirmware[0].size = sizeof (acc48_be);
#else
    qmssInitConfig.pdspFirmware[0].pdspId = Qmss_PdspId_PDSP3;
    qmssInitConfig.pdspFirmware[0].firmware = (void *) &acc48_le;
    qmssInitConfig.pdspFirmware[0].size = sizeof (acc48_le);
#endif
#endif

    qmssGblCfgParams.qmRmServiceHandle = rmServiceHandle;
#if (!defined(LINUX_NO_BOOT)) && (!defined(DEVICE_C6657) && !defined(DEVICE_C6678))
    /* Bypass hardware initialization as it is done within Kernel */
    qmssInitConfig.qmssHwStatus = QMSS_HW_INIT_COMPLETE;
#endif

    /* Initialize Queue Manager SubSystem */
    result = Qmss_init(&qmssInitConfig, &qmssGblCfgParams);
    if (result != QMSS_SOK) {
        System_printf("Error Core %d : "
                      "Initializing Queue Manager SubSystem error code : %d\n",
                      coreNum, result);
       // return(-1);
    }


    /* Start the QMSS. */
    if (Qmss_start() != QMSS_SOK) {
        System_printf("Error Core %d : Unable to start the QMSS\n", coreNum);
        return(-1);
    }

    result = Cppi_init(&cppiGblCfgParams);
    if (result != CPPI_SOK) {
        System_printf("Error Core %d : "
                      "Initializing CPPI LLD error code : %d\n", coreNum,
                      result);
    }

    /* Register RM with CPPI */
    cppiStartCfg.rmServiceHandle = rmServiceHandle;
    Cppi_startCfg(&cppiStartCfg);

    /* Setup memory region for host descriptors */
    memset((void *) &hostDesc, 0, HOST_DESC_NUM * HOST_DESC_SIZE_BYTES);
    memset((void *) &memInfo, 0, sizeof(memInfo));
    memInfo.descBase       = (uint32_t *) hostDesc;
    memInfo.descSize       = HOST_DESC_SIZE_BYTES;
    memInfo.descNum        = HOST_DESC_NUM;
    memInfo.manageDescFlag = Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    memInfo.memRegion      = (Qmss_MemRegion) HOST_DESC_MEM_REGION;
    result = Qmss_insertMemoryRegion(&memInfo);
    if (result < QMSS_SOK) {
        System_printf("Error Core %d : "
                      "Inserting memory region, error code : %d\n", coreNum,
                      result);
        return(-1);
    } else {
        System_printf("Core %d : Memory region %d inserted\n", coreNum,
                      HOST_DESC_MEM_REGION);
    }

    /* Writeback the descriptor pool. */
    wb((void *)hostDesc, HOST_DESC_NUM * HOST_DESC_SIZE_BYTES);

    return(0);
}

/**
 *  @b Description
 *  @n
 *      Deletes descriptor region and shuts down CPPI and QMSS.
 *      This function should only be called once across all DSP cores.
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t systemDeInit(void)
{
    Qmss_Result qmssResult;
    Cppi_Result cppiResult;

    /* Remove the memory region. */
    qmssResult = Qmss_removeMemoryRegion(HOST_DESC_MEM_REGION, 0);
    if (qmssResult < QMSS_SOK) {
        System_printf("Error Core %d : Removing memory region: %d\n", coreNum,
                      qmssResult);
        return(-1);
    }

    /* De Initialize CPPI CPDMA */
    cppiResult = Cppi_exit();
    if (cppiResult != CPPI_SOK) {
        System_printf("Error Core %d : Deinitializing CPPI error code : %d\n",
                      coreNum, cppiResult);
        return(-1);
    }

    return(0);
}

/**
 *  @b Description
 *  @n
 *      This functions prints the statistics gathered for the transport during
 *      the latency test.
 */
void printLatencyStats(void)
{
    uint32_t timeElapsed;
    uint32_t i;

    /* Convert timestamps to CPU time */
    for (i = 0; i < NUMLOOPS; i++) {
        rawtimestamps[i] *= cpuTimerFreqRatio;
    }

    for (i = 0; i < NUMLOOPS - 1; i++) {
        latencies[i] = (rawtimestamps[i + 1] - rawtimestamps[i]) /
                       ipcNumDspCores;
    }

    getStats(latencies + NUMIGNORED, NUMLOOPS - NUMIGNORED - 2, &latencyStats);

    timeElapsed = rawtimestamps[NUMLOOPS - NUMIGNORED - 2] -
                  rawtimestamps[NUMIGNORED];
    /* Throughput = time elapsed divided by total #of of hops */
    
    System_printf("Core %d : "
                  "=============== LATENCY RESULTS =============\n", coreNum);
    System_printf("Core %d : Number of messages received:  %8d\n", coreNum,
                  latencyStats.numVals);
    System_printf("Core %d : "
                  "Average 1-way latency:        %8d (cycles/msg) %6d (ns/msg)"
                  "\n", coreNum, (uint32_t)latencyStats.mean,
                  CYCLES_TO_NS(latencyStats.mean, cpuFreq.lo));
    System_printf("Core %d : "
                  "Maximum 1-way latency:        %8d (cycles/msg) %6d (ns/msg)"
                  "\n", coreNum, latencyStats.max,
                  CYCLES_TO_NS(latencyStats.max, cpuFreq.lo));
    System_printf("Core %d : "
                  "Minimum 1-way latency:        %8d (cycles/msg) %6d (ns/msg)"
                  "\n", 
                  coreNum, latencyStats.min, CYCLES_TO_NS(latencyStats.min,
                  cpuFreq.lo)); 
    System_printf("Core %d : Standard deviation:           %8d (cycles/msg)\n",
                  coreNum, (uint32_t)latencyStats.stddev);
    System_printf("Core %d : "
                  "Total time elapsed:           %8d (cycles)     %6d (us)\n",
                  coreNum, timeElapsed, CYCLES_TO_US(timeElapsed, cpuFreq.lo));
}

/**
 *  @b Description
 *  @n
 *      This functions measures latency by sending a message from core0 to
 *      core1.  Core1 relays all received messages back to core 2.  Core0 will
 *      measure the roundtrip latency.
 */
static uint32_t testLatency(MessageQ_Priority msgPriority, uint16_t transId)
{
    int32_t      status;
    uint32_t     numReceived;
    MessageQ_Msg msg;

    if (coreNum == SYSINIT) {
        msg = MessageQ_alloc(QMSS_MSGQ_HEAP_ID, sizeof(TstMsg));
        if (msg == NULL) {
            System_printf("Error Core %d : MessageQ_alloc failed\n", coreNum);
            return(TEST_FAIL);
        }

        MessageQ_setTransportId(msg, transId);
        /* Priority is ignored if transport ID is set to a value between 1
         * and 7 */
        MessageQ_setMsgPri(msg, msgPriority);

        System_printf("Core %d : "
                      "IPC Core ID=%d calling MessageQ_put(nextQueueName=%s). "
                      "msg=0x%x\n",
                      coreNum, ipcCoreId, nextQueueName, msg);
        /* Kick off the loop */
        status = MessageQ_put(nextQueueId, msg);
        if (status < 0) {
            System_printf("Error Core %d : MessageQ_put failed\n", coreNum);
            return(TEST_FAIL);
        }
    }

    for (numReceived = 0; numReceived < NUMLOOPS; numReceived++) {
        status = MessageQ_get(localMessageQ, &msg, MessageQ_FOREVER);
        if (status < 0) {
            System_printf("Error Core %d : MessageQ_get failed\n", coreNum);
            return (TEST_FAIL);
        }

        if (coreNum == SYSINIT) {
            rawtimestamps[numReceived] = Timestamp_get32();

            if (numReceived == NUMLOOPS - 1) {
                printLatencyStats();
                MessageQ_free(msg);
                break;
            }
        }

        status = MessageQ_put(nextQueueId, msg);
        if (status < 0) {
            System_printf("Error Core %d : MessageQ_put failed\n", coreNum);
            return (TEST_FAIL);
        }
    }

    return(TEST_PASS);
}

/**
 *  @b Description
 *  @n
 *      This functions allocate all messages to be sent up front on core0.
 *      Synchronize core 0 and core1.  Core 0 sends all messages to Core1
 *      in a burst.  Core 1 receives all the messages and measure the
 *      throughput over the time it took to send all the messages.
 */
static uint32_t testTputAndDataIntegrity(MessageQ_Priority msgPriority,
                                         uint16_t transId)
{
    uint32_t  i, j;
    TstMsg   *msg;

    if (coreNum == SYSINIT) {
        /* Last entry must be CORE_SYNC_NULL_CORE */
        int16_t   receiveCores[2] = {1, CORE_SYNC_NULL_CORE};
        TstMsg   *syncMsg = NULL;
        /* First message used to synchronize cores */
        uint32_t  numTxMsgs = NUM_MSGS_TO_PREALLOC;
        TstMsg   *txMsgPtrs[NUM_MSGS_TO_PREALLOC];
        int32_t   status;
        uint32_t  numSends = 0;

        syncMsg = (TstMsg *) MessageQ_alloc(QMSS_MSGQ_HEAP_ID, sizeof(TstMsg));
        if (syncMsg == NULL) {
            System_printf("Error Core %d : Failed to allocate sync msg\n",
                          coreNum);
            return(TEST_FAIL);
        }
        status = allocateMessages(NUM_MSGS_TO_PREALLOC, QMSS_MSGQ_HEAP_ID,
                                  &txMsgPtrs[0]);
        if (status != 0) {
            System_printf("Error Core %d : "
                          "Failed to preallocate msgs after allocating %d "
                          "messages.\n", coreNum, status);
            return(TEST_FAIL);
        }

        /* Populate msg's data with pattern for integrity check */
        for (i = 0; i < NUM_MSGS_TO_PREALLOC; i++) {
            msg = txMsgPtrs[i];
            for (j = 0; j < TEST_MSG_DATA_LEN_WORDS; j++) {
                msg->data[j] = ((i << 16) | j);
            }
        }

        syncSendCore(&receiveCores[0], localMessageQ, &nextQueueId, &syncMsg,
                     BENCH_TRUE, msgPriority, transId);

        /* Send all messages to remote core.  The last message sent will have a
         * flag signifying to remote core that all messages have been sent. */
        numSends = sendMessages(1, &numTxMsgs, &nextQueueId, &txMsgPtrs[0],
                                msgPriority, transId);
        System_printf("Core %d : Sent a total of %d messages.\n", coreNum,
                      numSends);
    } else {
        /* Last entry must be CORE_SYNC_NULL_CORE */
        int16_t   sendCores[2] = {0, CORE_SYNC_NULL_CORE};
        TstMsg   *rxMsgPtrs[NUM_MSGS_TO_PREALLOC];
        uint32_t  numReceived = 0;
        uint32_t  delay = 0;
        int32_t   status;
        uint64_t  timeStamp;

        System_printf("Core %d : Per message work delay is %dus\n", coreNum,
                      delay);

        /* Synchronize cores prior to starting test */
        syncReceiveCore(&sendCores[0], localMessageQ, &nextQueueId,
                        msgPriority, transId);

        timeStamp = getStartTime64();
        numReceived = receiveMessages(&sendCores[0], localMessageQ,
                                      &rxMsgPtrs[0], delay);
        timeLength = getExecutionTime64(timeStamp, timeAdj);

        if (numReceived != NUM_MSGS_TO_PREALLOC) {
            System_printf("Error Core %d : "
                          "Expected %d msgs but only received %d\n", coreNum,
                          NUM_MSGS_TO_PREALLOC, numReceived);
            return(TEST_FAIL);
        } else {
            System_printf("Core %d : Received a total of %d messages.\n",
                          coreNum, numReceived);
        }

        /* Check integrity of data in received messages */
        System_printf("Core %d : "
                      "Checking integrity of data in received messages...",
                      coreNum);
        for (i = 0; i < NUM_MSGS_TO_PREALLOC; i++) {
            msg = rxMsgPtrs[i];
            for (j = 0; j < TEST_MSG_DATA_LEN_WORDS; j++) {
                uint32_t integrityMask = ((i << 16) | j);

                if (msg->data[j] != integrityMask) {
                    System_printf("FAILED\n");
                    System_printf("Error Core %d : "
                                  "Data mismatch in receive message %d\n",
                                  coreNum, i);
                    return(TEST_FAIL);
                }
            }
        }
        System_printf("PASSED\n");
        calculateThroughput(numReceived, timeLength, cpuFreq);

        status = freeMessages(numReceived, &rxMsgPtrs[0]);
        if (status < 0) {
            System_printf("Error Core %d : Message free failed\n", coreNum);
            return (TEST_FAIL);
        }
    }

    return(TEST_PASS);
}

/**
 *  @b Description
 *  @n
 *      Cleanup task used to reset application to pre-initTsk state
 */
void cleanupTsk(UArg arg0, UArg arg1)
{
    Task_Params taskParams;
    Int         status;
    Qmss_Result qmssResult;
    int32_t     rmResult;
    int32_t     i;
    
    System_printf("Core %d : "
                  "================== CLEANUP ==================\n", coreNum);

    if (initTskHandle) {
        Task_delete(&initTskHandle);
        initTskHandle = NULL;
    }

    if (testTskHandle) {
        Task_delete(&testTskHandle);
        testTskHandle = NULL;
    }

    System_printf("Core %d : Closing remote MessageQ\n", coreNum);
    status = MessageQ_close(&nextQueueId);
    if (status != MessageQ_S_SUCCESS) {
        testFailed = BENCH_TRUE;
        System_printf ("Error Core %d : MessageQ_close\n", coreNum);
        goto cleanup_error;
    }
    System_printf("Core %d : Deleting local MessageQ\n", coreNum);
    status = MessageQ_delete(&localMessageQ);
    if (status != MessageQ_S_SUCCESS) {
        testFailed = BENCH_TRUE;
        System_printf ("Error Core %d : MessageQ_delete\n", coreNum);
        goto cleanup_error;
    }

    if (testIterations & 0x1) {
        System_printf("Core %d : Deleting QMSS QPEND IPC transport\n", coreNum);
    } else {
        System_printf("Core %d : Deleting QMSS Accumulator IPC transport\n",
                      coreNum);
    }
    TransportQmss_delete(&qmssTransHandle);
    qmssTransHandle = NULL;

    System_printf("Core %d : Unregistering MessageQ heap\n", coreNum);
    status = MessageQ_unregisterHeap(QMSS_MSGQ_HEAP_ID);
    if (status != MessageQ_S_SUCCESS) {
        testFailed = BENCH_TRUE;
        System_printf ("Error Core %d : MessageQ_unregisterHeap\n", coreNum);
        goto cleanup_error;
    }

    if (coreNum == SYSINIT) {
        /* Wait for other cores to complete cleanup */
        for (i = 0; i < NUM_DSP_CORES; i++) {
            if (i != coreNum) {
                do {
                    inv((void *) &syncCleanup[i][0], sizeof(syncCleanup) /
                        NUM_DSP_CORES);
                } while (!syncCleanup[i][0]);
            }
        }

        System_printf("Core %d : Closing HeapBufMP\n", coreNum);
        status = HeapBufMP_close(&heapHandle);
        if (status != HeapBufMP_S_SUCCESS) {
            testFailed = BENCH_TRUE;
            System_printf("Error Core %d : HeapBufMP_close\n", coreNum);
            goto cleanup_error;
        }

        System_printf("Core %d : Deleting GateMP used by HeapBufMP\n", coreNum);
        status = GateMP_delete(&gateMpHandle);
        if (status != GateMP_S_SUCCESS) {
            testFailed = BENCH_TRUE;
            System_printf("Error Core %d : GateMP_close\n", coreNum);
            goto cleanup_error;
        }

        System_printf("Core %d : De-initializing QMSS and CPPI\n", coreNum);
        status = systemDeInit();
        if (status < 0) {
            testFailed = BENCH_TRUE;
            goto cleanup_error;
        }

        /* Exit qmss */
        System_printf ("Core %d : exit QMSS\n", coreNum);
        if ((qmssResult = Qmss_exit ())) {
            testFailed = BENCH_TRUE;
            System_printf("Error Core %d : exit error code : %d\n", coreNum,
                          qmssResult);
            goto cleanup_error;
        }
    } else {
        System_printf("Core %d : Closing HeapBufMP\n", coreNum);
        status = HeapBufMP_close(&heapHandle);
        if (status != HeapBufMP_S_SUCCESS) {
            testFailed = BENCH_TRUE;
            System_printf("Error Core %d : HeapBufMP_close\n", coreNum);
            goto cleanup_error;
        }
    }

cleanup_error:

    if (coreNum == SYSINIT) {
        if ((rmResult = Rm_resourceStatus(rmHandle, FALSE)) != 0) {
            System_printf("Error Core %d : Number of unfreed resources : %d\n",
                          coreNum, rmResult);
            /* Print them */
            Rm_resourceStatus (rmHandle, TRUE);
            testFailed = BENCH_TRUE;
        } else {
            System_printf("Core %d : All resources freed successfully\n",
                          coreNum);
        }
    }

    /* SYSINIT cannot cleanup until all other cores have completed cleanup */
    if (coreNum != SYSINIT) {
        syncCleanup[coreNum][0] = 1;
        wb((void *) &syncCleanup[coreNum][0], sizeof(syncCleanup) /
                                                     NUM_DSP_CORES);
    }

    System_printf("Core %d : *********************************************\n",
                  coreNum);
    System_printf("Core %d : Completed Test Iteration: %d - ", coreNum,
                  testIterations);
    if (testFailed) {
        System_printf("FAILED\n");
        System_printf("Core %d : Cleaning up and exiting...\n", coreNum);
    } else {
        System_printf("PASSED\n");
    }
    System_printf("Core %d : *********************************************\n",
                  coreNum);

    testIterations++;
    if ((!testFailed) && (testIterations < NUM_TEST_ITERATIONS)) {
        /* Secondary DSPs must wait for SYSINIT DSP to complete cleanup if test
         * is starting another iteration */
        if (coreNum == SYSINIT) {
            syncCleanup[coreNum][0] = 1;
            wb((void *) &syncCleanup[coreNum][0], sizeof(syncCleanup) /
                                                         NUM_DSP_CORES);
            /* Sleep so secondary cores can get barrier update for sync
             * mechanism reset occurs */
            Task_sleep(1);
        } else {
            do {
                inv((void *) &syncCleanup[SYSINIT][0], sizeof(syncCleanup) /
                                                              NUM_DSP_CORES);
            } while (!syncCleanup[SYSINIT][0]); 
        }

        /* Reset all sync mechanisms */
        memset(&syncInit, 0, sizeof(syncInit));
        memset(&syncCleanup, 0, sizeof(syncCleanup));
        if (coreNum == SYSINIT) {
            wb((void *)&syncInit, sizeof(syncInit));
        } else {
            wb((void *)&syncCleanup[coreNum][0], sizeof(syncCleanup) /
                                                        NUM_DSP_CORES);
        }

        /* Restart test from initTsk */
        System_printf("Core %d : Recreating init task...\n", coreNum);
        Task_Params_init(&taskParams);
        taskParams.priority = 1;
        taskParams.stackSize = 4096;
        initTskHandle = Task_create(initTsk, &taskParams, NULL);
    } else {
        System_printf("Core %d : Testing complete! - ", coreNum);
        if (testFailed) {
            System_printf("FAILED\n");
        } else {
            System_printf("PASSED\n");
        }
    }
}

/**
 *  @b Description
 *  @n
 *      Task that runs the latency and throughput tests
 */
void testTsk(UArg arg0, UArg arg1)
{
    uint32_t    result;
    Task_Params taskParams;

    System_printf("Core %d : *********************************************\n",
                  coreNum);
    System_printf("Core %d : Starting Test Iteration: %d\n", coreNum,
                  testIterations);
    System_printf("Core %d : Test Packet Size: %d bytes\n", coreNum,
                  sizeof(TstMsg));
    System_printf("Core %d : *********************************************\n",
                  coreNum);

    System_printf("Core %d : ============== CORE ATTRIBUTES ==============\n",
                  coreNum);
    System_printf("Core %d : CPU Freq:        %d MHz\n", coreNum,
                  cpuFreq.lo / 1000000);
    System_printf("Core %d : Timer Freq:      %d MHz\n", coreNum,
                  timerFreq.lo / 1000000);
    System_printf("Core %d : nextQueueName:   %s\n", coreNum, nextQueueName);
    System_printf("Core %d : nextQueueId:     0x%08x\n", coreNum, nextQueueId);
    System_printf("Core %d : *********************************************\n\n",
                  coreNum);

    if (coreNum == SYSINIT) {
        System_printf("Core %d : "
                      "*********************************************\n",
                      coreNum);
        System_printf("Core %d : SHM transport latency measurement\n", coreNum);
    }
    result = testLatency(MessageQ_NORMALPRI, 0);
    if (result == TEST_FAIL) {
        testFailed = BENCH_TRUE;
        if (coreNum != SYSINIT) {
            System_printf("Core %d : SHM Latency Result\n", coreNum);
        }
        System_printf("Core %d : FAILED\n", coreNum);
        goto cleanup;
    }

    if (coreNum == SYSINIT) {
        System_printf("Core %d : PASSED\n", coreNum);
        System_printf("Core %d : "
                      "*********************************************\n\n",
                      coreNum);

        System_printf("Core %d : "
                      "*********************************************\n",
                      coreNum);
        if (testIterations & 0x1) {
            System_printf("Core %d : "
                          "QMSS QPEND transport latency measurement\n",
                          coreNum);
        } else {
            System_printf("Core %d : "
                          "QMSS Accumulator transport latency measurement\n",
                          coreNum);
        }
    }
    result = testLatency(MessageQ_NORMALPRI, QMSS_TRANS_NET_ID);
    if (result == TEST_FAIL) {
        testFailed = BENCH_TRUE;
        if (coreNum != SYSINIT) {
            if (testIterations & 0x1) {
                System_printf("Core %d : QMSS QPEND Latency Result\n",
                              coreNum);
            } else {
                System_printf("Core %d : QMSS Accumulator Latency Result\n",
                              coreNum);
            }
        }
        System_printf("Core %d : FAILED\n", coreNum);
        goto cleanup;
    }

    if (testIterations & 0x1) {
        System_printf("Core %d : Flushing transport's dst cache of dst "
                      "MessageQ queue ID 0x%x\n", coreNum, nextQueueId);
        if (!TransportQmss_flushDstCache(qmssTransHandle, nextQueueId)) {
            System_printf("Error Core %d : Dst cache flush failed\n", coreNum);
            goto cleanup;
        }
    } else {
        System_printf("Core %d : Flushing transport's entire dst cache\n",
                      coreNum);
        if (!TransportQmss_flushDstCache(qmssTransHandle,
                                         MessageQ_INVALIDMESSAGEQ)) {
            System_printf("Error Core %d : Dst cache flush failed\n", coreNum);
            goto cleanup;
        }
    }

    if (coreNum == SYSINIT) {
        System_printf("Core %d : PASSED\n", coreNum);
        System_printf("Core %d : "
                      "*********************************************\n\n",
                      coreNum);

        /* Wait for ready from secondary core */
        do {
            inv((void *) &syncInit, sizeof(syncInit));
        } while (!syncInit[SYNC_INDEX_SHM_TPUT]);

        System_printf("Core %d : "
                      "*********************************************\n",
                      coreNum);
        System_printf("Core %d : SHM transport throughput measurement\n",
                      coreNum);
    } else {
        /* Ready signal to primary DSP */
        syncInit[SYNC_INDEX_SHM_TPUT] = 1;
        wb((void *) &syncInit, sizeof(syncInit));
    }
    result = testTputAndDataIntegrity(MessageQ_NORMALPRI, 0);
    if (result == TEST_FAIL) {
        testFailed = BENCH_TRUE;
        if (coreNum != SYSINIT) {
            System_printf("Core %d : SHM Throughput Result\n", coreNum);
        }
        System_printf("Core %d : FAILED\n", coreNum);
        goto cleanup;
    }

    if (coreNum == SYSINIT) {
        System_printf("Core %d : PASSED\n", coreNum);
        System_printf("Core %d : "
                      "*********************************************\n\n",
                      coreNum);

        /* Wait for ready from secondary core */
        do {
            inv((void *) &syncInit, sizeof(syncInit));
        } while (!syncInit[SYNC_INDEX_QMSS_TPUT]);

        System_printf("Core %d : "
                      "*********************************************\n",
                      coreNum);
        if (testIterations & 0x1) {
            System_printf("Core %d : "
                          "QMSS QPEND transport throughput measurement\n",
                          coreNum);
        } else {
            System_printf("Core %d : "
                          "QMSS Accumulator transport throughput measurement\n",
                          coreNum);
        }
    } else {
        /* Ready signal to primary DSP */
        syncInit[SYNC_INDEX_QMSS_TPUT] = 1;
        wb((void *) &syncInit, sizeof(syncInit));
    }
    result = testTputAndDataIntegrity(MessageQ_NORMALPRI, QMSS_TRANS_NET_ID);
    if (result == TEST_FAIL) {
        testFailed = BENCH_TRUE;
        if (coreNum != SYSINIT) {
            if (testIterations & 0x1) {
                System_printf("Core %d : QMSS QPEND Throughput Result\n",
                              coreNum);
            } else {
                System_printf("Core %d : QMSS Accumulator Throughput Result\n",
                              coreNum);
            }
        }
        System_printf("Core %d : FAILED\n", coreNum);
        goto cleanup;
    }

    /* Cleanup any buffers that may be in transmit completion queue */
    TransportQmss_recycleUsedTxBufs(qmssTransHandle);

    if (coreNum == SYSINIT) {
        System_printf("Core %d : PASSED\n", coreNum);
    }

cleanup:
    if (coreNum == SYSINIT) {
        System_printf("Core %d : "
                      "*********************************************\n\n",
                      coreNum);
    }

    /* Create the cleanup task */
    System_printf("Core %d : Creating cleanup task...\n", coreNum);
    Task_Params_init(&taskParams);
    taskParams.priority = 1;
    cleanupTskHandle = Task_create(cleanupTsk, &taskParams, NULL);
}

/**
 *  @b Description
 *  @n
 *      Application initialization task.
 */
void initTsk(UArg arg0, UArg arg1)
{
    Types_Timestamp64     time64;
    uint64_t              timeStamp;
    Task_Params           taskParams;
    Qmss_StartCfg         qmssStartCfg;
    Cppi_StartCfg         cppiStartCfg;
    int32_t               status;
    Error_Block           errorBlock;
    TransportQmss_Params  transQmssParams;
    TransportQmss_Handle  tmpTransHandle;
    GateMP_Params         gateMpParams;
    HeapBufMP_Params      heapBufParams;

    /* System initializations for each core. */
    if (coreNum == SYSINIT) {
        /* Run QMSS and CPPI system wide initializations */
        System_printf("Core %d : Initialize system peripherals\n", coreNum);
        status = systemInit();
        if (status != 0) {
            System_printf("Error Core %d : initializing system peripherals\n",
                          coreNum);
            return;
        }

        /* Signal to other DSPs that system init is complete */
        syncInit[SYNC_INDEX_SYS_INIT] = 1;
        wb((void *) &syncInit, sizeof(syncInit));
    } else {
        System_printf("Core %d : Waiting for QMSS to be initialized.\n",
                      coreNum);

        /* Wait for SYSINIT core to complete system init */
        do {
            inv((void *) &syncInit, sizeof(syncInit));
        } while (!syncInit[SYNC_INDEX_SYS_INIT]);

        /* Start Queue Manager SubSystem with RM */
        qmssStartCfg.rmServiceHandle = rmServiceHandle;
        qmssStartCfg.pQmssGblCfgParams = &qmssGblCfgParams;
        status = Qmss_startCfg(&qmssStartCfg);
        if (status != QMSS_SOK) {
            System_printf("Error Core %d : Unable to start the QMSS\n",
                          coreNum);
            return;
        }

        /* Register RM with CPPI */
        cppiStartCfg.rmServiceHandle = rmServiceHandle;
        Cppi_startCfg(&cppiStartCfg);

        System_printf("Core %d : QMSS can now be used.\n", coreNum);
    }

    /* Timestamping setup */
    Timestamp_getFreq(&timerFreq);
    System_printf("Core %d : timerFreq.lo = %d. timerFreq.hi = %d\n", coreNum,
                  timerFreq.lo, timerFreq.hi);
    BIOS_getCpuFreq(&cpuFreq);
    System_printf("Core %d : cpuFreq.lo = %d. cpuFreq.hi = %d\n", coreNum,
                  cpuFreq.lo, cpuFreq.hi);
    cpuTimerFreqRatio = (Float)cpuFreq.lo / (Float)timerFreq.lo;

    Timestamp_get64(&time64);
    timeStamp = TIMESTAMP64_TO_UINT64(time64.hi,time64.lo);
    timeAdj = TIMESTAMP64_TO_UINT64(time64.hi,time64.lo) - timeStamp;

    if (coreNum == SYSINIT) {
        /* Create the heap that will be used to allocate messages. */
        GateMP_Params_init(&gateMpParams);
        gateMpParams.localProtect = GateMP_LocalProtect_INTERRUPT;
        gateMpHandle = GateMP_create(&gateMpParams);
        
        HeapBufMP_Params_init(&heapBufParams);
        heapBufParams.regionId  = 0;
        heapBufParams.name      = QMSS_MSGQ_HEAP_NAME;
        heapBufParams.numBlocks = HOST_DESC_NUM;
        heapBufParams.blockSize = QMSS_MTU_SIZE_BYTES;
        /* GateMP so allocation can take place within QMSS rx interrupt
         * context */
        heapBufParams.gate      = gateMpHandle;
        heapHandle = HeapBufMP_create(&heapBufParams);
        if (heapHandle == NULL) {
            System_printf("Error Core %d : HeapBufMP_create failed\n", coreNum);
            return;
        }
    } else {
        /* Open the heap created by the other processor. Loop until opened. */
        do {
            status = HeapBufMP_open(QMSS_MSGQ_HEAP_NAME, &heapHandle);
        } while (status < 0);
    }

    /* Each core must register this heap with MessageQ */
    MessageQ_registerHeap((IHeap_Handle)heapHandle, QMSS_MSGQ_HEAP_ID);

    /* Create QMSS Accumulator or QPEND transport instance.  They will be
     * network transports so won't interfere with default MessageQ transport,
     * shared memory notify transport */
    TransportQmss_Params_init(&transQmssParams);
    /* Configure common parameters */
    transQmssParams.deviceCfgParams = &qmssTransCfgParams;
    transQmssParams.txMemRegion     = HOST_DESC_MEM_REGION;
    /* Descriptor pool divided between all cores.  Account for send/receive
     * (divide by 2) */
    transQmssParams.txNumDesc       = (HOST_DESC_NUM / 2) / NUM_DSP_CORES;
    transQmssParams.txDescSize      = HOST_DESC_SIZE_BYTES;
    transQmssParams.rxMemRegion     = HOST_DESC_MEM_REGION;
    /* Descriptor pool divided between all cores.  Account for send/receive
     * (divide by 2) */
    transQmssParams.rxNumDesc       = (HOST_DESC_NUM / 2) / NUM_DSP_CORES;
    transQmssParams.rxDescSize      = HOST_DESC_SIZE_BYTES;
    transQmssParams.rxMsgQHeapId    = QMSS_MSGQ_HEAP_ID;
    transQmssParams.maxMTU          = QMSS_MTU_SIZE_BYTES;
    transQmssParams.rmServiceHandle = rmServiceHandle;
    transQmssParams.rxIntVectorId   = 8;
    transQmssParams.transNetworkId  = QMSS_TRANS_NET_ID;

    /* Receive type specific parameters */
    if (testIterations & 0x1) {
        /* Odd iterations create TransportQmss instance with QPEND receive
         * logic */
        transQmssParams.rcvQParams.qType             = TransportQmss_queueRcvType_QPEND;
#if defined(DEVICE_C6657)
        /* Choose an arbitrary system event from Table 8-33 System Event
         * Mapping in tms320c6657.pdf.  System event can be anything that is not
         * already in use and maps to a different CIC host interrupt per DSP */
        transQmssParams.rcvQParams.qpend.systemEvent = 30;
#elif defined(DEVICE_C6678)
        /* Choose an arbitrary system event from Table 7-32 System Event
         * Mapping in tms320c6678.pdf.  System event can be anything that is not
         * already in use and maps to a different CIC host interrupt per DSP */
        transQmssParams.rcvQParams.qpend.systemEvent = 30;
#else
        /* Choose an arbitrary system event from Table 6-22 System Event
         * Mapping in tci6638k2k.pdf.  System event can be anything that is not
         * already in use and maps to a different CIC host interrupt per DSP */
        transQmssParams.rcvQParams.qpend.systemEvent = 43;
#endif

        System_printf("Core %d : "
                      "Creating QMSS Transport instance with rx QPEND queue\n",
                      coreNum);
    } else {
        /* Even iterations create TransportQmss instance with accumulator
         * receive logic */
        transQmssParams.rcvQParams.qType             = TransportQmss_queueRcvType_ACCUMULATOR;
        transQmssParams.rcvQParams.accum.rxAccQType  = Qmss_QueueType_HIGH_PRIORITY_QUEUE;
#if defined(LINUX_NO_BOOT) || (defined(DEVICE_C6657) || defined(DEVICE_C6678))
        transQmssParams.rcvQParams.accum.qmPdsp      = (UInt32)Qmss_PdspId_PDSP1;
#else
        /* Use PDSP3 since Linux uses PDSP1.  Using the same PDSP as Linux can
         * cause a potential PDSP firmware lockup since Linux does not use the
         * critical section preventing commands being sent to a PDSP
         * simultaneously */
        transQmssParams.rcvQParams.accum.qmPdsp      = (UInt32)Qmss_PdspId_PDSP3;
#endif
        /* Must map to a valid channel for each DSP core.  Follow sprugr9f.pdf
         * Table 5-9 */
        transQmssParams.rcvQParams.accum.accCh       = DNUM;
        transQmssParams.rcvQParams.accum.accTimerCnt = 0;

        System_printf("Core %d : "
                      "Creating QMSS Transport instance with rx Accumulator "
                      "queue\n", coreNum);
    }

    Error_init(&errorBlock);
    qmssTransHandle = TransportQmss_create(&transQmssParams, &errorBlock);
    if (qmssTransHandle == NULL) {
        System_printf("Error Core %d : "
                      "TransportQmss_create failed with id %d\n", coreNum,
                      errorBlock.id);
        return;
    }

    /* Test that only a single instance can be created per core */
    tmpTransHandle = NULL;
    tmpTransHandle = TransportQmss_create(&transQmssParams, &errorBlock);
    if (tmpTransHandle) {
        System_printf("Error Core %d : "
                      "TransportQmss_create failed because more than one "
                      "transport instance was allowed to be created\n",
                      coreNum);
        return;
    }

#if RM_PRINT_STATS
    if (coreNum == SYSINIT) {
        Rm_resourceStatus(rmHandle, 1);
    }
    Rm_instanceStatus(rmHandle);
#endif

    /* Create MessageQs after transport instances have been created since
     * the queues will be bound to the transport instances during
     * MessageQ_create */
    System_sprintf(localQueueName, "CORE%d", coreNum);
    System_sprintf(nextQueueName, "CORE%d", ((coreNum + 1) % ipcNumDspCores));

    System_printf("Core %d : "
                  "localQueueName=%s. nextQueueName=%s\n",
                  coreNum, localQueueName, nextQueueName);

    /* Create a message queue. */
    localMessageQ = MessageQ_create(localQueueName, NULL);
    if (localMessageQ == NULL) {
        System_printf("Error Core %d : MessageQ_create failed\n", coreNum);
        return;
    }

    /* Open the 'next' remote message queue. Spin until it is ready. */
    do {
        status = MessageQ_open(nextQueueName, &nextQueueId);
    } while (status < 0);

    /* Delete a previous test iterations cleanup task */
    if (cleanupTskHandle) {
        Task_delete(&cleanupTskHandle);
        cleanupTskHandle = NULL;
    }

    /* Create the test task */
    System_printf("Core %d : Creating test task...\n", coreNum);
    Task_Params_init(&taskParams);
    taskParams.priority = 1;
    testTskHandle = Task_create(testTsk, &taskParams, NULL);
}

/**
 *  @b Description
 *  @n
 *      Proxy task for the initTsk.  The initTsk needs a larger stack.  The
 *      setupRmTransConfig function does not allow specification of post-setup
 *      task stack size.  This function takes care of that for the initTsk.
 */
void proxyInitTsk(UArg arg0, UArg arg1)
{
    Task_Params taskParams;

    /* Create the initialization task */
    Task_Params_init(&taskParams);
    taskParams.priority = 1;
    taskParams.stackSize = 4096;
    initTskHandle = Task_create(initTsk, &taskParams, NULL);
}

/**
 *  @b Description
 *  @n
 *      Main - Initialize the system and start BIOS
 */
void main(int32_t argc, char *argv[])
{
    int32_t     status;
    Rm_InitCfg  rmInitCfg;
    char        rmInstName[RM_NAME_MAX_CHARS];
    int32_t     rmResult;

    coreNum = CSL_chipReadReg(CSL_CHIP_DNUM);
    ipcCoreId = MultiProc_self();
    ipcNumDspCores = NUM_DSP_CORES;
    testIterations = 0;
    testFailed = BENCH_FALSE;

    System_printf("Core %d : ********************************************\n",
                  coreNum);
    System_printf("Core %d : *** IPC QMSS Transport Benchmark Example ***\n",
                  coreNum);
    System_printf("Core %d : ********************************************\n",
                  coreNum);
    System_printf("Core %d : Device name:               %s\n", coreNum,
                  DEVICENAME);
    System_printf("Core %d : Processor names:           %s\n", coreNum,
                  PROCNAMES);
    System_printf("Core %d : IPC Core ID:               %d\n", coreNum,
                  ipcCoreId);
    System_printf("Core %d : Number of DSPs             %d\n", coreNum,
                  ipcNumDspCores);
    System_printf("Core %d : Number of test iterations: %d\n", coreNum,
                  NUM_TEST_ITERATIONS);
    System_printf("Core %d : Starting IPC core %d with name (\"%s\")\n",
                  coreNum, ipcCoreId, MultiProc_getName(ipcCoreId));

    status = Ipc_start();
    if (status < 0) {
        System_printf("Error Core %d: Ipc_start failed\n", coreNum);
        return;
    }

    /* Initialize RM */
    if (coreNum == SYSINIT) {
        /* Create the Server instance */
        memset((void *)&rmInitCfg, 0, sizeof(Rm_InitCfg));
        System_sprintf(rmInstName, "RM_Server");
        rmInitCfg.instName = rmInstName;
        rmInitCfg.instType = Rm_instType_SERVER;
        rmInitCfg.instCfg.serverCfg.globalResourceList = (void *)rmGlobalResourceList;
#if defined(LINUX_NO_BOOT) || (defined(DEVICE_C6657) || defined(DEVICE_C6678))
        rmInitCfg.instCfg.serverCfg.globalPolicy = (void *)rmDspOnlyPolicy;
#else
        rmInitCfg.instCfg.serverCfg.globalPolicy = (void *)rmDspPlusArmPolicy;
#endif
        rmHandle = Rm_init(&rmInitCfg, &rmResult);
        if (rmResult != RM_OK) {
            System_printf("Error Core %d : "
                          "Initializing Resource Manager error code : %d\n",
                          coreNum, rmResult);
            return;
        }

        syncInit[SYNC_INDEX_RM_INIT] = 1;
        wb((void *) &syncInit, sizeof(syncInit));
    } else {
        /* Create a RM Client instance */
        memset((void *)&rmInitCfg, 0, sizeof(Rm_InitCfg));
        System_sprintf(rmInstName, "RM_Client%d", coreNum);
        rmInitCfg.instName = rmInstName;
        rmInitCfg.instType = Rm_instType_CLIENT;
        rmHandle = Rm_init(&rmInitCfg, &rmResult);
        if (rmResult != RM_OK) {
            System_printf("Error Core %d : "
                          "Initializing Resource Manager error code : %d\n",
                          coreNum, rmResult);
            return;
        }

        /* Wait for RM Server to start */
        do {
            inv((void *) &syncInit, sizeof(syncInit));
        } while (!syncInit[SYNC_INDEX_RM_INIT]);
    }

    rmServiceHandle = Rm_serviceOpenHandle(rmHandle, &rmResult);
    if (rmResult != RM_OK) {
        System_printf("Error Core %d : "
                      "Creating RM service handle error code : %d\n", coreNum,
                      rmResult);
        return;
    }

    /* Configure the RM transport.  Will jump to specified task upon
     * completion */
    System_printf("Core %d : Configuring RM transport via IPC...\n", coreNum);
    if (setupRmTransConfig(ipcNumDspCores, SYSINIT, proxyInitTsk) < 0) {
        System_printf("Error Core %d : Transport setup for RM error\n",
                      coreNum);
        return;
    }

    System_printf("Core %d : Starting BIOS...\n", coreNum);
    BIOS_start();
}

