/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_ProximityIndication_r9_IEs_H_
#define	_ProximityIndication_r9_IEs_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"
#include "ARFCN-ValueEUTRA.h"
#include "ARFCN-ValueUTRA.h"
#include "constr_CHOICE.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ProximityIndication_r9_IEs__type_r9 {
	ProximityIndication_r9_IEs__type_r9_entering	= 0,
	ProximityIndication_r9_IEs__type_r9_leaving	= 1
} e_ProximityIndication_r9_IEs__type_r9;
typedef enum ProximityIndication_r9_IEs__carrierFreq_r9_PR {
	ProximityIndication_r9_IEs__carrierFreq_r9_PR_NOTHING,	/* No components present */
	ProximityIndication_r9_IEs__carrierFreq_r9_PR_eutra_r9,
	ProximityIndication_r9_IEs__carrierFreq_r9_PR_utra_r9,
	/* Extensions may appear below */
	
} ProximityIndication_r9_IEs__carrierFreq_r9_PR;

/* Forward declarations */
struct ProximityIndication_v930_IEs;

/* ProximityIndication-r9-IEs */
typedef struct ProximityIndication_r9_IEs {
	long	 type_r9;
	struct ProximityIndication_r9_IEs__carrierFreq_r9 {
		ProximityIndication_r9_IEs__carrierFreq_r9_PR present;
		union ProximityIndication_r9_IEs__carrierFreq_r9_u {
			ARFCN_ValueEUTRA_t	 eutra_r9;
			ARFCN_ValueUTRA_t	 utra_r9;
			/*
			 * This type is extensible,
			 * possible extensions are below.
			 */
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} carrierFreq_r9;
	struct ProximityIndication_v930_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ProximityIndication_r9_IEs_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_type_r9_2;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_ProximityIndication_r9_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ProximityIndication-v930-IEs.h"

#endif	/* _ProximityIndication_r9_IEs_H_ */
#include "asn_internal.h"
