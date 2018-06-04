/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_CountingRequestList_r10_H_
#define	_CountingRequestList_r10_H_


#include "asn_application.h"

/* Including external dependencies */
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct CountingRequestInfo_r10;

/* CountingRequestList-r10 */
typedef struct CountingRequestList_r10 {
	A_SEQUENCE_OF(struct CountingRequestInfo_r10) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CountingRequestList_r10_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CountingRequestList_r10;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "CountingRequestInfo-r10.h"

#endif	/* _CountingRequestList_r10_H_ */
#include "asn_internal.h"
