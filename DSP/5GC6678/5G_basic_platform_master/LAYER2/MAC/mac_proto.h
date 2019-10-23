#ifndef __LAYER2_MAC_UE_PROTO_H__
#define __LAYER2_MAC_UE_PROTO_H__

#include "mac_defs.h"
#include "mac.h"


/**\brief decode mib pdu in NR_UE, from if_module ul_ind with P7 tx_ind message
   \param module_id      module id
   \param cc_id          component carrier id
   \param gNB_index      gNB index
   \param extra_bits     extra bits for frame calculation
   \param l_ssb_equal_64 check if ssb number of candicate is equal 64, 1=equal; 0=non equal. Reference 38.212 7.1.1
   \param pduP           pointer to pdu
   \param pdu_length     length of pdu
   \param cell_id        cell id */
int8_t nr_ue_decode_mib(module_id_t module_id,
							int cc_id,
							uint8_t gNB_index,
							uint8_t extra_bits,
							uint32_t ssb_length,
							uint32_t ssb_index,
							void *pduP,
							uint16_t cell_id );


/**\brief primitive from RRC layer to MAC layer for configuration L1/L2, now supported 4 rrc messages: MIB, cell_group_config for MAC/PHY, spcell_config(serving cell config)
   \param module_id                 module id
   \param cc_id                     component carrier id
   \param gNB_index                 gNB index
   \param mibP                      pointer to RRC message MIB
   \param mac_cell_group_configP    pointer to RRC message MAC-related in cell group config 
   \param phy_cell_group_configP    pointer to RRC message PHY-related in cell group config
   \param spcell_configP            pointer to RRC message serving cell config*/
int rrc_mac_config_req_ue(module_id_t module_id,
								int cc_id,
								uint8_t gNB_index,
								MIB_t *mibP,
								MAC_CellGroupConfig_t *mac_cell_group_configP,
								PhysicalCellGroupConfig_t *phy_cell_group_configP,
								SpCellConfig_t *spcell_configP);
   
/**\brief initialization UE MAC instance(s), total number of MAC instance based on NB_NR_UE_MAC_INST*/
int nr_l2_init_ue(int eMBMS_active, char *uecap_xer, uint8_t cba_group_active, uint8_t HO_active);

/**\brief fetch MAC instance by module_id, within 0 - (NB_NR_UE_MAC_INST-1)
   \param module_id index of MAC instance(s)*/
NR_UE_MAC_INST_t *get_mac_inst(module_id_t module_id);

/**\brief called at each slot, slot length based on numerology. now use u=0, scs=15kHz, slot=1ms
          performs BSR/SR/PHR procedures, random access procedure handler and DLSCH/ULSCH procedures.
   \param module_id     module id
   \param gNB_index     corresponding gNB index
   \param cc_id         component carrier id
   \param rx_frame      receive frame number
   \param rx_slot       receive slot number
   \param tx_frame      transmit frame number
   \param tx_slot       transmit slot number*/
NR_UE_L2_STATE_t nr_ue_scheduler(const module_id_t module_id,
										const uint8_t gNB_index,
										const int cc_id,
										const frame_t rx_frame,
										const slot_t rx_slot,
										const int32_t ssb_index,
										const frame_t tx_frame,
										const slot_t tx_slot);


/* \brief Get SR payload (0,1) from UE MAC
@param Mod_id Instance id of UE in machine
@param CC_id Component Carrier index
@param eNB_id Index of eNB that UE is attached to
@param rnti C_RNTI of UE
@param subframe subframe number
@returns 0 for no SR, 1 for SR
*/
int8_t nr_ue_get_SR(module_id_t module_idP, int CC_id, frame_t frameP, uint8_t eNB_id, uint16_t rnti, sub_frame_t subframe);

//int8_t nr_ue_process_dci(module_id_t module_id, int cc_id, uint8_t gNB_index, fapi_nr_dci_pdu_rel15_t *dci, uint16_t rnti, uint32_t dci_format);

uint32_t get_ssb_frame(uint32_t test);
uint32_t get_ssb_slot(uint32_t ssb_index);


void process_dlsch_mac_pdu(module_id_t module_idP,
								uint8_t CC_id,
								uint16_t rnti,
								const frame_t rx_frame,
								const sub_frame_t rx_subframe,
								const slot_t rx_slot,
								uint8_t *pduP,
								uint16_t mac_pdu_len);

/* \brief Called by PHY to get pdu for PUSCH transmission.  It performs the following operations: Checks BSR for DCCH, DCCH1 and DTCH corresponding to previous values computed either in SR or BSR procedures.  It gets rlc status indications on DCCH,DCCH1 and DTCH and forms BSR elements and PHR in MAC header.  CRNTI element is not supported yet.  It computes transport block for up to 3 SDUs and generates header and forms the complete MAC SDU.
@param Mod_id Instance id of UE in machine
@param eNB_id Index of eNB that UE is attached to
@param rnti C_RNTI of UE
@param subframe subframe number
*/
void generate_ulsch_mac_pdu(module_id_t module_idP,
								int CC_id,
								const frame_t frameP,
								const sub_frame_t subframe,
								const slot_t slot,
								uint8_t eNB_index,
								uint8_t* ulsch_buffer,
								uint16_t buflen,
								uint8_t* access_mode);

/*! \fn  boolean_t update_bsr(module_id_t module_idP, frame_t frameP,sub_frame_t subframeP)
   \brief get the rlc stats and update the bsr level for each lcid
\param[in] Mod_id instance of the UE
\param[in] frame Frame index
*/
boolean_t update_bsr(module_id_t module_idP, const frame_t tx_frameP, const sub_frame_t tx_subframeP, const slot_t tx_slot);

/*! \fn  locate_BsrIndexByBufferSize (int *table, int size, int value)
   \brief locate the BSR level in the table as defined in 38.321. This function requires that he values in table to be monotonic, either increasing or decreasing. The returned value is not less than 0, nor greater than n-1, where n is the size of table.
\param[in] *table Pointer to BSR table
\param[in] size Size of the table
\param[in] value Value of the buffer
\return the index in the BSR_LEVEL table
*/
uint8_t locate_BsrIndexByBufferSize(const uint32_t* table, int size, int value);



/*! \fn  int get_sf_periodicBSRTimer(uint8_t periodicBSR_Timer)
   \brief get the number of subframe from the periodic BSR timer configured by the higher layers
\param[in] periodicBSR_Timer timer for periodic BSR
\return the number of subframe
*/
int get_sf_periodicBSRTimer(uint8_t bucketSize);



/*! \fn  int get_sf_retxBSRTimer(uint8_t retxBSR_Timer)
   \brief get the number of subframe form the bucket size duration configured by the higher layer
\param[in]  retxBSR_Timer timer for regular BSR
\return the time in sf
*/
int get_sf_retxBSRTimer(uint8_t retxBSR_Timer);



/*! \fn  int get_ms_bucketsizeduration(uint8_t bucketSize)
   \brief get the time in ms form the bucket size duration configured by the higher layer
\param[in]  bucketSize the bucket size duration
\return the time in ms
*/
int get_ms_bucketsizeduration(uint8_t bucketsizeduration);



/*! \fn  int get_sf_perioidicPHR_Timer(uint8_t perioidicPHR_Timer){
   \brief get the number of subframe form the periodic PHR timer configured by the higher layer
\param[in]  perioidicPHR_Timer timer for reguluar PHR
\return the time in sf
*/
int get_sf_perioidicPHR_Timer(uint8_t perioidicPHR_Timer);


/*! \fn  int get_sf_prohibitPHR_Timer(uint8_t prohibitPHR_Timer)
   \brief get the number of subframe form the prohibit PHR duration configured by the higher layer
\param[in]  prohibitPHR_Timer timer for  PHR
\return the time in sf
*/
int get_sf_prohibitPHR_Timer(uint8_t prohibitPHR_Timer);

//int8_t nr_ue_process_dlsch(module_id_t module_id, int cc_id, uint8_t gNB_index, fapi_nr_dci_indication_t *dci_ind, void *pduP, uint32_t pdu_len);

#endif
/** @}*/
