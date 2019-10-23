/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_MobilityStateParameters_H_
#define	_MobilityStateParameters_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"
#include "NativeInteger.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MobilityStateParameters__t_Evaluation {
	MobilityStateParameters__t_Evaluation_s30	= 0,
	MobilityStateParameters__t_Evaluation_s60	= 1,
	MobilityStateParameters__t_Evaluation_s120	= 2,
	MobilityStateParameters__t_Evaluation_s180	= 3,
	MobilityStateParameters__t_Evaluation_s240	= 4,
	MobilityStateParameters__t_Evaluation_spare3	= 5,
	MobilityStateParameters__t_Evaluation_spare2	= 6,
	MobilityStateParameters__t_Evaluation_spare1	= 7
} e_MobilityStateParameters__t_Evaluation;
typedef enum MobilityStateParameters__t_HystNormal {
	MobilityStateParameters__t_HystNormal_s30	= 0,
	MobilityStateParameters__t_HystNormal_s60	= 1,
	MobilityStateParameters__t_HystNormal_s120	= 2,
	MobilityStateParameters__t_HystNormal_s180	= 3,
	MobilityStateParameters__t_HystNormal_s240	= 4,
	MobilityStateParameters__t_HystNormal_spare3	= 5,
	MobilityStateParameters__t_HystNormal_spare2	= 6,
	MobilityStateParameters__t_HystNormal_spare1	= 7
} e_MobilityStateParameters__t_HystNormal;

/* MobilityStateParameters */
typedef struct MobilityStateParameters {
	long	 t_Evaluation;
	long	 t_HystNormal;
	long	 n_CellChangeMedium;
	long	 n_CellChangeHigh;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MobilityStateParameters_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_t_Evaluation_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_t_HystNormal_11;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_MobilityStateParameters;
extern asn_SEQUENCE_specifics_t asn_SPC_MobilityStateParameters_specs_1;
extern asn_TYPE_member_t asn_MBR_MobilityStateParameters_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _MobilityStateParameters_H_ */
#include "asn_internal.h"
