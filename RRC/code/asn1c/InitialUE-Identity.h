/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_InitialUE_Identity_H_
#define	_InitialUE_Identity_H_


#include "asn_application.h"

/* Including external dependencies */
#include "S-TMSI.h"
#include "BIT_STRING.h"
#include "constr_CHOICE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum InitialUE_Identity_PR {
	InitialUE_Identity_PR_NOTHING,	/* No components present */
	InitialUE_Identity_PR_s_TMSI,
	InitialUE_Identity_PR_randomValue
} InitialUE_Identity_PR;

/* InitialUE-Identity */
typedef struct InitialUE_Identity {
	InitialUE_Identity_PR present;
	union InitialUE_Identity_u {
		S_TMSI_t	 s_TMSI;
		BIT_STRING_t	 randomValue;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} InitialUE_Identity_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InitialUE_Identity;

#ifdef __cplusplus
}
#endif

#endif	/* _InitialUE_Identity_H_ */
#include "asn_internal.h"
