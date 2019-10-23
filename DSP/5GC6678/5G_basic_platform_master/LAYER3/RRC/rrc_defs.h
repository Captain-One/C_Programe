#ifndef __NR_RRC_DEFS_H__
#define __NR_RRC_DEFS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform_types.h"
#include "mac.h"
#include "rrc_list.h"

#include "MeasConfig.h"
#include "CellGroupConfig.h"
#include "RadioBearerConfig.h"
#include "RLC-BearerConfig.h"
#include "TAG.h"
#include "asn1_constants.h"
#include "SchedulingRequestToAddMod.h"
#include "MIB.h"
#include "BCCH-BCH-Message.h"
#include "DL-DCCH-Message.h"
#include "TDD-UL-DL-SlotConfig.h"
#include "BWP-Downlink.h"
#include "ControlResourceSet.h"
#include "SearchSpace.h"
#include "SlotFormatCombinationsPerCell.h"
#include "TCI-State.h"
#include "RateMatchPattern.h"
#include "ZP-CSI-RS-Resource.h"
#include "ZP-CSI-RS-ResourceSet.h"
#include "NZP-CSI-RS-Resource.h"
#include "NZP-CSI-RS-ResourceSet.h"
#include "CSI-IM-Resource.h"
#include "CSI-IM-ResourceSet.h"
#include "CSI-SSB-ResourceSet.h"
#include "CSI-ResourceConfig.h"
#include "CSI-ReportConfig.h"
#include "UE-NR-Capability.h"

#define NB_UE_INST 1

typedef uint32_t channel_t;

typedef enum {
  RRC_OK=0,
  RRC_ConnSetup_failed,
  RRC_PHY_RESYNCH,
  RRC_Handover_failed,
  RRC_HO_STARTED
} RRC_status_t;

typedef enum UE_STATE_e {
  RRC_INACTIVE=0,
  RRC_IDLE,
  RRC_SI_RECEIVED,
  RRC_CONNECTED,
  RRC_RECONFIGURED,
  RRC_HO_EXECUTION
} UE_STATE_t;

typedef enum HO_STATE_e {
  HO_IDLE=0,
  HO_MEASUREMENT,
  HO_PREPARE,
  HO_CMD, // initiated by the src eNB
  HO_COMPLETE, // initiated by the target eNB
  HO_REQUEST,
  HO_ACK,
  HO_FORWARDING,
  HO_CONFIGURED,
  HO_END_MARKER,
  HO_FORWARDING_COMPLETE,
  HO_RELEASE,
  HO_CANCEL
} HO_STATE_t;

typedef enum DATA_FORWARDING_STATE_e {
  FORWARDING_EMPTY=0,
  FORWARDING_NO_EMPTY
} DATA_FORWARDING_STATE_t;

typedef enum DATA_ENDMARK_STATE_e {
  ENDMARK_EMPTY=0,
  ENDMARK_NO_EMPTY
} DATA_ENDMARK_STATE_t;

#define MAX_UE_CAPABILITY_SIZE 255

typedef struct WXS_UECapability_s {
  uint8_t sdu[MAX_UE_CAPABILITY_SIZE];
  uint8_t sdu_size;
  UE_NR_Capability_t *UE_NR_Capability;
} WXS_UECapability_t;

typedef struct {
  unsigned short transport_block_size;   /*!< \brief Minimum PDU size in bytes provided by RLC to MAC layer interface */
  unsigned short max_transport_blocks;   /*!< \brief Maximum PDU size in bytes provided by RLC to MAC layer interface */
  unsigned long  Guaranteed_bit_rate;    /*!< \brief Guaranteed Bit Rate (average) to be offered by MAC layer scheduling*/
  unsigned long  Max_bit_rate;           /*!< \brief Maximum Bit Rate that can be offered by MAC layer scheduling*/
  uint8_t  Delay_class;                  /*!< \brief Delay class offered by MAC layer scheduling*/
  uint8_t  Target_bler;                  /*!< \brief Target Average Transport Block Error rate*/
  uint8_t  Lchan_t;                      /*!< \brief Logical Channel Type (BCCH,CCCH,DCCH,DTCH_B,DTCH,MRBCH)*/
} __attribute__ ((__packed__))  LCHAN_DESC;

#define LCHAN_DESC_SIZE sizeof(LCHAN_DESC)

typedef struct RRC_INST_s {

    MeasConfig_t        *meas_config;
    CellGroupConfig_t   *cell_group_config;
    RadioBearerConfig_t *radio_bearer_config;

    MIB_t *mib;
  
    //  lists
    //  CellGroupConfig.rlc-BearerToAddModList
    RRC_LIST_TYPE(RLC_BearerConfig_t, maxLC_ID) RLC_Bearer_Config_list;
    //  CellGroupConfig.mac-CellGroupConfig.schedulingrequest
    RRC_LIST_TYPE(SchedulingRequestToAddMod_t, maxNrofSR_ConfigPerCellGroup) SchedulingRequest_list;
    //  CellGroupConfig.mac-CellGroupConfig.TAG
    RRC_LIST_TYPE(TAG_t, maxNrofTAGs) TAG_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.tdduldlslotconfig
    RRC_LIST_TYPE(TDD_UL_DL_SlotConfig_t, maxNrofSlots) TDD_UL_DL_SlotConfig_list;
   
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.bwps 
    RRC_LIST_TYPE(BWP_Downlink_t, maxNrofBWPs) BWP_Downlink_list;
    //BWP-DownlinkDedicated 0=INIT-DL-BWP, 1..4 for DL-BWPs
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdcchconfig.controlresourceset
    RRC_LIST_TYPE(ControlResourceSet_t, 3) ControlResourceSet_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdcchconfig.searchspace
    RRC_LIST_TYPE(SearchSpace_t, 10) SearchSpace_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdcchconfig.slotformatindicator
    RRC_LIST_TYPE(SlotFormatCombinationsPerCell_t, maxNrofAggregatedCellsPerCellGroup) SlotFormatCombinationsPerCell_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdschconfig
    RRC_LIST_TYPE(TCI_State_t, maxNrofTCI_States) TCI_State_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdschconfig
    RRC_LIST_TYPE(RateMatchPattern_t, maxNrofRateMatchPatterns) RateMatchPattern_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdschconfig
    RRC_LIST_TYPE(ZP_CSI_RS_Resource_t, maxNrofZP_CSI_RS_Resources) ZP_CSI_RS_Resource_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdschconfig
    RRC_LIST_TYPE(ZP_CSI_RS_ResourceSet_t, maxNrofZP_CSI_RS_ResourceSets) Aperidic_ZP_CSI_RS_ResourceSet_list[5];
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated.initialdlbwp.pdschconfig
    RRC_LIST_TYPE(ZP_CSI_RS_ResourceSet_t, maxNrofZP_CSI_RS_ResourceSets) SP_ZP_CSI_RS_ResourceSet_list[5];

    //  TODO check the way to implement mutiple list inside bwps
    //  uplink bwp also

    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(NZP_CSI_RS_Resource_t, maxNrofNZP_CSI_RS_Resources) NZP_CSI_RS_Resource_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(NZP_CSI_RS_ResourceSet_t, maxNrofNZP_CSI_RS_ResourceSets) NZP_CSI_RS_ResourceSet_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(CSI_IM_Resource_t, maxNrofCSI_IM_Resources) CSI_IM_Resource_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(CSI_IM_ResourceSet_t, maxNrofCSI_IM_ResourceSets) CSI_IM_ResourceSet_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(CSI_SSB_ResourceSet_t, maxNrofCSI_SSB_ResourceSets) CSI_SSB_ResourceSet_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(CSI_ResourceConfig_t, maxNrofCSI_ResourceConfigurations) CSI_ResourceConfig_list;
    //  CellGroupConfig.spCellConfig.spCellConfigDedicated
    RRC_LIST_TYPE(CSI_ReportConfig_t, maxNrofCSI_ReportConfigurations) CSI_ReportConfig_list;
  
} NR_UE_RRC_INST_t;

#endif
/** @} */
