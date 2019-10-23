/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_RLC_Parameters_H_
#define	_RLC_Parameters_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeEnumerated.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RLC_Parameters__am_WithShortSN {
	RLC_Parameters__am_WithShortSN_supported	= 0
} e_RLC_Parameters__am_WithShortSN;
typedef enum RLC_Parameters__um_WithShortSN {
	RLC_Parameters__um_WithShortSN_supported	= 0
} e_RLC_Parameters__um_WithShortSN;
typedef enum RLC_Parameters__um_WithLongSN {
	RLC_Parameters__um_WithLongSN_supported	= 0
} e_RLC_Parameters__um_WithLongSN;

/* RLC-Parameters */
typedef struct RLC_Parameters {
	long	*am_WithShortSN	/* OPTIONAL */;
	long	*um_WithShortSN	/* OPTIONAL */;
	long	*um_WithLongSN	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RLC_Parameters_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_am_WithShortSN_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_um_WithShortSN_4;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_um_WithLongSN_6;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RLC_Parameters;
extern asn_SEQUENCE_specifics_t asn_SPC_RLC_Parameters_specs_1;
extern asn_TYPE_member_t asn_MBR_RLC_Parameters_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _RLC_Parameters_H_ */
#include "asn_internal.h"
