#ifndef __RRC_DEFS_LTE_H__
#define __RRC_DEFS_LTE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rrc_types.h"
#include "rlc.h"
#include "platform_constants.h"
#include "platform_types.h"
#include "mac.h"
#include "MeasObjectToAddMod.h"
#include "MeasGapConfig.h"
#include "LogicalChannelConfig.h"
#include "CipheringAlgorithm.h"
#include "IntegrityProtAlgorithm.h"

//for D2D
#define DEBUG_CTRL_SOCKET
#define BUFSIZE                1024
#define CONTROL_SOCKET_PORT_NO 8888
#define MAX_NUM_DEST           10
//netlink
//#define DEBUG_PDCP
#define UE_IP_PDCP_NETLINK_ID  31
#define PDCP_PID               1
#define NETLINK_HEADER_SIZE    16
#define SL_DEFAULT_RAB_ID      3
#define SLRB_ID                3

#define MAX_PAYLOAD 1024 /* maximum payload size*/

#define MAX_NUM_NEIGH_CELLs 6 /* maximum neighbouring cells number */

#define UE_STATE_NOTIFICATION_INTERVAL      50

#define IPV4_ADDR    "%u.%u.%u.%u"
#define IPV4_ADDR_FORMAT(aDDRESS)                 \
  (uint8_t)((aDDRESS)  & 0x000000ff),         \
  (uint8_t)(((aDDRESS) & 0x0000ff00) >> 8 ),  \
  (uint8_t)(((aDDRESS) & 0x00ff0000) >> 16),  \
  (uint8_t)(((aDDRESS) & 0xff000000) >> 24)


//-----------------------------------------------------
// header for Control socket

//Primitives
#define SESSION_INIT_REQ                    1
#define UE_STATUS_INFO                      2
#define GROUP_COMMUNICATION_ESTABLISH_REQ   3
#define GROUP_COMMUNICATION_ESTABLISH_RSP   4
#define DIRECT_COMMUNICATION_ESTABLISH_REQ  5
#define DIRECT_COMMUNICATION_ESTABLISH_RSP  6
#define GROUP_COMMUNICATION_RELEASE_REQ     7
#define GROUP_COMMUNICATION_RELEASE_RSP     8
#define PC5S_ESTABLISH_REQ                  9
#define PC5S_ESTABLISH_RSP                  10
#define PC5_DISCOVERY_MESSAGE             11


#define PC5_DISCOVERY_PAYLOAD_SIZE      29


typedef enum {
  UE_STATE_OFF_NETWORK,
  UE_STATE_ON_NETWORK
} SL_UE_STATE_t;

typedef enum {
  GROUP_COMMUNICATION_RELEASE_OK = 0,
  GROUP_COMMUNICATION_RELEASE_FAILURE
} Group_Communication_Status_t;

struct GroupCommunicationEstablishReq {
  uint32_t sourceL2Id;
  uint32_t groupL2Id;
  uint32_t groupIpAddress;
  uint8_t pppp;
};

struct GroupCommunicationReleaseReq {
  uint32_t sourceL2Id;
  uint32_t groupL2Id;
  int slrb_id;
};

struct DirectCommunicationEstablishReq {
  uint32_t sourceL2Id;
  uint32_t destinationL2Id;
  uint32_t pppp;
};

struct PC5SEstablishReq {
  uint8_t type;
  uint32_t sourceL2Id;
  uint32_t destinationL2Id;
};

struct PC5SEstablishRsp {
  uint32_t slrbid_lcid28;
  uint32_t slrbid_lcid29;
  uint32_t slrbid_lcid30;
};


//PC5_DISCOVERY MESSAGE
typedef struct  {
  unsigned char payload[PC5_DISCOVERY_PAYLOAD_SIZE];
  uint32_t measuredPower;
}  __attribute__((__packed__)) PC5DiscoveryMessage ;


struct sidelink_ctrl_element {
  unsigned short type;
  union {
    struct GroupCommunicationEstablishReq group_comm_establish_req;
    struct DirectCommunicationEstablishReq direct_comm_establish_req;
    Group_Communication_Status_t group_comm_release_rsp;
    //struct DirectCommunicationReleaseReq  direct_comm_release_req;
    SL_UE_STATE_t ue_state;
    int slrb_id;
    struct PC5SEstablishReq pc5s_establish_req;
    struct PC5SEstablishRsp pc5s_establish_rsp;
    PC5DiscoveryMessage pc5_discovery_message;
  } sidelinkPrimitive;
};


//global variables
extern struct sockaddr_in clientaddr;
extern int slrb_id;
extern pthread_mutex_t slrb_mutex;

//the thread function
void *send_UE_status_notification(void *);



#ifndef USER_MODE
  //#include <rtai.h>
#endif

#include "SIB1.h"
#include "SystemInformation.h"
#include "RRCReconfiguration.h"
#include "RRCReconfigurationComplete.h"
#include "RRCSetup.h"
#include "RRCSetupComplete.h"
#include "RRCSetupRequest.h"
#include "RRCReestablishmentRequest.h"
#include "BCCH-DL-SCH-Message.h"
#include "BCCH-BCH-Message.h"
#include "UE-NR-Capability.h"
#include "MeasResults.h"

/* for ImsiMobileIdentity_t */
//#include "MobileIdentity.h"

#include "DRX-Config.h"

/* correct Rel(8|10)/Rel14 differences
 * the code is in favor of Rel14, those defines do the translation
 */
#if 0//(RRC_VERSION < MAKE_VERSION(14, 0, 0))
  #define CipheringAlgorithm_r12_t e_SecurityAlgorithmConfig__cipheringAlgorithm
  #define CipheringAlgorithm_r12_eea0 SecurityAlgorithmConfig_cipheringAlgorithm_eea0
  #define CipheringAlgorithm_r12_eea1 SecurityAlgorithmConfig__cipheringAlgorithm_eea1
  #define CipheringAlgorithm_r12_eea2 SecurityAlgorithmConfig__cipheringAlgorithm_eea2
  #define CipheringAlgorithm_r12_spare1 SecurityAlgorithmConfig__cipheringAlgorithm_spare1
  #define Alpha_r12_al0 UplinkPowerControlCommon__alpha_al0
  #define Alpha_r12_al04 UplinkPowerControlCommon__alpha_al04
  #define Alpha_r12_al05 UplinkPowerControlCommon__alpha_al05
  #define Alpha_r12_al06 UplinkPowerControlCommon__alpha_al06
  #define Alpha_r12_al07 UplinkPowerControlCommon__alpha_al07
  #define Alpha_r12_al08 UplinkPowerControlCommon__alpha_al08
  #define Alpha_r12_al09 UplinkPowerControlCommon__alpha_al09
  #define Alpha_r12_al1 UplinkPowerControlCommon__alpha_al1
  #define PreambleTransMax_n3 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n3
  #define PreambleTransMax_n4 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n4
  #define PreambleTransMax_n5 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n5
  #define PreambleTransMax_n6 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n6
  #define PreambleTransMax_n7 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n7
  #define PreambleTransMax_n8 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n8
  #define PreambleTransMax_n10 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n10
  #define PreambleTransMax_n20 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n20
  #define PreambleTransMax_n50 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n50
  #define PreambleTransMax_n100 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n100
  #define PreambleTransMax_n200 RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n200
  #define PeriodicBSR_Timer_r12_sf5 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf5
  #define PeriodicBSR_Timer_r12_sf10 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf10
  #define PeriodicBSR_Timer_r12_sf16 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf16
  #define PeriodicBSR_Timer_r12_sf20 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf20
  #define PeriodicBSR_Timer_r12_sf32 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf32
  #define PeriodicBSR_Timer_r12_sf40 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf40
  #define PeriodicBSR_Timer_r12_sf64 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf64
  #define PeriodicBSR_Timer_r12_sf80 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf80
  #define PeriodicBSR_Timer_r12_sf128 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf128
  #define PeriodicBSR_Timer_r12_sf160 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf160
  #define PeriodicBSR_Timer_r12_sf320 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf320
  #define PeriodicBSR_Timer_r12_sf640 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf640
  #define PeriodicBSR_Timer_r12_sf1280 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf1280
  #define PeriodicBSR_Timer_r12_sf2560 MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_sf2560
  #define PeriodicBSR_Timer_r12_infinity MAC_MainConfig__ul_SCH_Config__periodicBSR_Timer_infinity
  #define RetxBSR_Timer_r12_sf320 MAC_MainConfig__ul_SCH_Config__retxBSR_Timer_sf320
  #define RetxBSR_Timer_r12_sf640 MAC_MainConfig__ul_SCH_Config__retxBSR_Timer_sf640
  #define RetxBSR_Timer_r12_sf1280 MAC_MainConfig__ul_SCH_Config__retxBSR_Timer_sf1280
  #define RetxBSR_Timer_r12_sf2560 MAC_MainConfig__ul_SCH_Config__retxBSR_Timer_sf2560
  #define RetxBSR_Timer_r12_sf5120 MAC_MainConfig__ul_SCH_Config__retxBSR_Timer_sf5120
  #define RetxBSR_Timer_r12_sf10240 MAC_MainConfig__ul_SCH_Config__retxBSR_Timer_sf10240
#endif

// This corrects something generated by asn1c which is different between Rel8 and Rel10
#if 0//(RRC_VERSION <= MAKE_VERSION(10, 0, 0))
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member SystemInformation_r8_IEs_sib_TypeAndInfo_Member
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib2 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib2
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib3 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib3
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib4 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib4
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib5 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib5
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib6 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib6
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib7 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib7
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib8 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib8
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib9 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib9
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib10 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib10
  #define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib11 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib11
#endif


#define NB_SIG_CNX_CH 1
#define NB_CNX_CH MAX_MOBILES_PER_ENB
#define NB_SIG_CNX_UE 2 //MAX_MANAGED_RG_PER_MOBILE
#define NB_CNX_UE 2//MAX_MANAGED_RG_PER_MOBILE

/*
#if (RRC_VERSION < MAKE_VERSION(10, 0, 0))
#define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib12_v920 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib12_v920
#define SystemInformation_r8_IEs__sib_TypeAndInfo__Member_PR_sib13_v920 SystemInformation_r8_IEs_sib_TypeAndInfo_Member_PR_sib13_v920
#endif
*/
//#include "L3_rrc_defs.h"
//#ifndef NO_RRM
//  #include "L3_rrc_interface.h"
//  #include "rrc_rrm_msg.h"
//  #include "rrc_rrm_interface.h"
//#endif
//
//
//#include "intertask_interface.h"




#include "commonDef.h"


//--------
//typedef unsigned int uid_t;
#define UID_LINEAR_ALLOCATOR_BITMAP_SIZE (((MAX_MOBILES/8)/sizeof(unsigned int)) + 1)
typedef struct uid_linear_allocator_s {
  unsigned int   bitmap[UID_LINEAR_ALLOCATOR_BITMAP_SIZE];
} uid_allocator_t;

//--------

#define PROTOCOL_RRC_CTXT_UE_FMT           PROTOCOL_CTXT_FMT
#define PROTOCOL_RRC_CTXT_UE_ARGS(CTXT_Pp) PROTOCOL_CTXT_ARGS(CTXT_Pp)

#define PROTOCOL_RRC_CTXT_FMT           PROTOCOL_CTXT_FMT
#define PROTOCOL_RRC_CTXT_ARGS(CTXT_Pp) PROTOCOL_CTXT_ARGS(CTXT_Pp)

#define UE_MODULE_INVALID ((module_id_t) ~0) // FIXME attention! depends on type uint8_t!!!
#define UE_INDEX_INVALID  ((module_id_t) ~0) // FIXME attention! depends on type uint8_t!!! used to be -1



typedef enum SL_TRIGGER_e {
  SL_RECEIVE_COMMUNICATION=0,
  SL_TRANSMIT_RELAY_ONE_TO_ONE,
  SL_TRANSMIT_RELAY_ONE_TO_MANY,
  SL_TRANSMIT_NON_RELAY_ONE_TO_ONE,
  SL_TRANSMIT_NON_RELAY_ONE_TO_MANY,
  SL_RECEIVE_DISCOVERY,
  SL_TRANSMIT_NON_PS_DISCOVERY,
  SL_TRANSMIT_PS_DISCOVERY,
  SL_RECEIVE_V2X,
  SL_TRANSMIT_V2X,
  SL_REQUEST_DISCOVERY_TRANSMISSION_GAPS,
  SL_REQUEST_DISCOVERY_RECEPTION_GAPS
} SL_TRIGGER_t;

//#define MAX_MOBILES_PER_ENB MAX_MOBILES_PER_RG
#define RRM_FREE(p)       if ( (p) != NULL) { free(p) ; p=NULL ; }
#define RRM_MALLOC(t,n)   (t *) malloc16( sizeof(t) * n )
#define RRM_CALLOC(t,n)   (t *) malloc16( sizeof(t) * n)
#define RRM_CALLOC2(t,s)  (t *) malloc16( s )

#define MAX_MEAS_OBJ 6
#define MAX_MEAS_CONFIG 6
#define MAX_MEAS_ID 6

#define PAYLOAD_SIZE_MAX 1024
#define RRC_BUF_SIZE 255
#define UNDEF_SECURITY_MODE 0xff
#define NO_SECURITY_MODE 0x20

#define CBA_OFFSET        0xfff4
// #define NUM_MAX_CBA_GROUP 4 // in the platform_constants

/* TS 36.331: RRC-TransactionIdentifier ::= INTEGER (0..3) */
#define RRC_TRANSACTION_IDENTIFIER_NUMBER  3


typedef struct UE_RRC_INFO_s {
  UE_STATE_t State;
  uint8_t SIB1systemInfoValueTag;
  uint32_t SIStatus;
  uint32_t SIcnt;
  uint8_t SIwindowsize; //!< Corresponds to the SIB1 si-WindowLength parameter. The unit is ms. Possible values are (final): 1,2,5,10,15,20,40
  uint8_t handoverTarget;
  HO_STATE_t ho_state;
  uint16_t SIperiod; //!< Corresponds to the SIB1 si-Periodicity parameter (multiplied by 10). Possible values are (final): 80,160,320,640,1280,2560,5120
  unsigned short UE_index;
  uint32_t T300_active;
  uint32_t T300_cnt;
  uint32_t T304_active;
  uint32_t T304_cnt;
  uint32_t T310_active;
  uint32_t T310_cnt;
  uint32_t N310_cnt;
  uint32_t N311_cnt;
  rnti_t   rnti;
} __attribute__ ((__packed__)) UE_RRC_INFO;

typedef struct UE_S_TMSI_s {
  boolean_t  presence;
  mme_code_t mme_code;
  m_tmsi_t   m_tmsi;
} __attribute__ ((__packed__)) UE_S_TMSI;


typedef enum e_rab_satus_e {
  E_RAB_STATUS_NEW,
  E_RAB_STATUS_DONE, // from the eNB perspective
  E_RAB_STATUS_ESTABLISHED, // get the reconfigurationcomplete form UE
  E_RAB_STATUS_REESTABLISHED, // after HO
  E_RAB_STATUS_FAILED,
  E_RAB_STATUS_TORELEASE  // to release DRB between eNB and UE
} e_rab_status_t;

typedef struct PER_EVENT_s {
  long maxReportCells;
} PER_EVENT_t;

typedef struct A1_EVENT_s {
  long threshold_RSRP;
  long hysteresis;
  long timeToTrigger;
  long maxReportCells;
} A1_EVENT_t;

typedef struct A2_EVENT_s {
  long threshold_RSRP;
  long hysteresis;
  long timeToTrigger;
  long maxReportCells;
} A2_EVENT_t;

typedef struct A3_EVENT_s {
  long a3_offset;
  int reportOnLeave;
  long hysteresis;
  long timeToTrigger;
  long maxReportCells;
} A3_EVENT_t;


typedef struct A4_EVENT_s {
  long threshold_RSRP;
  long hysteresis;
  long timeToTrigger;
  long maxReportCells;
} A4_EVENT_t;

typedef struct A5_EVENT_s {
  long threshold_RSRP_1;
  long threshold_RSRP_2;
  long hysteresis;
  long timeToTrigger;
  long maxReportCells;
} A5_EVENT_t;

typedef struct EVENTS_s {
  PER_EVENT_t *per_event;

  A1_EVENT_t *a1_event;

  A2_EVENT_t *a2_event;

  A3_EVENT_t *a3_event;

  A4_EVENT_t *a4_event;

  A5_EVENT_t *a5_event;
} EVENTS_t;

typedef struct MEASUREMENT_INFO_s {
  //TODO: Extend to multiple meas objects for OFP/OFN offsets
  long  offsetFreq;
  //TODO: extend to multiple carriers for OCP/OCN offsets
  long cellIndividualOffset[MAX_NUM_NEIGH_CELLs+1];
  long filterCoefficientRSRP;
  long filterCoefficientRSRQ;
  EVENTS_t *events;
} MEASUREMENT_INFO;


#define RRC_HEADER_SIZE_MAX 64
#define RRC_BUFFER_SIZE_MAX 1024
typedef struct {
  char Payload[RRC_BUFFER_SIZE_MAX];
  char Header[RRC_HEADER_SIZE_MAX];
  char payload_size;
} RRC_BUFFER;
#define RRC_BUFFER_SIZE sizeof(RRC_BUFFER)

//typedef struct RB_INFO_s {
//  uint16_t Rb_id;  //=Lchan_id
//  LCHAN_DESC Lchan_desc[2];
//  //  MAC_MEAS_REQ_ENTRY *Meas_entry;
//} RB_INFO;

typedef struct SRB_INFO_s {
  uint16_t Srb_id;  //=Lchan_id
  RRC_BUFFER Rx_buffer;
  RRC_BUFFER Tx_buffer;
  LCHAN_DESC Lchan_desc[2];
  unsigned int Trans_id;
  uint8_t Active;
} SRB_INFO;

//typedef struct RB_INFO_TABLE_ENTRY_s {
//  RB_INFO Rb_info;
//  uint8_t Active;
//  uint32_t Next_check_frame;
//  uint8_t Status;
//} RB_INFO_TABLE_ENTRY;

typedef struct SRB_INFO_TABLE_ENTRY_s {
  SRB_INFO Srb_info;
  uint8_t Active;
  uint8_t Status;
  uint32_t Next_check_frame;
} SRB_INFO_TABLE_ENTRY;

typedef struct MEAS_REPORT_LIST_s {
  MeasId_t measId;
  //CellsTriggeredList  cellsTriggeredList;//OPTIONAL
  uint32_t numberOfReportsSent;
} MEAS_REPORT_LIST;

typedef struct HANDOVER_INFO_UE_s {
  PhysCellId_t targetCellId;
  uint8_t measFlag;
} HANDOVER_INFO_UE;

//typedef struct rrc_gummei_s {
//  uint16_t mcc;
//  uint16_t mnc;
//  uint8_t  mnc_len;
//  uint8_t  mme_code;
//  uint16_t mme_group_id;
//} rrc_gummei_t;

typedef uid_t ue_uid_t;

  
#define MAX_UE_CAPABILITY_SIZE 255

typedef struct UE_RRC_INST_s {
  RRC_State_t     RrcState;
  RRC_Sub_State_t RrcSubState;
  plmn_t          plmnID;
  Byte_t          rat;
//  as_nas_info_t   initialNasMsg;
  WXS_UECapability_t *UECap;
  uint8_t *UECapability;
  uint8_t UECapability_size;
  UE_RRC_INFO Info[NB_SIG_CNX_UE];
  SRB_INFO Srb0[NB_SIG_CNX_UE];
  SRB_INFO_TABLE_ENTRY Srb1[NB_CNX_UE];
  SRB_INFO_TABLE_ENTRY Srb2[NB_CNX_UE];
  HANDOVER_INFO_UE HandoverInfoUe;
  uint8_t *SIB1[NB_CNX_UE];
  uint8_t sizeof_SIB1[NB_CNX_UE];
  uint8_t *SI[NB_CNX_UE];
  uint8_t sizeof_SI[NB_CNX_UE];
  uint8_t SIB1Status[NB_CNX_UE];
  uint8_t SIStatus[NB_CNX_UE];
  SIB1_t *sib1[NB_CNX_UE];
  SystemInformation_t *si[NB_CNX_UE]; //!< Temporary storage for an SI message. Decoding happens in decode_SI().
//  SIB2_t *sib2[NB_CNX_UE];
//  SIB3_t *sib3[NB_CNX_UE];
//  SIB4_t *sib4[NB_CNX_UE];
//  SIB5_t *sib5[NB_CNX_UE];
//  SIB6_t *sib6[NB_CNX_UE];
//  SIB7_t *sib7[NB_CNX_UE];
//  SIB8_t *sib8[NB_CNX_UE];
//  SIB9_t *sib9[NB_CNX_UE];
  uint8_t                           *MIB;

#ifdef CBA
  uint8_t                         num_active_cba_groups;
  uint16_t                        cba_rnti[NUM_MAX_CBA_GROUP];
#endif
  uint8_t                         num_srb;
  struct SRB_ToAddMod         *SRB1_config[NB_CNX_UE];
  struct SRB_ToAddMod         *SRB2_config[NB_CNX_UE];
  struct DRB_ToAddMod         *DRB_config[NB_CNX_UE][8];
  rb_id_t                         *defaultDRB; // remember the ID of the default DRB
  MeasObjectToAddMod_t        *MeasObj[NB_CNX_UE][MAX_MEAS_OBJ];
  struct ReportConfigToAddMod *ReportConfig[NB_CNX_UE][MAX_MEAS_CONFIG];
  struct QuantityConfig       *QuantityConfig[NB_CNX_UE];
  struct MeasIdToAddMod       *MeasId[NB_CNX_UE][MAX_MEAS_ID];
  MEAS_REPORT_LIST                *measReportList[NB_CNX_UE][MAX_MEAS_ID];
  uint32_t                        measTimer[NB_CNX_UE][MAX_MEAS_ID][6]; // 6 neighboring cells
  RSRP_Range_t                s_measure;
  struct MeasConfig__speedStatePars *speedStatePars;
  struct PhysicalConfigDedicated  *physicalConfigDedicated[NB_CNX_UE];
  struct SPS_Config           *sps_Config[NB_CNX_UE];
//  MAC_MainConfig_t            *mac_MainConfig[NB_CNX_UE];
  MeasGapConfig_t             *measGapConfig[NB_CNX_UE];
  double                          filter_coeff_rsrp; // [7] ???
  double                          filter_coeff_rsrq; // [7] ???
  float                           rsrp_db[7];
  float                           rsrq_db[7];
  float                           rsrp_db_filtered[7];
  float                           rsrq_db_filtered[7];
  /* KeNB as computed from parameters within USIM card */
  uint8_t kenb[32];
  uint8_t nh[32];
  int8_t  nh_ncc;

  /* Used integrity/ciphering algorithms */
  CipheringAlgorithm_t                          ciphering_algorithm;
  IntegrityProtAlgorithm_t integrity_algorithm;
} UE_RRC_INST;

typedef struct UE_PF_PO_s {
  boolean_t enable_flag;  /* flag indicate whether current object is used */
  uint16_t ue_index_value;  /* UE index value */
  uint8_t PF_min;  /* minimal value of Paging Frame (PF) */
  uint8_t PO;  /* Paging Occasion (PO) */
  uint32_t T;  /* DRX cycle */
} UE_PF_PO_t;

#include "rrc_proto.h"

#endif
/** @} */
