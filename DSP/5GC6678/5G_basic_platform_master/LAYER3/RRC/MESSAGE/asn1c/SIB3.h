/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_SIB3_H_
#define	_SIB3_H_


#include "asn_application.h"

/* Including external dependencies */
#include "OCTET_STRING.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct IntraFreqNeighCellList;
struct IntraFreqBlackCellList;

/* SIB3 */
typedef struct SIB3 {
	struct IntraFreqNeighCellList	*intraFreqNeighCellList	/* OPTIONAL */;
	struct IntraFreqBlackCellList	*intraFreqBlackCellList	/* OPTIONAL */;
	OCTET_STRING_t	*lateNonCriticalExtension	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SIB3_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SIB3;
extern asn_SEQUENCE_specifics_t asn_SPC_SIB3_specs_1;
extern asn_TYPE_member_t asn_MBR_SIB3_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "IntraFreqNeighCellList.h"
#include "IntraFreqBlackCellList.h"

#endif	/* _SIB3_H_ */
#include "asn_internal.h"
