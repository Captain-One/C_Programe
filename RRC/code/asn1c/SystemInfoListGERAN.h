/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_SystemInfoListGERAN_H_
#define	_SystemInfoListGERAN_H_


#include "asn_application.h"

/* Including external dependencies */
#include "OCTET_STRING.h"
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"

#ifdef __cplusplus
extern "C" {
#endif

/* SystemInfoListGERAN */
typedef struct SystemInfoListGERAN {
	A_SEQUENCE_OF(OCTET_STRING_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SystemInfoListGERAN_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SystemInfoListGERAN;

#ifdef __cplusplus
}
#endif

#endif	/* _SystemInfoListGERAN_H_ */
#include "asn_internal.h"
