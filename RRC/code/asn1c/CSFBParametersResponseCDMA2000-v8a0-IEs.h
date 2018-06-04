/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_CSFBParametersResponseCDMA2000_v8a0_IEs_H_
#define	_CSFBParametersResponseCDMA2000_v8a0_IEs_H_


#include "asn_application.h"

/* Including external dependencies */
#include "OCTET_STRING.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CSFBParametersResponseCDMA2000-v8a0-IEs */
typedef struct CSFBParametersResponseCDMA2000_v8a0_IEs {
	OCTET_STRING_t	*lateNonCriticalExtension	/* OPTIONAL */;
	struct CSFBParametersResponseCDMA2000_v8a0_IEs__nonCriticalExtension {
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonCriticalExtension;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CSFBParametersResponseCDMA2000_v8a0_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CSFBParametersResponseCDMA2000_v8a0_IEs;

#ifdef __cplusplus
}
#endif

#endif	/* _CSFBParametersResponseCDMA2000_v8a0_IEs_H_ */
#include "asn_internal.h"
