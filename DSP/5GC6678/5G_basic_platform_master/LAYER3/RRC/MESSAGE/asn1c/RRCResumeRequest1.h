/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_RRCResumeRequest1_H_
#define	_RRCResumeRequest1_H_


#include "asn_application.h"

/* Including external dependencies */
#include "RRCResumeRequest1-IEs.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* RRCResumeRequest1 */
typedef struct RRCResumeRequest1 {
	RRCResumeRequest1_IEs_t	 rrcResumeRequest1;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RRCResumeRequest1_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RRCResumeRequest1;
extern asn_SEQUENCE_specifics_t asn_SPC_RRCResumeRequest1_specs_1;
extern asn_TYPE_member_t asn_MBR_RRCResumeRequest1_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _RRCResumeRequest1_H_ */
#include "asn_internal.h"
