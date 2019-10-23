#include "mac.h"
#include "mac_defs.h"
#include "mac_extern.h"
#include "proto.h"
#include "assertions.h"

#include "RACH-ConfigCommon.h"
#include "ServingCellConfigCommonSIB.h"
#include "UplinkConfigCommonSIB.h"

int8_t get_Po_NOMINAL_PUSCH(module_id_t module_idP, uint8_t CC_id)
{
	RACH_ConfigCommon_t * rach_configcommon = ue_mac_inst[module_idP].sib1->servingCellConfigCommon->uplinkConfigCommon->initialUplinkBWP.rach_ConfigCommon;

	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");
	AssertFatal(ue_mac_inst[module_idP].sib1 != NULL, "[UE %d] CCid %d FATAL radioResourceConfigCommon is NULL !!!\n",
			module_idP, CC_id);

	return (-120 + (rach_configcommon->rach_ConfigGeneric.preambleReceivedTargetPower << 1)
			+ get_DELTA_PREAMBLE(module_idP, CC_id));
}

//Table 7.3-1: DELTA_PREAMBLE values for long preamble formats.
//Preamble Format			DELTA_PREAMBLE values
//0							0 dB
//1							-3 dB
//2							-6 dB
//3							0 dB
//
//Table 7.3-2: DELTA_PREAMBLE values for short preamble formats.
//Preamble Format			DELTA_PREAMBLE values (dB)
//A1						8 + 3 × μ
//A2						5 + 3 × μ
//A3						3 + 3 × μ
//B1						8 + 3 × μ
//B2						5 + 3 × μ
//B3						3 + 3 × μ
//B4						3 × μ
//C0						11 + 3 × μ
//C2						5 + 3 × μ
//
//where μ is the sub-carrier spacing configuration determined by msg1-SubcarrierSpacing and Table 4.2-1 in TS 38.211 [8], and the preamble formats are given by prach-ConfigurationIndex and Tables 6.3.3.2-2 and 6.3.3.2-3 in TS 38.211 [8].


int8_t get_DELTA_PREAMBLE(module_id_t module_idP, int CC_id)
{
	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");
	RACH_ConfigCommon_t* rach_configcommon = ((RACH_ConfigCommon_t*)(ue_mac_inst[module_idP].sib1->servingCellConfigCommon->uplinkConfigCommon->initialUplinkBWP.rach_ConfigCommon));
	uint8_t prachConfigIndex = rach_configcommon->rach_ConfigGeneric.prach_ConfigurationIndex;

	uint8_t preambleformat1;

	uint8_t Lra = rach_configcommon->prach_RootSequenceIndex.present;

	uint8_t u;

//	3GPP 38.211  4.2
	if(ue_mac_inst[module_idP].mib->subCarrierSpacingCommon == MIB__subCarrierSpacingCommon_scs15or60) {
		u = 0;
	} else {
		u = 1;
	}


	if(prachConfigIndex <= 27) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l839)
			return 0;
	} else if(prachConfigIndex <= 52) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l839)
			return -3;
	} else if(prachConfigIndex <= 59) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l839)
			return -6;
	} else if(prachConfigIndex <= 86) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l839)
			return 0;
	} else if(prachConfigIndex <= 107) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (8 + 3 * u);
	} else if(prachConfigIndex <= 116) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (8 + 3 * u);
	} else if(prachConfigIndex <= 136) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (5 + 3 * u);
	} else if(prachConfigIndex <= 146) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (5 + 3 * u);
	} else if(prachConfigIndex <= 166) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (3 + 3 * u);
	} else if(prachConfigIndex <= 176) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (3 + 3 * u);
	} else if(prachConfigIndex <= 197) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (8 + 3 * u);
	} else if(prachConfigIndex <= 218) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (3 * u);
	} else if(prachConfigIndex <= 235) {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (11 + 3 * u);
	} else {
		if(rach_configcommon->prach_RootSequenceIndex.present == RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139)
			return (5 + 3 * u);
	}

//	AssertFatal(1 == 0, "[UE %d] ue_procedures.c: FATAL, Illegal preambleformat %d, prachConfigIndex %d\n",
//					module_idP, preambleformat, prachConfigIndex);
	return -1;
}

int8_t get_deltaP_rampup(module_id_t module_idP, uint8_t CC_id)
{
	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

	printf("[PUSCH]%d dB\n", ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER << 1);

	return ((int8_t)(ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER << 1));
}
