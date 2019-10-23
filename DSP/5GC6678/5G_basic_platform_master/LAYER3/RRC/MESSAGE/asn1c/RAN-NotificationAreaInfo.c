/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "RAN-NotificationAreaInfo.h"

static asn_oer_constraints_t asn_OER_type_RAN_NotificationAreaInfo_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_RAN_NotificationAreaInfo_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_RAN_NotificationAreaInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RAN_NotificationAreaInfo, choice.cellList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PLMN_RAN_AreaCellList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cellList"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RAN_NotificationAreaInfo, choice.ran_AreaConfigList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PLMN_RAN_AreaConfigList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ran-AreaConfigList"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_RAN_NotificationAreaInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cellList */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* ran-AreaConfigList */
};
asn_CHOICE_specifics_t asn_SPC_RAN_NotificationAreaInfo_specs_1 = {
	sizeof(struct RAN_NotificationAreaInfo),
	offsetof(struct RAN_NotificationAreaInfo, _asn_ctx),
	offsetof(struct RAN_NotificationAreaInfo, present),
	sizeof(((struct RAN_NotificationAreaInfo *)0)->present),
	asn_MAP_RAN_NotificationAreaInfo_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0,
	2	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_RAN_NotificationAreaInfo = {
	"RAN-NotificationAreaInfo",
	"RAN-NotificationAreaInfo",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_RAN_NotificationAreaInfo_constr_1, &asn_PER_type_RAN_NotificationAreaInfo_constr_1, CHOICE_constraint },
	asn_MBR_RAN_NotificationAreaInfo_1,
	2,	/* Elements count */
	&asn_SPC_RAN_NotificationAreaInfo_specs_1	/* Additional specs */
};

