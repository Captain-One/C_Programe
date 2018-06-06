/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "DeltaTxD-OffsetListPUCCH-r10.h"

static int
deltaTxD_OffsetPUCCH_Format1_r10_2_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
deltaTxD_OffsetPUCCH_Format1_r10_2_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
deltaTxD_OffsetPUCCH_Format1_r10_2_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format1_r10_2_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format1_r10_2_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format1_r10_2_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format1_r10_2_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format1_r10_2_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format1_r10_2_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	deltaTxD_OffsetPUCCH_Format1_r10_2_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format1a1b_r10_5_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format22a2b_r10_8_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
deltaTxD_OffsetPUCCH_Format3_r10_11_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
deltaTxD_OffsetPUCCH_Format3_r10_11_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
deltaTxD_OffsetPUCCH_Format3_r10_11_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format3_r10_11_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format3_r10_11_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format3_r10_11_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format3_r10_11_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
deltaTxD_OffsetPUCCH_Format3_r10_11_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
deltaTxD_OffsetPUCCH_Format3_r10_11_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	deltaTxD_OffsetPUCCH_Format3_r10_11_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_per_constraints_t asn_PER_type_deltaTxD_OffsetPUCCH_Format1_r10_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_deltaTxD_OffsetPUCCH_Format1a1b_r10_constr_5 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_deltaTxD_OffsetPUCCH_Format22a2b_r10_constr_8 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_deltaTxD_OffsetPUCCH_Format3_r10_constr_11 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_deltaTxD_OffsetPUCCH_Format1_r10_value2enum_2[] = {
	{ 0,	3,	"dB0" },
	{ 1,	4,	"dB-2" }
};
static const unsigned int asn_MAP_deltaTxD_OffsetPUCCH_Format1_r10_enum2value_2[] = {
	1,	/* dB-2(1) */
	0	/* dB0(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_deltaTxD_OffsetPUCCH_Format1_r10_specs_2 = {
	asn_MAP_deltaTxD_OffsetPUCCH_Format1_r10_value2enum_2,	/* "tag" => N; sorted by tag */
	asn_MAP_deltaTxD_OffsetPUCCH_Format1_r10_enum2value_2,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_2 = {
	"deltaTxD-OffsetPUCCH-Format1-r10",
	"deltaTxD-OffsetPUCCH-Format1-r10",
	deltaTxD_OffsetPUCCH_Format1_r10_2_free,
	deltaTxD_OffsetPUCCH_Format1_r10_2_print,
	deltaTxD_OffsetPUCCH_Format1_r10_2_constraint,
	deltaTxD_OffsetPUCCH_Format1_r10_2_decode_ber,
	deltaTxD_OffsetPUCCH_Format1_r10_2_encode_der,
	deltaTxD_OffsetPUCCH_Format1_r10_2_decode_xer,
	deltaTxD_OffsetPUCCH_Format1_r10_2_encode_xer,
	deltaTxD_OffsetPUCCH_Format1_r10_2_decode_uper,
	deltaTxD_OffsetPUCCH_Format1_r10_2_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2,
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2[0]) - 1, /* 1 */
	asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2,	/* Same as above */
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_tags_2[0]), /* 2 */
	&asn_PER_type_deltaTxD_OffsetPUCCH_Format1_r10_constr_2,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_deltaTxD_OffsetPUCCH_Format1_r10_specs_2	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_deltaTxD_OffsetPUCCH_Format1a1b_r10_value2enum_5[] = {
	{ 0,	3,	"dB0" },
	{ 1,	4,	"dB-2" }
};
static const unsigned int asn_MAP_deltaTxD_OffsetPUCCH_Format1a1b_r10_enum2value_5[] = {
	1,	/* dB-2(1) */
	0	/* dB0(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_deltaTxD_OffsetPUCCH_Format1a1b_r10_specs_5 = {
	asn_MAP_deltaTxD_OffsetPUCCH_Format1a1b_r10_value2enum_5,	/* "tag" => N; sorted by tag */
	asn_MAP_deltaTxD_OffsetPUCCH_Format1a1b_r10_enum2value_5,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_5 = {
	"deltaTxD-OffsetPUCCH-Format1a1b-r10",
	"deltaTxD-OffsetPUCCH-Format1a1b-r10",
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_free,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_print,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_constraint,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_decode_ber,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_encode_der,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_decode_xer,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_encode_xer,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_decode_uper,
	deltaTxD_OffsetPUCCH_Format1a1b_r10_5_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5,
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5[0]) - 1, /* 1 */
	asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5,	/* Same as above */
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_tags_5[0]), /* 2 */
	&asn_PER_type_deltaTxD_OffsetPUCCH_Format1a1b_r10_constr_5,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_deltaTxD_OffsetPUCCH_Format1a1b_r10_specs_5	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_deltaTxD_OffsetPUCCH_Format22a2b_r10_value2enum_8[] = {
	{ 0,	3,	"dB0" },
	{ 1,	4,	"dB-2" }
};
static const unsigned int asn_MAP_deltaTxD_OffsetPUCCH_Format22a2b_r10_enum2value_8[] = {
	1,	/* dB-2(1) */
	0	/* dB0(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_deltaTxD_OffsetPUCCH_Format22a2b_r10_specs_8 = {
	asn_MAP_deltaTxD_OffsetPUCCH_Format22a2b_r10_value2enum_8,	/* "tag" => N; sorted by tag */
	asn_MAP_deltaTxD_OffsetPUCCH_Format22a2b_r10_enum2value_8,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_8 = {
	"deltaTxD-OffsetPUCCH-Format22a2b-r10",
	"deltaTxD-OffsetPUCCH-Format22a2b-r10",
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_free,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_print,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_constraint,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_decode_ber,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_encode_der,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_decode_xer,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_encode_xer,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_decode_uper,
	deltaTxD_OffsetPUCCH_Format22a2b_r10_8_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8,
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8[0]) - 1, /* 1 */
	asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8,	/* Same as above */
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_tags_8[0]), /* 2 */
	&asn_PER_type_deltaTxD_OffsetPUCCH_Format22a2b_r10_constr_8,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_deltaTxD_OffsetPUCCH_Format22a2b_r10_specs_8	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_deltaTxD_OffsetPUCCH_Format3_r10_value2enum_11[] = {
	{ 0,	3,	"dB0" },
	{ 1,	4,	"dB-2" }
};
static const unsigned int asn_MAP_deltaTxD_OffsetPUCCH_Format3_r10_enum2value_11[] = {
	1,	/* dB-2(1) */
	0	/* dB0(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_deltaTxD_OffsetPUCCH_Format3_r10_specs_11 = {
	asn_MAP_deltaTxD_OffsetPUCCH_Format3_r10_value2enum_11,	/* "tag" => N; sorted by tag */
	asn_MAP_deltaTxD_OffsetPUCCH_Format3_r10_enum2value_11,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11[] = {
	(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_11 = {
	"deltaTxD-OffsetPUCCH-Format3-r10",
	"deltaTxD-OffsetPUCCH-Format3-r10",
	deltaTxD_OffsetPUCCH_Format3_r10_11_free,
	deltaTxD_OffsetPUCCH_Format3_r10_11_print,
	deltaTxD_OffsetPUCCH_Format3_r10_11_constraint,
	deltaTxD_OffsetPUCCH_Format3_r10_11_decode_ber,
	deltaTxD_OffsetPUCCH_Format3_r10_11_encode_der,
	deltaTxD_OffsetPUCCH_Format3_r10_11_decode_xer,
	deltaTxD_OffsetPUCCH_Format3_r10_11_encode_xer,
	deltaTxD_OffsetPUCCH_Format3_r10_11_decode_uper,
	deltaTxD_OffsetPUCCH_Format3_r10_11_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11,
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11[0]) - 1, /* 1 */
	asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11,	/* Same as above */
	sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11)
		/sizeof(asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_tags_11[0]), /* 2 */
	&asn_PER_type_deltaTxD_OffsetPUCCH_Format3_r10_constr_11,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_deltaTxD_OffsetPUCCH_Format3_r10_specs_11	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_DeltaTxD_OffsetListPUCCH_r10_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DeltaTxD_OffsetListPUCCH_r10, deltaTxD_OffsetPUCCH_Format1_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_deltaTxD_OffsetPUCCH_Format1_r10_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"deltaTxD-OffsetPUCCH-Format1-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DeltaTxD_OffsetListPUCCH_r10, deltaTxD_OffsetPUCCH_Format1a1b_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_deltaTxD_OffsetPUCCH_Format1a1b_r10_5,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"deltaTxD-OffsetPUCCH-Format1a1b-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DeltaTxD_OffsetListPUCCH_r10, deltaTxD_OffsetPUCCH_Format22a2b_r10),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_deltaTxD_OffsetPUCCH_Format22a2b_r10_8,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"deltaTxD-OffsetPUCCH-Format22a2b-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DeltaTxD_OffsetListPUCCH_r10, deltaTxD_OffsetPUCCH_Format3_r10),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_deltaTxD_OffsetPUCCH_Format3_r10_11,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"deltaTxD-OffsetPUCCH-Format3-r10"
		},
};
static const ber_tlv_tag_t asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_DeltaTxD_OffsetListPUCCH_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* deltaTxD-OffsetPUCCH-Format1-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* deltaTxD-OffsetPUCCH-Format1a1b-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* deltaTxD-OffsetPUCCH-Format22a2b-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* deltaTxD-OffsetPUCCH-Format3-r10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_DeltaTxD_OffsetListPUCCH_r10_specs_1 = {
	sizeof(struct DeltaTxD_OffsetListPUCCH_r10),
	offsetof(struct DeltaTxD_OffsetListPUCCH_r10, _asn_ctx),
	asn_MAP_DeltaTxD_OffsetListPUCCH_r10_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* Start extensions */
	5	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_DeltaTxD_OffsetListPUCCH_r10 = {
	"DeltaTxD-OffsetListPUCCH-r10",
	"DeltaTxD-OffsetListPUCCH-r10",
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
	asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1,
	sizeof(asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1)
		/sizeof(asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1[0]), /* 1 */
	asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1,	/* Same as above */
	sizeof(asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1)
		/sizeof(asn_DEF_DeltaTxD_OffsetListPUCCH_r10_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_DeltaTxD_OffsetListPUCCH_r10_1,
	4,	/* Elements count */
	&asn_SPC_DeltaTxD_OffsetListPUCCH_r10_specs_1	/* Additional specs */
};

