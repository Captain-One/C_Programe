/* 
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

#include <xdc/std.h>

/* XDC.RUNTIME module Headers */
#include <xdc/runtime/Types.h>

/* IPC module Headers */
#include <ti/ipc/MessageQ.h>

/* CSL modules */
#include <ti/csl/csl_chip.h>

#define VERBOSE_MODE              0

#define BENCH_FALSE               0
#define BENCH_TRUE                1

/* Message allocation/free Defines */
#define MSG_FREE_FAILED           (-1)
#define MSG_FREE_GOOD             (0)
#define MSG_PREALLOC_GOOD         (0)

/* Core Synchronization Defines */
#define CORE_SYNC_NULL_CORE       (-1)

#define CORE_SYNC_TX_SIDE_READY   (2)
#define CORE_SYNC_RX_SIDE_READY   (3)

#define SEND_MESSAGE_LAST_MESSAGE (4)

#define TEST_MSG_DATA_LEN_WORDS   16

/* Convert cycles to microseconds */
#define CYCLES_TO_US(CYCLES, CPUFREQ) \
    ((uint32_t)((((double)CYCLES * 1000000))/(double)CPUFREQ))

#define CYCLES_TO_US_DB(CYCLES, CPUFREQ) \
    ((double)((((double)CYCLES * 1000000))/(double)CPUFREQ))

/* Convert cycles to nanoseconds */
#define CYCLES_TO_NS(CYCLES, CPUFREQ) \
    ((uint32_t)((((double)CYCLES * 1000000000))/(double)CPUFREQ))

/* Convert Timestamp64 to uint64_t */
#define TIMESTAMP64_TO_UINT64(ts64hi, ts64lo) \
    ((((uint64_t) ts64hi) << 32) | ((uint64_t) ts64lo))

typedef struct {
    uint32_t numVals;
    double   stddev;
    uint32_t max;
    uint32_t min;
    uint32_t maxIndex;
    uint32_t minIndex;
    double   mean;
} Statistics;

typedef struct {
    MessageQ_MsgHeader header; /* 32 bytes */
    int32_t            src;
    int32_t            flags;
    int32_t            numMsgs;
    int32_t            seqNum;
    uint32_t           data[TEST_MSG_DATA_LEN_WORDS];
    uint8_t            pad[3856]; /* Pad to just under max SRIO message
                                   * size, 4096 bytes, so that fragmentation
                                   * does not automatically occur.  Pad must
                                   * make TstMsg multiple of 128 byte cache
                                   * line */
} TstMsg;

inline uint32_t l2_global_address(uint32_t addr)
{
    /* Compute the global address. */
    return(addr + (0x10000000 + (DNUM * 0x1000000)));
}

int32_t Osal_dataBufferInitMemory(uint32_t dataBufferSize);

void getStats(uint32_t *values, uint32_t numVals, Statistics *stats);
void attachAll(uint32_t numCores);
void detachAll(uint32_t numCores);

/* Common benchmark functions */
void     setLocalId(void);
int32_t  allocateMessages(uint32_t numMsgs, uint16_t heapId,
                          TstMsg **msgPtrArray);
int32_t  freeMessages(uint32_t numMsgs, TstMsg **msgPtrArray);
void     syncSendCore(int16_t *syncCoresArrayPtr, MessageQ_Handle coreRcvMsgQ,
                      MessageQ_QueueId *remoteCoreQIdArrayPtr,
                      TstMsg **syncMsgPtrArray, uint32_t freeRxMsgs,
                      MessageQ_Priority priority, uint16_t transId);
void     syncReceiveCore(int16_t *syncCoresArrayPtr,
                         MessageQ_Handle coreRcvMsgQ,
                         MessageQ_QueueId *remoteCoreQIdArrayPtr,
                         MessageQ_Priority priority, uint16_t transId);
uint32_t sendMessages(uint16_t numberOfReceivingCores,
                      uint32_t *numMsgsToSendPerCoreArrayPtr,
                      MessageQ_QueueId *remoteCoreQIdArrayPtr,
                      TstMsg **msgPtrArray, MessageQ_Priority priority,
                      uint16_t transId);
uint32_t receiveMessages(int16_t *sendCoresArrayPtr,
                         MessageQ_Handle coreRcvMsgQ, TstMsg **rxMsgPtrArray,
                         uint32_t uSecDelayPerMsg);
uint64_t getStartTime64();
uint64_t getExecutionTime64(uint64_t startTime,  uint64_t tsReadAdjust);
void     calculateThroughput(uint32_t numMsgsRx, uint64_t executionTime,
                             Types_FreqHz cpuFrequency);
