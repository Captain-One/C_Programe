/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_CQI_ReportConfigSCell_r10_H_
#define	_CQI_ReportConfigSCell_r10_H_


#include "asn_application.h"

/* Including external dependencies */
#include "CQI-ReportModeAperiodic.h"
#include "NativeInteger.h"
#include "NativeEnumerated.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CQI_ReportConfigSCell_r10__pmi_RI_Report_r10 {
	CQI_ReportConfigSCell_r10__pmi_RI_Report_r10_setup	= 0
} e_CQI_ReportConfigSCell_r10__pmi_RI_Report_r10;

/* Forward declarations */
struct CQI_ReportPeriodic_r10;

/* CQI-ReportConfigSCell-r10 */
typedef struct CQI_ReportConfigSCell_r10 {
	CQI_ReportModeAperiodic_t	*cqi_ReportModeAperiodic_r10	/* OPTIONAL */;
	long	 nomPDSCH_RS_EPRE_Offset_r10;
	struct CQI_ReportPeriodic_r10	*cqi_ReportPeriodicSCell_r10	/* OPTIONAL */;
	long	*pmi_RI_Report_r10	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CQI_ReportConfigSCell_r10_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_pmi_RI_Report_r10_5;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_CQI_ReportConfigSCell_r10;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "CQI-ReportPeriodic-r10.h"

#endif	/* _CQI_ReportConfigSCell_r10_H_ */
#include "asn_internal.h"
