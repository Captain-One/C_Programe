/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_UERadioPagingInformation_IEs_H_
#define	_UERadioPagingInformation_IEs_H_


#include "asn_application.h"

/* Including external dependencies */
#include "FreqBandIndicatorNR.h"
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* UERadioPagingInformation-IEs */
typedef struct UERadioPagingInformation_IEs {
	struct UERadioPagingInformation_IEs__supportedBandListNRForPaging {
		A_SEQUENCE_OF(FreqBandIndicatorNR_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *supportedBandListNRForPaging;
	struct UERadioPagingInformation_IEs__nonCriticalExtension {
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nonCriticalExtension;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UERadioPagingInformation_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UERadioPagingInformation_IEs;
extern asn_SEQUENCE_specifics_t asn_SPC_UERadioPagingInformation_IEs_specs_1;
extern asn_TYPE_member_t asn_MBR_UERadioPagingInformation_IEs_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _UERadioPagingInformation_IEs_H_ */
#include "asn_internal.h"
