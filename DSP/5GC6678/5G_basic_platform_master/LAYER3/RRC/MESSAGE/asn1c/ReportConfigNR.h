/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_ReportConfigNR_H_
#define	_ReportConfigNR_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PeriodicalReportConfig.h"
#include "EventTriggerConfig.h"
#include "ReportCGI.h"
#include "ReportSFTD-NR.h"
#include "constr_CHOICE.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ReportConfigNR__reportType_PR {
	ReportConfigNR__reportType_PR_NOTHING,	/* No components present */
	ReportConfigNR__reportType_PR_periodical,
	ReportConfigNR__reportType_PR_eventTriggered,
	/* Extensions may appear below */
	ReportConfigNR__reportType_PR_reportCGI,
	ReportConfigNR__reportType_PR_reportSFTD
} ReportConfigNR__reportType_PR;

/* ReportConfigNR */
typedef struct ReportConfigNR {
	struct ReportConfigNR__reportType {
		ReportConfigNR__reportType_PR present;
		union ReportConfigNR__reportType_u {
			PeriodicalReportConfig_t	 periodical;
			EventTriggerConfig_t	 eventTriggered;
			/*
			 * This type is extensible,
			 * possible extensions are below.
			 */
			ReportCGI_t	 reportCGI;
			ReportSFTD_NR_t	 reportSFTD;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} reportType;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ReportConfigNR_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReportConfigNR;
extern asn_SEQUENCE_specifics_t asn_SPC_ReportConfigNR_specs_1;
extern asn_TYPE_member_t asn_MBR_ReportConfigNR_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _ReportConfigNR_H_ */
#include "asn_internal.h"
