/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "SS-RSSI-Measurement.h"

static int
memb_measurementSlots_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const BIT_STRING_t *st = (const BIT_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	if(st->size > 0) {
		/* Size in bits */
		size = 8 * st->size - (st->bits_unused & 0x07);
	} else {
		size = 0;
	}
	
	if((size >= 1 && size <= 80)) {
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
memb_endSymbol_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 3)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_measurementSlots_constr_2 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..80)) */};
static asn_per_constraints_t asn_PER_memb_measurementSlots_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 7,  7,  1,  80 }	/* (SIZE(1..80)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_endSymbol_constr_3 CC_NOTUSED = {
	{ 1, 1 }	/* (0..3) */,
	-1};
static asn_per_constraints_t asn_PER_memb_endSymbol_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_SS_RSSI_Measurement_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SS_RSSI_Measurement, measurementSlots),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ &asn_OER_memb_measurementSlots_constr_2, &asn_PER_memb_measurementSlots_constr_2,  memb_measurementSlots_constraint_1 },
		0, 0, /* No default value */
		"measurementSlots"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SS_RSSI_Measurement, endSymbol),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_endSymbol_constr_3, &asn_PER_memb_endSymbol_constr_3,  memb_endSymbol_constraint_1 },
		0, 0, /* No default value */
		"endSymbol"
		},
};
static const ber_tlv_tag_t asn_DEF_SS_RSSI_Measurement_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SS_RSSI_Measurement_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measurementSlots */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* endSymbol */
};
asn_SEQUENCE_specifics_t asn_SPC_SS_RSSI_Measurement_specs_1 = {
	sizeof(struct SS_RSSI_Measurement),
	offsetof(struct SS_RSSI_Measurement, _asn_ctx),
	asn_MAP_SS_RSSI_Measurement_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SS_RSSI_Measurement = {
	"SS-RSSI-Measurement",
	"SS-RSSI-Measurement",
	&asn_OP_SEQUENCE,
	asn_DEF_SS_RSSI_Measurement_tags_1,
	sizeof(asn_DEF_SS_RSSI_Measurement_tags_1)
		/sizeof(asn_DEF_SS_RSSI_Measurement_tags_1[0]), /* 1 */
	asn_DEF_SS_RSSI_Measurement_tags_1,	/* Same as above */
	sizeof(asn_DEF_SS_RSSI_Measurement_tags_1)
		/sizeof(asn_DEF_SS_RSSI_Measurement_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SS_RSSI_Measurement_1,
	2,	/* Elements count */
	&asn_SPC_SS_RSSI_Measurement_specs_1	/* Additional specs */
};

