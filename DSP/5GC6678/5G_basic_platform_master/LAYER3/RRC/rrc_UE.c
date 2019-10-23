#define RRC_UE
#define RRC_UE_C

#include "rrc_list.h"
#include "rrc_defs.h"
#include "rrc_proto.h"
#include "rrc_vars.h"
#include "LAYER2/MAC/mac_proto.h"

#include "DL-DCCH-Message.h"     //asn_DEF_DL_DCCH_Message
#include "BCCH-BCH-Message.h"    //asn_DEF_BCCH_BCH_Message
#include "CellGroupConfig.h"     //asn_DEF_CellGroupConfig
#include "BWP-Downlink.h"        //asn_DEF_BWP_Downlink
#include "RRCReconfiguration-IEs.h"


UE_RRC_INST *UE_rrc_inst;



// from LTE-RRC DL-DCCH RRCConnectionReconfiguration nr-secondary-cell-group-config (encoded)
int8_t rrc_ue_decode_secondary_cellgroup_config(const uint8_t *buffer, const uint32_t size)
{
	CellGroupConfig_t *cell_group_config = NULL;
	uint32_t i;

	asn_dec_rval_t dec_rval = uper_decode_complete(NULL,
															&asn_DEF_CellGroupConfig,
															(void **)&cell_group_config,
															(uint8_t *)buffer,
															size );

	if ((dec_rval.code != RC_OK) && (dec_rval.consumed == 0)) {
		printf("CellGroupConfig decode error\n");

		for (i=0; i<size; i++){
			printf("%02x ",buffer[i]);
		}
		printf("\n");

		// free the memory
		SEQUENCE_free(&asn_DEF_CellGroupConfig, (void *)cell_group_config, 1);
		return -1;
	}

	if(ue_rrc_inst->cell_group_config == NULL){
		ue_rrc_inst->cell_group_config = cell_group_config;
		rrc_ue_process_scg_config(cell_group_config);
	} else {
		rrc_ue_process_scg_config(cell_group_config);
		SEQUENCE_free(&asn_DEF_CellGroupConfig, (void *)cell_group_config, 0);
	}

	//rrc_mac_config_req_ue( module_id_t module_id, int CC_id, uint8_t gNB_index, MIB_t *mibP, MAC_CellGroupConfig_t *mac_cell_group_configP, PhysicalCellGroupConfig_t *phy_cell_group_configP, SpCellConfig_t *spcell_configP );

	return 0;
}


// from LTE-RRC DL-DCCH RRCConnectionReconfiguration nr-secondary-cell-group-config (decoded)
// RRCReconfiguration
int8_t rrc_ue_process_rrcReconfiguration(RRCReconfiguration_t *rrcReconfiguration)
{
#if 0
	switch(rrcReconfiguration->criticalExtensions.present) {
	case RRCReconfiguration__criticalExtensions_PR_rrcReconfiguration:
		if(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->radioBearerConfig != NULL) {
			if(ue_rrc_inst->radio_bearer_config == NULL) {
				ue_rrc_inst->radio_bearer_config = rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->radioBearerConfig;
			} else {
				rrc_ue_process_radio_bearer_config(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->radioBearerConfig);
			}
		}

		if(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->secondaryCellGroup != NULL) {
			CellGroupConfig_t *cellGroupConfig = NULL;
			uper_decode(NULL,
							&asn_DEF_CellGroupConfig,   //might be added prefix later
							(void **)&cellGroupConfig,
							(uint8_t *)rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->secondaryCellGroup->buf,
							rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->secondaryCellGroup->size, 0, 0);

			if(ue_rrc_inst->cell_group_config == NULL) {
				//  first time receive the configuration, just use the memory allocated from uper_decoder. TODO this is not good implementation, need to maintain RRC_INST own structure every time.
				ue_rrc_inst->cell_group_config = cellGroupConfig;
				rrc_ue_process_scg_config(cellGroupConfig);
			}else{
				//  after first time, update it and free the memory after.
				rrc_ue_process_scg_config(cellGroupConfig);
				SEQUENCE_free(&asn_DEF_CellGroupConfig, (void *)cellGroupConfig, 0);
			}
		}

		if(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->measConfig != NULL) {
			if(ue_rrc_inst->meas_config == NULL) {
				ue_rrc_inst->meas_config = rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->measConfig;
			} else {
				//  if some element need to be updated
				rrc_ue_process_meas_config(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->measConfig);
			}
		}

		if(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->lateNonCriticalExtension != NULL){
		//  unuse now
		}

		if(rrcReconfiguration->criticalExtensions.choice.rrcReconfiguration->nonCriticalExtension != NULL){
		// unuse now
		}
		break;
	case RRCReconfiguration__criticalExtensions_PR_NOTHING:
	case RRCReconfiguration__criticalExtensions_PR_criticalExtensionsFuture:
	default:
		break;
	}
	//rrc_mac_config_req_ue();
#endif
	return 0;
}

int8_t rrc_ue_process_meas_config(MeasConfig_t *meas_config)
{
    return 0;
}

int8_t rrc_ue_process_scg_config(CellGroupConfig_t *cell_group_config)
{
	int i;
	if(ue_rrc_inst->cell_group_config==NULL) {
		//  initial list

		if(cell_group_config->spCellConfig != NULL) {
			if(cell_group_config->spCellConfig->spCellConfigDedicated != NULL) {
				if(cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToAddModList != NULL) {
					for(i=0; i<cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToAddModList->list.count; ++i) {
						RRC_LIST_MOD_ADD(ue_rrc_inst->BWP_Downlink_list, cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToAddModList->list.array[i], bwp_Id);
					}
				}
			}
		}
	} else {
	//  maintain list
		if(cell_group_config->spCellConfig != NULL) {
			if(cell_group_config->spCellConfig->spCellConfigDedicated != NULL) {
				//  process element of list to be add by RRC message
				if(cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToAddModList != NULL) {
					for(i=0; i<cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToAddModList->list.count; ++i) {
						RRC_LIST_MOD_ADD(ue_rrc_inst->BWP_Downlink_list, cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToAddModList->list.array[i], bwp_Id);
					}
				}

				//  process element of list to be release by RRC message
				if(cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToReleaseList != NULL) {
					for(i=0; i<cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToReleaseList->list.count; ++i) {
						BWP_Downlink_t *freeP = NULL;
						RRC_LIST_MOD_REL(ue_rrc_inst->BWP_Downlink_list, bwp_Id, *cell_group_config->spCellConfig->spCellConfigDedicated->downlinkBWP_ToReleaseList->list.array[i], freeP);

						if(freeP != NULL){
							SEQUENCE_free(&asn_DEF_BWP_Downlink, (void *)freeP, 0);
						}
					}
				}
			}
		}
	}

	return 0;
}

int8_t rrc_ue_process_radio_bearer_config(RadioBearerConfig_t *radio_bearer_config)
{
	return 0;
}


int8_t rrc_top_init_ue_nr(void)
{
	if(NB_UE_INST > 0) {
		ue_rrc_inst = (NR_UE_RRC_INST_t *)malloc(NB_UE_INST * sizeof(NR_UE_RRC_INST_t));
		memset(ue_rrc_inst, 0, NB_UE_INST * sizeof(NR_UE_RRC_INST_t));

		// fill UE-NR-Capability @ UE-CapabilityRAT-Container here.

		//  init RRC lists
		RRC_LIST_INIT(ue_rrc_inst->RLC_Bearer_Config_list, maxLC_ID);
		RRC_LIST_INIT(ue_rrc_inst->SchedulingRequest_list, maxNrofSR_ConfigPerCellGroup);
		RRC_LIST_INIT(ue_rrc_inst->TAG_list, maxNrofTAGs);
		RRC_LIST_INIT(ue_rrc_inst->TDD_UL_DL_SlotConfig_list, maxNrofSlots);
		RRC_LIST_INIT(ue_rrc_inst->BWP_Downlink_list, maxNrofBWPs);
		RRC_LIST_INIT(ue_rrc_inst->ControlResourceSet_list[0], 3);   //  for init-dl-bwp
		RRC_LIST_INIT(ue_rrc_inst->ControlResourceSet_list[1], 3);   //  for dl-bwp id=0
		RRC_LIST_INIT(ue_rrc_inst->ControlResourceSet_list[2], 3);   //  for dl-bwp id=1
		RRC_LIST_INIT(ue_rrc_inst->ControlResourceSet_list[3], 3);   //  for dl-bwp id=2
		RRC_LIST_INIT(ue_rrc_inst->ControlResourceSet_list[4], 3);   //  for dl-bwp id=3
		RRC_LIST_INIT(ue_rrc_inst->SearchSpace_list[0], 10);
		RRC_LIST_INIT(ue_rrc_inst->SearchSpace_list[1], 10);
		RRC_LIST_INIT(ue_rrc_inst->SearchSpace_list[2], 10);
		RRC_LIST_INIT(ue_rrc_inst->SearchSpace_list[3], 10);
		RRC_LIST_INIT(ue_rrc_inst->SearchSpace_list[4], 10);
		RRC_LIST_INIT(ue_rrc_inst->SlotFormatCombinationsPerCell_list[0], maxNrofAggregatedCellsPerCellGroup);
		RRC_LIST_INIT(ue_rrc_inst->SlotFormatCombinationsPerCell_list[1], maxNrofAggregatedCellsPerCellGroup);
		RRC_LIST_INIT(ue_rrc_inst->SlotFormatCombinationsPerCell_list[2], maxNrofAggregatedCellsPerCellGroup);
		RRC_LIST_INIT(ue_rrc_inst->SlotFormatCombinationsPerCell_list[3], maxNrofAggregatedCellsPerCellGroup);
		RRC_LIST_INIT(ue_rrc_inst->SlotFormatCombinationsPerCell_list[4], maxNrofAggregatedCellsPerCellGroup);
		RRC_LIST_INIT(ue_rrc_inst->TCI_State_list[0], maxNrofTCI_States);
		RRC_LIST_INIT(ue_rrc_inst->TCI_State_list[1], maxNrofTCI_States);
		RRC_LIST_INIT(ue_rrc_inst->TCI_State_list[2], maxNrofTCI_States);
		RRC_LIST_INIT(ue_rrc_inst->TCI_State_list[3], maxNrofTCI_States);
		RRC_LIST_INIT(ue_rrc_inst->TCI_State_list[4], maxNrofTCI_States);
		RRC_LIST_INIT(ue_rrc_inst->RateMatchPattern_list[0], maxNrofRateMatchPatterns);
		RRC_LIST_INIT(ue_rrc_inst->RateMatchPattern_list[1], maxNrofRateMatchPatterns);
		RRC_LIST_INIT(ue_rrc_inst->RateMatchPattern_list[2], maxNrofRateMatchPatterns);
		RRC_LIST_INIT(ue_rrc_inst->RateMatchPattern_list[3], maxNrofRateMatchPatterns);
		RRC_LIST_INIT(ue_rrc_inst->RateMatchPattern_list[4], maxNrofRateMatchPatterns);
		RRC_LIST_INIT(ue_rrc_inst->ZP_CSI_RS_Resource_list[0], maxNrofZP_CSI_RS_Resources);
		RRC_LIST_INIT(ue_rrc_inst->ZP_CSI_RS_Resource_list[1], maxNrofZP_CSI_RS_Resources);
		RRC_LIST_INIT(ue_rrc_inst->ZP_CSI_RS_Resource_list[2], maxNrofZP_CSI_RS_Resources);
		RRC_LIST_INIT(ue_rrc_inst->ZP_CSI_RS_Resource_list[3], maxNrofZP_CSI_RS_Resources);
		RRC_LIST_INIT(ue_rrc_inst->ZP_CSI_RS_Resource_list[4], maxNrofZP_CSI_RS_Resources);
		RRC_LIST_INIT(ue_rrc_inst->Aperidic_ZP_CSI_RS_ResourceSet_list[0], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->Aperidic_ZP_CSI_RS_ResourceSet_list[1], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->Aperidic_ZP_CSI_RS_ResourceSet_list[2], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->Aperidic_ZP_CSI_RS_ResourceSet_list[3], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->Aperidic_ZP_CSI_RS_ResourceSet_list[4], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->SP_ZP_CSI_RS_ResourceSet_list[0], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->SP_ZP_CSI_RS_ResourceSet_list[1], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->SP_ZP_CSI_RS_ResourceSet_list[2], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->SP_ZP_CSI_RS_ResourceSet_list[3], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->SP_ZP_CSI_RS_ResourceSet_list[4], maxNrofZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->NZP_CSI_RS_Resource_list, maxNrofNZP_CSI_RS_Resources);
		RRC_LIST_INIT(ue_rrc_inst->NZP_CSI_RS_ResourceSet_list, maxNrofNZP_CSI_RS_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->CSI_IM_Resource_list, maxNrofCSI_IM_Resources);
		RRC_LIST_INIT(ue_rrc_inst->CSI_IM_ResourceSet_list, maxNrofCSI_IM_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->CSI_SSB_ResourceSet_list, maxNrofCSI_SSB_ResourceSets);
		RRC_LIST_INIT(ue_rrc_inst->CSI_ResourceConfig_list, maxNrofCSI_ResourceConfigurations);
		RRC_LIST_INIT(ue_rrc_inst->CSI_ReportConfig_list, maxNrofCSI_ReportConfigurations);
	} else {
		ue_rrc_inst = NULL;
	}

	return 0;
}


int8_t ue_process_rlc_bearer_list(CellGroupConfig_t *cell_group_config)
{
	return 0;
}

int8_t ue_process_secondary_cell_list(CellGroupConfig_t *cell_group_config)
{
	return 0;
}

int8_t ue_process_mac_cell_group_config(MAC_CellGroupConfig_t *mac_cell_group_config)
{
	return 0;
}

int8_t ue_process_physical_cell_group_config(PhysicalCellGroupConfig_t *phy_cell_group_config)
{
	return 0;
}

int8_t ue_process_spcell_config(SpCellConfig_t *spcell_config)
{
	return 0;
}

/*brief decode BCCH-BCH (MIB) message*/
int8_t rrc_ue_decode_BCCH_BCH_Message(const module_id_t module_id,
											const uint8_t     gNB_index,
											uint8_t           *const bufferP,
											const uint8_t     buffer_len )
{
	int i;
	BCCH_BCH_Message_t *bcch_message = NULL;
	MIB_t *mib = ue_rrc_inst->mib;

	if(mib != NULL) {
		SEQUENCE_free(&asn_DEF_BCCH_BCH_Message, (void *)mib, 1);
	}


	for(i=0; i<buffer_len; ++i) {
		printf("[RRC] MIB PDU : %d\n", bufferP[i]);
	}

	asn_dec_rval_t dec_rval = uper_decode_complete(NULL,
												&asn_DEF_BCCH_BCH_Message,
												(void **)&bcch_message,
												(const void *)bufferP,
												buffer_len );

	if ((dec_rval.code != RC_OK) || (dec_rval.consumed == 0)) {
		printf("BCCH_BCH decode error\n");

		for (i=0; i<buffer_len; i++){
			printf("%02x ",bufferP[i]);
		}
		printf("\n");
		// free the memory
		SEQUENCE_free(&asn_DEF_BCCH_BCH_Message, (void *)bcch_message, 1);
		return -1;
	} else {
//		link to rrc instance
		mib = &(bcch_message->message.choice.mib);
		//memcpy( (void *)mib,
		//    (void *)&bcch_message->message.choice.mib,
		//    sizeof(MIB_t) );

		rrc_mac_config_req_ue(0, 0, 0, mib, NULL, NULL, NULL);
	}

	return 0;
}


// from NR SRB3
int8_t rrc_ue_decode_DL_DCCH_Message(const module_id_t module_id,
											const uint8_t     gNB_index,
											const uint8_t    *bufferP,
											const uint32_t    buffer_len )
{
    //  uper_decode by nr R15 rrc_connection_reconfiguration
    
    int32_t i;
    DL_DCCH_Message_t *dl_dcch_msg = NULL;

    asn_dec_rval_t dec_rval = uper_decode(NULL,
                                            &asn_DEF_DL_DCCH_Message,
                                            (void**)&dl_dcch_msg,
                                            (uint8_t *)bufferP,
                                            buffer_len, 0, 0);

    if ((dec_rval.code != RC_OK) || (dec_rval.consumed == 0)) {

        for (i=0; i<buffer_len; i++)
            printf("%02x ",bufferP[i]);

        printf("\n");
        // free the memory
        SEQUENCE_free(&asn_DEF_DL_DCCH_Message, (void *)dl_dcch_msg, 1);
        return -1;
    }

    if(dl_dcch_msg != NULL){
        switch(dl_dcch_msg->message.present){
            case DL_DCCH_MessageType_PR_c1:

                switch(dl_dcch_msg->message.choice.c1.present){
                    case DL_DCCH_MessageType__c1_PR_rrcReconfiguration:
                        rrc_ue_process_rrcReconfiguration(&(dl_dcch_msg->message.choice.c1.choice.rrcReconfiguration));
                        break;

                    case DL_DCCH_MessageType__c1_PR_NOTHING:
//#if (RRC_VERSION >= MAKE_VERSION(15, 3, 0))
#if 1
                    case DL_DCCH_MessageType__c1_PR_rrcResume:
                    case DL_DCCH_MessageType__c1_PR_rrcRelease:
                    case DL_DCCH_MessageType__c1_PR_rrcReestablishment:
                    case DL_DCCH_MessageType__c1_PR_securityModeCommand:
                    case DL_DCCH_MessageType__c1_PR_dlInformationTransfer:
                    case DL_DCCH_MessageType__c1_PR_ueCapabilityEnquiry:
                    case DL_DCCH_MessageType__c1_PR_counterCheck:
                    case DL_DCCH_MessageType__c1_PR_mobilityFromNRCommand:
#else
                    case DL_DCCH_MessageType__c1_PR_spare15:
                    case DL_DCCH_MessageType__c1_PR_spare14:
                    case DL_DCCH_MessageType__c1_PR_spare13:
                    case DL_DCCH_MessageType__c1_PR_spare12:
                    case DL_DCCH_MessageType__c1_PR_spare11:
                    case DL_DCCH_MessageType__c1_PR_spare10:
                    case DL_DCCH_MessageType__c1_PR_spare9:
                    case DL_DCCH_MessageType__c1_PR_spare8:
#endif
                    case DL_DCCH_MessageType__c1_PR_spare7:
                    case DL_DCCH_MessageType__c1_PR_spare6:
                    case DL_DCCH_MessageType__c1_PR_spare5:
                    case DL_DCCH_MessageType__c1_PR_spare4:
                    case DL_DCCH_MessageType__c1_PR_spare3:
                    case DL_DCCH_MessageType__c1_PR_spare2:
                    case DL_DCCH_MessageType__c1_PR_spare1:
                    default:
                        //  not support or unuse
                        break;
                }   
                break;
            case DL_DCCH_MessageType_PR_NOTHING:
            case DL_DCCH_MessageType_PR_messageClassExtension:
            default:
                //  not support or unuse
                break;
        }
        
        //  release memory allocation
        SEQUENCE_free(&asn_DEF_DL_DCCH_Message, (void *)dl_dcch_msg, 1);
    }else{
        //  log..
    }

    return 0;

}
