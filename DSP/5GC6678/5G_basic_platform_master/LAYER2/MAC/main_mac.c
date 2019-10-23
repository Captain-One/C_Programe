#include "mac_defs.h"
#include "mac_proto.h"
#include "assertions.h"



NR_UE_MAC_INST_t *ue_mac_inst;

/*
void dl_phy_sync_success(module_id_t module_idP, frame_t frameP, unsigned char eNB_index, uint8_t first_sync) { //init as MR
  printf("[UE %d] Frame %d: PHY Sync to eNB_index %d successful \n",
        module_idP, frameP, eNB_index);

  if (first_sync == 1 && !(EPC_MODE_ENABLED)) {
    //layer2_init_UE(module_idP);
    rrc_ue_init(module_idP, eNB_index);
  } else {
    rrc_in_sync_ind(module_idP, frameP, eNB_index);
  }
}
*/

int rlcmac_init_global_param_ue(void)
{
	printf("[MAIN] CALLING RLC_MODULE_INIT...\n");

	if (rlc_module_init() != 0) {
		return (-1);
	}

	pdcp_layer_init();

	printf("[MAIN] Init Global Param Done\n");

	return 0;
}

int mac_top_init_ue(int eMBMS_active, char *uecap_xer, uint8_t cba_group_active, uint8_t HO_active)
{
	int i;
	printf("[MAIN] Init function start:Nb_UE_INST=%d\n", NB_NR_UE_MAC_INST);

	if (NB_NR_UE_MAC_INST > 0) {
		ue_mac_inst = (NR_UE_MAC_INST_t *)malloc(NB_NR_UE_MAC_INST * sizeof(NR_UE_MAC_INST_t));

		AssertFatal(ue_mac_inst != NULL, "[MAIN] Can't ALLOCATE %zu Bytes for %d UE_MAC_INST with size %zu \n",
		NB_NR_UE_MAC_INST * sizeof(NR_UE_MAC_INST_t), NB_NR_UE_MAC_INST, sizeof(NR_UE_MAC_INST_t));

		printf("[MAIN] ALLOCATE %zu Bytes for %d UE_MAC_INST @ %p\n", NB_NR_UE_MAC_INST * sizeof(NR_UE_MAC_INST_t), NB_NR_UE_MAC_INST, ue_mac_inst);

		bzero(ue_mac_inst, NB_NR_UE_MAC_INST * sizeof(NR_UE_MAC_INST_t));

		for (i = 0; i < NB_NR_UE_MAC_INST; i++) {
			ue_init_mac(i);
		}
	} else {
		ue_mac_inst = NULL;
	}

	printf("[MAIN] calling RRC\n");

//	TODO 需要初始化RRC
//	rrc_top_init_ue(eMBMS_active, uecap_xer, cba_group_active, HO_active);

	printf("[MAIN][INIT] Init function finished\n");

	return (0);
}

int nr_l2_init_ue(int eMBMS_active, char *uecap_xer, uint8_t cba_group_active, uint8_t HO_active)
{
	printf("[MAIN] MAC_INIT_GLOBAL_PARAM IN...\n");

	rlcmac_init_global_param_ue();

	printf("[MAIN] init UE MAC functions \n");

	mac_top_init_ue(eMBMS_active, uecap_xer, cba_group_active, HO_active); // TODO 需要增加此函数
	return (1);
}

NR_UE_MAC_INST_t *get_mac_inst(module_id_t module_id)
{
    return &ue_mac_inst[(int)module_id];
}
