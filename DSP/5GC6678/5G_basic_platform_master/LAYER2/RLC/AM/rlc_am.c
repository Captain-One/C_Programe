#define RLC_AM_MODULE 1
#define RLC_AM_C 1
//-----------------------------------------------------------------------------
#include "platform_types.h"
#include "platform_constants.h"
//-----------------------------------------------------------------------------
#if ENABLE_ITTI
# include "intertask_interface.h"
#endif
#include "assertions.h"
#include "hashtable.h"
#include "rlc_am.h"
#include "rlc_am_segment.h"
#include "rlc_am_timer_poll_retransmit.h"
#include "rlc_primitives.h"
#include "list.h"
#include "mac_extern.h"
#include "UL-AM-RLC.h"
#include "DL-AM-RLC.h"


//-----------------------------------------------------------------------------
uint32_t rlc_am_get_status_pdu_buffer_occupancy(rlc_am_entity_t * const rlc_pP)
{
	//Compute Max Status PDU size according to what has been received and not received in the window [vrR vrMS[

    // minimum header size in bits to be transmitted: D/C + CPT + ACK_SN + E1
	uint32_t nb_bits_to_transmit = RLC_AM_PDU_D_C_BITS + RLC_AM_STATUS_PDU_CPT_LENGTH + RLC_AM_SN_BITS + RLC_AM_PDU_E_BITS;
	mem_block_t *cursor_p = rlc_pP->receiver_buffer.head;
    rlc_am_pdu_info_t *pdu_info_cursor_p = NULL;
    int waited_so = 0;

	rlc_sn_t sn_cursor = rlc_pP->RX_Next;
	rlc_sn_t sn_prev = rlc_pP->RX_Next;
	rlc_sn_t sn_end = rlc_pP->RX_Next_Highest;
	boolean_t	segment_loop_end	  = FALSE;


	if (sn_prev != sn_end)
	{
		while ((RLC_AM_DIFF_SN(sn_prev,rlc_pP->RX_Next) < RLC_AM_DIFF_SN(sn_end,rlc_pP->RX_Next)) && (cursor_p != NULL))
		{
			pdu_info_cursor_p     = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;
			sn_cursor             = pdu_info_cursor_p->sn;

			// Add holes between sn_prev and sn_cursor
			while ((sn_prev != sn_cursor) && (sn_prev != sn_end))
			{
				  /* Add 1 NACK_SN + E1 + E2 */
				  nb_bits_to_transmit += (RLC_AM_SN_BITS + (RLC_AM_PDU_E_BITS << 1));
				  sn_prev = RLC_AM_NEXT_SN(sn_prev);
			} //end while (sn_prev != sn_cursor)

			/* Handle case sn_cursor is partially received */
			/* Each gap will add NACK_SN + E1 + E2 + SOStart + SOEnd */
			if ((((rlc_am_rx_pdu_management_t*)(cursor_p->data))->all_segments_received == 0) && (RLC_AM_DIFF_SN(sn_cursor,rlc_pP->RX_Next) < RLC_AM_DIFF_SN(sn_end,rlc_pP->RX_Next)))
			{
                 /* Check lsf */
//				  segment_loop_end = (pdu_info_cursor_p->lsf == 1);

	    		  /* Fill for [0 SO[ if SO not null */
	    		  if (pdu_info_cursor_p->so) {
	    			  nb_bits_to_transmit += (RLC_AM_SN_BITS + (RLC_AM_PDU_E_BITS << 1) + (RLC_AM_STATUS_PDU_SO_LENGTH << 1));
	                  waited_so = pdu_info_cursor_p->so + pdu_info_cursor_p->payload_size;
	    		  }
	    		  else {
	        		  waited_so = pdu_info_cursor_p->payload_size;
	    		  }

                  /* Go to next segment */
                  cursor_p = cursor_p->next;
                  if (cursor_p != NULL)
                  {
                      pdu_info_cursor_p     = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;
                  }

	    		  /* Fill following gaps if any */
	    		  while (!segment_loop_end)
	    		  {
	    			  if ((cursor_p != NULL) && (pdu_info_cursor_p->sn == sn_cursor))
	    			  {
		                  /* Check lsf */
//	    				  segment_loop_end = (pdu_info_cursor_p->lsf == 1);

            			  if (waited_so < pdu_info_cursor_p->so) {
    	                      nb_bits_to_transmit += (RLC_AM_SN_BITS + (RLC_AM_PDU_E_BITS << 1) + (RLC_AM_STATUS_PDU_SO_LENGTH << 1));
            			  }
            			  else {
            				  /* contiguous segment: only update waited_so */
            				  /* Assuming so and payload_size updated according to duplication removal done at reception ... */
            				  waited_so += pdu_info_cursor_p->payload_size;
            			  }

            			  /* Go to next received PDU or PDU Segment */
            			  cursor_p = cursor_p->next;
    	                  if (cursor_p != NULL)
    	                  {
    		                  pdu_info_cursor_p     = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;
    	                  }
	    			  }
	    			  else
	    			  {
	    				  /* Fill last gap assuming LSF is not received */
	    				  nb_bits_to_transmit += (RLC_AM_SN_BITS + (RLC_AM_PDU_E_BITS << 1) + (RLC_AM_STATUS_PDU_SO_LENGTH << 1));
	    				  segment_loop_end = TRUE;
	    			  }
	    		  } // end while (!segment_loop_end)
			} // end if segments
			else
			{
				  /* Go to next received PDU or PDU segment with different SN */
				  do
				  {
					  cursor_p = cursor_p->next;
				  } while ((cursor_p != NULL) && (((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info.sn == sn_cursor));
			}

			sn_prev = RLC_AM_NEXT_SN(sn_cursor);
		}
	} // end if (sn_prev != sn_end)

	// round up to the greatest byte
	return ((nb_bits_to_transmit + 7) >> 3);

}

//-----------------------------------------------------------------------------
uint32_t
rlc_am_get_buffer_occupancy_in_bytes (
	const protocol_ctxt_t* const ctxt_pP,
	rlc_am_entity_t * const      rlc_pP)
{
	// priority of control trafic
	rlc_pP->status_buffer_occupancy = 0;
	if ((rlc_pP->status_requested) && !(rlc_pP->status_requested & RLC_AM_STATUS_NO_TX_MASK))
	{
		rlc_pP->status_buffer_occupancy = rlc_am_get_status_pdu_buffer_occupancy(rlc_pP);
#if TRACE_RLC_AM_BO

		LOG_D(RLC, PROTOCOL_CTXT_FMT RB_AM_FMT" BO : CONTROL PDU %d bytes \n",
		PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP),
		rlc_pP->status_buffer_occupancy);

#endif
	}


#if TRACE_RLC_AM_BO

	if ((rlc_pP->status_buffer_occupancy + rlc_pP->retrans_num_bytes_to_retransmit + rlc_pP->sdu_buffer_occupancy + max_li_overhead + header_overhead) > 0) {
	LOG_D(RLC, PROTOCOL_RLC_AM_CTXT_FMT" BO : STATUS  BUFFER %d bytes \n", PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP), rlc_pP->status_buffer_occupancy);
	LOG_D(RLC, PROTOCOL_RLC_AM_CTXT_FMT" BO : RETRANS BUFFER %d bytes \n", PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP), rlc_pP->retrans_num_bytes_to_retransmit);
	LOG_D(RLC, PROTOCOL_RLC_AM_CTXT_FMT" BO : SDU     BUFFER %d bytes + li_overhead %d bytes header_overhead %d bytes (nb sdu not segmented %d)\n",
	PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP),
	rlc_pP->sdu_buffer_occupancy,
	0,
	0,
	rlc_pP->nb_sdu_no_segmented);
	}

#endif
	return rlc_pP->status_buffer_occupancy + rlc_pP->retrans_num_bytes_to_retransmit + rlc_pP->sdu_buffer_occupancy;
}
//-----------------------------------------------------------------------------
void
rlc_am_release(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_am_entity_t * const      rlc_pP
)
{
  // empty
}
//-----------------------------------------------------------------------------
void
config_req_rlc_am (
	const protocol_ctxt_t* const ctxt_pP,
	const srb_flag_t             srb_flagP,
	const rlc_am_info_t  *       config_am_pP,
	const rb_id_t                rb_idP,
	const logical_chan_id_t      chan_idP
)
{
	rlc_union_t       *rlc_union_p = NULL;
	rlc_am_entity_t *l_rlc_p         = NULL;
	hash_key_t       key           = RLC_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, rb_idP, srb_flagP);
	hashtable_rc_t   h_rc;

	h_rc = hashtable_get(rlc_coll_p, key, (void**)&rlc_union_p);

	if (h_rc == HASH_TABLE_OK)
	{
		l_rlc_p = &rlc_union_p->rlc.am;
		printf(" CONFIG_REQ (max_retx_threshold=%d poll_pdu=%d poll_byte=%d t_poll_retransmit=%d t_reord=%d t_status_prohibit=%d)\n",
				config_am_pP->max_retx_threshold,
				config_am_pP->poll_pdu,
				config_am_pP->poll_byte,
				config_am_pP->t_poll_retransmit,
				config_am_pP->t_reordering,
				config_am_pP->t_status_prohibit);

//		rlc_am_init(ctxt_pP, l_rlc_p);

//		rlc_am_set_debug_infos(ctxt_pP, l_rlc_p, srb_flagP, rb_idP, chan_idP);

//		rlc_am_configure(ctxt_pP, l_rlc_p,
//				config_am_pP->max_retx_threshold,
//				config_am_pP->poll_pdu,
//				config_am_pP->poll_byte,
//				config_am_pP->t_poll_retransmit,
//				config_am_pP->t_reordering,
//				config_am_pP->t_status_prohibit);
	}
	else
	{
		printf(" CONFIG_REQ RLC NOT FOUND\n");
	}
}

uint16_t pollPDU_tab[PollPDU_infinity + 1]= {4,8,16,32,64,128,256,RLC_AM_POLL_PDU_INFINITE}; //PollPDU_pInfinity is chosen to 0xFFFF for now
uint32_t maxRetxThreshold_tab[UL_AM_RLC__maxRetxThreshold_t32+1]= {1,2,3,4,6,8,16,32};
uint32_t pollByte_tab[PollByte_spare1]= {25000,50000,75000,100000,125000,250000,375000,500000,750000,1000000,1250000,1500000,2000000,3000000,RLC_AM_POLL_BYTE_INFINITE}; // PollByte_kBinfinity is chosen to 0xFFFFFFFF for now
#if 0//(RRC_VERSION < MAKE_VERSION(15, 0, 0))
uint32_t PollRetransmit_tab[T_PollRetransmit_spare5]= {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,300,350,400,450,500,800,1000,2000,4000};
uint32_t am_t_Reordering_tab[32]= {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,1600};
uint32_t t_StatusProhibit_tab[T_StatusProhibit_spare2]= {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,300,350,400,450,500,800,1000,1200,1600,2000,2400};
#else
uint32_t PollRetransmit_tab[T_PollRetransmit_spare5]= {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,300,350,400,450,500};
uint32_t am_t_Reordering_tab[T_Reassembly_spare1]= {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200};
uint32_t t_StatusProhibit_tab[T_StatusProhibit_spare2]= {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250,300,350,400,450,500};
#endif

//-----------------------------------------------------------------------------
void config_req_rlc_am_asn1 (
	const protocol_ctxt_t* const         ctxt_pP,
	const srb_flag_t                     srb_flagP,
	const struct RLC_Config__am  * const config_am_pP,
	const rb_id_t                        rb_idP,
	const logical_chan_id_t              chan_idP)
{
  rlc_union_t     *rlc_union_p   = NULL;
  rlc_am_entity_t *l_rlc_p         = NULL;
  hash_key_t       key           = RLC_COLL_KEY_VALUE(ctxt_pP->module_id, ctxt_pP->rnti, rb_idP, srb_flagP);
  hashtable_rc_t   h_rc;

  h_rc = hashtable_get(rlc_coll_p, key, (void**)&rlc_union_p);

  if (h_rc == HASH_TABLE_OK) {
    l_rlc_p = &rlc_union_p->rlc.am;

    if ((config_am_pP->ul_AM_RLC.maxRetxThreshold <= UL_AM_RLC__maxRetxThreshold_t32) &&
        (config_am_pP->ul_AM_RLC.pollPDU<=PollPDU_infinity) &&
        (config_am_pP->ul_AM_RLC.pollByte<PollByte_spare1) &&
#if 0//(RRC_VERSION < MAKE_VERSION(15, 0, 0))
        (config_am_pP->ul_AM_RLC.t_PollRetransmit<T_PollRetransmit_spare5) &&
        (config_am_pP->dl_AM_RLC.t_Reordering<32) &&
        (config_am_pP->dl_AM_RLC.t_StatusProhibit<T_StatusProhibit_spare2) ) {
#else
        (config_am_pP->ul_AM_RLC.t_PollRetransmit<T_PollRetransmit_spare5) &&
        (config_am_pP->dl_AM_RLC.t_Reassembly<T_Reassembly_spare1) &&
        (config_am_pP->dl_AM_RLC.t_StatusProhibit<T_StatusProhibit_spare2) ) {
#endif

//      MSC_LOG_RX_MESSAGE(
//        (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,
//        (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RRC_ENB:MSC_RRC_UE,
//        NULL,
//        0,
//        MSC_AS_TIME_FMT" "PROTOCOL_RLC_AM_MSC_FMT" CONFIG-REQ t_PollRetx %u t_Reord %u t_StatusPro %u",
//        MSC_AS_TIME_ARGS(ctxt_pP),
//        PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP, l_rlc_p),
//        PollRetransmit_tab[config_am_pP->ul_AM_RLC.t_PollRetransmit],
//        am_t_Reordering_tab[config_am_pP->dl_AM_RLC.t_Reordering],
//        t_StatusProhibit_tab[config_am_pP->dl_AM_RLC.t_StatusProhibit]);

      printf(" CONFIG_REQ (max_retx_threshold=%d poll_pdu=%d poll_byte=%d t_poll_retransmit=%d t_reord=%d t_status_prohibit=%d)\n",
            maxRetxThreshold_tab[config_am_pP->ul_AM_RLC.maxRetxThreshold],
            pollPDU_tab[config_am_pP->ul_AM_RLC.pollPDU],
            pollByte_tab[config_am_pP->ul_AM_RLC.pollByte],
            PollRetransmit_tab[config_am_pP->ul_AM_RLC.t_PollRetransmit],
            am_t_Reordering_tab[config_am_pP->dl_AM_RLC.t_Reassembly],
            t_StatusProhibit_tab[config_am_pP->dl_AM_RLC.t_StatusProhibit]);

//      rlc_am_init(ctxt_pP, l_rlc_p);
//      rlc_am_set_debug_infos(ctxt_pP, l_rlc_p, srb_flagP, rb_idP, chan_idP);
//      rlc_am_configure(ctxt_pP, l_rlc_p,
//                       maxRetxThreshold_tab[config_am_pP->ul_AM_RLC.maxRetxThreshold],
//                       pollPDU_tab[config_am_pP->ul_AM_RLC.pollPDU],
//                       pollByte_tab[config_am_pP->ul_AM_RLC.pollByte],
//                       PollRetransmit_tab[config_am_pP->ul_AM_RLC.t_PollRetransmit],
//                       am_t_Reordering_tab[config_am_pP->dl_AM_RLC.t_Reassembly],
//                       t_StatusProhibit_tab[config_am_pP->dl_AM_RLC.t_StatusProhibit]);
    } else {
//      MSC_LOG_RX_DISCARDED_MESSAGE(
//        (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,
//        (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RRC_ENB:MSC_RRC_UE,
//        NULL,
//        0,
//        MSC_AS_TIME_FMT" "PROTOCOL_RLC_AM_MSC_FMT" CONFIG-REQ",
//        MSC_AS_TIME_ARGS(ctxt_pP),
//        PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP, l_rlc_p));

      printf("ILLEGAL CONFIG_REQ (max_retx_threshold=%ld poll_pdu=%ld poll_byte=%ld t_poll_retransmit=%ld t_reord=%ld t_status_prohibit=%ld), RLC-AM NOT CONFIGURED\n",
            config_am_pP->ul_AM_RLC.maxRetxThreshold,
            config_am_pP->ul_AM_RLC.pollPDU,
            config_am_pP->ul_AM_RLC.pollByte,
            config_am_pP->ul_AM_RLC.t_PollRetransmit,
            config_am_pP->dl_AM_RLC.t_Reassembly,
            config_am_pP->dl_AM_RLC.t_StatusProhibit);
    }
  } else {
    printf("CONFIG_REQ RLC NOT FOUND\n");
  }
}

//-----------------------------------------------------------------------------
void rlc_am_stat_req (
	const protocol_ctxt_t* const         ctxt_pP,
	rlc_am_entity_t * const              rlc_pP,
	unsigned int* stat_tx_pdcp_sdu,
	unsigned int* stat_tx_pdcp_bytes,
	unsigned int* stat_tx_pdcp_sdu_discarded,
	unsigned int* stat_tx_pdcp_bytes_discarded,
	unsigned int* stat_tx_data_pdu,
	unsigned int* stat_tx_data_bytes,
	unsigned int* stat_tx_retransmit_pdu_by_status,
	unsigned int* stat_tx_retransmit_bytes_by_status,
	unsigned int* stat_tx_retransmit_pdu,
	unsigned int* stat_tx_retransmit_bytes,
	unsigned int* stat_tx_control_pdu,
	unsigned int* stat_tx_control_bytes,
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
	unsigned int* stat_rx_control_pdu,
	unsigned int* stat_rx_control_bytes,
	unsigned int* stat_timer_reordering_timed_out,
	unsigned int* stat_timer_poll_retransmit_timed_out,
	unsigned int* stat_timer_status_prohibit_timed_out)
{
	*stat_tx_pdcp_sdu                     = rlc_pP->stat_tx_pdcp_sdu;
	*stat_tx_pdcp_bytes                   = rlc_pP->stat_tx_pdcp_bytes;
	*stat_tx_pdcp_sdu_discarded           = rlc_pP->stat_tx_pdcp_sdu_discarded;
	*stat_tx_pdcp_bytes_discarded         = rlc_pP->stat_tx_pdcp_bytes_discarded;
	*stat_tx_data_pdu                     = rlc_pP->stat_tx_data_pdu;
	*stat_tx_data_bytes                   = rlc_pP->stat_tx_data_bytes;
	*stat_tx_retransmit_pdu_by_status     = rlc_pP->stat_tx_retransmit_pdu_by_status;
	*stat_tx_retransmit_bytes_by_status   = rlc_pP->stat_tx_retransmit_bytes_by_status;
	*stat_tx_retransmit_pdu               = rlc_pP->stat_tx_retransmit_pdu;
	*stat_tx_retransmit_bytes             = rlc_pP->stat_tx_retransmit_bytes;
	*stat_tx_control_pdu                  = rlc_pP->stat_tx_control_pdu;
	*stat_tx_control_bytes                = rlc_pP->stat_tx_control_bytes;
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
	*stat_rx_control_pdu                  = rlc_pP->stat_rx_control_pdu;
	*stat_rx_control_bytes                = rlc_pP->stat_rx_control_bytes;
	*stat_timer_reordering_timed_out      = rlc_pP->stat_timer_reordering_timed_out;
	*stat_timer_poll_retransmit_timed_out = rlc_pP->stat_timer_poll_retransmit_timed_out;
	*stat_timer_status_prohibit_timed_out = rlc_pP->stat_timer_status_prohibit_timed_out;

}
//-----------------------------------------------------------------------------
void rlc_am_get_pdus(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t * const rlc_pP)
{
  //int display_flag = 0;
  // 5.1.3.1 Transmit operations
  // 5.1.3.1.1
  // General
  // The transmitting side of an AM RLC entity shall prioritize transmission of RLC control PDUs over RLC data PDUs.
  // The transmitting side of an AM RLC entity shall prioritize retransmission of RLC data PDUs over transmission of new
  // AMD PDUs.

	switch (rlc_pP->protocol_state) {
	case RLC_NULL_STATE:
		break;
	case RLC_DATA_TRANSFER_READY_STATE:

//		TRY TO SEND CONTROL PDU FIRST
		if ((rlc_pP->nb_bytes_requested_by_mac >= 2) && ((rlc_pP->status_requested) &&
				!(rlc_pP->status_requested & RLC_AM_STATUS_NO_TX_MASK)))
		{
//			 When STATUS reporting has been triggered, the receiving side of an AM RLC entity shall:
//			 - if t-StatusProhibit is not running:
//			     - at the first transmission opportunity indicated by lower layer, construct a STATUS PDU and deliver it to lower layer;
//			 - else:
//			     - at the first transmission opportunity indicated by lower layer after t-StatusProhibit expires, construct a single
//			       STATUS PDU even if status reporting was triggered several times while t-StatusProhibit was running and
//			       deliver it to lower layer;
//
//			 When a STATUS PDU has been delivered to lower layer, the receiving side of an AM RLC entity shall:
//			     - start t-StatusProhibit.

			rlc_am_send_status_pdu(ctxt_pP, rlc_pP);

			mem_block_t* pdu = list_remove_head(&rlc_pP->control_pdu_list);

			if(pdu) {
				list_add_tail_eurecom(pdu, &rlc_pP->pdus_to_mac_layer);

				RLC_AM_CLEAR_ALL_STATUS(rlc_pP->status_requested);
				rlc_pP->status_buffer_occupancy = 0;

				rlc_am_start_timer_status_prohibit(ctxt_pP, rlc_pP);
				return;
			}
		} else {
			printf(" DELAYED SENT STATUS PDU (Available MAC Data %u)(T-PROHIBIT %u) (DELAY FLAG %u)\n",
			rlc_pP->nb_bytes_requested_by_mac,rlc_pP->t_status_prohibit.ms_time_out,(rlc_pP->status_requested & RLC_AM_STATUS_TRIGGERED_DELAYED));
		}

		/* THEN TRY TO SEND RETRANS PDU */
		if ((rlc_pP->retrans_num_bytes_to_retransmit) && (rlc_pP->nb_bytes_requested_by_mac > 2)) {
			/* Get 1 AM data PDU or PDU segment to retransmit */
			mem_block_t* pdu_retx = rlc_am_get_pdu_to_retransmit(ctxt_pP, rlc_pP);

			if (pdu_retx != NULL) {
				list_add_tail_eurecom(pdu_retx, &rlc_pP->pdus_to_mac_layer);

				return;
			}
		}

		/* THEN TRY TO SEND NEW DATA PDU */
		if ((rlc_pP->nb_bytes_requested_by_mac > 2) && (rlc_pP->sdu_buffer_occupancy) &&
				(rlc_pP->TX_Next_Ack != rlc_pP->TX_Next)){

			rlc_am_segment(ctxt_pP, rlc_pP);

			list_add_list(&rlc_pP->segmentation_pdu_list, &rlc_pP->pdus_to_mac_layer);

			if (rlc_pP->pdus_to_mac_layer.head != NULL) {
				rlc_pP->stat_tx_data_pdu += 1;
				rlc_pP->stat_tx_data_bytes += (((struct mac_tb_req*)(rlc_pP->pdus_to_mac_layer.head->data))->tb_size);
				return;
			}
		}
		break;
	default:
		printf(" MAC_DATA_REQ UNKNOWN PROTOCOL STATE 0x%02X\n", rlc_pP->protocol_state);
	}
}

//-----------------------------------------------------------------------------
void
rlc_am_rx (
	const protocol_ctxt_t* const ctxt_pP,
	void * const                 arg_pP,
	struct mac_data_ind          data_indP
)
{
	rlc_am_entity_t *rlc = (rlc_am_entity_t *)arg_pP;

	switch (rlc->protocol_state)
	{
	case RLC_NULL_STATE:
		printf("ERROR MAC_DATA_IND IN RLC_NULL_STATE\n");
		list_free(&data_indP.data);
		break;
	case RLC_DATA_TRANSFER_READY_STATE:
		rlc_am_receive_routing(ctxt_pP, rlc, data_indP);
		break;
	default:
		printf("TX UNKNOWN PROTOCOL STATE 0x%02X\n", rlc->protocol_state);
		list_free(&data_indP.data);
	}
}

//-----------------------------------------------------------------------------
struct mac_status_resp
rlc_am_mac_status_indication (
  const protocol_ctxt_t* const ctxt_pP,
  void * const                 rlc_pP,
  const uint16_t               tb_sizeP,
  struct mac_status_ind        tx_statusP,
  const eNB_flag_t enb_flagP)
{
  struct mac_status_resp  status_resp;
  uint16_t  sdu_size = 0;
  uint16_t  sdu_remaining_size = 0;
  int32_t diff_time=0;
  rlc_am_entity_t *rlc = (rlc_am_entity_t *) rlc_pP;

  status_resp.buffer_occupancy_in_bytes        = 0;
  status_resp.buffer_occupancy_in_pdus         = 0;
  status_resp.head_sdu_remaining_size_to_send  = 0;
  status_resp.head_sdu_creation_time           = 0;
  status_resp.head_sdu_is_segmented            = 0;
  status_resp.rlc_info.rlc_protocol_state = rlc->protocol_state;

  /* TODO: remove this hack. Problem is: there is a race.
   * UE comes. SRB2 is configured via message to RRC.
   * At some point the RLC AM is created but not configured yet.
   * At this moment (I think) MAC calls mac_rlc_status_ind
   * which calls this function. But the init was not finished yet
   * and we have a crash below when testing mem_block != NULL.
   */
  if (rlc->input_sdus.head == NULL) return status_resp;

  if (rlc->last_absolute_subframe_status_indication != (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP))) {
    rlc_am_check_timer_poll_retransmit(ctxt_pP, rlc);
    rlc_am_check_timer_reordering(ctxt_pP, rlc);
    rlc_am_check_timer_status_prohibit(ctxt_pP, rlc);
  }

  rlc->last_absolute_subframe_status_indication = PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP);

  if (tb_sizeP > 0) {
    rlc->nb_bytes_requested_by_mac = tb_sizeP;
  }

  status_resp.buffer_occupancy_in_bytes = rlc_am_get_buffer_occupancy_in_bytes(ctxt_pP, rlc);

  // For eNB scheduler : Add Max RLC header size for new PDU
  // For UE : do not add RLC header part to be compliant with BSR definition in 38.321
  if (enb_flagP == ENB_FLAG_YES) {
	  uint32_t max_li_overhead = 0;
	  uint32_t header_overhead = 0;

	   if (rlc->nb_sdu_no_segmented > 1) {
	   	/* This computation assumes there is no SDU with size greater than 2047 bytes, otherwise a new PDU must be built except for LI15 configuration from Rel12*/
	 	  uint32_t num_li = rlc->nb_sdu_no_segmented - 1;
	       max_li_overhead = num_li + (num_li >> 1) + (num_li & 1);
	   }

	   if (rlc->sdu_buffer_occupancy > 0) {
	     header_overhead = 2;
	   }

	   status_resp.buffer_occupancy_in_bytes += (header_overhead + max_li_overhead);
  }


  if ((rlc->input_sdus.head != NULL) && (status_resp.buffer_occupancy_in_bytes)) {

    //status_resp.buffer_occupancy_in_bytes += ((rlc_am_entity_t *) rlc)->tx_header_min_length_in_bytes;
    status_resp.buffer_occupancy_in_pdus = rlc->nb_sdu;
    diff_time =   ctxt_pP->frame - ((rlc_am_tx_sdu_management_t *) (rlc->input_sdus.head->data))->sdu_creation_time;

    status_resp.head_sdu_creation_time = (diff_time > 0 ) ? (uint32_t) diff_time :  (uint32_t)(0xffffffff - diff_time + ctxt_pP->frame) ;

    sdu_size            = ((rlc_am_tx_sdu_management_t *) (rlc->input_sdus.head->data))->sdu_size;
    sdu_remaining_size  = ((rlc_am_tx_sdu_management_t *) (rlc->input_sdus.head->data))->sdu_remaining_size;
    status_resp.head_sdu_remaining_size_to_send = sdu_remaining_size;

    if (sdu_size == sdu_remaining_size)  {
      status_resp.head_sdu_is_segmented = 0;
    } else {
      status_resp.head_sdu_is_segmented = 1;
    }

  } else {
	  /* Not so many possibilities ... */
	  /* either buffer_occupancy_in_bytes = 0 and that's it */
	  /* or we have segmented all received SDUs and buffer occupancy is then made of retransmissions and/or status pdu pending */
	  /* then consider only retransmission buffer for the specific BO values used by eNB scheduler (not used up to now...) */
	  if (rlc->retrans_num_bytes_to_retransmit) {
		  status_resp.buffer_occupancy_in_pdus = rlc->retrans_num_pdus;
		  status_resp.head_sdu_remaining_size_to_send = rlc->retrans_num_bytes_to_retransmit;
		  status_resp.head_sdu_is_segmented = 1;
			    }
			  }
#if MESSAGE_CHART_GENERATOR_RLC_MAC
  MSC_LOG_RX_MESSAGE(
    (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,
    (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_MAC_ENB:MSC_MAC_UE,
    NULL,0,
    MSC_AS_TIME_FMT" "PROTOCOL_RLC_AM_MSC_FMT" STATUS-IND %u",
    MSC_AS_TIME_ARGS(ctxt_pP),
    PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP, rlc),
    tb_sizeP);
  MSC_LOG_TX_MESSAGE(
    (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,
    (ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_MAC_ENB:MSC_MAC_UE,
    NULL,0,
    MSC_AS_TIME_FMT" "PROTOCOL_RLC_AM_MSC_FMT" STATUS-RESP BO:%u/n%u(%u)  %s sdu remain %u",
    MSC_AS_TIME_ARGS(ctxt_pP),
    PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP, rlc),
    status_resp.buffer_occupancy_in_bytes,
    status_resp.buffer_occupancy_in_pdus,rlc->nb_sdu,
    (status_resp.head_sdu_is_segmented)?"sdu seg":"sdu not seg",
    status_resp.head_sdu_remaining_size_to_send);
#endif

#if TRACE_RLC_AM_TX_STATUS

  if (tb_sizeP > 0) {
    LOG_D(RLC, PROTOCOL_RLC_AM_CTXT_FMT" MAC_STATUS_INDICATION (DATA) %d bytes -> %d bytes\n",
          PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP),
          tb_sizeP,
          status_resp.buffer_occupancy_in_bytes);
    /*if ((tx_statusP.tx_status == MAC_TX_STATUS_SUCCESSFUL) && (tx_statusP.no_pdu)) {
        msg ("[FRAME %5u][%s][RLC_AM][MOD %u/%u][RB %u] MAC_STATUS_INDICATION  TX STATUS   SUCCESSFUL %d PDUs\n",rlc->ueid,
    rlc->rb_id, ctxt_pP->frame, tx_statusP.no_pdu);
    }
    if ((tx_statusP.tx_status == MAC_TX_STATUS_UNSUCCESSFUL) && (tx_statusP.no_pdu)) {
        msg ("[FRAME %5u][%s][RLC_AM][MOD %u/%u][RB %u] MAC_STATUS_INDICATION  TX STATUS UNSUCCESSFUL %d PDUs\n",rlc->ueid, rlc->rb_id,
    ctxt_pP->frame, tx_statusP.no_pdu);
    }*/
  }

#endif
  return status_resp;
}

//-----------------------------------------------------------------------------
void rlc_am_set_nb_bytes_requested_by_mac (
  void * const            rlc_pP,
  const tb_size_t         tb_sizeP
)
{
	((rlc_am_entity_t *)rlc_pP)->nb_bytes_requested_by_mac = tb_sizeP;
}

//-----------------------------------------------------------------------------
struct mac_data_req rlc_am_mac_data_request (
	const protocol_ctxt_t* const ctxt_pP,
	void * const                 rlc_pP,
	const eNB_flag_t        enb_flagP)
{
	struct mac_data_req data_req;

	rlc_am_entity_t *l_rlc_p = (rlc_am_entity_t *) rlc_pP;

	unsigned int nb_bytes_requested_by_mac = ((rlc_am_entity_t *)rlc_pP)->nb_bytes_requested_by_mac;

	list_init(&data_req.data, NULL);

	rlc_am_get_pdus(ctxt_pP, l_rlc_p);

	list_add_list(&l_rlc_p->pdus_to_mac_layer, &data_req.data);

	//((rlc_am_entity_t *) rlc_pP)->tx_pdus += data_req.data.nb_elements;
	if ((nb_bytes_requested_by_mac + data_req.data.nb_elements) > 0) {
		printf(PROTOCOL_RLC_AM_CTXT_FMT" MAC_DATA_REQUEST %05d BYTES REQUESTED -> %d TBs\n",
				PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,l_rlc_p), nb_bytes_requested_by_mac, data_req.data.nb_elements);
	}

	if (enb_flagP) {
//		redundant in UE MAC Tx processing and not used in eNB ...
		data_req.buffer_occupancy_in_bytes   = rlc_am_get_buffer_occupancy_in_bytes(ctxt_pP, l_rlc_p);
	}

	data_req.rlc_info.rlc_protocol_state = l_rlc_p->protocol_state;

	data_req.buffer_occupancy_in_pdus = 0;

	return data_req;
}

//-----------------------------------------------------------------------------
void
rlc_am_mac_data_indication(
	const protocol_ctxt_t* const ctxt_pP,
	void * const rlc_pP,
	struct mac_data_ind data_indP
)
{
//	rlc_am_entity_t* l_rlc_p = (rlc_am_entity_t*) rlc_pP;
//
//	(void)l_rlc_p; /* avoid gcc warning "unused variable" */

	rlc_am_rx (ctxt_pP, rlc_pP, data_indP);
}

//-----------------------------------------------------------------------------
void rlc_am_data_req(const protocol_ctxt_t* const ctxt_pP,
							void * const                rlc_pP,
							mem_block_t * const         sdu_pP)
{
	rlc_am_entity_t     *l_rlc_p = (rlc_am_entity_t *)rlc_pP;
	uint32_t             mui;
	uint16_t             data_offset;
	uint16_t             data_size;

	printf(" RLC_AM_DATA_REQ size %d Bytes, NB SDU %d\n",((struct rlc_am_data_req *) (sdu_pP->data))->data_size,
			l_rlc_p->input_sdus.nb_elements);

	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->mem_block = sdu_pP;
	mui         = ((struct rlc_am_data_req *)(sdu_pP->data))->mui;
	data_offset = ((struct rlc_am_data_req *)(sdu_pP->data))->data_offset;
	data_size   = ((struct rlc_am_data_req *)(sdu_pP->data))->data_size;

	l_rlc_p->stat_tx_pdcp_sdu   += 1;
	l_rlc_p->stat_tx_pdcp_bytes += data_size;

// IMPORTANT : do not change order of affectations
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->mui      = mui;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->sdu_size = data_size;
	l_rlc_p->sdu_buffer_occupancy += data_size;
	l_rlc_p->nb_sdu += 1;
	l_rlc_p->nb_sdu_no_segmented += 1;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->first_byte = (uint8_t *)(&sdu_pP->data[data_offset]);
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->sdu_remaining_size = data_size;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->sdu_segmented_size = 0;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->sdu_creation_time  = ctxt_pP->frame;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->flags.discarded    = 0;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->flags.segmented    = 0;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->flags.segmentation_in_progress = 0;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->flags.no_new_sdu_segmented_in_last_pdu = 0;

//	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->sn = -1;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->retx_count = 0;
	((struct rlc_am_tx_sdu_management *)(sdu_pP->data))->retx_count_next = 1;

//	RLC_AM_MUTEX_LOCK(&l_rlc_p->lock_input_sdus, ctxt_pP, l_rlc_p);
	list_add_tail_eurecom(sdu_pP, &l_rlc_p->input_sdus);

	if (l_rlc_p->channel_id < 3) {
		printf(PROTOCOL_RLC_AM_CTXT_FMT" RLC_AM_DATA_REQ size %d Bytes,  NB SDU %d current_sdu_index=%d next_sdu_index=%d conf %d mui %d vtA %d vtS %d\n",
				PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,l_rlc_p), data_size, l_rlc_p->nb_sdu, l_rlc_p->current_sdu_index,
				l_rlc_p->next_sdu_index, ((struct rlc_am_data_req *) (sdu_pP->data))->conf, mui,
				l_rlc_p->TX_Next_Ack, l_rlc_p->TX_Next);
	}
//	RLC_AM_MUTEX_LOCK(&l_rlc_p->lock_input_sdus, ctxt_pP, l_rlc_p);
}
