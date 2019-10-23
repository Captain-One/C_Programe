#define RLC_AM_MODULE 1
#define RLC_AM_SEGMENT_C 1
//-----------------------------------------------------------------------------
#include <assert.h>
//-----------------------------------------------------------------------------
#include "platform_types.h"
//-----------------------------------------------------------------------------

#include "list.h"
#include "rlc_am.h"
#include "mac_extern.h"


//-----------------------------------------------------------------------------
void rlc_am_pdu_polling(
	const protocol_ctxt_t* const  ctxt_pP,
	rlc_am_entity_t *const rlc_pP,
	uint8_t *const pdu_pP,
	const int16_t payload_sizeP,
	boolean_t is_new_pdu)
{
//	5.2.2 Polling
//	An AM RLC entity can poll its peer AM RLC entity in order to trigger STATUS reporting at the peer AM RLC entity.
//	5.2.2.1 Transmission of a AMD PDU or AMD PDU segment
//	Upon assembly of a new AMD PDU, the transmitting side of an AM RLC entity shall:
//	   - increment PDU_WITHOUT_POLL by one;
//	   - increment BYTE_WITHOUT_POLL by every new byte of Data field element that it maps to the Data field of
//		 the RLC data PDU;
//	   - if PDU_WITHOUT_POLL >= pollPDU; or
//	   - if BYTE_WITHOUT_POLL >= pollByte;
//		   -include a poll in the RLC data PDU as described below.
//	Upon assembly of an AMD PDU or AMD PDU segment, the transmitting side of an AM RLC entity shall:
//	   - if both the transmission buffer and the retransmission buffer becomes empty (excluding transmitted RLC data
//		 PDU awaiting for acknowledgements) after the transmission of the RLC data PDU; or
//	   - if no new RLC data PDU can be transmitted after the transmission of the RLC data PDU (e.g. due to window
//		 stalling);
//		   - include a poll in the RLC data PDU as described below.
//	To include a poll in a RLC data PDU, the transmitting side of an AM RLC entity shall:
//	   - set the P field of the RLC data PDU to "1";
//	   - set PDU_WITHOUT_POLL to 0;
//	   - set BYTE_WITHOUT_POLL to 0;
//	After delivering a RLC data PDU including a poll to lower layer and after incrementing of VT(S) if necessary, the
//	transmitting side of an AM RLC entity shall:
//	   - set POLL_SN to VT(S) – 1;
//	   - if t-PollRetransmit is not running:
//		   - start t-PollRetransmit;
//	   - else:
//		   - restart t-PollRetransmit;

	if (is_new_pdu) {
		if (rlc_pP->poll_pdu != RLC_AM_POLL_PDU_INFINITE) {
			rlc_pP->c_pdu_without_poll     += 1;
		}

		if (rlc_pP->poll_byte != RLC_AM_POLL_BYTE_INFINITE) {
			rlc_pP->c_byte_without_poll    += payload_sizeP;
		}
	}

	if (((is_new_pdu) && ((rlc_pP->c_pdu_without_poll >= rlc_pP->poll_pdu) ||
			(rlc_pP->c_byte_without_poll >= rlc_pP->poll_byte))) ||
			((rlc_pP->sdu_buffer_occupancy == 0) && (rlc_pP->retrans_num_bytes_to_retransmit == 0)) ||
			(rlc_pP->TX_Next_Ack == rlc_pP->TX_Next) ||
			(rlc_pP->force_poll == TRUE)) {

		rlc_pP->force_poll = FALSE;

		if ((is_new_pdu) && (rlc_pP->c_pdu_without_poll >= rlc_pP->poll_pdu)) {
			printf(PROTOCOL_RLC_AM_CTXT_FMT"[POLL] SET POLL BECAUSE TX NUM PDU THRESHOLD %d  HAS BEEN REACHED\n",
					PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP), rlc_pP->poll_pdu);
		}

		if ((is_new_pdu) && (rlc_pP->c_byte_without_poll >= rlc_pP->poll_byte)) {
			printf(PROTOCOL_RLC_AM_CTXT_FMT"[POLL] SET POLL BECAUSE TX NUM BYTES THRESHOLD %d  HAS BEEN REACHED\n",
					PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP), rlc_pP->poll_byte);
		}

		if ((rlc_pP->sdu_buffer_occupancy == 0) && (rlc_pP->retrans_num_bytes_to_retransmit == 0)) {
			printf(PROTOCOL_RLC_AM_CTXT_FMT"[POLL] SET POLL BECAUSE TX BUFFERS ARE EMPTY\n",
			            PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP));
		}

		if (rlc_pP->TX_Next == rlc_pP->TX_Next_Ack) {
			printf(PROTOCOL_RLC_AM_CTXT_FMT"[POLL] SET POLL BECAUSE OF WINDOW STALLING\n",
			            PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP));
		}

		RLC_AM_PDU_SET_POLL(*pdu_pP);
		rlc_pP->c_pdu_without_poll     = 0;
		rlc_pP->c_byte_without_poll    = 0;

		rlc_pP->poll_sn = (rlc_pP->TX_Next - 1) % rlc_pP->tx_sn_modulo;

		rlc_am_start_timer_poll_retransmit(ctxt_pP, rlc_pP);
	} else {
//		Need to clear poll bit as it may be a copy(retransmission case) of the original RLC PDU which was containing a poll
		RLC_AM_PDU_CLEAR_POLL(*pdu_pP);
	}
}
//-----------------------------------------------------------------------------
void rlc_am_segment(const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t *const rlc_pP)
{
	list2_t				pdus;
	sdu_size_t				pdu_remaining_size      = 0;
	sdu_size_t				test_pdu_remaining_size = 0;

	sdu_size_t                       nb_bytes_to_transmit = rlc_pP->nb_bytes_requested_by_mac;
	rlc_am_pdu_sn_10_t              *pdu_p        = NULL;
	struct mac_tb_req               *pdu_tb_req_p = NULL;
	mem_block_t                     *pdu_mem_p    = NULL;
	unsigned char                   *data         = NULL;
	unsigned char                   *data_sdu_p   = NULL;
	rlc_am_e_li_t                   *e_li_p       = NULL;
	rlc_am_tx_sdu_management_t      *sdu_mngt_p   = NULL;
	rlc_am_tx_data_pdu_management_t *pdu_mngt_p   = NULL;

	sdu_size_t         li_length_in_bytes         = 0;
	sdu_size_t         test_li_length_in_bytes    = 0;
	sdu_size_t         test_remaining_size_to_substract= 0;
	unsigned int       test_remaining_num_li_to_substract = 0;
	unsigned int       continue_fill_pdu_with_sdu         = 0;
	unsigned int       num_fill_sdu                       = 0;
	unsigned int       test_num_li                        = 0;
	unsigned int       fill_num_li                        = 0;
	unsigned int       sdu_buffer_index                   = 0;
	sdu_size_t         data_pdu_size                      = 0;

	unsigned int       fi_first_byte_pdu_is_first_byte_sdu = 0;
	unsigned int       fi_last_byte_pdu_is_last_byte_sdu   = 0;
	unsigned int       fi                                  = 0;
	signed int         max_li_overhead                     = 0;
	mem_block_t        *sdu_in_buffer = NULL;
	int16_t				headerL = 0;
	int8_t si = 0;
	rlc_am_header_t* header_pP = NULL;

//	printf(PROTOCOL_RLC_AM_CTXT_FMT"[SEGMENT] rlc_pP->current_sdu_index %d rlc_pP->next_sdu_index %d rlc_pP->input_sdus[rlc_pP->current_sdu_index].mem_block %p sdu_buffer_occupancy %d\n",
//			PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP),
//			rlc_pP->current_sdu_index, rlc_pP->next_sdu_index,
//			rlc_pP->input_sdus[rlc_pP->current_sdu_index].mem_block, rlc_pP->sdu_buffer_occupancy);

	if (rlc_pP->sdu_buffer_occupancy <= 0) {
		return;
	}

	list2_init(&pdus, NULL);    // param string identifying the list is NULL
	pdu_mem_p = NULL;

//	RLC_AM_MUTEX_LOCK(&rlc_pP->lock_input_sdus, ctxt_pP, rlc_pP);

	while((sdu_in_buffer = list2_get_head(&rlc_pP->input_sdus)) && (nb_bytes_to_transmit > 0)) {
		printf(PROTOCOL_RLC_AM_CTXT_FMT"[SEGMENT] nb_bytes_to_transmit %d BO %d\n",
				PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP), nb_bytes_to_transmit, rlc_pP->sdu_buffer_occupancy);

		sdu_mngt_p = (struct rlc_am_tx_sdu_management *)(sdu_in_buffer->data);

		headerL += rlc_pP->tx_sn_length == 18 ? 3 : 2;

//		当前SDU未分片并且数据空间可以包含整个SDU
		if((sdu_mngt_p->sdu_segmented_size == 0) && (sdu_mngt_p->sdu_size + headerL <= nb_bytes_to_transmit)) {
			data_pdu_size = sdu_mngt_p->sdu_size + headerL;
			si = RLC_SI_DATA_FIELD_CONTAINS_ALL_BYTES_OF_AN_RLC_SDU;
		} else {
			headerL += 2;

			if(headerL + sdu_mngt_p->sdu_remaining_size > nb_bytes_to_transmit) {
				data_pdu_size = nb_bytes_to_transmit;

				if(sdu_mngt_p->sdu_segmented_size == 0) {
					si = RLC_SI_DATA_FIELD_CONTAINS_THE_FIRST_SEGMENT_OF_AN_RLC_SDU;
				} else {
					si = RLC_SI_DATA_FIELD_CONTAINS_NEITHER_THE_FIRST_NOR_LAST_SEGMENT_OF_AN_RLC_SDU;
				}
			} else {
				data_pdu_size = headerL + sdu_mngt_p->sdu_remaining_size;

				si = RLC_SI_DATA_FIELD_CONTAINS_THE_LAST_SEGMENT_OF_AN_RLC_SDU;
			}
		}

		if(!(pdu_mem_p = get_free_mem_block (data_pdu_size + sizeof(struct mac_tb_req), __func__))) {
//			RLC_AM_MUTEX_UNLOCK(&rlc_pP->lock_input_sdus);
			return;
		}

//		增加 MAC subheader before MAC SDU（RLC PDU）
		if(data_pdu_size <= 0xFF) {
			rlc_pP->nb_bytes_requested_by_mac -= data_pdu_size + 2;
		} else {
			rlc_pP->nb_bytes_requested_by_mac -= data_pdu_size + 3;
		}

//		清零头部
		memset(pdu_mem_p->data, 0, sizeof(struct mac_tb_req) + headerL);

		header_pP = (rlc_am_header_t *)(pdu_mem_p->data + sizeof(struct mac_tb_req));

//		赋值RLC头
		if(rlc_pP->tx_sn_length == 18) {
			header_pP->h18.d_c = 1;
			header_pP->h18.si = si;
			header_pP->h18.snh2 = (rlc_pP->TX_Next >> 16) & 0x00000003;
			header_pP->h18.snm = (rlc_pP->TX_Next >> 8) & 0x000000FF;
			header_pP->h18.snl = rlc_pP->TX_Next & 0x000000FF;

			if(sdu_mngt_p->sdu_segmented_size != 0) {
				header_pP->h18.soh = (sdu_mngt_p->sdu_segmented_size >> 8) & 0x000000FF;
				header_pP->h18.sol = sdu_mngt_p->sdu_segmented_size & 0x000000FF;
			}
		} else {
			header_pP->h12.d_c = 1;
			header_pP->h12.si = si;
			header_pP->h12.snh4 = (rlc_pP->TX_Next >> 8) & 0x0000000F;
			header_pP->h12.snl = rlc_pP->TX_Next & 0x000000FF;

			if(sdu_mngt_p->sdu_segmented_size != 0) {
				header_pP->h12.soh = (sdu_mngt_p->sdu_segmented_size >> 8) & 0x000000FF;
				header_pP->h12.sol = sdu_mngt_p->sdu_segmented_size & 0x000000FF;
			}
		}

//		拷贝RLC SDU
		memcpy(pdu_mem_p->data + sizeof(struct mac_tb_req) + headerL, sdu_mngt_p->first_byte, data_pdu_size - headerL);

//		设置TB块参数
		((struct mac_tb_req *)(pdu_mem_p->data))->data_ptr = pdu_mem_p->data + sizeof(struct mac_tb_req);
		((struct mac_tb_req *)(pdu_mem_p->data))->tb_size = data_pdu_size;

		rlc_am_pdu_polling(ctxt_pP, rlc_pP, pdu_mem_p->data + sizeof(struct mac_tb_req), data_pdu_size, TRUE);

		list_add_tail_eurecom(pdu_mem_p, &rlc_pP->segmentation_pdu_list);

		sdu_mngt_p->sdu_segmented_size += data_pdu_size - headerL;
		sdu_mngt_p->sdu_remaining_size -= data_pdu_size - headerL;

//		如果SDU数据传输完成，则移动SDU至已传输缓冲
		if(sdu_mngt_p->sdu_remaining_size == 0) {
			list2_add_tail(sdu_in_buffer, &rlc_pP->tx_sdus);

			list2_remove_head(&rlc_pP->input_sdus);
		}
	}

//	RLC_AM_MUTEX_UNLOCK(&rlc_pP->lock_input_sdus);
}
