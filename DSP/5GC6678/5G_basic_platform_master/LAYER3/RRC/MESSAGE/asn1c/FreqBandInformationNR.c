/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "FreqBandInformationNR.h"

static int
memb_maxCarriersRequestedDL_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 32)) {
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
memb_maxCarriersRequestedUL_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 32)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_maxCarriersRequestedDL_constr_5 CC_NOTUSED = {
	{ 1, 1 }	/* (1..32) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxCarriersRequestedDL_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (1..32) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxCarriersRequestedUL_constr_6 CC_NOTUSED = {
	{ 1, 1 }	/* (1..32) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxCarriersRequestedUL_constr_6 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (1..32) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_FreqBandInformationNR_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct FreqBandInformationNR, bandNR),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FreqBandIndicatorNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"bandNR"
		},
	{ ATF_POINTER, 4, offsetof(struct FreqBandInformationNR, maxBandwidthRequestedDL),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AggregatedBandwidth,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"maxBandwidthRequestedDL"
		},
	{ ATF_POINTER, 3, offsetof(struct FreqBandInformationNR, maxBandwidthRequestedUL),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AggregatedBandwidth,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"maxBandwidthRequestedUL"
		},
	{ ATF_POINTER, 2, offsetof(struct FreqBandInformationNR, maxCarriersRequestedDL),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxCarriersRequestedDL_constr_5, &asn_PER_memb_maxCarriersRequestedDL_constr_5,  memb_maxCarriersRequestedDL_constraint_1 },
		0, 0, /* No default value */
		"maxCarriersRequestedDL"
		},
	{ ATF_POINTER, 1, offsetof(struct FreqBandInformationNR, maxCarriersRequestedUL),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxCarriersRequestedUL_constr_6, &asn_PER_memb_maxCarriersRequestedUL_constr_6,  memb_maxCarriersRequestedUL_constraint_1 },
		0, 0, /* No default value */
		"maxCarriersRequestedUL"
		},
};
static const int asn_MAP_FreqBandInformationNR_oms_1[] = { 1, 2, 3, 4 };
static const ber_tlv_tag_t asn_DEF_FreqBandInformationNR_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_FreqBandInformationNR_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* bandNR */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* maxBandwidthRequestedDL */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* maxBandwidthRequestedUL */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* maxCarriersRequestedDL */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* maxCarriersRequestedUL */
};
asn_SEQUENCE_specifics_t asn_SPC_FreqBandInformationNR_specs_1 = {
	sizeof(struct FreqBandInformationNR),
	offsetof(struct FreqBandInformationNR, _asn_ctx),
	asn_MAP_FreqBandInformationNR_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_FreqBandInformationNR_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_FreqBandInformationNR = {
	"FreqBandInformationNR",
	"FreqBandInformationNR",
	&asn_OP_SEQUENCE,
	asn_DEF_FreqBandInformationNR_tags_1,
	sizeof(asn_DEF_FreqBandInformationNR_tags_1)
		/sizeof(asn_DEF_FreqBandInformationNR_tags_1[0]), /* 1 */
	asn_DEF_FreqBandInformationNR_tags_1,	/* Same as above */
	sizeof(asn_DEF_FreqBandInformationNR_tags_1)
		/sizeof(asn_DEF_FreqBandInformationNR_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_FreqBandInformationNR_1,
	5,	/* Elements count */
	&asn_SPC_FreqBandInformationNR_specs_1	/* Additional specs */
};

