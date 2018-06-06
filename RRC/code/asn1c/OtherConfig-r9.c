/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "OtherConfig-r9.h"

static asn_TYPE_member_t asn_MBR_OtherConfig_r9_1[] = {
	{ ATF_POINTER, 1, offsetof(struct OtherConfig_r9, reportProximityConfig_r9),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReportProximityConfig_r9,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"reportProximityConfig-r9"
		},
};
static const int asn_MAP_OtherConfig_r9_oms_1[] = { 0 };
static const ber_tlv_tag_t asn_DEF_OtherConfig_r9_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_OtherConfig_r9_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* reportProximityConfig-r9 */
};
static asn_SEQUENCE_specifics_t asn_SPC_OtherConfig_r9_specs_1 = {
	sizeof(struct OtherConfig_r9),
	offsetof(struct OtherConfig_r9, _asn_ctx),
	asn_MAP_OtherConfig_r9_tag2el_1,
	1,	/* Count of tags in the map */
	asn_MAP_OtherConfig_r9_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	0,	/* Start extensions */
	2	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_OtherConfig_r9 = {
	"OtherConfig-r9",
	"OtherConfig-r9",
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
	asn_DEF_OtherConfig_r9_tags_1,
	sizeof(asn_DEF_OtherConfig_r9_tags_1)
		/sizeof(asn_DEF_OtherConfig_r9_tags_1[0]), /* 1 */
	asn_DEF_OtherConfig_r9_tags_1,	/* Same as above */
	sizeof(asn_DEF_OtherConfig_r9_tags_1)
		/sizeof(asn_DEF_OtherConfig_r9_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_OtherConfig_r9_1,
	1,	/* Elements count */
	&asn_SPC_OtherConfig_r9_specs_1	/* Additional specs */
};

