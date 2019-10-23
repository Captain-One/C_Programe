/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_UECapabilityEnquiry_H_
#define	_UECapabilityEnquiry_H_


#include "asn_application.h"

/* Including external dependencies */
#include "RRC-TransactionIdentifier.h"
#include "UECapabilityEnquiry-IEs.h"
#include "constr_SEQUENCE.h"
#include "constr_CHOICE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UECapabilityEnquiry__criticalExtensions_PR {
	UECapabilityEnquiry__criticalExtensions_PR_NOTHING,	/* No components present */
	UECapabilityEnquiry__criticalExtensions_PR_ueCapabilityEnquiry,
	UECapabilityEnquiry__criticalExtensions_PR_criticalExtensionsFuture
} UECapabilityEnquiry__criticalExtensions_PR;

/* UECapabilityEnquiry */
typedef struct UECapabilityEnquiry {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
	struct UECapabilityEnquiry__criticalExtensions {
		UECapabilityEnquiry__criticalExtensions_PR present;
		union UECapabilityEnquiry__criticalExtensions_u {
			UECapabilityEnquiry_IEs_t	 ueCapabilityEnquiry;
			struct UECapabilityEnquiry__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UECapabilityEnquiry_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UECapabilityEnquiry;
extern asn_SEQUENCE_specifics_t asn_SPC_UECapabilityEnquiry_specs_1;
extern asn_TYPE_member_t asn_MBR_UECapabilityEnquiry_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _UECapabilityEnquiry_H_ */
#include "asn_internal.h"
