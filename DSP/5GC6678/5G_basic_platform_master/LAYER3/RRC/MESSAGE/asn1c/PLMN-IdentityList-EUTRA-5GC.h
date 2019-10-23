/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_PLMN_IdentityList_EUTRA_5GC_H_
#define	_PLMN_IdentityList_EUTRA_5GC_H_


#include "asn_application.h"

/* Including external dependencies */
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PLMN_Identity_EUTRA_5GC;

/* PLMN-IdentityList-EUTRA-5GC */
typedef struct PLMN_IdentityList_EUTRA_5GC {
	A_SEQUENCE_OF(struct PLMN_Identity_EUTRA_5GC) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PLMN_IdentityList_EUTRA_5GC_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PLMN_IdentityList_EUTRA_5GC;
extern asn_SET_OF_specifics_t asn_SPC_PLMN_IdentityList_EUTRA_5GC_specs_1;
extern asn_TYPE_member_t asn_MBR_PLMN_IdentityList_EUTRA_5GC_1[1];
extern asn_per_constraints_t asn_PER_type_PLMN_IdentityList_EUTRA_5GC_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PLMN-Identity-EUTRA-5GC.h"

#endif	/* _PLMN_IdentityList_EUTRA_5GC_H_ */
#include "asn_internal.h"
