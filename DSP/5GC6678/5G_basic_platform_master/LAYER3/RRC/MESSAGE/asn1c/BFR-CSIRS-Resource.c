/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "BFR-CSIRS-Resource.h"

static int
memb_NativeInteger_constraint_3(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 511)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_ra_OccasionList_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 64)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_ra_PreambleIndex_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 63)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_Member_constr_4 CC_NOTUSED = {
	{ 2, 1 }	/* (0..511) */,
	-1};
static asn_per_constraints_t asn_PER_memb_Member_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 9,  9,  0,  511 }	/* (0..511) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_ra_OccasionList_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_type_ra_OccasionList_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_ra_OccasionList_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_memb_ra_OccasionList_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_ra_PreambleIndex_constr_5 CC_NOTUSED = {
	{ 1, 1 }	/* (0..63) */,
	-1};
static asn_per_constraints_t asn_PER_memb_ra_PreambleIndex_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6,  0,  63 }	/* (0..63) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_ra_OccasionList_3[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_Member_constr_4, &asn_PER_memb_Member_constr_4,  memb_NativeInteger_constraint_3 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_ra_OccasionList_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_ra_OccasionList_specs_3 = {
	sizeof(struct BFR_CSIRS_Resource__ra_OccasionList),
	offsetof(struct BFR_CSIRS_Resource__ra_OccasionList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ra_OccasionList_3 = {
	"ra-OccasionList",
	"ra-OccasionList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_ra_OccasionList_tags_3,
	sizeof(asn_DEF_ra_OccasionList_tags_3)
		/sizeof(asn_DEF_ra_OccasionList_tags_3[0]) - 1, /* 1 */
	asn_DEF_ra_OccasionList_tags_3,	/* Same as above */
	sizeof(asn_DEF_ra_OccasionList_tags_3)
		/sizeof(asn_DEF_ra_OccasionList_tags_3[0]), /* 2 */
	{ &asn_OER_type_ra_OccasionList_constr_3, &asn_PER_type_ra_OccasionList_constr_3, SEQUENCE_OF_constraint },
	asn_MBR_ra_OccasionList_3,
	1,	/* Single element */
	&asn_SPC_ra_OccasionList_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_BFR_CSIRS_Resource_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct BFR_CSIRS_Resource, csi_RS),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NZP_CSI_RS_ResourceId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"csi-RS"
		},
	{ ATF_POINTER, 2, offsetof(struct BFR_CSIRS_Resource, ra_OccasionList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_ra_OccasionList_3,
		0,
		{ &asn_OER_memb_ra_OccasionList_constr_3, &asn_PER_memb_ra_OccasionList_constr_3,  memb_ra_OccasionList_constraint_1 },
		0, 0, /* No default value */
		"ra-OccasionList"
		},
	{ ATF_POINTER, 1, offsetof(struct BFR_CSIRS_Resource, ra_PreambleIndex),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_ra_PreambleIndex_constr_5, &asn_PER_memb_ra_PreambleIndex_constr_5,  memb_ra_PreambleIndex_constraint_1 },
		0, 0, /* No default value */
		"ra-PreambleIndex"
		},
};
static const int asn_MAP_BFR_CSIRS_Resource_oms_1[] = { 1, 2 };
static const ber_tlv_tag_t asn_DEF_BFR_CSIRS_Resource_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_BFR_CSIRS_Resource_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* csi-RS */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ra-OccasionList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* ra-PreambleIndex */
};
asn_SEQUENCE_specifics_t asn_SPC_BFR_CSIRS_Resource_specs_1 = {
	sizeof(struct BFR_CSIRS_Resource),
	offsetof(struct BFR_CSIRS_Resource, _asn_ctx),
	asn_MAP_BFR_CSIRS_Resource_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_BFR_CSIRS_Resource_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_BFR_CSIRS_Resource = {
	"BFR-CSIRS-Resource",
	"BFR-CSIRS-Resource",
	&asn_OP_SEQUENCE,
	asn_DEF_BFR_CSIRS_Resource_tags_1,
	sizeof(asn_DEF_BFR_CSIRS_Resource_tags_1)
		/sizeof(asn_DEF_BFR_CSIRS_Resource_tags_1[0]), /* 1 */
	asn_DEF_BFR_CSIRS_Resource_tags_1,	/* Same as above */
	sizeof(asn_DEF_BFR_CSIRS_Resource_tags_1)
		/sizeof(asn_DEF_BFR_CSIRS_Resource_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_BFR_CSIRS_Resource_1,
	3,	/* Elements count */
	&asn_SPC_BFR_CSIRS_Resource_specs_1	/* Additional specs */
};

