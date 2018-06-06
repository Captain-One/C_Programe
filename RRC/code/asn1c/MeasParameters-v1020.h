/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_MeasParameters_v1020_H_
#define	_MeasParameters_v1020_H_


#include "asn_application.h"

/* Including external dependencies */
#include "BandCombinationListEUTRA-r10.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MeasParameters-v1020 */
typedef struct MeasParameters_v1020 {
	BandCombinationListEUTRA_r10_t	 bandCombinationListEUTRA_r10;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasParameters_v1020_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasParameters_v1020;

#ifdef __cplusplus
}
#endif

#endif	/* _MeasParameters_v1020_H_ */
#include "asn_internal.h"
