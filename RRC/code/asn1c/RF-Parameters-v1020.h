/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_RF_Parameters_v1020_H_
#define	_RF_Parameters_v1020_H_


#include "asn_application.h"

/* Including external dependencies */
#include "SupportedBandCombination-r10.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* RF-Parameters-v1020 */
typedef struct RF_Parameters_v1020 {
	SupportedBandCombination_r10_t	 supportedBandCombination_r10;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RF_Parameters_v1020_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RF_Parameters_v1020;

#ifdef __cplusplus
}
#endif

#endif	/* _RF_Parameters_v1020_H_ */
#include "asn_internal.h"
