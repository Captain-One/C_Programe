#include "mac_extern.h"
#include "mac.h"
#include "mac_defs.h"
#include "mac_proto.h"
#include "mac_rrc_primitives.h"
#include "rrc_extern.h"

#ifdef softSIM
#include "../../simulate/sim.h"
#endif


#if 0
//extern UE_MODE_t get_ue_mode(uint8_t Mod_id,uint8_t CC_id,uint8_t eNB_index);

/// This routine implements Section 5.1.2 (UE Random Access Resource Selection) from 38.321

//1>	else (i.e. for the contention-based Random Access preamble selection):
//	2>	if at least one of the SSBs with SS-RSRP above rsrp-ThresholdSSB is available:
//		3>	select an SSB with SS-RSRP above rsrp-ThresholdSSB.
//	2>	else:
//		3>	select any SSB.
//	2>	if Msg3 has not yet been transmitted:
//		3>	if Random Access Preambles group B is configured:
//			4>	if the potential Msg3 size (UL data available for transmission plus MAC header and, where required, MAC CEs) is greater than ra-Msg3SizeGroupA and the pathloss is less than PCMAX (of the Serving Cell performing the Random Access Procedure) – preambleReceivedTargetPower – msg3-DeltaPreamble – messagePowerOffsetGroupB; or
//			4>	if the Random Access procedure was initiated for the CCCH logical channel and the CCCH SDU size plus MAC subheader is greater than ra-Msg3SizeGroupA:
//				5>	select the Random Access Preambles group B.
//			4>	else:
//				5>	select the Random Access Preambles group A.
//		3>	else:
//			4>	select the Random Access Preambles group A.
//	2>	else (i.e. Msg3 is being retransmitted):
//		3>	select the same group of Random Access Preambles as was used for the Random Access Preamble transmission attempt corresponding to the first transmission of Msg3.
//	2>	select a Random Access Preamble randomly with equal probability from the Random Access Preambles associated with the selected SSB and the selected Random Access Preambles group.
//	2>	set the PREAMBLE_INDEX to the selected Random Access Preamble.

void get_prach_resources(module_id_t module_idP,
								int CC_id,
								uint8_t eNB_index,
								uint8_t t_id,
								uint8_t first_Msg3,
								RACH_ConfigDedicated_t * rach_ConfigDedicated)
{
	uint8_t Msg3_size = ue_mac_inst[module_idP].RA_Msg3_size;
	PRACH_RESOURCES_t *prach_resources = &ue_mac_inst[module_idP].RA_prach_resources;
	RACH_ConfigCommon_t *rach_ConfigCommon = NULL;
	uint8_t noGroupB = 0;
	uint8_t f_id = 0, num_prach = 0;
	int numberOfRA_Preambles;
	int messageSizeGroupA;
	int sizeOfRA_PreamblesGroupA;
	int messagePowerOffsetGroupB;
	int PLThreshold;

	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

	AssertFatal(ue_mac_inst[module_idP].sib1 != NULL,
			"[UE %d] FATAL  SIB1 radioResourceConfigCommon is NULL !!!\n", module_idP);

	if(ue_mac_inst[module_idP].RA_prach_resources.Msg3 == NULL) {
		if(ue_mac_inst[module_idP].sib1->servingCellConfigCommon->uplinkConfigCommon->initialUplinkBWP.rach_ConfigCommon) {
			rach_ConfigCommon = (RACH_ConfigCommon_t*)(ue_mac_inst[module_idP].sib1->servingCellConfigCommon->uplinkConfigCommon->initialUplinkBWP.rach_ConfigCommon);

			if(rach_ConfigCommon->groupBconfigured) {

			} else {

			}
		}
	} else {

	}

//	rach_ConfigCommon = &ue_mac_inst[module_idP].radioResourceConfigCommon->rach_ConfigCommon;
	rach_ConfigCommon = &ue_mac_inst[module_idP].sib1->servingCellConfigCommon->uplinkConfigCommon->initialUplinkBWP.rach_ConfigCommon;

	numberOfRA_Preambles = (1 + rach_ConfigCommon->preambleInfo.numberOfRA_Preambles) << 2;

	if (rach_ConfigDedicated) {	// This is for network controlled Mobility, later
		if (rach_ConfigDedicated->ra_PRACH_MaskIndex != 0) {
			prach_resources->ra_PreambleIndex = rach_ConfigDedicated->ra_PreambleIndex;
			prach_resources->ra_RACH_MaskIndex = rach_ConfigDedicated->ra_PRACH_MaskIndex;
			return;
		}
	}

	/* TODO: gcc warns if this variable is not always set, let's put -1 for no more warning */
	messageSizeGroupA = -1;

	if (!rach_ConfigCommon->preambleInfo.preamblesGroupAConfig) {
		noGroupB = 1;
	} else {
		sizeOfRA_PreamblesGroupA = (rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->sizeOfRA_PreamblesGroupA + 1) << 2;
		switch (rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->messageSizeGroupA) {
		case 0:
			messageSizeGroupA = 56;
			break;
		case 1:
			messageSizeGroupA = 144;
			break;
		case 2:
			messageSizeGroupA = 208;
			break;
		case 3:
			messageSizeGroupA = 256;
			break;
		}

		/* TODO: what value to use as default? */
		messagePowerOffsetGroupB = -9999;
		switch (rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->messagePowerOffsetGroupB) {
		case 0:
			messagePowerOffsetGroupB = -9999;
			break;
		case 1:
			messagePowerOffsetGroupB = 0;
			break;
		case 2:
			messagePowerOffsetGroupB = 5;
			break;
		case 3:
			messagePowerOffsetGroupB = 8;
			break;
		case 4:
			messagePowerOffsetGroupB = 10;
			break;
		case 5:
			messagePowerOffsetGroupB = 12;
			break;
		case 6:
			messagePowerOffsetGroupB = 15;
			break;
		case 7:
			messagePowerOffsetGroupB = 18;
			break;
		}

		PLThreshold = 0 - get_DELTA_PREAMBLE(module_idP,CC_id) - get_Po_NOMINAL_PUSCH(module_idP,CC_id) - messagePowerOffsetGroupB;
		// Note Pcmax is set to 0 here, we have to fix this

		if (sizeOfRA_PreamblesGroupA == numberOfRA_Preambles) {
			noGroupB = 1;
		}
	}

	if (first_Msg3 == 1) {
		if (noGroupB == 1) {
		// use Group A procedure
			ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex = (taus()) % numberOfRA_Preambles;
			ue_mac_inst[module_idP].RA_prach_resources.ra_RACH_MaskIndex = 0;
			ue_mac_inst[module_idP].RA_usedGroupA = 1;
		} else if ((Msg3_size < messageSizeGroupA) || (get_PL(module_idP, 0, eNB_index) > PLThreshold)) {
			// use Group A procedure
			ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex = (taus()) % sizeOfRA_PreamblesGroupA;
			ue_mac_inst[module_idP].RA_prach_resources.ra_RACH_MaskIndex = 0;
			ue_mac_inst[module_idP].RA_usedGroupA = 1;
		} else {		// use Group B
			ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex =
					sizeOfRA_PreamblesGroupA + (taus()) % (numberOfRA_Preambles - sizeOfRA_PreamblesGroupA);
			ue_mac_inst[module_idP].RA_prach_resources.ra_RACH_MaskIndex = 0;
			ue_mac_inst[module_idP].RA_usedGroupA = 0;
		}

		ue_mac_inst[module_idP].RA_prach_resources.ra_PREAMBLE_RECEIVED_TARGET_POWER = get_Po_NOMINAL_PUSCH(module_idP, CC_id);
	} else {			// Msg3 is being retransmitted
		if (ue_mac_inst[module_idP].RA_usedGroupA == 1) {
			if (rach_ConfigCommon->preambleInfo.preamblesGroupAConfig) {
				ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex =
						(taus()) % rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->sizeOfRA_PreamblesGroupA;
			} else {
				ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex = (taus()) & 0x3f;
			}

			ue_mac_inst[module_idP].RA_prach_resources.ra_RACH_MaskIndex = 0;
		} else {
			// FIXME rach_ConfigCommon->preambleInfo.preamblesGroupAConfig may be zero
			ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex =
			rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->sizeOfRA_PreamblesGroupA + (taus()) %
			(rach_ConfigCommon->preambleInfo.numberOfRA_Preambles - rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->sizeOfRA_PreamblesGroupA);

			ue_mac_inst[module_idP].RA_prach_resources.ra_RACH_MaskIndex = 0;
		}
	}

	// choose random PRACH resource in TDD
	if (ue_mac_inst[module_idP].tdd_Config) {
		num_prach = get_num_prach_tdd(module_idP);

		if ((num_prach > 0) && (num_prach < 6)) {
			ue_mac_inst[module_idP].RA_prach_resources.ra_TDD_map_index = (taus() % num_prach);
		}

		f_id = get_fid_prach_tdd(module_idP, ue_mac_inst[module_idP].RA_prach_resources.ra_TDD_map_index);
	}
	// choose RA-RNTI
//	RA-RNTI = 1 + s_id + 14 × t_id + 14 × 80 × f_id + 14 × 80 × 8 × ul_carrier_id
	ue_mac_inst[module_idP].RA_prach_resources.ra_RNTI = 1 + t_id + 10 * f_id;
}
#endif

void Msg1_transmitted(module_id_t module_idP, uint8_t CC_id, frame_t frameP, uint8_t eNB_id)
{

	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

	// start contention resolution timer
//	ue_mac_inst[module_idP].RA_attempt_number++;
}


void Msg3_transmitted(module_id_t module_idP, uint8_t CC_id, frame_t frameP, uint8_t eNB_id)
{

	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

//	start contention resolution timer
	printf("[UE %d][RAPROC] Frame %d : Msg3_tx: Setting contention resolution timer\n",
			module_idP, frameP);

//	ue_mac_inst[module_idP].RA_contention_resolution_cnt = 0;
//	ue_mac_inst[module_idP].RA_contention_resolution_timer_active = 1;
}

#if 0
PRACH_RESOURCES_t *ue_get_rach(module_id_t module_idP,
						int CC_id,
						frame_t frameP,
						uint8_t eNB_indexP,
						sub_frame_t subframeP,
						slot_t slot)
{
	uint8_t Size = 0;
	UE_MODE_t UE_mode;
	uint8_t lcid = DL_SCH_LCID_CCCH;
	uint16_t Size16;
	struct RACH_ConfigCommon *rach_ConfigCommon = (struct RACH_ConfigCommon *) NULL;
	int32_t frame_diff = 0;
	uint8_t dcch_header_len = 0;
	uint16_t sdu_lengths;
	uint8_t ulsch_buff[MAX_ULSCH_PAYLOAD_BYTES];

// Full stack mode
//	UE_mode = get_ue_mode(module_idP,0,eNB_indexP);
	UE_mode = PRACH;

	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

	if (UE_mode == PRACH) {
		printf("ue_get_rach 3, RA_active value: %d", ue_mac_inst[module_idP].RA_active);

		if (ue_mac_inst[module_idP].sib1) {
			rach_ConfigCommon = &ue_mac_inst[module_idP].sib1->servingCellConfigCommon->uplinkConfigCommon->initialUplinkBWP.rach_ConfigCommon;
		} else {
			return (NULL);
		}

		if (ue_mac_inst[module_idP].RA_active == 0) {
			printf("RA not active\n");
			// check if RRC is ready to initiate the RA procedure
			Size = mac_rrc_data_req_ue(module_idP,
											CC_id,
											frameP,
											CCCH,
											1,
											&ue_mac_inst[module_idP].CCCH_pdu.payload[sizeof(SCH_SUBHEADER_SHORT) + 1],
											eNB_indexP,
											0);

			Size16 = (uint16_t) Size;

			//  LOG_D(MAC,"[UE %d] Frame %d: Requested RRCConnectionRequest, got %d bytes\n",module_idP,frameP,Size);
			printf("[MSC_MSG][FRAME %05d][RRC_UE][MOD %02d][][--- MAC_DATA_REQ (RRCConnectionRequest eNB %d) --->][MAC_UE][MOD %02d][]\n",
					frameP, module_idP, eNB_indexP, module_idP);
			printf("[UE %d] Frame %d: Requested RRCConnectionRequest, got %d bytes\n", module_idP, frameP, Size);

			if (Size > 0) {
				ue_mac_inst[module_idP].RA_active = 1;
				ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER = 1;
				ue_mac_inst[module_idP].RA_Msg3_size = Size + sizeof(SCH_SUBHEADER_SHORT) + sizeof(SCH_SUBHEADER_SHORT);
				ue_mac_inst[module_idP].RA_prachMaskIndex = 0;
				ue_mac_inst[module_idP].RA_prach_resources.Msg3 = ue_mac_inst[module_idP].CCCH_pdu.payload;
				ue_mac_inst[module_idP].RA_backoff_cnt = 0;	// add the backoff condition here if we have it from a previous RA reponse which failed (i.e. backoff indicator)

				AssertFatal(rach_ConfigCommon != NULL, "[UE %d] FATAL Frame %d: rach_ConfigCommon is NULL !!!\n", module_idP, frameP);

				ue_mac_inst[module_idP].RA_window_cnt = 2 + rach_ConfigCommon->rach_ConfigGeneric.ra_ResponseWindow;

				if (ue_mac_inst[module_idP].RA_window_cnt == 9) {
					ue_mac_inst[module_idP].RA_window_cnt = 10;	// Note: 9 subframe window doesn't exist, after 8 is 10!
				}

				ue_mac_inst[module_idP].RA_tx_frame = frameP;
				ue_mac_inst[module_idP].RA_tx_subframe = subframeP;
				ue_mac_inst[module_idP].RA_backoff_frame = frameP;
				ue_mac_inst[module_idP].RA_backoff_subframe = subframeP;
				// Fill in preamble and PRACH resource
				get_prach_resources(module_idP, CC_id, eNB_indexP,subframeP, 1, NULL);

				generate_ulsch_header((uint8_t *) & ue_mac_inst[module_idP].CCCH_pdu.payload[0],	// mac header
											1,	// num sdus
											0,	// short pading
											&Size16,	// sdu length
											&lcid,	// sdu lcid
											NULL,	// power headroom
											NULL,	// crnti
											NULL,	// truncated bsr
											NULL,	// short bsr
											NULL,	// long_bsr
											1);	//post_padding

				return (&ue_mac_inst[module_idP].RA_prach_resources);

			} else if (ue_mac_inst[module_idP].scheduling_info.BSR_bytes[ue_mac_inst[module_idP].scheduling_info.LCGID[DCCH]] > 0) {
				// This is for triggering a transmission on DCCH using PRACH (during handover, or sending SR for example)
				dcch_header_len = 2 + 2;	/// SHORT Subheader + C-RNTI control element
//				LOG_USEDINLOG_VAR(mac_rlc_status_resp_t,rlc_status)=mac_rlc_status_ind(module_idP,
//							ue_mac_inst[module_idP].crnti,
//							eNB_indexP, frameP, subframeP,
//							ENB_FLAG_NO, MBMS_FLAG_NO, DCCH, 6
//							#if (RRC_VERSION < MAKE_VERSION(15, 0, 0))
//							,0, 0
//							#endif
//							);

				if (ue_mac_inst[module_idP].crnti_before_ho)
					printf("[UE %d] Frame %d : UL-DCCH -> ULSCH, HO RRCConnectionReconfigurationComplete (%x, %x), RRC message has %d bytes to send throug PRACH (mac header len %d)\n",
							module_idP, frameP, ue_mac_inst[module_idP].crnti, ue_mac_inst[module_idP].crnti_before_ho, rlc_status.bytes_in_buffer, dcch_header_len);
				else
					printf("[UE %d] Frame %d : UL-DCCH -> ULSCH, RRC message has %d bytes to send through PRACH(mac header len %d)\n",
							module_idP, frameP, rlc_status.bytes_in_buffer, dcch_header_len);

				sdu_lengths = mac_rlc_data_req(module_idP, ue_mac_inst[module_idP].crnti, eNB_indexP, frameP, ENB_FLAG_NO, MBMS_FLAG_NO, DCCH, 6,	//not used
													(char *) &ulsch_buff[0]
													#if (RRC_VERSION < MAKE_VERSION(15, 0, 0))
													,0,
													0
													#endif
													);

				if(sdu_lengths > 0)
					printf("[UE %d] TX Got %d bytes for DCCH\n",module_idP, sdu_lengths);
				else
					printf("[UE %d] TX DCCH error\n", module_idP );

				update_bsr(module_idP, frameP, subframeP, eNB_indexP);
				ue_mac_inst[module_idP].scheduling_info.BSR[ue_mac_inst[module_idP].scheduling_info.LCGID[DCCH]] =
							locate_BsrIndexByBufferSize(BSR5_TABLE, BSR5_TABLE_SIZE,
																ue_mac_inst
																[module_idP].scheduling_info.BSR_bytes
																[ue_mac_inst
																[module_idP].scheduling_info.LCGID
																[DCCH]]);

				//TO DO: fill BSR infos in UL TBS

				//header_len +=2;
				ue_mac_inst[module_idP].RA_active = 1;
				ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER = 1;
				ue_mac_inst[module_idP].RA_Msg3_size = Size + dcch_header_len;
				ue_mac_inst[module_idP].RA_prachMaskIndex = 0;
				ue_mac_inst[module_idP].RA_prach_resources.Msg3 = ulsch_buff;
				ue_mac_inst[module_idP].RA_backoff_cnt = 0;	// add the backoff condition here if we have it from a previous RA reponse which failed (i.e. backoff indicator)

				AssertFatal(rach_ConfigCommon != NULL, "[UE %d] FATAL Frame %d: rach_ConfigCommon is NULL !!!\n", module_idP, frameP);
				ue_mac_inst[module_idP].RA_window_cnt = 2 + rach_ConfigCommon->ra_SupervisionInfo.ra_ResponseWindowSize;

				if (ue_mac_inst[module_idP].RA_window_cnt == 9) {
					ue_mac_inst[module_idP].RA_window_cnt = 10;	// Note: 9 subframe window doesn't exist, after 8 is 10!
				}


				ue_mac_inst[module_idP].RA_tx_frame = frameP;
				ue_mac_inst[module_idP].RA_tx_subframe = subframeP;
				ue_mac_inst[module_idP].RA_backoff_frame = frameP;
				ue_mac_inst[module_idP].RA_backoff_subframe = subframeP;
				// Fill in preamble and PRACH resource
				get_prach_resources(module_idP, CC_id, eNB_indexP, subframeP, 1, NULL);

				generate_ulsch_header((uint8_t *) ulsch_buff,	// mac header
											1,	// num sdus
											0,	// short pading
											&Size16,	// sdu length
											&lcid,	// sdu lcid
											NULL,	// power headroom
											&ue_mac_inst[module_idP].crnti,	// crnti
											NULL,	// truncated bsr
											NULL,	// short bsr
											NULL,	// long_bsr
											0);	//post_padding

				return (&ue_mac_inst[module_idP].RA_prach_resources);
			}
		} else {		// RACH is active
			printf("[MAC][UE %d][RAPROC] frameP %d, subframe %d: RA Active, window cnt %d (RA_tx_frame %d, RA_tx_subframe %d)\n",
					module_idP, frameP, subframeP, ue_mac_inst[module_idP].RA_window_cnt, ue_mac_inst[module_idP].RA_tx_frame,
					ue_mac_inst[module_idP].RA_tx_subframe);

			// compute backoff parameters
			if (ue_mac_inst[module_idP].RA_backoff_cnt > 0) {
				frame_diff = (sframe_t) frameP - ue_mac_inst[module_idP].RA_backoff_frame;

				if (frame_diff < 0) {
					frame_diff = -frame_diff;
				}

				ue_mac_inst[module_idP].RA_backoff_cnt -= ((10 * frame_diff) + (subframeP - ue_mac_inst[module_idP].RA_backoff_subframe));

				ue_mac_inst[module_idP].RA_backoff_frame = frameP;
				ue_mac_inst[module_idP].RA_backoff_subframe = subframeP;
			}
			// compute RA window parameters
			if (ue_mac_inst[module_idP].RA_window_cnt > 0) {
				frame_diff = (frame_t) frameP - ue_mac_inst[module_idP].RA_tx_frame;

				if (frame_diff < 0) {
					frame_diff = -frame_diff;
				}

				ue_mac_inst[module_idP].RA_window_cnt -= ((10 * frame_diff) + (subframeP - ue_mac_inst[module_idP].RA_tx_subframe));
				printf("[MAC][UE %d][RAPROC] frameP %d, subframe %d: RA Active, adjusted window cnt %d\n",
						module_idP, frameP, subframeP, ue_mac_inst[module_idP].RA_window_cnt);
			}

			if ((ue_mac_inst[module_idP].RA_window_cnt <= 0) && (ue_mac_inst[module_idP].RA_backoff_cnt <= 0)) {

				ue_mac_inst[module_idP].RA_tx_frame = frameP;
				ue_mac_inst[module_idP].RA_tx_subframe = subframeP;
				ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER++;
				ue_mac_inst[module_idP].RA_prach_resources.ra_PREAMBLE_RECEIVED_TARGET_POWER += (rach_ConfigCommon->powerRampingParameters.powerRampingStep << 1);	// 2dB increments in ASN.1 definition
				int preambleTransMax = -1;
				switch (rach_ConfigCommon->ra_SupervisionInfo.preambleTransMax) {
				case PreambleTransMax_n3:
					preambleTransMax = 3;
					break;
				case PreambleTransMax_n4:
					preambleTransMax = 4;
					break;
				case PreambleTransMax_n5:
					preambleTransMax = 5;
					break;
				case PreambleTransMax_n6:
					preambleTransMax = 6;
					break;
				case PreambleTransMax_n7:
					preambleTransMax = 7;
					break;
				case PreambleTransMax_n8:
					preambleTransMax = 8;
					break;
				case PreambleTransMax_n10:
					preambleTransMax = 10;
					break;
				case PreambleTransMax_n20:
					preambleTransMax = 20;
					break;
				case PreambleTransMax_n50:
					preambleTransMax = 50;
					break;
				case PreambleTransMax_n100:
					preambleTransMax = 100;
					break;
				case PreambleTransMax_n200:
					preambleTransMax = 200;
					break;
				}

				if (ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER == preambleTransMax) {
					printf("[UE %d] Frame %d: Maximum number of RACH attempts (%d)\n", module_idP, frameP, preambleTransMax);
					// send message to RRC
					ue_mac_inst[module_idP].RA_PREAMBLE_TRANSMISSION_COUNTER = 1;
					ue_mac_inst[module_idP].RA_prach_resources.ra_PREAMBLE_RECEIVED_TARGET_POWER = get_Po_NOMINAL_PUSCH(module_idP, CC_id);
				}

				ue_mac_inst[module_idP].RA_window_cnt = 2 + rach_ConfigCommon->ra_SupervisionInfo.ra_ResponseWindowSize;
				ue_mac_inst[module_idP].RA_backoff_cnt = 0;

				// Fill in preamble and PRACH resource
				get_prach_resources(module_idP, CC_id, eNB_indexP, subframeP, 0, NULL);

				return (&ue_mac_inst[module_idP].RA_prach_resources);
			}
		}
	} else if (UE_mode == PUSCH) {
		printf("[UE %d] FATAL: Should not have checked for RACH in PUSCH yet ...", module_idP);
		AssertFatal(1 == 0, "");
	}

	return (NULL);
}
#endif
