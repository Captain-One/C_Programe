/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_PhysicalConfigDedicatedSCell_r10_H_
#define	_PhysicalConfigDedicatedSCell_r10_H_


#include "asn_application.h"

/* Including external dependencies */
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AntennaInfoDedicated_r10;
struct CrossCarrierSchedulingConfig_r10;
struct CSI_RS_Config_r10;
struct PDSCH_ConfigDedicated;
struct AntennaInfoUL_r10;
struct PUSCH_ConfigDedicatedSCell_r10;
struct UplinkPowerControlDedicatedSCell_r10;
struct CQI_ReportConfigSCell_r10;
struct SoundingRS_UL_ConfigDedicated;
struct SoundingRS_UL_ConfigDedicated_v1020;
struct SoundingRS_UL_ConfigDedicatedAperiodic_r10;

/* PhysicalConfigDedicatedSCell-r10 */
typedef struct PhysicalConfigDedicatedSCell_r10 {
	struct PhysicalConfigDedicatedSCell_r10__nonUL_Configuration_r10 {
		struct AntennaInfoDedicated_r10	*antennaInfo_r10	/* OPTIONAL */;
		struct CrossCarrierSchedulingConfig_r10	*crossCarrierSchedulingConfig_r10	/* OPTIONAL */;
		struct CSI_RS_Config_r10	*csi_RS_Config_r10	/* OPTIONAL */;
		struct PDSCH_ConfigDedicated	*pdsch_ConfigDedicated_r10	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonUL_Configuration_r10;
	struct PhysicalConfigDedicatedSCell_r10__ul_Configuration_r10 {
		struct AntennaInfoUL_r10	*antennaInfoUL_r10	/* OPTIONAL */;
		struct PUSCH_ConfigDedicatedSCell_r10	*pusch_ConfigDedicatedSCell_r10	/* OPTIONAL */;
		struct UplinkPowerControlDedicatedSCell_r10	*uplinkPowerControlDedicatedSCell_r10	/* OPTIONAL */;
		struct CQI_ReportConfigSCell_r10	*cqi_ReportConfigSCell_r10	/* OPTIONAL */;
		struct SoundingRS_UL_ConfigDedicated	*soundingRS_UL_ConfigDedicated_r10	/* OPTIONAL */;
		struct SoundingRS_UL_ConfigDedicated_v1020	*soundingRS_UL_ConfigDedicated_v1020	/* OPTIONAL */;
		struct SoundingRS_UL_ConfigDedicatedAperiodic_r10	*soundingRS_UL_ConfigDedicatedAperiodic_r10	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ul_Configuration_r10;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PhysicalConfigDedicatedSCell_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PhysicalConfigDedicatedSCell_r10;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AntennaInfoDedicated-r10.h"
#include "CrossCarrierSchedulingConfig-r10.h"
#include "CSI-RS-Config-r10.h"
#include "PDSCH-ConfigDedicated.h"
#include "AntennaInfoUL-r10.h"
#include "PUSCH-ConfigDedicatedSCell-r10.h"
#include "UplinkPowerControlDedicatedSCell-r10.h"
#include "CQI-ReportConfigSCell-r10.h"
#include "SoundingRS-UL-ConfigDedicated.h"
#include "SoundingRS-UL-ConfigDedicated-v1020.h"
#include "SoundingRS-UL-ConfigDedicatedAperiodic-r10.h"

#endif	/* _PhysicalConfigDedicatedSCell_r10_H_ */
#include "asn_internal.h"
