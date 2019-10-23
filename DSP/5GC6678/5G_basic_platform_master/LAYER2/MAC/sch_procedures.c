#include "mac_proto.h"
#include "mac_extern.h"
#include "rlc.h"
#include "RRC/rrc_proto.h"
#include "assertions.h"

#include "MeasGapConfig.h"
#include "GapConfig.h"
#include "SetupRelease.h"

#include <stdio.h>
#include <math.h>


#ifdef softSIM
#include "../../simulate/sim.h"

extern unsigned int taus(void);
#endif

uint32_t get_ssb_slot(uint32_t ssb_index){
    //  this function now only support f <= 3GHz
    return ssb_index & 0x3 ;

    //  return first_symbol(case, freq, ssb_index) / 14
}

void ue_init_mac(module_id_t module_idP)
{
	int i;
//	default values as deined in 38.331 sec 9.2.2
	printf("[UE%d] Applying default macMainConfig\n", module_idP);
//	ue_mac_inst[module_idP].scheduling_info.macConfig=NULL;
	ue_mac_inst[module_idP].scheduling_info.retxBSR_Timer = BSR_Config__retxBSR_Timer_sf80;
	ue_mac_inst[module_idP].scheduling_info.periodicBSR_Timer = BSR_Config__periodicBSR_Timer_sf10;
	ue_mac_inst[module_idP].scheduling_info.periodicPHR_SF = PHR_Config__phr_PeriodicTimer_sf10;
	ue_mac_inst[module_idP].scheduling_info.prohibitPHR_SF = PHR_Config__phr_ProhibitTimer_sf10;
	ue_mac_inst[module_idP].scheduling_info.SR_COUNTER = 0;
	ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer = 0;
	ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer_Running = 0;
//	ue_mac_inst[module_idP].scheduling_info.maxHARQ_Tx = LTE_MAC_MainConfig__ul_SCH_Config__maxHARQ_Tx_n5;
	ue_mac_inst[module_idP].scheduling_info.ttiBundling = 0;
	ue_mac_inst[module_idP].scheduling_info.extendedBSR_Sizes_r10 = 0;
//	ue_mac_inst[module_idP].scheduling_info.extendedPHR_r10 = 0;
	ue_mac_inst[module_idP].drx_Config = NULL;
	ue_mac_inst[module_idP].phr_Config = NULL;
//	set init value 0xFFFF, make sure periodic timer and retx time counters are NOT active, after bsr transmission set the value configured by the NW.
	ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF = MAC_UE_BSR_TIMER_NOT_RUNNING;
	ue_mac_inst[module_idP].scheduling_info.retxBSR_SF =
	MAC_UE_BSR_TIMER_NOT_RUNNING;
	ue_mac_inst[module_idP].BSR_reporting_active = BSR_TRIGGER_NONE;
	ue_mac_inst[module_idP].scheduling_info.periodicPHR_SF =
			get_sf_perioidicPHR_Timer(ue_mac_inst[module_idP].scheduling_info.periodicPHR_SF);
	ue_mac_inst[module_idP].scheduling_info.prohibitPHR_SF =
			get_sf_prohibitPHR_Timer(ue_mac_inst[module_idP].scheduling_info.prohibitPHR_SF);
	ue_mac_inst[module_idP].PHR_reporting_active = 0;

	for (i = 0; i < maxLC_ID; i++) {
		printf("[UE%d] Applying default logical channel config for LCGID %d\n", module_idP, i);
		ue_mac_inst[module_idP].scheduling_info.Bj[i] = -1;
		ue_mac_inst[module_idP].scheduling_info.bucket_size[i] = -1;

		if (i < DTCH) {   // initilize all control channels lcgid to 0
			ue_mac_inst[module_idP].scheduling_info.LCGID[i] = 0;
		} else {    // initialize all the data channels lcgid to 1
			ue_mac_inst[module_idP].scheduling_info.LCGID[i] = 1;
		}

		ue_mac_inst[module_idP].scheduling_info.LCID_status[i] = LCID_EMPTY;
		ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[i] = 0;
	}
}


int8_t nr_ue_get_SR(module_id_t module_idP,
						int CC_id,
						frame_t frameP,
						uint8_t eNB_id,
						uint16_t rnti,
						sub_frame_t subframe)
{
//	no UL-SCH resources available for this tti && UE has a valid PUCCH resources for SR configuration for this tti
//	int MGL=6;// measurement gap length in ms
	int MGRP = 0;   // measurement gap repetition period in ms
	int gapOffset = -1;
	int T = 0;
	SetupRelease_1073P25_t* gapconfig = NULL;
	SchedulingRequestToAddMod_t* srmod;

	DevCheck(module_idP < (int) NB_UE_INST, module_idP, NB_UE_INST, 0);
	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

	// determin the measurement gap
	if (ue_mac_inst[module_idP].measconfig->measGapConfig->gapFR1 != NULL) {
		gapconfig = (SetupRelease_1073P25_t*)ue_mac_inst[module_idP].measconfig->measGapConfig->gapFR1;

		if(gapconfig->present == SetupRelease_1073P25_PR_setup) {
			MGRP = gapconfig->choice.setup->mgrp;
			gapOffset = gapconfig->choice.setup->gapOffset;
//			if (gapconfig->choice.setup-> == LTE_MeasGapConfig__setup__gapOffset_PR_gp0) {
//				MGRP = 40;
//				gapOffset = ue_mac_inst[module_idP].measconfig->measGapConfig->choice.setup.gapOffset.choice.gp0;
//			} else if (ue_mac_inst[module_idP].measconfig->measGapConfig->choice.setup.gapOffset.present ==
//					LTE_MeasGapConfig__setup__gapOffset_PR_gp1) {
//				MGRP = 80;
//				gapOffset = ue_mac_inst[module_idP].measconfig->measGapConfig->choice.setup.gapOffset.choice.gp1;
//			} else {
//				printf("Measurement GAP offset is unknown\n");
//			}

			T = MGRP / 10;
			DevAssert(T != 0);

			//check the measurement gap and sr prohibit timer
			if ((subframe == gapOffset % 10) && ((frameP % T) == (floor(gapOffset / 10)))
					&& (ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer_Running == 0)) {
				ue_mac_inst[module_idP].scheduling_info.SR_pending = 1;
				return (0);
			}
		}
	}

	if(ue_mac_inst[module_idP].schedulingRequestConfig->schedulingRequestToAddModList->list.count != 0) {
		srmod = *(ue_mac_inst[module_idP].schedulingRequestConfig->schedulingRequestToAddModList->list.array);
	}

	if ((ue_mac_inst[module_idP].schedulingRequestConfig != NULL) && (ue_mac_inst[module_idP].scheduling_info.SR_pending == 1) &&
			(ue_mac_inst[module_idP].scheduling_info.SR_COUNTER < (1 << (2 + srmod->sr_TransMax)))) {
		printf("[UE %d][SR %x] Frame %d subframe %d PHY asks for SR (SR_COUNTER/dsr_TransMax %d/%d), SR_pending %d\n",
				module_idP, rnti, frameP, subframe, ue_mac_inst[module_idP].scheduling_info.SR_COUNTER,
				(1 << (2 + srmod->sr_TransMax)), ue_mac_inst[module_idP].scheduling_info.SR_pending);
		ue_mac_inst[module_idP].scheduling_info.SR_COUNTER++;

//		start the sr-prohibittimer : rel 9 and above
		if (ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer > 0) { // timer configured
			ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer--;
			ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer_Running = 1;
		} else {
			ue_mac_inst[module_idP].scheduling_info.sr_ProhibitTimer_Running = 0;
		}

		printf("[UE %d][SR %x] Frame %d subframe %d send SR indication (SR_COUNTER/dsr_TransMax %d/%d), SR_pending %d\n",
				module_idP, rnti, frameP, subframe, ue_mac_inst[module_idP].scheduling_info.SR_COUNTER,
				(1 << (2 + srmod->sr_TransMax)), ue_mac_inst[module_idP].scheduling_info.SR_pending);
//		ue_mac_inst[module_idP].ul_active =1;
		return (1);   //instruct phy to signal SR
	} else {
//		notify RRC to relase PUCCH/SRS
//		clear any configured dl/ul
//		initiate RA
		if (ue_mac_inst[module_idP].scheduling_info.SR_pending) {
//			release all pucch resource
			ue_mac_inst[module_idP].schedulingRequestConfig = NULL;
//			ue_mac_inst[module_idP].ul_active = 0;
			ue_mac_inst[module_idP].BSR_reporting_active = BSR_TRIGGER_NONE;
			printf("[UE %d] Release all SRs \n", module_idP);
		}

		ue_mac_inst[module_idP].scheduling_info.SR_pending = 0;
		ue_mac_inst[module_idP].scheduling_info.SR_COUNTER = 0;
		return (0);
	}
}


void process_dlsch_mac_pdu(module_id_t module_idP,
								uint8_t CC_id,
								uint16_t rnti,
								const frame_t rx_frame,
								const sub_frame_t rx_subframe,
								const slot_t rx_slot,
								uint8_t *pduP,
								uint16_t mac_pdu_len)
{
	uint8_t *pdu_ptr = pduP;
	uint16_t pdu_len = mac_pdu_len;

	uint8_t lcid;
	uint16_t mac_ce_len;
	uint16_t mac_subheader_len;
	uint16_t mac_sdu_len;

	int i;

//	For both DL/UL-SCH
//	Except:
//	- UL/DL-SCH: fixed-size MAC CE(known by LCID)
//	- UL/DL-SCH: padding
//	- UL-SCH:    MSG3 48-bits
//	|0|1|2|3|4|5|6|7|  bit-wise
//	|R|F|   LCID    |
//	|       L       |
//	|0|1|2|3|4|5|6|7|  bit-wise
//	|R|F|   LCID    |
//	|       L       |
//	|       L       |
//
//	For both DL/UL-SCH
//	For:
//	- UL/DL-SCH: fixed-size MAC CE(known by LCID)
//	- UL/DL-SCH: padding, for single/multiple 1-oct padding CE(s)
//	- UL-SCH:    MSG3 48-bits
//	|0|1|2|3|4|5|6|7|  bit-wise
//	|R|R|   LCID    |
//	LCID: The Logical Channel ID field identifies the logical channel instance of the corresponding MAC SDU or the type of the corresponding MAC CE or padding as described in Tables 6.2.1-1 and 6.2.1-2 for the DL-SCH and UL-SCH respectively. There is one LCID field per MAC subheader. The LCID field size is 6 bits;
//	L: The Length field indicates the length of the corresponding MAC SDU or variable-sized MAC CE in bytes. There is one L field per MAC subheader except for subheaders corresponding to fixed-sized MAC CEs and padding. The size of the L field is indicated by the F field;
//	F: lenght of L is 0:8 or 1:16 bits wide
//	R: Reserved bit, set to zero.

	uint8_t done = 0;

	while (!done || pdu_len <= 0) {
		mac_ce_len = 0x0000;
		mac_subheader_len = 0x0001; //  default to fixed-length subheader = 1-oct
		mac_sdu_len = 0x0000;
		lcid = ((NR_MAC_SUBHEADER_FIXED *)pdu_ptr)->LCID;
		printf("LCID = %d \n", lcid);

		switch(((NR_MAC_SUBHEADER_FIXED *)pdu_ptr)->LCID) {
//		MAC CE
		case DL_SCH_LCID_CCCH:
//			MSG4 RRC Connection Setup 38.331
//			varialbe length
			mac_ce_len |= (uint16_t)((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->L;
			mac_subheader_len = 2;
			if(((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->F) {
				mac_ce_len |= (uint16_t)(((NR_MAC_SUBHEADER_LONG *)pdu_ptr)->L2) << 8;
				mac_subheader_len = 3;
			}

			printf("DL_SCH_LCID_CCCH payload size is %d\n", mac_ce_len);

//			mac_rrc_data_ind(
//				module_idP,
//				CC_id,
//				rx_frame,
//				rx_subframe,
//				rnti,
//				DL_SCH_LCID_CCCH,
//				(uint8_t *) (pdu_ptr + mac_subheader_len),
//				mac_ce_len,
//				0);
			break;
		case DL_SCH_LCID_TCI_STATE_ACT_UE_SPEC_PDSCH:
//			38.321 Ch6.1.3.14
//			varialbe length
			mac_ce_len |= (uint16_t)((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->L;
			mac_subheader_len = 2;

			if(((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->F) {
				mac_ce_len |= (uint16_t)(((NR_MAC_SUBHEADER_LONG *)pdu_ptr)->L2) << 8;
				mac_subheader_len = 3;
			}

			printf("DL_SCH_LCID_TCI_STATE_ACT_UE_SPEC_PDSCH: MAC CE length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_APERIODIC_CSI_TRI_STATE_SUBSEL:
//			38.321 Ch6.1.3.13
//			varialbe length
			mac_ce_len |= (uint16_t)((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->L;
			mac_subheader_len = 2;

			if(((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->F) {
				mac_ce_len |= (uint16_t)(((NR_MAC_SUBHEADER_LONG *)pdu_ptr)->L2) << 8;
				mac_subheader_len = 3;
			}

			printf("DL_SCH_LCID_APERIODIC_CSI_TRI_STATE_SUBSEL: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_SP_CSI_RS_CSI_IM_RES_SET_ACT:
//			38.321 Ch6.1.3.12
//			varialbe length
			mac_ce_len |= (uint16_t)((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->L;
			mac_subheader_len = 2;

			if(((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->F) {
				mac_ce_len |= (uint16_t)(((NR_MAC_SUBHEADER_LONG *)pdu_ptr)->L2) << 8;
				mac_subheader_len = 3;
			}

			printf("DL_SCH_LCID_SP_CSI_RS_CSI_IM_RES_SET_ACT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_SP_SRS_ACTIVATION:
//			38.321 Ch6.1.3.17
//			varialbe length
			mac_ce_len |= (uint16_t)((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->L;
			mac_subheader_len = 2;

			if(((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->F)
			{
				mac_ce_len |= (uint16_t)(((NR_MAC_SUBHEADER_LONG *)pdu_ptr)->L2) << 8;
				mac_subheader_len = 3;
			}

			printf("DL_SCH_LCID_SP_SRS_ACTIVATION: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_RECOMMENDED_BITRATE:
//			38.321 Ch6.1.3.20
			mac_ce_len = 2;

			printf("DL_SCH_LCID_RECOMMENDED_BITRATE: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_SP_ZP_CSI_RS_RES_SET_ACT:
//			38.321 Ch6.1.3.19
			mac_ce_len = 2;

			printf("DL_SCH_LCID_SP_ZP_CSI_RS_RES_SET_ACT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_PUCCH_SPATIAL_RELATION_ACT:
//			38.321 Ch6.1.3.18
			mac_ce_len = 3;

			printf("DL_SCH_LCID_PUCCH_SPATIAL_RELATION_ACT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_SP_CSI_REP_PUCCH_ACT:
//			38.321 Ch6.1.3.16
			mac_ce_len = 2;

			printf("DL_SCH_LCID_SP_CSI_REP_PUCCH_ACT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_TCI_STATE_IND_UE_SPEC_PDCCH:
//			38.321 Ch6.1.3.15
			mac_ce_len = 2;

			printf("DL_SCH_LCID_TCI_STATE_IND_UE_SPEC_PDCCH: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_DUPLICATION_ACT:
//			38.321 Ch6.1.3.11
			mac_ce_len = 1;

			printf("DL_SCH_LCID_DUPLICATION_ACT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_SCell_ACT_4_OCT:
//			38.321 Ch6.1.3.10
			mac_ce_len = 4;

			printf("DL_SCH_LCID_SCell_ACT_4_OCT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_SCell_ACT_1_OCT:
//			38.321 Ch6.1.3.10
			mac_ce_len = 1;

			printf("DL_SCH_LCID_SCell_ACT_1_OCT: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_L_DRX:
//			38.321 Ch6.1.3.6
//			fixed length but not yet specify.
			mac_ce_len = 0;

			printf("DL_SCH_LCID_L_DRX: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_DRX:
//			38.321 Ch6.1.3.5
//			fixed length but not yet specify.
			mac_ce_len = 0;

			printf("DL_SCH_LCID_DRX: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_TA_COMMAND:
//			38.321 Ch6.1.3.4
			mac_ce_len = 1;

			printf("DL_SCH_LCID_TA_COMMAND: length = %d\n", mac_ce_len);
			break;
		case DL_SCH_LCID_CON_RES_ID:
//			38.321 Ch6.1.3.3
//			与UL CCCH数据进行对比
			mac_ce_len = 6;
			printf("DL_SCH_LCID_CON_RES_ID:\t");
			for(i=0; i<6; i++)
			{
				printf("0x%02x ", *(pdu_ptr + i));
			}
			printf("\n");
			break;
		case DL_SCH_LCID_PADDING:
			done = 1;
//			end of MAC PDU, can ignore the rest.
			break;

//		MAC SDU
		case DL_SCH_LCID_SRB1:
//		check if LCID is valid at current time.
		case UL_SCH_LCID_SRB2:
//		check if LCID is valid at current time.
		case UL_SCH_LCID_SRB3:
//		check if LCID is valid at current time.
		default:
//		check if LCID is valid at current time.
			mac_sdu_len |= (uint16_t)((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->L;
			mac_subheader_len = 2;

			if(((NR_MAC_SUBHEADER_SHORT *)pdu_ptr)->F)
			{
				mac_sdu_len |= (uint16_t)(((NR_MAC_SUBHEADER_LONG *)pdu_ptr)->L2)<<8;
				mac_subheader_len = 3;
			}
			//  DRB LCID by RRC
			printf("DLSCH MAC SDU LCID = %d, length = %d\n", lcid, mac_sdu_len);

			mac_rlc_data_ind(
				module_idP,
				rnti,
				rx_frame,
				ENB_FLAG_NO,
				MBMS_FLAG_NO,
				lcid,
				pdu_ptr + mac_subheader_len,
				mac_sdu_len,
				1,
				NULL);
			break;
		}

		pdu_ptr += (mac_subheader_len + mac_ce_len + mac_sdu_len);
		pdu_len -= (mac_subheader_len + mac_ce_len + mac_sdu_len);

		AssertFatal(pdu_len >= 0, "[MAC] nr_ue_process_mac_pdu, residual mac pdu length < 0!\n");
	}
}

void generate_ulsch_mac_pdu(
	module_id_t module_idP,
	int CC_id,
	const frame_t frameP,
	const sub_frame_t subframe,
	const slot_t slotP,
	uint8_t eNB_index,
	uint8_t * ulsch_buffer,
	uint16_t buflen,
	uint8_t * access_mode)
{
	uint8_t total_rlc_pdu_header_len = 0, rlc_pdu_header_len_last = 0;
	uint16_t buflen_remain = 0;
	uint8_t bsr_len = 0, bsr_ce_len = 0, bsr_header_len = 0;
	uint8_t cgc_len = 0, cgc_ce_len = 0, cgc_header_len =0;
	uint8_t phr_header_len = 0, phr_ce_len = 0, phr_len = 0;
	uint8_t lcid = 0, lcid_rlc_pdu_count = 0;
	boolean_t is_lcid_processed = FALSE;
	boolean_t is_all_lcid_processed = FALSE;
	uint16_t sdu_lengths[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	uint16_t subPDU_len[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t sdu_lcids[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t payload_offset = 0, num_sdus = 0;
	uint8_t ulsch_buff[MAX_ULSCH_PAYLOAD_BYTES];
	uint16_t sdu_length_total = 0;
	uint16_t subPDU_len_total = 0;
	BSR_SHORT bsr_short, bsr_truncated;
	BSR_LONG bsr_long;
	BSR_SHORT *bsr_s = &bsr_short;
	BSR_LONG *bsr_l = &bsr_long;
	BSR_SHORT *bsr_t = &bsr_truncated;
	SINGLE_POWER_HEADROOM phr;
	SINGLE_POWER_HEADROOM *phr_p = &phr;
	unsigned short short_padding = 0, post_padding = 0, padding_len = 0;
	int j;			// used for padding
	// Compute header length
	int lcg_id = 0;
	int lcg_id_bsr_trunc = 0;
	int highest_priority = 16;
	int num_lcg_id_with_data = 0;
	rlc_buffer_occupancy_t lcid_buffer_occupancy_old = 0, lcid_buffer_occupancy_new = 0;
	int offset = 0;
	boolean_t crnti_mce = FALSE;
	uint8_t crnti_mce_len = 0;
	uint8_t cg_mce_len = 0;

	printf("[UE %d] MAC PROCESS UL TRANSPORT BLOCK at frame%d subframe %d TBS=%d\n", module_idP, frameP, subframe, buflen);

	AssertFatal(CC_id == 0, "Transmission on secondary CCs is not supported yet\n");

	cgc_header_len = 1;
	bsr_header_len = 0;
	phr_header_len = 1;		//sizeof(SCH_SUBHEADER_FIXED);

//	TODO 增加C-RNTI MAC CE处理 3GPP 38.321 5.1.4 如果是传输MSG3并且不是CCCH信道，则需要附加
	if(crnti_mce)
	{
		crnti_mce_len = 3;
	}

//	TODO 增加Configured Grant Confirmation MAC CE处理
//	When a configured uplink grant is released by upper layers, all the corresponding configurations shall be released and all corresponding uplink grants shall be cleared.
//	The MAC entity shall:
//	1>	if the configured uplink grant confirmation has been triggered and not cancelled; and
//	1>	if the MAC entity has UL resources allocated for new transmission:
//		2>	instruct the Multiplexing and Assembly procedure to generate an Configured Grant Confirmation MAC CE as defined in clause 6.1.3.7;
//		2>	cancel the triggered configured uplink grant confirmation.
//	For a configured grant Type 2, the MAC entity shall clear the configured uplink grant immediately after first transmission of Configured Grant Confirmation MAC CE triggered by the configured uplink grant deactivation.
//	Retransmissions except for repetition of configured uplink grants use uplink grants addressed to CS-RNTI.
	if(ue_mac_inst[module_idP].configuredGrantReleased) {
		cg_mce_len = 1;
	}

	while (lcg_id <= maxLCG_ID) {
		if (ue_mac_inst[module_idP].scheduling_info.BSR_bytes[lcg_id]) {
			num_lcg_id_with_data++;
		}
		lcg_id++;
	}

	if (num_lcg_id_with_data) {
		printf("[UE %d] MAC Tx data pending at frame%d subframe %d nb LCG =%d Bytes for "
				"LCG0=%d LCG1=%d LCG2=%d LCG3=%d LCG4=%d LCG5=%d LCG6=%d LCG7=%d BSR Trigger status =%d TBS=%d\n",
				module_idP, frameP, subframe, num_lcg_id_with_data,
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[0],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[1],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[2],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[3],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[4],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[5],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[6],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[7],
				ue_mac_inst[module_idP].BSR_reporting_active, buflen);
	}

//	Restart ReTxBSR Timer at new grant indication (38.321)
	if (ue_mac_inst[module_idP].scheduling_info.retxBSR_SF != MAC_UE_BSR_TIMER_NOT_RUNNING) {
		ue_mac_inst[module_idP].scheduling_info.retxBSR_SF =
				get_sf_retxBSRTimer(ue_mac_inst[module_idP].scheduling_info.retxBSR_Timer);
	}

//	periodicBSR-Timer expires, trigger BSR
	if ((ue_mac_inst[module_idP].scheduling_info.periodicBSR_Timer != BSR_Config__periodicBSR_Timer_infinity)
			&& (ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF == 0)) {
//		Trigger BSR Periodic
		ue_mac_inst[module_idP].BSR_reporting_active |= BSR_TRIGGER_PERIODIC;

		printf("[UE %d] MAC BSR Triggered PeriodicBSR Timer expiry at frame%d subframe %d TBS=%d\n",
				module_idP, frameP, subframe, buflen);
	}

	//Compute BSR Length if Regular or Periodic BSR is triggered
	//WARNING: if BSR long is computed, it may be changed to BSR short during or after multiplexing if there remains less than 1 LCGROUP with data after Tx
	if (ue_mac_inst[module_idP].BSR_reporting_active) {
		AssertFatal((ue_mac_inst[module_idP].BSR_reporting_active & BSR_TRIGGER_PADDING) == 0,
				"Inconsistent BSR Trigger=%d !\n", ue_mac_inst[module_idP].BSR_reporting_active);

		if(buflen - crnti_mce_len - cg_mce_len >= 9)
		{
			bsr_header_len = 1;
			bsr_ce_len = 9;
		}
	}

	bsr_len = bsr_ce_len + bsr_header_len; // 此部分可以不计算

//	TODO 当前的PHR与配置有关，长度不定。
//	暂时只支持Single Entry PHR MAC CE。
	if(ue_mac_inst[module_idP].PHR_reporting_active && buflen >= 3)
	{
		phr_header_len = 1;
		phr_ce_len = 2;
	}

	phr_len = phr_header_len + phr_ce_len;

#if 0
	phr_ce_len = (ue_mac_inst[module_idP].PHR_reporting_active == 1) ? 1 : 0;

	if ((phr_ce_len > 0) && ((phr_ce_len + phr_header_len + bsr_len) <= buflen)) {
		phr_len = phr_ce_len + phr_header_len;
		printf("[UE %d] header size info: PHR len %d (ce%d,hdr%d) buff_len %d\n",
				module_idP, phr_len, phr_ce_len, phr_header_len, buflen);
	} else {
		phr_len = 0;
		phr_header_len = 0;
		phr_ce_len = 0;
	}
#endif

//	check for UL bandwidth requests and add SR control element

//	check for UL bandwidth requests and add SR control element

//	Check for DCCH first
//	TO DO: Multiplex in the order defined by the logical channel prioritization
	for (lcid = UL_SCH_LCID_SRB1; (lcid < maxLC_ID) && (is_all_lcid_processed == FALSE); lcid++) {

		if (ue_mac_inst[module_idP].scheduling_info.LCID_status[lcid] == LCID_NOT_EMPTY) {

			lcid_rlc_pdu_count = 0;

			is_lcid_processed = FALSE;

			lcid_buffer_occupancy_old = mac_rlc_get_buffer_occupancy_ind(module_idP,
																					ue_mac_inst[module_idP].cs_RNTI,
																					frameP,
																					subframe,
																					slotP,
																					ENB_FLAG_NO,
																					lcid);

			lcid_buffer_occupancy_new = lcid_buffer_occupancy_old;

			AssertFatal(lcid_buffer_occupancy_new == ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[lcid],
					"LCID=%d RLC has BO %d bytes but MAC has stored %d bytes\n", lcid, lcid_buffer_occupancy_new,
					ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[lcid]);

			AssertFatal(lcid_buffer_occupancy_new <=
					ue_mac_inst[module_idP].scheduling_info.BSR_bytes[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]],
					"LCID=%d RLC has more BO %d bytes than BSR = %d bytes\n", lcid, lcid_buffer_occupancy_new,
					ue_mac_inst[module_idP].scheduling_info.BSR_bytes[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]]);


//			Multiplex all available DCCH RLC PDUs considering to multiplex the last PDU each time for maximize the data
//			Adjust at the end of the loop
//			while ((!is_lcid_processed) && (lcid_buffer_occupancy_new) &&
//					(bsr_len + phr_len + total_rlc_pdu_header_len + sdu_length_total + MIN_MAC_HDR_RLC_SIZE <= buflen)) {
			while ((!is_lcid_processed) && (lcid_buffer_occupancy_new) && (buflen >= 4)) {
//				if ((usim_test == 0) && (lcid == UL_SCH_LCID_SRB2) && (lcid_rlc_pdu_count == 0) && (num_sdus))
				if ((lcid == UL_SCH_LCID_SRB2) && (lcid_rlc_pdu_count == 0) && (num_sdus)) {
//					Skip SRB2 multiplex if at least one SRB1 SDU is already multiplexed
					break;
				}

				buflen_remain = buflen - (crnti_mce_len + cg_mce_len + bsr_len + phr_len + total_rlc_pdu_header_len + sdu_length_total + 1);

//				TODO 计算当前时刻当前逻辑信道可以传输的最大数据量
				if(buflen_remain > ue_mac_inst[module_idP].scheduling_info.Bj[lcid])
				{
					buflen_remain = ue_mac_inst[module_idP].scheduling_info.Bj[lcid];
				}

				printf("[UE %d] Frame %d : UL-DXCH -> ULSCH, RLC %d has %d bytes to "
						"send (Transport Block size %d BSR size=%d PHR=%d SDU Length Total %d , "
						"mac header len %d BSR byte before Tx=%d)\n",
						module_idP, frameP, lcid, lcid_buffer_occupancy_new,	buflen, bsr_len, phr_len, sdu_length_total,
						total_rlc_pdu_header_len,
						ue_mac_inst[module_idP].scheduling_info.BSR_bytes[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]]);

				sdu_lengths[num_sdus] = mac_rlc_data_req(module_idP,
																ue_mac_inst[module_idP].cs_RNTI,
																frameP,
																subframe,
																slotP,
																lcid,
																buflen_remain,
																(char *)&ulsch_buff[sdu_length_total]);

				AssertFatal(buflen_remain >= sdu_lengths[num_sdus],"LCID=%d RLC has segmented %d bytes but MAC has max=%d\n",
						lcid, sdu_lengths[num_sdus], buflen_remain);

				if(sdu_lengths[num_sdus]) {
					sdu_length_total += sdu_lengths[num_sdus];
					sdu_lcids[num_sdus] = lcid;

					printf("[UE %d] TX Multiplex RLC PDU TX Got %d bytes for LcId%d\n", module_idP, sdu_lengths[num_sdus], lcid);

					if (buflen ==	(bsr_len + phr_len + total_rlc_pdu_header_len + sdu_length_total + 1)) {
//						No more remaining TBS after this PDU
//						exit the function
						rlc_pdu_header_len_last = 1;
						is_lcid_processed = TRUE;
						is_all_lcid_processed = TRUE;
					} else {
						rlc_pdu_header_len_last = (sdu_lengths[num_sdus] > 128) ? 3 : 2;

//						Change to 1 byte if it does not fit in the TBS, ie last PDU
						if (buflen <=	(bsr_len + phr_len + total_rlc_pdu_header_len + rlc_pdu_header_len_last + sdu_length_total)) {
							rlc_pdu_header_len_last = 1;
							is_lcid_processed = TRUE;
							is_all_lcid_processed = TRUE;
						}
					}

					//Update number of SDU
					num_sdus++;

					//Update total MAC Header size for RLC PDUs and save last one
					total_rlc_pdu_header_len += rlc_pdu_header_len_last;

					lcid_rlc_pdu_count++;
				} else {
					/* avoid infinite loop ... */
					is_lcid_processed = TRUE;
				}

				/* Get updated BO after multiplexing this PDU */
				lcid_buffer_occupancy_new = mac_rlc_get_buffer_occupancy_ind(module_idP,
																						ue_mac_inst[module_idP].cs_RNTI,
																						frameP,
																						subframe,
																						slotP,
																						ENB_FLAG_NO,
																						lcid);

				is_lcid_processed = (is_lcid_processed) || (lcid_buffer_occupancy_new <= 0);
			}

//			Update Buffer remain and BSR bytes after transmission

			AssertFatal(lcid_buffer_occupancy_new <= lcid_buffer_occupancy_old,
					"MAC UE Tx error : Buffer Occupancy After Tx=%d greater than before=%d BO! for LCID=%d RLC PDU nb=%d Frame %d Subrame %d\n",
					lcid_buffer_occupancy_new, lcid_buffer_occupancy_old, lcid, lcid_rlc_pdu_count, frameP, subframe);

			ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[lcid] = lcid_buffer_occupancy_new;
			ue_mac_inst[module_idP].scheduling_info.BSR_bytes[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]] +=
					(lcid_buffer_occupancy_new - lcid_buffer_occupancy_old);

//			Update the number of LCGID with data as BSR shall reflect status after BSR transmission
			if ((num_lcg_id_with_data > 1) &&
					(ue_mac_inst[module_idP].scheduling_info.BSR_bytes[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]] == 0)) {
				num_lcg_id_with_data--;
//				Change BSR size to BSR SHORT if num_lcg_id_with_data becomes to 1
				if ((bsr_len) && (num_lcg_id_with_data == 1)) {
					bsr_ce_len = sizeof(BSR_SHORT);
					bsr_len = bsr_ce_len + bsr_header_len;
				}
			}

			ue_mac_inst[module_idP].scheduling_info.LCID_status[lcid] = LCID_EMPTY;
		}
	}

//	TODO 填充C-RNTI MAC CE

//	TODO 填充Configured Grant Confirmation MAC CE

//	TODO 填充MAC CE for BSR，根据剩余数据长度填充类型可变化

//	TODO 填充Single Entry PHR MAC CE

//	TODO 填充MAC CE for Recommended bit rate query

//	TODO 如果有填充字段，并且未触发 BSR，填充MAC CE for BSR included for padding



//	Compute BSR Values and update Nb LCGID with data after multiplexing
	num_lcg_id_with_data = 0;
	lcg_id_bsr_trunc = 0;

	for (lcg_id = 0; lcg_id <= maxLCG_ID; lcg_id++) {
		ue_mac_inst[module_idP].scheduling_info.BSR[lcg_id] =
				locate_BsrIndexByBufferSize(BSR5_TABLE, BSR5_TABLE_SIZE, ue_mac_inst[module_idP].scheduling_info.BSR_bytes[lcg_id]);

		if (ue_mac_inst[module_idP].scheduling_info.BSR_bytes[lcg_id]) {
			num_lcg_id_with_data++;
			lcg_id_bsr_trunc = lcg_id;
		}
	}


	if (bsr_ce_len) {
//		Print updated BSR when sent
		printf("[UE %d] Remaining Buffer after Tx frame%d subframe %d nb LCG =%d Bytes for LCG0=%d LCG1=%d LCG2=%d LCG3=%d BSR Trigger status =%d TBS=%d\n",
				module_idP, frameP, subframe, num_lcg_id_with_data,
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[0],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[1],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[2],
				ue_mac_inst[module_idP].scheduling_info.BSR_bytes[3],
				ue_mac_inst[module_idP].BSR_reporting_active, buflen);

		printf("[UE %d] Frame %d Subframe %d TX BSR Regular or Periodic size=%d BSR0=%d BSR1=%d BSR2=%d BSR3=%d\n",
				module_idP, frameP, subframe, bsr_ce_len,
				ue_mac_inst[module_idP].scheduling_info.BSR[0],
				ue_mac_inst[module_idP].scheduling_info.BSR[1],
				ue_mac_inst[module_idP].scheduling_info.BSR[2],
				ue_mac_inst[module_idP].scheduling_info.BSR[3]);
	}

	// build PHR and update the timers
	if (phr_ce_len == sizeof(SINGLE_POWER_HEADROOM)) {
#if 0
		if(nfapi_mode ==3)
		{
//			Substitute with a static value for the MAC layer abstraction (phy_stub mode)
			phr_p->PH = 40;
		}
		else
		{
#endif
//			phr_p->PH = get_phr_mapping(module_idP, CC_id, eNB_index); // TODO need fixed
//		}

		phr_p->R1 = 0;

//		printf("[UE %d] Frame %d report PHR with mapping (%d->%d) for LCID %d\n",
//				module_idP, frameP, get_PHR(module_idP, CC_id, eNB_index), // TODO need fixed
//				phr_p->PH, 5/*POWER_HEADROOM*/);

//		update_phr(module_idP, CC_id); //TODO need fixed
	} else {
		phr_p = NULL;
	}

	printf("[UE %d] Frame %d: bsr s %p bsr_l %p, phr_p %p\n", module_idP, frameP, bsr_s, bsr_l, phr_p);

	// Check BSR padding: it is done after PHR according to Logical Channel Prioritization order
	// Check for max padding size, ie MAC Hdr for last RLC PDU = 1
	/* For Padding BSR:
	-  if the number of padding bits is equal to or larger than the size of the Short BSR plus its subheader but smaller than the size of the Long BSR plus its subheader:
	-  if more than one LCG has data available for transmission in the TTI where the BSR is transmitted: report Truncated BSR of the LCG with the highest priority logical channel with data available for transmission;
	-  else report Short BSR.
	-  else if the number of padding bits is equal to or larger than the size of the Long BSR plus its subheader, report Long BSR.
	*/
	if (sdu_length_total) {
		padding_len = buflen - (bsr_len + phr_len + total_rlc_pdu_header_len - rlc_pdu_header_len_last + sdu_length_total + 1);
	} else {
		padding_len = buflen - (bsr_len + phr_len);
	}


	if ((padding_len) && (bsr_len == 0)) {
		/* if the number of padding bits is equal to or larger than the size of the Long BSR plus its subheader, report Long BSR */
		if (padding_len >= (1 + BSR_LONG_SIZE)) {
			bsr_ce_len = BSR_LONG_SIZE;
			bsr_header_len = 1;
			// Trigger BSR Padding
			ue_mac_inst[module_idP].BSR_reporting_active |= BSR_TRIGGER_PADDING;
		} else if (padding_len >= (1 + sizeof(BSR_SHORT))) {
			bsr_ce_len = sizeof(BSR_SHORT);
			bsr_header_len = 1;

			if (num_lcg_id_with_data > 1) {
//				REPORT TRUNCATED BSR
//				Get LCGID of highest priority LCID with data
				for (lcid = UL_SCH_LCID_SRB1; lcid < maxLC_ID; lcid++) {
					if (ue_mac_inst[module_idP].logicalChannelConfig[lcid] != NULL) {
						lcg_id = ue_mac_inst[module_idP].scheduling_info.LCGID[lcid];

						if ((lcg_id < maxLCG_ID) && (ue_mac_inst[module_idP].scheduling_info.BSR_bytes[lcg_id]) &&
						(ue_mac_inst[module_idP].logicalChannelConfig[lcid]->ul_SpecificParameters->priority <=  highest_priority)) {
							highest_priority = ue_mac_inst[module_idP].logicalChannelConfig[lcid]->ul_SpecificParameters->priority;

							lcg_id_bsr_trunc = lcg_id;
						}
					}
				}
			} else {
//				Report SHORT BSR, clear bsr_t
				bsr_t = NULL;
			}

//			Trigger BSR Padding
			ue_mac_inst[module_idP].BSR_reporting_active |= BSR_TRIGGER_PADDING;
		}
		bsr_len = bsr_header_len + bsr_ce_len;
	}

//	Fill BSR Infos
	if (bsr_ce_len == 0) {
		bsr_s = NULL;
		bsr_l = NULL;
		bsr_t = NULL;
	} else if (bsr_ce_len == BSR_LONG_SIZE) {
		bsr_s = NULL;
		bsr_t = NULL;
		bsr_l->Buffer_size0 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID0];
		bsr_l->Buffer_size1 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID1];
		bsr_l->Buffer_size2 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID2];
		bsr_l->Buffer_size3 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID3];
		bsr_l->Buffer_size4 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID4];
		bsr_l->Buffer_size5 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID5];
		bsr_l->Buffer_size6 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID6];
		bsr_l->Buffer_size7 = ue_mac_inst[module_idP].scheduling_info.BSR[LCGID7];

		printf("[UE %d] Frame %d subframe %d BSR Trig=%d report long BSR (level LCGID0 %d,level LCGID1 %d,"
				"level LCGID2 %d,level LCGID3 %d,level LCGID4 %d,level LCGID5 %d,level LCGID6 %d,level LCGID7 %d)\n",
				module_idP, frameP, subframe,
				ue_mac_inst[module_idP].BSR_reporting_active,
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID0],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID1],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID2],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID3],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID4],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID5],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID6],
				ue_mac_inst[module_idP].scheduling_info.BSR[LCGID7]);
	} else if (bsr_ce_len == sizeof(BSR_SHORT)) {
		bsr_l = NULL;

		if ((bsr_t != NULL) && (ue_mac_inst[module_idP].BSR_reporting_active & BSR_TRIGGER_PADDING)) {
//			Truncated BSR
			bsr_s = NULL;
			bsr_t->LCGID = lcg_id_bsr_trunc;
			bsr_t->Buffer_size = ue_mac_inst[module_idP].scheduling_info.BSR[lcg_id_bsr_trunc];

			printf("[UE %d] Frame %d subframe %d BSR Trig=%d report TRUNCATED BSR with level %d for LCGID %d\n",
					module_idP, frameP, subframe, ue_mac_inst[module_idP].BSR_reporting_active,
					ue_mac_inst[module_idP].scheduling_info.BSR[lcg_id_bsr_trunc], lcg_id_bsr_trunc);

		} else {
			bsr_t = NULL;
			bsr_s->LCGID = lcg_id_bsr_trunc;
			bsr_s->Buffer_size = ue_mac_inst[module_idP].scheduling_info.BSR[lcg_id_bsr_trunc];

			printf("[UE %d] Frame %d subframe %d BSR Trig=%d report SHORT BSR with level %d for LCGID %d\n",
					module_idP, frameP, subframe, ue_mac_inst[module_idP].BSR_reporting_active,
					ue_mac_inst[module_idP].scheduling_info.BSR[lcg_id_bsr_trunc], lcg_id_bsr_trunc);
		}
	}
//	1-bit padding or 2-bit padding  special padding subheader
//	Check for max padding size, ie MAC Hdr for last RLC PDU = 1
	if (sdu_length_total) {
		padding_len =
		buflen - (bsr_len + phr_len + total_rlc_pdu_header_len -
		rlc_pdu_header_len_last + sdu_length_total + 1);
	} else {
		padding_len = buflen - (bsr_len + phr_len);
	}

	if (padding_len <= 2) {
		short_padding = padding_len;
//		only add padding header
		post_padding = 0;
//		update total MAC Hdr size for RLC data
		if (sdu_length_total) {
			total_rlc_pdu_header_len =
			total_rlc_pdu_header_len - rlc_pdu_header_len_last + 1;
			rlc_pdu_header_len_last = 1;
		}
	} else if (sdu_length_total) {
		post_padding = buflen - (bsr_len + phr_len + total_rlc_pdu_header_len + sdu_length_total + 1);

		// If by adding MAC Hdr for last RLC PDU the padding is 0 then set MAC Hdr for last RLC PDU = 1 and compute 1 or 2 byte padding
		if (post_padding == 0) {
			total_rlc_pdu_header_len -= rlc_pdu_header_len_last;
			padding_len = buflen - (bsr_len + phr_len + total_rlc_pdu_header_len + sdu_length_total + 1);
			short_padding = padding_len;
			total_rlc_pdu_header_len++;
		}
	} else {
		if (padding_len == buflen) {	// nona mac pdu
			*access_mode = CANCELED_ACCESS;
		}

		short_padding = 0;

		post_padding =
		buflen - (bsr_len + phr_len + total_rlc_pdu_header_len +
		sdu_length_total + 1);
	}

	printf("[UE %d] Generate header :bufflen %d  sdu_length_total %d, num_sdus %d, sdu_lengths[0] %d, "
			"sdu_lcids[0] %d => payload offset %d,  total_rlc_pdu_header_len %d, padding %d,post_padding %d, "
			"bsr len %d, phr len %d, reminder %d \n",
			module_idP, buflen, sdu_length_total, num_sdus, sdu_lengths[0],
			sdu_lcids[0], payload_offset, total_rlc_pdu_header_len,
			short_padding, post_padding, bsr_len, phr_len,
			buflen - sdu_length_total - payload_offset);

//	cycle through SDUs and place in ulsch_buffer
	if (sdu_length_total) {
		memcpy(&ulsch_buffer[payload_offset], ulsch_buff, sdu_length_total);
	}

//	fill remainder of DLSCH with random data
	if (post_padding) {
		for (j = 0; j < (buflen - sdu_length_total - payload_offset); j++) {
#ifdef softSIM
			ulsch_buffer[payload_offset + sdu_length_total + j] = (char) (taus() & 0xff);
#else
			ulsch_buffer[payload_offset + sdu_length_total + j] = 0x00;
#endif
		}
	}

	printf("[UE %d][SR] Gave SDU to PHY, clearing any scheduling request\n", module_idP);

	ue_mac_inst[module_idP].scheduling_info.SR_pending = 0;
	ue_mac_inst[module_idP].scheduling_info.SR_COUNTER = 0;

	/* Actions when a BSR is sent */
	if (bsr_ce_len) {
		printf("[UE %d] MAC BSR Sent !! bsr (ce%d,hdr%d) buff_len %d\n", module_idP, bsr_ce_len, bsr_header_len, buflen);

//		Reset ReTx BSR Timer
		ue_mac_inst[module_idP].scheduling_info.retxBSR_SF =
				get_sf_retxBSRTimer(ue_mac_inst[module_idP].scheduling_info.retxBSR_Timer);

		printf("[UE %d] MAC ReTx BSR Timer Reset =%d\n", module_idP, ue_mac_inst[module_idP].scheduling_info.retxBSR_SF);

//		eset Periodic Timer except when BSR is truncated
		if ((bsr_t == NULL) && (ue_mac_inst[module_idP].scheduling_info.periodicBSR_Timer != BSR_Config__periodicBSR_Timer_infinity)) {
			ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF =
					get_sf_periodicBSRTimer(ue_mac_inst[module_idP].scheduling_info.periodicBSR_Timer);

			printf("[UE %d] MAC Periodic BSR Timer Reset =%d\n",	module_idP, ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF);

		}

//		Reset BSR Trigger flags
		ue_mac_inst[module_idP].BSR_reporting_active = BSR_TRIGGER_NONE;
	}
}

#if 0
//------------------------------------------------------------------------------
// called at each subframe
// Performs :
// 1. Trigger PDCP every 5ms
// 2. Call RRC for link status return to PHY
// 3. Perform SR/BSR procedures for scheduling feedback
// 4. Perform PHR procedures

NR_UE_L2_STATE_t ue_scheduler(const module_id_t module_idP,
								const frame_t rxFrameP,
								const sub_frame_t rxSubframeP,
								const frame_t txFrameP,
								const sub_frame_t txSubframeP,
								const lte_subframe_t directionP,
								const uint8_t eNB_indexP, const int CC_id)
//------------------------------------------------------------------------------
{
	int lcid;     // lcid index
	int TTI = 1;
	int bucketsizeduration = -1;
	int bucketsizeduration_max = -1;
	// mac_rlc_status_resp_t rlc_status[MAX_NUM_LCGID]; // 4
	// int8_t lcg_id;
	struct LTE_RACH_ConfigCommon *rach_ConfigCommon =
	(struct LTE_RACH_ConfigCommon *) NULL;
	protocol_ctxt_t ctxt;

	PROTOCOL_CTXT_SET_BY_MODULE_ID(&ctxt, module_idP, ENB_FLAG_NO, ue_mac_inst[module_idP].cs_RNTI, txFrameP, txSubframeP);


	//Mac_rlc_xface->frameP=frameP;
	//Rrc_xface->Frame_index=Mac_rlc_xface->frameP;
	//if (subframe%5 == 0)
	//LG#ifdef EXMIMO

	// data to/from NETLINK is treated in pdcp_run.
	// one socket is used in multiple UE's L2 FAPI simulator and
	// only first UE need to do this.
	if (UE_NAS_USE_TUN) {
		pdcp_run(&ctxt);
	} else {
		if(module_idP == 0) {
			pdcp_run(&ctxt);
		}
	}

	ue_mac_inst[module_idP].txFrame = txFrameP;
	ue_mac_inst[module_idP].txSubframe = txSubframeP;
	ue_mac_inst[module_idP].rxFrame = rxFrameP;
	ue_mac_inst[module_idP].rxSubframe = rxSubframeP;

	switch (rrc_rx_tx_ue(&ctxt, eNB_indexP, CC_id)) {
	case RRC_OK:
	break;

	case RRC_ConnSetup_failed:
		LOG_E(MAC, "RRCConnectionSetup failed, returning to IDLE state\n");
		VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME
		(VCD_SIGNAL_DUMPER_FUNCTIONS_UE_SCHEDULER, VCD_FUNCTION_OUT);
		#if UE_TIMING_TRACE
		stop_meas(&ue_mac_inst[module_idP].ue_scheduler);
		#endif
		return (CONNECTION_LOST);
		break;

	case RRC_PHY_RESYNCH:
		LOG_E(MAC, "RRC Loss of synch, returning PHY_RESYNCH\n");

		#if UE_TIMING_TRACE
		stop_meas(&ue_mac_inst[module_idP].ue_scheduler);
		#endif
		return (PHY_RESYNCH);

	case RRC_Handover_failed:
		printf("Handover failure for UE %d eNB_index %d\n", module_idP,
		eNB_indexP);
		//Invalid...need to add another MAC UE state for re-connection procedure
		phy_config_afterHO_ue(module_idP, 0, eNB_indexP,
		(LTE_MobilityControlInfo_t *) NULL, 1);
		//return(3);
		break;

	case RRC_HO_STARTED:
		LOG_I(MAC,
		"RRC handover, Instruct PHY to start the contention-free PRACH and synchronization\n");

		#if UE_TIMING_TRACE
		stop_meas(&ue_mac_inst[module_idP].ue_scheduler);
		#endif
		return (PHY_HO_PRACH);

	default:
		break;
	}


	// Check Contention resolution timer (put in a function later)
	if (ue_mac_inst[module_idP].RA_contention_resolution_timer_active == 1) {
		if (ue_mac_inst[module_idP].radioResourceConfigCommon) {
			rach_ConfigCommon = &ue_mac_inst[module_idP].radioResourceConfigCommon->rach_ConfigCommon;
		} else {
			LOG_E(MAC, "FATAL: radioResourceConfigCommon is NULL!!!\n");

			AssertFatal(1 == 0, "");
			#if UE_TIMING_TRACE
			stop_meas(&ue_mac_inst[module_idP].ue_scheduler);
			#endif
			//return(RRC_OK);
		}

		printf("Frame %d: Contention resolution timer %d/%ld\n",
				txFrameP, ue_mac_inst[module_idP].RA_contention_resolution_cnt,
				((1 + rach_ConfigCommon->ra_SupervisionInfo.mac_ContentionResolutionTimer) << 3));

		ue_mac_inst[module_idP].RA_contention_resolution_cnt++;

		if (ue_mac_inst[module_idP].RA_contention_resolution_cnt ==
				((1 + rach_ConfigCommon->ra_SupervisionInfo.mac_ContentionResolutionTimer) << 3)) {
			ue_mac_inst[module_idP].RA_active = 0;
			ue_mac_inst[module_idP].RA_contention_resolution_timer_active = 0;
			// Signal PHY to quit RA procedure
			LOG_E(MAC, "Module id %u Contention resolution timer expired, RA failed\n", module_idP);

			if(NFAPI_MODE==NFAPI_UE_STUB_PNF) { // phy_stub mode
				// Modification for phy_stub mode operation here. We only need to make sure that the ue_mode is back to
				// PRACH state.
				printf("nfapi_mode3: Setting UE_mode to PRACH 2 \n");
				ue_mac_inst[module_idP].UE_mode[eNB_indexP] = PRACH;
				//ra_failed(module_idP,CC_id,eNB_index);ue_mac_inst[module_idP].RA_contention_resolution_timer_active = 0;
			} else {
				ra_failed(module_idP, CC_id, eNB_indexP);
			}

			//ra_failed(module_idP, 0, eNB_indexP);
		}
	}

	// Get RLC status info and update Bj for all lcids that are active
	for (lcid = DCCH; lcid < MAX_NUM_LCID; lcid++) {
		if (ue_mac_inst[module_idP].logicalChannelConfig[lcid]) {
			// meausre the Bj
			if ((directionP == SF_UL) && (ue_mac_inst[module_idP].scheduling_info.Bj[lcid] >= 0)) {
				if (ue_mac_inst[module_idP].logicalChannelConfig[lcid]->ul_SpecificParameters) {
					bucketsizeduration =
					ue_mac_inst[module_idP].logicalChannelConfig
					[lcid]->ul_SpecificParameters->prioritisedBitRate *
					TTI;
					bucketsizeduration_max =
					get_ms_bucketsizeduration(ue_mac_inst
					[module_idP].logicalChannelConfig
					[lcid]->ul_SpecificParameters->bucketSizeDuration);
				} else {
					LOG_E(MAC,
					"[UE %d] lcid %d, NULL ul_SpecificParameters\n",
					module_idP, lcid);
					AssertFatal(1 == 0, "");
				}

				if (ue_mac_inst[module_idP].scheduling_info.Bj[lcid] > bucketsizeduration_max) {
					ue_mac_inst[module_idP].scheduling_info.Bj[lcid] = bucketsizeduration_max;
				} else {
					ue_mac_inst[module_idP].scheduling_info.Bj[lcid] = bucketsizeduration;
				}
			}

			/*
			if (lcid == DCCH) {
			LOG_D(MAC,"[UE %d][SR] Frame %d subframe %d Pending data for SRB1=%d for LCGID %d \n",
			module_idP, txFrameP,txSubframeP,ue_mac_inst[module_idP].scheduling_info.BSR[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]],
			//         ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]);
			}
			*/
		}
	}

	// Call BSR procedure as described in Section 5.4.5 in 38.321

	// First check ReTxBSR Timer because it is always configured
	// Decrement ReTxBSR Timer if it is running and not null
	if ((ue_mac_inst[module_idP].scheduling_info.retxBSR_SF != MAC_UE_BSR_TIMER_NOT_RUNNING)
			&& (ue_mac_inst[module_idP].scheduling_info.retxBSR_SF != 0)) {
		ue_mac_inst[module_idP].scheduling_info.retxBSR_SF--;
	}

	// Decrement Periodic Timer if it is running and not null
	if ((ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF != MAC_UE_BSR_TIMER_NOT_RUNNING)
			&& (ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF != 0)) {
		ue_mac_inst[module_idP].scheduling_info.periodicBSR_SF--;
	}

	//Check whether Regular BSR is triggered
	if (update_bsr(module_idP, txFrameP, txSubframeP, eNB_indexP) == TRUE) {
		// call SR procedure to generate pending SR and BSR for next PUCCH/PUSCH TxOp.  This should implement the procedures
		// outlined in Sections 5.4.4 an 5.4.5 of 38.321
		ue_mac_inst[module_idP].scheduling_info.SR_pending = 1;
		// Regular BSR trigger
		ue_mac_inst[module_idP].BSR_reporting_active |= BSR_TRIGGER_REGULAR;
		printf("[UE %d][BSR] Regular BSR Triggered Frame %d subframe %d SR for PUSCH is pending\n",
				module_idP, txFrameP, txSubframeP);
	}

	// UE has no valid phy config dedicated ||  no valid/released  SR
	if ((ue_mac_inst[module_idP].physicalConfigDedicated == NULL)) {
		// cancel all pending SRs
		ue_mac_inst[module_idP].scheduling_info.SR_pending = 0;
		ue_mac_inst[module_idP].ul_active = 0;
		LOG_T(MAC, "[UE %d] Release all SRs \n", module_idP);

		#if UE_TIMING_TRACE
		stop_meas(&ue_mac_inst[module_idP].ue_scheduler);
		#endif
		return (CONNECTION_OK);
	}

	if ((ue_mac_inst[module_idP].physicalConfigDedicated->schedulingRequestConfig == NULL)
			|| (ue_mac_inst[module_idP].physicalConfigDedicated->schedulingRequestConfig->present ==
					LTE_SchedulingRequestConfig_PR_release)) {
		// initiate RA with CRNTI included in msg3 (no contention) as descibed in 38.321 sec 5.1.5
		// cancel all pending SRs
		ue_mac_inst[module_idP].scheduling_info.SR_pending = 0;
		ue_mac_inst[module_idP].ul_active = 0;
		LOG_T(MAC, "[UE %d] Release all SRs \n", module_idP);
	}

	// Put this in a function
	// Call PHR procedure as described in Section 5.4.6 in 38.321
	if (ue_mac_inst[module_idP].PHR_state == LTE_MAC_MainConfig__phr_Config_PR_setup) { // normal operation
		if (ue_mac_inst[module_idP].PHR_reconfigured == 1) {  // upon (re)configuration of the power headroom reporting functionality by upper layers
			ue_mac_inst[module_idP].PHR_reporting_active = 1;
			ue_mac_inst[module_idP].PHR_reconfigured = 0;
		} else {
			//LOG_D(MAC,"PHR normal operation %d active %d \n", ue_mac_inst[module_idP].scheduling_info.periodicPHR_SF, ue_mac_inst[module_idP].PHR_reporting_active);
			if ((ue_mac_inst[module_idP].scheduling_info.prohibitPHR_SF <= 0) &&
					((get_PL(module_idP, 0, eNB_indexP) < ue_mac_inst[module_idP].scheduling_info.PathlossChange_db)
							|| (ue_mac_inst[module_idP].power_backoff_db[eNB_indexP] > ue_mac_inst[module_idP].scheduling_info.PathlossChange_db)))
			// trigger PHR and reset the timer later when the PHR report is sent
			{
				ue_mac_inst[module_idP].PHR_reporting_active = 1;
			} else if (ue_mac_inst[module_idP].PHR_reporting_active == 0) {
				ue_mac_inst[module_idP].scheduling_info.prohibitPHR_SF--;
			}

			if (ue_mac_inst[module_idP].scheduling_info.periodicPHR_SF <= 0)
			// trigger PHR and reset the timer later when the PHR report is sent
			{
				ue_mac_inst[module_idP].PHR_reporting_active = 1;
			} else if (ue_mac_inst[module_idP].PHR_reporting_active == 0) {
				ue_mac_inst[module_idP].scheduling_info.periodicPHR_SF--;
			}
		}
	} else {      // release / nothing
		ue_mac_inst[module_idP].PHR_reporting_active = 0; // release PHR
	}

	//If the UE has UL resources allocated for new transmission for this TTI here:
	#if UE_TIMING_TRACE
	stop_meas(&ue_mac_inst[module_idP].ue_scheduler);
	#endif
	return (CONNECTION_OK);
}
#endif

boolean_t update_bsr(
	module_id_t module_idP,
	const frame_t tx_frameP,
	const sub_frame_t tx_subframeP,
	const slot_t tx_slot)
{
	mac_rlc_status_resp_t rlc_status;
	boolean_t bsr_regular_triggered = FALSE;
	uint8_t lcid;
	uint8_t lcgid;
	uint8_t num_lcid_with_data = 0; // for LCID with data only if LCGID is defined
	uint16_t lcgid_buffer_remain[maxLCG_ID + 1] = {0, 0, 0, 0, 0, 0, 0, 0};
	int32_t lcid_bytes_in_buffer[maxLC_ID];
	/* Array for ordering LCID with data per decreasing priority order */
	uint8_t lcid_reordered_array[maxLC_ID] = {maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID,
													maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID,
													maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID,
													maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID, maxLC_ID};
	uint8_t pos_next = 0;
	uint8_t highest_priority = 16;
	uint8_t array_index = 0;
	// Reset All BSR Infos
	lcid_bytes_in_buffer[0] = 0;

	for (lcid=UL_SCH_LCID_SRB1; lcid<=maxLC_ID; lcid++) {
//		Reset transmission status
		lcid_bytes_in_buffer[lcid] = 0;
		ue_mac_inst[module_idP].scheduling_info.LCID_status[lcid]=LCID_EMPTY;
	}

	for (lcgid=0; lcgid<=maxLCG_ID; lcgid++) {
//		Reset Buffer Info
		ue_mac_inst[module_idP].scheduling_info.BSR[lcgid]=0;
		ue_mac_inst[module_idP].scheduling_info.BSR_bytes[lcgid]=0;
	}

//	Get Buffer Occupancy and fill lcid_reordered_array
	for (lcid=UL_SCH_LCID_SRB1; lcid<=maxLC_ID; lcid++)
	{
		if (ue_mac_inst[module_idP].logicalChannelConfig[lcid] != NULL)
		{
			lcgid = ue_mac_inst[module_idP].scheduling_info.LCGID[lcid];

//			Store already available data to transmit per Group
			if (lcgid <= maxLCG_ID)
			{
				lcgid_buffer_remain[lcgid] += ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[lcid];
			}

			rlc_status = mac_rlc_status_ind(
								module_idP,
								ue_mac_inst[module_idP].cs_RNTI,
								1,
								tx_frameP,
								tx_subframeP,
								0,
								ENB_FLAG_NO,
								MBMS_FLAG_NO,
								lcid,
								0xFFFF //TBS is not used in RLC at this step, set a special value for debug
								);
			lcid_bytes_in_buffer[lcid] = rlc_status.bytes_in_buffer;

			if (rlc_status.bytes_in_buffer > 0)
			{
				printf("[UE %d] PDCCH Tick : LCID%d LCGID%d has data to transmit =%d bytes at frame %d subframe %d, slot %d\n",
							module_idP, lcid,lcgid,rlc_status.bytes_in_buffer, tx_frameP, tx_subframeP, tx_slot);

				ue_mac_inst[module_idP].scheduling_info.LCID_status[lcid] = LCID_NOT_EMPTY;

				//Update BSR_bytes and position in lcid_reordered_array only if Group is defined
				if (lcgid <= maxLCG_ID)
				{
					num_lcid_with_data ++;
					// sum lcid buffer which has same lcgid
					ue_mac_inst[module_idP].scheduling_info.BSR_bytes[lcgid] += rlc_status.bytes_in_buffer;
					//Fill in the array
					array_index = 0;

					do
					{
						if (ue_mac_inst[module_idP].logicalChannelConfig[lcid]->ul_SpecificParameters->priority <= highest_priority)
						{
							//Insert if priority is higher or equal (lower or equal in value)
							for(pos_next=num_lcid_with_data-1; pos_next>array_index; pos_next--)
							{
								lcid_reordered_array[pos_next] = lcid_reordered_array[pos_next - 1];
							}

							lcid_reordered_array[array_index] = lcid;
							break;
						}

						array_index ++;
					}
					while ((array_index < num_lcid_with_data) && (array_index < maxLC_ID));
				}
			}
		}
	}

	// Check whether a regular BSR can be triggered according to the first cases in 38.321
	if(num_lcid_with_data)
	{
		printf("[UE %d] PDCCH Tick at frame %d subframe %d: NumLCID with data=%d Reordered LCID0=%d LCID1=%d LCID2=%d\n",
					module_idP, tx_frameP, tx_subframeP, num_lcid_with_data, lcid_reordered_array[0], lcid_reordered_array[1],
					lcid_reordered_array[2]);

		for(array_index = 0; array_index < num_lcid_with_data; array_index++)
		{
			lcid = lcid_reordered_array[array_index];

			/* UL data, for a logical channel which belongs to a LCG, becomes available for transmission in the RLC entity
			either the data belongs to a logical channel with higher priority than the priorities of the logical channels
			which belong to any LCG and for which data is already available for transmission
			*/
			if ((ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[lcid] == 0)
			/* or there is no data available for any of the logical channels which belong to a LCG */
			|| (lcgid_buffer_remain[ue_mac_inst[module_idP].scheduling_info.LCGID[lcid]] == 0))
			{
				bsr_regular_triggered = TRUE;
				printf("[UE %d] PDCCH Tick : MAC BSR Triggered LCID%d LCGID%d data become available at frame %d subframe %d\n",
				module_idP, lcid,	ue_mac_inst[module_idP].scheduling_info.LCGID[lcid], tx_frameP, tx_subframeP);

				break;
			}
		}

		// Trigger Regular BSR if ReTxBSR Timer has expired and UE has data for transmission
		if (ue_mac_inst[module_idP].scheduling_info.retxBSR_SF == 0)
		{
			bsr_regular_triggered = TRUE;

			if ((ue_mac_inst[module_idP].BSR_reporting_active & BSR_TRIGGER_REGULAR) == 0)
			{
				printf("[UE %d] PDCCH Tick : MAC BSR Triggered ReTxBSR Timer expiry at frame %d subframe %d\n",
						module_idP, tx_frameP, tx_subframeP);
			}
		}
	}

	//Store Buffer Occupancy in remain buffers for next TTI
	for (lcid = UL_SCH_LCID_SRB1; lcid < maxLC_ID; lcid++)
	{
		ue_mac_inst[module_idP].scheduling_info.LCID_buffer_remain[lcid] = lcid_bytes_in_buffer[lcid];
	}

	return bsr_regular_triggered;
}

uint8_t locate_BsrIndexByBufferSize(const uint32_t* table, int size, int value)
{
	uint8_t ju, jm, jl;
	int ascend;

	DevAssert(size > 0);

	if (value <= 0 || value >= 6000000) {
		return 0;		//elseif (value > 150000) return 63;
	}

	jl = 0;			// lower bound
	ju = size - 1;		// upper bound
	ascend = (table[ju] >= table[jl]) ? 1 : 0;	// determine the order of the the table:  1 if ascending order of table, 0 otherwise

	while (ju - jl > 1) {	//If we are not yet done,
		jm = (ju + jl) >> 1;	//compute a midpoint,

		if ((value >= table[jm]) == ascend) {
			jl = jm;		// replace the lower limit
		} else {
			ju = jm;		//replace the upper limit
		}

		printf("[UE] searching BSR index %d for (BSR TABLE %d < value %d)\n", jm, table[jm], value);
	}

	if (value == table[jl]) {
		return jl;
	} else {
		return jl + 1;		//equally  ju
	}
}



int get_sf_periodicBSRTimer(uint8_t sf_offset)
{
	switch (sf_offset) {
	case BSR_Config__periodicBSR_Timer_sf1:
		return 5;
		break;
	case BSR_Config__periodicBSR_Timer_sf5:
		return 5;
		break;
	case BSR_Config__periodicBSR_Timer_sf10:
		return 10;
		break;
	case BSR_Config__periodicBSR_Timer_sf16:
		return 16;
		break;
	case BSR_Config__periodicBSR_Timer_sf20:
		return 20;
		break;
	case BSR_Config__periodicBSR_Timer_sf32:
		return 32;
		break;
	case BSR_Config__periodicBSR_Timer_sf40:
		return 40;
		break;
	case BSR_Config__periodicBSR_Timer_sf64:
		return 64;
		break;
	case BSR_Config__periodicBSR_Timer_sf80:
		return 80;
		break;
	case BSR_Config__periodicBSR_Timer_sf128:
		return 128;
		break;
	case BSR_Config__periodicBSR_Timer_sf160:
		return 160;
		break;
	case BSR_Config__periodicBSR_Timer_sf320:
		return 320;
		break;
	case BSR_Config__periodicBSR_Timer_sf640:
		return 640;
		break;
	case BSR_Config__periodicBSR_Timer_sf1280:
		return 1280;
		break;
	case BSR_Config__periodicBSR_Timer_sf2560:
		return 2560;
		break;
	case BSR_Config__periodicBSR_Timer_infinity:
		default:
		return 0xFFFF;
		break;
	}
}

int get_sf_retxBSRTimer(uint8_t sf_offset)
{
	switch (sf_offset) {
	case BSR_Config__retxBSR_Timer_sf10:
		return 10;
		break;
	case BSR_Config__retxBSR_Timer_sf20:
		return 20;
		break;
	case BSR_Config__retxBSR_Timer_sf40:
		return 40;
		break;
	case BSR_Config__retxBSR_Timer_sf80:
		return 80;
		break;
	case BSR_Config__retxBSR_Timer_sf160:
		return 160;
		break;
	case BSR_Config__retxBSR_Timer_sf320:
		return 320;
		break;
	case BSR_Config__retxBSR_Timer_sf640:
		return 640;
		break;
	case BSR_Config__retxBSR_Timer_sf1280:
		return 1280;
		break;
	case BSR_Config__retxBSR_Timer_sf2560:
		return 2560;
		break;
	case BSR_Config__retxBSR_Timer_sf5120:
		return 5120;
		break;
	case BSR_Config__retxBSR_Timer_sf10240:
		return 10240;
		break;
	default:
		return -1;
		break;
	}
}

int get_ms_bucketsizeduration(uint8_t bucketsizeduration)
{
	switch (bucketsizeduration) {
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms5:
		return 5;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms10:
		return 10;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms20:
		return 20;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms50:
		return 50;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms100:
		return	100;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms150:
		return	150;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms300:
		return	300;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms500:
		return	500;
		break;
	case LogicalChannelConfig__ul_SpecificParameters__bucketSizeDuration_ms1000:
		return	1000;
		break;
	default:
		return 0;
		break;
	}
}

int get_sf_perioidicPHR_Timer(uint8_t perioidicPHR_Timer)
{
	return (perioidicPHR_Timer + 1) * 10;
}


int get_sf_prohibitPHR_Timer(uint8_t prohibitPHR_Timer)
{
	return (prohibitPHR_Timer) * 10;
}
