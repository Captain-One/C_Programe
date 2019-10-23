/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_PDCCH_Config_H_
#define	_PDCCH_Config_H_


#include "asn_application.h"

/* Including external dependencies */
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"
#include "ControlResourceSetId.h"
#include "SearchSpaceId.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SetupRelease;
struct ControlResourceSet;
struct SearchSpace;

/* PDCCH-Config */
typedef struct PDCCH_Config {
	struct PDCCH_Config__controlResourceSetToAddModList {
		A_SEQUENCE_OF(struct ControlResourceSet) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *controlResourceSetToAddModList;
	struct PDCCH_Config__controlResourceSetToReleaseList {
		A_SEQUENCE_OF(ControlResourceSetId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *controlResourceSetToReleaseList;
	struct PDCCH_Config__searchSpacesToAddModList {
		A_SEQUENCE_OF(struct SearchSpace) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *searchSpacesToAddModList;
	struct PDCCH_Config__searchSpacesToReleaseList {
		A_SEQUENCE_OF(SearchSpaceId_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *searchSpacesToReleaseList;
	struct SetupRelease	*downlinkPreemption	/* OPTIONAL */;
	struct SetupRelease	*tpc_PUSCH	/* OPTIONAL */;
	struct SetupRelease	*tpc_PUCCH	/* OPTIONAL */;
	struct SetupRelease	*tpc_SRS	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDCCH_Config_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDCCH_Config;
extern asn_SEQUENCE_specifics_t asn_SPC_PDCCH_Config_specs_1;
extern asn_TYPE_member_t asn_MBR_PDCCH_Config_1[8];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SetupRelease.h"
#include "ControlResourceSet.h"
#include "SearchSpace.h"

#endif	/* _PDCCH_Config_H_ */
#include "asn_internal.h"
