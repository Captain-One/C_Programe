/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-E10
 */

/*
 * ======== GENERATED SECTIONS ========
 *
 *     PROLOGUE
 *     INCLUDES
 *
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     PER-INSTANCE TYPES
 *     VIRTUAL FUNCTIONS
 *     FUNCTION DECLARATIONS
 *     CONVERTORS
 *     SYSTEM FUNCTIONS
 *
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_transport_ipc_c66_qmss_TransportQmss__include
#define ti_transport_ipc_c66_qmss_TransportQmss__include

#ifndef __nested__
#define __nested__
#define ti_transport_ipc_c66_qmss_TransportQmss__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_transport_ipc_c66_qmss_TransportQmss___VERS 200


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/IInstance.h>
#include <ti/transport/ipc/c66/qmss/package/package.defs.h>

#include <xdc/runtime/Assert.h>
#include <ti/sdo/utils/MultiProc.h>
#include <ti/sdo/ipc/MessageQ.h>
#include <ti/sdo/ipc/interfaces/INetworkTransport.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* OK */
#define ti_transport_ipc_c66_qmss_TransportQmss_OK (0)

/* ERROR_COULD_NOT_OPEN_TX_COMP_Q */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_TX_COMP_Q (64)

/* ERROR_TX_DESCRIPTOR_INIT_FAILED */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_TX_DESCRIPTOR_INIT_FAILED (65)

/* ERROR_COULD_NOT_OPEN_RX_FREE_Q */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_RX_FREE_Q (66)

/* ERROR_COULD_NOT_OPEN_RX_ACCUM_Q */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_RX_ACCUM_Q (67)

/* ERROR_RX_DESCRIPTOR_INIT_FAILED */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_RX_DESCRIPTOR_INIT_FAILED (68)

/* ERROR_ALLOC_FROM_RX_MESSAGEQ_HEAP_FAILED */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_ALLOC_FROM_RX_MESSAGEQ_HEAP_FAILED (69)

/* ERROR_ALLOC_OF_ACCUM_LIST_FAILED */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_ALLOC_OF_ACCUM_LIST_FAILED (70)

/* ERROR_INVALID_ACCUMULATOR_CH */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_ACCUMULATOR_CH (71)

/* ERROR_INST_ALREADY_EXISTS */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INST_ALREADY_EXISTS (72)

/* ERROR_INVALID_QUEUE_RCV_TYPE */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_QUEUE_RCV_TYPE (73)

/* ERROR_INVALID_DEVICE_CFG_PARAMS */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_DEVICE_CFG_PARAMS (74)

/* ERROR_INVALID_TRANSPORT_ID */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_TRANSPORT_ID (75)

/* ERROR_COULD_NOT_REGISTER_TRANSPORT */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_REGISTER_TRANSPORT (76)

/* ERROR_COULD_NOT_OPEN_RX_QPEND_Q */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_RX_QPEND_Q (77)

/* ERROR_COULD_NOT_FIND_VALID_RX_QPEND_Q */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_FIND_VALID_RX_QPEND_Q (78)

/* ERROR_INVALID_QMSS_PDSP */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_QMSS_PDSP (79)

/* ERROR_COULD_NOT_PROGRAM_ACCUM */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_PROGRAM_ACCUM (80)

/* ERROR_COULD_NOT_OPEN_INFRA_CPDMA */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_INFRA_CPDMA (81)

/* ERROR_COULD_NOT_OPEN_CPPI_RX_FLOW */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_CPPI_RX_FLOW (82)

/* ERROR_COULD_NOT_ENABLE_CPPI_TX_CH */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_TX_CH (83)

/* ERROR_COULD_NOT_ENABLE_CPPI_RX_CH */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_RX_CH (84)

/* ERROR_INVALID_SYSTEM_EVENT */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_SYSTEM_EVENT (85)

/* ERROR_RM_SERVICE_HANDLE_IS_NULL */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_RM_SERVICE_HANDLE_IS_NULL (86)

/* ERROR_ALLOC_OF_FLOW_CACHE */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_ALLOC_OF_FLOW_CACHE (87)

/* ERROR_COULD_NOT_FIND_INFRA_TRIPLET */
#define ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_FIND_INFRA_TRIPLET (88)

/* pdspCfg */
struct ti_transport_ipc_c66_qmss_TransportQmss_pdspCfg {
    xdc_UInt32 intd;
    xdc_UInt8 *intdChEvtMap;
};

/* intcQInfo */
struct ti_transport_ipc_c66_qmss_TransportQmss_intcQInfo {
    xdc_Int32 baseQ;
    xdc_Int32 baseSecInt;
    xdc_Int32 len;
};

/* dspIntcCfg */
struct ti_transport_ipc_c66_qmss_TransportQmss_dspIntcCfg {
    xdc_UInt32 cic;
    ti_transport_ipc_c66_qmss_TransportQmss_intcQInfo *intcInfo;
};

/* hostIntMod */
struct ti_transport_ipc_c66_qmss_TransportQmss_hostIntMod {
    xdc_Int32 sysEvt;
    xdc_Int32 offset;
    xdc_Int32 multiplier;
};

/* DeviceConfigParams */
struct ti_transport_ipc_c66_qmss_TransportQmss_DeviceConfigParams {
    xdc_UInt16 maxPdsps;
    xdc_Int32 qmssInfraQBase;
    xdc_Int32 qmssInfraQMax;
    xdc_UInt16 numAccumCh;
    ti_transport_ipc_c66_qmss_TransportQmss_pdspCfg *pdspCfg;
    ti_transport_ipc_c66_qmss_TransportQmss_dspIntcCfg *dspIntcCfg;
    ti_transport_ipc_c66_qmss_TransportQmss_hostIntMod *hostIntModMap;
};

/* FlowCacheNode */
struct ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheNode {
    xdc_UInt32 queue_id;
    xdc_UInt16 flow;
};

/* FlowCacheList */
struct ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheList {
    xdc_UInt32 total_nodes;
    xdc_UInt32 used_nodes;
    ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheNode *node_list;
};

/* QueueRcvType */
enum ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType {
    ti_transport_ipc_c66_qmss_TransportQmss_queueRcvType_INVALID,
    ti_transport_ipc_c66_qmss_TransportQmss_queueRcvType_ACCUMULATOR,
    ti_transport_ipc_c66_qmss_TransportQmss_queueRcvType_QPEND
};
typedef enum ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType;

/* AccumRcvParams */
struct ti_transport_ipc_c66_qmss_TransportQmss_AccumRcvParams {
    xdc_UInt32 rxAccQType;
    xdc_UInt32 qmPdsp;
    xdc_UInt8 accCh;
    xdc_UInt32 accTimerCnt;
};

/* QpendRcvParams */
struct ti_transport_ipc_c66_qmss_TransportQmss_QpendRcvParams {
    xdc_UInt systemEvent;
};

/* QueueRcvParams */
struct ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvParams {
    ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType qType;
    ti_transport_ipc_c66_qmss_TransportQmss_AccumRcvParams accum;
    ti_transport_ipc_c66_qmss_TransportQmss_QpendRcvParams qpend;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* Accum_State */
struct ti_transport_ipc_c66_qmss_TransportQmss_Accum_State {
    xdc_Int32 rxAccQ;
    xdc_UInt8 accCh;
    xdc_UInt32 accListSize;
    xdc_UInt32 *accList;
    xdc_Int usePing;
    xdc_Int32 pdsp;
};

/* Qpend_State */
struct ti_transport_ipc_c66_qmss_TransportQmss_Qpend_State {
    xdc_Int32 rxQpendQ;
    xdc_UInt cicSecInt;
    xdc_UInt sysEvt;
};

/* __struct__1 */
union ti_transport_ipc_c66_qmss_TransportQmss___struct__1 {
    ti_transport_ipc_c66_qmss_TransportQmss_Accum_State accum;
    ti_transport_ipc_c66_qmss_TransportQmss_Qpend_State qpend;
};


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled (ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded (ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask (ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj (ti_transport_ipc_c66_qmss_TransportQmss_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms (ti_transport_ipc_c66_qmss_TransportQmss_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__id;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__id ti_transport_ipc_c66_qmss_TransportQmss_Module__id__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__id__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__id__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__id*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__id__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__id (ti_transport_ipc_c66_qmss_TransportQmss_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0 ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0 (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1 ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1 (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2 ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2 (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn2__C)
#endif

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4 ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4 (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn4__C)
#endif

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8 ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8 (ti_transport_ipc_c66_qmss_TransportQmss_Module__loggerFxn8__C)
#endif

/* Object__count */
typedef xdc_Int CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__count;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__count ti_transport_ipc_c66_qmss_TransportQmss_Object__count__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Object__count__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__count__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__count*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Object__count__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__count (ti_transport_ipc_c66_qmss_TransportQmss_Object__count__C)
#endif

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__heap;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__heap ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__heap*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__heap (ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__C)
#endif

/* Object__sizeof */
typedef xdc_SizeT CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof (ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof__C)
#endif

/* Object__table */
typedef xdc_Ptr CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__table;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__table ti_transport_ipc_c66_qmss_TransportQmss_Object__table__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_Object__table__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__table__C (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_Object__table*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Object__table__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Object__table (ti_transport_ipc_c66_qmss_TransportQmss_Object__table__C)
#endif

/* A_txMsgQFreeError */
typedef xdc_runtime_Assert_Id CT__ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError (ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError__C)
#endif

/* A_newRxBufNull */
typedef xdc_runtime_Assert_Id CT__ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull;
__extern __FAR__ const CT__ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull__C;
#ifdef ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull__CR
#define ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull (*((CT__ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull*)(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull__C_offset)))
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull (ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull__C)
#endif


/*
 * ======== PER-INSTANCE TYPES ========
 */

/* Params */
struct ti_transport_ipc_c66_qmss_TransportQmss_Params {
    size_t __size;
    const void *__self;
    void *__fxns;
    xdc_runtime_IInstance_Params *instance;
    ti_transport_ipc_c66_qmss_TransportQmss_DeviceConfigParams *deviceCfgParams;
    xdc_Int txMemRegion;
    xdc_UInt32 txNumDesc;
    xdc_UInt32 txDescSize;
    xdc_Int rxMemRegion;
    xdc_UInt32 rxNumDesc;
    xdc_UInt32 rxDescSize;
    xdc_UInt16 rxMsgQHeapId;
    xdc_UInt32 maxMTU;
    ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvParams rcvQParams;
    xdc_Void *rmServiceHandle;
    xdc_UInt rxIntVectorId;
    xdc_UInt transNetworkId;
    xdc_runtime_IInstance_Params __iprms;
};

/* Struct */
struct ti_transport_ipc_c66_qmss_TransportQmss_Struct {
    const ti_transport_ipc_c66_qmss_TransportQmss_Fxns__ *__fxns;
    ti_transport_ipc_c66_qmss_TransportQmss_DeviceConfigParams *f0;
    xdc_Int32 f1;
    xdc_Int32 f2;
    xdc_Int32 f3;
    xdc_Int32 f4;
    xdc_UInt32 f5;
    xdc_UInt16 f6;
    xdc_UInt32 f7;
    xdc_UInt32 f8;
    xdc_UInt32 *f9;
    xdc_UInt32 *f10;
    xdc_UInt32 *f11;
    xdc_UInt32 *f12;
    xdc_Void *f13;
    ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType f14;
    ti_transport_ipc_c66_qmss_TransportQmss___struct__1 f15;
    xdc_UInt32 f16;
    xdc_Void *f17;
    ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheList f18;
    xdc_UInt16 f19;
    xdc_runtime_Types_CordAddr __name;
};


/*
 * ======== VIRTUAL FUNCTIONS ========
 */

/* Fxns__ */
struct ti_transport_ipc_c66_qmss_TransportQmss_Fxns__ {
    const xdc_runtime_Types_Base* __base;
    const xdc_runtime_Types_SysFxns2* __sysp;
    xdc_Int (*bind)(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst, xdc_UInt32 queueId);
    xdc_Int (*unbind)(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst, xdc_UInt32 queueId);
    xdc_Bool (*put)(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst, xdc_Ptr msg);
    xdc_runtime_Types_SysFxns2 __sfxns;
};
#ifndef ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__CR

/* Module__FXNS__C */
__extern const ti_transport_ipc_c66_qmss_TransportQmss_Fxns__ ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C;
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C (*(xdcRomConstPtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C_offset))
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_transport_ipc_c66_qmss_TransportQmss_Module_startup( state ) (-1)

/* Instance_init__E */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Instance_init__E, "ti_transport_ipc_c66_qmss_TransportQmss_Instance_init")
__extern xdc_Int ti_transport_ipc_c66_qmss_TransportQmss_Instance_init__E(ti_transport_ipc_c66_qmss_TransportQmss_Object *obj, const ti_transport_ipc_c66_qmss_TransportQmss_Params *prms, xdc_runtime_Error_Block *eb);

/* Instance_finalize__E */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Instance_finalize__E, "ti_transport_ipc_c66_qmss_TransportQmss_Instance_finalize")
__extern void ti_transport_ipc_c66_qmss_TransportQmss_Instance_finalize__E(ti_transport_ipc_c66_qmss_TransportQmss_Object *obj, int ec);

/* create */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_create, "ti_transport_ipc_c66_qmss_TransportQmss_create")
__extern ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_create( const ti_transport_ipc_c66_qmss_TransportQmss_Params *prms, xdc_runtime_Error_Block *eb);

/* construct */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_construct, "ti_transport_ipc_c66_qmss_TransportQmss_construct")
__extern void ti_transport_ipc_c66_qmss_TransportQmss_construct(ti_transport_ipc_c66_qmss_TransportQmss_Struct *obj, const ti_transport_ipc_c66_qmss_TransportQmss_Params *prms, xdc_runtime_Error_Block *eb);

/* delete */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_delete, "ti_transport_ipc_c66_qmss_TransportQmss_delete")
__extern void ti_transport_ipc_c66_qmss_TransportQmss_delete(ti_transport_ipc_c66_qmss_TransportQmss_Handle *instp);

/* destruct */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_destruct, "ti_transport_ipc_c66_qmss_TransportQmss_destruct")
__extern void ti_transport_ipc_c66_qmss_TransportQmss_destruct(ti_transport_ipc_c66_qmss_TransportQmss_Struct *obj);

/* Handle__label__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Handle__label__S, "ti_transport_ipc_c66_qmss_TransportQmss_Handle__label__S")
__extern xdc_runtime_Types_Label *ti_transport_ipc_c66_qmss_TransportQmss_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label *lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Module__startupDone__S, "ti_transport_ipc_c66_qmss_TransportQmss_Module__startupDone__S")
__extern xdc_Bool ti_transport_ipc_c66_qmss_TransportQmss_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Object__create__S, "ti_transport_ipc_c66_qmss_TransportQmss_Object__create__S")
__extern xdc_Ptr ti_transport_ipc_c66_qmss_TransportQmss_Object__create__S( xdc_CPtr aa, const xdc_UChar *pa, xdc_SizeT psz, xdc_runtime_Error_Block *eb );

/* Object__delete__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Object__delete__S, "ti_transport_ipc_c66_qmss_TransportQmss_Object__delete__S")
__extern xdc_Void ti_transport_ipc_c66_qmss_TransportQmss_Object__delete__S( xdc_Ptr instp );

/* Object__get__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Object__get__S, "ti_transport_ipc_c66_qmss_TransportQmss_Object__get__S")
__extern xdc_Ptr ti_transport_ipc_c66_qmss_TransportQmss_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Object__first__S, "ti_transport_ipc_c66_qmss_TransportQmss_Object__first__S")
__extern xdc_Ptr ti_transport_ipc_c66_qmss_TransportQmss_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Object__next__S, "ti_transport_ipc_c66_qmss_TransportQmss_Object__next__S")
__extern xdc_Ptr ti_transport_ipc_c66_qmss_TransportQmss_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Params__init__S, "ti_transport_ipc_c66_qmss_TransportQmss_Params__init__S")
__extern xdc_Void ti_transport_ipc_c66_qmss_TransportQmss_Params__init__S( xdc_Ptr dst, const xdc_Void *src, xdc_SizeT psz, xdc_SizeT isz );

/* bind__E */
#define ti_transport_ipc_c66_qmss_TransportQmss_bind ti_transport_ipc_c66_qmss_TransportQmss_bind__E
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_bind__E, "ti_transport_ipc_c66_qmss_TransportQmss_bind")
__extern xdc_Int ti_transport_ipc_c66_qmss_TransportQmss_bind__E( ti_transport_ipc_c66_qmss_TransportQmss_Handle __inst, xdc_UInt32 queueId );

/* unbind__E */
#define ti_transport_ipc_c66_qmss_TransportQmss_unbind ti_transport_ipc_c66_qmss_TransportQmss_unbind__E
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_unbind__E, "ti_transport_ipc_c66_qmss_TransportQmss_unbind")
__extern xdc_Int ti_transport_ipc_c66_qmss_TransportQmss_unbind__E( ti_transport_ipc_c66_qmss_TransportQmss_Handle __inst, xdc_UInt32 queueId );

/* put__E */
#define ti_transport_ipc_c66_qmss_TransportQmss_put ti_transport_ipc_c66_qmss_TransportQmss_put__E
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_put__E, "ti_transport_ipc_c66_qmss_TransportQmss_put")
__extern xdc_Bool ti_transport_ipc_c66_qmss_TransportQmss_put__E( ti_transport_ipc_c66_qmss_TransportQmss_Handle __inst, xdc_Ptr msg );

/* recycleUsedTxBufs__E */
#define ti_transport_ipc_c66_qmss_TransportQmss_recycleUsedTxBufs ti_transport_ipc_c66_qmss_TransportQmss_recycleUsedTxBufs__E
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_recycleUsedTxBufs__E, "ti_transport_ipc_c66_qmss_TransportQmss_recycleUsedTxBufs")
__extern xdc_Int ti_transport_ipc_c66_qmss_TransportQmss_recycleUsedTxBufs__E( ti_transport_ipc_c66_qmss_TransportQmss_Handle __inst );

/* flushDstCache__E */
#define ti_transport_ipc_c66_qmss_TransportQmss_flushDstCache ti_transport_ipc_c66_qmss_TransportQmss_flushDstCache__E
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_flushDstCache__E, "ti_transport_ipc_c66_qmss_TransportQmss_flushDstCache")
__extern xdc_Bool ti_transport_ipc_c66_qmss_TransportQmss_flushDstCache__E( ti_transport_ipc_c66_qmss_TransportQmss_Handle __inst, xdc_UInt32 queueId );

/* Accum_isr__I */
#define ti_transport_ipc_c66_qmss_TransportQmss_Accum_isr ti_transport_ipc_c66_qmss_TransportQmss_Accum_isr__I
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Accum_isr__I, "ti_transport_ipc_c66_qmss_TransportQmss_Accum_isr")
__extern xdc_Void ti_transport_ipc_c66_qmss_TransportQmss_Accum_isr__I( xdc_UArg arg );

/* Qpend_isr__I */
#define ti_transport_ipc_c66_qmss_TransportQmss_Qpend_isr ti_transport_ipc_c66_qmss_TransportQmss_Qpend_isr__I
xdc__CODESECT(ti_transport_ipc_c66_qmss_TransportQmss_Qpend_isr__I, "ti_transport_ipc_c66_qmss_TransportQmss_Qpend_isr")
__extern xdc_Void ti_transport_ipc_c66_qmss_TransportQmss_Qpend_isr__I( xdc_UArg arg );


/*
 * ======== CONVERTORS ========
 */

/* Module_upCast */
static inline ti_sdo_ipc_interfaces_INetworkTransport_Module ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast(void);
static inline ti_sdo_ipc_interfaces_INetworkTransport_Module ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast(void)
{
    return (ti_sdo_ipc_interfaces_INetworkTransport_Module)&ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_INetworkTransport */
#define ti_transport_ipc_c66_qmss_TransportQmss_Module_to_ti_sdo_ipc_interfaces_INetworkTransport ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast

/* Handle_upCast */
static inline ti_sdo_ipc_interfaces_INetworkTransport_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast(ti_transport_ipc_c66_qmss_TransportQmss_Handle i);
static inline ti_sdo_ipc_interfaces_INetworkTransport_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast(ti_transport_ipc_c66_qmss_TransportQmss_Handle i)
{
    return (ti_sdo_ipc_interfaces_INetworkTransport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_INetworkTransport */
#define ti_transport_ipc_c66_qmss_TransportQmss_Handle_to_ti_sdo_ipc_interfaces_INetworkTransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast

/* Handle_downCast */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast(ti_sdo_ipc_interfaces_INetworkTransport_Handle i);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast(ti_sdo_ipc_interfaces_INetworkTransport_Handle i)
{
    ti_sdo_ipc_interfaces_INetworkTransport_Handle i2 = (ti_sdo_ipc_interfaces_INetworkTransport_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C) ? (ti_transport_ipc_c66_qmss_TransportQmss_Handle)i : (ti_transport_ipc_c66_qmss_TransportQmss_Handle)NULL;
}

/* Handle_from_ti_sdo_ipc_interfaces_INetworkTransport */
#define ti_transport_ipc_c66_qmss_TransportQmss_Handle_from_ti_sdo_ipc_interfaces_INetworkTransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast

/* Module_upCast2 */
static inline ti_sdo_ipc_interfaces_ITransport_Module ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast2(void);
static inline ti_sdo_ipc_interfaces_ITransport_Module ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast2(void)
{
    return (ti_sdo_ipc_interfaces_ITransport_Module)&ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C;
}

/* Module_to_ti_sdo_ipc_interfaces_ITransport */
#define ti_transport_ipc_c66_qmss_TransportQmss_Module_to_ti_sdo_ipc_interfaces_ITransport ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast2

/* Handle_upCast2 */
static inline ti_sdo_ipc_interfaces_ITransport_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast2(ti_transport_ipc_c66_qmss_TransportQmss_Handle i);
static inline ti_sdo_ipc_interfaces_ITransport_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast2(ti_transport_ipc_c66_qmss_TransportQmss_Handle i)
{
    return (ti_sdo_ipc_interfaces_ITransport_Handle)i;
}

/* Handle_to_ti_sdo_ipc_interfaces_ITransport */
#define ti_transport_ipc_c66_qmss_TransportQmss_Handle_to_ti_sdo_ipc_interfaces_ITransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast2

/* Handle_downCast2 */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast2(ti_sdo_ipc_interfaces_ITransport_Handle i);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast2(ti_sdo_ipc_interfaces_ITransport_Handle i)
{
    ti_sdo_ipc_interfaces_ITransport_Handle i2 = (ti_sdo_ipc_interfaces_ITransport_Handle)i;
    return ((const void*)i2->__fxns == (const void*)&ti_transport_ipc_c66_qmss_TransportQmss_Module__FXNS__C) ? (ti_transport_ipc_c66_qmss_TransportQmss_Handle)i : (ti_transport_ipc_c66_qmss_TransportQmss_Handle)NULL;
}

/* Handle_from_ti_sdo_ipc_interfaces_ITransport */
#define ti_transport_ipc_c66_qmss_TransportQmss_Handle_from_ti_sdo_ipc_interfaces_ITransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast2


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_transport_ipc_c66_qmss_TransportQmss_Module_startupDone() ti_transport_ipc_c66_qmss_TransportQmss_Module__startupDone__S()

/* Object_heap */
#define ti_transport_ipc_c66_qmss_TransportQmss_Object_heap() ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__C

/* Module_heap */
#define ti_transport_ipc_c66_qmss_TransportQmss_Module_heap() ti_transport_ipc_c66_qmss_TransportQmss_Object__heap__C

/* Module_id */
static inline CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__id ti_transport_ipc_c66_qmss_TransportQmss_Module_id(void);
static inline CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__id ti_transport_ipc_c66_qmss_TransportQmss_Module_id( void ) 
{
    return ti_transport_ipc_c66_qmss_TransportQmss_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_transport_ipc_c66_qmss_TransportQmss_Module_hasMask(void);
static inline xdc_Bool ti_transport_ipc_c66_qmss_TransportQmss_Module_hasMask(void)
{
    return (xdc_Bool)(ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C != (CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask)NULL);
}

/* Module_getMask */
static inline xdc_Bits16 ti_transport_ipc_c66_qmss_TransportQmss_Module_getMask(void);
static inline xdc_Bits16 ti_transport_ipc_c66_qmss_TransportQmss_Module_getMask(void)
{
    return (ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C != (CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask)NULL) ? *ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C : (xdc_Bits16)0;
}

/* Module_setMask */
static inline xdc_Void ti_transport_ipc_c66_qmss_TransportQmss_Module_setMask(xdc_Bits16 mask);
static inline xdc_Void ti_transport_ipc_c66_qmss_TransportQmss_Module_setMask(xdc_Bits16 mask)
{
    if (ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C != (CT__ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask)NULL) {
        *ti_transport_ipc_c66_qmss_TransportQmss_Module__diagsMask__C = mask;
    }
}

/* Params_init */
static inline void ti_transport_ipc_c66_qmss_TransportQmss_Params_init(ti_transport_ipc_c66_qmss_TransportQmss_Params *prms);
static inline void ti_transport_ipc_c66_qmss_TransportQmss_Params_init( ti_transport_ipc_c66_qmss_TransportQmss_Params *prms ) 
{
    if (prms != NULL) {
        ti_transport_ipc_c66_qmss_TransportQmss_Params__init__S(prms, NULL, sizeof(ti_transport_ipc_c66_qmss_TransportQmss_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Params_copy */
static inline void ti_transport_ipc_c66_qmss_TransportQmss_Params_copy(ti_transport_ipc_c66_qmss_TransportQmss_Params *dst, const ti_transport_ipc_c66_qmss_TransportQmss_Params *src);
static inline void ti_transport_ipc_c66_qmss_TransportQmss_Params_copy(ti_transport_ipc_c66_qmss_TransportQmss_Params *dst, const ti_transport_ipc_c66_qmss_TransportQmss_Params *src) 
{
    if (dst != NULL) {
        ti_transport_ipc_c66_qmss_TransportQmss_Params__init__S(dst, (const void *)src, sizeof(ti_transport_ipc_c66_qmss_TransportQmss_Params), sizeof(xdc_runtime_IInstance_Params));
    }
}

/* Object_count */
#define ti_transport_ipc_c66_qmss_TransportQmss_Object_count() ti_transport_ipc_c66_qmss_TransportQmss_Object__count__C

/* Object_sizeof */
#define ti_transport_ipc_c66_qmss_TransportQmss_Object_sizeof() ti_transport_ipc_c66_qmss_TransportQmss_Object__sizeof__C

/* Object_get */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Object_get(ti_transport_ipc_c66_qmss_TransportQmss_Instance_State *oarr, int i);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Object_get(ti_transport_ipc_c66_qmss_TransportQmss_Instance_State *oarr, int i) 
{
    return (ti_transport_ipc_c66_qmss_TransportQmss_Handle)ti_transport_ipc_c66_qmss_TransportQmss_Object__get__S(oarr, i);
}

/* Object_first */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Object_first(void);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Object_first(void)
{
    return (ti_transport_ipc_c66_qmss_TransportQmss_Handle)ti_transport_ipc_c66_qmss_TransportQmss_Object__first__S();
}

/* Object_next */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Object_next(ti_transport_ipc_c66_qmss_TransportQmss_Object *obj);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Object_next(ti_transport_ipc_c66_qmss_TransportQmss_Object *obj)
{
    return (ti_transport_ipc_c66_qmss_TransportQmss_Handle)ti_transport_ipc_c66_qmss_TransportQmss_Object__next__S(obj);
}

/* Handle_label */
static inline xdc_runtime_Types_Label *ti_transport_ipc_c66_qmss_TransportQmss_Handle_label(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst, xdc_runtime_Types_Label *lab);
static inline xdc_runtime_Types_Label *ti_transport_ipc_c66_qmss_TransportQmss_Handle_label(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst, xdc_runtime_Types_Label *lab)
{
    return ti_transport_ipc_c66_qmss_TransportQmss_Handle__label__S(inst, lab);
}

/* Handle_name */
static inline xdc_String ti_transport_ipc_c66_qmss_TransportQmss_Handle_name(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst);
static inline xdc_String ti_transport_ipc_c66_qmss_TransportQmss_Handle_name(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst)
{
    xdc_runtime_Types_Label lab;
    return ti_transport_ipc_c66_qmss_TransportQmss_Handle__label__S(inst, &lab)->iname;
}

/* handle */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_handle(ti_transport_ipc_c66_qmss_TransportQmss_Struct *str);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_handle(ti_transport_ipc_c66_qmss_TransportQmss_Struct *str)
{
    return (ti_transport_ipc_c66_qmss_TransportQmss_Handle)str;
}

/* struct */
static inline ti_transport_ipc_c66_qmss_TransportQmss_Struct *ti_transport_ipc_c66_qmss_TransportQmss_struct(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst);
static inline ti_transport_ipc_c66_qmss_TransportQmss_Struct *ti_transport_ipc_c66_qmss_TransportQmss_struct(ti_transport_ipc_c66_qmss_TransportQmss_Handle inst)
{
    return (ti_transport_ipc_c66_qmss_TransportQmss_Struct*)inst;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_transport_ipc_c66_qmss_TransportQmss__top__
#undef __nested__
#endif

#endif /* ti_transport_ipc_c66_qmss_TransportQmss__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_transport_ipc_c66_qmss_TransportQmss__internalaccess))

#ifndef ti_transport_ipc_c66_qmss_TransportQmss__include_state
#define ti_transport_ipc_c66_qmss_TransportQmss__include_state

/* Module_State */
struct ti_transport_ipc_c66_qmss_TransportQmss_Module_State {
    xdc_UInt instCreated;
};

/* Module__state__V */
#ifndef ti_transport_ipc_c66_qmss_TransportQmss_Module__state__VR
extern struct ti_transport_ipc_c66_qmss_TransportQmss_Module_State__ ti_transport_ipc_c66_qmss_TransportQmss_Module__state__V;
#else
#define ti_transport_ipc_c66_qmss_TransportQmss_Module__state__V (*((struct ti_transport_ipc_c66_qmss_TransportQmss_Module_State__*)(xdcRomStatePtr + ti_transport_ipc_c66_qmss_TransportQmss_Module__state__V_offset)))
#endif

/* Object */
struct ti_transport_ipc_c66_qmss_TransportQmss_Object {
    const ti_transport_ipc_c66_qmss_TransportQmss_Fxns__ *__fxns;
    ti_transport_ipc_c66_qmss_TransportQmss_DeviceConfigParams *devCfg;
    xdc_Int32 txCompletionQ;
    xdc_Int32 txQ;
    xdc_Int32 txFreeQ;
    xdc_Int32 rxFreeQ;
    xdc_UInt32 maxMTU;
    xdc_UInt16 rxMsgQHeapId;
    xdc_UInt32 txDescSize;
    xdc_UInt32 rxDescSize;
    xdc_UInt32 *cppiHnd;
    xdc_UInt32 *txCppiHnd;
    xdc_UInt32 *rxCppiHnd;
    xdc_UInt32 *rxFlowHnd;
    xdc_Void *hwiHandle;
    ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType queueRcvConfig;
    ti_transport_ipc_c66_qmss_TransportQmss___struct__1 u;
    xdc_UInt32 rxIntVectorId;
    xdc_Void *rmServiceHandle;
    ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheList flowCache;
    xdc_UInt16 transNetId;
};

#endif /* ti_transport_ipc_c66_qmss_TransportQmss__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_transport_ipc_c66_qmss_TransportQmss__nolocalnames)

#ifndef ti_transport_ipc_c66_qmss_TransportQmss__localnames__done
#define ti_transport_ipc_c66_qmss_TransportQmss__localnames__done

/* module prefix */
#define TransportQmss_Instance ti_transport_ipc_c66_qmss_TransportQmss_Instance
#define TransportQmss_Handle ti_transport_ipc_c66_qmss_TransportQmss_Handle
#define TransportQmss_Module ti_transport_ipc_c66_qmss_TransportQmss_Module
#define TransportQmss_Object ti_transport_ipc_c66_qmss_TransportQmss_Object
#define TransportQmss_Struct ti_transport_ipc_c66_qmss_TransportQmss_Struct
#define TransportQmss_OK ti_transport_ipc_c66_qmss_TransportQmss_OK
#define TransportQmss_ERROR_COULD_NOT_OPEN_TX_COMP_Q ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_TX_COMP_Q
#define TransportQmss_ERROR_TX_DESCRIPTOR_INIT_FAILED ti_transport_ipc_c66_qmss_TransportQmss_ERROR_TX_DESCRIPTOR_INIT_FAILED
#define TransportQmss_ERROR_COULD_NOT_OPEN_RX_FREE_Q ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_RX_FREE_Q
#define TransportQmss_ERROR_COULD_NOT_OPEN_RX_ACCUM_Q ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_RX_ACCUM_Q
#define TransportQmss_ERROR_RX_DESCRIPTOR_INIT_FAILED ti_transport_ipc_c66_qmss_TransportQmss_ERROR_RX_DESCRIPTOR_INIT_FAILED
#define TransportQmss_ERROR_ALLOC_FROM_RX_MESSAGEQ_HEAP_FAILED ti_transport_ipc_c66_qmss_TransportQmss_ERROR_ALLOC_FROM_RX_MESSAGEQ_HEAP_FAILED
#define TransportQmss_ERROR_ALLOC_OF_ACCUM_LIST_FAILED ti_transport_ipc_c66_qmss_TransportQmss_ERROR_ALLOC_OF_ACCUM_LIST_FAILED
#define TransportQmss_ERROR_INVALID_ACCUMULATOR_CH ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_ACCUMULATOR_CH
#define TransportQmss_ERROR_INST_ALREADY_EXISTS ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INST_ALREADY_EXISTS
#define TransportQmss_ERROR_INVALID_QUEUE_RCV_TYPE ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_QUEUE_RCV_TYPE
#define TransportQmss_ERROR_INVALID_DEVICE_CFG_PARAMS ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_DEVICE_CFG_PARAMS
#define TransportQmss_ERROR_INVALID_TRANSPORT_ID ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_TRANSPORT_ID
#define TransportQmss_ERROR_COULD_NOT_REGISTER_TRANSPORT ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_REGISTER_TRANSPORT
#define TransportQmss_ERROR_COULD_NOT_OPEN_RX_QPEND_Q ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_RX_QPEND_Q
#define TransportQmss_ERROR_COULD_NOT_FIND_VALID_RX_QPEND_Q ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_FIND_VALID_RX_QPEND_Q
#define TransportQmss_ERROR_INVALID_QMSS_PDSP ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_QMSS_PDSP
#define TransportQmss_ERROR_COULD_NOT_PROGRAM_ACCUM ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_PROGRAM_ACCUM
#define TransportQmss_ERROR_COULD_NOT_OPEN_INFRA_CPDMA ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_INFRA_CPDMA
#define TransportQmss_ERROR_COULD_NOT_OPEN_CPPI_RX_FLOW ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_OPEN_CPPI_RX_FLOW
#define TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_TX_CH ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_TX_CH
#define TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_RX_CH ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_ENABLE_CPPI_RX_CH
#define TransportQmss_ERROR_INVALID_SYSTEM_EVENT ti_transport_ipc_c66_qmss_TransportQmss_ERROR_INVALID_SYSTEM_EVENT
#define TransportQmss_ERROR_RM_SERVICE_HANDLE_IS_NULL ti_transport_ipc_c66_qmss_TransportQmss_ERROR_RM_SERVICE_HANDLE_IS_NULL
#define TransportQmss_ERROR_ALLOC_OF_FLOW_CACHE ti_transport_ipc_c66_qmss_TransportQmss_ERROR_ALLOC_OF_FLOW_CACHE
#define TransportQmss_ERROR_COULD_NOT_FIND_INFRA_TRIPLET ti_transport_ipc_c66_qmss_TransportQmss_ERROR_COULD_NOT_FIND_INFRA_TRIPLET
#define TransportQmss_pdspCfg ti_transport_ipc_c66_qmss_TransportQmss_pdspCfg
#define TransportQmss_intcQInfo ti_transport_ipc_c66_qmss_TransportQmss_intcQInfo
#define TransportQmss_dspIntcCfg ti_transport_ipc_c66_qmss_TransportQmss_dspIntcCfg
#define TransportQmss_hostIntMod ti_transport_ipc_c66_qmss_TransportQmss_hostIntMod
#define TransportQmss_DeviceConfigParams ti_transport_ipc_c66_qmss_TransportQmss_DeviceConfigParams
#define TransportQmss_FlowCacheNode ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheNode
#define TransportQmss_FlowCacheList ti_transport_ipc_c66_qmss_TransportQmss_FlowCacheList
#define TransportQmss_QueueRcvType ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvType
#define TransportQmss_AccumRcvParams ti_transport_ipc_c66_qmss_TransportQmss_AccumRcvParams
#define TransportQmss_QpendRcvParams ti_transport_ipc_c66_qmss_TransportQmss_QpendRcvParams
#define TransportQmss_QueueRcvParams ti_transport_ipc_c66_qmss_TransportQmss_QueueRcvParams
#define TransportQmss_Module_State ti_transport_ipc_c66_qmss_TransportQmss_Module_State
#define TransportQmss_Accum_State ti_transport_ipc_c66_qmss_TransportQmss_Accum_State
#define TransportQmss_Qpend_State ti_transport_ipc_c66_qmss_TransportQmss_Qpend_State
#define TransportQmss___struct__1 ti_transport_ipc_c66_qmss_TransportQmss___struct__1
#define TransportQmss_Instance_State ti_transport_ipc_c66_qmss_TransportQmss_Instance_State
#define TransportQmss_queueRcvType_INVALID ti_transport_ipc_c66_qmss_TransportQmss_queueRcvType_INVALID
#define TransportQmss_queueRcvType_ACCUMULATOR ti_transport_ipc_c66_qmss_TransportQmss_queueRcvType_ACCUMULATOR
#define TransportQmss_queueRcvType_QPEND ti_transport_ipc_c66_qmss_TransportQmss_queueRcvType_QPEND
#define TransportQmss_A_txMsgQFreeError ti_transport_ipc_c66_qmss_TransportQmss_A_txMsgQFreeError
#define TransportQmss_A_newRxBufNull ti_transport_ipc_c66_qmss_TransportQmss_A_newRxBufNull
#define TransportQmss_Params ti_transport_ipc_c66_qmss_TransportQmss_Params
#define TransportQmss_bind ti_transport_ipc_c66_qmss_TransportQmss_bind
#define TransportQmss_unbind ti_transport_ipc_c66_qmss_TransportQmss_unbind
#define TransportQmss_put ti_transport_ipc_c66_qmss_TransportQmss_put
#define TransportQmss_recycleUsedTxBufs ti_transport_ipc_c66_qmss_TransportQmss_recycleUsedTxBufs
#define TransportQmss_flushDstCache ti_transport_ipc_c66_qmss_TransportQmss_flushDstCache
#define TransportQmss_Module_name ti_transport_ipc_c66_qmss_TransportQmss_Module_name
#define TransportQmss_Module_id ti_transport_ipc_c66_qmss_TransportQmss_Module_id
#define TransportQmss_Module_startup ti_transport_ipc_c66_qmss_TransportQmss_Module_startup
#define TransportQmss_Module_startupDone ti_transport_ipc_c66_qmss_TransportQmss_Module_startupDone
#define TransportQmss_Module_hasMask ti_transport_ipc_c66_qmss_TransportQmss_Module_hasMask
#define TransportQmss_Module_getMask ti_transport_ipc_c66_qmss_TransportQmss_Module_getMask
#define TransportQmss_Module_setMask ti_transport_ipc_c66_qmss_TransportQmss_Module_setMask
#define TransportQmss_Object_heap ti_transport_ipc_c66_qmss_TransportQmss_Object_heap
#define TransportQmss_Module_heap ti_transport_ipc_c66_qmss_TransportQmss_Module_heap
#define TransportQmss_construct ti_transport_ipc_c66_qmss_TransportQmss_construct
#define TransportQmss_create ti_transport_ipc_c66_qmss_TransportQmss_create
#define TransportQmss_handle ti_transport_ipc_c66_qmss_TransportQmss_handle
#define TransportQmss_struct ti_transport_ipc_c66_qmss_TransportQmss_struct
#define TransportQmss_Handle_label ti_transport_ipc_c66_qmss_TransportQmss_Handle_label
#define TransportQmss_Handle_name ti_transport_ipc_c66_qmss_TransportQmss_Handle_name
#define TransportQmss_Instance_init ti_transport_ipc_c66_qmss_TransportQmss_Instance_init
#define TransportQmss_Object_count ti_transport_ipc_c66_qmss_TransportQmss_Object_count
#define TransportQmss_Object_get ti_transport_ipc_c66_qmss_TransportQmss_Object_get
#define TransportQmss_Object_first ti_transport_ipc_c66_qmss_TransportQmss_Object_first
#define TransportQmss_Object_next ti_transport_ipc_c66_qmss_TransportQmss_Object_next
#define TransportQmss_Object_sizeof ti_transport_ipc_c66_qmss_TransportQmss_Object_sizeof
#define TransportQmss_Params_copy ti_transport_ipc_c66_qmss_TransportQmss_Params_copy
#define TransportQmss_Params_init ti_transport_ipc_c66_qmss_TransportQmss_Params_init
#define TransportQmss_Instance_finalize ti_transport_ipc_c66_qmss_TransportQmss_Instance_finalize
#define TransportQmss_delete ti_transport_ipc_c66_qmss_TransportQmss_delete
#define TransportQmss_destruct ti_transport_ipc_c66_qmss_TransportQmss_destruct
#define TransportQmss_Module_upCast ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast
#define TransportQmss_Module_to_ti_sdo_ipc_interfaces_INetworkTransport ti_transport_ipc_c66_qmss_TransportQmss_Module_to_ti_sdo_ipc_interfaces_INetworkTransport
#define TransportQmss_Handle_upCast ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast
#define TransportQmss_Handle_to_ti_sdo_ipc_interfaces_INetworkTransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_to_ti_sdo_ipc_interfaces_INetworkTransport
#define TransportQmss_Handle_downCast ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast
#define TransportQmss_Handle_from_ti_sdo_ipc_interfaces_INetworkTransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_from_ti_sdo_ipc_interfaces_INetworkTransport
#define TransportQmss_Module_upCast2 ti_transport_ipc_c66_qmss_TransportQmss_Module_upCast2
#define TransportQmss_Module_to_ti_sdo_ipc_interfaces_ITransport ti_transport_ipc_c66_qmss_TransportQmss_Module_to_ti_sdo_ipc_interfaces_ITransport
#define TransportQmss_Handle_upCast2 ti_transport_ipc_c66_qmss_TransportQmss_Handle_upCast2
#define TransportQmss_Handle_to_ti_sdo_ipc_interfaces_ITransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_to_ti_sdo_ipc_interfaces_ITransport
#define TransportQmss_Handle_downCast2 ti_transport_ipc_c66_qmss_TransportQmss_Handle_downCast2
#define TransportQmss_Handle_from_ti_sdo_ipc_interfaces_ITransport ti_transport_ipc_c66_qmss_TransportQmss_Handle_from_ti_sdo_ipc_interfaces_ITransport

#endif /* ti_transport_ipc_c66_qmss_TransportQmss__localnames__done */
#endif
