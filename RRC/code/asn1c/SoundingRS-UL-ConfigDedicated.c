/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "SoundingRS-UL-ConfigDedicated.h"

static int
srs_Bandwidth_4_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
srs_Bandwidth_4_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
srs_Bandwidth_4_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
srs_Bandwidth_4_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
srs_Bandwidth_4_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
srs_Bandwidth_4_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
srs_Bandwidth_4_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
srs_Bandwidth_4_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
srs_Bandwidth_4_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
srs_Bandwidth_4_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	srs_Bandwidth_4_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
srs_HoppingBandwidth_9_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
srs_HoppingBandwidth_9_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
srs_HoppingBandwidth_9_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
srs_HoppingBandwidth_9_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
srs_HoppingBandwidth_9_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
srs_HoppingBandwidth_9_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
srs_HoppingBandwidth_9_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
srs_HoppingBandwidth_9_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
srs_HoppingBandwidth_9_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
srs_HoppingBandwidth_9_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	srs_HoppingBandwidth_9_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
cyclicShift_18_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
cyclicShift_18_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
cyclicShift_18_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
cyclicShift_18_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
cyclicShift_18_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
cyclicShift_18_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
cyclicShift_18_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
cyclicShift_18_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
cyclicShift_18_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
cyclicShift_18_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	cyclicShift_18_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
memb_freqDomainPosition_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 23)) {
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
memb_srs_ConfigIndex_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 1023)) {
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
memb_transmissionComb_constraint_3(asn_TYPE_descriptor_t *td, const void *sptr,
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

static asn_per_constraints_t asn_PER_type_srs_Bandwidth_constr_4 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_srs_HoppingBandwidth_constr_9 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_cyclicShift_constr_18 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_freqDomainPosition_constr_14 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  0,  23 }	/* (0..23) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_srs_ConfigIndex_constr_16 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 10,  10,  0,  1023 }	/* (0..1023) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_transmissionComb_constr_17 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_SoundingRS_UL_ConfigDedicated_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_srs_Bandwidth_value2enum_4[] = {
	{ 0,	3,	"bw0" },
	{ 1,	3,	"bw1" },
	{ 2,	3,	"bw2" },
	{ 3,	3,	"bw3" }
};
static const unsigned int asn_MAP_srs_Bandwidth_enum2value_4[] = {
	0,	/* bw0(0) */
	1,	/* bw1(1) */
	2,	/* bw2(2) */
	3	/* bw3(3) */
};
static const asn_INTEGER_specifics_t asn_SPC_srs_Bandwidth_specs_4 = {
	asn_MAP_srs_Bandwidth_value2enum_4,	/* "tag" => N; sorted by tag */
	asn_MAP_srs_Bandwidth_enum2value_4,	/* N => "tag"; sorted by N */
	4,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_srs_Bandwidth_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_srs_Bandwidth_4 = {
	"srs-Bandwidth",
	"srs-Bandwidth",
	srs_Bandwidth_4_free,
	srs_Bandwidth_4_print,
	srs_Bandwidth_4_constraint,
	srs_Bandwidth_4_decode_ber,
	srs_Bandwidth_4_encode_der,
	srs_Bandwidth_4_decode_xer,
	srs_Bandwidth_4_encode_xer,
	srs_Bandwidth_4_decode_uper,
	srs_Bandwidth_4_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_srs_Bandwidth_tags_4,
	sizeof(asn_DEF_srs_Bandwidth_tags_4)
		/sizeof(asn_DEF_srs_Bandwidth_tags_4[0]) - 1, /* 1 */
	asn_DEF_srs_Bandwidth_tags_4,	/* Same as above */
	sizeof(asn_DEF_srs_Bandwidth_tags_4)
		/sizeof(asn_DEF_srs_Bandwidth_tags_4[0]), /* 2 */
	&asn_PER_type_srs_Bandwidth_constr_4,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_srs_Bandwidth_specs_4	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_srs_HoppingBandwidth_value2enum_9[] = {
	{ 0,	4,	"hbw0" },
	{ 1,	4,	"hbw1" },
	{ 2,	4,	"hbw2" },
	{ 3,	4,	"hbw3" }
};
static const unsigned int asn_MAP_srs_HoppingBandwidth_enum2value_9[] = {
	0,	/* hbw0(0) */
	1,	/* hbw1(1) */
	2,	/* hbw2(2) */
	3	/* hbw3(3) */
};
static const asn_INTEGER_specifics_t asn_SPC_srs_HoppingBandwidth_specs_9 = {
	asn_MAP_srs_HoppingBandwidth_value2enum_9,	/* "tag" => N; sorted by tag */
	asn_MAP_srs_HoppingBandwidth_enum2value_9,	/* N => "tag"; sorted by N */
	4,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_srs_HoppingBandwidth_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_srs_HoppingBandwidth_9 = {
	"srs-HoppingBandwidth",
	"srs-HoppingBandwidth",
	srs_HoppingBandwidth_9_free,
	srs_HoppingBandwidth_9_print,
	srs_HoppingBandwidth_9_constraint,
	srs_HoppingBandwidth_9_decode_ber,
	srs_HoppingBandwidth_9_encode_der,
	srs_HoppingBandwidth_9_decode_xer,
	srs_HoppingBandwidth_9_encode_xer,
	srs_HoppingBandwidth_9_decode_uper,
	srs_HoppingBandwidth_9_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_srs_HoppingBandwidth_tags_9,
	sizeof(asn_DEF_srs_HoppingBandwidth_tags_9)
		/sizeof(asn_DEF_srs_HoppingBandwidth_tags_9[0]) - 1, /* 1 */
	asn_DEF_srs_HoppingBandwidth_tags_9,	/* Same as above */
	sizeof(asn_DEF_srs_HoppingBandwidth_tags_9)
		/sizeof(asn_DEF_srs_HoppingBandwidth_tags_9[0]), /* 2 */
	&asn_PER_type_srs_HoppingBandwidth_constr_9,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_srs_HoppingBandwidth_specs_9	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_cyclicShift_value2enum_18[] = {
	{ 0,	3,	"cs0" },
	{ 1,	3,	"cs1" },
	{ 2,	3,	"cs2" },
	{ 3,	3,	"cs3" },
	{ 4,	3,	"cs4" },
	{ 5,	3,	"cs5" },
	{ 6,	3,	"cs6" },
	{ 7,	3,	"cs7" }
};
static const unsigned int asn_MAP_cyclicShift_enum2value_18[] = {
	0,	/* cs0(0) */
	1,	/* cs1(1) */
	2,	/* cs2(2) */
	3,	/* cs3(3) */
	4,	/* cs4(4) */
	5,	/* cs5(5) */
	6,	/* cs6(6) */
	7	/* cs7(7) */
};
static const asn_INTEGER_specifics_t asn_SPC_cyclicShift_specs_18 = {
	asn_MAP_cyclicShift_value2enum_18,	/* "tag" => N; sorted by tag */
	asn_MAP_cyclicShift_enum2value_18,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_cyclicShift_tags_18[] = {
	(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_cyclicShift_18 = {
	"cyclicShift",
	"cyclicShift",
	cyclicShift_18_free,
	cyclicShift_18_print,
	cyclicShift_18_constraint,
	cyclicShift_18_decode_ber,
	cyclicShift_18_encode_der,
	cyclicShift_18_decode_xer,
	cyclicShift_18_encode_xer,
	cyclicShift_18_decode_uper,
	cyclicShift_18_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_cyclicShift_tags_18,
	sizeof(asn_DEF_cyclicShift_tags_18)
		/sizeof(asn_DEF_cyclicShift_tags_18[0]) - 1, /* 1 */
	asn_DEF_cyclicShift_tags_18,	/* Same as above */
	sizeof(asn_DEF_cyclicShift_tags_18)
		/sizeof(asn_DEF_cyclicShift_tags_18[0]), /* 2 */
	&asn_PER_type_cyclicShift_constr_18,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_cyclicShift_specs_18	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_setup_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, srs_Bandwidth),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_srs_Bandwidth_4,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"srs-Bandwidth"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, srs_HoppingBandwidth),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_srs_HoppingBandwidth_9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"srs-HoppingBandwidth"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, freqDomainPosition),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_freqDomainPosition_constraint_3,
		&asn_PER_memb_freqDomainPosition_constr_14,
		0,
		"freqDomainPosition"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, duration),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"duration"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, srs_ConfigIndex),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_srs_ConfigIndex_constraint_3,
		&asn_PER_memb_srs_ConfigIndex_constr_16,
		0,
		"srs-ConfigIndex"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, transmissionComb),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		memb_transmissionComb_constraint_3,
		&asn_PER_memb_transmissionComb_constr_17,
		0,
		"transmissionComb"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated__setup, cyclicShift),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_cyclicShift_18,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cyclicShift"
		},
};
static const ber_tlv_tag_t asn_DEF_setup_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_setup_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* srs-Bandwidth */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* srs-HoppingBandwidth */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* freqDomainPosition */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* duration */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* srs-ConfigIndex */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* transmissionComb */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* cyclicShift */
};
static asn_SEQUENCE_specifics_t asn_SPC_setup_specs_3 = {
	sizeof(struct SoundingRS_UL_ConfigDedicated__setup),
	offsetof(struct SoundingRS_UL_ConfigDedicated__setup, _asn_ctx),
	asn_MAP_setup_tag2el_3,
	7,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_setup_3 = {
	"setup",
	"setup",
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
	asn_DEF_setup_tags_3,
	sizeof(asn_DEF_setup_tags_3)
		/sizeof(asn_DEF_setup_tags_3[0]) - 1, /* 1 */
	asn_DEF_setup_tags_3,	/* Same as above */
	sizeof(asn_DEF_setup_tags_3)
		/sizeof(asn_DEF_setup_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_setup_3,
	7,	/* Elements count */
	&asn_SPC_setup_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SoundingRS_UL_ConfigDedicated_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated, choice.release),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"release"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SoundingRS_UL_ConfigDedicated, choice.setup),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_setup_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"setup"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_SoundingRS_UL_ConfigDedicated_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* release */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* setup */
};
static asn_CHOICE_specifics_t asn_SPC_SoundingRS_UL_ConfigDedicated_specs_1 = {
	sizeof(struct SoundingRS_UL_ConfigDedicated),
	offsetof(struct SoundingRS_UL_ConfigDedicated, _asn_ctx),
	offsetof(struct SoundingRS_UL_ConfigDedicated, present),
	sizeof(((struct SoundingRS_UL_ConfigDedicated *)0)->present),
	asn_MAP_SoundingRS_UL_ConfigDedicated_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_SoundingRS_UL_ConfigDedicated = {
	"SoundingRS-UL-ConfigDedicated",
	"SoundingRS-UL-ConfigDedicated",
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
	&asn_PER_type_SoundingRS_UL_ConfigDedicated_constr_1,
	asn_MBR_SoundingRS_UL_ConfigDedicated_1,
	2,	/* Elements count */
	&asn_SPC_SoundingRS_UL_ConfigDedicated_specs_1	/* Additional specs */
};
