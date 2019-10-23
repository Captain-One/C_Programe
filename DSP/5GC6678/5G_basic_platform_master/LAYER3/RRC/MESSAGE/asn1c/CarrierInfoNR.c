/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "38331-f60.asn"
 * 	`asn1c -gen-PER -fcompound-names -fnative-types -fskeletons-copy`
 */

#include "CarrierInfoNR.h"

asn_TYPE_member_t asn_MBR_CarrierInfoNR_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CarrierInfoNR, carrierFreq),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ARFCN_ValueNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"carrierFreq"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CarrierInfoNR, ssbSubcarrierSpacing),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SubcarrierSpacing,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ssbSubcarrierSpacing"
		},
	{ ATF_POINTER, 1, offsetof(struct CarrierInfoNR, smtc),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SSB_MTC,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"smtc"
		},
};
static const int asn_MAP_CarrierInfoNR_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_CarrierInfoNR_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CarrierInfoNR_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* carrierFreq */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ssbSubcarrierSpacing */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* smtc */
};
asn_SEQUENCE_specifics_t asn_SPC_CarrierInfoNR_specs_1 = {
	sizeof(struct CarrierInfoNR),
	offsetof(struct CarrierInfoNR, _asn_ctx),
	asn_MAP_CarrierInfoNR_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_CarrierInfoNR_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_CarrierInfoNR = {
	"CarrierInfoNR",
	"CarrierInfoNR",
	&asn_OP_SEQUENCE,
	asn_DEF_CarrierInfoNR_tags_1,
	sizeof(asn_DEF_CarrierInfoNR_tags_1)
		/sizeof(asn_DEF_CarrierInfoNR_tags_1[0]), /* 1 */
	asn_DEF_CarrierInfoNR_tags_1,	/* Same as above */
	sizeof(asn_DEF_CarrierInfoNR_tags_1)
		/sizeof(asn_DEF_CarrierInfoNR_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_CarrierInfoNR_1,
	3,	/* Elements count */
	&asn_SPC_CarrierInfoNR_specs_1	/* Additional specs */
};

