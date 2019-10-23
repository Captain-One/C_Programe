/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_PUSCH_PathlossReferenceRS_H_
#define	_PUSCH_PathlossReferenceRS_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PUSCH-PathlossReferenceRS-Id.h"
#include "SSB-Index.h"
#include "NZP-CSI-RS-ResourceId.h"
#include "constr_CHOICE.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PUSCH_PathlossReferenceRS__referenceSignal_PR {
	PUSCH_PathlossReferenceRS__referenceSignal_PR_NOTHING,	/* No components present */
	PUSCH_PathlossReferenceRS__referenceSignal_PR_ssb_Index,
	PUSCH_PathlossReferenceRS__referenceSignal_PR_csi_RS_Index
} PUSCH_PathlossReferenceRS__referenceSignal_PR;

/* PUSCH-PathlossReferenceRS */
typedef struct PUSCH_PathlossReferenceRS {
	PUSCH_PathlossReferenceRS_Id_t	 pusch_PathlossReferenceRS_Id;
	struct PUSCH_PathlossReferenceRS__referenceSignal {
		PUSCH_PathlossReferenceRS__referenceSignal_PR present;
		union PUSCH_PathlossReferenceRS__referenceSignal_u {
			SSB_Index_t	 ssb_Index;
			NZP_CSI_RS_ResourceId_t	 csi_RS_Index;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} referenceSignal;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PUSCH_PathlossReferenceRS_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PUSCH_PathlossReferenceRS;
extern asn_SEQUENCE_specifics_t asn_SPC_PUSCH_PathlossReferenceRS_specs_1;
extern asn_TYPE_member_t asn_MBR_PUSCH_PathlossReferenceRS_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _PUSCH_PathlossReferenceRS_H_ */
#include "asn_internal.h"
