/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_LocationMeasurementIndication_H_
#define	_LocationMeasurementIndication_H_


#include "asn_application.h"

/* Including external dependencies */
#include "LocationMeasurementIndication-IEs.h"
#include "constr_SEQUENCE.h"
#include "constr_CHOICE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LocationMeasurementIndication__criticalExtensions_PR {
	LocationMeasurementIndication__criticalExtensions_PR_NOTHING,	/* No components present */
	LocationMeasurementIndication__criticalExtensions_PR_locationMeasurementIndication,
	LocationMeasurementIndication__criticalExtensions_PR_criticalExtensionsFuture
} LocationMeasurementIndication__criticalExtensions_PR;

/* LocationMeasurementIndication */
typedef struct LocationMeasurementIndication {
	struct LocationMeasurementIndication__criticalExtensions {
		LocationMeasurementIndication__criticalExtensions_PR present;
		union LocationMeasurementIndication__criticalExtensions_u {
			LocationMeasurementIndication_IEs_t	 locationMeasurementIndication;
			struct LocationMeasurementIndication__criticalExtensions__criticalExtensionsFuture {
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} criticalExtensionsFuture;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} criticalExtensions;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LocationMeasurementIndication_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LocationMeasurementIndication;
extern asn_SEQUENCE_specifics_t asn_SPC_LocationMeasurementIndication_specs_1;
extern asn_TYPE_member_t asn_MBR_LocationMeasurementIndication_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _LocationMeasurementIndication_H_ */
#include "asn_internal.h"
