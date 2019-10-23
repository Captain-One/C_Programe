#define RLC_UM_MODULE 1
#define RLC_UM_C 1
//-----------------------------------------------------------------------------
#include "platform_types.h"
#include "platform_constants.h"
//-----------------------------------------------------------------------------
#include "assertions.h"
#include "rlc_um.h"
#include "list.h"
#include "rlc_primitives.h"
#include "mac_extern.h"

//#include "rlc_um_very_simple_test.h"

//-----------------------------------------------------------------------------
void rlc_um_stat_req(rlc_um_entity_t *rlc_pP,
							unsigned int* stat_tx_pdcp_sdu,
							unsigned int* stat_tx_pdcp_bytes,
							unsigned int* stat_tx_pdcp_sdu_discarded,
							unsigned int* stat_tx_pdcp_bytes_discarded,
							unsigned int* stat_tx_data_pdu,
							unsigned int* stat_tx_data_bytes,
							unsigned int* stat_rx_pdcp_sdu,
							unsigned int* stat_rx_pdcp_bytes,
							unsigned int* stat_rx_data_pdus_duplicate,
							unsigned int* stat_rx_data_bytes_duplicate,
							unsigned int* stat_rx_data_pdu,
							unsigned int* stat_rx_data_bytes,
							unsigned int* stat_rx_data_pdu_dropped,
							unsigned int* stat_rx_data_bytes_dropped,
							unsigned int* stat_rx_data_pdu_out_of_window,
							unsigned int* stat_rx_data_bytes_out_of_window,
							unsigned int* stat_timer_reordering_timed_out)
{
	*stat_tx_pdcp_sdu                     = rlc_pP->stat_tx_pdcp_sdu;
	*stat_tx_pdcp_bytes                   = rlc_pP->stat_tx_pdcp_bytes;
	*stat_tx_pdcp_sdu_discarded           = rlc_pP->stat_tx_pdcp_sdu_discarded;
	*stat_tx_pdcp_bytes_discarded         = rlc_pP->stat_tx_pdcp_bytes_discarded;
	*stat_tx_data_pdu                     = rlc_pP->stat_tx_data_pdu;
	*stat_tx_data_bytes                   = rlc_pP->stat_tx_data_bytes;
	*stat_rx_pdcp_sdu                     = rlc_pP->stat_rx_pdcp_sdu;
	*stat_rx_pdcp_bytes                   = rlc_pP->stat_rx_pdcp_bytes;
	*stat_rx_data_pdus_duplicate          = rlc_pP->stat_rx_data_pdus_duplicate;
	*stat_rx_data_bytes_duplicate         = rlc_pP->stat_rx_data_bytes_duplicate;
	*stat_rx_data_pdu                     = rlc_pP->stat_rx_data_pdu;
	*stat_rx_data_bytes                   = rlc_pP->stat_rx_data_bytes;
	*stat_rx_data_pdu_dropped             = rlc_pP->stat_rx_data_pdu_dropped;
	*stat_rx_data_bytes_dropped           = rlc_pP->stat_rx_data_bytes_dropped;
	*stat_rx_data_pdu_out_of_window       = rlc_pP->stat_rx_data_pdu_out_of_window;
	*stat_rx_data_bytes_out_of_window     = rlc_pP->stat_rx_data_bytes_out_of_window;
	*stat_timer_reordering_timed_out      = rlc_pP->stat_timer_reordering_timed_out;
}
//-----------------------------------------------------------------------------
uint32_t rlc_um_get_buffer_occupancy (rlc_um_entity_t *rlc_pP)
{
	if (rlc_pP->buffer_occupancy > 0) {
		return rlc_pP->buffer_occupancy;
	} else {
		return 0;
	}
}
//-----------------------------------------------------------------------------
void rlc_um_get_pdus(const protocol_ctxt_t* const ctxt_pP, void *argP)
{
	rlc_um_entity_t *rlc_p = (rlc_um_entity_t *) argP;

	switch (rlc_p->protocol_state) {
	case RLC_NULL_STATE:
		break;
	case RLC_DATA_TRANSFER_READY_STATE:
		rlc_um_segment(ctxt_pP, rlc_p);
		break;
	case RLC_LOCAL_SUSPEND_STATE:
		break;
	default:
		printf(" MAC_DATA_REQ UNKNOWN PROTOCOL STATE %02X hex\n", rlc_p->protocol_state);
	}
}


//-----------------------------------------------------------------------------
void rlc_um_rx (const protocol_ctxt_t* const ctxt_pP, void *argP, struct mac_data_ind data_indP)
{
	rlc_um_entity_t    *l_rlc_p = (rlc_um_entity_t *) argP;

	switch (l_rlc_p->protocol_state) {
	case RLC_NULL_STATE:
		printf(" ERROR MAC_DATA_IND IN RLC_NULL_STATE\n");

		list_free (&data_indP.data);
		break;
	case RLC_DATA_TRANSFER_READY_STATE:
		data_indP.tb_size = data_indP.tb_size >> 3;

		rlc_um_receive (ctxt_pP, l_rlc_p, data_indP);
		break;

	case RLC_LOCAL_SUSPEND_STATE:
		printf(" RLC_LOCAL_SUSPEND_STATE\n");

		list_free (&data_indP.data);
		break;

	default:
		printf(" TX UNKNOWN PROTOCOL STATE %02X hex\n", l_rlc_p->protocol_state);
		list_free (&data_indP.data);
		break;
	}
}

//-----------------------------------------------------------------------------
struct mac_status_resp rlc_um_mac_status_indication (const protocol_ctxt_t* const ctxt_pP,
																void *rlc_pP, uint16_t tbs_sizeP,
																struct mac_status_ind tx_statusP,
																const eNB_flag_t enb_flagP)
{
	struct mac_status_resp status_resp;
	uint16_t  sdu_size = 0;
	uint16_t  sdu_remaining_size = 0;
	int32_t diff_time=0;
	rlc_um_entity_t   *rlc_p = NULL;
	mem_block_t       *mb_p = NULL;

	status_resp.buffer_occupancy_in_pdus         = 0;
	status_resp.buffer_occupancy_in_bytes        = 0;
	status_resp.head_sdu_remaining_size_to_send  = 0;
	status_resp.head_sdu_creation_time           = 0;
	status_resp.head_sdu_is_segmented            = 0;

	if (rlc_pP) {
		rlc_p = (rlc_um_entity_t *) rlc_pP;
		status_resp.rlc_info.rlc_protocol_state      = rlc_p->protocol_state;

		rlc_um_check_timer_dar_time_out(ctxt_pP, rlc_p);

		rlc_p->nb_bytes_requested_by_mac = tbs_sizeP;

		status_resp.buffer_occupancy_in_bytes = rlc_um_get_buffer_occupancy (rlc_p);

		if ((status_resp.buffer_occupancy_in_bytes > 0) && ((mb_p = list_get_head(&rlc_p->input_sdus)) != NULL)) {

			if (enb_flagP == ENB_FLAG_YES) {
				/* For eNB: add minimum RLC UM header size for the scheduler */
				/* For UE : RLC header part is not taken into account for BSR reporting (cf 38.321) */
				status_resp.buffer_occupancy_in_bytes += rlc_p->tx_header_min_length_in_bytes;
			}
			status_resp.buffer_occupancy_in_pdus = rlc_p->input_sdus.nb_elements;

			diff_time =   ctxt_pP->frame - ((struct rlc_um_tx_sdu_management *)mb_p->data)->sdu_creation_time;
			status_resp.head_sdu_creation_time = (diff_time > 0 ) ? (uint32_t) diff_time :  (uint32_t)(0xffffffff - diff_time + ctxt_pP->frame) ;
			//msg("rlc_p status for ctxt_pP->frame %d diff time %d resp %d\n", ctxt_pP->frame, diff_time,status_resp.head_sdu_creation_time) ;

			sdu_size            = ((struct rlc_um_tx_sdu_management *) mb_p->data)->sdu_size;
			sdu_remaining_size  = ((struct rlc_um_tx_sdu_management *) mb_p->data)->sdu_remaining_size;

			status_resp.head_sdu_remaining_size_to_send = sdu_remaining_size;

			if (sdu_size == sdu_remaining_size)  {
				status_resp.head_sdu_is_segmented = 0;
			} else {
				status_resp.head_sdu_is_segmented = 1;
			}

		}

		status_resp.rlc_info.rlc_protocol_state = ((rlc_um_entity_t *) rlc_pP)->protocol_state;
	} else {
		printf("[RLC] rlc_um_mac_status_indication RLC NULL!!!\n");
	}

	return status_resp;
}

//-----------------------------------------------------------------------------
void rlc_um_set_nb_bytes_requested_by_mac(void * rlc_pP, const tb_size_t tb_sizeP)
{
	((rlc_um_entity_t *) rlc_pP)->nb_bytes_requested_by_mac = tb_sizeP;
}

//-----------------------------------------------------------------------------
struct mac_data_req rlc_um_mac_data_request (const protocol_ctxt_t* const ctxt_pP, void *rlc_pP,const eNB_flag_t  enb_flagP)
{
	struct mac_data_req data_req;
	int16_t tb_size_in_bytes;
	mem_block_t        *tb_p;
	rlc_um_entity_t *l_rlc_p = (rlc_um_entity_t *) rlc_pP;

	rlc_um_get_pdus(ctxt_pP, l_rlc_p);

	list_init (&data_req.data, NULL);
	list2_add_list (&l_rlc_p->pdus_to_mac_layer, &data_req.data);


	if (enb_flagP) {
//		redundant in UE MAC Tx processing and not used in eNB scheduler ...
		data_req.buffer_occupancy_in_bytes = rlc_um_get_buffer_occupancy (l_rlc_p);

		if (data_req.buffer_occupancy_in_bytes > 0) {
			data_req.buffer_occupancy_in_bytes += l_rlc_p->tx_header_min_length_in_bytes;
		}
	}

	data_req.rlc_info.rlc_protocol_state = l_rlc_p->protocol_state;

	if (data_req.data.nb_elements > 0) {
		tb_p = data_req.data.head;

		while (tb_p != NULL) {
			tb_size_in_bytes   = ((struct mac_tb_req *) (tb_p->data))->tb_size;

			printf(" MAC_DATA_REQUEST  TB SIZE %u\n", ((struct mac_tb_req *) (tb_p->data))->tb_size);

			l_rlc_p->stat_tx_data_pdu += 1;
			l_rlc_p->stat_tx_data_bytes += tb_size_in_bytes;

			AssertFatal( tb_size_in_bytes > 0 , "RLC UM PDU LENGTH %d", tb_size_in_bytes);
			if(tb_size_in_bytes <= 0) {
				printf("RLC UM PDU LENGTH %d\n", tb_size_in_bytes);
				tb_p = tb_p->next;
				continue;
			}
			tb_p = tb_p->next;
		}
	}

	return data_req;
}

//-----------------------------------------------------------------------------
void rlc_um_mac_data_indication (const protocol_ctxt_t* const ctxt_pP, void *rlc_pP, struct mac_data_ind data_indP)
{
	rlc_um_rx (ctxt_pP, rlc_pP, data_indP);
	rlc_um_check_timer_dar_time_out(ctxt_pP, rlc_pP);
}

//-----------------------------------------------------------------------------
void rlc_um_data_req (const protocol_ctxt_t* const ctxt_pP, void *rlc_pP, mem_block_t *sdu_pP)
{
	rlc_um_entity_t *rlc_p = (rlc_um_entity_t *) rlc_pP;

	printf(PROTOCOL_RLC_UM_CTXT_FMT" RLC_UM_DATA_REQ size %d Bytes, BO %d , NB SDU %d\n",
				PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP,rlc_p), ((struct rlc_um_data_req *) (sdu_pP->data))->data_size,
				rlc_p->buffer_occupancy, rlc_p->input_sdus.nb_elements);

	// IMPORTANT : do not change order of affectations
	((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->sdu_size = ((struct rlc_um_data_req *) (sdu_pP->data))->data_size;
	//rlc_p->nb_sdu += 1;
	((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->first_byte =
			(uint8_t*)&sdu_pP->data[sizeof (struct rlc_um_data_req_alloc)];

	((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->sdu_remaining_size =
			((struct rlc_um_tx_sdu_management *)(sdu_pP->data))->sdu_size;

	((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->sdu_segmented_size = 0;

	((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->sdu_creation_time = ctxt_pP->frame;
	//rlc_p->next_sdu_index = (rlc_p->next_sdu_index + 1) % rlc_p->size_input_sdus_buffer;

	rlc_p->stat_tx_pdcp_sdu += 1;
	rlc_p->stat_tx_pdcp_bytes += ((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->sdu_size;


//	RLC_UM_MUTEX_LOCK(&rlc_p->lock_input_sdus, ctxt_pP, rlc_p);
	rlc_p->buffer_occupancy += ((struct rlc_um_tx_sdu_management *) (sdu_pP->data))->sdu_size;

	list_add_tail_eurecom(sdu_pP, &rlc_p->input_sdus);
//	RLC_UM_MUTEX_UNLOCK(&rlc_p->lock_input_sdus);
}
