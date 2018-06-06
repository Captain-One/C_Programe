/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "CQI-ReportConfigSCell-r10.h"

static int
pmi_RI_Report_r10_5_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
pmi_RI_Report_r10_5_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

static void
pmi_RI_Report_r10_5_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
pmi_RI_Report_r10_5_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
pmi_RI_Report_r10_5_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
pmi_RI_Report_r10_5_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
pmi_RI_Report_r10_5_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
pmi_RI_Report_r10_5_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
pmi_RI_Report_r10_5_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
pmi_RI_Report_r10_5_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	pmi_RI_Report_r10_5_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
memb_nomPDSCH_RS_EPRE_Offset_r10_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= -1 && value <= 6)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_pmi_RI_Report_r10_constr_5 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_nomPDSCH_RS_EPRE_Offset_r10_constr_3 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3, -1,  6 }	/* (-1..6) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_pmi_RI_Report_r10_value2enum_5[] = {
	{ 0,	5,	"setup" }
};
static const unsigned int asn_MAP_pmi_RI_Report_r10_enum2value_5[] = {
	0	/* setup(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_pmi_RI_Report_r10_specs_5 = {
	asn_MAP_pmi_RI_Report_r10_value2enum_5,	/* "tag" => N; sorted by tag */
	asn_MAP_pmi_RI_Report_r10_enum2value_5,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_pmi_RI_Report_r10_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_pmi_RI_Report_r10_5 = {
	"pmi-RI-Report-r10",
	"pmi-RI-Report-r10",
	pmi_RI_Report_r10_5_free,
	pmi_RI_Report_r10_5_print,
	pmi_RI_Report_r10_5_constraint,
	pmi_RI_Report_r10_5_decode_ber,
	pmi_RI_Report_r10_5_encode_der,
	pmi_RI_Report_r10_5_decode_xer,
	pmi_RI_Report_r10_5_encode_xer,
	pmi_RI_Report_r10_5_decode_uper,
	pmi_RI_Report_r10_5_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_pmi_RI_Report_r10_tags_5,
	sizeof(asn_DEF_pmi_RI_Report_r10_tags_5)
		/sizeof(asn_DEF_pmi_RI_Report_r10_tags_5[0]) - 1, /* 1 */
	asn_DEF_pmi_RI_Report_r10_tags_5,	/* Same as above */
	sizeof(asn_DEF_pmi_RI_Report_r10_tags_5)
		/sizeof(asn_DEF_pmi_RI_Report_r10_tags_5[0]), /* 2 */
	&asn_PER_type_pmi_RI_Report_r10_constr_5,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_pmi_RI_Report_r10_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_CQI_ReportConfigSCell_r10_1[] = {
	{ ATF_POINTER, 1, offsetof(struct CQI_ReportConfigSCell_r10, cqi_ReportModeAperiodic_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CQI_ReportModeAperiodic,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cqi-ReportModeAperiodic-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CQI_ReportConfigSCell_r10, nomPDSCH_RS_EPRE_Offset_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_nomPDSCH_RS_EPRE_Offset_r10_constraint_1,
		&asn_PER_memb_nomPDSCH_RS_EPRE_Offset_r10_constr_3,
		0,
		"nomPDSCH-RS-EPRE-Offset-r10"
		},
	{ ATF_POINTER, 2, offsetof(struct CQI_ReportConfigSCell_r10, cqi_ReportPeriodicSCell_r10),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_CQI_ReportPeriodic_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cqi-ReportPeriodicSCell-r10"
		},
	{ ATF_POINTER, 1, offsetof(struct CQI_ReportConfigSCell_r10, pmi_RI_Report_r10),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_pmi_RI_Report_r10_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pmi-RI-Report-r10"
		},
};
static const int asn_MAP_CQI_ReportConfigSCell_r10_oms_1[] = { 0, 2, 3 };
static const ber_tlv_tag_t asn_DEF_CQI_ReportConfigSCell_r10_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CQI_ReportConfigSCell_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cqi-ReportModeAperiodic-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* nomPDSCH-RS-EPRE-Offset-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* cqi-ReportPeriodicSCell-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* pmi-RI-Report-r10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_CQI_ReportConfigSCell_r10_specs_1 = {
	sizeof(struct CQI_ReportConfigSCell_r10),
	offsetof(struct CQI_ReportConfigSCell_r10, _asn_ctx),
	asn_MAP_CQI_ReportConfigSCell_r10_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_CQI_ReportConfigSCell_r10_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_CQI_ReportConfigSCell_r10 = {
	"CQI-ReportConfigSCell-r10",
	"CQI-ReportConfigSCell-r10",
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
	asn_DEF_CQI_ReportConfigSCell_r10_tags_1,
	sizeof(asn_DEF_CQI_ReportConfigSCell_r10_tags_1)
		/sizeof(asn_DEF_CQI_ReportConfigSCell_r10_tags_1[0]), /* 1 */
	asn_DEF_CQI_ReportConfigSCell_r10_tags_1,	/* Same as above */
	sizeof(asn_DEF_CQI_ReportConfigSCell_r10_tags_1)
		/sizeof(asn_DEF_CQI_ReportConfigSCell_r10_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CQI_ReportConfigSCell_r10_1,
	4,	/* Elements count */
	&asn_SPC_CQI_ReportConfigSCell_r10_specs_1	/* Additional specs */
};

