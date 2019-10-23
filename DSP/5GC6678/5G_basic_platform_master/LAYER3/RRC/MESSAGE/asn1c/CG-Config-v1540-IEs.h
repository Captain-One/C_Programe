/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_CG_Config_v1540_IEs_H_
#define	_CG_Config_v1540_IEs_H_


#include "asn_application.h"

/* Including external dependencies */
#include "ARFCN-ValueNR.h"
#include "PhysCellId.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PH_TypeListSCG;
struct CG_Config_v1560_IEs;

/* CG-Config-v1540-IEs */
typedef struct CG_Config_v1540_IEs {
	ARFCN_ValueNR_t	*pSCellFrequency	/* OPTIONAL */;
	struct CG_Config_v1540_IEs__reportCGI_RequestNR {
		struct CG_Config_v1540_IEs__reportCGI_RequestNR__requestedCellInfo {
			ARFCN_ValueNR_t	 ssbFrequency;
			PhysCellId_t	 cellForWhichToReportCGI;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *requestedCellInfo;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *reportCGI_RequestNR;
	struct PH_TypeListSCG	*ph_InfoSCG	/* OPTIONAL */;
	struct CG_Config_v1560_IEs	*nonCriticalExtension	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CG_Config_v1540_IEs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CG_Config_v1540_IEs;
extern asn_SEQUENCE_specifics_t asn_SPC_CG_Config_v1540_IEs_specs_1;
extern asn_TYPE_member_t asn_MBR_CG_Config_v1540_IEs_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PH-TypeListSCG.h"
#include "CG-Config-v1560-IEs.h"

#endif	/* _CG_Config_v1540_IEs_H_ */
#include "asn_internal.h"
