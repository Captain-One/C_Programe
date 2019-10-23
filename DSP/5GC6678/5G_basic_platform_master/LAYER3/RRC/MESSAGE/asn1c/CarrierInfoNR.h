/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_CarrierInfoNR_H_
#define	_CarrierInfoNR_H_


#include "asn_application.h"

/* Including external dependencies */
#include "ARFCN-ValueNR.h"
#include "SubcarrierSpacing.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SSB_MTC;

/* CarrierInfoNR */
typedef struct CarrierInfoNR {
	ARFCN_ValueNR_t	 carrierFreq;
	SubcarrierSpacing_t	 ssbSubcarrierSpacing;
	struct SSB_MTC	*smtc	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CarrierInfoNR_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CarrierInfoNR;
extern asn_SEQUENCE_specifics_t asn_SPC_CarrierInfoNR_specs_1;
extern asn_TYPE_member_t asn_MBR_CarrierInfoNR_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SSB-MTC.h"

#endif	/* _CarrierInfoNR_H_ */
#include "asn_internal.h"
