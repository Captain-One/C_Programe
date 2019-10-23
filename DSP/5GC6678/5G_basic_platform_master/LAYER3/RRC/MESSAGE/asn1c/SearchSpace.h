/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#ifndef	_SearchSpace_H_
#define	_SearchSpace_H_


#include "asn_application.h"

/* Including external dependencies */
#include "SearchSpaceId.h"
#include "ControlResourceSetId.h"
#include "NativeInteger.h"
#include "BIT_STRING.h"
#include "NULL.h"
#include "constr_CHOICE.h"
#include "NativeEnumerated.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SearchSpace__monitoringSlotPeriodicityAndOffset_PR {
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_NOTHING,	/* No components present */
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl2,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl4,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl5,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl8,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl10,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl16,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl20,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl40,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl80,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl160,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl320,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl640,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl1280,
	SearchSpace__monitoringSlotPeriodicityAndOffset_PR_sl2560
} SearchSpace__monitoringSlotPeriodicityAndOffset_PR;
typedef enum SearchSpace__nrofCandidates__aggregationLevel1 {
	SearchSpace__nrofCandidates__aggregationLevel1_n0	= 0,
	SearchSpace__nrofCandidates__aggregationLevel1_n1	= 1,
	SearchSpace__nrofCandidates__aggregationLevel1_n2	= 2,
	SearchSpace__nrofCandidates__aggregationLevel1_n3	= 3,
	SearchSpace__nrofCandidates__aggregationLevel1_n4	= 4,
	SearchSpace__nrofCandidates__aggregationLevel1_n5	= 5,
	SearchSpace__nrofCandidates__aggregationLevel1_n6	= 6,
	SearchSpace__nrofCandidates__aggregationLevel1_n8	= 7
} e_SearchSpace__nrofCandidates__aggregationLevel1;
typedef enum SearchSpace__nrofCandidates__aggregationLevel2 {
	SearchSpace__nrofCandidates__aggregationLevel2_n0	= 0,
	SearchSpace__nrofCandidates__aggregationLevel2_n1	= 1,
	SearchSpace__nrofCandidates__aggregationLevel2_n2	= 2,
	SearchSpace__nrofCandidates__aggregationLevel2_n3	= 3,
	SearchSpace__nrofCandidates__aggregationLevel2_n4	= 4,
	SearchSpace__nrofCandidates__aggregationLevel2_n5	= 5,
	SearchSpace__nrofCandidates__aggregationLevel2_n6	= 6,
	SearchSpace__nrofCandidates__aggregationLevel2_n8	= 7
} e_SearchSpace__nrofCandidates__aggregationLevel2;
typedef enum SearchSpace__nrofCandidates__aggregationLevel4 {
	SearchSpace__nrofCandidates__aggregationLevel4_n0	= 0,
	SearchSpace__nrofCandidates__aggregationLevel4_n1	= 1,
	SearchSpace__nrofCandidates__aggregationLevel4_n2	= 2,
	SearchSpace__nrofCandidates__aggregationLevel4_n3	= 3,
	SearchSpace__nrofCandidates__aggregationLevel4_n4	= 4,
	SearchSpace__nrofCandidates__aggregationLevel4_n5	= 5,
	SearchSpace__nrofCandidates__aggregationLevel4_n6	= 6,
	SearchSpace__nrofCandidates__aggregationLevel4_n8	= 7
} e_SearchSpace__nrofCandidates__aggregationLevel4;
typedef enum SearchSpace__nrofCandidates__aggregationLevel8 {
	SearchSpace__nrofCandidates__aggregationLevel8_n0	= 0,
	SearchSpace__nrofCandidates__aggregationLevel8_n1	= 1,
	SearchSpace__nrofCandidates__aggregationLevel8_n2	= 2,
	SearchSpace__nrofCandidates__aggregationLevel8_n3	= 3,
	SearchSpace__nrofCandidates__aggregationLevel8_n4	= 4,
	SearchSpace__nrofCandidates__aggregationLevel8_n5	= 5,
	SearchSpace__nrofCandidates__aggregationLevel8_n6	= 6,
	SearchSpace__nrofCandidates__aggregationLevel8_n8	= 7
} e_SearchSpace__nrofCandidates__aggregationLevel8;
typedef enum SearchSpace__nrofCandidates__aggregationLevel16 {
	SearchSpace__nrofCandidates__aggregationLevel16_n0	= 0,
	SearchSpace__nrofCandidates__aggregationLevel16_n1	= 1,
	SearchSpace__nrofCandidates__aggregationLevel16_n2	= 2,
	SearchSpace__nrofCandidates__aggregationLevel16_n3	= 3,
	SearchSpace__nrofCandidates__aggregationLevel16_n4	= 4,
	SearchSpace__nrofCandidates__aggregationLevel16_n5	= 5,
	SearchSpace__nrofCandidates__aggregationLevel16_n6	= 6,
	SearchSpace__nrofCandidates__aggregationLevel16_n8	= 7
} e_SearchSpace__nrofCandidates__aggregationLevel16;
typedef enum SearchSpace__searchSpaceType_PR {
	SearchSpace__searchSpaceType_PR_NOTHING,	/* No components present */
	SearchSpace__searchSpaceType_PR_common,
	SearchSpace__searchSpaceType_PR_ue_Specific
} SearchSpace__searchSpaceType_PR;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel1 {
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel1_n1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel1_n2	= 1
} e_SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel1;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel2 {
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel2_n1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel2_n2	= 1
} e_SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel2;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel4 {
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel4_n1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel4_n2	= 1
} e_SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel4;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel8 {
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel8_n1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel8_n2	= 1
} e_SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel8;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel16 {
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel16_n1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel16_n2	= 1
} e_SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI__aggregationLevel16;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1 {
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl2	= 1,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl4	= 2,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl5	= 3,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl8	= 4,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl10	= 5,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl16	= 6,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1_sl20	= 7
} e_SearchSpace__searchSpaceType__common__dci_Format2_3__dummy1;
typedef enum SearchSpace__searchSpaceType__common__dci_Format2_3__dummy2 {
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy2_n1	= 0,
	SearchSpace__searchSpaceType__common__dci_Format2_3__dummy2_n2	= 1
} e_SearchSpace__searchSpaceType__common__dci_Format2_3__dummy2;
typedef enum SearchSpace__searchSpaceType__ue_Specific__dci_Formats {
	SearchSpace__searchSpaceType__ue_Specific__dci_Formats_formats0_0_And_1_0	= 0,
	SearchSpace__searchSpaceType__ue_Specific__dci_Formats_formats0_1_And_1_1	= 1
} e_SearchSpace__searchSpaceType__ue_Specific__dci_Formats;

/* SearchSpace */
typedef struct SearchSpace {
	SearchSpaceId_t	 searchSpaceId;
	ControlResourceSetId_t	*controlResourceSetId	/* OPTIONAL */;
	struct SearchSpace__monitoringSlotPeriodicityAndOffset {
		SearchSpace__monitoringSlotPeriodicityAndOffset_PR present;
		union SearchSpace__monitoringSlotPeriodicityAndOffset_u {
			NULL_t	 sl1;
			long	 sl2;
			long	 sl4;
			long	 sl5;
			long	 sl8;
			long	 sl10;
			long	 sl16;
			long	 sl20;
			long	 sl40;
			long	 sl80;
			long	 sl160;
			long	 sl320;
			long	 sl640;
			long	 sl1280;
			long	 sl2560;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *monitoringSlotPeriodicityAndOffset;
	long	*duration	/* OPTIONAL */;
	BIT_STRING_t	*monitoringSymbolsWithinSlot	/* OPTIONAL */;
	struct SearchSpace__nrofCandidates {
		long	 aggregationLevel1;
		long	 aggregationLevel2;
		long	 aggregationLevel4;
		long	 aggregationLevel8;
		long	 aggregationLevel16;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *nrofCandidates;
	struct SearchSpace__searchSpaceType {
		SearchSpace__searchSpaceType_PR present;
		union SearchSpace__searchSpaceType_u {
			struct SearchSpace__searchSpaceType__common {
				struct SearchSpace__searchSpaceType__common__dci_Format0_0_AndFormat1_0 {
					/*
					 * This type is extensible,
					 * possible extensions are below.
					 */
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *dci_Format0_0_AndFormat1_0;
				struct SearchSpace__searchSpaceType__common__dci_Format2_0 {
					struct SearchSpace__searchSpaceType__common__dci_Format2_0__nrofCandidates_SFI {
						long	*aggregationLevel1	/* OPTIONAL */;
						long	*aggregationLevel2	/* OPTIONAL */;
						long	*aggregationLevel4	/* OPTIONAL */;
						long	*aggregationLevel8	/* OPTIONAL */;
						long	*aggregationLevel16	/* OPTIONAL */;
						
						/* Context for parsing across buffer boundaries */
						asn_struct_ctx_t _asn_ctx;
					} nrofCandidates_SFI;
					/*
					 * This type is extensible,
					 * possible extensions are below.
					 */
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *dci_Format2_0;
				struct SearchSpace__searchSpaceType__common__dci_Format2_1 {
					/*
					 * This type is extensible,
					 * possible extensions are below.
					 */
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *dci_Format2_1;
				struct SearchSpace__searchSpaceType__common__dci_Format2_2 {
					/*
					 * This type is extensible,
					 * possible extensions are below.
					 */
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *dci_Format2_2;
				struct SearchSpace__searchSpaceType__common__dci_Format2_3 {
					long	*dummy1	/* OPTIONAL */;
					long	 dummy2;
					/*
					 * This type is extensible,
					 * possible extensions are below.
					 */
					
					/* Context for parsing across buffer boundaries */
					asn_struct_ctx_t _asn_ctx;
				} *dci_Format2_3;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} common;
			struct SearchSpace__searchSpaceType__ue_Specific {
				long	 dci_Formats;
				/*
				 * This type is extensible,
				 * possible extensions are below.
				 */
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} ue_Specific;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *searchSpaceType;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SearchSpace_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel1_23;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel2_32;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel4_41;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel8_50;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel16_59;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel1_74;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel2_77;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel4_80;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel8_83;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_aggregationLevel16_86;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_dummy1_95;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_dummy2_104;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_dci_Formats_109;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_SearchSpace;
extern asn_SEQUENCE_specifics_t asn_SPC_SearchSpace_specs_1;
extern asn_TYPE_member_t asn_MBR_SearchSpace_1[7];

#ifdef __cplusplus
}
#endif

#endif	/* _SearchSpace_H_ */
#include "asn_internal.h"
