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

#include <math.h>

/* XDC module Headers */
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/System.h>
#include <xdc/std.h>

/* IPC modules */
#include <ti/ipc/SharedRegion.h>
#include <ti/ipc/Notify.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>

/* BIOS modules */
#include <ti/sysbios/family/c66/Cache.h>

#include <ti/transport/ipc/c66/example/common_src/bench_common.h>

extern uint32_t coreNum;

/* FUNCTION PURPOSE: Cycle Delay
 ***********************************************************************
 * DESCRIPTION: Delays for the specified amount of cycles
 */
static void cycleDelay(int count)
{
    uint32_t TSCLin = TSCL;

    if (count <= 0)
        return;

    while ((TSCL - TSCLin) < (uint32_t)count);
}

/*
 *  ======== getStats ========
 */
void getStats(uint32_t *values, uint32_t numVals, Statistics *stats )
{
    uint32_t i;
    double   sum = 0;
    
    stats->numVals = numVals;
    stats->min = values[0];
    stats->minIndex = 0;
    stats->max = values[0];
    stats->maxIndex = 0;
    for (i = 0; i < numVals; i++) {
        sum += (double)values[i];
        if (values[i] < stats->min) {
            stats->min = values[i];
            stats->minIndex = i;
        } else if (values[i] > stats->max) {
            stats->max = values[i];
            stats->maxIndex = i;
        }
    }
    stats->mean = sum / (double)numVals;
    sum = 0;
    for (i = 0; i < numVals; i++) {
        sum += pow((double)values[i] - stats->mean, 2);
    }
    stats->stddev = sqrt(sum / (double)numVals);
}


/*
 *  ======== attachAll ========
 */
void attachAll(uint32_t numCores)
{
    SharedRegion_Entry entry;
    int32_t            status;
    uint32_t           i;
    uint16_t           clusterBaseId = MultiProc_getBaseIdOfCluster();

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    /* if entry is not valid then return */
    if (entry.isValid == FALSE) {
        return;
    }

    /* Must attach to owner first to get default GateMP */
    if (MultiProc_self() != entry.ownerProcId) {
        do {
            status = Ipc_attach(entry.ownerProcId);
        } while (status < 0);
    }

    /* Loop to attach to all other processors */
    for (i = clusterBaseId; i < (clusterBaseId+numCores); i++) {
        if ((i == MultiProc_self()) || (i == entry.ownerProcId)) {
            continue;
        }

        if (Notify_numIntLines(i) == 0) {
            continue;
        }

        /* call Ipc_attach for every remote processor */
        do {
            status = Ipc_attach(i);
        } while (status < 0);
    }
}

/*
 *  ======== attachAll ========
 */

void detachAll(uint32_t numCores)
{
    SharedRegion_Entry entry;
    int32_t            status;
    uint32_t           i;
    uint16_t           clusterBaseId = MultiProc_getBaseIdOfCluster();

    /* get region 0 information */
    SharedRegion_getEntry(0, &entry);

    /* if entry is not valid then return */
    if (entry.isValid == FALSE) {
        return;
    }

    /* Loop to attach to all other processors */
    for (i = clusterBaseId; i < (clusterBaseId + numCores); i++) {
        if ((i == MultiProc_self()) || (i == entry.ownerProcId)) {
            continue;
        }

        if (Notify_numIntLines(i) == 0) {
            continue;
        }

        /* call Ipc_attach for every remote processor */
        do {
            status = Ipc_detach(i);
        } while (status < 0);
    }

    /* Must detach from shared region owner last */
    if (MultiProc_self() != entry.ownerProcId) {
        do {
            status = Ipc_detach(entry.ownerProcId);
        } while (status < 0);
    }
}

int32_t allocateMessages(Uint32 numMsgs, uint16_t heapId, TstMsg **msgPtrArray)
{
    int32_t  i;
    TstMsg  *allocatedMsg;

#if VERBOSE_MODE
    System_printf("Core %d : Preallocating %d MessageQ messages.\n",
                  coreNum, numMsgs);
#endif
    /* Allocate the number of messages specified */
    for (i = 0; i < numMsgs; i++) {
        allocatedMsg = (TstMsg *)MessageQ_alloc(heapId, sizeof(TstMsg));
        if (allocatedMsg) {
            /* Initialize and store the allocated message as long as it's not
             * NULL */
            allocatedMsg->src    = coreNum;
            allocatedMsg->seqNum = i;
            msgPtrArray[i] = allocatedMsg;
        }
        else {
            /* Return the number of messages allocated prior to error */
            return(i);
        }
    }

#if VERBOSE_MODE
    System_printf("Core %d : Allocated %d MessageQ messages.\n", 
                  coreNum, numMsgs);
#endif
    return MSG_PREALLOC_GOOD;
}

int32_t freeMessages(Uint32 numMsgs, TstMsg **msgPtrArray)
{
    int32_t i;
    int32_t status = 0;

#if VERBOSE_MODE
    System_printf ("Core %d : Freeing %d MessageQ messages.\n", 
                   coreNum, numMsgs);
#endif
    /* Free the number of messages specified */
    for (i = 0; i < numMsgs; i++) {
        status = MessageQ_free((MessageQ_Msg) msgPtrArray[i]);
        if (status < 0) {
#if VERBOSE_MODE
            System_printf("Core %d : "
                          "Freed %d messages prior to failing with error %d\n",
                          coreNum, (i+1), status);
#endif
            return MSG_FREE_FAILED;
        }
    }

#if VERBOSE_MODE
    System_printf ("Core %d : Freed %d MessageQ messages.\n", 
                   coreNum, numMsgs);
#endif
    return MSG_FREE_GOOD;
}

void syncSendCore(int16_t *syncCoresArrayPtr, MessageQ_Handle coreRcvMsgQ,
                  MessageQ_QueueId *remoteCoreQIdArrayPtr,
                  TstMsg **syncMsgPtrArray, uint32_t freeRxMsgs,
                  MessageQ_Priority priority, uint16_t transId)
{
    int32_t   status;
    int32_t   i = 0;
    TstMsg   *txSyncMsg = NULL;
    TstMsg   *rxSyncMsg = NULL;
    uint32_t  syncReceivedMask = 0; /* Support for up to 32 cores */

    /* Send a sync message to each core */
    while (syncCoresArrayPtr[i] != CORE_SYNC_NULL_CORE) {
        /* Get a new sync message */
        txSyncMsg = syncMsgPtrArray[i];
        txSyncMsg->src = coreNum;
        txSyncMsg->flags = CORE_SYNC_TX_SIDE_READY;
        MessageQ_setTransportId(txSyncMsg, transId);
        /* Priority is ignored if transport ID is set to a value between
         * 1 and 7 */
        MessageQ_setMsgPri(txSyncMsg, priority);

        /* Send the TX side sync message */
#if VERBOSE_MODE
        System_printf ("Core %d : Sending sync message to Core %d\n",
                       coreNum, syncCoresArrayPtr[i]);
#endif
        status = MessageQ_put(remoteCoreQIdArrayPtr[i],
                              (MessageQ_Msg)txSyncMsg);
        if (status < 0) {
            System_printf("Error Core %d : ", coreNum);
            System_abort("MessageQ_put failed\n");
        }

        /* Add to mask the core that sync was sent to */
        syncReceivedMask |= (0x1 << syncCoresArrayPtr[i]);
        i++;
    }

    /* Wait for response from remote cores */
    do {
        /* Get the sync message */
        status = MessageQ_get(coreRcvMsgQ, (MessageQ_Msg*)&rxSyncMsg,
                              MessageQ_FOREVER);
        if (status < 0) {
            System_printf("Error Core %d : ", coreNum);
            System_abort("MessageQ_get failed\n");
        }

        /* Check if it is remote core informing it is sync'd */
        if (rxSyncMsg->flags == CORE_SYNC_RX_SIDE_READY) {
            /* Clear the core from the received mask */
            if (syncReceivedMask & (0x1 << rxSyncMsg->src)) {
#if VERBOSE_MODE
                System_printf("Core %d : "
                              "Received sync message back from Core %d\n",
                              coreNum, rxSyncMsg->src);
#endif
                syncReceivedMask &= ~(0x1 << rxSyncMsg->src);
            }
        }

        if (freeRxMsgs) {
            /* Free message if requested.  This is used for certain transport
             * implementations that allocate new messages for each newly
             * received packet */
            MessageQ_free((MessageQ_Msg) rxSyncMsg);
        }
    } while(syncReceivedMask != 0);
}

void syncReceiveCore(int16_t *syncCoresArrayPtr, MessageQ_Handle coreRcvMsgQ,
                     MessageQ_QueueId *remoteCoreQIdArrayPtr,
                     MessageQ_Priority priority, uint16_t transId)
{
    int32_t   status;
    int32_t   i = 0;
    int16_t   coreIndex = 0;
    TstMsg   *txSyncMsg = NULL;
    TstMsg   *rxSyncMsg = NULL;
    uint32_t  syncReceivedMask = 0; /* Support for up to 32 cores */

    /* Initialize the receive core bitfield for verifying all sync messages
     * were received */
    while (syncCoresArrayPtr[i] != CORE_SYNC_NULL_CORE) {
        /* Add to mask the core that sync should be received from */
        syncReceivedMask |= (0x1 << syncCoresArrayPtr[i]);
        i++;
    }

    /* Receive sync messages as long as sync's have not been received from
     * all specified cores */
    while (syncReceivedMask != 0) {
        /* Wait for sync message from TX core */
        do {
            /* Get the sync message */
            status = MessageQ_get(coreRcvMsgQ, (MessageQ_Msg*)&rxSyncMsg,
                                  MessageQ_FOREVER);
            if (status < 0) {
                System_printf("Error Core %d : ", coreNum);
                System_abort("MessageQ_get failed\n");
            }

            /* Check if it is sending core wanting to sync */
            if (rxSyncMsg->flags == CORE_SYNC_TX_SIDE_READY) {
                /* Clear the core from the received mask */
                if (syncReceivedMask & (0x1 << rxSyncMsg->src)) {
#if VERBOSE_MODE
                    System_printf("Core %d : "
                                  "received sync message from Core %d\n",
                                  coreNum, rxSyncMsg->src);
#endif
                    syncReceivedMask &= ~(0x1 << rxSyncMsg->src);

                    /* Store index of core for send back of sync */
                    i = 0;
                    while (syncCoresArrayPtr[i] != CORE_SYNC_NULL_CORE) {
                        if (syncCoresArrayPtr[i] == rxSyncMsg->src) {
                            coreIndex = i;
                            break;
                        }
                        i++;
                    }
                }
            }
        } while(rxSyncMsg->flags != CORE_SYNC_TX_SIDE_READY);

        txSyncMsg = rxSyncMsg;
        txSyncMsg->src = coreNum;
        txSyncMsg->flags = CORE_SYNC_RX_SIDE_READY;
        MessageQ_setTransportId(txSyncMsg, transId);
        /* Priority is ignored if transport ID is set to a value between
         * 1 and 7 */
        MessageQ_setMsgPri(txSyncMsg, priority);

        /* Send the RX side sync message */
#if VERBOSE_MODE
        System_printf("Core %d : Sending sync message back to Core %d\n",
                      coreNum, syncCoresArrayPtr[i]);
#endif
        status = MessageQ_put(remoteCoreQIdArrayPtr[coreIndex],
                              (MessageQ_Msg)txSyncMsg);
        if (status < 0) {
            System_printf("Error Core %d : ", coreNum);
            System_abort("MessageQ_put failed\n");
        }
    }
}

uint32_t sendMessages(uint16_t numberOfReceivingCores,
                      uint32_t *numMsgsToSendPerCoreArrayPtr,
                      MessageQ_QueueId *remoteCoreQIdArrayPtr,
                      TstMsg **msgPtrArray, MessageQ_Priority priority,
                      uint16_t transId)
{
    uint32_t  maxMsgs = 0;
    int32_t   i, j;
    int32_t   status;
    uint32_t  msgIndex = 0;
    TstMsg   *sndMsg;

    /* Find maximum number of messages to be sent */
    for (i = 0; i < numberOfReceivingCores; i++) {
        if (numMsgsToSendPerCoreArrayPtr[i] > maxMsgs) {
            maxMsgs = numMsgsToSendPerCoreArrayPtr[i];
        }
    }

    /* Send the specified number of messages to the specified cores.  
    * The last message sent will have a flag signifying to receiving core that
    * all messages have been sent. */
    for (i = 0; i < maxMsgs; i++) {
        for (j = 0; j < numberOfReceivingCores; j++) {
            /* Send a message if haven't gone over max to send to this
             * destination core */
            if (i < numMsgsToSendPerCoreArrayPtr[j]) {
                /* Get a message */
                sndMsg = msgPtrArray[msgIndex];
                sndMsg->src = coreNum;
                MessageQ_setTransportId(sndMsg, transId);
                /* Priority is ignored if transport ID is set to a value
                 * between 1 and 7 */
                MessageQ_setMsgPri(sndMsg, priority);

                if (i == (numMsgsToSendPerCoreArrayPtr[j] - 1)) {
                    /* If it's the last message for this core inform the
                     * remote core */
                    sndMsg->flags = SEND_MESSAGE_LAST_MESSAGE;
#if VERBOSE_MODE
                    System_printf("Core %d : "
                                  "Sent %d messages to Queue ID: %d\n",
                                  coreNum, (i+1), remoteCoreQIdArrayPtr[j]);
#endif
                }
                else {
                    sndMsg->flags = 0;
                }

                /* Send message to remote core */
                status = MessageQ_put(remoteCoreQIdArrayPtr[j],
                                      (MessageQ_Msg)sndMsg);
                if (status < 0) {
                    System_abort("MessageQ_put failed\n");
                }

                msgIndex++;
            }
        }
    }

    return msgIndex;
}

uint32_t receiveMessages(int16_t *sendCoresArrayPtr,
                         MessageQ_Handle coreRcvMsgQ, TstMsg **rxMsgPtrArray,
                         uint32_t uSecDelayPerMsg)
{
    uint32_t  numberReceived = 0;
    int32_t   status;
    int32_t   i = 0;
    TstMsg   *rxMsg;
    uint32_t  senderCoresMask = 0; /* Support for up to 32 cores */

    /* Initialize the sender core bitfield for to track whether all messages 
     * have been received from all senders */
    while (sendCoresArrayPtr[i] != CORE_SYNC_NULL_CORE) {
        /* Add to mask the core that sync should be received from */
        senderCoresMask |= (0x1 << sendCoresArrayPtr[i]);
        i++;
    }

    /* Receive messages until all senders have completed */
    while (senderCoresMask) {
        /* Get a message */
        status = MessageQ_get(coreRcvMsgQ, (MessageQ_Msg*)&rxMsg,
                              MessageQ_FOREVER);
        if (status < 0) {
            System_printf("Error Core %d : ", coreNum);
            System_abort("MessageQ_get failed\n");
        }

        /* Make sure the message received was from an expected sender */
        if (senderCoresMask & (0x1 << rxMsg->src)) {
            if (rxMsg->flags == SEND_MESSAGE_LAST_MESSAGE) {
#if VERBOSE_MODE
                System_printf("Core %d : "
                              "Received all messages from Core %d\n",
                              coreNum, rxMsg->src);
#endif
                senderCoresMask &= ~(0x1 << rxMsg->src);
            }

            /* Time system should wait in while loop per message.  This can be
             * used to simulate application processing for each message
             * received */
            if (uSecDelayPerMsg != 0) {
                cycleDelay(uSecDelayPerMsg);
            }

            /* Store the received messageQ msg for use by the application */
            if (rxMsgPtrArray != NULL) {
                rxMsgPtrArray[numberReceived] = rxMsg;
            }

            numberReceived++;
#if VERBOSE_MODE
            System_printf("Core %d : Received message from Core %d\n",
                          coreNum, rxMsg->src);
            System_printf("Core %d : Total received: %d, Last seqNum %d\n",
                          numberReceived, rxMsg->seqNum);
#endif
        } else {
#if VERBOSE_MODE
            System_printf("Core %d : "
                          "Received unexpected message from Core %d\n",
                          coreNum, rxMsg->src);
#endif
        }
    }

#if VERBOSE_MODE
    System_printf("Core %d : Received a total of %d messages\n",
                  coreNum, numberReceived);
#endif

    return(numberReceived);
}

uint64_t getStartTime64()
{
    Types_Timestamp64 time64;

    Timestamp_get64(&time64);
    return(TIMESTAMP64_TO_UINT64(time64.hi,time64.lo));
}

uint64_t getExecutionTime64(uint64_t startTime, uint64_t tsReadAdjust)
{
    Types_Timestamp64 time64;

    Timestamp_get64(&time64);
    return(TIMESTAMP64_TO_UINT64(time64.hi,time64.lo) -
           startTime - tsReadAdjust);
}

void calculateThroughput(uint32_t numMsgsRx, uint64_t executionTime,
                         Types_FreqHz cpuFrequency)
{
    long throughPut = 0;
    long throughPutBytes = 0;

    throughPut = ((uint32_t)(1000000)*(double)numMsgsRx /
                  (double)CYCLES_TO_US(executionTime, cpuFrequency.lo));

    throughPutBytes = throughPut * sizeof(TstMsg);

    System_printf("Core %d : "
                  "============= THROUGHPUT RESULTS ============\n", coreNum);
    System_printf("Core %d : Msgs received = %u\n", coreNum, numMsgsRx);
    System_printf("Core %d : Time          = %u cycles (%d us)\n", coreNum,
                  (uint32_t) executionTime,
                  (uint32_t) CYCLES_TO_US(executionTime, cpuFrequency.lo));
    System_printf("Core %d : Throughput    = %ul [msgs/s]\n", coreNum,
                  throughPut);
    System_printf("Core %d :               = %ul [bytes/s]\n", coreNum,
                  throughPutBytes);
    System_printf("Core %d : Cycles/msg    = %u\n", coreNum, 
                  (uint32_t)(((double)executionTime)/((double)numMsgsRx)));
}
