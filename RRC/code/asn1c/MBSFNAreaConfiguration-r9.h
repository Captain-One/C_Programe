/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_MBSFNAreaConfiguration_r9_H_
#define	_MBSFNAreaConfiguration_r9_H_


#include "asn_application.h"

/* Including external dependencies */
#include "CommonSF-AllocPatternList-r9.h"
#include "NativeEnumerated.h"
#include "PMCH-InfoList-r9.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9 {
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf4	= 0,
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf8	= 1,
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf16	= 2,
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf32	= 3,
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf64	= 4,
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf128	= 5,
	MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9_rf256	= 6
} e_MBSFNAreaConfiguration_r9__commonSF_AllocPeriod_r9;

/* Forward declarations */
struct MBSFNAreaConfiguration_v930_IEs;

/* MBSFNAreaConfiguration-r9 */
typedef struct MBSFNAreaConfiguration_r9 {
	CommonSF_AllocPatternList_r9_t	 commonSF_Alloc_r9;
	long	 commonSF_AllocPeriod_r9;
	PMCH_InfoList_r9_t	 pmch_InfoList_r9;
	struct MBSFNAreaConfiguration_v930_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MBSFNAreaConfiguration_r9_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_commonSF_AllocPeriod_r9_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_MBSFNAreaConfiguration_r9;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MBSFNAreaConfiguration-v930-IEs.h"

#endif	/* _MBSFNAreaConfiguration_r9_H_ */
#include "asn_internal.h"
