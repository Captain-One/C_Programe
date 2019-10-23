/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "DummyF.h"

static int
memb_maxNumberPeriodicCSI_ReportPerBWP_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 4)) {
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
memb_maxNumberAperiodicCSI_ReportPerBWP_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 4)) {
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
memb_maxNumberSemiPersistentCSI_ReportPerBWP_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 4)) {
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
memb_simultaneousCSI_ReportsAllCC_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 5 && value <= 32)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_maxNumberPeriodicCSI_ReportPerBWP_constr_2 CC_NOTUSED = {
	{ 1, 1 }	/* (1..4) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxNumberPeriodicCSI_ReportPerBWP_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  1,  4 }	/* (1..4) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxNumberAperiodicCSI_ReportPerBWP_constr_3 CC_NOTUSED = {
	{ 1, 1 }	/* (1..4) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxNumberAperiodicCSI_ReportPerBWP_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  1,  4 }	/* (1..4) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxNumberSemiPersistentCSI_ReportPerBWP_constr_4 CC_NOTUSED = {
	{ 1, 1 }	/* (0..4) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxNumberSemiPersistentCSI_ReportPerBWP_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  4 }	/* (0..4) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_simultaneousCSI_ReportsAllCC_constr_5 CC_NOTUSED = {
	{ 1, 1 }	/* (5..32) */,
	-1};
static asn_per_constraints_t asn_PER_memb_simultaneousCSI_ReportsAllCC_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  5,  32 }	/* (5..32) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_DummyF_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DummyF, maxNumberPeriodicCSI_ReportPerBWP),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxNumberPeriodicCSI_ReportPerBWP_constr_2, &asn_PER_memb_maxNumberPeriodicCSI_ReportPerBWP_constr_2,  memb_maxNumberPeriodicCSI_ReportPerBWP_constraint_1 },
		0, 0, /* No default value */
		"maxNumberPeriodicCSI-ReportPerBWP"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DummyF, maxNumberAperiodicCSI_ReportPerBWP),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxNumberAperiodicCSI_ReportPerBWP_constr_3, &asn_PER_memb_maxNumberAperiodicCSI_ReportPerBWP_constr_3,  memb_maxNumberAperiodicCSI_ReportPerBWP_constraint_1 },
		0, 0, /* No default value */
		"maxNumberAperiodicCSI-ReportPerBWP"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DummyF, maxNumberSemiPersistentCSI_ReportPerBWP),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxNumberSemiPersistentCSI_ReportPerBWP_constr_4, &asn_PER_memb_maxNumberSemiPersistentCSI_ReportPerBWP_constr_4,  memb_maxNumberSemiPersistentCSI_ReportPerBWP_constraint_1 },
		0, 0, /* No default value */
		"maxNumberSemiPersistentCSI-ReportPerBWP"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DummyF, simultaneousCSI_ReportsAllCC),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_simultaneousCSI_ReportsAllCC_constr_5, &asn_PER_memb_simultaneousCSI_ReportsAllCC_constr_5,  memb_simultaneousCSI_ReportsAllCC_constraint_1 },
		0, 0, /* No default value */
		"simultaneousCSI-ReportsAllCC"
		},
};
static const ber_tlv_tag_t asn_DEF_DummyF_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_DummyF_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* maxNumberPeriodicCSI-ReportPerBWP */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* maxNumberAperiodicCSI-ReportPerBWP */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* maxNumberSemiPersistentCSI-ReportPerBWP */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* simultaneousCSI-ReportsAllCC */
};
asn_SEQUENCE_specifics_t asn_SPC_DummyF_specs_1 = {
	sizeof(struct DummyF),
	offsetof(struct DummyF, _asn_ctx),
	asn_MAP_DummyF_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_DummyF = {
	"DummyF",
	"DummyF",
	&asn_OP_SEQUENCE,
	asn_DEF_DummyF_tags_1,
	sizeof(asn_DEF_DummyF_tags_1)
		/sizeof(asn_DEF_DummyF_tags_1[0]), /* 1 */
	asn_DEF_DummyF_tags_1,	/* Same as above */
	sizeof(asn_DEF_DummyF_tags_1)
		/sizeof(asn_DEF_DummyF_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_DummyF_1,
	4,	/* Elements count */
	&asn_SPC_DummyF_specs_1	/* Additional specs */
};

