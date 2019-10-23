/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_PH_UplinkCarrierMCG_H_
#define	_PH_UplinkCarrierMCG_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PH_UplinkCarrierMCG__ph_Type1or3 {
	PH_UplinkCarrierMCG__ph_Type1or3_type1	= 0,
	PH_UplinkCarrierMCG__ph_Type1or3_type3	= 1
} e_PH_UplinkCarrierMCG__ph_Type1or3;

/* PH-UplinkCarrierMCG */
typedef struct PH_UplinkCarrierMCG {
	long	 ph_Type1or3;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PH_UplinkCarrierMCG_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_ph_Type1or3_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_PH_UplinkCarrierMCG;
extern asn_SEQUENCE_specifics_t asn_SPC_PH_UplinkCarrierMCG_specs_1;
extern asn_TYPE_member_t asn_MBR_PH_UplinkCarrierMCG_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _PH_UplinkCarrierMCG_H_ */
#include "asn_internal.h"
