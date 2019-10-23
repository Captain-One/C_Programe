#include "mac_defs.h"
#include "mac_proto.h"
#include "mac_extern.h"

#include "MAC-CellGroupConfig.h"
#include "SetupRelease.h"



/* sec 5.12, 38.321 v15.5.0: MAC Reset Procedure */
void ue_mac_reset(module_id_t module_idP, uint8_t eNB_index)
{
//	Resetting Bj
	ue_mac_inst[module_idP].scheduling_info.Bj[0] = 0;
	ue_mac_inst[module_idP].scheduling_info.Bj[1] = 0;
	ue_mac_inst[module_idP].scheduling_info.Bj[2] = 0;
//	Stopping all timers
//	timeAlignmentTimer expires
//	PHY changes for UE MAC reset


//	phy_reset_ue(module_idP, 0, eNB_index); // TODO fixed me，调用物理层复位函数

//	notify RRC to relase PUCCH/SRS
//	cancel all pending SRs
	ue_mac_inst[module_idP].scheduling_info.SR_pending = 0;
	ue_mac_inst[module_idP].scheduling_info.SR_COUNTER = 0;
//	Set BSR Trigger Bmp and remove timer flags
	ue_mac_inst[module_idP].BSR_reporting_active = BSR_TRIGGER_NONE;
//	stop ongoing RACH procedure
//	discard explicitly signaled ra_PreambleIndex and ra_RACH_MaskIndex, if any
//	ue_mac_inst[module_idP].RA_prach_resources.ra_PreambleIndex = 0;  // check!
//	ue_mac_inst[module_idP].RA_prach_resources.ra_RACH_MaskIndex = 0;
	ue_init_mac(module_idP);  //This will hopefully do the rest of the MAC reset procedure
}

int rrc_mac_config_req_ue(module_id_t                     module_id,
								int                             cc_idP,
								uint8_t                         gNB_index,
								MIB_t                        *mibP,
								MAC_CellGroupConfig_t        *mac_cell_group_configP,
								PhysicalCellGroupConfig_t    *phy_cell_group_configP,
								SpCellConfig_t               *spcell_configP )
{
	NR_UE_MAC_INST_t *mac = get_mac_inst(module_id);

//	NR_ServingCellConfig_t *serving_cell_config = spcell_configP->spCellConfigDedicated;
//	TODO do something FAPI-like P5 L1/L2 config interface in config_si, config_mib, etc.

	if(mibP != NULL) {
		mac->mib = mibP;    //  update by every reception
	}

	if(mac_cell_group_configP != NULL) {
		if(mac_cell_group_configP->drx_Config != NULL) {
			switch(((SetupRelease_1073P22_t*)(mac_cell_group_configP->drx_Config))->present) {
			case SetupRelease_1073P22_PR_NOTHING:
				break;
			case SetupRelease_1073P22_PR_release:
				mac->drx_Config = NULL;
				break;
			case SetupRelease_1073P22_PR_setup:
				mac->drx_Config = ((SetupRelease_1073P22_t*)(mac_cell_group_configP->drx_Config))->choice.setup;
				break;
			default:
				break;
			}
		}

		if(mac_cell_group_configP->schedulingRequestConfig != NULL) {
			mac->schedulingRequestConfig = mac_cell_group_configP->schedulingRequestConfig;
		}

		if(mac_cell_group_configP->bsr_Config != NULL) {
			mac->bsr_Config = mac_cell_group_configP->bsr_Config;
		}

		if(mac_cell_group_configP->tag_Config != NULL) {
			mac->tag_Config = mac_cell_group_configP->tag_Config;
		}

		if(mac_cell_group_configP->phr_Config != NULL) {
			switch(((SetupRelease_1073P23_t*)mac_cell_group_configP->phr_Config)->present) {
			case SetupRelease_1073P23_PR_NOTHING:
				break;
			case SetupRelease_1073P23_PR_release:
				mac->phr_Config = NULL;
				break;
			case SetupRelease_1073P23_PR_setup:
				mac->phr_Config = ((SetupRelease_1073P23_t*)mac_cell_group_configP->phr_Config)->choice.setup;
				break;
			default:
				break;
			}
		}

		if(phy_cell_group_configP->cs_RNTI != NULL) {
			switch(((SetupRelease_1073P38_t*)phy_cell_group_configP->cs_RNTI)->present) {
			case SetupRelease_1073P38_PR_NOTHING:
				break;
			case SetupRelease_1073P38_PR_release:
				mac->cs_RNTI = NULL;
				break;
			case SetupRelease_1073P38_PR_setup:
				mac->cs_RNTI = ((SetupRelease_1073P38_t*)phy_cell_group_configP->cs_RNTI)->choice.setup;
				break;
			default:
				break;
			}
		}
	}
	
	if(phy_cell_group_configP != NULL) {
//		config_phy(phy_cell_group_config, NULL);
	}

//  TODO check
#if 0
	if(serving_cell_config_configP != NULL ) {
//		config_phy(NULL, spcell_config);
		mac->servCellIndex = spcell_config->servCellIndex;
	}


	if(serving_cell_config != NULL ){
		if(serving_cell_config->tdd_UL_DL_ConfigurationDedicated != NULL) {
			mac->tdd_UL_DL_ConfigurationDedicated = serving_cell_config->tdd_UL_DL_ConfigurationDedicated;
		}

		if(spcell_config->initialDownlinkBWP != NULL) {
			mac->init_DL_BWP = spcell_config->initialDownlinkBWP;
		}

//		storage list of DL BWP config. TODO should be modify to maintain(add/release) a list inside MAC instance, this implementation just use for one-shot RRC configuration setting.
		if(spcell_config->downlinkBWP_ToAddModList != NULL) {
			mac->BWP_Downlink_list = spcell_config->downlinkBWP_ToAddModList->list;
			mac->BWP_Downlink_count = spcell_config->downlinkBWP_ToAddModList->count;
		}

		if(spcell_config->bwp_InactivityTimer != NULL) {
			mac->bwp_InactivityTimer = spcell_config->bwp_InactivityTimer;
		}

		if(spcell_config->defaultDownlinkBWP_Id != NULL) {
			mac->defaultDownlinkBWP_Id = spcell_config->defaultDownlinkBWP_Id;
		}

		if(spcell_config->pdsch_ServingCellConfig != NULL) {
			mac->pdsch_ServingCellConfig = spcell_config->pdsch_ServingCellConfig;
		}

		if(spcell_config->csi_MeasConfig != NULL) {
			mac->csi_MeasConfig = spcell_config->csi_MeasConfig;
		}

		spcell_config->tag_Id = spcell_config.tag_Id;
	}
#endif
//	scell config not yet

    return 0;
}
