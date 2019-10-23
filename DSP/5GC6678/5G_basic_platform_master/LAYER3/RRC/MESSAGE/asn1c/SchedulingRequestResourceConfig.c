/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "SchedulingRequestResourceConfig.h"

static int
memb_sl2_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 1)) {
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
memb_sl4_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
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

static int
memb_sl5_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_sl8_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 7)) {
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
memb_sl10_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 9)) {
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
memb_sl16_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
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
memb_sl20_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 19)) {
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
memb_sl40_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 39)) {
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
memb_sl80_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 79)) {
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
memb_sl160_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 159)) {
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
memb_sl320_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 319)) {
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
memb_sl640_constraint_4(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 639)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_sl2_constr_8 CC_NOTUSED = {
	{ 1, 1 }	/* (0..1) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl2_constr_8 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl4_constr_9 CC_NOTUSED = {
	{ 1, 1 }	/* (0..3) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl4_constr_9 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl5_constr_10 CC_NOTUSED = {
	{ 1, 1 }	/* (0..4) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl5_constr_10 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  4 }	/* (0..4) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl8_constr_11 CC_NOTUSED = {
	{ 1, 1 }	/* (0..7) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl8_constr_11 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl10_constr_12 CC_NOTUSED = {
	{ 1, 1 }	/* (0..9) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl10_constr_12 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  9 }	/* (0..9) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl16_constr_13 CC_NOTUSED = {
	{ 1, 1 }	/* (0..15) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl16_constr_13 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl20_constr_14 CC_NOTUSED = {
	{ 1, 1 }	/* (0..19) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl20_constr_14 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  0,  19 }	/* (0..19) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl40_constr_15 CC_NOTUSED = {
	{ 1, 1 }	/* (0..39) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl40_constr_15 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6,  0,  39 }	/* (0..39) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl80_constr_16 CC_NOTUSED = {
	{ 1, 1 }	/* (0..79) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl80_constr_16 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  0,  79 }	/* (0..79) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl160_constr_17 CC_NOTUSED = {
	{ 1, 1 }	/* (0..159) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl160_constr_17 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  0,  159 }	/* (0..159) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl320_constr_18 CC_NOTUSED = {
	{ 2, 1 }	/* (0..319) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl320_constr_18 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 9,  9,  0,  319 }	/* (0..319) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_sl640_constr_19 CC_NOTUSED = {
	{ 2, 1 }	/* (0..639) */,
	-1};
static asn_per_constraints_t asn_PER_memb_sl640_constr_19 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 10,  10,  0,  639 }	/* (0..639) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_periodicityAndOffset_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_periodicityAndOffset_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  14 }	/* (0..14) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_periodicityAndOffset_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sym2),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sym2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sym6or7),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sym6or7"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl1),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sl1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl2),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl2_constr_8, &asn_PER_memb_sl2_constr_8,  memb_sl2_constraint_4 },
		0, 0, /* No default value */
		"sl2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl4),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl4_constr_9, &asn_PER_memb_sl4_constr_9,  memb_sl4_constraint_4 },
		0, 0, /* No default value */
		"sl4"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl5),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl5_constr_10, &asn_PER_memb_sl5_constr_10,  memb_sl5_constraint_4 },
		0, 0, /* No default value */
		"sl5"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl8),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl8_constr_11, &asn_PER_memb_sl8_constr_11,  memb_sl8_constraint_4 },
		0, 0, /* No default value */
		"sl8"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl10),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl10_constr_12, &asn_PER_memb_sl10_constr_12,  memb_sl10_constraint_4 },
		0, 0, /* No default value */
		"sl10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl16),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl16_constr_13, &asn_PER_memb_sl16_constr_13,  memb_sl16_constraint_4 },
		0, 0, /* No default value */
		"sl16"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl20),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl20_constr_14, &asn_PER_memb_sl20_constr_14,  memb_sl20_constraint_4 },
		0, 0, /* No default value */
		"sl20"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl40),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl40_constr_15, &asn_PER_memb_sl40_constr_15,  memb_sl40_constraint_4 },
		0, 0, /* No default value */
		"sl40"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl80),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl80_constr_16, &asn_PER_memb_sl80_constr_16,  memb_sl80_constraint_4 },
		0, 0, /* No default value */
		"sl80"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl160),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl160_constr_17, &asn_PER_memb_sl160_constr_17,  memb_sl160_constraint_4 },
		0, 0, /* No default value */
		"sl160"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl320),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl320_constr_18, &asn_PER_memb_sl320_constr_18,  memb_sl320_constraint_4 },
		0, 0, /* No default value */
		"sl320"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, choice.sl640),
		(ASN_TAG_CLASS_CONTEXT | (14 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_sl640_constr_19, &asn_PER_memb_sl640_constr_19,  memb_sl640_constraint_4 },
		0, 0, /* No default value */
		"sl640"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_periodicityAndOffset_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sym2 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* sym6or7 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* sl1 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* sl2 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* sl4 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* sl5 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* sl8 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* sl10 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* sl16 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* sl20 */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* sl40 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* sl80 */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* sl160 */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 }, /* sl320 */
    { (ASN_TAG_CLASS_CONTEXT | (14 << 2)), 14, 0, 0 } /* sl640 */
};
static asn_CHOICE_specifics_t asn_SPC_periodicityAndOffset_specs_4 = {
	sizeof(struct SchedulingRequestResourceConfig__periodicityAndOffset),
	offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, _asn_ctx),
	offsetof(struct SchedulingRequestResourceConfig__periodicityAndOffset, present),
	sizeof(((struct SchedulingRequestResourceConfig__periodicityAndOffset *)0)->present),
	asn_MAP_periodicityAndOffset_tag2el_4,
	15,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_periodicityAndOffset_4 = {
	"periodicityAndOffset",
	"periodicityAndOffset",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_periodicityAndOffset_constr_4, &asn_PER_type_periodicityAndOffset_constr_4, CHOICE_constraint },
	asn_MBR_periodicityAndOffset_4,
	15,	/* Elements count */
	&asn_SPC_periodicityAndOffset_specs_4	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_SchedulingRequestResourceConfig_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig, schedulingRequestResourceId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SchedulingRequestResourceId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"schedulingRequestResourceId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SchedulingRequestResourceConfig, schedulingRequestID),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SchedulingRequestId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"schedulingRequestID"
		},
	{ ATF_POINTER, 2, offsetof(struct SchedulingRequestResourceConfig, periodicityAndOffset),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_periodicityAndOffset_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"periodicityAndOffset"
		},
	{ ATF_POINTER, 1, offsetof(struct SchedulingRequestResourceConfig, resource),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PUCCH_ResourceId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"resource"
		},
};
static const int asn_MAP_SchedulingRequestResourceConfig_oms_1[] = { 2, 3 };
static const ber_tlv_tag_t asn_DEF_SchedulingRequestResourceConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SchedulingRequestResourceConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* schedulingRequestResourceId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* schedulingRequestID */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* periodicityAndOffset */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* resource */
};
asn_SEQUENCE_specifics_t asn_SPC_SchedulingRequestResourceConfig_specs_1 = {
	sizeof(struct SchedulingRequestResourceConfig),
	offsetof(struct SchedulingRequestResourceConfig, _asn_ctx),
	asn_MAP_SchedulingRequestResourceConfig_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_SchedulingRequestResourceConfig_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SchedulingRequestResourceConfig = {
	"SchedulingRequestResourceConfig",
	"SchedulingRequestResourceConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_SchedulingRequestResourceConfig_tags_1,
	sizeof(asn_DEF_SchedulingRequestResourceConfig_tags_1)
		/sizeof(asn_DEF_SchedulingRequestResourceConfig_tags_1[0]), /* 1 */
	asn_DEF_SchedulingRequestResourceConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_SchedulingRequestResourceConfig_tags_1)
		/sizeof(asn_DEF_SchedulingRequestResourceConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SchedulingRequestResourceConfig_1,
	4,	/* Elements count */
	&asn_SPC_SchedulingRequestResourceConfig_specs_1	/* Additional specs */
};

