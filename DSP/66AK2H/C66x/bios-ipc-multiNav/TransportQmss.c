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
 * */
 
/*
 *  ======== TransportQmss.c ========
 */

/* XDC includes */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>

/* BIOS includes */
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c66/tci66xx/CpIntc.h> 
#include <ti/sysbios/family/c66/Cache.h>
#include <ti/sysbios/knl/Task.h>

/* IPC internal includes */
#include <ti/sdo/ipc/_MessageQ.h>

/* IPC external include */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>

/* CSL Includes */
#include <ti/csl/csl_chip.h>

/* QMSS LLD */
#include <ti/drv/qmss/qmss_drv.h>

/* CPPI LLD */
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>

/* RM LLD */
#include <ti/drv/rm/rm_services.h>

/* QMSS Transport include */
#include "package/internal/TransportQmss.xdc.h"

#define TRANS_QMSS_MAX_PAGE_ENTRIES    80
/* Initial allocation size of sorted list used for destination flow cache */
#define FLOW_CACHE_INIT_SIZE           16
/* Return value for flow IDs not found in the flow cache */
#define UNCACHED_FLOW_ID               (-1)
/* Recycle all used buffers in the txCompletionQ */
#define TRANS_QMSS_RECYCLE_ALL_TX_BUFS (-1)

static UInt32 l2_to_global_addr(UInt32 addr)
{
    if ((addr & 0xFF800000) == 0x00800000) {
        /* In L2, compute the global address. */
        return(addr + (0x10000000 + (DNUM << 24)));
    } else {
        return(addr);
    }
}

static UInt32 global_to_l2_addr(UInt32 addr)
{
    UInt32 mask = 0x10000000 + (DNUM << 24);

    if ((addr & 0xFF000000) == mask) {
        /* Return L2 address */
        return(addr - mask);
    } else {
        /* DDR3 or MSMC - do nothing */
        return(addr);
    }
}

static Void wb(Void *addr, UInt32 numBytes)
{
    UInt32 coreMask = 0x10000000 + (DNUM << 24);

    if ((((UInt32)addr) & 0x1F800000) != coreMask) {
        /* A different core's global L2 addres - only writeback L1 */
        Cache_wb((Ptr)addr, numBytes, Cache_Type_L1D, TRUE);
    } else if ((((UInt32)addr) & 0xFC000000) == 0x0C000000) {
        /* MSMC addres - only writeback L1 */
        Cache_wb((Ptr)addr, numBytes, Cache_Type_L1D, TRUE);
    } else if ((((UInt32)addr) & 0x80000000) == 0x80000000) {
        /* DDR3 address - writeback L1 & L2 */
        Cache_wb((Ptr)addr, numBytes, Cache_Type_ALL, TRUE);
    }
}

static Void inv(Void *addr, UInt32 numBytes) 
{
    UInt32 coreMask = 0x10000000 + (DNUM << 24);

    if ((((UInt32)addr) & 0x1F800000) != coreMask) {
        /* A different core's global L2 addres - only invalidate L1 */
        Cache_inv((Ptr)addr, numBytes, Cache_Type_L1D, TRUE);
    } else if ((((UInt32)addr) & 0xFC000000) == 0x0C000000) {
        /* MSMC addres - only invalidate L1 */
        Cache_inv((Ptr)addr, numBytes, Cache_Type_L1D, TRUE);
    } else if ((((UInt32)addr) & 0x80000000) == 0x80000000) {
        /* DDR3 address - invalidate L1 & L2 */
        Cache_inv((Ptr)addr, numBytes, Cache_Type_ALL, TRUE);
    }
}

/* FUNCTION PURPOSE: Utility to feed a command to RM
 ***********************************************************************
 * DESCRIPTION: Formulates a RM service request and returns the response
 *              data value and resultant state
 */
static int32_t rm_cmd(Rm_ServiceHandle *service_h, const char *name,
                      int32_t *val, Rm_ServiceType type, int retry)
{
    Rm_ServiceReqInfo  rmServiceReq;
    Rm_ServiceRespInfo rmServiceResp;
    int                succeed;

    memset((void *)&rmServiceReq, 0, sizeof(rmServiceReq));
    memset((void *)&rmServiceResp, 0, sizeof(rmServiceResp));
    
    rmServiceReq.type           = type;
    rmServiceReq.resourceName   = name;
    rmServiceReq.resourceNsName = name;
    rmServiceReq.resourceLength = 1;
    if (val) {
        rmServiceReq.resourceBase = *val;
    }

    /* RM will block until resource is returned since callback is NULL */
    rmServiceReq.callback.serviceCallback = NULL;
    do {
        service_h->Rm_serviceHandler(service_h->rmHandle, &rmServiceReq,
                                     &rmServiceResp);
        succeed = (rmServiceResp.serviceState == RM_SERVICE_APPROVED) ||
                  (rmServiceResp.serviceState == RM_SERVICE_APPROVED_STATIC);
        if (retry && (!succeed)) {
            Task_sleep(1);
        }
    } while (retry && (!succeed));

    if (succeed) {
        if ((type == Rm_service_RESOURCE_GET_BY_NAME) && (val)) {
            *val = rmServiceResp.resourceBase;
        }
    } else {
        if (rmServiceResp.serviceState < RM_ERROR_BASE) {
            Log_warning4("RM transaction failed %d %s %d (%d)\n", type,
                         (xdc_IArg)name, val ? *val : 0,
                         rmServiceResp.serviceState);
        } else {
            Log_warning4("RM transaction denied %d %s %d (%d)\n", type,
                         (xdc_IArg)name, val ? *val : 0,
                         rmServiceResp.serviceState);
        }
    }

    return(rmServiceResp.serviceState);
}

/* FUNCTION PURPOSE: Utility to lookup a name in RM NameServer
 ***********************************************************************
 * DESCRIPTION: Sends a name lookup request to RM NameServer.  Value
 *              associated with the name is returned through the val pointer
 *              if the name exists.  The service request state (pass, deny, or
 *              fail) is returned.
 */
static int32_t rm_name_lookup(Rm_ServiceHandle *service_h, const char *name,
                              int32_t *val)
{
    *val = RM_RESOURCE_BASE_UNSPECIFIED;
    return(rm_cmd(service_h, name, val, Rm_service_RESOURCE_GET_BY_NAME, 1));
}

/* FUNCTION PURPOSE: Utility to set a name in RM NameServer
 ***********************************************************************
 * DESCRIPTION: Sends a name set request to RM NameServer.  Value to be
 *              associated with the name is passed through the val pointer.
 *              The service request state (pass, deny, or fail) is returned.
 */
static int32_t rm_name_set(Rm_ServiceHandle *service_h, const char *name,
                           int32_t *val)
{
    return(rm_cmd(service_h, name, val, Rm_service_RESOURCE_MAP_TO_NAME, 0));
}

/* FUNCTION PURPOSE: Utility to delete a name from the RM NameServer
 ***********************************************************************
 * DESCRIPTION: Sends a name delete request to RM NameServer.  The service
 *              request state (pass, deny, or fail) is returned.
 */
static int32_t rm_name_del(Rm_ServiceHandle *service_h, const char *name)
{
    return(rm_cmd(service_h, name, NULL, Rm_service_RESOURCE_UNMAP_NAME, 0));
}

/* FUNCTION PURPOSE: Utility to lookup CPPI flow ID in the flow cache
 ***********************************************************************
 * DESCRIPTION: Looks up a CPPI flow ID based on an associated MessageQ
 *              queue ID.  Assumes the flow cache list is a sorted list
 *              with the sort key being the MessageQ queue ID.
 *              UNCACHED_FLOW_ID will be returned for a failed lookup
 */
static int32_t fcache_list_lookup(TransportQmss_FlowCacheList *list,
                                  uint32_t queue_id)
{
    uint16_t min = 0;
    uint16_t max = list->used_nodes;
    uint16_t mid;

    while (max >= min) {
        mid = min + ((max - min) / 2);
        if (list->node_list[mid].queue_id == queue_id) {
            return ((int32_t) list->node_list[mid].flow);
        } else if (list->node_list[mid].queue_id < queue_id) {
            min = mid + 1;
        } else {
            max = mid - 1;
        }
    }
    return(UNCACHED_FLOW_ID);
}

/* FUNCTION PURPOSE: Utility to add a CPPI flow ID to the flow cache
 ***********************************************************************
 * DESCRIPTION: Adds a MessageQ queue ID to CPPI rx flow ID mapping to
 *              the flow cache sorted list.  New cache entry will be
 *              slotted into the flow cache based on the MessageQ queue ID.
 *              Total nodes will be expanded by a power of 2 if 
 *              used_nodes = total_nodes prior to adding the new entry
 */
static void fcache_list_add(TransportQmss_FlowCacheList *list,
                            uint32_t queue_id, uint16_t flow)
{
    TransportQmss_FlowCacheNode *tmp_list;
    uint32_t                     tmp_total;
    uint32_t                     i;
    Error_Block                  eb;

    Error_init(&eb);

    if (list->total_nodes == list->used_nodes) {
        /* Need to expand list by power of 2 */
        tmp_list = list->node_list;
        tmp_total = list->total_nodes;
        list->total_nodes *= 2;
        list->node_list = Memory_alloc(0,
            (list->total_nodes * sizeof(*(list->node_list))), 16, &eb);
        for (i = 0; i < list->used_nodes; i++) {
            list->node_list[i] = tmp_list[i];
        }
        Memory_free(0, (UInt32 *)tmp_list, tmp_total * sizeof(*tmp_list));
    }

    for (i = list->used_nodes;
         (i > 0) && (queue_id < list->node_list[i - 1].queue_id);
         i--) {
        list->node_list[i].queue_id = list->node_list[i - 1].queue_id;
        list->node_list[i].flow= list->node_list[i - 1].flow;
    }
    list->node_list[i].queue_id = queue_id;
    list->node_list[i].flow = flow;
    list->used_nodes++;
}

/* FUNCTION PURPOSE: Utility to remove a CPPI flow ID from the flow cache
 ***********************************************************************
 * DESCRIPTION: Deletes a MessageQ queue ID to CPPI rx flow ID mapping from
 *              the flow cache sorted list.  Total nodes will be contracted by
 *              a power of 2 if used_nodes = (total_nodes/2) post entry removal
 */
static void fcache_list_del(TransportQmss_FlowCacheList *list, 
                            uint32_t queue_id)
{
    TransportQmss_FlowCacheNode *tmp_list;
    uint32_t                     tmp_total;
    uint32_t                     i;
    Error_Block                  eb;

    Error_init(&eb);

    for (i = 0; i < (list->used_nodes - 1); i++) {
        if (list->node_list[i].queue_id >= queue_id) {
            list->node_list[i].queue_id = list->node_list[i+1].queue_id;
            list->node_list[i].flow = list->node_list[i+1].flow;
        }
    }
    list->node_list[i].queue_id = 0;
    list->node_list[i].flow = 0;
    list->used_nodes--;

    if (list->used_nodes == (list->total_nodes / 2)) {
        /* Need to shrink list by power of 2 */
        tmp_list = list->node_list;
        tmp_total = list->total_nodes;
        list->total_nodes /= 2;
        list->node_list = Memory_alloc(0,
            (list->total_nodes * sizeof(*(list->node_list))), 16, &eb);
        for (i = 0; i < list->used_nodes; i++) {
            list->node_list[i].queue_id = tmp_list[i].queue_id;
            list->node_list[i].flow = tmp_list[i].flow;
        }
        Memory_free(0, (UInt32 *)tmp_list, tmp_total * sizeof(*tmp_list));
    }
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/**
 *  @b Description
 *  @n
 *      Resets all QMSS transport module parameters to initial state.
 *      This should be done after all instances of a transport have
 *      been closed on a DSP core.
 *
 *  @retval
 *      Not Applicable.
 */
static Void transportQmssResetModuleParams(Int status)
{
    UInt32 hwiKey;

    switch (status) {
        /* Errors that don't require module param reset */
        case TransportQmss_ERROR_INVALID_QUEUE_RCV_TYPE:
        case TransportQmss_ERROR_INST_ALREADY_EXISTS:
            return;
        default:
            break;
    }

    hwiKey = Hwi_disable();
    TransportQmss_module->instCreated = 0;
    Hwi_restore(hwiKey);
}

/**
 *  @b Description
 *  @n
 *      Cleans up an instance of TransportQmss.
 *
 *  @retval
 *      Not Applicable.
 */
static Void transportQmssInstCleanup(TransportQmss_Object *obj)
{
    if (obj->flowCache.node_list) {
        Memory_free(0, (UInt32 *)obj->flowCache.node_list,
            (obj->flowCache.total_nodes * sizeof(*(obj->flowCache.node_list))));
    }

    if (obj->hwiHandle) {
        /* Disable the interrupt tied to the receive side */
        Hwi_disableInterrupt(obj->rxIntVectorId);
        Hwi_delete((Hwi_Handle *) &(obj->hwiHandle));

        if (obj->queueRcvConfig == TransportQmss_queueRcvType_QPEND) {
            UInt                      cpIntId = 0;
            TransportQmss_hostIntMod *hostIntMods;
            UInt                      hostInt = 0;
            Int                       i;

            cpIntId     = obj->devCfg->dspIntcCfg[DNUM].cic;
            hostIntMods = obj->devCfg->hostIntModMap;

            /* Find CIC secondary interrupt based on the QPENDQ chosen */
            i = 0;
            while (hostIntMods[i].sysEvt != (-1)) {
                if (hostIntMods[i].sysEvt == obj->u.qpend.sysEvt) {
                    hostInt = hostIntMods[i].offset +
                              (hostIntMods[i].multiplier * DNUM);
                    break;
                }
                i++;
            }

            if (hostInt) {
                CpIntc_disableHostInt(cpIntId, hostInt);
            }
        }
    }

    /* Disable and Close CPPI channels and flows */
    if (obj->rxCppiHnd) {
        Cppi_channelDisable(obj->rxCppiHnd);
    }
    if (obj->txCppiHnd) {
        Cppi_channelDisable(obj->txCppiHnd);
    }
    if (obj->rxFlowHnd) {
        Cppi_closeRxFlow(obj->rxFlowHnd);
    }

    if (obj->txQ) {
        Qmss_queueEmpty(obj->txQ);
        Qmss_queueClose(obj->txQ);
    }

    if (obj->rxCppiHnd) {
        Cppi_channelClose(obj->rxCppiHnd);
    }
    if (obj->txCppiHnd) {
        Cppi_channelClose(obj->txCppiHnd);
    }

    if (obj->cppiHnd) {
        Cppi_closeDecRef(obj->cppiHnd);
    }

    /* Disable the accumulator channel */
    if (obj->u.accum.pdsp != (-1)) {
        Qmss_disableAccumulator((Qmss_PdspId)obj->u.accum.pdsp,
                                obj->u.accum.accCh);
    }

    /* Empty and close all QMSS queues */
    if (obj->txCompletionQ) {
        /* Clean up any MessageQ buffers attached to completed send
         * descriptors */
        while (Qmss_getQueueEntryCount(obj->txCompletionQ)) {
            Cppi_HostDesc *hostDesc;
            MessageQ_Msg   msgQBuf;
            UInt32         numBytes;

            hostDesc = (Cppi_HostDesc *) QMSS_DESC_PTR(Qmss_queuePop(obj->txCompletionQ));
            Cppi_getData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                         (UInt8 **)&msgQBuf, &numBytes);
            if (msgQBuf) {
                msgQBuf = (MessageQ_Msg) global_to_l2_addr((UInt32) msgQBuf);
                MessageQ_free(msgQBuf);
            }
        }
        Qmss_queueEmpty(obj->txCompletionQ);
        Qmss_queueClose(obj->txCompletionQ);
    }
    if (obj->txFreeQ) {
        Qmss_queueEmpty(obj->txFreeQ);
        Qmss_queueClose(obj->txFreeQ);
    }
    if (obj->rxFreeQ) {
        /* Clean up any MessageQ buffers attached to rx free descriptors */
        while (Qmss_getQueueEntryCount(obj->rxFreeQ)) {
            Cppi_HostDesc *hostDesc;
            MessageQ_Msg   msgQBuf;
            UInt32         numBytes;

            hostDesc = (Cppi_HostDesc *) QMSS_DESC_PTR(Qmss_queuePop(obj->rxFreeQ));
            Cppi_getData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                         (UInt8 **)&msgQBuf, &numBytes);
            if (msgQBuf) {
                msgQBuf = (MessageQ_Msg) global_to_l2_addr((UInt32) msgQBuf);
                MessageQ_free(msgQBuf);
            }
        }
        Qmss_queueEmpty(obj->rxFreeQ);
        Qmss_queueClose(obj->rxFreeQ);
    }
    if (obj->u.accum.rxAccQ) {
        Qmss_queueClose(obj->u.accum.rxAccQ);
    }

    if (obj->u.accum.accList) {
        /* Free accumulator list memory */
        Memory_free(0, (UInt32 *)(global_to_l2_addr(
            (UInt32)obj->u.accum.accList)), obj->u.accum.accListSize);
    }

    if (obj->u.qpend.rxQpendQ) {
        Qmss_queueEmpty(obj->u.qpend.rxQpendQ);
        Qmss_queueClose(obj->u.qpend.rxQpendQ);
    }
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/* CPPI TX ch, RX ch, and infrastructure queue form a triplet that must
 * be allocated together based on the same value */
static Int transportQmssAllocInfraTriplet(TransportQmss_Object *obj)
{
    Qmss_QueueHnd     tmpTxQ;
    Cppi_ChHnd        tmpTxCh;
    Cppi_ChHnd        tmpRxCh;
    Cppi_TxChInitCfg  txChCfg;
    Cppi_RxChInitCfg  rxChCfg;
    Qmss_QueueHnd    *invTrip = NULL;
    int               invIdx;
    uint32_t          isAllocated;
    int               foundTriplet;
    int               i;
    Int               retVal = TransportQmss_OK;
    Error_Block       eb;

    Error_init(&eb);

    /* Init array where invalid triplets are stored.  Invalid triplets will be
     * freed once a valid triplet is found */
    invTrip = (int32_t *)Memory_alloc(0, obj->devCfg->qmssInfraQMax *
                                      sizeof(Qmss_QueueHnd), 0, &eb);
    memset(invTrip, 0,
           obj->devCfg->qmssInfraQMax * sizeof(Qmss_QueueHnd));
    invIdx = 0;
    
    foundTriplet = 0;
    while(!foundTriplet) {
        /* Open the Tx infrastructure queue.  Should be offset from infrastructure
         * queue base using the CPPI tx channel number */
        tmpTxQ = Qmss_queueOpen(Qmss_QueueType_INFRASTRUCTURE_QUEUE,
                                QMSS_PARAM_NOT_SPECIFIED,
                                (UInt8 *)&isAllocated);
        if (tmpTxQ < 0) {
            retVal = TransportQmss_ERROR_COULD_NOT_FIND_INFRA_TRIPLET;
            goto triplet_error;
        }

        memset((void *)&txChCfg, 0, sizeof(txChCfg));
        txChCfg.channelNum  = Qmss_getQIDFromHandle(tmpTxQ) -
                              obj->devCfg->qmssInfraQBase;
        txChCfg.priority    = 0;
        txChCfg.filterEPIB  = 0;
        txChCfg.filterPS    = 0;
        txChCfg.aifMonoMode = 0;
        txChCfg.txEnable    = Cppi_ChState_CHANNEL_DISABLE;
        tmpTxCh = (UInt32 *)Cppi_txChannelOpen(obj->cppiHnd, &txChCfg,
                                               (uint8_t *)&isAllocated);
        if (tmpTxCh == NULL) {
            invTrip[invIdx++] = tmpTxQ;
            /* Try to get next triplet */
            continue;
        }

        memset((void *)&rxChCfg, 0, sizeof(rxChCfg));
        rxChCfg.channelNum = Qmss_getQIDFromHandle(tmpTxQ) -
                              obj->devCfg->qmssInfraQBase;
        rxChCfg.rxEnable   = Cppi_ChState_CHANNEL_DISABLE;
        tmpRxCh = (UInt32 *)Cppi_rxChannelOpen(obj->cppiHnd, &rxChCfg,
                                               (uint8_t *)&isAllocated);
        if (tmpRxCh == NULL) {
            Cppi_channelClose(tmpTxCh);
            invTrip[invIdx++] = tmpTxQ;
            /* Try to get next triplet */
            continue;
        }
        /* Found a triplet if got here */
        foundTriplet = 1;
    }

    /* Save triplet */
    obj->txQ       = tmpTxQ;
    obj->txCppiHnd = tmpTxCh;
    obj->rxCppiHnd = tmpRxCh;

triplet_error:
    /* Free unused triplets */
    for (i = 0; i < invIdx; i++) {
        Qmss_queueClose(invTrip[i]);
    }
    Memory_free(0, (UInt32 *)invTrip, obj->devCfg->qmssInfraQMax *
                                      sizeof(Qmss_QueueHnd));

    return(retVal);
}

static Int transportQmssAllocIntcQ(TransportQmss_Object *obj)
{
    TransportQmss_intcQInfo *intcInfo;
    int32_t                  i, j;
    Qmss_QueueHnd            tmpQ;
    UInt                     tmpSecInt;
    uint8_t                  isAllocated;
    Int                      retVal = TransportQmss_OK;

    intcInfo = obj->devCfg->dspIntcCfg[DNUM].intcInfo;

    /* Open QPEND receive queues until a valid queue for the DSP is found */
    i = 0;
    while ((obj->u.qpend.rxQpendQ == 0) && (intcInfo[i].baseQ != -1)) {
        for (j = intcInfo[i].baseQ, tmpSecInt = intcInfo[i].baseSecInt;
             j < (intcInfo[i].baseQ + intcInfo[i].len);
             j++, tmpSecInt++) {
            tmpQ = Qmss_queueOpen((Qmss_QueueType)QMSS_PARAM_NOT_SPECIFIED, j,
                                  &isAllocated);
            if ((tmpQ < 0) && (tmpQ != QMSS_RESOURCE_ALLOCATE_USE_DENIED)) {
                retVal = TransportQmss_ERROR_COULD_NOT_OPEN_RX_QPEND_Q;
                goto error_ret;
            }

            if ((tmpQ != QMSS_RESOURCE_ALLOCATE_USE_DENIED) &&
                (isAllocated == 1)) {
                obj->u.qpend.rxQpendQ = tmpQ;
                obj->u.qpend.cicSecInt = tmpSecInt;
                break;
            } else {
                Qmss_queueClose(tmpQ);
            }
        }
        i++;
    }

    if (obj->u.qpend.rxQpendQ == 0) {
        retVal = TransportQmss_ERROR_COULD_NOT_FIND_VALID_RX_QPEND_Q;
    }
error_ret:
    return(retVal);
}

/**
 *  @b Description
 *  @n
 *      Allocates a new MessageQ buffer for a QMSS receive descriptor
 *
 *  @retval
 *      Not Applicable.
 */
static Void transportQmssNewRxBuf(TransportQmss_Object *obj,
                                  Cppi_HostDesc *hostDesc)
{
    MessageQ_Msg newMsg = MessageQ_alloc(obj->rxMsgQHeapId, obj->maxMTU);

    Assert_isTrue((newMsg != NULL), TransportQmss_A_newRxBufNull);

    /* Convert the buffer to the global address - Only applicable for buffers
     * residing in L2 */
    newMsg = (MessageQ_Msg) l2_to_global_addr((UInt32) newMsg);

    Cppi_setData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc, (UInt8 *)newMsg,
                 obj->maxMTU);
    Cppi_setOriginalBufInfo(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                            (UInt8 *)newMsg, obj->maxMTU);

    wb((Void *)newMsg, newMsg->msgSize);
    wb((Void *)hostDesc, obj->rxDescSize);

    Qmss_queuePushDescSize(obj->rxFreeQ, (Void *)hostDesc, obj->rxDescSize);
}

/**
 *  @b Description
 *  @n
 *      Recycle QMSS transmit side buffers.  If TRANS_QMSS_RECYCLE_ALL_TX_BUFS
 *      (-1) is passed all buffers in the TX completion queue will be recycled.
 *
 *  @retval
 *      Int - Number of buffers recycled
 */
static Int transportQmssTxBufRecycle(TransportQmss_Object *obj,
                                     Int numBufsToRecycle)
{
    Int            i = 0;
    Cppi_HostDesc *hostDesc;
    Ptr            msg;
    UInt32         msgQDataLen;
    Int32          status;
    Qmss_QueueHnd  txCompQ = (Qmss_QueueHnd) obj->txCompletionQ;

    while (1) {
        if (numBufsToRecycle != TRANS_QMSS_RECYCLE_ALL_TX_BUFS) {
            if (i >= numBufsToRecycle) {
                break;
            }
        }

        if (hostDesc = (Cppi_HostDesc *)QMSS_DESC_PTR(Qmss_queuePop(txCompQ))) {
            inv((Void *) hostDesc, obj->txDescSize);
            Cppi_getData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                         (UInt8 **)&msg, (UInt32 *)&msgQDataLen);

            /* Free msg back to MessageQ */
            msg = (Ptr) global_to_l2_addr((UInt32)msg);
            status = MessageQ_free(msg);
            Assert_isTrue((status >= 0), TransportQmss_A_txMsgQFreeError);

            Qmss_queuePushDesc((Qmss_QueueHnd) obj->txFreeQ, (Void *)hostDesc);
        } else {
            break;
        }
        i++;
    }

    return(i);
}

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== TransportQmss_Instance_init ========
 */
Int TransportQmss_Instance_init(TransportQmss_Object *obj,
                                const TransportQmss_Params *params,
                                Error_Block *eb)
{
    uint32_t           isAllocated;
    Cppi_DescCfg       descCfg;
    Qmss_QueueHnd      tmpQ;
    Int                i;
    Cppi_HostDesc     *hostDesc;
    Qmss_Queue         queueInfo;
    Qmss_AccCmdCfg     accCfg;
    Cppi_CpDmaInitCfg  cpdmaCfg;
    Cppi_RxFlowCfg     rxFlowCfg;
    Int16              isrEventId;
    Hwi_Params         hwiAttrs;
    UInt32             hwiKey;
    Int                retVal = TransportQmss_OK;

    if ((params->rcvQParams.qType != TransportQmss_queueRcvType_ACCUMULATOR) &&
        (params->rcvQParams.qType != TransportQmss_queueRcvType_QPEND)) {
        retVal = TransportQmss_ERROR_INVALID_QUEUE_RCV_TYPE;
        goto error_cleanup;
    }

    /* Initialize object parameters - don't memset to avoid wiping out
     * parameters set by RTSC wrapper */
    obj->devCfg                  = NULL;
    obj->txCompletionQ           = 0;
    obj->txQ                     = 0;
    obj->txFreeQ                 = 0;
    obj->rxFreeQ                 = 0;
    obj->maxMTU                  = 0;
    obj->rxMsgQHeapId            = 0;
    obj->txDescSize              = 0;
    obj->rxDescSize              = 0;
    obj->cppiHnd                 = NULL;
    obj->txCppiHnd               = NULL;
    obj->rxCppiHnd               = NULL;
    obj->rxFlowHnd               = NULL;
    obj->hwiHandle               = NULL;
    obj->queueRcvConfig          = TransportQmss_queueRcvType_INVALID;
    if (params->rcvQParams.qType == TransportQmss_queueRcvType_ACCUMULATOR) {
        obj->u.accum.rxAccQ      = 0;
        obj->u.accum.accCh       = 0;
        obj->u.accum.accListSize = 0;
        obj->u.accum.accList     = NULL;
        obj->u.accum.usePing     = 1;
        obj->u.accum.pdsp        = (-1);
    } else if (params->rcvQParams.qType != TransportQmss_queueRcvType_QPEND) {
        obj->u.qpend.rxQpendQ    = 0;
        obj->u.qpend.cicSecInt   = 0;
        obj->u.qpend.sysEvt      = 0;
    }
    obj->rxIntVectorId           = 0;
    obj->rmServiceHandle         = NULL;
    obj->flowCache.total_nodes   = 0;
    obj->flowCache.used_nodes    = 0;
    obj->flowCache.node_list     = NULL;
    obj->transNetId              = 0;

    /* Check if TransportQmss instance has already been created.  Only one
     * TransportQmss instance can exist per DSP core.  Protect from interrupt
     * from another task */
    hwiKey = Hwi_disable();
    if (TransportQmss_module->instCreated) {
        retVal = TransportQmss_ERROR_INST_ALREADY_EXISTS;
    }

    if (retVal != TransportQmss_OK) {
        Hwi_restore(hwiKey);
        goto error_cleanup;
    }

    /* Designate creation of TransportQmss instance */
    TransportQmss_module->instCreated = 1;
    Hwi_restore(hwiKey);

    if (params->deviceCfgParams) {
        /* Store the device configuration parameters */
        obj->devCfg = params->deviceCfgParams;
    } else {
        retVal = TransportQmss_ERROR_INVALID_DEVICE_CFG_PARAMS;
        goto error_cleanup;
    }

    if (params->rmServiceHandle) {
        obj->rmServiceHandle = params->rmServiceHandle;
    } else {
        retVal = TransportQmss_ERROR_RM_SERVICE_HANDLE_IS_NULL;
    }

    /* Transmit queue and descriptor initialization - MessageQ buffers will be
     * attached to the descriptors at _put() time to facilitate zero copy */
    obj->txCompletionQ = Qmss_queueOpen(Qmss_QueueType_GENERAL_PURPOSE_QUEUE,
                                        QMSS_PARAM_NOT_SPECIFIED,
                                        (UInt8 *)&isAllocated);
    if (obj->txCompletionQ < 0) {
        retVal = TransportQmss_ERROR_COULD_NOT_OPEN_TX_COMP_Q;
        goto error_cleanup;
    }

    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion             = (Qmss_MemRegion) params->txMemRegion;
    descCfg.descNum               = params->txNumDesc;
    descCfg.destQueueNum          = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.queueType             = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc              = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType              = Cppi_DescType_HOST;
    descCfg.returnQueue           = Qmss_getQueueNumber(obj->txCompletionQ);
    descCfg.epibPresent           = Cppi_EPIB_NO_EPIB_PRESENT;
    descCfg.returnPushPolicy      = Qmss_Location_TAIL;
    descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;
    descCfg.cfg.host.psLocation   = Cppi_PSLoc_PS_IN_DESC;
    obj->txFreeQ = Cppi_initDescriptor(&descCfg, &isAllocated);
    if (obj->txFreeQ < 0) {
        retVal = TransportQmss_ERROR_TX_DESCRIPTOR_INIT_FAILED;
        goto error_cleanup;
    }

    /* Receive queue and descriptor initialization - MessageQ buffers are
     * pre-allocated and attached to the host descriptors.  On packet reception,
     * QMSS's configured flow will copy the data directly into the MessageQ
     * buffer attached to the popped rx descriptor */
    obj->rxFreeQ = Qmss_queueOpen(Qmss_QueueType_GENERAL_PURPOSE_QUEUE,
                                  QMSS_PARAM_NOT_SPECIFIED,
                                  (UInt8 *)&isAllocated);
    if (obj->rxFreeQ < 0) {
        retVal = TransportQmss_ERROR_COULD_NOT_OPEN_RX_FREE_Q;
        goto error_cleanup;
    }

    memset(&descCfg, 0, sizeof(descCfg));
    descCfg.memRegion             = (Qmss_MemRegion) params->rxMemRegion;
    descCfg.descNum               = params->rxNumDesc;
    descCfg.destQueueNum          = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.queueType             = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc              = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType              = Cppi_DescType_HOST;
    descCfg.returnQueue           = Qmss_getQueueNumber(obj->rxFreeQ);
    descCfg.epibPresent           = Cppi_EPIB_NO_EPIB_PRESENT;
    descCfg.returnPushPolicy      = Qmss_Location_HEAD;
    descCfg.cfg.host.returnPolicy = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;
    descCfg.cfg.host.psLocation   = Cppi_PSLoc_PS_IN_DESC;
    tmpQ = Cppi_initDescriptor (&descCfg, &isAllocated);
    if (tmpQ < 0) {
        retVal = TransportQmss_ERROR_RX_DESCRIPTOR_INIT_FAILED;
        goto error_cleanup;
    }

    for (i = 0; i < params->rxNumDesc; i++) {
        /* Attach pre-allocated MessageQ buffers to the receive descriptors */
        if (hostDesc = (Cppi_HostDesc *) Qmss_queuePop(tmpQ)) {
            MessageQ_Msg msgQBuf;

            msgQBuf = MessageQ_alloc(params->rxMsgQHeapId, params->maxMTU);
            if (msgQBuf == NULL) {
                retVal = TransportQmss_ERROR_ALLOC_FROM_RX_MESSAGEQ_HEAP_FAILED;
                Qmss_queueEmpty(tmpQ);
                Qmss_queueClose(tmpQ);
                goto error_cleanup;
            }

            /* Convert the buffer to the global address - Only applicable for
             * buffers residing in L2 */
            msgQBuf = (MessageQ_Msg) l2_to_global_addr((UInt32)msgQBuf);

            Cppi_setData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                         (UInt8 *)msgQBuf, params->maxMTU);
            Cppi_setOriginalBufInfo(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                                    (UInt8 *)msgQBuf, params->maxMTU);

            wb((Void *)msgQBuf, msgQBuf->msgSize);
            wb((Void *)hostDesc, params->rxDescSize);

            Qmss_queuePushDescSize(obj->rxFreeQ, (Void *)hostDesc,
                                   params->rxDescSize);
        }
    }

    Qmss_queueClose(tmpQ);

    /* Save the queue receive type */
    obj->queueRcvConfig = params->rcvQParams.qType;
    /* Save receive MessageQ heap ID and the maxMTU size for use in the ISR */
    obj->rxMsgQHeapId = params->rxMsgQHeapId;
    obj->maxMTU = params->maxMTU;
    /* Save the send and receive descriptor lengths for cache coherence
     * operations */
    obj->txDescSize = params->txDescSize;
    obj->rxDescSize = params->rxDescSize;

    if (obj->queueRcvConfig == TransportQmss_queueRcvType_ACCUMULATOR) {
        UInt8 *chToEventMap = NULL;

        if (params->rcvQParams.accum.qmPdsp >= obj->devCfg->maxPdsps) {
            retVal = TransportQmss_ERROR_INVALID_QMSS_PDSP;
            goto error_cleanup;
        }
        obj->u.accum.pdsp = params->rcvQParams.accum.qmPdsp;
        
        /* Open the receive queue used by the accumulator - queue type does not
         * matter so pass in from application. */
        obj->u.accum.rxAccQ = Qmss_queueOpen(
            (Qmss_QueueType)params->rcvQParams.accum.rxAccQType,
            QMSS_PARAM_NOT_SPECIFIED, (UInt8 *) &isAllocated);
        if (obj->u.accum.rxAccQ < 0) {
            retVal = TransportQmss_ERROR_COULD_NOT_OPEN_RX_ACCUM_Q;
            goto error_cleanup;
        }

        /* List size: max entries * size of Host descriptor pointer * 2 (for
         * ping/pong) */
        obj->u.accum.accListSize = TRANS_QMSS_MAX_PAGE_ENTRIES *
                                   sizeof(Cppi_HostDesc *) * 2;
        obj->u.accum.accList = (UInt32 *)l2_to_global_addr((UInt32)Memory_alloc(
                                          0, obj->u.accum.accListSize, 16, eb));
        if (obj->u.accum.accList == NULL) {
            retVal = TransportQmss_ERROR_ALLOC_OF_ACCUM_LIST_FAILED;
            goto error_cleanup;
        }
        memset(obj->u.accum.accList, 0, obj->u.accum.accListSize);

        /* Check accumulator channel validity for the DSP core and the
         * specified PDSP */
        if (params->rcvQParams.accum.accCh > obj->devCfg->numAccumCh) {
            retVal = TransportQmss_ERROR_INVALID_ACCUMULATOR_CH;
            goto error_cleanup;
        }
        chToEventMap = obj->devCfg->pdspCfg[obj->u.accum.pdsp].intdChEvtMap;
        if ((isrEventId = chToEventMap[(DNUM * obj->devCfg->numAccumCh) +
                                    params->rcvQParams.accum.accCh]) == 0) {
            retVal = TransportQmss_ERROR_INVALID_ACCUMULATOR_CH;
            goto error_cleanup;
        }

        memset(&accCfg, 0, sizeof(accCfg));
        accCfg.channel             = params->rcvQParams.accum.accCh;
        accCfg.command             = Qmss_AccCmd_ENABLE_CHANNEL;
        accCfg.queueEnMask         = 0;
        accCfg.listAddress         = (UInt32) obj->u.accum.accList;
        accCfg.queMgrIndex         = QMSS_QUEUE_QID(obj->u.accum.rxAccQ);
        accCfg.maxPageEntries      = TRANS_QMSS_MAX_PAGE_ENTRIES;
        accCfg.timerLoadCount      = params->rcvQParams.accum.accTimerCnt;
        accCfg.interruptPacingMode = Qmss_AccPacingMode_LAST_INTERRUPT;
        accCfg.listEntrySize       = Qmss_AccEntrySize_REG_D;
        accCfg.listCountMode       = Qmss_AccCountMode_ENTRY_COUNT;
        accCfg.multiQueueMode      = Qmss_AccQueueMode_SINGLE_QUEUE;

        if (Qmss_programAccumulator((Qmss_PdspId) obj->u.accum.pdsp,
                                     &accCfg) < 0) {
            retVal = TransportQmss_ERROR_COULD_NOT_PROGRAM_ACCUM;
            goto error_cleanup;
        }
        obj->u.accum.accCh = params->rcvQParams.accum.accCh;
    } else if (obj->queueRcvConfig == TransportQmss_queueRcvType_QPEND) {
        if ((retVal = transportQmssAllocIntcQ(obj)) != TransportQmss_OK) {
            goto error_cleanup;
        }
    }

    /* Set up and open QMSS CPDMA */
    memset((void *)&cpdmaCfg, 0, sizeof(cpdmaCfg));
    cpdmaCfg.dmaNum = Cppi_CpDma_QMSS_CPDMA;
    obj->cppiHnd = (UInt32 *)Cppi_open(&cpdmaCfg);
    if (obj->cppiHnd == NULL) {
        retVal = TransportQmss_ERROR_COULD_NOT_OPEN_INFRA_CPDMA;
        goto error_cleanup;
    }

    /* Configure CPPI Tx and Rx Channels and QMSS infrastructure queue */
    if ((retVal = transportQmssAllocInfraTriplet(obj)) != TransportQmss_OK) {
        goto error_cleanup;
    }

    /* Empty the rx queue in case there are residual desciptors within */
    if (obj->queueRcvConfig == TransportQmss_queueRcvType_ACCUMULATOR) {
        Qmss_queueEmpty(obj->u.accum.rxAccQ);
    } else if (obj->queueRcvConfig == TransportQmss_queueRcvType_QPEND) {
        Qmss_queueEmpty(obj->u.qpend.rxQpendQ);
    }

    /* Configure rx CPPI flow */
    memset((void *)&rxFlowCfg, 0, sizeof(rxFlowCfg));
    rxFlowCfg.flowIdNum        = CPPI_PARAM_NOT_SPECIFIED;
    if (obj->queueRcvConfig == TransportQmss_queueRcvType_ACCUMULATOR) {
        queueInfo = Qmss_getQueueNumber(obj->u.accum.rxAccQ);
    } else if (obj->queueRcvConfig == TransportQmss_queueRcvType_QPEND) {
        queueInfo = Qmss_getQueueNumber(obj->u.qpend.rxQpendQ);
    }
    rxFlowCfg.rx_dest_qnum     = queueInfo.qNum;
    rxFlowCfg.rx_dest_qmgr     = queueInfo.qMgr;
    rxFlowCfg.rx_sop_offset    = 0;
    rxFlowCfg.rx_desc_type     = Cppi_DescType_HOST;
    queueInfo = Qmss_getQueueNumber(obj->rxFreeQ);
    rxFlowCfg.rx_fdq0_sz0_qnum = queueInfo.qNum;
    rxFlowCfg.rx_fdq0_sz0_qmgr = queueInfo.qMgr;

    /* Configure Rx flow */
    obj->rxFlowHnd = (UInt32 *)Cppi_configureRxFlow(obj->cppiHnd, &rxFlowCfg,
                                                    (uint8_t *)&isAllocated);
    if (obj->rxFlowHnd == NULL) {
        retVal = TransportQmss_ERROR_COULD_NOT_OPEN_CPPI_RX_FLOW;
        goto error_cleanup;
    }

    /* Enable CPPI channels */
    if (Cppi_channelEnable(obj->txCppiHnd) != CPPI_SOK) {
        retVal = TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_TX_CH;
        goto error_cleanup;
    }
    if (Cppi_channelEnable(obj->rxCppiHnd) != CPPI_SOK) {
        retVal = TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_RX_CH;
        goto error_cleanup;
    }

    /* Configure interrupts based on rx queue type */
    if (obj->queueRcvConfig == TransportQmss_queueRcvType_ACCUMULATOR) {
        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.maskSetting = Hwi_MaskingOption_SELF;
        hwiAttrs.arg         = (UArg) obj;
        hwiAttrs.eventId     = isrEventId;
        obj->hwiHandle = (Void *) Hwi_create(params->rxIntVectorId,
                                           (Hwi_FuncPtr)TransportQmss_Accum_isr,
                                           &hwiAttrs, eb);
        Hwi_enableInterrupt(params->rxIntVectorId);
    } else if (obj->queueRcvConfig == TransportQmss_queueRcvType_QPEND) {
        UInt                      cpIntId = 0;
        TransportQmss_hostIntMod *hostIntMods;
        UInt                      hostInt = 0;

        cpIntId     = obj->devCfg->dspIntcCfg[DNUM].cic;
        hostIntMods = obj->devCfg->hostIntModMap;

        /* Find CIC secondary interrupt based on the QPENDQ chosen */
        i = 0;
        while (hostIntMods[i].sysEvt != (-1)) {
            if (hostIntMods[i].sysEvt ==
                params->rcvQParams.qpend.systemEvent) {
                hostInt = hostIntMods[i].offset +
                          (hostIntMods[i].multiplier * DNUM);
                break;
            }
            i++;
        }
        if (hostInt == 0) {
            retVal = TransportQmss_ERROR_INVALID_SYSTEM_EVENT;
            goto error_cleanup;
        }

        CpIntc_mapSysIntToHostInt(cpIntId, obj->u.qpend.cicSecInt, hostInt);
        CpIntc_dispatchPlug(obj->u.qpend.cicSecInt,
                            (CpIntc_FuncPtr)TransportQmss_Qpend_isr, (UArg)obj,
                            1);
        CpIntc_enableHostInt(cpIntId, hostInt);
        isrEventId = CpIntc_getEventId(hostInt);
        obj->u.qpend.sysEvt = params->rcvQParams.qpend.systemEvent;

        Hwi_Params_init(&hwiAttrs);
        hwiAttrs.arg       = hostInt;
        hwiAttrs.eventId   = isrEventId;
        hwiAttrs.enableInt = TRUE;
        /* Register CpIntc_dispatch with Hwi module.  CpIntc_dispatch will
         * invoke TransportQmss_qpendIsr */
        obj->hwiHandle = (Void *)Hwi_create(params->rxIntVectorId,
                                            (Hwi_FuncPtr)CpIntc_dispatch,
                                            &hwiAttrs, eb);
        Hwi_enableInterrupt(params->rxIntVectorId);
    }
    obj->rxIntVectorId = params->rxIntVectorId;

    /* Initialize destination flow cache */
    obj->flowCache.total_nodes = FLOW_CACHE_INIT_SIZE;
    obj->flowCache.used_nodes  = 0;
    obj->flowCache.node_list   = Memory_alloc(0,
       (FLOW_CACHE_INIT_SIZE * sizeof(*(obj->flowCache.node_list))), 16, eb);
    if (obj->flowCache.node_list == NULL) {
        retVal = TransportQmss_ERROR_ALLOC_OF_FLOW_CACHE;
        goto error_cleanup;
    }
    memset(obj->flowCache.node_list, 0,
           (FLOW_CACHE_INIT_SIZE * sizeof(*(obj->flowCache.node_list))));

    if ((params->transNetworkId < 1) && (params->transNetworkId > 7)) {
        retVal = TransportQmss_ERROR_INVALID_TRANSPORT_ID;
        goto error_cleanup;
    }
    obj->transNetId = params->transNetworkId;

    /* Register the transport with MessageQ */
    if (MessageQ_registerTransportId(obj->transNetId,
        ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast2(obj)) == FALSE) {
        retVal = TransportQmss_ERROR_COULD_NOT_REGISTER_TRANSPORT;
        goto error_cleanup;
    }

    return(retVal);

error_cleanup:
    /* No need to cleanup on error here.  Specifying an error return value
     * will cause RTSC wrapper to invoke TransportQmss_Instance_finalize */
    Error_raise(eb, retVal, 0, 0);
    return(retVal);
}

/*
 *  ======== TransportQmss_Instance_finalize ========
 */
Void TransportQmss_Instance_finalize(TransportQmss_Object* obj, Int status)
{
    if ((obj->transNetId >= 1) && (obj->transNetId <= 7)) {
        MessageQ_unregisterTransportId(obj->transNetId);
    }

    transportQmssInstCleanup(obj);
    transportQmssResetModuleParams(status);
}

/*
 *  ======== TransportQmss_put ========
 *  Routine used to send packets via QMSS driver
 */
Bool TransportQmss_put(TransportQmss_Object *obj, Ptr msg)
{
    MessageQ_Msg   msgQMsg = (MessageQ_Msg) msg;
    Int32          status;
    int32_t        flowId = UNCACHED_FLOW_ID;
    uint32_t       dstQid;
    char           flowName[RM_NAME_MAX_CHARS];
    Cppi_HostDesc *hostDesc;
    Qmss_QueueHnd  txCompQ = (Qmss_QueueHnd) obj->txCompletionQ;
    Ptr            oldMsg;
    UInt32         msgQDataLen;
    Cppi_DescTag   tag;

    dstQid = ((uint32_t)(msgQMsg->dstProc << 16)) |
              ((uint32_t)(msgQMsg->dstId));

    if (obj->flowCache.used_nodes) {
        flowId = fcache_list_lookup(&(obj->flowCache), dstQid);
    }
    if (flowId == UNCACHED_FLOW_ID) {
        System_snprintf(flowName, sizeof(flowName), "%d", dstQid);
        rm_name_lookup(obj->rmServiceHandle, flowName, &flowId);
        if (flowId == RM_RESOURCE_BASE_UNSPECIFIED) {
            /* Destination processor has not bound a rx flow to the destination
             * MessageQ queue ID via RM */
            Log_warning0("TransportQmss_put : "
                         "Destination MsgQ Id not bound to rx flow\n");
            return(FALSE);
        }
        fcache_list_add(&(obj->flowCache), dstQid, flowId);
    }

    hostDesc = (Cppi_HostDesc *)Qmss_queuePop((Qmss_QueueHnd) obj->txFreeQ);
    if (!hostDesc) {
        /* Free Q out of descriptors: poll completion Q until descriptor
         * becomes available from QMSS hardware */
        do {
            hostDesc = (Cppi_HostDesc *)QMSS_DESC_PTR(Qmss_queuePop(txCompQ));
        } while (!hostDesc);
        /* Free old MessageQ msg attached to descriptor before reusing */
        inv((Void *) hostDesc, obj->txDescSize);
        Cppi_getData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                     (UInt8 **)&oldMsg, (UInt32 *)&msgQDataLen);
        oldMsg = (Ptr) global_to_l2_addr((UInt32)oldMsg);
        status = MessageQ_free(oldMsg);
        Assert_isTrue((status >= 0), TransportQmss_A_txMsgQFreeError);
    }

    /* Convert MsgQ message addr to global addr (applicable to L2), writeback,
     * then add to descriptor */
    msgQDataLen = MessageQ_getMsgSize(msg);
    msg = (Ptr) l2_to_global_addr((UInt32)msg);
    wb((Void *) msg, msgQDataLen);
    Cppi_setData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc, (UInt8 *)msg,
                 msgQDataLen);
    /* Set tag information that defines the receiving flow */
    tag.destTagLo = 0;
    tag.destTagHi = 0;
    tag.srcTagLo  = flowId;
    tag.srcTagHi  = 0;
    Cppi_setTag(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc, &tag);
    Cppi_setPacketLen(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc, msgQDataLen);
    Cppi_setOriginalBufInfo(Cppi_DescType_HOST, (Cppi_Desc*)hostDesc,
                            (UInt8 *)msg, msgQDataLen);
    wb((Void *) hostDesc, obj->txDescSize);

    Qmss_queuePushDescSize(obj->txQ, (void *)hostDesc, obj->txDescSize);

    /* Check completion queue to clean up the previous transaction descriptor */
    transportQmssTxBufRecycle(obj, 1);

    return(TRUE);
}

/* FUNCTION PURPOSE: Binds a created MessageQ queue ID
 ***********************************************************************
 * DESCRIPTION: Registers a new MessageQ queue ID, created within the same
 *              context as the TransportQmss object, with the transport's
 *              flow ID discovery mechanism.
 *
 *              Each MessageQ queue ID will be associated to the rx flow ID of
 *              the TransportQmss object created within the same system context.
 *              The association is stored in the RM NameServer.
 *              TransportQmss will query the RM NameServer on send operations
 *              for the flow ID associated with the destination flow ID.
 */
Int TransportQmss_bind(TransportQmss_Object *obj, UInt32 queueId)
{
    Int     status = 0;
    char    flowName[RM_NAME_MAX_CHARS];
    int32_t flowId = Cppi_getFlowId(obj->rxFlowHnd);

    /* Map flowId to a unique string name containing local MultiProc ID and
     * MessageQ queue index.  Mapping stored in NameServer */
    System_snprintf(flowName, sizeof(flowName), "%d", queueId);
    rm_name_set(obj->rmServiceHandle, flowName, &flowId);

    return(status);
}

/* FUNCTION PURPOSE: Unbinds a deleted MessageQ queue ID
 ***********************************************************************
 * DESCRIPTION: Unbinds a MessageQ queue ID, deleted within the same context
 *              as the TransportQmss object, by removing the associated
 *              MessageQ queue ID to CPPI rx flow ID mapping from the RM
 *              NameServer.
 */
Int TransportQmss_unbind(TransportQmss_Object *obj, UInt32 queueId)
{
    Int  status = 0;
    char flowName[RM_NAME_MAX_CHARS];

    /* Removing mapping of flowId to string stored in RM NameServer */
    System_snprintf(flowName, sizeof(flowName), "%d", queueId);
    rm_name_del(obj->rmServiceHandle, flowName);

    return(status);
}

/*
 *************************************************************************
 *                      Module functions
 *************************************************************************
 */

Int TransportQmss_recycleUsedTxBufs(TransportQmss_Handle handle)
{
    return(transportQmssTxBufRecycle((TransportQmss_Object *)handle,
                                     TRANS_QMSS_RECYCLE_ALL_TX_BUFS));
}

Bool TransportQmss_flushDstCache(TransportQmss_Handle handle, UInt32 queueId)
{
    TransportQmss_Object *obj = (TransportQmss_Object *)handle;
    Bool                  status = TRUE;
    Error_Block           eb;

    Error_init(&eb);

    if (queueId == MessageQ_INVALIDMESSAGEQ) {
        /* Delete dst flow cache */
        if (obj->flowCache.node_list) {
            Memory_free(0, (UInt32 *)obj->flowCache.node_list,
                        (obj->flowCache.total_nodes *
                         sizeof(*(obj->flowCache.node_list))));
        }

        /* Re-init destination flow cache */
        obj->flowCache.total_nodes = FLOW_CACHE_INIT_SIZE;
        obj->flowCache.used_nodes  = 0;
        obj->flowCache.node_list   = Memory_alloc(0,
           (FLOW_CACHE_INIT_SIZE * sizeof(*(obj->flowCache.node_list))),
           16, &eb);
        if (obj->flowCache.node_list == NULL) {
            status = FALSE;
        }
        memset(obj->flowCache.node_list, 0,
               (FLOW_CACHE_INIT_SIZE * sizeof(*(obj->flowCache.node_list))));
    } else {
        if (fcache_list_lookup(&(obj->flowCache), queueId) ==
            UNCACHED_FLOW_ID) {
            status = FALSE;
        } else {
            fcache_list_del(&(obj->flowCache), queueId);
        }
    }

    return(status);
}

/*
 *************************************************************************
 *                       Internal functions
 *************************************************************************
 */

/*
 *  ======== TransportQmss_Accum_isr ========
 */
Void TransportQmss_Accum_isr(UArg arg)
{
    TransportQmss_Object *obj = (TransportQmss_Object *)arg;
    UInt32               *accumList;
    UInt32                descCount;
    UInt32                i;
    Cppi_HostDesc        *hostDesc;
    MessageQ_Msg          rxMsg;
    UInt32                rxNumBytes;
    UInt32                queueId;

    if (obj->u.accum.usePing) {
        accumList = (UInt32 *)&obj->u.accum.accList[0];
    } else {
        accumList = (UInt32 *)&obj->u.accum.accList[TRANS_QMSS_MAX_PAGE_ENTRIES];
    }

    /* Get number of received descriptors */
    descCount = accumList[0];
    if (descCount == 0) {
        goto ack_int;
    }

    for (i = 1; i < (descCount + 1); i++) {
        /* Invalidate descriptor then extract and invalidate MessageQ msg */
        hostDesc = (Cppi_HostDesc *)QMSS_DESC_PTR(accumList[i]);
        if (hostDesc) {
            inv((Void *) hostDesc, obj->rxDescSize);
            Cppi_getData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                         (UInt8 **)&rxMsg, (UInt32 *)&rxNumBytes);
            inv((Void *) rxMsg, rxNumBytes);

            /* Reset heapId to rxMsgQHeapId.  This heap is overwritten when
             * message is received over DMA */
            rxMsg->heapId = obj->rxMsgQHeapId;
            /* Reception overwrote actual size of preallocated buffer */
            rxMsg->msgSize = obj->maxMTU;

            /* Route to destination MessageQ */
            queueId = MessageQ_getDstQueue(rxMsg);
            MessageQ_put(queueId, rxMsg);

            /* Get new MessageQ buffer for descriptor then push back to
             * free Q */
            transportQmssNewRxBuf(obj, hostDesc);
        } else {
            Log_warning1("TransportQmss_Accum_ist : "
                         "NULL descriptor at index %d in Accumulator list\n",
                         i);
        }
    }

    if (obj->u.accum.usePing) {
        obj->u.accum.usePing = 0;
    } else {
        obj->u.accum.usePing = 1;
    }

ack_int:
    Qmss_ackInterruptByIntd(obj->devCfg->pdspCfg[obj->u.accum.pdsp].intd,
                            obj->u.accum.accCh, 1);
    Qmss_setEoiVectorByIntd(obj->devCfg->pdspCfg[obj->u.accum.pdsp].intd,
                            Qmss_IntdInterruptType_HIGH, obj->u.accum.accCh);
}

/*
 *  ======== TransportQmss_Qpend_isr ========
 */
Void TransportQmss_Qpend_isr(UArg arg)
{
    TransportQmss_Object *obj = (TransportQmss_Object *)arg;
    UInt                  cpIntId = obj->devCfg->dspIntcCfg[DNUM].cic;
    Cppi_HostDesc        *hostDesc;
    MessageQ_Msg          rxMsg;
    UInt32                rxNumBytes;
    UInt32                queueId;

    /* Disable CIC secondary interrupt while in ISR */
    CpIntc_disableSysInt(cpIntId, obj->u.qpend.cicSecInt);

    while (hostDesc = (Cppi_HostDesc *)QMSS_DESC_PTR(Qmss_queuePop(
                                                     obj->u.qpend.rxQpendQ))) {
        /* Invalidate descriptor then extract and invalidate MessageQ msg */
        inv((Void *) hostDesc, obj->rxDescSize);
        Cppi_getData(Cppi_DescType_HOST, (Cppi_Desc *)hostDesc,
                     (UInt8 **)&rxMsg, (UInt32 *)&rxNumBytes);
        inv((Void *) rxMsg, rxNumBytes);

        /* Reset heapId to rxMsgQHeapId.  This heap is overwritten when message
         * is received over DMA */
        rxMsg->heapId = obj->rxMsgQHeapId;
        /* Reception overwrote actual size of preallocated buffer */
        rxMsg->msgSize = obj->maxMTU;

        /* Route to destination MessageQ */
        queueId = MessageQ_getDstQueue(rxMsg);
        MessageQ_put(queueId, rxMsg);

        /* Get new MessageQ buffer for descriptor then push back to free Q */
        transportQmssNewRxBuf(obj, hostDesc);
    }

    /* Clear and reenable the CIC secondary interrupt */
    CpIntc_clearSysInt(cpIntId, obj->u.qpend.cicSecInt);
    CpIntc_enableSysInt(cpIntId, obj->u.qpend.cicSecInt);
}
