#ifndef __LAYER2_MAC_PROTO_H__
#define __LAYER2_MAC_PROTO_H__

#include "mac.h"
#include "mac_defs.h"


/** \addtogroup _mac
 *  @{
 */

/** \brief Function for UE/PHY to compute PUSCH transmit power in power-control procedure.
    @param Mod_id Module id of UE
    @returns Po_NOMINAL_PUSCH (PREAMBLE_RECEIVED_TARGET_POWER+DELTA_PREAMBLE
*/
int8_t get_Po_NOMINAL_PUSCH(module_id_t module_idP, uint8_t CC_id);

/** \brief Function to compute DELTA_PREAMBLE from 38.321 ch 7.3 (for RA power ramping procedure and Msg3 PUSCH power control policy)
    @param Mod_id Module id of UE
    @returns DELTA_PREAMBLE
*/
int8_t get_DELTA_PREAMBLE(module_id_t module_idP, int CC_id);

/** \brief Function for compute deltaP_rampup from 38.321 (for RA power ramping procedure and Msg3 PUSCH power control policy)
    @param Mod_id Module id of UE
    @param CC_id carrier component id of UE
    @returns deltaP_rampup
*/
int8_t get_deltaP_rampup(module_id_t module_idP, uint8_t CC_id);

//uint16_t mac_computeRIV(uint16_t N_RB_DL, uint16_t RBstart, uint16_t Lcrbs);

//main.c

//void init_UE_list(UE_list_t *UE_list);

char layer2_init_UE(module_id_t module_idP);

//int mac_init_global_param(void);

//void mac_top_cleanup(void);

void mac_UE_out_of_sync_ind(module_id_t module_idP, frame_t frameP, uint16_t eNB_index);

void ue_mac_reset(module_id_t module_idP, uint8_t eNB_index);

void ue_init_mac(module_id_t module_idP);

int find_UE_id(module_id_t module_idP, rnti_t rnti);
int find_RA_id(module_id_t mod_idP, int CC_idP, rnti_t rntiP);

uint8_t get_aggregation(uint8_t bw_index, uint8_t cqi, uint8_t dci_fmt);

/* \brief Get SR payload (0,1) from UE MAC
@param Mod_id Instance id of UE in machine
@param CC_id Component Carrier index
@param eNB_id Index of eNB that UE is attached to
@param rnti C_RNTI of UE
@param subframe subframe number
@returns 0 for no SR, 1 for SR
*/
uint32_t ue_get_SR(module_id_t module_idP, int CC_id, frame_t frameP, uint8_t eNB_id, rnti_t rnti, sub_frame_t subframe);

// UE functions
void mac_out_of_sync_ind(module_id_t module_idP, frame_t frameP, uint16_t CH_index);

void ue_decode_si(module_id_t module_idP, int CC_id, frame_t frame, uint8_t CH_index, void *pdu, uint16_t len);

void ue_decode_p(module_id_t module_idP, int CC_id, frame_t frame, uint8_t CH_index, void *pdu, uint16_t len);

void ue_send_sdu(module_id_t module_idP, uint8_t CC_id, frame_t frame, sub_frame_t subframe, uint8_t * sdu, uint16_t sdu_len,
					uint8_t CH_index);

/* \brief Called by PHY to get sdu for PUSCH transmission.  It performs the following operations: Checks BSR for DCCH, DCCH1 and DTCH corresponding to previous values computed either in SR or BSR procedures.  It gets rlc status indications on DCCH,DCCH1 and DTCH and forms BSR elements and PHR in MAC header.  CRNTI element is not supported yet.  It computes transport block for up to 3 SDUs and generates header and forms the complete MAC SDU.
@param Mod_id Instance id of UE in machine
@param eNB_id Index of eNB that UE is attached to
@param rnti C_RNTI of UE
@param subframe subframe number
*/
void ue_get_sdu(module_id_t module_idP, int CC_id, frame_t frameP,
					sub_frame_t subframe, uint8_t eNB_index,
					uint8_t * ulsch_buffer, uint16_t buflen,
					uint8_t * access_mode);


/* \brief Function called by PHY to retrieve information to be transmitted using the RA procedure.  If the UE is not in PUSCH mode for a particular eNB index, this is assumed to be an Msg3 and MAC attempts to retrieves the CCCH message from RRC. If the UE is in PUSCH mode for a particular eNB index and PUCCH format 0 (Scheduling Request) is not activated, the MAC may use this resource for random-access to transmit a BSR along with the C-RNTI control element (see 5.1.4 from 38.321)
@param Mod_id Index of UE instance
@param Mod_id Component Carrier Index
@param New_Msg3 Flag to indicate this call is for a new Msg3
@param subframe Index of subframe for PRACH transmission (0 ... 9)
@returns A pointer to a PRACH_RESOURCES_t */
PRACH_RESOURCES_t *ue_get_rach(module_id_t module_idP, int CC_id, frame_t frameP, uint8_t new_Msg3, sub_frame_t subframe);

/* \brief Function called by PHY to process the received RAR.  It checks that the preamble matches what was sent by the eNB and provides the timing advance and t-CRNTI.
@param Mod_id Index of UE instance
@param CC_id Index to a component carrier
@param frame Frame index
@param ra_rnti RA_RNTI value
@param dlsch_buffer  Pointer to dlsch_buffer containing RAR PDU
@param t_crnti Pointer to PHY variable containing the T_CRNTI
@param preamble_index Preamble Index used by PHY to transmit the PRACH.  This should match the received RAR to trigger the rest of
random-access procedure
@param selected_rar_buffer the output buffer for storing the selected RAR header and RAR payload
@returns timing advance or 0xffff if preamble doesn't match
*/
uint16_t process_rar(const module_id_t module_idP,
							const int CC_id,
							const frame_t frameP,
							const sub_frame_t subframe,
							const slot_t slot,
							const rnti_t ra_rnti,
							uint8_t * const dlsch_buffer,
							rnti_t * const t_crnti,
							const uint8_t preamble_index,
							uint8_t * selected_rar_buffer);


int to_prb(int);
int to_rbg(int);
int mac_init(void);
int add_new_ue(module_id_t Mod_id, int CC_id, rnti_t rnti, int harq_pid);
int rrc_mac_remove_ue(module_id_t Mod_id, rnti_t rntiP);

void store_dlsch_buffer(module_id_t Mod_id, int slice_idx, frame_t frameP, sub_frame_t subframeP);
//void assign_rbs_required(module_id_t Mod_id, int slice_idx, frame_t frameP, sub_frame_t subframe, uint16_t nb_rbs_required[NFAPI_CC_MAX][MAX_MOBILES_PER_ENB], int min_rb_unit[NFAPI_CC_MAX]);

int maxround(module_id_t Mod_id, uint16_t rnti, int frame, sub_frame_t subframe, uint8_t ul_flag);

int UE_PCCID(module_id_t mod_idP, int ue_idP);
rnti_t UE_RNTI(module_id_t mod_idP, int ue_idP);

uint8_t find_rb_table_index(uint8_t average_rbs);

void set_ul_DAI(int module_idP, int UE_idP, int CC_idP, int frameP, int subframeP);

void ulsch_scheduler_pre_processor(module_id_t module_idP,
											int slice_idx,
											int frameP,
											sub_frame_t subframeP,
											unsigned char sched_subframeP,
											uint16_t * first_rb);

void store_ulsch_buffer(module_id_t module_idP, int frameP, sub_frame_t subframeP);

void sort_ue_ul(module_id_t module_idP, int frameP, sub_frame_t subframeP);
void assign_max_mcs_min_rb(module_id_t module_idP, int slice_idx, int frameP,
								sub_frame_t subframeP, uint16_t * first_rb);
//void adjust_bsr_info(int buffer_occupancy, uint16_t TBS,
//		     UE_TEMPLATE * UE_template);

int phy_stats_exist(module_id_t Mod_id, int rnti);
void sort_UEs(module_id_t Mod_idP, int slice_idx, int frameP, sub_frame_t subframeP);

/*! \fn  UE_L2_state_t ue_scheduler(const module_id_t module_idP,const frame_t frameP, const sub_frame_t subframe, const lte_subframe_t direction,const uint8_t eNB_index)
   \brief UE scheduler where all the ue background tasks are done.  This function performs the following:  1) Trigger PDCP every 5ms 2) Call RRC for link status return to PHY3) Perform SR/BSR procedures for scheduling feedback 4) Perform PHR procedures.
\param[in] module_idP instance of the UE
\param[in] rxFrame the RX frame number
\param[in] rxSubframe the RX subframe number
\param[in] txFrame the TX frame number
\param[in] txSubframe the TX subframe number
\param[in] direction  subframe direction
\param[in] eNB_index  instance of eNB
@returns L2 state (CONNETION_OK or CONNECTION_LOST or PHY_RESYNCH)
*/
NR_UE_L2_STATE_t ue_scheduler(const module_id_t module_idP,
								const frame_t rxFrameP,
								const sub_frame_t rxSubframe,
								const frame_t txFrameP,
								const sub_frame_t txSubframe,
								const lte_subframe_t direction,
								const uint8_t eNB_index, const int CC_id);

/*! \fn  int cba_access(module_id_t module_idP,frame_t frameP,sub_frame_t subframe, uint8_t eNB_index,uint16_t buflen);
\brief determine whether to use cba resource to transmit or not
\param[in] Mod_id instance of the UE
\param[in] frame the frame number
\param[in] subframe the subframe number
\param[in] eNB_index instance of eNB
\param[out] access(1) or postpone (0)
*/
int cba_access(module_id_t module_idP, frame_t frameP, sub_frame_t subframe, uint8_t eNB_index, uint16_t buflen);

/*! \fn  BSR_SHORT *  get_bsr_short(module_id_t module_idP, uint8_t bsr_len)
\brief get short bsr level
\param[in] Mod_id instance of the UE
\param[in] bsr_len indicator for no, short, or long bsr
\param[out] bsr_s pointer to short bsr
*/
BSR_SHORT *get_bsr_short(module_id_t module_idP, uint8_t bsr_len);

/*! \fn  BSR_LONG * get_bsr_long(module_id_t module_idP, uint8_t bsr_len)
\brief get long bsr level
\param[in] Mod_id instance of the UE
\param[in] bsr_len indicator for no, short, or long bsr
\param[out] bsr_l pointer to long bsr
*/
BSR_LONG *get_bsr_long(module_id_t module_idP, uint8_t bsr_len);


/*! \fn  int get_db_dl_PathlossChange(uint8_t dl_PathlossChange)
   \brief get the db form the path loss change configured by the higher layer
\param[in]  dl_PathlossChange path loss for PHR
\return the pathloss in db
*/
//int get_db_dl_PathlossChange(uint8_t dl_PathlossChange);

/*! \fn  uint8_t get_phr_mapping (module_id_t module_idP, int CC_id,uint8_t eNB_index)
   \brief get phr mapping as described in 38.313
\param[in]  Mod_id index of eNB
\param[in] CC_id Component Carrier Index
\return phr mapping
*/
//uint8_t get_phr_mapping(module_id_t module_idP, int CC_id,
//			uint8_t eNB_index);

/*! \fn  void update_phr (module_id_t module_idP)
   \brief update/reset the phr timers
\param[in]  Mod_id index of eNB
\param[in] CC_id Component carrier index
\return void
*/
void update_phr(module_id_t module_idP, int CC_id);

/*! \brief Function to indicate Msg3 transmission/retransmission which initiates/reset Contention Resolution Timer
\param[in] Mod_id Instance index of UE
\param[in] eNB_id Index of eNB
*/
void Msg3_tx(module_id_t module_idP, uint8_t CC_id, frame_t frameP, uint8_t eNB_id);

/*! \brief Function to indicate the transmission of msg1/rach
\param[in] Mod_id Instance index of UE
\param[in] eNB_id Index of eNB
*/

void Msg1_tx(module_id_t module_idP, uint8_t CC_id, frame_t frameP, uint8_t eNB_id);

void dl_phy_sync_success(module_id_t module_idP, frame_t frameP, unsigned char eNB_index, uint8_t first_sync);

//int dump_eNB_l2_stats(char *buffer, int length);

double uniform_rngen(int min, int max);


uint16_t mac_computeRIV(uint16_t N_RB_DL, uint16_t RBstart, uint16_t Lcrbs);

int to_rbg(int dl_Bandwidth);

int to_prb(int dl_Bandwidth);

void Msg1_transmitted(module_id_t module_idP, uint8_t CC_id, frame_t frameP, uint8_t eNB_id);
void Msg3_transmitted(module_id_t module_idP, uint8_t CC_id, frame_t frameP, uint8_t eNB_id);

uint32_t from_earfcn(int eutra_bandP, uint32_t dl_earfcn);
//int32_t get_uldl_offset(int eutra_bandP);
//int l2_init_ue(int eMBMS_active, char *uecap_xer, uint8_t cba_group_active, uint8_t HO_active);

#endif
/** @}*/
