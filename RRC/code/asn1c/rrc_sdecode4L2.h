#ifndef _RRC_SDDECODE_4_L2_H_
#define _RRC_SDDECODE_4_L2_H_


#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>	/* for atoi(3) */
#include <unistd.h>	/* for getopt(3) */
#include <string.h>	/* for strerror(3) */
#include <sysexits.h>	/* for EX_* exit codes */
#include <errno.h>	/* for errno */
#include <string.h>


#include "asn_application.h"
#include "asn_internal.h"	/* for ASN__DEFAULT_STACK_MAX */

#include "BCCH-BCH-Message.h"
#include "BCCH-BCH-MessageType.h"

#include "BCCH-DL-SCH-Message.h"
#include "BCCH-DL-SCH-MessageType.h"

#include "DL-CCCH-Message.h"
#include "DL-CCCH-MessageType.h"

#include "UL-CCCH-Message.h"
#include "UL-CCCH-MessageType.h"

#include "DL-DCCH-Message.h"
#include "DL-DCCH-MessageType.h"

#include "UL-DCCH-Message.h"
#include "UL-DCCH-MessageType.h"

#include "MCCH-Message.h"
#include "MCCH-MessageType.h"

#include "PCCH-Message.h"
#include "PCCH-MessageType.h"



#ifdef _WINDOWS
#ifdef DLL_EXPORTS
#define CYDD_EXPORT __declspec(dllexport)
#else
#define CYDD_EXPORT __declspec(dllimport)
#endif
#else
#define CYDD_EXPORT 
#endif


enum RRC_MsgType {
	eBCCH_BCH,
	eBCCH_DL_SCH,
	eDL_CCCH,
	eUL_CCCH,
	eDL_DCCH,
	eUL_DCCH,
	eMCCH,
	ePCCH
};

enum PHY_CH_TYPE
{
	PCH_UNKNOWN,
	PCH_PBCH,
	PCH_PCFICH,
	PCH_PHICH,
	PCH_PDCCH,
	PCH_PDSCH,
	PCH_PRACH,
	PCH_PUCCH,
	PCH_PUSCH,
	PCH_PMCH,
};

enum CHANNEL_DIRE
{
	E_UTRAN_TO_UE,
	UE_TO_E_UTRAN,
};

enum LOGICAL_CH_TYPE
{
	LCH_UNKNOWN,
	LCH_BCCH,
	LCH_PCCH,
	LCH_CCCH,
	LCH_DCCH,
	LCH_DTCH,
	LCH_MCCH,
	LCH_MTCH
};

enum TRANSPORT_CH_TYPE
{
	TCH_UNKNOWN,
	TCH_BCH,
	TCH_PCH,
	TCH_DL_SCH,
	TCH_RACH,
	TCH_UL_SCH,
	TCH_MCH,
};

#ifdef RRC_API_TEST_CASE
typedef struct _RRC_Sdecode_Result_4_L2 {
	unsigned int uMsgType;//RRC_MsgType 

	union
	{
		BCCH_BCH_Message_t BCCH_BCH_msg;
		BCCH_DL_SCH_Message_t BCCH_DL_SCH_msg;
		DL_CCCH_Message_t DL_CCCH_msg;
	    UL_CCCH_Message_t UL_CCCH_msg;
		DL_DCCH_Message_t DL_DCCH_msg;
		UL_DCCH_Message_t UL_DCCH_msg;
		MCCH_Message_t MCCH_msg;
		PCCH_Message_t PCCH_msg;
	}ulInformationTransfer;
}RRC_Sdecode_Result_4_L2;

typedef union subpackage_type_u {
	struct {
//		uint16_t PCH:4;
//		uint16_t subtype:3;
//		uint16_t res:1;
//		uint16_t LCH:4;
//		uint16_t TrCH:4;

		uint16_t LCH:4;
		uint16_t TrCH:4;
		uint16_t PCH:4;
		uint16_t subtype:3;
		uint16_t res:1;
	} spktype_s;
	uint16_t spktype_u16;
} SubPKType_t;

//定义帧号与子帧号联合数据结构
typedef union fn_u {
	struct {
		uint16_t sfn:10;
		uint16_t subfn:4;
		uint16_t Res1:2;
	} fn_s;
	uint16_t fn_u16;
} FN_t;

//定义载波信息联合数据结构
typedef union carrier_u {
	struct {
		uint16_t physCellId9:9;
		uint16_t DIR:1;
		uint16_t en:1;
		uint16_t Res:1;
		uint16_t RFBN:4;
	} carrier;
	struct {
		uint16_t PhysCellID:8;
		uint16_t PhyCellIDmsb:1;
		uint16_t DIR:1;
		uint16_t en:1;
		uint16_t Res:1;
		uint16_t RFBN:4;
	} carrier_2pid;
	uint16_t carrier_u16;
} CARRIER_t;


//定义非基带板协议解析相关数据结构
typedef struct ProcH_s {
	SubPKType_t sptype;	//子包类型
//	---------------------------
	FN_t fn;
//	---------------------------
	uint16_t RNTI;
//	---------------------------
	CARRIER_t carrier_info;
//	---------------------------
} ProcH_t;
#endif

int  CYDD_EXPORT RRC_sdecode(ProcH_t* proch_infoP, void *data, size_t size, RRC_Sdecode_Result_4_L2 *output);

#endif
