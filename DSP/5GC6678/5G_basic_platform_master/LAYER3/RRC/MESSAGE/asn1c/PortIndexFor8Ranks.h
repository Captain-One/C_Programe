/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_PortIndexFor8Ranks_H_
#define	_PortIndexFor8Ranks_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NULL.h"
#include "PortIndex8.h"
#include "asn_SEQUENCE_OF.h"
#include "constr_SEQUENCE_OF.h"
#include "constr_SEQUENCE.h"
#include "PortIndex4.h"
#include "PortIndex2.h"
#include "constr_CHOICE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum PortIndexFor8Ranks_PR {
	PortIndexFor8Ranks_PR_NOTHING,	/* No components present */
	PortIndexFor8Ranks_PR_portIndex8,
	PortIndexFor8Ranks_PR_portIndex4,
	PortIndexFor8Ranks_PR_portIndex2,
	PortIndexFor8Ranks_PR_portIndex1
} PortIndexFor8Ranks_PR;

/* PortIndexFor8Ranks */
typedef struct PortIndexFor8Ranks {
	PortIndexFor8Ranks_PR present;
	union PortIndexFor8Ranks_u {
		struct PortIndexFor8Ranks__portIndex8 {
			PortIndex8_t	*rank1_8	/* OPTIONAL */;
			struct PortIndexFor8Ranks__portIndex8__rank2_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank2_8;
			struct PortIndexFor8Ranks__portIndex8__rank3_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank3_8;
			struct PortIndexFor8Ranks__portIndex8__rank4_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank4_8;
			struct PortIndexFor8Ranks__portIndex8__rank5_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank5_8;
			struct PortIndexFor8Ranks__portIndex8__rank6_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank6_8;
			struct PortIndexFor8Ranks__portIndex8__rank7_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank7_8;
			struct PortIndexFor8Ranks__portIndex8__rank8_8 {
				A_SEQUENCE_OF(PortIndex8_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank8_8;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} portIndex8;
		struct PortIndexFor8Ranks__portIndex4 {
			PortIndex4_t	*rank1_4	/* OPTIONAL */;
			struct PortIndexFor8Ranks__portIndex4__rank2_4 {
				A_SEQUENCE_OF(PortIndex4_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank2_4;
			struct PortIndexFor8Ranks__portIndex4__rank3_4 {
				A_SEQUENCE_OF(PortIndex4_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank3_4;
			struct PortIndexFor8Ranks__portIndex4__rank4_4 {
				A_SEQUENCE_OF(PortIndex4_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank4_4;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} portIndex4;
		struct PortIndexFor8Ranks__portIndex2 {
			PortIndex2_t	*rank1_2	/* OPTIONAL */;
			struct PortIndexFor8Ranks__portIndex2__rank2_2 {
				A_SEQUENCE_OF(PortIndex2_t) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} *rank2_2;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} portIndex2;
		NULL_t	 portIndex1;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PortIndexFor8Ranks_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PortIndexFor8Ranks;
extern asn_CHOICE_specifics_t asn_SPC_PortIndexFor8Ranks_specs_1;
extern asn_TYPE_member_t asn_MBR_PortIndexFor8Ranks_1[4];
extern asn_per_constraints_t asn_PER_type_PortIndexFor8Ranks_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _PortIndexFor8Ranks_H_ */
#include "asn_internal.h"
