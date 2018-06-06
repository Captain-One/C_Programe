/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_UplinkPowerControlDedicatedSCell_r10_H_
#define	_UplinkPowerControlDedicatedSCell_r10_H_


#include "asn_application.h"

/* Including external dependencies */
#include "NativeInteger.h"
#include "NativeEnumerated.h"
#include "BOOLEAN.h"
#include "FilterCoefficient.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UplinkPowerControlDedicatedSCell_r10__deltaMCS_Enabled_r10 {
	UplinkPowerControlDedicatedSCell_r10__deltaMCS_Enabled_r10_en0	= 0,
	UplinkPowerControlDedicatedSCell_r10__deltaMCS_Enabled_r10_en1	= 1
} e_UplinkPowerControlDedicatedSCell_r10__deltaMCS_Enabled_r10;
typedef enum UplinkPowerControlDedicatedSCell_r10__pathlossReferenceLinking_r10 {
	UplinkPowerControlDedicatedSCell_r10__pathlossReferenceLinking_r10_pCell	= 0,
	UplinkPowerControlDedicatedSCell_r10__pathlossReferenceLinking_r10_sCell	= 1
} e_UplinkPowerControlDedicatedSCell_r10__pathlossReferenceLinking_r10;

/* UplinkPowerControlDedicatedSCell-r10 */
typedef struct UplinkPowerControlDedicatedSCell_r10 {
	long	 p0_UE_PUSCH_r10;
	long	 deltaMCS_Enabled_r10;
	BOOLEAN_t	 accumulationEnabled_r10;
	long	 pSRS_Offset_r10;
	long	*pSRS_OffsetAp_r10	/* OPTIONAL */;
	FilterCoefficient_t	*filterCoefficient_r10	/* DEFAULT 4 */;
	long	 pathlossReferenceLinking_r10;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UplinkPowerControlDedicatedSCell_r10_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_deltaMCS_Enabled_r10_3;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_pathlossReferenceLinking_r10_10;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_UplinkPowerControlDedicatedSCell_r10;

#ifdef __cplusplus
}
#endif

#endif	/* _UplinkPowerControlDedicatedSCell_r10_H_ */
#include "asn_internal.h"
