/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_MeasResultEUTRA_H_
#define	_MeasResultEUTRA_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PhysCellId.h"
#include "CellGlobalIdEUTRA.h"
#include "TrackingAreaCode.h"
#include "constr_SEQUENCE.h"
#include "RSRP-Range.h"
#include "RSRQ-Range.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PLMN_IdentityList2;
struct AdditionalSI_Info_r9;

/* MeasResultEUTRA */
typedef struct MeasResultEUTRA {
	PhysCellId_t	 physCellId;
	struct MeasResultEUTRA__cgi_Info {
		CellGlobalIdEUTRA_t	 cellGlobalId;
		TrackingAreaCode_t	 trackingAreaCode;
		struct PLMN_IdentityList2	*plmn_IdentityList	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *cgi_Info;
	struct MeasResultEUTRA__measResult {
		RSRP_Range_t	*rsrpResult	/* OPTIONAL */;
		RSRQ_Range_t	*rsrqResult	/* OPTIONAL */;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
		struct AdditionalSI_Info_r9	*additionalSI_Info_r9	/* OPTIONAL */;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} measResult;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasResultEUTRA_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasResultEUTRA;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PLMN-IdentityList2.h"
#include "AdditionalSI-Info-r9.h"

#endif	/* _MeasResultEUTRA_H_ */
#include "asn_internal.h"
