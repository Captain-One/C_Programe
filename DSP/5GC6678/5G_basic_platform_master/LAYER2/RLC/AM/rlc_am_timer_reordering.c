#define RLC_AM_MODULE 1
#define RLC_AM_TIMER_POLL_REORDERING_C 1
//-----------------------------------------------------------------------------
#include "platform_types.h"
#include "platform_constants.h"
//-----------------------------------------------------------------------------
#include "rlc_am.h"
# include "mac_extern.h"

//-----------------------------------------------------------------------------
void
rlc_am_check_timer_reordering(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_am_entity_t * const rlc_pP)
{

  if (rlc_pP->t_Reassembly.running) {
    if (
      // CASE 1:          start              time out
      //        +-----------+------------------+----------+
      //        |           |******************|          |
      //        +-----------+------------------+----------+
      //FRAME # 0                                     FRAME MAX
      ((rlc_pP->t_Reassembly.ms_start < rlc_pP->t_Reassembly.ms_time_out) &&
       ((PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) >= rlc_pP->t_Reassembly.ms_time_out) ||
        (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) < rlc_pP->t_Reassembly.ms_start)))                                   ||
      // CASE 2:        time out            start
      //        +-----------+------------------+----------+
      //        |***********|                  |**********|
      //        +-----------+------------------+----------+
      //FRAME # 0                                     FRAME MAX VALUE
      ((rlc_pP->t_Reassembly.ms_start > rlc_pP->t_Reassembly.ms_time_out) &&
       (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) < rlc_pP->t_Reassembly.ms_start) &&
       (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) >= rlc_pP->t_Reassembly.ms_time_out))
    ) {
      //if (rlc_pP->t_Reassembly.frame_time_out == ctxt_pP->frame) {
      // 5.1.3.2.4 Actions when t-Reordering expires
      // When t-Reordering expires, the receiving side of an AM RLC entity shall:
      //     - update VR(MS) to the SN of the first AMD PDU with SN >= VR(X) for which not all byte segments have been
      //       received;
      //     - if VR(H) > VR(MS):
      //         - start t-Reordering;
      //         - set VR(X) to VR(H).

#if MESSAGE_CHART_GENERATOR_RLC_MAC
      MSC_LOG_EVENT((ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,\
                             "0 "PROTOCOL_RLC_AM_MSC_FMT" t_Reassembly timed out",\
                             PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP,rlc_pP));
#endif

      //AssertFatal (rlc_pP->vr_x != RLC_SN_UNDEFINED, "RLC AM TReordering Expiry vrX not defined LcId=%d\n", rlc_pP->channel_id);
      if(rlc_pP->vr_x == RLC_SN_UNDEFINED){
      	printf("RLC AM TReordering Expiry vrX not defined LcId=%d\n", rlc_pP->channel_id);
      	return;
      }
      	

      rlc_pP->t_Reassembly.running   = 0;
      rlc_pP->t_Reassembly.timed_out = 1;
      rlc_pP->stat_timer_reordering_timed_out += 1;

      rlc_am_pdu_info_t* pdu_info;
      mem_block_t*       cursor;
      cursor    =  rlc_pP->receiver_buffer.head;
      rlc_usn_t vr_ms_new = rlc_pP->vr_x;

      //AssertFatal (cursor != NULL, "RLC AM TReordering Expiry Rx PDU list empty LcId=%d\n", rlc_pP->channel_id);
      if(cursor == NULL){
      	printf("RLC AM TReordering Expiry Rx PDU list empty LcId=%d\n", rlc_pP->channel_id);
      	return;
      }
      	
      /* go to memblock up to vrX*/
      pdu_info =  &((rlc_am_rx_pdu_management_t*)(cursor->data))->pdu_info;
      while ((cursor != NULL) && (RLC_AM_DIFF_SN(pdu_info->sn,rlc_pP->vr_r) < RLC_AM_DIFF_SN(vr_ms_new,rlc_pP->vr_r))) {
    	  cursor = cursor->next;
    	  if (cursor != NULL) {
    		  pdu_info =  &((rlc_am_rx_pdu_management_t*)(cursor->data))->pdu_info;
    	  }
      }

      /* Now find a SN for which either no PDU is received or partially received */
      while ((cursor != NULL) && (vr_ms_new != rlc_pP->vr_h) && (pdu_info->sn == vr_ms_new) && (((rlc_am_rx_pdu_management_t*)(cursor->data))->all_segments_received > 0)) {
    	  /* Increment vrMS if the PDU is fully received or if this is the last PDU segment */
//    	  if ((pdu_info->rf == 0) || (pdu_info->lsf == 1)) {
//        	  vr_ms_new = RLC_AM_NEXT_SN(vr_ms_new);
//    	  }
    	  cursor = cursor->next;
    	  if (cursor != NULL) {
    		  pdu_info =  &((rlc_am_rx_pdu_management_t*)(cursor->data))->pdu_info;
    	  }
      }

	  /* Update vr_ms */
	  rlc_pP->vr_ms = vr_ms_new;


//	printf("[T-REORDERING] TIME-OUT UPDATED VR(MS) %04d\n", PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP), rlc_pP->vr_ms);

	  /* if new vrMS is lower than vrH, update vrX and restart timerReordering */
      if (rlc_pP->vr_ms != rlc_pP->vr_h) {
        rlc_pP->vr_x = rlc_pP->vr_h;
        rlc_pP->t_Reassembly.ms_time_out = PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) + rlc_pP->t_Reassembly.ms_duration;


        printf("[T-REORDERING] TIME-OUT, RESTARTED T-REORDERING, UPDATED VR(X) to VR(R) %04d\n", rlc_pP->vr_x);
      }

      /* Trigger a STATUS report */
      RLC_AM_SET_STATUS(rlc_pP->status_requested,RLC_AM_STATUS_TRIGGERED_T_REORDERING);
      // Clear Delay flag if it was setup as it is useless due to Status PDU to be sent for TReordering expiry
      RLC_AM_CLEAR_STATUS(rlc_pP->status_requested,RLC_AM_STATUS_TRIGGERED_DELAYED);
      rlc_pP->sn_status_triggered_delayed = RLC_SN_UNDEFINED;

    }
  }
}
//-----------------------------------------------------------------------------
void
rlc_am_stop_and_reset_timer_reordering(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_am_entity_t * const      rlc_pP)
{
//  printf("[T-REORDERING] STOPPED AND RESET\n", PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP));
  rlc_pP->t_Reassembly.running         = 0;
  rlc_pP->t_Reassembly.ms_time_out     = 0;
  rlc_pP->t_Reassembly.ms_start        = 0;
  rlc_pP->t_Reassembly.timed_out       = 0;
#if MESSAGE_CHART_GENERATOR_RLC_MAC
    MSC_LOG_EVENT((ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,\
                  "0 "PROTOCOL_RLC_AM_MSC_FMT" t_Reassembly stopped & reseted",\
                  PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP,rlc_pP));
#endif
}
//-----------------------------------------------------------------------------
void
rlc_am_start_timer_reordering(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_am_entity_t * const      rlc_pP)
{
  rlc_pP->t_Reassembly.timed_out       = 0;

  if (rlc_pP->t_Reassembly.running == 0){
    if (rlc_pP->t_Reassembly.ms_duration > 0) {
      rlc_pP->t_Reassembly.running         = 1;
      rlc_pP->t_Reassembly.ms_time_out     = PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) + rlc_pP->t_Reassembly.ms_duration;
      rlc_pP->t_Reassembly.ms_start        = PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP);
      printf("[T-REORDERING] STARTED (TIME-OUT = %5u ms)\n", rlc_pP->t_Reassembly.ms_time_out);
#if MESSAGE_CHART_GENERATOR_RLC_MAC
      MSC_LOG_EVENT((ctxt_pP->enb_flag == ENB_FLAG_YES) ? MSC_RLC_ENB:MSC_RLC_UE,\
                             "0 "PROTOCOL_RLC_AM_MSC_FMT" t_Reassembly started (TO %u ms)",\
                             PROTOCOL_RLC_AM_MSC_ARGS(ctxt_pP,rlc_pP), rlc_pP->t_Reassembly.ms_time_out);
#endif
    } else {
    	printf("[T-REORDERING] NOT STARTED, CAUSE CONFIGURED 0 ms\n");
    }
  }
}
//-----------------------------------------------------------------------------
void
rlc_am_init_timer_reordering(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_am_entity_t * const      rlc_pP,
  const uint32_t              ms_durationP)
{
  rlc_pP->t_Reassembly.running         = 0;
  rlc_pP->t_Reassembly.ms_time_out     = 0;
  rlc_pP->t_Reassembly.ms_start        = 0;
  rlc_pP->t_Reassembly.ms_duration     = ms_durationP;
  rlc_pP->t_Reassembly.timed_out       = 0;
}
