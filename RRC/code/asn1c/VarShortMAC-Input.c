/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-UE-Variables"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "VarShortMAC-Input.h"

static asn_TYPE_member_t asn_MBR_VarShortMAC_Input_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct VarShortMAC_Input, cellIdentity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CellIdentity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellIdentity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarShortMAC_Input, physCellId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PhysCellId,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"physCellId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VarShortMAC_Input, c_RNTI),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_C_RNTI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"c-RNTI"
		},
};
static const ber_tlv_tag_t asn_DEF_VarShortMAC_Input_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_VarShortMAC_Input_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* cellIdentity */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* physCellId */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* c-RNTI */
};
static asn_SEQUENCE_specifics_t asn_SPC_VarShortMAC_Input_specs_1 = {
	sizeof(struct VarShortMAC_Input),
	offsetof(struct VarShortMAC_Input, _asn_ctx),
	asn_MAP_VarShortMAC_Input_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_VarShortMAC_Input = {
	"VarShortMAC-Input",
	"VarShortMAC-Input",
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
	asn_DEF_VarShortMAC_Input_tags_1,
	sizeof(asn_DEF_VarShortMAC_Input_tags_1)
		/sizeof(asn_DEF_VarShortMAC_Input_tags_1[0]), /* 1 */
	asn_DEF_VarShortMAC_Input_tags_1,	/* Same as above */
	sizeof(asn_DEF_VarShortMAC_Input_tags_1)
		/sizeof(asn_DEF_VarShortMAC_Input_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_VarShortMAC_Input_1,
	3,	/* Elements count */
	&asn_SPC_VarShortMAC_Input_specs_1	/* Additional specs */
};

