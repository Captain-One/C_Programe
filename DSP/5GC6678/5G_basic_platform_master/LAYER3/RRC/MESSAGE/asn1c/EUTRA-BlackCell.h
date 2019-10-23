/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_EUTRA_BlackCell_H_
#define	_EUTRA_BlackCell_H_


#include "asn_application.h"

/* Including external dependencies */
#include "EUTRA-CellIndex.h"
#include "EUTRA-PhysCellIdRange.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* EUTRA-BlackCell */
typedef struct EUTRA_BlackCell {
	EUTRA_CellIndex_t	 cellIndexEUTRA;
	EUTRA_PhysCellIdRange_t	 physCellIdRange;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EUTRA_BlackCell_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EUTRA_BlackCell;
extern asn_SEQUENCE_specifics_t asn_SPC_EUTRA_BlackCell_specs_1;
extern asn_TYPE_member_t asn_MBR_EUTRA_BlackCell_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _EUTRA_BlackCell_H_ */
#include "asn_internal.h"
