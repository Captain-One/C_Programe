/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "MeasResults.h"

static asn_per_constraints_t asn_PER_type_measResultNeighCells_constr_6 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  2,  2,  0,  3 }	/* (0..3,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_measResultPCell_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultPCell, rsrpResult),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSRP_Range,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rsrpResult"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultPCell, rsrqResult),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSRQ_Range,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"rsrqResult"
		},
};
static const ber_tlv_tag_t asn_DEF_measResultPCell_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_measResultPCell_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rsrpResult */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* rsrqResult */
};
static asn_SEQUENCE_specifics_t asn_SPC_measResultPCell_specs_3 = {
	sizeof(struct MeasResults__measResultPCell),
	offsetof(struct MeasResults__measResultPCell, _asn_ctx),
	asn_MAP_measResultPCell_tag2el_3,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_measResultPCell_3 = {
	"measResultPCell",
	"measResultPCell",
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
	asn_DEF_measResultPCell_tags_3,
	sizeof(asn_DEF_measResultPCell_tags_3)
		/sizeof(asn_DEF_measResultPCell_tags_3[0]) - 1, /* 1 */
	asn_DEF_measResultPCell_tags_3,	/* Same as above */
	sizeof(asn_DEF_measResultPCell_tags_3)
		/sizeof(asn_DEF_measResultPCell_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_measResultPCell_3,
	2,	/* Elements count */
	&asn_SPC_measResultPCell_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_measResultNeighCells_6[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultNeighCells, choice.measResultListEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultListEUTRA,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultListEUTRA"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultNeighCells, choice.measResultListUTRA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultListUTRA,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultListUTRA"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultNeighCells, choice.measResultListGERAN),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultListGERAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultListGERAN"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults__measResultNeighCells, choice.measResultsCDMA2000),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultsCDMA2000,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultsCDMA2000"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_measResultNeighCells_tag2el_6[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measResultListEUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* measResultListUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* measResultListGERAN */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* measResultsCDMA2000 */
};
static asn_CHOICE_specifics_t asn_SPC_measResultNeighCells_specs_6 = {
	sizeof(struct MeasResults__measResultNeighCells),
	offsetof(struct MeasResults__measResultNeighCells, _asn_ctx),
	offsetof(struct MeasResults__measResultNeighCells, present),
	sizeof(((struct MeasResults__measResultNeighCells *)0)->present),
	asn_MAP_measResultNeighCells_tag2el_6,
	4,	/* Count of tags in the map */
	0,
	4	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_measResultNeighCells_6 = {
	"measResultNeighCells",
	"measResultNeighCells",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_measResultNeighCells_constr_6,
	asn_MBR_measResultNeighCells_6,
	4,	/* Elements count */
	&asn_SPC_measResultNeighCells_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_MeasResults_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults, measId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasId,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasResults, measResultPCell),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_measResultPCell_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultPCell"
		},
	{ ATF_POINTER, 4, offsetof(struct MeasResults, measResultNeighCells),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_measResultNeighCells_6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultNeighCells"
		},
	{ ATF_POINTER, 3, offsetof(struct MeasResults, measResultForECID_r9),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultForECID_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultForECID-r9"
		},
	{ ATF_POINTER, 2, offsetof(struct MeasResults, locationInfo_r10),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LocationInfo_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"locationInfo-r10"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasResults, measResultServFreqList_r10),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MeasResultServFreqList_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"measResultServFreqList-r10"
		},
};
static const int asn_MAP_MeasResults_oms_1[] = { 2, 3, 4, 5 };
static const ber_tlv_tag_t asn_DEF_MeasResults_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasResults_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* measResultPCell */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* measResultNeighCells */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* measResultForECID-r9 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* locationInfo-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* measResultServFreqList-r10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_MeasResults_specs_1 = {
	sizeof(struct MeasResults),
	offsetof(struct MeasResults, _asn_ctx),
	asn_MAP_MeasResults_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_MeasResults_oms_1,	/* Optional members */
	1, 3,	/* Root/Additions */
	2,	/* Start extensions */
	7	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_MeasResults = {
	"MeasResults",
	"MeasResults",
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
	asn_DEF_MeasResults_tags_1,
	sizeof(asn_DEF_MeasResults_tags_1)
		/sizeof(asn_DEF_MeasResults_tags_1[0]), /* 1 */
	asn_DEF_MeasResults_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasResults_tags_1)
		/sizeof(asn_DEF_MeasResults_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_MeasResults_1,
	6,	/* Elements count */
	&asn_SPC_MeasResults_specs_1	/* Additional specs */
};

