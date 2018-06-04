/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_InterFreqNeighCellInfo_H_
#define	_InterFreqNeighCellInfo_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PhysCellId.h"
#include "Q-OffsetRange.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* InterFreqNeighCellInfo */
typedef struct InterFreqNeighCellInfo {
	PhysCellId_t	 physCellId;
	Q_OffsetRange_t	 q_OffsetCell;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} InterFreqNeighCellInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_InterFreqNeighCellInfo;

#ifdef __cplusplus
}
#endif

#endif	/* _InterFreqNeighCellInfo_H_ */
#include "asn_internal.h"
