/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "ControlResourceSet.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_shiftIndex_constraint_6(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 274)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_frequencyDomainResources_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size == 45)) {
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
memb_duration_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 1 && value <= 3)) {
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
memb_tci_StatesPDCCH_ToAddList_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_tci_StatesPDCCH_ToReleaseList_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_pdcch_DMRS_ScramblingID_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 65535)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_reg_BundleSize_constr_7 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_reg_BundleSize_constr_7 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_interleaverSize_constr_11 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_interleaverSize_constr_11 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_shiftIndex_constr_15 CC_NOTUSED = {
	{ 2, 1 }	/* (0..274) */,
	-1};
static asn_per_constraints_t asn_PER_memb_shiftIndex_constr_15 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 9,  9,  0,  274 }	/* (0..274) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_cce_REG_MappingType_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_cce_REG_MappingType_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_precoderGranularity_constr_17 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_precoderGranularity_constr_17 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_tci_StatesPDCCH_ToAddList_constr_20 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_type_tci_StatesPDCCH_ToAddList_constr_20 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_tci_StatesPDCCH_ToReleaseList_constr_22 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_type_tci_StatesPDCCH_ToReleaseList_constr_22 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_tci_PresentInDCI_constr_24 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_tci_PresentInDCI_constr_24 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_frequencyDomainResources_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	45	/* (SIZE(45..45)) */};
static asn_per_constraints_t asn_PER_memb_frequencyDomainResources_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  45,  45 }	/* (SIZE(45..45)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_duration_constr_4 CC_NOTUSED = {
	{ 1, 1 }	/* (1..3) */,
	-1};
static asn_per_constraints_t asn_PER_memb_duration_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  1,  3 }	/* (1..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_tci_StatesPDCCH_ToAddList_constr_20 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_memb_tci_StatesPDCCH_ToAddList_constr_20 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_tci_StatesPDCCH_ToReleaseList_constr_22 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_memb_tci_StatesPDCCH_ToReleaseList_constr_22 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_pdcch_DMRS_ScramblingID_constr_26 CC_NOTUSED = {
	{ 2, 1 }	/* (0..65535) */,
	-1};
static asn_per_constraints_t asn_PER_memb_pdcch_DMRS_ScramblingID_constr_26 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 16,  16,  0,  65535 }	/* (0..65535) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_reg_BundleSize_value2enum_7[] = {
	{ 0,	2,	"n2" },
	{ 1,	2,	"n3" },
	{ 2,	2,	"n6" }
};
static const unsigned int asn_MAP_reg_BundleSize_enum2value_7[] = {
	0,	/* n2(0) */
	1,	/* n3(1) */
	2	/* n6(2) */
};
static const asn_INTEGER_specifics_t asn_SPC_reg_BundleSize_specs_7 = {
	asn_MAP_reg_BundleSize_value2enum_7,	/* "tag" => N; sorted by tag */
	asn_MAP_reg_BundleSize_enum2value_7,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_reg_BundleSize_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_reg_BundleSize_7 = {
	"reg-BundleSize",
	"reg-BundleSize",
	&asn_OP_NativeEnumerated,
	asn_DEF_reg_BundleSize_tags_7,
	sizeof(asn_DEF_reg_BundleSize_tags_7)
		/sizeof(asn_DEF_reg_BundleSize_tags_7[0]) - 1, /* 1 */
	asn_DEF_reg_BundleSize_tags_7,	/* Same as above */
	sizeof(asn_DEF_reg_BundleSize_tags_7)
		/sizeof(asn_DEF_reg_BundleSize_tags_7[0]), /* 2 */
	{ &asn_OER_type_reg_BundleSize_constr_7, &asn_PER_type_reg_BundleSize_constr_7, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_reg_BundleSize_specs_7	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_interleaverSize_value2enum_11[] = {
	{ 0,	2,	"n2" },
	{ 1,	2,	"n3" },
	{ 2,	2,	"n6" }
};
static const unsigned int asn_MAP_interleaverSize_enum2value_11[] = {
	0,	/* n2(0) */
	1,	/* n3(1) */
	2	/* n6(2) */
};
static const asn_INTEGER_specifics_t asn_SPC_interleaverSize_specs_11 = {
	asn_MAP_interleaverSize_value2enum_11,	/* "tag" => N; sorted by tag */
	asn_MAP_interleaverSize_enum2value_11,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_interleaverSize_tags_11[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_interleaverSize_11 = {
	"interleaverSize",
	"interleaverSize",
	&asn_OP_NativeEnumerated,
	asn_DEF_interleaverSize_tags_11,
	sizeof(asn_DEF_interleaverSize_tags_11)
		/sizeof(asn_DEF_interleaverSize_tags_11[0]) - 1, /* 1 */
	asn_DEF_interleaverSize_tags_11,	/* Same as above */
	sizeof(asn_DEF_interleaverSize_tags_11)
		/sizeof(asn_DEF_interleaverSize_tags_11[0]), /* 2 */
	{ &asn_OER_type_interleaverSize_constr_11, &asn_PER_type_interleaverSize_constr_11, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_interleaverSize_specs_11	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_interleaved_6[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet__cce_REG_MappingType__interleaved, reg_BundleSize),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_reg_BundleSize_7,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reg-BundleSize"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet__cce_REG_MappingType__interleaved, interleaverSize),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_interleaverSize_11,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"interleaverSize"
		},
	{ ATF_POINTER, 1, offsetof(struct ControlResourceSet__cce_REG_MappingType__interleaved, shiftIndex),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_shiftIndex_constr_15, &asn_PER_memb_shiftIndex_constr_15,  memb_shiftIndex_constraint_6 },
		0, 0, /* No default value */
		"shiftIndex"
		},
};
static const int asn_MAP_interleaved_oms_6[] = { 2 };
static const ber_tlv_tag_t asn_DEF_interleaved_tags_6[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_interleaved_tag2el_6[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* reg-BundleSize */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* interleaverSize */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* shiftIndex */
};
static asn_SEQUENCE_specifics_t asn_SPC_interleaved_specs_6 = {
	sizeof(struct ControlResourceSet__cce_REG_MappingType__interleaved),
	offsetof(struct ControlResourceSet__cce_REG_MappingType__interleaved, _asn_ctx),
	asn_MAP_interleaved_tag2el_6,
	3,	/* Count of tags in the map */
	asn_MAP_interleaved_oms_6,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_interleaved_6 = {
	"interleaved",
	"interleaved",
	&asn_OP_SEQUENCE,
	asn_DEF_interleaved_tags_6,
	sizeof(asn_DEF_interleaved_tags_6)
		/sizeof(asn_DEF_interleaved_tags_6[0]) - 1, /* 1 */
	asn_DEF_interleaved_tags_6,	/* Same as above */
	sizeof(asn_DEF_interleaved_tags_6)
		/sizeof(asn_DEF_interleaved_tags_6[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_interleaved_6,
	3,	/* Elements count */
	&asn_SPC_interleaved_specs_6	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_cce_REG_MappingType_5[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet__cce_REG_MappingType, choice.interleaved),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_interleaved_6,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"interleaved"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet__cce_REG_MappingType, choice.nonInterleaved),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"nonInterleaved"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_cce_REG_MappingType_tag2el_5[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* interleaved */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonInterleaved */
};
static asn_CHOICE_specifics_t asn_SPC_cce_REG_MappingType_specs_5 = {
	sizeof(struct ControlResourceSet__cce_REG_MappingType),
	offsetof(struct ControlResourceSet__cce_REG_MappingType, _asn_ctx),
	offsetof(struct ControlResourceSet__cce_REG_MappingType, present),
	sizeof(((struct ControlResourceSet__cce_REG_MappingType *)0)->present),
	asn_MAP_cce_REG_MappingType_tag2el_5,
	2,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_cce_REG_MappingType_5 = {
	"cce-REG-MappingType",
	"cce-REG-MappingType",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_cce_REG_MappingType_constr_5, &asn_PER_type_cce_REG_MappingType_constr_5, CHOICE_constraint },
	asn_MBR_cce_REG_MappingType_5,
	2,	/* Elements count */
	&asn_SPC_cce_REG_MappingType_specs_5	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_precoderGranularity_value2enum_17[] = {
	{ 0,	16,	"sameAsREG-bundle" },
	{ 1,	16,	"allContiguousRBs" }
};
static const unsigned int asn_MAP_precoderGranularity_enum2value_17[] = {
	1,	/* allContiguousRBs(1) */
	0	/* sameAsREG-bundle(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_precoderGranularity_specs_17 = {
	asn_MAP_precoderGranularity_value2enum_17,	/* "tag" => N; sorted by tag */
	asn_MAP_precoderGranularity_enum2value_17,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_precoderGranularity_tags_17[] = {
	(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_precoderGranularity_17 = {
	"precoderGranularity",
	"precoderGranularity",
	&asn_OP_NativeEnumerated,
	asn_DEF_precoderGranularity_tags_17,
	sizeof(asn_DEF_precoderGranularity_tags_17)
		/sizeof(asn_DEF_precoderGranularity_tags_17[0]) - 1, /* 1 */
	asn_DEF_precoderGranularity_tags_17,	/* Same as above */
	sizeof(asn_DEF_precoderGranularity_tags_17)
		/sizeof(asn_DEF_precoderGranularity_tags_17[0]), /* 2 */
	{ &asn_OER_type_precoderGranularity_constr_17, &asn_PER_type_precoderGranularity_constr_17, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_precoderGranularity_specs_17	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tci_StatesPDCCH_ToAddList_20[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_TCI_StateId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_tci_StatesPDCCH_ToAddList_tags_20[] = {
	(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_tci_StatesPDCCH_ToAddList_specs_20 = {
	sizeof(struct ControlResourceSet__tci_StatesPDCCH_ToAddList),
	offsetof(struct ControlResourceSet__tci_StatesPDCCH_ToAddList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tci_StatesPDCCH_ToAddList_20 = {
	"tci-StatesPDCCH-ToAddList",
	"tci-StatesPDCCH-ToAddList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_tci_StatesPDCCH_ToAddList_tags_20,
	sizeof(asn_DEF_tci_StatesPDCCH_ToAddList_tags_20)
		/sizeof(asn_DEF_tci_StatesPDCCH_ToAddList_tags_20[0]) - 1, /* 1 */
	asn_DEF_tci_StatesPDCCH_ToAddList_tags_20,	/* Same as above */
	sizeof(asn_DEF_tci_StatesPDCCH_ToAddList_tags_20)
		/sizeof(asn_DEF_tci_StatesPDCCH_ToAddList_tags_20[0]), /* 2 */
	{ &asn_OER_type_tci_StatesPDCCH_ToAddList_constr_20, &asn_PER_type_tci_StatesPDCCH_ToAddList_constr_20, SEQUENCE_OF_constraint },
	asn_MBR_tci_StatesPDCCH_ToAddList_20,
	1,	/* Single element */
	&asn_SPC_tci_StatesPDCCH_ToAddList_specs_20	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_tci_StatesPDCCH_ToReleaseList_22[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_TCI_StateId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22[] = {
	(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_tci_StatesPDCCH_ToReleaseList_specs_22 = {
	sizeof(struct ControlResourceSet__tci_StatesPDCCH_ToReleaseList),
	offsetof(struct ControlResourceSet__tci_StatesPDCCH_ToReleaseList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tci_StatesPDCCH_ToReleaseList_22 = {
	"tci-StatesPDCCH-ToReleaseList",
	"tci-StatesPDCCH-ToReleaseList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22,
	sizeof(asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22)
		/sizeof(asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22[0]) - 1, /* 1 */
	asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22,	/* Same as above */
	sizeof(asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22)
		/sizeof(asn_DEF_tci_StatesPDCCH_ToReleaseList_tags_22[0]), /* 2 */
	{ &asn_OER_type_tci_StatesPDCCH_ToReleaseList_constr_22, &asn_PER_type_tci_StatesPDCCH_ToReleaseList_constr_22, SEQUENCE_OF_constraint },
	asn_MBR_tci_StatesPDCCH_ToReleaseList_22,
	1,	/* Single element */
	&asn_SPC_tci_StatesPDCCH_ToReleaseList_specs_22	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_tci_PresentInDCI_value2enum_24[] = {
	{ 0,	7,	"enabled" }
};
static const unsigned int asn_MAP_tci_PresentInDCI_enum2value_24[] = {
	0	/* enabled(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_tci_PresentInDCI_specs_24 = {
	asn_MAP_tci_PresentInDCI_value2enum_24,	/* "tag" => N; sorted by tag */
	asn_MAP_tci_PresentInDCI_enum2value_24,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_tci_PresentInDCI_tags_24[] = {
	(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_tci_PresentInDCI_24 = {
	"tci-PresentInDCI",
	"tci-PresentInDCI",
	&asn_OP_NativeEnumerated,
	asn_DEF_tci_PresentInDCI_tags_24,
	sizeof(asn_DEF_tci_PresentInDCI_tags_24)
		/sizeof(asn_DEF_tci_PresentInDCI_tags_24[0]) - 1, /* 1 */
	asn_DEF_tci_PresentInDCI_tags_24,	/* Same as above */
	sizeof(asn_DEF_tci_PresentInDCI_tags_24)
		/sizeof(asn_DEF_tci_PresentInDCI_tags_24[0]), /* 2 */
	{ &asn_OER_type_tci_PresentInDCI_constr_24, &asn_PER_type_tci_PresentInDCI_constr_24, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_tci_PresentInDCI_specs_24	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ControlResourceSet_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet, controlResourceSetId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ControlResourceSetId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"controlResourceSetId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet, frequencyDomainResources),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ &asn_OER_memb_frequencyDomainResources_constr_3, &asn_PER_memb_frequencyDomainResources_constr_3,  memb_frequencyDomainResources_constraint_1 },
		0, 0, /* No default value */
		"frequencyDomainResources"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet, duration),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_duration_constr_4, &asn_PER_memb_duration_constr_4,  memb_duration_constraint_1 },
		0, 0, /* No default value */
		"duration"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet, cce_REG_MappingType),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_cce_REG_MappingType_5,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cce-REG-MappingType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ControlResourceSet, precoderGranularity),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_precoderGranularity_17,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"precoderGranularity"
		},
	{ ATF_POINTER, 4, offsetof(struct ControlResourceSet, tci_StatesPDCCH_ToAddList),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		0,
		&asn_DEF_tci_StatesPDCCH_ToAddList_20,
		0,
		{ &asn_OER_memb_tci_StatesPDCCH_ToAddList_constr_20, &asn_PER_memb_tci_StatesPDCCH_ToAddList_constr_20,  memb_tci_StatesPDCCH_ToAddList_constraint_1 },
		0, 0, /* No default value */
		"tci-StatesPDCCH-ToAddList"
		},
	{ ATF_POINTER, 3, offsetof(struct ControlResourceSet, tci_StatesPDCCH_ToReleaseList),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		0,
		&asn_DEF_tci_StatesPDCCH_ToReleaseList_22,
		0,
		{ &asn_OER_memb_tci_StatesPDCCH_ToReleaseList_constr_22, &asn_PER_memb_tci_StatesPDCCH_ToReleaseList_constr_22,  memb_tci_StatesPDCCH_ToReleaseList_constraint_1 },
		0, 0, /* No default value */
		"tci-StatesPDCCH-ToReleaseList"
		},
	{ ATF_POINTER, 2, offsetof(struct ControlResourceSet, tci_PresentInDCI),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_tci_PresentInDCI_24,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"tci-PresentInDCI"
		},
	{ ATF_POINTER, 1, offsetof(struct ControlResourceSet, pdcch_DMRS_ScramblingID),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_pdcch_DMRS_ScramblingID_constr_26, &asn_PER_memb_pdcch_DMRS_ScramblingID_constr_26,  memb_pdcch_DMRS_ScramblingID_constraint_1 },
		0, 0, /* No default value */
		"pdcch-DMRS-ScramblingID"
		},
};
static const int asn_MAP_ControlResourceSet_oms_1[] = { 5, 6, 7, 8 };
static const ber_tlv_tag_t asn_DEF_ControlResourceSet_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ControlResourceSet_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* controlResourceSetId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* frequencyDomainResources */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* duration */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* cce-REG-MappingType */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* precoderGranularity */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* tci-StatesPDCCH-ToAddList */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* tci-StatesPDCCH-ToReleaseList */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* tci-PresentInDCI */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 } /* pdcch-DMRS-ScramblingID */
};
asn_SEQUENCE_specifics_t asn_SPC_ControlResourceSet_specs_1 = {
	sizeof(struct ControlResourceSet),
	offsetof(struct ControlResourceSet, _asn_ctx),
	asn_MAP_ControlResourceSet_tag2el_1,
	9,	/* Count of tags in the map */
	asn_MAP_ControlResourceSet_oms_1,	/* Optional members */
	4, 0,	/* Root/Additions */
	9,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ControlResourceSet = {
	"ControlResourceSet",
	"ControlResourceSet",
	&asn_OP_SEQUENCE,
	asn_DEF_ControlResourceSet_tags_1,
	sizeof(asn_DEF_ControlResourceSet_tags_1)
		/sizeof(asn_DEF_ControlResourceSet_tags_1[0]), /* 1 */
	asn_DEF_ControlResourceSet_tags_1,	/* Same as above */
	sizeof(asn_DEF_ControlResourceSet_tags_1)
		/sizeof(asn_DEF_ControlResourceSet_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ControlResourceSet_1,
	9,	/* Elements count */
	&asn_SPC_ControlResourceSet_specs_1	/* Additional specs */
};

