/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-UE-Variables"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "VarLogMeasReport-r10.h"

static int
memb_traceRecordingSessionRef_r10_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 2)) {
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
memb_tce_Id_r10_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 1)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_traceRecordingSessionRef_r10_constr_3 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  2,  2 }	/* (SIZE(2..2)) */,
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_tce_Id_r10_constr_4 GCC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  1,  1 }	/* (SIZE(1..1)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_VarLogMeasReport_r10_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct VarLogMeasReport_r10, traceReference_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TraceReference_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"traceReference-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarLogMeasReport_r10, traceRecordingSessionRef_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_traceRecordingSessionRef_r10_constraint_1,
		&asn_PER_memb_traceRecordingSessionRef_r10_constr_3,
		0,
		"traceRecordingSessionRef-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarLogMeasReport_r10, tce_Id_r10),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_tce_Id_r10_constraint_1,
		&asn_PER_memb_tce_Id_r10_constr_4,
		0,
		"tce-Id-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarLogMeasReport_r10, plmn_Identity_r10),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PLMN_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"plmn-Identity-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarLogMeasReport_r10, absoluteTimeInfo_r10),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AbsoluteTimeInfo_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"absoluteTimeInfo-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarLogMeasReport_r10, logMeasInfoList_r10),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LogMeasInfoList2_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"logMeasInfoList-r10"
		},
};
static const ber_tlv_tag_t asn_DEF_VarLogMeasReport_r10_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_VarLogMeasReport_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* traceReference-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* traceRecordingSessionRef-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* tce-Id-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* plmn-Identity-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* absoluteTimeInfo-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* logMeasInfoList-r10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_VarLogMeasReport_r10_specs_1 = {
	sizeof(struct VarLogMeasReport_r10),
	offsetof(struct VarLogMeasReport_r10, _asn_ctx),
	asn_MAP_VarLogMeasReport_r10_tag2el_1,
	6,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_VarLogMeasReport_r10 = {
	"VarLogMeasReport-r10",
	"VarLogMeasReport-r10",
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
	asn_DEF_VarLogMeasReport_r10_tags_1,
	sizeof(asn_DEF_VarLogMeasReport_r10_tags_1)
		/sizeof(asn_DEF_VarLogMeasReport_r10_tags_1[0]), /* 1 */
	asn_DEF_VarLogMeasReport_r10_tags_1,	/* Same as above */
	sizeof(asn_DEF_VarLogMeasReport_r10_tags_1)
		/sizeof(asn_DEF_VarLogMeasReport_r10_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_VarLogMeasReport_r10_1,
	6,	/* Elements count */
	&asn_SPC_VarLogMeasReport_r10_specs_1	/* Additional specs */
};

