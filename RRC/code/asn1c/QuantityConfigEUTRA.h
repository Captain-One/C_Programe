/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_QuantityConfigEUTRA_H_
#define	_QuantityConfigEUTRA_H_


#include "asn_application.h"

/* Including external dependencies */
#include "FilterCoefficient.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* QuantityConfigEUTRA */
typedef struct QuantityConfigEUTRA {
	FilterCoefficient_t	*filterCoefficientRSRP	/* DEFAULT 4 */;
	FilterCoefficient_t	*filterCoefficientRSRQ	/* DEFAULT 4 */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} QuantityConfigEUTRA_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_QuantityConfigEUTRA;

#ifdef __cplusplus
}
#endif

#endif	/* _QuantityConfigEUTRA_H_ */
#include "asn_internal.h"
