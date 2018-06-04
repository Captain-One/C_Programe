/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "CQI-ReportModeAperiodic.h"

int
CQI_ReportModeAperiodic_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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

void
CQI_ReportModeAperiodic_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

int
CQI_ReportModeAperiodic_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

asn_dec_rval_t
CQI_ReportModeAperiodic_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

asn_enc_rval_t
CQI_ReportModeAperiodic_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

asn_dec_rval_t
CQI_ReportModeAperiodic_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

asn_enc_rval_t
CQI_ReportModeAperiodic_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

asn_dec_rval_t
CQI_ReportModeAperiodic_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

asn_enc_rval_t
CQI_ReportModeAperiodic_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	CQI_ReportModeAperiodic_1_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_per_constraints_t asn_PER_type_CQI_ReportModeAperiodic_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_CQI_ReportModeAperiodic_value2enum_1[] = {
	{ 0,	4,	"rm12" },
	{ 1,	4,	"rm20" },
	{ 2,	4,	"rm22" },
	{ 3,	4,	"rm30" },
	{ 4,	4,	"rm31" },
	{ 5,	6,	"spare3" },
	{ 6,	6,	"spare2" },
	{ 7,	6,	"spare1" }
};
static const unsigned int asn_MAP_CQI_ReportModeAperiodic_enum2value_1[] = {
	0,	/* rm12(0) */
	1,	/* rm20(1) */
	2,	/* rm22(2) */
	3,	/* rm30(3) */
	4,	/* rm31(4) */
	7,	/* spare1(7) */
	6,	/* spare2(6) */
	5	/* spare3(5) */
};
static const asn_INTEGER_specifics_t asn_SPC_CQI_ReportModeAperiodic_specs_1 = {
	asn_MAP_CQI_ReportModeAperiodic_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_CQI_ReportModeAperiodic_enum2value_1,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_CQI_ReportModeAperiodic_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_CQI_ReportModeAperiodic = {
	"CQI-ReportModeAperiodic",
	"CQI-ReportModeAperiodic",
	CQI_ReportModeAperiodic_free,
	CQI_ReportModeAperiodic_print,
	CQI_ReportModeAperiodic_constraint,
	CQI_ReportModeAperiodic_decode_ber,
	CQI_ReportModeAperiodic_encode_der,
	CQI_ReportModeAperiodic_decode_xer,
	CQI_ReportModeAperiodic_encode_xer,
	CQI_ReportModeAperiodic_decode_uper,
	CQI_ReportModeAperiodic_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_CQI_ReportModeAperiodic_tags_1,
	sizeof(asn_DEF_CQI_ReportModeAperiodic_tags_1)
		/sizeof(asn_DEF_CQI_ReportModeAperiodic_tags_1[0]), /* 1 */
	asn_DEF_CQI_ReportModeAperiodic_tags_1,	/* Same as above */
	sizeof(asn_DEF_CQI_ReportModeAperiodic_tags_1)
		/sizeof(asn_DEF_CQI_ReportModeAperiodic_tags_1[0]), /* 1 */
	&asn_PER_type_CQI_ReportModeAperiodic_constr_1,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_CQI_ReportModeAperiodic_specs_1	/* Additional specs */
};

