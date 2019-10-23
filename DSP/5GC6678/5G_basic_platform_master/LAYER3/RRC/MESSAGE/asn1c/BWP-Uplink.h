/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_BWP_Uplink_H_
#define	_BWP_Uplink_H_


#include "asn_application.h"

/* Including external dependencies */
#include "BWP-Id.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct BWP_UplinkCommon;
struct BWP_UplinkDedicated;

/* BWP-Uplink */
typedef struct BWP_Uplink {
	BWP_Id_t	 bwp_Id;
	struct BWP_UplinkCommon	*bwp_Common	/* OPTIONAL */;
	struct BWP_UplinkDedicated	*bwp_Dedicated	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BWP_Uplink_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BWP_Uplink;
extern asn_SEQUENCE_specifics_t asn_SPC_BWP_Uplink_specs_1;
extern asn_TYPE_member_t asn_MBR_BWP_Uplink_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "BWP-UplinkCommon.h"
#include "BWP-UplinkDedicated.h"

#endif	/* _BWP_Uplink_H_ */
#include "asn_internal.h"
