#ifndef __NR_RRC_PROTO_H_
#define __NR_RRC_PROTO_H_


#include "rrc_defs.h"
#include "RRCReconfiguration.h"
#include "MeasConfig.h"
#include "CellGroupConfig.h"
#include "RadioBearerConfig.h"
//
//  main_rrc.c
//
/**\brief Layer 3 initialization*/
int l3_init_ue(void);

//
//  UE_rrc.c
//

/**\brief Initial the top level RRC structure instance*/
int8_t rrc_top_init_ue_nr(void);



/**\brief Decode RRC Connection Reconfiguration, sent from E-UTRA RRC Connection Reconfiguration v1510 carring EN-DC config
   \param buffer  encoded NR-RRC-Connection-Reconfiguration/Secondary-Cell-Group-Config message.
   \param size    length of buffer*/
//TODO check to use which one
//int8_t rrc_ue_decode_rrcReconfiguration(const uint8_t *buffer, const uint32_t size);
int8_t rrc_ue_decode_secondary_cellgroup_config(const uint8_t *buffer, const uint32_t size);
   

/**\brief Process NR RRC connection reconfiguration via SRB3
   \param rrcReconfiguration  decoded rrc connection reconfiguration*/
int8_t rrc_ue_process_rrcReconfiguration(RRCReconfiguration_t *rrcReconfiguration);

/**\prief Process measurement config from NR RRC connection reconfiguration message
   \param meas_config   measurement configuration*/
int8_t rrc_ue_process_meas_config(MeasConfig_t *meas_config);

/**\prief Process secondary cell group config from NR RRC connection reconfiguration message or EN-DC primitives
   \param cell_group_config   secondary cell group configuration*/
//TODO check EN-DC function call flow.
int8_t rrc_ue_process_scg_config(CellGroupConfig_t *cell_group_config);

/**\prief Process radio bearer config from NR RRC connection reconfiguration message
   \param radio_bearer_config    radio bearer configuration*/
int8_t rrc_ue_process_radio_bearer_config(RadioBearerConfig_t *radio_bearer_config);

/**\brief decode NR BCCH-BCH (MIB) message
   \param module_idP    module id
   \param gNB_index     gNB index
   \param sduP          pointer to buffer of ASN message BCCH-BCH
   \param sdu_len       length of buffer*/
int8_t rrc_ue_decode_BCCH_BCH_Message(const module_id_t module_id, const uint8_t gNB_index, uint8_t *const bufferP, const uint8_t buffer_len);

/**\brief Decode NR DCCH from gNB, sent from lower layer through SRB3
   \param module_id  module id
   \param gNB_index  gNB index
   \param buffer     encoded DCCH bytes stream message
   \param size       length of buffer*/
int8_t rrc_ue_decode_DL_DCCH_Message(const module_id_t module_id, const uint8_t gNB_index, const uint8_t *buffer, const uint32_t size);

/**\brief interface between MAC and RRC thru SRB0 (RLC TM/no PDCP)
   \param module_id  module id
   \param CC_id      component carrier id
   \param gNB_index  gNB index
   \param channel    indicator for channel of the pdu
   \param pduP       pointer to pdu
   \param pdu_len    data length of pdu*/
int8_t nr_mac_rrc_data_ind_ue(const module_id_t module_id, const int CC_id, const uint8_t gNB_index, const channel_t channel, const uint8_t* pduP, const sdu_size_t pdu_len);

/** @}*/
#endif

