/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "RedirectedCarrierInfo.h"

static asn_oer_constraints_t asn_OER_type_RedirectedCarrierInfo_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_RedirectedCarrierInfo_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_RedirectedCarrierInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RedirectedCarrierInfo, choice.nr),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CarrierInfoNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"nr"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RedirectedCarrierInfo, choice.eutra),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RedirectedCarrierInfo_EUTRA,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"eutra"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_RedirectedCarrierInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* nr */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* eutra */
};
asn_CHOICE_specifics_t asn_SPC_RedirectedCarrierInfo_specs_1 = {
	sizeof(struct RedirectedCarrierInfo),
	offsetof(struct RedirectedCarrierInfo, _asn_ctx),
	offsetof(struct RedirectedCarrierInfo, present),
	sizeof(((struct RedirectedCarrierInfo *)0)->present),
	asn_MAP_RedirectedCarrierInfo_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0,
	2	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_RedirectedCarrierInfo = {
	"RedirectedCarrierInfo",
	"RedirectedCarrierInfo",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_RedirectedCarrierInfo_constr_1, &asn_PER_type_RedirectedCarrierInfo_constr_1, CHOICE_constraint },
	asn_MBR_RedirectedCarrierInfo_1,
	2,	/* Elements count */
	&asn_SPC_RedirectedCarrierInfo_specs_1	/* Additional specs */
};

