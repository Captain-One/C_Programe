/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_HandoverFromEUTRAPreparationRequest_v890_IEs_H_
#define	_HandoverFromEUTRAPreparationRequest_v890_IEs_H_


#include "asn_application.h"

/* Including external dependencies */
#include "OCTET_STRING.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct HandoverFromEUTRAPreparationRequest_v920_IEs;

/* HandoverFromEUTRAPreparationRequest-v890-IEs */
typedef struct HandoverFromEUTRAPreparationRequest_v890_IEs {
	OCTET_STRING_t	*lateNonCriticalExtension	/* OPTIONAL */;
	struct HandoverFromEUTRAPreparationRequest_v920_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} HandoverFromEUTRAPreparationRequest_v890_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_HandoverFromEUTRAPreparationRequest_v890_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "HandoverFromEUTRAPreparationRequest-v920-IEs.h"

#endif	/* _HandoverFromEUTRAPreparationRequest_v890_IEs_H_ */
#include "asn_internal.h"
