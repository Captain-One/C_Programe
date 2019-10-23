/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_PDSCH_ConfigCommon_H_
#define	_PDSCH_ConfigCommon_H_


#include "asn_application.h"

/* Including external dependencies */
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PDSCH_TimeDomainResourceAllocationList;

/* PDSCH-ConfigCommon */
typedef struct PDSCH_ConfigCommon {
	struct PDSCH_TimeDomainResourceAllocationList	*pdsch_TimeDomainAllocationList	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PDSCH_ConfigCommon_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PDSCH_ConfigCommon;
extern asn_SEQUENCE_specifics_t asn_SPC_PDSCH_ConfigCommon_specs_1;
extern asn_TYPE_member_t asn_MBR_PDSCH_ConfigCommon_1[1];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PDSCH-TimeDomainResourceAllocationList.h"

#endif	/* _PDSCH_ConfigCommon_H_ */
#include "asn_internal.h"
