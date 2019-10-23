/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "ReportConfigToAddMod.h"

static asn_oer_constraints_t asn_OER_type_reportConfig_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_reportConfig_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  0,  0,  0,  0 }	/* (0..0,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_reportConfig_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfigToAddMod__reportConfig, choice.reportConfigNR),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReportConfigNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportConfigNR"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfigToAddMod__reportConfig, choice.reportConfigInterRAT),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReportConfigInterRAT,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportConfigInterRAT"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_reportConfig_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* reportConfigNR */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* reportConfigInterRAT */
};
static asn_CHOICE_specifics_t asn_SPC_reportConfig_specs_3 = {
	sizeof(struct ReportConfigToAddMod__reportConfig),
	offsetof(struct ReportConfigToAddMod__reportConfig, _asn_ctx),
	offsetof(struct ReportConfigToAddMod__reportConfig, present),
	sizeof(((struct ReportConfigToAddMod__reportConfig *)0)->present),
	asn_MAP_reportConfig_tag2el_3,
	2,	/* Count of tags in the map */
	0, 0,
	1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_reportConfig_3 = {
	"reportConfig",
	"reportConfig",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_reportConfig_constr_3, &asn_PER_type_reportConfig_constr_3, CHOICE_constraint },
	asn_MBR_reportConfig_3,
	2,	/* Elements count */
	&asn_SPC_reportConfig_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ReportConfigToAddMod_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfigToAddMod, reportConfigId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReportConfigId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportConfigId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfigToAddMod, reportConfig),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_reportConfig_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportConfig"
		},
};
static const ber_tlv_tag_t asn_DEF_ReportConfigToAddMod_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ReportConfigToAddMod_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* reportConfigId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* reportConfig */
};
asn_SEQUENCE_specifics_t asn_SPC_ReportConfigToAddMod_specs_1 = {
	sizeof(struct ReportConfigToAddMod),
	offsetof(struct ReportConfigToAddMod, _asn_ctx),
	asn_MAP_ReportConfigToAddMod_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ReportConfigToAddMod = {
	"ReportConfigToAddMod",
	"ReportConfigToAddMod",
	&asn_OP_SEQUENCE,
	asn_DEF_ReportConfigToAddMod_tags_1,
	sizeof(asn_DEF_ReportConfigToAddMod_tags_1)
		/sizeof(asn_DEF_ReportConfigToAddMod_tags_1[0]), /* 1 */
	asn_DEF_ReportConfigToAddMod_tags_1,	/* Same as above */
	sizeof(asn_DEF_ReportConfigToAddMod_tags_1)
		/sizeof(asn_DEF_ReportConfigToAddMod_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ReportConfigToAddMod_1,
	2,	/* Elements count */
	&asn_SPC_ReportConfigToAddMod_specs_1	/* Additional specs */
};

