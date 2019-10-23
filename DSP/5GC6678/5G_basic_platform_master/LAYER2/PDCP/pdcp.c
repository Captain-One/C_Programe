#define PDCP_C

//#define MBMS_MULTICAST_OUT

#include "assertions.h"
#include "hashtable.h"
#include "pdcp.h"
#include "pdcp_util.h"
#include "pdcp_list.h"
#include "pdcp_sequence_manager.h"
#include "LAYER2/RLC/rlc.h"
#include "LAYER2/MAC/mac_extern.h"
#include "RRC/rrc_proto.h"
#include "pdcp_primitives.h"
#include <inttypes.h>
#include "platform_constants.h"
//#include "NAS/nas_config.h"



hash_table_t  *pdcp_coll_p = NULL;


/* pdcp module parameters and related functions */
static pdcp_params_t pdcp_params= {0,NULL};

uint64_t get_pdcp_optmask(void) {
	return pdcp_params.optmask;
}
//-----------------------------------------------------------------------------
/*
 * If PDCP_UNIT_TEST is set here then data flow between PDCP and RLC is broken
 * and PDCP has no longer anything to do with RLC. In this case, after it's handed
 * an SDU it appends PDCP header and returns (by filling in incoming pointer parameters)
 * this mem_block_t to be dissected for testing purposes. For further details see test
 * code at targets/TEST/PDCP/test_pdcp.c:test_pdcp_data_req()
 */
boolean_t pdcp_data_req(
	protocol_ctxt_t  *ctxt_pP,
	const srb_flag_t     srb_flagP,
	const rb_id_t        rb_idP,
	const mui_t          muiP,
	const confirm_t      confirmP,
	const sdu_size_t     sdu_buffer_sizeP,
	unsigned char *const sdu_buffer_pP,
	const pdcp_transmission_mode_t modeP
#if 0//(RRC_VERSION <  MAKE_VERSION(15, 0, 0))
	,const uint32_t *const sourceL2Id,
	const uint32_t *const destinationL2Id
#endif
)
//-----------------------------------------------------------------------------
{
	pdcp_t            *pdcp_p          = NULL;
	uint8_t            i               = 0;
	uint8_t            pdcp_header_len = 0;
	uint8_t            pdcp_tailer_len = 0;
	uint16_t           pdcp_pdu_size   = 0;
	uint32_t           current_sn      = 0;
	mem_block_t       *pdcp_pdu_p      = NULL;
	rlc_op_status_t    rlc_status;
	boolean_t          ret             = TRUE;
	hash_key_t         key             = HASHTABLE_NOT_A_KEY_VALUE;
	hashtable_rc_t     h_rc;
	uint8_t            rb_offset = (srb_flagP == 0) ? DTCH -1 : 0;
	uint16_t           pdcp_uid = 0;


	if (sdu_buffer_sizeP == 0) {
		printf("Handed SDU is of size 0! Ignoring...\n");
		return FALSE;
	}

	/*
	* XXX MAX_IP_PACKET_SIZE is 4096, shouldn't this be MAX SDU size, which is 8188 bytes?
	*/
	AssertFatal(sdu_buffer_sizeP<= MAX_IP_PACKET_SIZE,"Requested SDU size (%d) is bigger than that can be handled by PDCP (%u)!\n",
			sdu_buffer_sizeP, MAX_IP_PACKET_SIZE);

	if (modeP == PDCP_TRANSMISSION_MODE_TRANSPARENT) {
//		AssertError (rb_idP < NB_RB_MBMS_MAX, return FALSE, "RB id is too high (%u/%d) %u %u!\n", rb_idP, NB_RB_MBMS_MAX, ctxt_pP->module_id, ctxt_pP->rnti);
	} else {
		if (srb_flagP) {
			AssertError (rb_idP < 3, return FALSE, "RB id is too high (%u/%d) %u %u!\n", rb_idP, 3, ctxt_pP->module_id, ctxt_pP->rnti);
		} else {
			AssertError (rb_idP < maxLC_ID, return FALSE, "RB id is too high (%u/%d) %u %u!\n", rb_idP, maxLC_ID, ctxt_pP->module_id, ctxt_pP->rnti);
		}
	}

	key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, rb_idP, srb_flagP);
	h_rc = hashtable_get(pdcp_coll_p, key, (void **)&pdcp_p);

	if (h_rc != HASH_TABLE_OK) {
		if (modeP != PDCP_TRANSMISSION_MODE_TRANSPARENT) {
			printf(PROTOCOL_CTXT_FMT" Instance is not configured for rb_id %d Ignoring SDU...\n",
					PROTOCOL_CTXT_ARGS(ctxt_pP), rb_idP);

			ctxt_pP->configured=FALSE;
			return FALSE;
		}
	} else {
//		instance for a given RB is configured
		ctxt_pP->configured=TRUE;
	}



//	calculate the pdcp header and trailer size
	if (srb_flagP) {
		pdcp_header_len = PDCP_CONTROL_PLANE_DATA_PDU_SN_SIZE;
		pdcp_tailer_len = PDCP_CONTROL_PLANE_DATA_PDU_MAC_I_SIZE;
	} else {
		pdcp_header_len = pdcp_p->pdcp_SN_SizeUL == 12 ? PDCP_USER_PLANE_DATA_PDU_SN12_HEADER_SIZE : PDCP_USER_PLANE_DATA_PDU_SN18_HEADER_SIZE;

//		鐢ㄦ埛闈㈡暟鎹槸鍚﹁缃簡瀹屾暣鎬т繚鎶�
		pdcp_tailer_len = (pdcp_p->security_activated && pdcp_p->kUPint) ? PDCP_USER_PLANE_DATA_PDU_MAC_I_SIZE : 0;
	}

	pdcp_pdu_size = sdu_buffer_sizeP + pdcp_header_len + pdcp_tailer_len;

	printf(PROTOCOL_PDCP_CTXT_FMT"Data request notification  pdu size %d (header%d, trailer%d)\n",
			PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p), pdcp_pdu_size, pdcp_header_len, pdcp_tailer_len);
	/*
	* Allocate a new block for the new PDU (i.e. PDU header and SDU payload)
	*/
	pdcp_pdu_p = get_free_mem_block(pdcp_pdu_size, __func__);

	if (pdcp_pdu_p != NULL) {
		/*
		* Create a Data PDU with header and append data
		*
		* Place User Plane PDCP Data PDU header first
		*/
		if (srb_flagP) { // this Control plane PDCP Data PDU
			pdcp_control_plane_data_pdu_header pdu_header;

			pdu_header.sn = pdcp_get_next_tx_seq_number(pdcp_p);
			current_sn = pdu_header.sn;

			memset(&pdu_header.mac_i[0], 0, PDCP_CONTROL_PLANE_DATA_PDU_MAC_I_SIZE);
			memset(&pdcp_pdu_p->data[sdu_buffer_sizeP + pdcp_header_len], 0, PDCP_CONTROL_PLANE_DATA_PDU_MAC_I_SIZE);

			if (pdcp_serialize_control_plane_data_pdu_with_SRB_sn_buffer((unsigned char *)pdcp_pdu_p->data, &pdu_header) == FALSE) {
				printf( PROTOCOL_PDCP_CTXT_FMT" Cannot fill PDU buffer with relevant header fields!\n",
						PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p));

				return FALSE;
			}
		} else {
			pdcp_user_plane_data_pdu_header pdu_header;
			if(pdcp_p->security_activated && pdcp_p->kUPint)
			{
				memset(&pdu_header.mac_i[0], 0, PDCP_CONTROL_PLANE_DATA_PDU_MAC_I_SIZE);
			}

			pdu_header.dc = (modeP == PDCP_TRANSMISSION_MODE_DATA) ? PDCP_DATA_PDU_BIT_SET : PDCP_CONTROL_PDU_BIT_SET;
			pdu_header.sn = pdcp_get_next_tx_seq_number(pdcp_p);
			current_sn = pdu_header.sn ;

			if (pdcp_serialize_user_plane_data_pdu_with_DRB_sn_buffer((unsigned char *)pdcp_pdu_p->data, pdcp_p->pdcp_SN_SizeUL, &pdu_header) == FALSE) {
				printf( PROTOCOL_PDCP_CTXT_FMT" Cannot fill PDU buffer with relevant header fields!\n",
						PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p));

				return FALSE;
			}
		}

		/*
		* Validate incoming sequence number, there might be a problem with PDCP initialization
		*/
//		if (current_sn > pdcp_calculate_max_seq_num_for_given_size(pdcp_p->seq_num_size)) {
//			printf( PROTOCOL_PDCP_CTXT_FMT" Generated sequence number (%"PRIu16") is greater than a sequence number could ever be!\n"\
//					"There must be a problem with PDCP initialization, ignoring this PDU...\n",
//					PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p), current_sn);
//
//			free_mem_block(pdcp_pdu_p, __func__);
//
//			return FALSE;
//		}

		printf("Sequence number %d is assigned to current PDU\n", current_sn);
		/* Then append data... */
		memcpy(&pdcp_pdu_p->data[pdcp_header_len], sdu_buffer_pP, sdu_buffer_sizeP);

//		For control plane data that are not integrity protected,
//		the MAC-I field is still present and should be padded with padding bits set to 0.
//		NOTE: user-plane data are never integrity protected
		for (i=0; i<pdcp_tailer_len; i++) {
			pdcp_pdu_p->data[pdcp_header_len + sdu_buffer_sizeP + i] = 0x00;// pdu_header.mac_i[i];
		}

		if ((pdcp_p->security_activated != 0) && (((pdcp_p->cipheringAlgorithm) != 0) ||	((pdcp_p->integrityProtAlgorithm) != 0))) {

//			pdcp_apply_security(ctxt_pP,
//									pdcp_p,
//									srb_flagP,
//									rb_idP % maxLC_ID,
//									pdcp_header_len,
//									current_sn,
//									pdcp_pdu_p->data,
//									sdu_buffer_sizeP);

		}

		/* Print octets of outgoing data in hexadecimal form */
		printf("Following content with size %d will be sent over RLC (PDCP PDU header is the first two bytes)\n", pdcp_pdu_size);

//		util_print_hex_octets(PDCP, (unsigned char*)pdcp_pdu_p->data, pdcp_pdu_size);
//		util_flush_hex_octets(PDCP, (unsigned char*)pdcp_pdu->data, pdcp_pdu_size);
	} else {
		printf( "Cannot create a mem_block for a PDU!\n");

		printf(  "[FRAME %5u][%s][PDCP][MOD %u][RB %u] PDCP_DATA_REQ SDU DROPPED, OUT OF MEMORY \n",
				ctxt_pP->frame, (ctxt_pP->enb_flag) ? "eNB" : "UE", ctxt_pP->module_id, rb_idP);

		return FALSE;
	}

	/*
	* Ask sublayer to transmit data and check return value
	* to see if RLC succeeded
	*/
	rlc_status = rlc_data_req(ctxt_pP
								, srb_flagP
								, MBMS_FLAG_NO
								, rb_idP
								, muiP
								, confirmP
								, pdcp_pdu_size
								, pdcp_pdu_p
//								,NULL
//								,NULL
								);

	switch (rlc_status) {
	case RLC_OP_STATUS_OK:
		printf("Data sending request over RLC succeeded!\n");
		ret=TRUE;
		break;

	case RLC_OP_STATUS_BAD_PARAMETER:
		printf("Data sending request over RLC failed with 'Bad Parameter' reason!\n");
		ret= FALSE;
		break;

	case RLC_OP_STATUS_INTERNAL_ERROR:
		printf("Data sending request over RLC failed with 'Internal Error' reason!\n");
		ret= FALSE;
		break;

	case RLC_OP_STATUS_OUT_OF_RESSOURCES:
		printf("Data sending request over RLC failed with 'Out of Resources' reason!\n");
		ret= FALSE;
		break;

	default:
		printf("RLC returned an unknown status code after PDCP placed the order to send some data (Status Code:%d)\n", rlc_status);
		ret= FALSE;
		break;
	} // switch case




	/*
	* Control arrives here only if rlc_data_req() returns RLC_OP_STATUS_OK
	* so we return TRUE afterwards
	*/

//	for (pdcp_uid=0; pdcp_uid< MAX_MOBILES; pdcp_uid++) {
//		if (pdcp_enb[ctxt_pP->module_id].rnti == ctxt_pP->rnti )
//			break;
//	}

	Pdcp_stats_tx[ctxt_pP->module_id][rb_idP+rb_offset]++;
	Pdcp_stats_tx_tmp_w[ctxt_pP->module_id][rb_idP+rb_offset]++;
	Pdcp_stats_tx_bytes[ctxt_pP->module_id][rb_idP+rb_offset]+=sdu_buffer_sizeP;
	Pdcp_stats_tx_bytes_tmp_w[ctxt_pP->module_id][rb_idP+rb_offset]+=sdu_buffer_sizeP;
	Pdcp_stats_tx_sn[ctxt_pP->module_id][rb_idP+rb_offset]=current_sn;

	return ret;
}


//-----------------------------------------------------------------------------
boolean_t pdcp_data_ind(
	const protocol_ctxt_t *const ctxt_pP,
	const srb_flag_t   srb_flagP,
	const MBMS_flag_t  MBMS_flagP,
	const rb_id_t      rb_idP,
	const sdu_size_t   sdu_buffer_sizeP,
	mem_block_t *const sdu_buffer_pP
)
//-----------------------------------------------------------------------------
{
	pdcp_t      *pdcp_p          = NULL;
	list_t      *sdu_list_p      = NULL;
	mem_block_t *new_sdu_p       = NULL;
	mem_block_t *tb_pP = NULL;
	mem_block_t *cursor_p = NULL;
	uint8_t      pdcp_header_len = 0;
	uint8_t      pdcp_tailer_len = 0;
	pdcp_sn_t    sequence_number = 0;
	volatile sdu_size_t   payload_offset  = 0;
	rb_id_t      rb_id            = rb_idP;
	boolean_t    packet_forwarded = FALSE;
	hash_key_t      key             = HASHTABLE_NOT_A_KEY_VALUE;
	hashtable_rc_t  h_rc;
	uint8_t      rb_offset= (srb_flagP == 0) ? DTCH -1 :0;
	uint16_t     pdcp_uid=0;
//	MessageDef  *message_p        = NULL;
//	uint8_t     *gtpu_buffer_p    = NULL;
	uint32_t    rx_hfn_for_count;
	int         pdcp_sn_for_count;
	int         security_ok;
	uint8_t dc = 0;

	printf("PDCP DL %s PDU on rb_id %d\n", (srb_flagP) ? "CONTROL" : "DATA", rb_idP);
#if T_TRACER

	if (ctxt_pP->enb_flag != ENB_FLAG_NO)
	T(T_ENB_PDCP_UL, T_INT(ctxt_pP->module_id), T_INT(ctxt_pP->rnti), T_INT(rb_idP), T_INT(sdu_buffer_sizeP));

#endif


	rb_id = rb_idP % maxLC_ID;
	AssertError (rb_id < maxLC_ID, return FALSE, "RB id is too high (%u/%d) %u UE %x!\n",
				rb_id, maxLC_ID, ctxt_pP->module_id, ctxt_pP->rnti);
	AssertError (rb_id > 0, return FALSE, "RB id is too low (%u/%d) %u UE %x!\n",
				rb_id, maxLC_ID, ctxt_pP->module_id, ctxt_pP->rnti);

	key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, rb_id, srb_flagP);

	h_rc = hashtable_get(pdcp_coll_p, key, (void **)&pdcp_p);

	if (h_rc != HASH_TABLE_OK) {
		printf( PROTOCOL_CTXT_FMT"Could not get PDCP instance key 0x%"PRIx64"\n", PROTOCOL_CTXT_ARGS(ctxt_pP), key);

		free_mem_block(sdu_buffer_pP, __func__);

		return FALSE;
	}

	sdu_list_p = &pdcp_sdu_list;

	if (sdu_buffer_sizeP == 0) {
		printf("SDU buffer size is zero! Ignoring this chunk!\n");
		return FALSE;
	}


	/*
	* Parse the PDU placed at the beginning of SDU to check
	* if incoming SN is in line with RX window
	*/

	if (srb_flagP) { //SRB1/2
		pdcp_header_len = PDCP_CONTROL_PLANE_DATA_PDU_SN_SIZE;
		pdcp_tailer_len = PDCP_CONTROL_PLANE_DATA_PDU_MAC_I_SIZE;
		sequence_number = pdcp_get_sequence_number_of_pdu_with_SRB_sn((unsigned char *)sdu_buffer_pP->data);
	} else { // DRB
		dc = pdcp_get_dc_filed((unsigned char*)sdu_buffer_pP->data);

		if(dc == PDCP_CONTROL_PDU_BIT_SET)
		{
		  printf("Get Control PDU for PDCP!\n");
		  return FALSE;
		}


		pdcp_tailer_len = pdcp_p->kUPint ? PDCP_USER_PLANE_DATA_PDU_MAC_I_SIZE : 0;

		if (pdcp_p->pdcp_SN_SizeDL == 18) {
			pdcp_header_len = PDCP_USER_PLANE_DATA_PDU_SN18_HEADER_SIZE;
			sequence_number = pdcp_get_sequence_number_of_pdu_with_sn18((unsigned char *)sdu_buffer_pP->data);
		} else if (pdcp_p->pdcp_SN_SizeDL == 12) {
			pdcp_header_len = PDCP_USER_PLANE_DATA_PDU_SN12_HEADER_SIZE;
			sequence_number = pdcp_get_sequence_number_of_pdu_with_sn12((unsigned char *)sdu_buffer_pP->data);
		} else {
			printf(PROTOCOL_PDCP_CTXT_FMT"wrong sequence number  (%d) for this pdcp entity \n",
					PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p), pdcp_p->seq_num_size);

//			exit(1);
			return 0;
		}
	}

	/*
	* Check if incoming SDU is long enough to carry a PDU header
	*/
	if (sdu_buffer_sizeP < pdcp_header_len + pdcp_tailer_len ) {
		printf(PROTOCOL_PDCP_CTXT_FMT"Incoming (from RLC) SDU is short of size (size:%d)! Ignoring...\n",
				PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p), sdu_buffer_sizeP);

		free_mem_block(sdu_buffer_pP, __func__);

		return FALSE;
	}

//	TS38.323 5.2.2.1
//	At reception of a PDCP Data PDU from lower layers, the receiving PDCP entity shall determine the COUNT value of the received PDCP Data PDU, i.e. RCVD_COUNT, as follows:
//	-	if RCVD_SN < SN(RX_DELIV) 鈥� Window_Size:
//		-	RCVD_HFN = HFN(RX_DELIV) + 1.
//	-	else if RCVD_SN >= SN(RX_DELIV) + Window_Size:
//		-	RCVD_HFN = HFN(RX_DELIV) 鈥� 1.
//	-	else:
//		-	RCVD_HFN = HFN(RX_DELIV);
//	-	RCVD_COUNT = [RCVD_HFN, RCVD_SN].
	if(pdcp_p->RCVD_SN < pdcp_p->RX_DELIV & (1 << pdcp_p->pdcp_SN_SizeDL - 1) - pdcp_p->Window_Size) {
		pdcp_p->RCVD_HFN = pdcp_p->RX_DELIV >> pdcp_p->pdcp_SN_SizeDL + 1;
	}
	else if(pdcp_p->RCVD_SN < pdcp_p->RX_DELIV & (1 << pdcp_p->pdcp_SN_SizeDL - 1) + pdcp_p->Window_Size) {
		pdcp_p->RCVD_HFN = pdcp_p->RX_DELIV >> pdcp_p->pdcp_SN_SizeDL - 1;
	}
	else {
		pdcp_p->RCVD_HFN = pdcp_p->RX_DELIV >> pdcp_p->pdcp_SN_SizeDL;
	}

	pdcp_p->RCVD_COUNT = pdcp_p->RCVD_HFN << pdcp_p->pdcp_SN_SizeDL | pdcp_p->RCVD_SN;

//	After determining the COUNT value of the received PDCP Data PDU = RCVD_COUNT, the receiving PDCP entity shall:
//	-	perform deciphering and integrity verification of the PDCP Data PDU using COUNT = RCVD_COUNT;
//		-	if integrity verification fails:
//			-	indicate the integrity verification failure to upper layer;
//			-	discard the PDCP Data PDU;



//	TODO add code for security
	if (pdcp_p->security_activated == 1) {
//		security_ok = pdcp_validate_security(ctxt_pP,
//							pdcp_p,
//							srb_flagP,
//							rb_idP,
//							pdcp_header_len,
//							rx_hfn_for_count,
//							pdcp_sn_for_count,
//							sdu_buffer_pP->data,
//							sdu_buffer_sizeP - pdcp_tailer_len) == 0;

	} else {
		security_ok = 1;
	}

	if (security_ok == 0) {
		printf(PROTOCOL_PDCP_CTXT_FMT"security not validated for incoming PDCP SRB PDU\n",
				PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p));

		printf("Ignoring PDU...\n");

		free_mem_block(sdu_buffer_pP, __func__);
		/* TODO: indicate integrity verification failure to upper layer */
		return FALSE;
	}

//	-	if RCVD_COUNT < RX_DELIV; or
//	-	if the PDCP Data PDU with COUNT = RCVD_COUNT has been received before:
//		-	discard the PDCP Data PDU;
	if(pdcp_p->RCVD_COUNT < pdcp_p->RX_DELIV) {
		printf("Ignoring PDU...\n");
		free_mem_block(sdu_buffer_pP, __func__);
		return FALSE;
	}

//	缂撳啿鏁版嵁锛屽鏋滄槸閲嶅鏁版嵁锛屽垯涓㈠純褰撳墠鏁版嵁骞堕��鍑恒��
	tb_pP = get_free_mem_block(sizeof(pdcp_pdu_info_t), __func__);
	((pdcp_pdu_info_t*)(tb_pP->data))->count = pdcp_p->RCVD_COUNT;
	((pdcp_pdu_info_t*)(tb_pP->data))->payload_size = sdu_buffer_sizeP;
	((pdcp_pdu_info_t*)(tb_pP->data))->header_size = pdcp_header_len;
	((pdcp_pdu_info_t*)(tb_pP->data))->rb_id = rb_idP;
	((pdcp_pdu_info_t*)(tb_pP->data))->pdu_mbP = sdu_buffer_pP;

	if(pdcp_rx_list_check_duplicate_insert_sdu(ctxt_pP, pdcp_p, tb_pP) == FALSE) {
		free_mem_block(sdu_buffer_pP, __func__);
		return FALSE;
	}

//	If the received PDCP Data PDU with COUNT value = RCVD_COUNT is not discarded above, the receiving PDCP entity shall:
//	-	store the resulting PDCP SDU in the reception buffer;
//	-	if RCVD_COUNT >= RX_NEXT:
//		-	update RX_NEXT to RCVD_COUNT + 1.
//	-	if outOfOrderDelivery is configured:
//		-	deliver the resulting PDCP SDU to upper layers.
//	-	if RCVD_COUNT = RX_DELIV:
//		-	deliver to upper layers in ascending order of the associated COUNT value after performing header decompression, if not decompressed before;
//			-	all stored PDCP SDU(s) with consecutively associated COUNT value(s) starting from COUNT = RX_DELIV;
//		-	update RX_DELIV to the COUNT value of the first PDCP SDU which has not been delivered to upper layers, with COUNT value > RX_DELIV;
//	-	if t-Reordering is running, and if RX_DELIV >= RX_REORD:
//		-	stop and reset t-Reordering.
//	-	if t-Reordering is not running (includes the case when t-Reordering is stopped due to actions above), and RX_DELIV < RX_NEXT:
//		-	update RX_REORD to RX_NEXT;
//		-	start t-Reordering.

	if(pdcp_p->RCVD_COUNT >= pdcp_p->RX_NEXT) {
		pdcp_p->RX_NEXT = pdcp_p->RCVD_COUNT + 1;
	}

//	鏃犲簭浜や簰锛屽垯鐩存帴浼犻�扴DU鑷充笂灞�
	if(pdcp_p->outOfOrderDelivery)	{

	} else if(pdcp_p->RCVD_COUNT == pdcp_p->RX_DELIV) {
		cursor_p = pdcp_p->reception_buffer.head;

		do
		{
			if(((pdcp_pdu_info_t*)cursor_p->data)->count == pdcp_p->RCVD_COUNT)
			{
				if(srb_flagP) // RRC瑙ｇ爜銆�2019.6.20
				{
//					rrc_data_ind(ctxt_pP,
//					   rb_id,
//					   sdu_buffer_sizeP - pdcp_header_len - pdcp_tailer_len,
//					   (uint8_t*)&sdu_buffer_pP->data[pdcp_header_len]);
				}
				else // DRBs锛屼笂浼燬DAP瀛愬眰銆�2019.6.20
				{

				}
			}
			else
			{
				pdcp_p->RX_DELIV = ((pdcp_pdu_info_t*)cursor_p->data)->count;

				break;
			}

			pdcp_p->RCVD_COUNT += 1;
			cursor_p = cursor_p->next;

			list_remove_head(pdcp_p->reception_buffer.head);
		}
		while(cursor_p != NULL);
	}

	if(pdcp_p->t_reordering.running && pdcp_p->RX_DELIV >= pdcp_p->RX_REORD)
	{
		pdcp_p->t_reordering.running = 0;
	}

	if(!pdcp_p->t_reordering.running)
	{
		pdcp_p->RX_REORD = pdcp_p->RX_NEXT;
		pdcp_p->t_reordering.running = 1;
		pdcp_p->t_reordering.ms_start = ctxt_pP->frame * 10 + ctxt_pP->subframe;
	}

//	5.2.2.2	Actions when a t-Reordering expires
//	When t-Reordering expires, the receiving PDCP entity shall:
//		-	deliver to upper layers in ascending order of the associated COUNT value after performing header decompression, if not decompressed before:
//			-	all stored PDCP SDU(s) with associated COUNT value(s) < RX_REORD;
//			-	all stored PDCP SDU(s) with consecutively associated COUNT value(s) starting from RX_REORD;
//	-	update RX_DELIV to the COUNT value of the first PDCP SDU which has not been delivered to upper layers, with COUNT value >= RX_REORD;
//	-	if RX_DELIV < RX_NEXT:
//		-	update RX_REORD to RX_NEXT;
//		-	start t-Reordering.



//	5.2.2.3	Actions when the value of t-Reordering is reconfigured
//	When the value of the t-Reordering is reconfigured by upper layers while the t-Reordering is running, the receiving PDCP entity shall:
//		-	update RX_REORD to RX_NEXT;
//		-	stop and restart t-Reordering.



	Pdcp_stats_rx[ctxt_pP->module_id][rb_idP+rb_offset]++;
	Pdcp_stats_rx_tmp_w[ctxt_pP->module_id][rb_idP+rb_offset]++;
	Pdcp_stats_rx_bytes[ctxt_pP->module_id][rb_idP+rb_offset]+=(sdu_buffer_sizeP  - payload_offset);
	Pdcp_stats_rx_bytes_tmp_w[ctxt_pP->module_id][rb_idP+rb_offset]+=(sdu_buffer_sizeP  - payload_offset);
	Pdcp_stats_rx_sn[ctxt_pP->module_id][rb_idP+rb_offset]=sequence_number;
//	Pdcp_stats_rx_aiat[ctxt_pP->module_id][rb_idP+rb_offset]+= (pdcp_enb[ctxt_pP->module_id].sfn - Pdcp_stats_rx_iat[ctxt_pP->module_id][rb_idP+rb_offset]);
//	Pdcp_stats_rx_aiat_tmp_w[ctxt_pP->module_id][rb_idP+rb_offset]+=(pdcp_enb[ctxt_pP->module_id].sfn - Pdcp_stats_rx_iat[ctxt_pP->module_id][rb_idP+rb_offset]);
//	Pdcp_stats_rx_iat[ctxt_pP->module_id][rb_idP+rb_offset]=pdcp_enb[ctxt_pP->module_id].sfn;
	free_mem_block(sdu_buffer_pP, __func__);

	return TRUE;
}

void pdcp_update_stats(const protocol_ctxt_t *const  ctxt_pP)
{
	uint16_t           pdcp_uid = 0;
	uint8_t            rb_id     = 0;

	// these stats are measured for both eNB and UE on per seond basis
	for (rb_id = 0; rb_id < NB_RB_MAX; rb_id++) {
		for (pdcp_uid=0; pdcp_uid< MAX_MOBILES; pdcp_uid++) {
			//printf("frame %d and subframe %d \n", pdcp_enb[ctxt_pP->module_id].frame, pdcp_enb[ctxt_pP->module_id].subframe);
			// tx stats
			if (Pdcp_stats_tx_window_ms[ctxt_pP->module_id] > 0) {
				// unit: bit/s
				Pdcp_stats_tx_throughput_w[ctxt_pP->module_id][rb_id]=Pdcp_stats_tx_bytes_tmp_w[ctxt_pP->module_id][rb_id]*8;
				Pdcp_stats_tx_w[ctxt_pP->module_id][rb_id]= Pdcp_stats_tx_tmp_w[ctxt_pP->module_id][rb_id];
				Pdcp_stats_tx_bytes_w[ctxt_pP->module_id][rb_id]= Pdcp_stats_tx_bytes_tmp_w[ctxt_pP->module_id][rb_id];

				if (Pdcp_stats_tx_tmp_w[ctxt_pP->module_id][rb_id] > 0) {
					Pdcp_stats_tx_aiat_w[ctxt_pP->module_id][rb_id]=(Pdcp_stats_tx_aiat_tmp_w[ctxt_pP->module_id][rb_id]/Pdcp_stats_tx_tmp_w[ctxt_pP->module_id][rb_id]);
				} else {
					Pdcp_stats_tx_aiat_w[ctxt_pP->module_id][rb_id]=0;
				}

				// reset the tmp vars
				Pdcp_stats_tx_tmp_w[ctxt_pP->module_id][rb_id]=0;
				Pdcp_stats_tx_bytes_tmp_w[ctxt_pP->module_id][rb_id]=0;
				Pdcp_stats_tx_aiat_tmp_w[ctxt_pP->module_id][rb_id]=0;
			}

			if (Pdcp_stats_rx_window_ms[ctxt_pP->module_id] > 0) {
				// rx stats
				Pdcp_stats_rx_goodput_w[ctxt_pP->module_id][rb_id]=Pdcp_stats_rx_bytes_tmp_w[ctxt_pP->module_id][rb_id]*8;
				Pdcp_stats_rx_w[ctxt_pP->module_id][rb_id]=   Pdcp_stats_rx_tmp_w[ctxt_pP->module_id][rb_id];
				Pdcp_stats_rx_bytes_w[ctxt_pP->module_id][rb_id]= Pdcp_stats_rx_bytes_tmp_w[ctxt_pP->module_id][rb_id];

				if(Pdcp_stats_rx_tmp_w[ctxt_pP->module_id][rb_id] > 0) {
					Pdcp_stats_rx_aiat_w[ctxt_pP->module_id][rb_id]= (Pdcp_stats_rx_aiat_tmp_w[ctxt_pP->module_id][rb_id]/Pdcp_stats_rx_tmp_w[ctxt_pP->module_id][rb_id]);
				} else {
					Pdcp_stats_rx_aiat_w[ctxt_pP->module_id][rb_id]=0;
				}

				// reset the tmp vars
				Pdcp_stats_rx_tmp_w[ctxt_pP->module_id][rb_id]=0;
				Pdcp_stats_rx_bytes_tmp_w[ctxt_pP->module_id][rb_id]=0;
				Pdcp_stats_rx_aiat_tmp_w[ctxt_pP->module_id][rb_id]=0;
			}
		}
	}
}


//-----------------------------------------------------------------------------
void pdcp_run (const protocol_ctxt_t *const  ctxt_pP)
//-----------------------------------------------------------------------------
{
	pdcp_update_stats(ctxt_pP);
}

void pdcp_init_stats_UE(module_id_t mod, uint16_t uid)
{
	Pdcp_stats_tx_window_ms[mod] = 100;
	Pdcp_stats_rx_window_ms[mod] = 100;

	for (int i = 0; i < NB_RB_MAX; ++i) {
		Pdcp_stats_tx_bytes[mod][i] = 0;
		Pdcp_stats_tx_bytes_w[mod][i] = 0;
		Pdcp_stats_tx_bytes_tmp_w[mod][i] = 0;
		Pdcp_stats_tx[mod][i] = 0;
		Pdcp_stats_tx_w[mod][i] = 0;
		Pdcp_stats_tx_tmp_w[mod][i] = 0;
		Pdcp_stats_tx_sn[mod][i] = 0;
		Pdcp_stats_tx_throughput_w[mod][i] = 0;
		Pdcp_stats_tx_aiat[mod][i] = 0;
		Pdcp_stats_tx_aiat_w[mod][i] = 0;
		Pdcp_stats_tx_aiat_tmp_w[mod][i] = 0;
		Pdcp_stats_tx_iat[mod][i] = 0;
		Pdcp_stats_rx[mod][i] = 0;
		Pdcp_stats_rx_w[mod][i] = 0;
		Pdcp_stats_rx_tmp_w[mod][i] = 0;
		Pdcp_stats_rx_bytes[mod][i] = 0;
		Pdcp_stats_rx_bytes_w[mod][i] = 0;
		Pdcp_stats_rx_bytes_tmp_w[mod][i] = 0;
		Pdcp_stats_rx_sn[mod][i] = 0;
		Pdcp_stats_rx_goodput_w[mod][i] = 0;
		Pdcp_stats_rx_aiat[mod][i] = 0;
		Pdcp_stats_rx_aiat_w[mod][i] = 0;
		Pdcp_stats_rx_aiat_tmp_w[mod][i] = 0;
		Pdcp_stats_rx_iat[mod][i] = 0;
		Pdcp_stats_rx_outoforder[mod][i] = 0;
	}
}

void pdcp_add_UE(const protocol_ctxt_t *const  ctxt_pP)
{
	int i; //, ret=-1; to be decied later

	for (i=0; i < MAX_MOBILES ; i++) {
		pdcp_init_stats_UE(ctxt_pP->module_id, i);
	}

  //return ret;
}

//-----------------------------------------------------------------------------
boolean_t pdcp_remove_UE(const protocol_ctxt_t *const  ctxt_pP)
//-----------------------------------------------------------------------------
{
	DRB_Identity_t  srb_id         = 0;
	DRB_Identity_t  drb_id         = 0;
	hash_key_t      key            = HASHTABLE_NOT_A_KEY_VALUE;
	hashtable_rc_t  h_rc;
	int i;
	// check and remove SRBs first

	for(int i = 0; i<MAX_MOBILES; i++) {
		if(pdcp_eNB_UE_instance_to_rnti[i] == ctxt_pP->rnti) {
			pdcp_eNB_UE_instance_to_rnti[i] = NOT_A_RNTI;
			break;
		}
	}

	for (srb_id=1; srb_id<3; srb_id++) {
		key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, srb_id, SRB_FLAG_YES);
		h_rc = hashtable_remove(pdcp_coll_p, key);
	}

	for (drb_id=0; drb_id<maxLC_ID; drb_id++) {
		key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, drb_id, SRB_FLAG_NO);
		h_rc = hashtable_remove(pdcp_coll_p, key);
	}

	(void)h_rc; /* remove gcc warning "set but not used" */

	// remove ue for pdcp enb inst
//	for (i=0; i < MAX_MOBILES; i++) {
//		if (pdcp_enb[ctxt_pP->module_id].rnti[i] == ctxt_pP->rnti ) {
//			printf("remove uid is %d/%d %x\n", i,
//			pdcp_enb[ctxt_pP->module_id].uid[i],
//			pdcp_enb[ctxt_pP->module_id].rnti[i]);
//			pdcp_enb[ctxt_pP->module_id].uid[i]=0;
//			pdcp_enb[ctxt_pP->module_id].rnti[i]=0;
//			pdcp_enb[ctxt_pP->module_id].num_ues--;
//			break;
//		}
//	}

	return 1;
}

#if 0
//-----------------------------------------------------------------------------
boolean_t
rrc_pdcp_config_asn1_req (
	const protocol_ctxt_t *const  ctxt_pP,
	SRB_ToAddModList_t  *const srb2add_list_pP,
	DRB_ToAddModList_t  *const drb2add_list_pP,
	DRB_ToReleaseList_t *const drb2release_list_pP,
	const uint8_t                   security_modeP,
	uint8_t                  *const kRRCenc_pP,
	uint8_t                  *const kRRCint_pP,
	uint8_t                  *const kUPenc_pP,
	rb_id_t                 *const defaultDRB
)
//-----------------------------------------------------------------------------
{
  long int        lc_id          = 0;
  DRB_Identity_t  srb_id     = 0;
  long int        mch_id         = 0;
  rlc_mode_t      rlc_type       = RLC_MODE_NONE;
  DRB_Identity_t  drb_id     = 0;
  DRB_Identity_t *pdrb_id_p  = NULL;
  uint8_t         drb_sn         = 12;
  uint8_t         srb_sn         = 5; // fixed sn for SRBs
  uint8_t         drb_report     = 0;
  long int        cnt            = 0;
  uint16_t        header_compression_profile = 0;
  config_action_t action                     = CONFIG_ACTION_ADD;
  SRB_ToAddMod_t *srb_toaddmod_p = NULL;
  DRB_ToAddMod_t *drb_toaddmod_p = NULL;
  pdcp_t         *pdcp_p         = NULL;
  hash_key_t      key            = HASHTABLE_NOT_A_KEY_VALUE;
  hashtable_rc_t  h_rc;
  hash_key_t      key_defaultDRB = HASHTABLE_NOT_A_KEY_VALUE;
  hashtable_rc_t  h_defaultDRB_rc;
  int i,j;
  MBMS_SessionInfoList_r9_t *mbms_SessionInfoList_r9_p = NULL;
  MBMS_SessionInfo_r9_t     *MBMS_SessionInfo_p        = NULL;
  LOG_T(PDCP, PROTOCOL_CTXT_FMT" %s() SRB2ADD %p DRB2ADD %p DRB2RELEASE %p\n",
        PROTOCOL_CTXT_ARGS(ctxt_pP),
        __FUNCTION__,
        srb2add_list_pP,
        drb2add_list_pP,
        drb2release_list_pP);

  // srb2add_list does not define pdcp config, we use rlc info to setup the pdcp dcch0 and dcch1 channels

  if (srb2add_list_pP != NULL) {
    for (cnt=0; cnt<srb2add_list_pP->list.count; cnt++) {
      srb_id = srb2add_list_pP->list.array[cnt]->srb_Identity;
      srb_toaddmod_p = srb2add_list_pP->list.array[cnt];
      rlc_type = RLC_MODE_AM;
      lc_id = srb_id;
      key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, ctxt_pP->enb_flag, srb_id, SRB_FLAG_YES);
      h_rc = hashtable_get(pdcp_coll_p, key, (void **)&pdcp_p);

      if (h_rc == HASH_TABLE_OK) {
        action = CONFIG_ACTION_MODIFY;
        printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_MODIFY key 0x%"PRIx64"\n",
              PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
              key);
      } else {
        action = CONFIG_ACTION_ADD;
        pdcp_p = calloc(1, sizeof(pdcp_t));
        h_rc = hashtable_insert(pdcp_coll_p, key, pdcp_p);

        if (h_rc != HASH_TABLE_OK) {
          printf( PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_ADD key 0x%"PRIx64" FAILED\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
                key);
          free(pdcp_p);
          return TRUE;
        } else {
          printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_ADD key 0x%"PRIx64"\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
                key);
        }
      }

      if (srb_toaddmod_p->rlc_Config) {
        switch (srb_toaddmod_p->rlc_Config->present) {
          case SRB_ToAddMod__rlc_Config_PR_NOTHING:
            break;

          case SRB_ToAddMod__rlc_Config_PR_explicitValue:
            switch (srb_toaddmod_p->rlc_Config->choice.explicitValue.present) {
              case RLC_Config_PR_NOTHING:
                break;

              default:
                pdcp_config_req_asn1 (
                  ctxt_pP,
                  pdcp_p,
                  SRB_FLAG_YES,
                  rlc_type,
                  action,
                  lc_id,
                  mch_id,
                  srb_id,
                  srb_sn,
                  0, // drb_report
                  0, // header compression
                  security_modeP,
                  kRRCenc_pP,
                  kRRCint_pP,
                  kUPenc_pP);
                break;
            }

            break;

          case SRB_ToAddMod__rlc_Config_PR_defaultValue:
            pdcp_config_req_asn1 (
              ctxt_pP,
              pdcp_p,
              SRB_FLAG_YES,
              rlc_type,
              action,
              lc_id,
              mch_id,
              srb_id,
              srb_sn,
              0, // drb_report
              0, // header compression
              security_modeP,
              kRRCenc_pP,
              kRRCint_pP,
              kUPenc_pP);
            // already the default values
            break;

          default:
            DevParam(srb_toaddmod_p->rlc_Config->present, ctxt_pP->module_id, ctxt_pP->rnti);
            break;
        }
      }
    }
  }

  // reset the action

  if (drb2add_list_pP != NULL) {
    for (cnt=0; cnt<drb2add_list_pP->list.count; cnt++) {
      drb_toaddmod_p = drb2add_list_pP->list.array[cnt];
      drb_id = drb_toaddmod_p->drb_Identity;// + drb_id_offset;

      if (drb_toaddmod_p->logicalChannelIdentity) {
        lc_id = *(drb_toaddmod_p->logicalChannelIdentity);
      } else {
        printf( PROTOCOL_PDCP_CTXT_FMT" logicalChannelIdentity is missing in DRB-ToAddMod information element!\n",
              PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p));
        continue;
      }

      if (lc_id == 1 || lc_id == 2) {
        LOG_E(RLC, PROTOCOL_CTXT_FMT" logicalChannelIdentity = %ld is invalid in RRC message when adding DRB!\n", PROTOCOL_CTXT_ARGS(ctxt_pP), lc_id);
        continue;
      }

      DevCheck4(drb_id < maxLC_ID, drb_id, maxLC_ID, ctxt_pP->module_id, ctxt_pP->rnti);
      key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, ctxt_pP->enb_flag, drb_id, SRB_FLAG_NO);
      h_rc = hashtable_get(pdcp_coll_p, key, (void **)&pdcp_p);

      if (h_rc == HASH_TABLE_OK) {
        action = CONFIG_ACTION_MODIFY;
        printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_MODIFY key 0x%"PRIx64"\n",
              PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
              key);
      } else {
        action = CONFIG_ACTION_ADD;
        pdcp_p = calloc(1, sizeof(pdcp_t));
        h_rc = hashtable_insert(pdcp_coll_p, key, pdcp_p);

        // save the first configured DRB-ID as the default DRB-ID
        if ((defaultDRB != NULL) && (*defaultDRB == drb_id)) {
          key_defaultDRB = PDCP_COLL_KEY_DEFAULT_DRB_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, ctxt_pP->enb_flag);
          h_defaultDRB_rc = hashtable_insert(pdcp_coll_p, key_defaultDRB, pdcp_p);
        } else {
          h_defaultDRB_rc = HASH_TABLE_OK; // do not trigger any error handling if this is not a default DRB
        }

        if (h_defaultDRB_rc != HASH_TABLE_OK) {
          printf( PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_ADD ADD default DRB key 0x%"PRIx64" FAILED\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
                key_defaultDRB);
          free(pdcp_p);
          return TRUE;
        } else if (h_rc != HASH_TABLE_OK) {
          printf( PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_ADD ADD key 0x%"PRIx64" FAILED\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
                key);
          free(pdcp_p);
          return TRUE;
        } else {
          printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_ADD ADD key 0x%"PRIx64"\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p),
                key);
        }
      }

      if (drb_toaddmod_p->pdcp_Config) {
        if (drb_toaddmod_p->pdcp_Config->discardTimer) {
          // set the value of the timer
        }

        if (drb_toaddmod_p->pdcp_Config->rlc_AM) {
          drb_report = drb_toaddmod_p->pdcp_Config->rlc_AM->statusReportRequired;
          drb_sn = PDCP_Config__rlc_UM__pdcp_SN_Size_len12bits; // default SN size
          rlc_type = RLC_MODE_AM;
        }

        if (drb_toaddmod_p->pdcp_Config->rlc_UM) {
          drb_sn = drb_toaddmod_p->pdcp_Config->rlc_UM->pdcp_SN_Size;
          rlc_type =RLC_MODE_UM;
        }

        switch (drb_toaddmod_p->pdcp_Config->headerCompression.present) {
          case PDCP_Config__headerCompression_PR_NOTHING:
          case PDCP_Config__headerCompression_PR_notUsed:
            header_compression_profile=0x0;
            break;

          case PDCP_Config__headerCompression_PR_rohc:

            // parse the struc and get the rohc profile
            if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0001) {
              header_compression_profile=0x0001;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0002) {
              header_compression_profile=0x0002;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0003) {
              header_compression_profile=0x0003;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0004) {
              header_compression_profile=0x0004;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0006) {
              header_compression_profile=0x0006;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0101) {
              header_compression_profile=0x0101;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0102) {
              header_compression_profile=0x0102;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0103) {
              header_compression_profile=0x0103;
            } else if(drb_toaddmod_p->pdcp_Config->headerCompression.choice.rohc.profiles.profile0x0104) {
              header_compression_profile=0x0104;
            } else {
              header_compression_profile=0x0;
              printf("unknown header compresion profile\n");
            }

            // set the applicable profile
            break;

          default:
            printf(PROTOCOL_PDCP_CTXT_FMT"[RB %ld] unknown drb_toaddmod->PDCP_Config->headerCompression->present \n",
                  PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p), drb_id);
            break;
        }

        pdcp_config_req_asn1 (
          ctxt_pP,
          pdcp_p,
          SRB_FLAG_NO,
          rlc_type,
          action,
          lc_id,
          mch_id,
          drb_id,
          drb_sn,
          drb_report,
          header_compression_profile,
          security_modeP,
          kRRCenc_pP,
          kRRCint_pP,
          kUPenc_pP);
      }
    }
  }

  if (drb2release_list_pP != NULL) {
    for (cnt=0; cnt<drb2release_list_pP->list.count; cnt++) {
      pdrb_id_p = drb2release_list_pP->list.array[cnt];
      drb_id =  *pdrb_id_p;
      key = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, ctxt_pP->enb_flag, drb_id, SRB_FLAG_NO);
      h_rc = hashtable_get(pdcp_coll_p, key, (void **)&pdcp_p);

      if (h_rc != HASH_TABLE_OK) {
        printf( PROTOCOL_CTXT_FMT" PDCP REMOVE FAILED drb_id %ld\n",
              PROTOCOL_CTXT_ARGS(ctxt_pP),
              drb_id);
        continue;
      }

      lc_id = pdcp_p->lcid;
      action = CONFIG_ACTION_REMOVE;
      pdcp_config_req_asn1 (
        ctxt_pP,
        pdcp_p,
        SRB_FLAG_NO,
        rlc_type,
        action,
        lc_id,
        mch_id,
        drb_id,
        0,
        0,
        0,
        security_modeP,
        kRRCenc_pP,
        kRRCint_pP,
        kUPenc_pP);
      h_rc = hashtable_remove(pdcp_coll_p, key);

      if ((defaultDRB != NULL) && (*defaultDRB == drb_id)) {
        // default DRB being removed. nevertheless this shouldn't happen as removing default DRB is not allowed in standard
        key_defaultDRB = PDCP_COLL_KEY_DEFAULT_DRB_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, ctxt_pP->enb_flag);
        h_defaultDRB_rc = hashtable_get(pdcp_coll_p, key_defaultDRB, (void **)&pdcp_p);

        if (h_defaultDRB_rc == HASH_TABLE_OK) {
          h_defaultDRB_rc = hashtable_remove(pdcp_coll_p, key_defaultDRB);
        } else {
          printf( PROTOCOL_CTXT_FMT" PDCP REMOVE FAILED default DRB\n", PROTOCOL_CTXT_ARGS(ctxt_pP));
        }
      } else {
        key_defaultDRB = HASH_TABLE_OK; // do not trigger any error handling if this is not a default DRB
      }
    }
  }

  if (pmch_InfoList_r9_pP != NULL) {
    for (i=0; i<pmch_InfoList_r9_pP->list.count; i++) {
      mbms_SessionInfoList_r9_p = &(pmch_InfoList_r9_pP->list.array[i]->mbms_SessionInfoList_r9);

      for (j=0; j<mbms_SessionInfoList_r9_p->list.count; j++) {
        MBMS_SessionInfo_p = mbms_SessionInfoList_r9_p->list.array[j];

        if (MBMS_SessionInfo_p->sessionId_r9)
          lc_id = MBMS_SessionInfo_p->sessionId_r9->buf[0];
        else
          lc_id = MBMS_SessionInfo_p->logicalChannelIdentity_r9;

        mch_id = MBMS_SessionInfo_p->tmgi_r9.serviceId_r9.buf[2]; //serviceId is 3-octet string
        //        mch_id = j;

        // can set the mch_id = i
        if (ctxt_pP->enb_flag) {
          drb_id =  (mch_id * maxSessionPerPMCH ) + lc_id ;//+ (maxLC_ID + 3)*MAX_MOBILES; // 1

          if (pdcp_mbms_array_eNB[ctxt_pP->module_id][mch_id][lc_id].instanciated_instance == TRUE) {
            action = CONFIG_ACTION_MBMS_MODIFY;
          } else {
            action = CONFIG_ACTION_MBMS_ADD;
          }
        } else {
          drb_id =  (mch_id * maxSessionPerPMCH ) + lc_id; // + (maxLC_ID + 3); // 15

          if (pdcp_mbms_array_ue[ctxt_pP->module_id][mch_id][lc_id].instanciated_instance == TRUE) {
            action = CONFIG_ACTION_MBMS_MODIFY;
          } else {
            action = CONFIG_ACTION_MBMS_ADD;
          }
        }

        printf("lc_id (%02ld) mch_id(%02x,%02x,%02x) drb_id(%ld) action(%d)\n",
              lc_id,
              MBMS_SessionInfo_p->tmgi_r9.serviceId_r9.buf[0],
              MBMS_SessionInfo_p->tmgi_r9.serviceId_r9.buf[1],
              MBMS_SessionInfo_p->tmgi_r9.serviceId_r9.buf[2],
              drb_id,
              action);
        pdcp_config_req_asn1 (
          ctxt_pP,
          NULL,  // unused for MBMS
          SRB_FLAG_NO,
          RLC_MODE_NONE,
          action,
          lc_id,
          mch_id,
          drb_id,
          0,   // unused for MBMS
          0,   // unused for MBMS
          0,   // unused for MBMS
          0,   // unused for MBMS
          NULL,  // unused for MBMS
          NULL,  // unused for MBMS
          NULL); // unused for MBMS
      }
    }
  }

  return 0;
}

//-----------------------------------------------------------------------------
boolean_t
pdcp_config_req_asn1 (
  const protocol_ctxt_t *const  ctxt_pP,
  pdcp_t          *const        pdcp_pP,
  const srb_flag_t              srb_flagP,
  const rlc_mode_t              rlc_modeP,
  const config_action_t         actionP,
  const uint16_t                lc_idP,
  const uint16_t                mch_idP,
  const rb_id_t                 rb_idP,
  const uint8_t                 rb_snP,
  const uint8_t                 rb_reportP,
  const uint16_t                header_compression_profileP,
  const uint8_t                 security_modeP,
  uint8_t         *const        kRRCenc_pP,
  uint8_t         *const        kRRCint_pP,
  uint8_t         *const        kUPenc_pP)
//-----------------------------------------------------------------------------
{
  switch (actionP) {
    case CONFIG_ACTION_ADD:
      DevAssert(pdcp_pP != NULL);

      if (ctxt_pP->enb_flag == ENB_FLAG_YES) {
        pdcp_pP->is_ue = FALSE;
        pdcp_add_UE(ctxt_pP);

        //pdcp_eNB_UE_instance_to_rnti[ctxtP->module_id] = ctxt_pP->rnti;
        //      pdcp_eNB_UE_instance_to_rnti[pdcp_eNB_UE_instance_to_rnti_index] = ctxt_pP->rnti;
        if( srb_flagP == SRB_FLAG_NO ) {
          for(int i = 0; i<MAX_MOBILES; i++) {
            if(pdcp_eNB_UE_instance_to_rnti[pdcp_eNB_UE_instance_to_rnti_index] == NOT_A_RNTI) {
              break;
            }

            pdcp_eNB_UE_instance_to_rnti_index = (pdcp_eNB_UE_instance_to_rnti_index + 1) % MAX_MOBILES;
          }

          pdcp_eNB_UE_instance_to_rnti[pdcp_eNB_UE_instance_to_rnti_index] = ctxt_pP->rnti;
          pdcp_eNB_UE_instance_to_rnti_index = (pdcp_eNB_UE_instance_to_rnti_index + 1) % MAX_MOBILES;
        }

        //pdcp_eNB_UE_instance_to_rnti_index = (pdcp_eNB_UE_instance_to_rnti_index + 1) % MAX_MOBILES;
      } else {
        pdcp_pP->is_ue = TRUE;
        pdcp_UE_UE_module_id_to_rnti[ctxt_pP->module_id] = ctxt_pP->rnti;
      }

      pdcp_pP->is_srb                     = (srb_flagP == SRB_FLAG_YES) ? TRUE : FALSE;
      pdcp_pP->lcid                       = lc_idP;
      pdcp_pP->rb_id                      = rb_idP;
      pdcp_pP->header_compression_profile = header_compression_profileP;
      pdcp_pP->status_report              = rb_reportP;

      if (rb_snP == PDCP_Config__rlc_UM__pdcp_SN_Size_len12bits) {
        pdcp_pP->seq_num_size = 12;
        pdcp_pP->maximum_pdcp_rx_sn = (1 << 12) - 1;
      } else if (rb_snP == PDCP_Config__rlc_UM__pdcp_SN_Size_len7bits) {
        pdcp_pP->seq_num_size = 7;
        pdcp_pP->maximum_pdcp_rx_sn = (1 << 7) - 1;
      } else {
        pdcp_pP->seq_num_size = 5;
        pdcp_pP->maximum_pdcp_rx_sn = (1 << 5) - 1;
      }

      pdcp_pP->rlc_mode                         = rlc_modeP;
      pdcp_pP->next_pdcp_tx_sn                  = 0;
      pdcp_pP->next_pdcp_rx_sn                  = 0;
      pdcp_pP->tx_hfn                           = 0;
      pdcp_pP->rx_hfn                           = 0;
      pdcp_pP->last_submitted_pdcp_rx_sn        = 4095;
      pdcp_pP->first_missing_pdu                = -1;
      printf(PROTOCOL_PDCP_CTXT_FMT" Action ADD  LCID %d (%s id %d) "
            "configured with SN size %d bits and RLC %s\n",
            PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_pP),
            lc_idP,
            (srb_flagP == SRB_FLAG_YES) ? "SRB" : "DRB",
            rb_idP,
            pdcp_pP->seq_num_size,
            (rlc_modeP == RLC_MODE_AM ) ? "AM" : (rlc_modeP == RLC_MODE_TM) ? "TM" : "UM");

      /* Setup security */
      if (security_modeP != 0xff) {
        pdcp_config_set_security(
          ctxt_pP,
          pdcp_pP,
          rb_idP,
          lc_idP,
          security_modeP,
          kRRCenc_pP,
          kRRCint_pP,
          kUPenc_pP);
      }

      break;

    case CONFIG_ACTION_MODIFY:
      DevAssert(pdcp_pP != NULL);
      pdcp_pP->header_compression_profile=header_compression_profileP;
      pdcp_pP->status_report = rb_reportP;
      pdcp_pP->rlc_mode = rlc_modeP;

      /* Setup security */
      if (security_modeP != 0xff) {
        pdcp_config_set_security(
          ctxt_pP,
          pdcp_pP,
          rb_idP,
          lc_idP,
          security_modeP,
          kRRCenc_pP,
          kRRCint_pP,
          kUPenc_pP);
      }

      if (rb_snP == PDCP_Config__rlc_UM__pdcp_SN_Size_len7bits) {
        pdcp_pP->seq_num_size = 7;
      } else if (rb_snP == PDCP_Config__rlc_UM__pdcp_SN_Size_len12bits) {
        pdcp_pP->seq_num_size = 12;
      } else {
        pdcp_pP->seq_num_size=5;
      }

      LOG_I(PDCP,PROTOCOL_PDCP_CTXT_FMT" Action MODIFY LCID %d "
            "RB id %d reconfigured with SN size %d and RLC %s \n",
            PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_pP),
            lc_idP,
            rb_idP,
            rb_snP,
            (rlc_modeP == RLC_MODE_AM) ? "AM" : (rlc_modeP == RLC_MODE_TM) ? "TM" : "UM");
      break;

    case CONFIG_ACTION_REMOVE:
      DevAssert(pdcp_pP != NULL);
      //#warning "TODO pdcp_module_id_to_rnti"
      //pdcp_module_id_to_rnti[ctxt_pP.module_id ][dst_id] = NOT_A_RNTI;
      printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_REMOVE LCID %d RBID %d configured\n",
            PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_pP),
            lc_idP,
            rb_idP);

      if (ctxt_pP->enb_flag == ENB_FLAG_YES) {
        // pdcp_remove_UE(ctxt_pP);
      }

      /* Security keys */
      if (pdcp_pP->kUPenc != NULL) {
        free(pdcp_pP->kUPenc);
      }

      if (pdcp_pP->kRRCint != NULL) {
        free(pdcp_pP->kRRCint);
      }

      if (pdcp_pP->kRRCenc != NULL) {
        free(pdcp_pP->kRRCenc);
      }

      memset(pdcp_pP, 0, sizeof(pdcp_t));
      break;

    case CONFIG_ACTION_MBMS_ADD:
    case CONFIG_ACTION_MBMS_MODIFY:
      LOG_D(PDCP," %s service_id/mch index %d, session_id/lcid %d, rbid %d configured\n",
            //PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_pP),
            actionP == CONFIG_ACTION_MBMS_ADD ? "CONFIG_ACTION_MBMS_ADD" : "CONFIG_ACTION_MBMS_MODIFY",
            mch_idP,
            lc_idP,
            rb_idP);

      if (ctxt_pP->enb_flag == ENB_FLAG_YES) {
        pdcp_mbms_array_eNB[ctxt_pP->module_id][mch_idP][lc_idP].instanciated_instance = TRUE ;
        pdcp_mbms_array_eNB[ctxt_pP->module_id][mch_idP][lc_idP].rb_id = rb_idP;
      } else {
        pdcp_mbms_array_ue[ctxt_pP->module_id][mch_idP][lc_idP].instanciated_instance = TRUE ;
        pdcp_mbms_array_ue[ctxt_pP->module_id][mch_idP][lc_idP].rb_id = rb_idP;
      }

      break;

    case CONFIG_ACTION_SET_SECURITY_MODE:
      pdcp_config_set_security(
        ctxt_pP,
        pdcp_pP,
        rb_idP,
        lc_idP,
        security_modeP,
        kRRCenc_pP,
        kRRCint_pP,
        kUPenc_pP);
      break;

    default:
      DevParam(actionP, ctxt_pP->module_id, ctxt_pP->rnti);
      break;
  }

  return 0;
}

//-----------------------------------------------------------------------------
void
pdcp_config_set_security(
  const protocol_ctxt_t *const  ctxt_pP,
  pdcp_t          *const pdcp_pP,
  const rb_id_t         rb_idP,
  const uint16_t        lc_idP,
  const uint8_t         security_modeP,
  uint8_t         *const kRRCenc,
  uint8_t         *const kRRCint,
  uint8_t         *const  kUPenc)
//-----------------------------------------------------------------------------
{
  DevAssert(pdcp_pP != NULL);

  if ((security_modeP >= 0) && (security_modeP <= 0x77)) {
    pdcp_pP->cipheringAlgorithm     = security_modeP & 0x0f;
    pdcp_pP->integrityProtAlgorithm = (security_modeP>>4) & 0xf;
    printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_SET_SECURITY_MODE: cipheringAlgorithm %d integrityProtAlgorithm %d\n",
          PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_pP),
          pdcp_pP->cipheringAlgorithm,
          pdcp_pP->integrityProtAlgorithm);
    pdcp_pP->kRRCenc = kRRCenc;
    pdcp_pP->kRRCint = kRRCint;
    pdcp_pP->kUPenc  = kUPenc;
    /* Activate security */
    pdcp_pP->security_activated = 1;
    MSC_LOG_EVENT(
      (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_PDCP_ENB:MSC_PDCP_UE,
      "0 Set security ciph %X integ %x UE %"PRIx16" ",
      pdcp_pP->cipheringAlgorithm,
      pdcp_pP->integrityProtAlgorithm,
      ctxt_pP->rnti);
  } else {
    MSC_LOG_EVENT(
      (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_PDCP_ENB:MSC_PDCP_UE,
      "0 Set security failed UE %"PRIx16" ",
      ctxt_pP->rnti);
    printf(PROTOCOL_PDCP_CTXT_FMT"  bad security mode %d",
          PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_pP),
          security_modeP);
  }
}

//-----------------------------------------------------------------------------
void
rrc_pdcp_config_req (
  const protocol_ctxt_t *const  ctxt_pP,
  const srb_flag_t srb_flagP,
  const uint32_t actionP,
  const rb_id_t rb_idP,
  const uint8_t security_modeP)
//-----------------------------------------------------------------------------
{
  pdcp_t *pdcp_p = NULL;
  hash_key_t       key           = PDCP_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, ctxt_pP->enb_flag, rb_idP, srb_flagP);
  hashtable_rc_t   h_rc;
  h_rc = hashtable_get(pdcp_coll_p, key, (void **)&pdcp_p);

  if (h_rc == HASH_TABLE_OK) {
    /*
     * Initialize sequence number state variables of relevant PDCP entity
     */
    switch (actionP) {
      case CONFIG_ACTION_ADD:
        pdcp_p->is_srb = srb_flagP;
        pdcp_p->rb_id  = rb_idP;

        if (ctxt_pP->enb_flag == ENB_FLAG_NO) {
          pdcp_p->is_ue = TRUE;
          pdcp_UE_UE_module_id_to_rnti[ctxt_pP->module_id] = ctxt_pP->rnti;
        } else {
          pdcp_p->is_ue = FALSE;
        }

        pdcp_p->next_pdcp_tx_sn = 0;
        pdcp_p->next_pdcp_rx_sn = 0;
        pdcp_p->tx_hfn = 0;
        pdcp_p->rx_hfn = 0;
        /* SN of the last PDCP SDU delivered to upper layers */
        pdcp_p->last_submitted_pdcp_rx_sn = 4095;

        if (rb_idP < DTCH) { // SRB
          pdcp_p->seq_num_size = 5;
        } else { // DRB
          pdcp_p->seq_num_size = 12;
        }

        pdcp_p->first_missing_pdu = -1;
        LOG_D(PDCP,PROTOCOL_PDCP_CTXT_FMT" Config request : Action ADD:  radio bearer id %d (already added) configured\n",
              PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p),
              rb_idP);
        break;

      case CONFIG_ACTION_MODIFY:
        break;

      case CONFIG_ACTION_REMOVE:
        printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_REMOVE: radio bearer id %d configured\n",
              PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p),
              rb_idP);
        pdcp_p->next_pdcp_tx_sn = 0;
        pdcp_p->next_pdcp_rx_sn = 0;
        pdcp_p->tx_hfn = 0;
        pdcp_p->rx_hfn = 0;
        pdcp_p->last_submitted_pdcp_rx_sn = 4095;
        pdcp_p->seq_num_size = 0;
        pdcp_p->first_missing_pdu = -1;
        pdcp_p->security_activated = 0;
        h_rc = hashtable_remove(pdcp_coll_p, key);
        break;

      case CONFIG_ACTION_SET_SECURITY_MODE:
        if ((security_modeP >= 0) && (security_modeP <= 0x77)) {
          pdcp_p->cipheringAlgorithm= security_modeP & 0x0f;
          pdcp_p->integrityProtAlgorithm = (security_modeP>>4) & 0xf;
          printf(PROTOCOL_PDCP_CTXT_FMT" CONFIG_ACTION_SET_SECURITY_MODE: cipheringAlgorithm %d integrityProtAlgorithm %d\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p),
                pdcp_p->cipheringAlgorithm,
                pdcp_p->integrityProtAlgorithm );
        } else {
          printf(PROTOCOL_PDCP_CTXT_FMT" bad security mode %d", PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p), security_modeP);
        }

        break;

      default:
        DevParam(actionP, ctxt_pP->module_id, ctxt_pP->rnti);
        break;
    }
  } else {
    switch (actionP) {
      case CONFIG_ACTION_ADD:
        pdcp_p = calloc(1, sizeof(pdcp_t));
        h_rc = hashtable_insert(pdcp_coll_p, key, pdcp_p);

        if (h_rc != HASH_TABLE_OK) {
          printf( PROTOCOL_PDCP_CTXT_FMT" PDCP ADD FAILED\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP, pdcp_p));
          free(pdcp_p);
        } else {
          pdcp_p->is_srb = srb_flagP;
          pdcp_p->rb_id  = rb_idP;

          if (ctxt_pP->enb_flag == ENB_FLAG_NO) {
            pdcp_p->is_ue = TRUE;
            pdcp_UE_UE_module_id_to_rnti[ctxt_pP->module_id] = ctxt_pP->rnti;
          } else {
            pdcp_p->is_ue = FALSE;
          }

          pdcp_p->next_pdcp_tx_sn = 0;
          pdcp_p->next_pdcp_rx_sn = 0;
          pdcp_p->tx_hfn = 0;
          pdcp_p->rx_hfn = 0;
          /* SN of the last PDCP SDU delivered to upper layers */
          pdcp_p->last_submitted_pdcp_rx_sn = 4095;

          if (rb_idP < DTCH) { // SRB
            pdcp_p->seq_num_size = 5;
          } else { // DRB
            pdcp_p->seq_num_size = 12;
          }

          pdcp_p->first_missing_pdu = -1;
          LOG_D(PDCP,PROTOCOL_PDCP_CTXT_FMT" Inserting PDCP instance in collection key 0x%"PRIx64"\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p), key);
          LOG_D(PDCP,PROTOCOL_PDCP_CTXT_FMT" Config request : Action ADD:  radio bearer id %d configured\n",
                PROTOCOL_PDCP_CTXT_ARGS(ctxt_pP,pdcp_p),
                rb_idP);
        }

        break;

      case CONFIG_ACTION_REMOVE:
        printf(PROTOCOL_CTXT_FMT" CONFIG_REQ PDCP CONFIG_ACTION_REMOVE PDCP instance not found\n",
              PROTOCOL_CTXT_ARGS(ctxt_pP));
        break;

      default:
        printf( PROTOCOL_CTXT_FMT" CONFIG_REQ PDCP NOT FOUND\n",
              PROTOCOL_CTXT_ARGS(ctxt_pP));
    }
  }
}
#endif

pdcp_data_ind_func_t get_pdcp_data_ind_func()
{
	return pdcp_params.pdcp_data_ind_func;
}

void pdcp_set_rlc_data_req_func(send_rlc_data_req_func_t send_rlc_data_req)
{
	pdcp_params.send_rlc_data_req_func = send_rlc_data_req;
}

void pdcp_set_pdcp_data_ind_func(pdcp_data_ind_func_t pdcp_data_ind)
{
	pdcp_params.pdcp_data_ind_func = pdcp_data_ind;
}

uint64_t pdcp_module_init( uint64_t pdcp_optmask )
{
  /* temporary enforce netlink when UE_NAS_USE_TUN is set,
     this is while switching from noS1 as build option
     to noS1 as config option                               */
  if ( pdcp_optmask & UE_NAS_USE_TUN_BIT) {
    pdcp_params.optmask = pdcp_params.optmask | PDCP_USE_NETLINK_BIT ;
  }

  pdcp_params.optmask = pdcp_params.optmask | pdcp_optmask ;
  printf("pdcp init,%s %s\n", ((LINK_ENB_PDCP_TO_GTPV1U)?"usegtp":""), ((PDCP_USE_NETLINK)?"usenetlink":""));

//  if (PDCP_USE_NETLINK) {
//    nas_getparams();
//
//    if(UE_NAS_USE_TUN) {
//      int num_if = (NFAPI_MODE == NFAPI_UE_STUB_PNF || IS_SOFTMODEM_SIML1 )?MAX_NUMBER_NETIF:1;
//      netlink_init_tun("ue",num_if);
//      printf("UE pdcp will use tun interface\n");
//    } else if(ENB_NAS_USE_TUN) {
//      netlink_init_tun("enb",1);
//      nas_config(1, 1, 1, "enb");
//      printf("ENB pdcp will use tun interface\n");
//    } else {
//      printf("pdcp will use kernel modules\n");
//      netlink_init();
//    }
//  }
  return pdcp_params.optmask ;
}


//-----------------------------------------------------------------------------
void pdcp_free (void *pdcp_pP)
//-----------------------------------------------------------------------------
{
	pdcp_t *pdcp_p = (pdcp_t *)pdcp_pP;

	if (pdcp_p != NULL) {
		if (pdcp_p->kUPenc != NULL) {
			free(pdcp_p->kUPenc);
		}

		if (pdcp_p->kRRCint != NULL) {
			free(pdcp_p->kRRCint);
		}

		if (pdcp_p->kRRCenc != NULL) {
			free(pdcp_p->kRRCenc);
		}

		memset(pdcp_pP, 0, sizeof(pdcp_t));
		free(pdcp_pP);
	}
}

//-----------------------------------------------------------------------------
void pdcp_module_cleanup (void)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
void pdcp_layer_init(void)
//-----------------------------------------------------------------------------
{
  module_id_t       instance;
  int i,j;
  mbms_session_id_t session_id;
  mbms_service_id_t service_id;
  /*
   * Initialize SDU list
   */
  list_init(&pdcp_sdu_list, NULL);
  pdcp_coll_p = hashtable_create ((maxLC_ID + 2) * MAX_MOBILES, NULL, pdcp_free);
  AssertFatal(pdcp_coll_p != NULL, "UNRECOVERABLE error, PDCP hashtable_create failed");

  for (instance = 0; instance < MAX_MOBILES; instance++) {
//    for (service_id = 0; service_id < maxServiceCount; service_id++) {
//      for (session_id = 0; session_id < maxSessionPerPMCH; session_id++) {
//        memset(&pdcp_mbms_array_ue[instance][service_id][session_id], 0, sizeof(pdcp_mbms_t));
//      }
//    }

    pdcp_eNB_UE_instance_to_rnti[instance] = NOT_A_RNTI;
  }

  pdcp_eNB_UE_instance_to_rnti_index = 0;

//  for (instance = 0; instance < NUMBER_OF_eNB_MAX; instance++) {
//    for (service_id = 0; service_id < maxServiceCount; service_id++) {
//      for (session_id = 0; session_id < maxSessionPerPMCH; session_id++) {
//        memset(&pdcp_mbms_array_eNB[instance][service_id][session_id], 0, sizeof(pdcp_mbms_t));
//      }
//    }
//  }

#ifdef MBMS_MULTICAST_OUT
  mbms_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

  if (mbms_socket == -1)
    printf("Could not create RAW socket, MBMS packets will not be put to the network\n");

#endif
  printf("PDCP layer has been initialized\n");
  pdcp_output_sdu_bytes_to_write=0;
  pdcp_output_header_bytes_to_write=0;
  pdcp_input_sdu_remaining_size_to_read=0;
//  memset(pdcp_enb, 0, sizeof(pdcp_enb_t));
  memset(Pdcp_stats_tx_window_ms, 0, sizeof(Pdcp_stats_tx_window_ms));
  memset(Pdcp_stats_rx_window_ms, 0, sizeof(Pdcp_stats_rx_window_ms));

//  for (i = 0; i < MAX_eNB; i++) {
    for (j = 0; j < MAX_MOBILES; j++) {
      Pdcp_stats_tx_window_ms[j]=100;
      Pdcp_stats_rx_window_ms[j]=100;
    }
//  }

  memset(Pdcp_stats_tx, 0, sizeof(Pdcp_stats_tx));
  memset(Pdcp_stats_tx_w, 0, sizeof(Pdcp_stats_tx_w));
  memset(Pdcp_stats_tx_tmp_w, 0, sizeof(Pdcp_stats_tx_tmp_w));
  memset(Pdcp_stats_tx_bytes, 0, sizeof(Pdcp_stats_tx_bytes));
  memset(Pdcp_stats_tx_bytes_w, 0, sizeof(Pdcp_stats_tx_bytes_w));
  memset(Pdcp_stats_tx_bytes_tmp_w, 0, sizeof(Pdcp_stats_tx_bytes_tmp_w));
  memset(Pdcp_stats_tx_sn, 0, sizeof(Pdcp_stats_tx_sn));
  memset(Pdcp_stats_tx_throughput_w, 0, sizeof(Pdcp_stats_tx_throughput_w));
  memset(Pdcp_stats_tx_aiat, 0, sizeof(Pdcp_stats_tx_aiat));
  memset(Pdcp_stats_tx_iat, 0, sizeof(Pdcp_stats_tx_iat));
  memset(Pdcp_stats_rx, 0, sizeof(Pdcp_stats_rx));
  memset(Pdcp_stats_rx_w, 0, sizeof(Pdcp_stats_rx_w));
  memset(Pdcp_stats_rx_tmp_w, 0, sizeof(Pdcp_stats_rx_tmp_w));
  memset(Pdcp_stats_rx_bytes, 0, sizeof(Pdcp_stats_rx_bytes));
  memset(Pdcp_stats_rx_bytes_w, 0, sizeof(Pdcp_stats_rx_bytes_w));
  memset(Pdcp_stats_rx_bytes_tmp_w, 0, sizeof(Pdcp_stats_rx_bytes_tmp_w));
  memset(Pdcp_stats_rx_sn, 0, sizeof(Pdcp_stats_rx_sn));
  memset(Pdcp_stats_rx_goodput_w, 0, sizeof(Pdcp_stats_rx_goodput_w));
  memset(Pdcp_stats_rx_aiat, 0, sizeof(Pdcp_stats_rx_aiat));
  memset(Pdcp_stats_rx_iat, 0, sizeof(Pdcp_stats_rx_iat));
  memset(Pdcp_stats_rx_outoforder, 0, sizeof(Pdcp_stats_rx_outoforder));
}

//-----------------------------------------------------------------------------
void pdcp_layer_cleanup (void)
//-----------------------------------------------------------------------------
{
  list_free (&pdcp_sdu_list);
  hashtable_destroy(&pdcp_coll_p);
#ifdef MBMS_MULTICAST_OUT

  if(mbms_socket != -1) {
    close(mbms_socket);
    mbms_socket = -1;
  }

#endif
}
