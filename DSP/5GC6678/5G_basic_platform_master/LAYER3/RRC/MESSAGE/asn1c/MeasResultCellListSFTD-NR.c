/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "MeasResultCellListSFTD-NR.h"

static asn_oer_constraints_t asn_OER_type_MeasResultCellListSFTD_NR_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..3)) */};
asn_per_constraints_t asn_PER_type_MeasResultCellListSFTD_NR_constr_1 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 2,  2,  1,  3 }	/* (SIZE(1..3)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_MeasResultCellListSFTD_NR_1[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_MeasResultCellSFTD_NR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_MeasResultCellListSFTD_NR_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_SET_OF_specifics_t asn_SPC_MeasResultCellListSFTD_NR_specs_1 = {
	sizeof(struct MeasResultCellListSFTD_NR),
	offsetof(struct MeasResultCellListSFTD_NR, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
asn_TYPE_descriptor_t asn_DEF_MeasResultCellListSFTD_NR = {
	"MeasResultCellListSFTD-NR",
	"MeasResultCellListSFTD-NR",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_MeasResultCellListSFTD_NR_tags_1,
	sizeof(asn_DEF_MeasResultCellListSFTD_NR_tags_1)
		/sizeof(asn_DEF_MeasResultCellListSFTD_NR_tags_1[0]), /* 1 */
	asn_DEF_MeasResultCellListSFTD_NR_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasResultCellListSFTD_NR_tags_1)
		/sizeof(asn_DEF_MeasResultCellListSFTD_NR_tags_1[0]), /* 1 */
	{ &asn_OER_type_MeasResultCellListSFTD_NR_constr_1, &asn_PER_type_MeasResultCellListSFTD_NR_constr_1, SEQUENCE_OF_constraint },
	asn_MBR_MeasResultCellListSFTD_NR_1,
	1,	/* Single element */
	&asn_SPC_MeasResultCellListSFTD_NR_specs_1	/* Additional specs */
};

