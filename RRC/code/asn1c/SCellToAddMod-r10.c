/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "36331-b00.asn"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "SCellToAddMod-r10.h"

static asn_TYPE_member_t asn_MBR_cellIdentification_r10_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SCellToAddMod_r10__cellIdentification_r10, physCellId_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PhysCellId,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"physCellId-r10"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SCellToAddMod_r10__cellIdentification_r10, dl_CarrierFreq_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ARFCN_ValueEUTRA,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"dl-CarrierFreq-r10"
		},
};
static const ber_tlv_tag_t asn_DEF_cellIdentification_r10_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_cellIdentification_r10_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* physCellId-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* dl-CarrierFreq-r10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_cellIdentification_r10_specs_3 = {
	sizeof(struct SCellToAddMod_r10__cellIdentification_r10),
	offsetof(struct SCellToAddMod_r10__cellIdentification_r10, _asn_ctx),
	asn_MAP_cellIdentification_r10_tag2el_3,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_cellIdentification_r10_3 = {
	"cellIdentification-r10",
	"cellIdentification-r10",
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
	asn_DEF_cellIdentification_r10_tags_3,
	sizeof(asn_DEF_cellIdentification_r10_tags_3)
		/sizeof(asn_DEF_cellIdentification_r10_tags_3[0]) - 1, /* 1 */
	asn_DEF_cellIdentification_r10_tags_3,	/* Same as above */
	sizeof(asn_DEF_cellIdentification_r10_tags_3)
		/sizeof(asn_DEF_cellIdentification_r10_tags_3[0]), /* 2 */
	0,	/* No PER visible constraints */
	asn_MBR_cellIdentification_r10_3,
	2,	/* Elements count */
	&asn_SPC_cellIdentification_r10_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_SCellToAddMod_r10_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SCellToAddMod_r10, sCellIndex_r10),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SCellIndex_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"sCellIndex-r10"
		},
	{ ATF_POINTER, 3, offsetof(struct SCellToAddMod_r10, cellIdentification_r10),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_cellIdentification_r10_3,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"cellIdentification-r10"
		},
	{ ATF_POINTER, 2, offsetof(struct SCellToAddMod_r10, radioResourceConfigCommonSCell_r10),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RadioResourceConfigCommonSCell_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"radioResourceConfigCommonSCell-r10"
		},
	{ ATF_POINTER, 1, offsetof(struct SCellToAddMod_r10, radioResourceConfigDedicatedSCell_r10),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RadioResourceConfigDedicatedSCell_r10,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"radioResourceConfigDedicatedSCell-r10"
		},
};
static const int asn_MAP_SCellToAddMod_r10_oms_1[] = { 1, 2, 3 };
static const ber_tlv_tag_t asn_DEF_SCellToAddMod_r10_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SCellToAddMod_r10_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sCellIndex-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* cellIdentification-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* radioResourceConfigCommonSCell-r10 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* radioResourceConfigDedicatedSCell-r10 */
};
static asn_SEQUENCE_specifics_t asn_SPC_SCellToAddMod_r10_specs_1 = {
	sizeof(struct SCellToAddMod_r10),
	offsetof(struct SCellToAddMod_r10, _asn_ctx),
	asn_MAP_SCellToAddMod_r10_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_SCellToAddMod_r10_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	3,	/* Start extensions */
	5	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_SCellToAddMod_r10 = {
	"SCellToAddMod-r10",
	"SCellToAddMod-r10",
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
	asn_DEF_SCellToAddMod_r10_tags_1,
	sizeof(asn_DEF_SCellToAddMod_r10_tags_1)
		/sizeof(asn_DEF_SCellToAddMod_r10_tags_1[0]), /* 1 */
	asn_DEF_SCellToAddMod_r10_tags_1,	/* Same as above */
	sizeof(asn_DEF_SCellToAddMod_r10_tags_1)
		/sizeof(asn_DEF_SCellToAddMod_r10_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_SCellToAddMod_r10_1,
	4,	/* Elements count */
	&asn_SPC_SCellToAddMod_r10_specs_1	/* Additional specs */
};

