/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_EUTRA_ParametersXDD_Diff_H_
#define	_EUTRA_ParametersXDD_Diff_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum EUTRA_ParametersXDD_Diff__rsrqMeasWidebandEUTRA {
	EUTRA_ParametersXDD_Diff__rsrqMeasWidebandEUTRA_supported	= 0
} e_EUTRA_ParametersXDD_Diff__rsrqMeasWidebandEUTRA;

/* EUTRA-ParametersXDD-Diff */
typedef struct EUTRA_ParametersXDD_Diff {
	long	*rsrqMeasWidebandEUTRA	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EUTRA_ParametersXDD_Diff_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_rsrqMeasWidebandEUTRA_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_EUTRA_ParametersXDD_Diff;
extern asn_SEQUENCE_specifics_t asn_SPC_EUTRA_ParametersXDD_Diff_specs_1;
extern asn_TYPE_member_t asn_MBR_EUTRA_ParametersXDD_Diff_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _EUTRA_ParametersXDD_Diff_H_ */
#include "asn_internal.h"
