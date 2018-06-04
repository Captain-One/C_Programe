/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-UE-Variables"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_VarMeasConfig_H_
#define	_VarMeasConfig_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeInteger.h"
#include "NULL.h"
#include "MobilityStateParameters.h"
#include "SpeedStateScaleFactors.h"
#include "constr_SEQUENCE.h"
#include "constr_CHOICE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum VarMeasConfig__speedStatePars_PR {
	VarMeasConfig__speedStatePars_PR_NOTHING,	/* No components present */
	VarMeasConfig__speedStatePars_PR_release,
	VarMeasConfig__speedStatePars_PR_setup
} VarMeasConfig__speedStatePars_PR;

/* Forward declarations */
struct MeasIdToAddModList;
struct MeasObjectToAddModList;
struct ReportConfigToAddModList;
struct QuantityConfig;

/* VarMeasConfig */
typedef struct VarMeasConfig {
	struct MeasIdToAddModList	*measIdList	/* OPTIONAL */;
	struct MeasObjectToAddModList	*measObjectList	/* OPTIONAL */;
	struct ReportConfigToAddModList	*reportConfigList	/* OPTIONAL */;
	struct QuantityConfig	*quantityConfig	/* OPTIONAL */;
	long	*s_Measure	/* OPTIONAL */;
	struct VarMeasConfig__speedStatePars {
		VarMeasConfig__speedStatePars_PR present;
		union VarMeasConfig__speedStatePars_u {
			NULL_t	 release;
			struct VarMeasConfig__speedStatePars__setup {
				MobilityStateParameters_t	 mobilityStateParameters;
				SpeedStateScaleFactors_t	 timeToTrigger_SF;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} setup;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *speedStatePars;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VarMeasConfig_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VarMeasConfig;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MeasIdToAddModList.h"
#include "MeasObjectToAddModList.h"
#include "ReportConfigToAddModList.h"
#include "QuantityConfig.h"

#endif	/* _VarMeasConfig_H_ */
#include "asn_internal.h"
