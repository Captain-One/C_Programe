/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_BandCombinationList_v1550_H_
#define	_BandCombinationList_v1550_H_


#include "asn_application.h"

/* Including external dependencies */
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct BandCombination_v1550;

/* BandCombinationList-v1550 */
typedef struct BandCombinationList_v1550 {
	A_SEQUENCE_OF(struct BandCombination_v1550) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BandCombinationList_v1550_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BandCombinationList_v1550;
extern asn_SET_OF_specifics_t asn_SPC_BandCombinationList_v1550_specs_1;
extern asn_TYPE_member_t asn_MBR_BandCombinationList_v1550_1[1];
extern asn_per_constraints_t asn_PER_type_BandCombinationList_v1550_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "BandCombination-v1550.h"

#endif	/* _BandCombinationList_v1550_H_ */
#include "asn_internal.h"
