/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_MeasIdToAddMod_H_
#define	_MeasIdToAddMod_H_


#include "asn_application.h"

/* Including external dependencies */
#include "MeasId.h"
#include "MeasObjectId.h"
#include "ReportConfigId.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MeasIdToAddMod */
typedef struct MeasIdToAddMod {
	MeasId_t	 measId;
	MeasObjectId_t	 measObjectId;
	ReportConfigId_t	 reportConfigId;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasIdToAddMod_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasIdToAddMod;
extern asn_SEQUENCE_specifics_t asn_SPC_MeasIdToAddMod_specs_1;
extern asn_TYPE_member_t asn_MBR_MeasIdToAddMod_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _MeasIdToAddMod_H_ */
#include "asn_internal.h"
