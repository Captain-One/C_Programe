/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_UplinkTxDirectCurrentCell_H_
#define	_UplinkTxDirectCurrentCell_H_


#include "asn_application.h"

/* Including external dependencies */
#include "ServCellIndex.h"
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct UplinkTxDirectCurrentBWP;

/* UplinkTxDirectCurrentCell */
typedef struct UplinkTxDirectCurrentCell {
	ServCellIndex_t	 servCellIndex;
	struct UplinkTxDirectCurrentCell__uplinkDirectCurrentBWP {
		A_SEQUENCE_OF(struct UplinkTxDirectCurrentBWP) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} uplinkDirectCurrentBWP;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct UplinkTxDirectCurrentCell__uplinkDirectCurrentBWP_SUL {
		A_SEQUENCE_OF(struct UplinkTxDirectCurrentBWP) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *uplinkDirectCurrentBWP_SUL;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UplinkTxDirectCurrentCell_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UplinkTxDirectCurrentCell;
extern asn_SEQUENCE_specifics_t asn_SPC_UplinkTxDirectCurrentCell_specs_1;
extern asn_TYPE_member_t asn_MBR_UplinkTxDirectCurrentCell_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "UplinkTxDirectCurrentBWP.h"

#endif	/* _UplinkTxDirectCurrentCell_H_ */
#include "asn_internal.h"
