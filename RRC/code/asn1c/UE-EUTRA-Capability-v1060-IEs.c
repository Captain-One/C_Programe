/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "UE-EUTRA-Capability-v1060-IEs.h"

static const ber_tlv_tag_t asn_DEF_nonCriticalExtension_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SEQUENCE_specifics_t asn_SPC_nonCriticalExtension_specs_5 = {
	sizeof(struct UE_EUTRA_Capability_v1060_IEs__nonCriticalExtension),
	offsetof(struct UE_EUTRA_Capability_v1060_IEs__nonCriticalExtension, _asn_ctx),
	0,	/* No top level tags */
	0,	/* No tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_nonCriticalExtension_5 = {
	"nonCriticalExtension",
	"nonCriticalExtension",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_nonCriticalExtension_tags_5,
	sizeof(asn_DEF_nonCriticalExtension_tags_5)
		/sizeof(asn_DEF_nonCriticalExtension_tags_5[0]) - 1, /* 1 */
	asn_DEF_nonCriticalExtension_tags_5,	/* Same as above */
	sizeof(asn_DEF_nonCriticalExtension_tags_5)
		/sizeof(asn_DEF_nonCriticalExtension_tags_5[0]), /* 2 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	&asn_SPC_nonCriticalExtension_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_UE_EUTRA_Capability_v1060_IEs_1[] = {
	{ ATF_POINTER, 4, offsetof(struct UE_EUTRA_Capability_v1060_IEs, fdd_Add_UE_EUTRA_Capabilities_v1060),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_EUTRA_CapabilityAddXDD_Mode_v1060,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"fdd-Add-UE-EUTRA-Capabilities-v1060"
		},
	{ ATF_POINTER, 3, offsetof(struct UE_EUTRA_Capability_v1060_IEs, tdd_Add_UE_EUTRA_Capabilities_v1060),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UE_EUTRA_CapabilityAddXDD_Mode_v1060,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tdd-Add-UE-EUTRA-Capabilities-v1060"
		},
	{ ATF_POINTER, 2, offsetof(struct UE_EUTRA_Capability_v1060_IEs, rf_Parameters_v1060),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RF_Parameters_v1060,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rf-Parameters-v1060"
		},
	{ ATF_POINTER, 1, offsetof(struct UE_EUTRA_Capability_v1060_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		0,
		&asn_DEF_nonCriticalExtension_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtension"
		},
};
static const int asn_MAP_UE_EUTRA_Capability_v1060_IEs_oms_1[] = { 0, 1, 2, 3 };
static const ber_tlv_tag_t asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_UE_EUTRA_Capability_v1060_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* fdd-Add-UE-EUTRA-Capabilities-v1060 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* tdd-Add-UE-EUTRA-Capabilities-v1060 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* rf-Parameters-v1060 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* nonCriticalExtension */
};
static asn_SEQUENCE_specifics_t asn_SPC_UE_EUTRA_Capability_v1060_IEs_specs_1 = {
	sizeof(struct UE_EUTRA_Capability_v1060_IEs),
	offsetof(struct UE_EUTRA_Capability_v1060_IEs, _asn_ctx),
	asn_MAP_UE_EUTRA_Capability_v1060_IEs_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_UE_EUTRA_Capability_v1060_IEs_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_UE_EUTRA_Capability_v1060_IEs = {
	"UE-EUTRA-Capability-v1060-IEs",
	"UE-EUTRA-Capability-v1060-IEs",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1,
	sizeof(asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1)
		/sizeof(asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1[0]), /* 1 */
	asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1)
		/sizeof(asn_DEF_UE_EUTRA_Capability_v1060_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_UE_EUTRA_Capability_v1060_IEs_1,
	4,	/* Elements count */
	&asn_SPC_UE_EUTRA_Capability_v1060_IEs_specs_1	/* Additional specs */
};

