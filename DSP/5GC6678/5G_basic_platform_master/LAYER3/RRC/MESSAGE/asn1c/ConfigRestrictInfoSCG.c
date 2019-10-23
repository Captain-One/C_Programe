/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "ConfigRestrictInfoSCG.h"

static int
memb_maxMeasFreqsSCG_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_maxMeasIdentitiesSCG_NR_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 62)) {
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
memb_selectedBandEntriesMN_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 32)) {
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
memb_pdcch_BlindDetectionSCG_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 15)) {
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
memb_maxNumberROHC_ContextSessionsSN_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 16384)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_selectedBandEntriesMN_constr_13 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_type_selectedBandEntriesMN_constr_13 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxMeasFreqsSCG_constr_10 CC_NOTUSED = {
	{ 1, 1 }	/* (1..32) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxMeasFreqsSCG_constr_10 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (1..32) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxMeasIdentitiesSCG_NR_constr_11 CC_NOTUSED = {
	{ 1, 1 }	/* (1..62) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxMeasIdentitiesSCG_NR_constr_11 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6,  1,  62 }	/* (1..62) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_selectedBandEntriesMN_constr_13 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_memb_selectedBandEntriesMN_constr_13 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_pdcch_BlindDetectionSCG_constr_15 CC_NOTUSED = {
	{ 1, 1 }	/* (1..15) */,
	-1};
static asn_per_constraints_t asn_PER_memb_pdcch_BlindDetectionSCG_constr_15 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  1,  15 }	/* (1..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxNumberROHC_ContextSessionsSN_constr_16 CC_NOTUSED = {
	{ 2, 1 }	/* (0..16384) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxNumberROHC_ContextSessionsSN_constr_16 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 15,  15,  0,  16384 }	/* (0..16384) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_powerCoordination_FR1_3[] = {
	{ ATF_POINTER, 3, offsetof(struct ConfigRestrictInfoSCG__powerCoordination_FR1, p_maxNR_FR1),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_P_Max,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"p-maxNR-FR1"
		},
	{ ATF_POINTER, 2, offsetof(struct ConfigRestrictInfoSCG__powerCoordination_FR1, p_maxEUTRA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_P_Max,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"p-maxEUTRA"
		},
	{ ATF_POINTER, 1, offsetof(struct ConfigRestrictInfoSCG__powerCoordination_FR1, p_maxUE_FR1),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_P_Max,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"p-maxUE-FR1"
		},
};
static const int asn_MAP_powerCoordination_FR1_oms_3[] = { 0, 1, 2 };
static const ber_tlv_tag_t asn_DEF_powerCoordination_FR1_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_powerCoordination_FR1_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* p-maxNR-FR1 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* p-maxEUTRA */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* p-maxUE-FR1 */
};
static asn_SEQUENCE_specifics_t asn_SPC_powerCoordination_FR1_specs_3 = {
	sizeof(struct ConfigRestrictInfoSCG__powerCoordination_FR1),
	offsetof(struct ConfigRestrictInfoSCG__powerCoordination_FR1, _asn_ctx),
	asn_MAP_powerCoordination_FR1_tag2el_3,
	3,	/* Count of tags in the map */
	asn_MAP_powerCoordination_FR1_oms_3,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_powerCoordination_FR1_3 = {
	"powerCoordination-FR1",
	"powerCoordination-FR1",
	&asn_OP_SEQUENCE,
	asn_DEF_powerCoordination_FR1_tags_3,
	sizeof(asn_DEF_powerCoordination_FR1_tags_3)
		/sizeof(asn_DEF_powerCoordination_FR1_tags_3[0]) - 1, /* 1 */
	asn_DEF_powerCoordination_FR1_tags_3,	/* Same as above */
	sizeof(asn_DEF_powerCoordination_FR1_tags_3)
		/sizeof(asn_DEF_powerCoordination_FR1_tags_3[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_powerCoordination_FR1_3,
	3,	/* Elements count */
	&asn_SPC_powerCoordination_FR1_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_servCellIndexRangeSCG_7[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ConfigRestrictInfoSCG__servCellIndexRangeSCG, lowBound),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ServCellIndex,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"lowBound"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ConfigRestrictInfoSCG__servCellIndexRangeSCG, upBound),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ServCellIndex,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"upBound"
		},
};
static const ber_tlv_tag_t asn_DEF_servCellIndexRangeSCG_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_servCellIndexRangeSCG_tag2el_7[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* lowBound */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* upBound */
};
static asn_SEQUENCE_specifics_t asn_SPC_servCellIndexRangeSCG_specs_7 = {
	sizeof(struct ConfigRestrictInfoSCG__servCellIndexRangeSCG),
	offsetof(struct ConfigRestrictInfoSCG__servCellIndexRangeSCG, _asn_ctx),
	asn_MAP_servCellIndexRangeSCG_tag2el_7,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_servCellIndexRangeSCG_7 = {
	"servCellIndexRangeSCG",
	"servCellIndexRangeSCG",
	&asn_OP_SEQUENCE,
	asn_DEF_servCellIndexRangeSCG_tags_7,
	sizeof(asn_DEF_servCellIndexRangeSCG_tags_7)
		/sizeof(asn_DEF_servCellIndexRangeSCG_tags_7[0]) - 1, /* 1 */
	asn_DEF_servCellIndexRangeSCG_tags_7,	/* Same as above */
	sizeof(asn_DEF_servCellIndexRangeSCG_tags_7)
		/sizeof(asn_DEF_servCellIndexRangeSCG_tags_7[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_servCellIndexRangeSCG_7,
	2,	/* Elements count */
	&asn_SPC_servCellIndexRangeSCG_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_selectedBandEntriesMN_13[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_BandEntryIndex,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_selectedBandEntriesMN_tags_13[] = {
	(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_selectedBandEntriesMN_specs_13 = {
	sizeof(struct ConfigRestrictInfoSCG__selectedBandEntriesMN),
	offsetof(struct ConfigRestrictInfoSCG__selectedBandEntriesMN, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_selectedBandEntriesMN_13 = {
	"selectedBandEntriesMN",
	"selectedBandEntriesMN",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_selectedBandEntriesMN_tags_13,
	sizeof(asn_DEF_selectedBandEntriesMN_tags_13)
		/sizeof(asn_DEF_selectedBandEntriesMN_tags_13[0]) - 1, /* 1 */
	asn_DEF_selectedBandEntriesMN_tags_13,	/* Same as above */
	sizeof(asn_DEF_selectedBandEntriesMN_tags_13)
		/sizeof(asn_DEF_selectedBandEntriesMN_tags_13[0]), /* 2 */
	{ &asn_OER_type_selectedBandEntriesMN_constr_13, &asn_PER_type_selectedBandEntriesMN_constr_13, SEQUENCE_OF_constraint },
	asn_MBR_selectedBandEntriesMN_13,
	1,	/* Single element */
	&asn_SPC_selectedBandEntriesMN_specs_13	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ConfigRestrictInfoSCG_1[] = {
	{ ATF_POINTER, 8, offsetof(struct ConfigRestrictInfoSCG, allowedBC_ListMRDC),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BandCombinationInfoList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"allowedBC-ListMRDC"
		},
	{ ATF_POINTER, 7, offsetof(struct ConfigRestrictInfoSCG, powerCoordination_FR1),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_powerCoordination_FR1_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"powerCoordination-FR1"
		},
	{ ATF_POINTER, 6, offsetof(struct ConfigRestrictInfoSCG, servCellIndexRangeSCG),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_servCellIndexRangeSCG_7,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"servCellIndexRangeSCG"
		},
	{ ATF_POINTER, 5, offsetof(struct ConfigRestrictInfoSCG, maxMeasFreqsSCG),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxMeasFreqsSCG_constr_10, &asn_PER_memb_maxMeasFreqsSCG_constr_10,  memb_maxMeasFreqsSCG_constraint_1 },
		0, 0, /* No default value */
		"maxMeasFreqsSCG"
		},
	{ ATF_POINTER, 4, offsetof(struct ConfigRestrictInfoSCG, maxMeasIdentitiesSCG_NR),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxMeasIdentitiesSCG_NR_constr_11, &asn_PER_memb_maxMeasIdentitiesSCG_NR_constr_11,  memb_maxMeasIdentitiesSCG_NR_constraint_1 },
		0, 0, /* No default value */
		"maxMeasIdentitiesSCG-NR"
		},
	{ ATF_POINTER, 3, offsetof(struct ConfigRestrictInfoSCG, selectedBandEntriesMN),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		0,
		&asn_DEF_selectedBandEntriesMN_13,
		0,
		{ &asn_OER_memb_selectedBandEntriesMN_constr_13, &asn_PER_memb_selectedBandEntriesMN_constr_13,  memb_selectedBandEntriesMN_constraint_1 },
		0, 0, /* No default value */
		"selectedBandEntriesMN"
		},
	{ ATF_POINTER, 2, offsetof(struct ConfigRestrictInfoSCG, pdcch_BlindDetectionSCG),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_pdcch_BlindDetectionSCG_constr_15, &asn_PER_memb_pdcch_BlindDetectionSCG_constr_15,  memb_pdcch_BlindDetectionSCG_constraint_1 },
		0, 0, /* No default value */
		"pdcch-BlindDetectionSCG"
		},
	{ ATF_POINTER, 1, offsetof(struct ConfigRestrictInfoSCG, maxNumberROHC_ContextSessionsSN),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxNumberROHC_ContextSessionsSN_constr_16, &asn_PER_memb_maxNumberROHC_ContextSessionsSN_constr_16,  memb_maxNumberROHC_ContextSessionsSN_constraint_1 },
		0, 0, /* No default value */
		"maxNumberROHC-ContextSessionsSN"
		},
};
static const int asn_MAP_ConfigRestrictInfoSCG_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
static const ber_tlv_tag_t asn_DEF_ConfigRestrictInfoSCG_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ConfigRestrictInfoSCG_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* allowedBC-ListMRDC */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* powerCoordination-FR1 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* servCellIndexRangeSCG */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* maxMeasFreqsSCG */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* maxMeasIdentitiesSCG-NR */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* selectedBandEntriesMN */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* pdcch-BlindDetectionSCG */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* maxNumberROHC-ContextSessionsSN */
};
asn_SEQUENCE_specifics_t asn_SPC_ConfigRestrictInfoSCG_specs_1 = {
	sizeof(struct ConfigRestrictInfoSCG),
	offsetof(struct ConfigRestrictInfoSCG, _asn_ctx),
	asn_MAP_ConfigRestrictInfoSCG_tag2el_1,
	8,	/* Count of tags in the map */
	asn_MAP_ConfigRestrictInfoSCG_oms_1,	/* Optional members */
	5, 3,	/* Root/Additions */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ConfigRestrictInfoSCG = {
	"ConfigRestrictInfoSCG",
	"ConfigRestrictInfoSCG",
	&asn_OP_SEQUENCE,
	asn_DEF_ConfigRestrictInfoSCG_tags_1,
	sizeof(asn_DEF_ConfigRestrictInfoSCG_tags_1)
		/sizeof(asn_DEF_ConfigRestrictInfoSCG_tags_1[0]), /* 1 */
	asn_DEF_ConfigRestrictInfoSCG_tags_1,	/* Same as above */
	sizeof(asn_DEF_ConfigRestrictInfoSCG_tags_1)
		/sizeof(asn_DEF_ConfigRestrictInfoSCG_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ConfigRestrictInfoSCG_1,
	8,	/* Elements count */
	&asn_SPC_ConfigRestrictInfoSCG_specs_1	/* Additional specs */
};

