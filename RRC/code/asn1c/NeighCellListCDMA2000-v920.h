/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_NeighCellListCDMA2000_v920_H_
#define	_NeighCellListCDMA2000_v920_H_


#include "asn_application.h"

/* Including external dependencies */
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct NeighCellCDMA2000_v920;

/* NeighCellListCDMA2000-v920 */
typedef struct NeighCellListCDMA2000_v920 {
	A_SEQUENCE_OF(struct NeighCellCDMA2000_v920) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NeighCellListCDMA2000_v920_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NeighCellListCDMA2000_v920;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "NeighCellCDMA2000-v920.h"

#endif	/* _NeighCellListCDMA2000_v920_H_ */
#include "asn_internal.h"
