/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "MeasResults.h"

static asn_oer_constraints_t asn_OER_type_measResultNeighCells_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_measResultNeighCells_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  0,  0,  0,  0 }	/* (0..0,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_measResultNeighCells_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultNeighCells, choice.measResultListNR),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultListNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultListNR"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultNeighCells, choice.measResultListEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultListEUTRA,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultListEUTRA"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_measResultNeighCells_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measResultListNR */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* measResultListEUTRA */
};
static asn_CHOICE_specifics_t asn_SPC_measResultNeighCells_specs_4 = {
	sizeof(struct MeasResults__measResultNeighCells),
	offsetof(struct MeasResults__measResultNeighCells, _asn_ctx),
	offsetof(struct MeasResults__measResultNeighCells, present),
	sizeof(((struct MeasResults__measResultNeighCells *)0)->present),
	asn_MAP_measResultNeighCells_tag2el_4,
	2,	/* Count of tags in the map */
	0, 0,
	1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_measResultNeighCells_4 = {
	"measResultNeighCells",
	"measResultNeighCells",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_measResultNeighCells_constr_4, &asn_PER_type_measResultNeighCells_constr_4, CHOICE_constraint },
	asn_MBR_measResultNeighCells_4,
	2,	/* Elements count */
	&asn_SPC_measResultNeighCells_specs_4	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_MeasResults_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults, measId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults, measResultServingMOList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultServMOList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultServingMOList"
		},
	{ ATF_POINTER, 5, offsetof(struct MeasResults, measResultNeighCells),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_measResultNeighCells_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultNeighCells"
		},
	{ ATF_POINTER, 4, offsetof(struct MeasResults, measResultServFreqListEUTRA_SCG),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultServFreqListEUTRA_SCG,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultServFreqListEUTRA-SCG"
		},
	{ ATF_POINTER, 3, offsetof(struct MeasResults, measResultServFreqListNR_SCG),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultServFreqListNR_SCG,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultServFreqListNR-SCG"
		},
	{ ATF_POINTER, 2, offsetof(struct MeasResults, measResultSFTD_EUTRA),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultSFTD_EUTRA,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultSFTD-EUTRA"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasResults, measResultSFTD_NR),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultCellSFTD_NR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measResultSFTD-NR"
		},
};
static const int asn_MAP_MeasResults_oms_1[] = { 2, 3, 4, 5, 6 };
static const ber_tlv_tag_t asn_DEF_MeasResults_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasResults_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* measResultServingMOList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* measResultNeighCells */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* measResultServFreqListEUTRA-SCG */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* measResultServFreqListNR-SCG */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* measResultSFTD-EUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* measResultSFTD-NR */
};
asn_SEQUENCE_specifics_t asn_SPC_MeasResults_specs_1 = {
	sizeof(struct MeasResults),
	offsetof(struct MeasResults, _asn_ctx),
	asn_MAP_MeasResults_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_MeasResults_oms_1,	/* Optional members */
	1, 4,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MeasResults = {
	"MeasResults",
	"MeasResults",
	&asn_OP_SEQUENCE,
	asn_DEF_MeasResults_tags_1,
	sizeof(asn_DEF_MeasResults_tags_1)
		/sizeof(asn_DEF_MeasResults_tags_1[0]), /* 1 */
	asn_DEF_MeasResults_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasResults_tags_1)
		/sizeof(asn_DEF_MeasResults_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MeasResults_1,
	7,	/* Elements count */
	&asn_SPC_MeasResults_specs_1	/* Additional specs */
};

