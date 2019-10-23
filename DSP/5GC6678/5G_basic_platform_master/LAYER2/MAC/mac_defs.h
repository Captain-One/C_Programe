#ifndef __LAYER2_MAC_DEFS_H__
#define __LAYER2_MAC_DEFS_H__



#include "platform_types.h"
#include "mac.h"

#include "DRX-Config.h"
#include "SchedulingRequestConfig.h"
#include "BSR-Config.h"
#include "TAG-Config.h"
#include "PHR-Config.h"
#include "RNTI-Value.h"
#include "MIB.h"
#include "SIB1.h"
#include "MAC-CellGroupConfig.h"
#include "MeasConfig.h"
#include "PhysicalCellGroupConfig.h"
#include "SpCellConfig.h"
#include "ServingCellConfig.h"
#include "LogicalChannelConfig.h"
#include "BWP-UplinkCommon.h"
#include "TDD-UL-DL-ConfigDedicated.h"
#include "RRCSetup.h"
#include "RRCReconfiguration.h"
#include "asn1_constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NB_NR_UE_MAC_INST 1

#define BCCH_PAYLOAD_SIZE_MAX 128
#define CCCH_PAYLOAD_SIZE_MAX 128
#define PCCH_PAYLOAD_SIZE_MAX 128
#define RAR_PAYLOAD_SIZE_MAX 128

#define SCH_PAYLOAD_SIZE_MAX 8192
#define DCH_PAYLOAD_SIZE_MAX 4096

/*!\brief size of buffer status report table */
#define BSR5_TABLE_SIZE 32
#define BSR8_TABLE_SIZE 256

/*!\bitmaps for BSR Triggers */
#define BSR_TRIGGER_NONE			(0)			/* No BSR Trigger */
#define BSR_TRIGGER_REGULAR		(1)			/* For Regular and ReTxBSR Expiry Triggers */
#define BSR_TRIGGER_PERIODIC	(2)			/* For BSR Periodic Timer Expiry Trigger */
#define BSR_TRIGGER_PADDING		(4)			/* For Padding BSR Trigger */

enum transmission_access_mode {
	NO_ACCESS=0,
	POSTPONED_ACCESS,
	CANCELED_ACCESS,
	UNKNOWN_ACCESS,
	SCHEDULED_ACCESS,
	CBA_ACCESS};

/*!\brief UE ULSCH scheduling states*/
typedef enum {
	S_UL_NONE =0,
	S_UL_WAITING,
	S_UL_SCHEDULED,
	S_UL_BUFFERED,
	S_UL_NUM_STATUS
} UE_ULSCH_STATUS;

/*!\brief UE DLSCH scheduling states*/
typedef enum {
	S_DL_NONE =0,
	S_DL_WAITING,
	S_DL_SCHEDULED,
	S_DL_BUFFERED,
	S_DL_NUM_STATUS
} UE_DLSCH_STATUS;

/*! \brief Downlink SCH PDU Structure */
typedef struct {
	uint8_t payload[8][SCH_PAYLOAD_SIZE_MAX];
	uint16_t Pdu_size[8];
} __attribute__ ((__packed__)) DLSCH_PDU;

/*! \brief Uplink SCH PDU Structure */
typedef struct {
	int8_t payload[SCH_PAYLOAD_SIZE_MAX];	/*!< \brief SACH payload */
	uint16_t Pdu_size;
} __attribute__ ((__packed__)) ULSCH_PDU;

/*! \brief Uplink SCH PDU Structure */
typedef struct {
	int8_t payload[DCH_PAYLOAD_SIZE_MAX];         /*!< \brief SACH payload */
	uint16_t Pdu_size;
} __attribute__ ((__packed__)) ULDCH_PDU;

typedef enum {
	SFN_C_MOD_2_EQ_0,
	SFN_C_MOD_2_EQ_1
} SFN_C_TYPE;

typedef enum {
	NOT_SYNCHED=0,
	PRACH=1,
	RA_RESPONSE=2,
	PUSCH=3,
	RESYNCH=4
} UE_MODE_t;

//随机接入前导资源结构体
typedef struct {
//	Preamble index for PRACH (0-63)
	uint8_t ra_PreambleIndex;
//	RACH MaskIndex
	uint8_t ra_RACH_MaskIndex;
//	Target received power at eNB (-120 ... -82 dBm)
	int8_t ra_PREAMBLE_RECEIVED_TARGET_POWER;
//	PRACH index for TDD (0 ... 6) depending on TDD configuration and prachConfigIndex
	uint8_t ra_TDD_map_index;
//	Corresponding RA-RNTI for UL-grant
	uint16_t ra_RNTI;
//	Pointer to Msg3 payload for UL-grant
	uint8_t *Msg3;
} PRACH_RESOURCES_t;

/*!\brief UE scheduling info */
typedef struct {
//	buffer status for each lcgid
	uint8_t BSR[maxLCG_ID + 1];	// should be more for mesh topology
//	keep the number of bytes in rlc buffer for each lcgid
	int32_t BSR_bytes[maxLCG_ID + 1];
//	after multiplexing buffer remain for each lcid
	int32_t LCID_buffer_remain[maxLC_ID];
//	sum of all lcid buffer size
	uint16_t All_lcid_buffer_size_lastTTI;
//	buffer status for each lcid
	uint8_t LCID_status[maxLC_ID];
//	SR pending as defined in 38.321
	uint8_t SR_pending;
//	SR_COUNTER as defined in 38.321
	uint16_t SR_COUNTER;
//	logical channel group ide for each LCID
	uint8_t LCGID[maxLC_ID];
//	retxBSR-Timer, default value is sf2560
	uint16_t retxBSR_Timer;
//	retxBSR_SF, number of subframe before triggering a regular BSR
	uint16_t retxBSR_SF;
//	periodicBSR-Timer, default to infinity
	uint16_t periodicBSR_Timer;
//	periodicBSR_SF, number of subframe before triggering a periodic BSR
	uint16_t periodicBSR_SF;
//	default value is 0: not configured
	uint16_t sr_ProhibitTimer;
//	sr ProhibitTime running
	uint8_t sr_ProhibitTimer_Running;
//	default value to n5
	uint16_t maxHARQ_Tx;
//	default value is false
	uint16_t ttiBundling;
//	DL Pathloss change value
	uint16_t PathlossChange;
//	number of subframe before triggering a periodic PHR
	int16_t periodicPHR_SF;
//	number of subframe before triggering a prohibit PHR
	int16_t prohibitPHR_SF;
//	DL Pathloss Change in db
	uint16_t PathlossChange_db;
//	default value is false
	uint16_t extendedBSR_Sizes_r10;
//	Bj bucket usage per  lcid
	int16_t Bj[maxLC_ID];
//	Bucket size per lcid
	int16_t bucket_size[maxLC_ID];
} SCHEDULING_INFO;

typedef enum {
	kHz15=0,
	kHz30,
	kHz60,
	kHz120,
	kHz240
} nr_scs_e;

typedef struct {
//	Size of first RBG
	uint8_t start_size;
//	Nominal size
	uint8_t P;
//	Size of last RBG
	uint8_t end_size;
//	Number of RBG
	uint8_t N_RBG;
} nr_rbg_parms_t;

typedef struct {
//	Size of first PRG
	uint8_t start_size;
//	Nominal size
	uint8_t P_prime;
//	Size of last PRG
	uint8_t end_size;
//	Number of PRG
	uint8_t N_PRG;
} nr_prg_parms_t;

typedef struct NR_BWP_PARMS {
//	BWP ID
	uint8_t bwp_id;
//	Subcarrier spacing
	nr_scs_e scs;
//	Freq domain location -- 1st CRB index
	uint8_t location;
//	Bandwidth in PRB
	uint16_t N_RB;
//	Cyclic prefix
	uint8_t cyclic_prefix;
//	RBG params
	nr_rbg_parms_t rbg_parms;
//	PRG params
	nr_prg_parms_t prg_parms;
} NR_BWP_PARMS;

/*!\brief Top level UE MAC structure */
typedef struct {
	MIB_t							*mib;
	SIB1_t							*sib1;
//	MAC-CellGroupConfig
	DRX_Config_t					*drx_Config;
	SchedulingRequestConfig_t	*schedulingRequestConfig;
	BSR_Config_t					*bsr_Config;
	TAG_Config_t					*tag_Config;
	PHR_Config_t					*phr_Config;
	MeasConfig_t					*measconfig;
	boolean_t						skipUplinkTxDynamic;
	RNTI_Value_t					cs_RNTI;
	LogicalChannelConfig_t		*logicalChannelConfig[maxLC_ID];
//	RRCSetup包含的CellGroupConfig
	RRCSetup_t						*rrcsetup;
	RRCReconfiguration_t			*rrcreconfig;
//	BSR report falg management
	uint8_t						BSR_reporting_active;
//	power backoff due to power management (as allowed by P-MPRc) for this cell
	uint8_t						PHR_reporting_active;
//	Scheduling Information
	SCHEDULING_INFO				scheduling_info;
//	Type0-PDCCH seach space
	uint32_t						type0_pdcch_ss_mux_pattern;
	SFN_C_TYPE						type0_pdcch_ss_sfn_c;
	uint32_t						type0_pdcch_ss_n_c;
	uint32_t						type0_pdcch_consecutive_slots;

//	Random access parameter
	PRACH_RESOURCES_t				RA_prach_resources;
	RA_state						rast;
	uint8_t						preambleid;
	uint16_t						ra_rnti;
	uint8_t						CCCH_pdu[128];
	uint8_t 						RA_PREAMBLE_TRANSMISSION_COUNTER;

//	BWP params
	NR_BWP_PARMS					initial_bwp_dl;
	NR_BWP_PARMS					initial_bwp_ul;
//	BWP_UplinkCommon_t* 			initial_bwp_ul;
	boolean_t						configuredGrantReleased;
} NR_UE_MAC_INST_t;

typedef enum seach_space_mask_e {
	type0_pdcch  = 0x1,
	type0a_pdcch = 0x2,
	type1_pdcch  = 0x4,
	type2_pdcch  = 0x8,
	type3_pdcch  = 0x10
} search_space_mask_t;

typedef enum subcarrier_spacing_e {
	scs_15kHz  = 0x1,
	scs_30kHz  = 0x2,
	scs_60kHz  = 0x4,
	scs_120kHz = 0x8,
	scs_240kHz = 0x16
} subcarrier_spacing_t;

typedef enum channel_bandwidth_e {
	bw_5MHz   = 0x1,
	bw_10MHz  = 0x2,
	bw_20MHz  = 0x4,
	bw_40MHz  = 0x8,
	bw_80MHz  = 0x16,
	bw_100MHz = 0x32
} channel_bandwidth_t;

typedef enum frequency_range_e {
	FR1 = 0, // sub6G
	FR2
} frequency_range_t;

typedef enum {
	SF_DL = 0,
	SF_UL,
	SF_S
} lte_subframe_t;

#define NUM_SLOT_FRAME 10

/*@}*/
#endif /*__LAYER2_MAC_DEFS_H__ */
