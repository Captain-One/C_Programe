/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_PhysCellIdRange_H_
#define	_PhysCellIdRange_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PhysCellId.h"
#include "NativeEnumerated.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PhysCellIdRange__range {
	PhysCellIdRange__range_n4	= 0,
	PhysCellIdRange__range_n8	= 1,
	PhysCellIdRange__range_n12	= 2,
	PhysCellIdRange__range_n16	= 3,
	PhysCellIdRange__range_n24	= 4,
	PhysCellIdRange__range_n32	= 5,
	PhysCellIdRange__range_n48	= 6,
	PhysCellIdRange__range_n64	= 7,
	PhysCellIdRange__range_n84	= 8,
	PhysCellIdRange__range_n96	= 9,
	PhysCellIdRange__range_n128	= 10,
	PhysCellIdRange__range_n168	= 11,
	PhysCellIdRange__range_n252	= 12,
	PhysCellIdRange__range_n504	= 13,
	PhysCellIdRange__range_spare2	= 14,
	PhysCellIdRange__range_spare1	= 15
} e_PhysCellIdRange__range;

/* PhysCellIdRange */
typedef struct PhysCellIdRange {
	PhysCellId_t	 start;
	long	*range	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PhysCellIdRange_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_range_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_PhysCellIdRange;

#ifdef __cplusplus
}
#endif

#endif	/* _PhysCellIdRange_H_ */
#include "asn_internal.h"
