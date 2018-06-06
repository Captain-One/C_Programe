/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_CSFBParametersResponseCDMA2000_H_
#define	_CSFBParametersResponseCDMA2000_H_


#include "asn_application.h"

/* Including external dependencies */
#include "RRC-TransactionIdentifier.h"
#include "CSFBParametersResponseCDMA2000-r8-IEs.h"
#include "constr_SEQUENCE.h"
#include "constr_CHOICE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CSFBParametersResponseCDMA2000__criticalExtensions_PR {
	CSFBParametersResponseCDMA2000__criticalExtensions_PR_NOTHING,	/* No components present */
	CSFBParametersResponseCDMA2000__criticalExtensions_PR_csfbParametersResponseCDMA2000_r8,
	CSFBParametersResponseCDMA2000__criticalExtensions_PR_criticalExtensionsFuture
} CSFBParametersResponseCDMA2000__criticalExtensions_PR;

/* CSFBParametersResponseCDMA2000 */
typedef struct CSFBParametersResponseCDMA2000 {
	RRC_TransactionIdentifier_t	 rrc_TransactionIdentifier;
	struct CSFBParametersResponseCDMA2000__criticalExtensions {
		CSFBParametersResponseCDMA2000__criticalExtensions_PR present;
		union CSFBParametersResponseCDMA2000__criticalExtensions_u {
			CSFBParametersResponseCDMA2000_r8_IEs_t	 csfbParametersResponseCDMA2000_r8;
			struct CSFBParametersResponseCDMA2000__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CSFBParametersResponseCDMA2000_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CSFBParametersResponseCDMA2000;

#ifdef __cplusplus
}
#endif

#endif	/* _CSFBParametersResponseCDMA2000_H_ */
#include "asn_internal.h"
