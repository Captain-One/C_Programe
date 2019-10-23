#ifndef __LAYER2_UE_MAC_DEFS_H__
#define __LAYER2_UE_MAC_DEFS_H__



#include "platform_types.h"
#include "asn1_constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>



#define NR_BCCH_DL_SCH 3            // SI

#define NR_BCCH_BCH 5           // MIB

/*!\brief UE layer 2 status */
typedef enum {
    UE_CONNECTION_OK = 0,
    UE_CONNECTION_LOST,
    UE_PHY_RESYNCH,
    UE_PHY_HO_PRACH
} NR_UE_L2_STATE_t;

/*!\brief type of Random Access */
typedef enum {
	Random_Access = 0,
	NO_Random_Access,
	SI_REQUEST_RA
} NR_UE_RA_TYPE_t;

/*!\brief MAC header of Random Access Response for Random access preamble identifier (RAPID) */
typedef struct {
    uint8_t PreambleID:6;
    uint8_t T:2;
} __attribute__ ((__packed__)) PREAMBLE_IND;

/*!\brief MAC header of Random Access Response for Random access preamble identifier (RAPID) */
typedef struct {
    uint8_t RAPID:6;
    uint8_t T:1;
    uint8_t E:1;
} __attribute__ ((__packed__)) RA_HEADER_RAPID;

/*!\brief  MAC header of Random Access Response for backoff indicator (BI)*/
typedef struct {
    uint8_t BI:4;
    uint8_t R:2;
    uint8_t T:1;
    uint8_t E:1;
} __attribute__ ((__packed__)) RA_HEADER_BI;

/*
typedef struct {
  uint64_t padding:8;
  uint64_t t_crnti:16;
  uint64_t xx:8;
  uint64_t hopping_flag:1;
  uint64_t rb_alloc:10;
  uint64_t mcs:4;
  uint64_t TPC:3;
  uint64_t UL_delay:1;
  uint64_t cqi_req:1;
  uint64_t Timing_Advance_Command:12;  // first/2nd octet LSB
  uint64_t R:1;                        // octet MSB
  } __attribute__((__packed__))RAR_PDU;

typedef struct {
  uint64_t padding:16;
  uint64_t R:1;                        // octet MSB
  uint64_t Timing_Advance_Command:11;  // first/2nd octet LSB
  uint64_t cqi_req:1;
  uint64_t UL_delay:1;
  uint64_t TPC:3;
  uint64_t mcs:4;
  uint64_t rb_alloc:10;
  uint64_t hopping_flag:1;
  uint64_t t_crnti:16;
  } __attribute__((__packed__))RAR_PDU;

#define sizeof_RAR_PDU 7
*/
/*
typedef struct {
  uint64_t padding:16;
  uint64_t t_crnti:16;
  uint64_t hopping_flag:1;
  uint64_t rb_alloc:10;
  uint64_t mcs:4;
  uint64_t TPC:3;
  uint64_t UL_delay:1;
  uint64_t cqi_req:1;
  uint64_t Timing_Advance_Command:11;  // first/2nd octet LSB
  uint64_t R:1;                        // octet MSB
  } __attribute__((__packed__))RAR_PDU;

typedef struct {
  uint64_t padding:16;
  uint64_t R:1;                        // octet MSB
  uint64_t Timing_Advance_Command:11;  // first/2nd octet LSB
  uint64_t cqi_req:1;
  uint64_t UL_delay:1;
  uint64_t TPC:3;
  uint64_t mcs:4;
  uint64_t rb_alloc:10;
  uint64_t hopping_flag:1;
  uint64_t t_crnti:16;
  } __attribute__((__packed__))RAR_PDU;

#define sizeof_RAR_PDU 6
*/

typedef struct {
    uint8_t LCID:6;     // octet 1 [5:0]
    uint8_t F:1;        // octet 1 [6]
    uint8_t R:1;        // octet 1 [7]
    uint8_t L:8;        // octet 2 [7:0]
} __attribute__ ((__packed__)) NR_MAC_SUBHEADER_SHORT;

typedef struct {
    uint8_t LCID:6;     // octet 1 [5:0]
    uint8_t F:1;        // octet 1 [6]
    uint8_t R:1;        // octet 1 [7]
    uint8_t L1:8;       // octet 2 [7:0]
    uint8_t L2:8;       // octet 3 [7:0]
} __attribute__ ((__packed__)) NR_MAC_SUBHEADER_LONG;

typedef struct {
    uint8_t LCID:6;     // octet 1 [5:0]
    uint8_t R:2;        // octet 1 [7:6]
} __attribute__ ((__packed__)) NR_MAC_SUBHEADER_FIXED;

/*!\brief  mac control element: short buffer status report for a specific logical channel group ID*/
typedef struct {
	uint8_t Buffer_size:5;	// octet 1 LSB
	uint8_t LCGID:3;		// octet 1 MSB
} __attribute__ ((__packed__)) BSR_SHORT;

typedef BSR_SHORT BSR_TRUNCATED;
/*!\brief  mac control element: long buffer status report for all logical channel group ID*/
typedef struct {
	uint8_t LCG0:1;
	uint8_t LCG1:1;
	uint8_t LCG2:1;
	uint8_t LCG3:1;
	uint8_t LCG4:1;
	uint8_t LCG5:1;
	uint8_t LCG6:1;
	uint8_t LCG7:1;
	uint8_t Buffer_size0;
	uint8_t Buffer_size1;
	uint8_t Buffer_size2;
	uint8_t Buffer_size3;
	uint8_t Buffer_size4;
	uint8_t Buffer_size5;
	uint8_t Buffer_size6;
	uint8_t Buffer_size7;
} __attribute__ ((__packed__)) BSR_LONG;

#define BSR_LONG_SIZE  (sizeof(BSR_LONG))


/*!\brief  mac control element: power headroom report  */
typedef struct {
	uint8_t PH:6;
	uint8_t R1:2;
	uint8_t PCMAXfc:6;
	uint8_t R2:2;
} __attribute__ ((__packed__)) SINGLE_POWER_HEADROOM;

typedef struct {
    uint8_t R:1;
    uint8_t C1:1;
    uint8_t C2:1;
    uint8_t C3:1;
    uint8_t C4:1;
    uint8_t C5:1;
    uint8_t C6:1;
    uint8_t C7:1;
} __attribute__ ((__packed__)) MULTIPLE_POWER_HEADROOM_LESS8_H;

typedef struct {
	uint8_t R:1;
	uint8_t C1:1;
	uint8_t C2:1;
	uint8_t C3:1;
	uint8_t C4:1;
	uint8_t C5:1;
	uint8_t C6:1;
	uint8_t C7:1;
	uint8_t C8:1;
	uint8_t C9:1;
	uint8_t C10:1;
	uint8_t C11:1;
	uint8_t C12:1;
	uint8_t C13:1;
	uint8_t C14:1;
	uint8_t C15:1;
	uint8_t C16:1;
	uint8_t C17:1;
	uint8_t C18:1;
	uint8_t C19:1;
	uint8_t C20:1;
	uint8_t C21:1;
	uint8_t C22:1;
	uint8_t C23:1;
	uint8_t C24:1;
	uint8_t C25:1;
	uint8_t C26:1;
	uint8_t C27:1;
	uint8_t C28:1;
	uint8_t C29:1;
	uint8_t C30:1;
	uint8_t C31:1;
} __attribute__ ((__packed__)) MULTIPLE_POWER_HEADROOM_MORE8_H;

typedef struct {
	uint8_t PH:6;
	uint8_t V:1;
	uint8_t P:1;
	uint8_t PCMAXfc:6;
	uint8_t R:2;
} __attribute__ ((__packed__)) MULTIPLE_POWER_HEADROOM;

typedef enum {
    IDLE = 0,
    MSG2,
    WAITMSG3,
    MSG4,
    WAITMSG4ACK,
    MSGCRNTI,
    MSGCRNTI_ACK
} RA_state;

typedef enum {
	NONE = 0,
	contentionbased,
	contentionfree,
	beamfailurerecovery,
	SIrequest,
	pdcch
} RA_type;

/*! \brief eNB template for the Random access information */
typedef struct {
//	Flag to indicate this process is active
	RA_state state;
//	Subframe where preamble was received
	uint8_t preamble_subframe;
//	Subframe where Msg2 is to be sent
	uint8_t Msg2_subframe;
//	Frame where Msg2 is to be sent
	frame_t Msg2_frame;
//	Subframe where Msg3 is to be sent
	sub_frame_t Msg3_subframe;
//	Frame where Msg3 is to be sent
	frame_t Msg3_frame;
//	Delay cnt for Msg4 transmission (waiting for RRC message piggyback)
	int Msg4_delay_cnt;
//	Subframe where Msg4 is to be sent
	sub_frame_t Msg4_subframe;
//	Frame where Msg4 is to be sent
	frame_t Msg4_frame;
//	harq_pid used for Msg4 transmission
	uint8_t harq_pid;
//	UE RNTI allocated during RAR
	rnti_t rnti;
//	RA RNTI allocated from received PRACH
	uint16_t RA_rnti;
//	Received preamble_index
	uint8_t preamble_index;
//	Received UE Contention Resolution Identifier
	uint8_t cont_res_id[6];
//	Timing offset indicated by PHY
	int16_t timing_offset;
//	Timeout for RRC connection
	int16_t RRC_timer;
//	Msg3 first RB
	uint8_t msg3_first_rb;
//	Msg3 number of RB
	uint8_t msg3_nb_rb;
//	Msg3 MCS
	uint8_t msg3_mcs;
//	Msg3 TPC command
	uint8_t msg3_TPC;
//	Msg3 ULdelay command
	uint8_t msg3_ULdelay;
//	Msg3 cqireq command
	uint8_t msg3_cqireq;
//	Round of Msg3 HARQ
	uint8_t msg3_round;
//	TBS used for Msg4
	int msg4_TBsize;
//	MCS used for Msg4
	int msg4_mcs;
	int32_t  crnti_rrc_mui;
	int8_t   crnti_harq_pid;
} RA_t;


/*!\brief logical channl group ID 0 */
#define LCGID0 0
/*!\brief logical channl group ID 1 */
#define LCGID1 1
/*!\brief logical channl group ID 2 */
#define LCGID2 2
/*!\brief logical channl group ID 3 */
#define LCGID3 3
/*!\brief logical channl group ID 4 */
#define LCGID4 4
/*!\brief logical channl group ID 5 */
#define LCGID5 5
/*!\brief logical channl group ID 6 */
#define LCGID6 6
/*!\brief logical channl group ID 7 */
#define LCGID7 7

/*!\brief value for indicating BSR Timer is not running */
#define MAC_UE_BSR_TIMER_NOT_RUNNING   (0xFFFF)

#define LCID_EMPTY 0
#define LCID_NOT_EMPTY 1

/*!\brief minimum RLC PDU size to be transmitted = min RLC Status PDU or RLC UM PDU SN 5 bits */
#define MIN_RLC_PDU_SIZE    (2)

/*!\brief minimum MAC data needed for transmitting 1 min RLC PDU size + 1 byte MAC subHeader */
#define MIN_MAC_HDR_RLC_SIZE    (1 + MIN_RLC_PDU_SIZE)

#define MAX_NUM_DLSCH_SEGMENTS 16
#define MAX_NUM_ULSCH_SEGMENTS MAX_NUM_DLSCH_SEGMENTS
#define MAX_DLSCH_PAYLOAD_BYTES (MAX_NUM_DLSCH_SEGMENTS*768)
#define MAX_ULSCH_PAYLOAD_BYTES (MAX_NUM_ULSCH_SEGMENTS*768)

/*!\brief minimum MAC data needed for transmitting 1 min RLC PDU size + 1 byte MAC subHeader */
#define MIN_MAC_HDR_RLC_SIZE    (1 + MIN_RLC_PDU_SIZE)

//  38.321 ch6.2.1, 38.331
#define DL_SCH_LCID_CCCH                           0x00
#define DL_SCH_LCID_SRB1                           0x01
#define DL_SCH_LCID_SRB2                           0x02
#define DL_SCH_LCID_SRB3                           0x03
#define DL_SCH_LCID_RECOMMENDED_BITRATE            0x2F
#define DL_SCH_LCID_SP_ZP_CSI_RS_RES_SET_ACT       0x30
#define DL_SCH_LCID_PUCCH_SPATIAL_RELATION_ACT     0x31
#define DL_SCH_LCID_SP_SRS_ACTIVATION              0x32
#define DL_SCH_LCID_SP_CSI_REP_PUCCH_ACT           0x33
#define DL_SCH_LCID_TCI_STATE_IND_UE_SPEC_PDCCH    0x34
#define DL_SCH_LCID_TCI_STATE_ACT_UE_SPEC_PDSCH    0x35
#define DL_SCH_LCID_APERIODIC_CSI_TRI_STATE_SUBSEL 0x36
#define DL_SCH_LCID_SP_CSI_RS_CSI_IM_RES_SET_ACT   0X37 
#define DL_SCH_LCID_DUPLICATION_ACT                0X38
#define DL_SCH_LCID_SCell_ACT_4_OCT                0X39
#define DL_SCH_LCID_SCell_ACT_1_OCT                0X3A
#define DL_SCH_LCID_L_DRX                          0x3B
#define DL_SCH_LCID_DRX                            0x3C
#define DL_SCH_LCID_TA_COMMAND                     0x3D
#define DL_SCH_LCID_CON_RES_ID                     0x3E
#define DL_SCH_LCID_PADDING                        0x3F

#define UL_SCH_LCID_CCCH                           0x00
#define UL_SCH_LCID_SRB1                           0x01
#define UL_SCH_LCID_SRB2                           0x02
#define UL_SCH_LCID_SRB3                           0x03
#define UL_SCH_LCID_CCCH_MSG3                      0x21
#define UL_SCH_LCID_RECOMMENDED_BITRATE_QUERY      0x35
#define UL_SCH_LCID_MULTI_ENTRY_PHR_4_OCT          0x36
#define UL_SCH_LCID_CONFIGURED_GRANT_CONFIRMATION  0x37
#define UL_SCH_LCID_MULTI_ENTRY_PHR_1_OCT          0x38
#define UL_SCH_LCID_SINGLE_ENTRY_PHR               0x39
#define UL_SCH_LCID_C_RNTI                         0x3A
#define UL_SCH_LCID_S_TRUNCATED_BSR                0x3B
#define UL_SCH_LCID_L_TRUNCATED_BSR                0x3C
#define UL_SCH_LCID_S_BSR                          0x3D
#define UL_SCH_LCID_L_BSR                          0x3E
#define UL_SCH_LCID_PADDING                        0x3F


#endif /*__LAYER2_MAC_DEFS_H__ */
