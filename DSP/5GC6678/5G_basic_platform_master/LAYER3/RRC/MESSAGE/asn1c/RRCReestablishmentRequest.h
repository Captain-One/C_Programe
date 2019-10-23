/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_RRCReestablishmentRequest_H_
#define	_RRCReestablishmentRequest_H_


#include "asn_application.h"

/* Including external dependencies */
#include "RRCReestablishmentRequest-IEs.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* RRCReestablishmentRequest */
typedef struct RRCReestablishmentRequest {
	RRCReestablishmentRequest_IEs_t	 rrcReestablishmentRequest;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCReestablishmentRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCReestablishmentRequest;
extern asn_SEQUENCE_specifics_t asn_SPC_RRCReestablishmentRequest_specs_1;
extern asn_TYPE_member_t asn_MBR_RRCReestablishmentRequest_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _RRCReestablishmentRequest_H_ */
#include "asn_internal.h"
