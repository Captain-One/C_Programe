/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "MeasTriggerQuantityOffset.h"

static int
memb_rsrp_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -30 && value <= 30)) {
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
memb_rsrq_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -30 && value <= 30)) {
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
memb_sinr_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -30 && value <= 30)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_rsrp_constr_2 CC_NOTUSED = {
	{ 1, 0 }	/* (-30..30) */,
	-1};
static asn_per_constraints_t asn_PER_memb_rsrp_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6, -30,  30 }	/* (-30..30) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_rsrq_constr_3 CC_NOTUSED = {
	{ 1, 0 }	/* (-30..30) */,
	-1};
static asn_per_constraints_t asn_PER_memb_rsrq_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6, -30,  30 }	/* (-30..30) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sinr_constr_4 CC_NOTUSED = {
	{ 1, 0 }	/* (-30..30) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sinr_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6, -30,  30 }	/* (-30..30) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_MeasTriggerQuantityOffset_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_MeasTriggerQuantityOffset_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_MeasTriggerQuantityOffset_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasTriggerQuantityOffset, choice.rsrp),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_rsrp_constr_2, &asn_PER_memb_rsrp_constr_2,  memb_rsrp_constraint_1 },
		0, 0, /* No default value */
		"rsrp"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasTriggerQuantityOffset, choice.rsrq),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_rsrq_constr_3, &asn_PER_memb_rsrq_constr_3,  memb_rsrq_constraint_1 },
		0, 0, /* No default value */
		"rsrq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasTriggerQuantityOffset, choice.sinr),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sinr_constr_4, &asn_PER_memb_sinr_constr_4,  memb_sinr_constraint_1 },
		0, 0, /* No default value */
		"sinr"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_MeasTriggerQuantityOffset_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rsrp */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* rsrq */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* sinr */
};
asn_CHOICE_specifics_t asn_SPC_MeasTriggerQuantityOffset_specs_1 = {
	sizeof(struct MeasTriggerQuantityOffset),
	offsetof(struct MeasTriggerQuantityOffset, _asn_ctx),
	offsetof(struct MeasTriggerQuantityOffset, present),
	sizeof(((struct MeasTriggerQuantityOffset *)0)->present),
	asn_MAP_MeasTriggerQuantityOffset_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_MeasTriggerQuantityOffset = {
	"MeasTriggerQuantityOffset",
	"MeasTriggerQuantityOffset",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_MeasTriggerQuantityOffset_constr_1, &asn_PER_type_MeasTriggerQuantityOffset_constr_1, CHOICE_constraint },
	asn_MBR_MeasTriggerQuantityOffset_1,
	3,	/* Elements count */
	&asn_SPC_MeasTriggerQuantityOffset_specs_1	/* Additional specs */
};

