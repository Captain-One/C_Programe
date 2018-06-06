/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "SystemInformation-r8-IEs.h"

static int
memb_sib_TypeAndInfo_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
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
		return td->check_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_Member_constr_3 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  9 }	/* (0..9,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_sib_TypeAndInfo_constr_2 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_sib_TypeAndInfo_constr_2 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_Member_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib2),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib3),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib3"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib4),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib4"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib5),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib5"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib6),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType6,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib6"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib7),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType7,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib7"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib8),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType8,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib8"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib9),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib9"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib10),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib11),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib11"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib12_v920),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType12_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib12-v920"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, choice.sib13_v920),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformationBlockType13_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sib13-v920"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_Member_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sib2 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* sib3 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* sib4 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* sib5 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* sib6 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* sib7 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* sib8 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* sib9 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* sib10 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* sib11 */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* sib12-v920 */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 } /* sib13-v920 */
};
static asn_CHOICE_specifics_t asn_SPC_Member_specs_3 = {
	sizeof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member),
	offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, _asn_ctx),
	offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member, present),
	sizeof(((struct SystemInformation_r8_IEs__sib_TypeAndInfo__Member *)0)->present),
	asn_MAP_Member_tag2el_3,
	12,	/* Count of tags in the map */
	0,
	10	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_Member_3 = {
	"CHOICE",
	"CHOICE",
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
	&asn_PER_type_Member_constr_3,
	asn_MBR_Member_3,
	12,	/* Elements count */
	&asn_SPC_Member_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_sib_TypeAndInfo_2[] = {
	{ ATF_POINTER, 0, 0,
		-1 /* Ambiguous tag (CHOICE?) */,
		0,
		&asn_DEF_Member_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		""
		},
};
static const ber_tlv_tag_t asn_DEF_sib_TypeAndInfo_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_sib_TypeAndInfo_specs_2 = {
	sizeof(struct SystemInformation_r8_IEs__sib_TypeAndInfo),
	offsetof(struct SystemInformation_r8_IEs__sib_TypeAndInfo, _asn_ctx),
	2,	/* XER encoding is XMLValueList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_sib_TypeAndInfo_2 = {
	"sib-TypeAndInfo",
	"sib-TypeAndInfo",
	SEQUENCE_OF_free,
	SEQUENCE_OF_print,
	SEQUENCE_OF_constraint,
	SEQUENCE_OF_decode_ber,
	SEQUENCE_OF_encode_der,
	SEQUENCE_OF_decode_xer,
	SEQUENCE_OF_encode_xer,
	SEQUENCE_OF_decode_uper,
	SEQUENCE_OF_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_sib_TypeAndInfo_tags_2,
	sizeof(asn_DEF_sib_TypeAndInfo_tags_2)
		/sizeof(asn_DEF_sib_TypeAndInfo_tags_2[0]) - 1, /* 1 */
	asn_DEF_sib_TypeAndInfo_tags_2,	/* Same as above */
	sizeof(asn_DEF_sib_TypeAndInfo_tags_2)
		/sizeof(asn_DEF_sib_TypeAndInfo_tags_2[0]), /* 2 */
	&asn_PER_type_sib_TypeAndInfo_constr_2,
	asn_MBR_sib_TypeAndInfo_2,
	1,	/* Single element */
	&asn_SPC_sib_TypeAndInfo_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SystemInformation_r8_IEs_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SystemInformation_r8_IEs, sib_TypeAndInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_sib_TypeAndInfo_2,
		memb_sib_TypeAndInfo_constraint_1,
		&asn_PER_memb_sib_TypeAndInfo_constr_2,
		0,
		"sib-TypeAndInfo"
		},
	{ ATF_POINTER, 1, offsetof(struct SystemInformation_r8_IEs, nonCriticalExtension),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SystemInformation_v8a0_IEs,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"nonCriticalExtension"
		},
};
static const int asn_MAP_SystemInformation_r8_IEs_oms_1[] = { 1 };
static const ber_tlv_tag_t asn_DEF_SystemInformation_r8_IEs_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SystemInformation_r8_IEs_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sib-TypeAndInfo */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* nonCriticalExtension */
};
static asn_SEQUENCE_specifics_t asn_SPC_SystemInformation_r8_IEs_specs_1 = {
	sizeof(struct SystemInformation_r8_IEs),
	offsetof(struct SystemInformation_r8_IEs, _asn_ctx),
	asn_MAP_SystemInformation_r8_IEs_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_SystemInformation_r8_IEs_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SystemInformation_r8_IEs = {
	"SystemInformation-r8-IEs",
	"SystemInformation-r8-IEs",
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
	asn_DEF_SystemInformation_r8_IEs_tags_1,
	sizeof(asn_DEF_SystemInformation_r8_IEs_tags_1)
		/sizeof(asn_DEF_SystemInformation_r8_IEs_tags_1[0]), /* 1 */
	asn_DEF_SystemInformation_r8_IEs_tags_1,	/* Same as above */
	sizeof(asn_DEF_SystemInformation_r8_IEs_tags_1)
		/sizeof(asn_DEF_SystemInformation_r8_IEs_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SystemInformation_r8_IEs_1,
	2,	/* Elements count */
	&asn_SPC_SystemInformation_r8_IEs_specs_1	/* Additional specs */
};

