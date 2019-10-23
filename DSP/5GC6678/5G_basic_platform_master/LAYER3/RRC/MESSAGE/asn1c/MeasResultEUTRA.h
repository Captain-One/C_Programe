/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_MeasResultEUTRA_H_
#define	_MeasResultEUTRA_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PhysCellId.h"
#include "MeasQuantityResultsEUTRA.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct CGI_InfoEUTRA;

/* MeasResultEUTRA */
typedef struct MeasResultEUTRA {
	PhysCellId_t	 eutra_PhysCellId;
	MeasQuantityResultsEUTRA_t	 measResult;
	struct CGI_InfoEUTRA	*cgi_Info	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasResultEUTRA_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasResultEUTRA;
extern asn_SEQUENCE_specifics_t asn_SPC_MeasResultEUTRA_specs_1;
extern asn_TYPE_member_t asn_MBR_MeasResultEUTRA_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "CGI-InfoEUTRA.h"

#endif	/* _MeasResultEUTRA_H_ */
#include "asn_internal.h"
