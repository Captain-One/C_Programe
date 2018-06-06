/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "AntennaInfoDedicated-r10.h"

static int
transmissionMode_r10_2_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
transmissionMode_r10_2_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
transmissionMode_r10_2_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
transmissionMode_r10_2_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
transmissionMode_r10_2_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
transmissionMode_r10_2_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
transmissionMode_r10_2_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
transmissionMode_r10_2_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
transmissionMode_r10_2_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
transmissionMode_r10_2_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	transmissionMode_r10_2_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static int
setup_22_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
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
setup_22_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
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
setup_22_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	setup_22_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

static int
setup_22_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

static asn_dec_rval_t
setup_22_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

static asn_enc_rval_t
setup_22_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

static asn_dec_rval_t
setup_22_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

static asn_enc_rval_t
setup_22_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_dec_rval_t
setup_22_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);
}

static asn_enc_rval_t
setup_22_encode_uper(asn_TYPE_descriptor_t *td,
		asn_per_constraints_t *constraints,
		void *structure, asn_per_outp_t *per_out) {
	setup_22_inherit_TYPE_descriptor(td);
	return td->uper_encoder(td, constraints, structure, per_out);
}

static asn_per_constraints_t asn_PER_type_transmissionMode_r10_constr_2 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_setup_constr_22 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_type_ue_TransmitAntennaSelection_constr_20 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_transmissionMode_r10_value2enum_2[] = {
	{ 0,	3,	"tm1" },
	{ 1,	3,	"tm2" },
	{ 2,	3,	"tm3" },
	{ 3,	3,	"tm4" },
	{ 4,	3,	"tm5" },
	{ 5,	3,	"tm6" },
	{ 6,	3,	"tm7" },
	{ 7,	8,	"tm8-v920" },
	{ 8,	9,	"tm9-v1020" },
	{ 9,	6,	"spare7" },
	{ 10,	6,	"spare6" },
	{ 11,	6,	"spare5" },
	{ 12,	6,	"spare4" },
	{ 13,	6,	"spare3" },
	{ 14,	6,	"spare2" },
	{ 15,	6,	"spare1" }
};
static const unsigned int asn_MAP_transmissionMode_r10_enum2value_2[] = {
	15,	/* spare1(15) */
	14,	/* spare2(14) */
	13,	/* spare3(13) */
	12,	/* spare4(12) */
	11,	/* spare5(11) */
	10,	/* spare6(10) */
	9,	/* spare7(9) */
	0,	/* tm1(0) */
	1,	/* tm2(1) */
	2,	/* tm3(2) */
	3,	/* tm4(3) */
	4,	/* tm5(4) */
	5,	/* tm6(5) */
	6,	/* tm7(6) */
	7,	/* tm8-v920(7) */
	8	/* tm9-v1020(8) */
};
static const asn_INTEGER_specifics_t asn_SPC_transmissionMode_r10_specs_2 = {
	asn_MAP_transmissionMode_r10_value2enum_2,	/* "tag" => N; sorted by tag */
	asn_MAP_transmissionMode_r10_enum2value_2,	/* N => "tag"; sorted by N */
	16,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_transmissionMode_r10_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_transmissionMode_r10_2 = {
	"transmissionMode-r10",
	"transmissionMode-r10",
	transmissionMode_r10_2_free,
	transmissionMode_r10_2_print,
	transmissionMode_r10_2_constraint,
	transmissionMode_r10_2_decode_ber,
	transmissionMode_r10_2_encode_der,
	transmissionMode_r10_2_decode_xer,
	transmissionMode_r10_2_encode_xer,
	transmissionMode_r10_2_decode_uper,
	transmissionMode_r10_2_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_transmissionMode_r10_tags_2,
	sizeof(asn_DEF_transmissionMode_r10_tags_2)
		/sizeof(asn_DEF_transmissionMode_r10_tags_2[0]) - 1, /* 1 */
	asn_DEF_transmissionMode_r10_tags_2,	/* Same as above */
	sizeof(asn_DEF_transmissionMode_r10_tags_2)
		/sizeof(asn_DEF_transmissionMode_r10_tags_2[0]), /* 2 */
	&asn_PER_type_transmissionMode_r10_constr_2,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_transmissionMode_r10_specs_2	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_setup_value2enum_22[] = {
	{ 0,	10,	"closedLoop" },
	{ 1,	8,	"openLoop" }
};
static const unsigned int asn_MAP_setup_enum2value_22[] = {
	0,	/* closedLoop(0) */
	1	/* openLoop(1) */
};
static const asn_INTEGER_specifics_t asn_SPC_setup_specs_22 = {
	asn_MAP_setup_value2enum_22,	/* "tag" => N; sorted by tag */
	asn_MAP_setup_enum2value_22,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_setup_tags_22[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_setup_22 = {
	"setup",
	"setup",
	setup_22_free,
	setup_22_print,
	setup_22_constraint,
	setup_22_decode_ber,
	setup_22_encode_der,
	setup_22_decode_xer,
	setup_22_encode_xer,
	setup_22_decode_uper,
	setup_22_encode_uper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_setup_tags_22,
	sizeof(asn_DEF_setup_tags_22)
		/sizeof(asn_DEF_setup_tags_22[0]) - 1, /* 1 */
	asn_DEF_setup_tags_22,	/* Same as above */
	sizeof(asn_DEF_setup_tags_22)
		/sizeof(asn_DEF_setup_tags_22[0]), /* 2 */
	&asn_PER_type_setup_constr_22,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_setup_specs_22	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ue_TransmitAntennaSelection_20[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AntennaInfoDedicated_r10__ue_TransmitAntennaSelection, choice.release),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NULL,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"release"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AntennaInfoDedicated_r10__ue_TransmitAntennaSelection, choice.setup),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_setup_22,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"setup"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_ue_TransmitAntennaSelection_tag2el_20[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* release */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* setup */
};
static asn_CHOICE_specifics_t asn_SPC_ue_TransmitAntennaSelection_specs_20 = {
	sizeof(struct AntennaInfoDedicated_r10__ue_TransmitAntennaSelection),
	offsetof(struct AntennaInfoDedicated_r10__ue_TransmitAntennaSelection, _asn_ctx),
	offsetof(struct AntennaInfoDedicated_r10__ue_TransmitAntennaSelection, present),
	sizeof(((struct AntennaInfoDedicated_r10__ue_TransmitAntennaSelection *)0)->present),
	asn_MAP_ue_TransmitAntennaSelection_tag2el_20,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ue_TransmitAntennaSelection_20 = {
	"ue-TransmitAntennaSelection",
	"ue-TransmitAntennaSelection",
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
	&asn_PER_type_ue_TransmitAntennaSelection_constr_20,
	asn_MBR_ue_TransmitAntennaSelection_20,
	2,	/* Elements count */
	&asn_SPC_ue_TransmitAntennaSelection_specs_20	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_AntennaInfoDedicated_r10_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AntennaInfoDedicated_r10, transmissionMode_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_transmissionMode_r10_2,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"transmissionMode-r10"
		},
	{ ATF_POINTER, 1, offsetof(struct AntennaInfoDedicated_r10, codebookSubsetRestriction_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"codebookSubsetRestriction-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AntennaInfoDedicated_r10, ue_TransmitAntennaSelection),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ue_TransmitAntennaSelection_20,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"ue-TransmitAntennaSelection"
		},
};
static const int asn_MAP_AntennaInfoDedicated_r10_oms_1[] = { 1 };
static const ber_tlv_tag_t asn_DEF_AntennaInfoDedicated_r10_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_AntennaInfoDedicated_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* transmissionMode-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* codebookSubsetRestriction-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* ue-TransmitAntennaSelection */
};
static asn_SEQUENCE_specifics_t asn_SPC_AntennaInfoDedicated_r10_specs_1 = {
	sizeof(struct AntennaInfoDedicated_r10),
	offsetof(struct AntennaInfoDedicated_r10, _asn_ctx),
	asn_MAP_AntennaInfoDedicated_r10_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_AntennaInfoDedicated_r10_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_AntennaInfoDedicated_r10 = {
	"AntennaInfoDedicated-r10",
	"AntennaInfoDedicated-r10",
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
	asn_DEF_AntennaInfoDedicated_r10_tags_1,
	sizeof(asn_DEF_AntennaInfoDedicated_r10_tags_1)
		/sizeof(asn_DEF_AntennaInfoDedicated_r10_tags_1[0]), /* 1 */
	asn_DEF_AntennaInfoDedicated_r10_tags_1,	/* Same as above */
	sizeof(asn_DEF_AntennaInfoDedicated_r10_tags_1)
		/sizeof(asn_DEF_AntennaInfoDedicated_r10_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_AntennaInfoDedicated_r10_1,
	3,	/* Elements count */
	&asn_SPC_AntennaInfoDedicated_r10_specs_1	/* Additional specs */
};

