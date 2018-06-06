/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_S_TMSI_H_
#define	_S_TMSI_H_


#include "asn_application.h"

/* Including external dependencies */
#include "MMEC.h"
#include "BIT_STRING.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* S-TMSI */
typedef struct S_TMSI {
	MMEC_t	 mmec;
	BIT_STRING_t	 m_TMSI;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} S_TMSI_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_S_TMSI;

#ifdef __cplusplus
}
#endif

#endif	/* _S_TMSI_H_ */
#include "asn_internal.h"
