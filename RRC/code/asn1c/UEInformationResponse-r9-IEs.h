/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_UEInformationResponse_r9_IEs_H_
#define	_UEInformationResponse_r9_IEs_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeInteger.h"
#include "BOOLEAN.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct RLF_Report_r9;
struct UEInformationResponse_v930_IEs;

/* UEInformationResponse-r9-IEs */
typedef struct UEInformationResponse_r9_IEs {
	struct UEInformationResponse_r9_IEs__rach_Report_r9 {
		long	 numberOfPreamblesSent_r9;
		BOOLEAN_t	 contentionDetected_r9;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *rach_Report_r9;
	struct RLF_Report_r9	*rlf_Report_r9	/* OPTIONAL */;
	struct UEInformationResponse_v930_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UEInformationResponse_r9_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UEInformationResponse_r9_IEs;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "RLF-Report-r9.h"
#include "UEInformationResponse-v930-IEs.h"

#endif	/* _UEInformationResponse_r9_IEs_H_ */
#include "asn_internal.h"
