/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "MeasGapSharingConfig.h"

asn_TYPE_member_t asn_MBR_MeasGapSharingConfig_1[] = {
	{ ATF_POINTER, 3, offsetof(struct MeasGapSharingConfig, gapSharingFR2),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_SetupRelease_1076P26,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gapSharingFR2"
		},
	{ ATF_POINTER, 2, offsetof(struct MeasGapSharingConfig, gapSharingFR1),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_SetupRelease_1076P26,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gapSharingFR1"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasGapSharingConfig, gapSharingUE),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_SetupRelease_1076P26,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gapSharingUE"
		},
};
static const int asn_MAP_MeasGapSharingConfig_oms_1[] = { 0, 1, 2 };
static const ber_tlv_tag_t asn_DEF_MeasGapSharingConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasGapSharingConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* gapSharingFR2 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* gapSharingFR1 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* gapSharingUE */
};
asn_SEQUENCE_specifics_t asn_SPC_MeasGapSharingConfig_specs_1 = {
	sizeof(struct MeasGapSharingConfig),
	offsetof(struct MeasGapSharingConfig, _asn_ctx),
	asn_MAP_MeasGapSharingConfig_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_MeasGapSharingConfig_oms_1,	/* Optional members */
	1, 2,	/* Root/Additions */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MeasGapSharingConfig = {
	"MeasGapSharingConfig",
	"MeasGapSharingConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_MeasGapSharingConfig_tags_1,
	sizeof(asn_DEF_MeasGapSharingConfig_tags_1)
		/sizeof(asn_DEF_MeasGapSharingConfig_tags_1[0]), /* 1 */
	asn_DEF_MeasGapSharingConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasGapSharingConfig_tags_1)
		/sizeof(asn_DEF_MeasGapSharingConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MeasGapSharingConfig_1,
	3,	/* Elements count */
	&asn_SPC_MeasGapSharingConfig_specs_1	/* Additional specs */
};

