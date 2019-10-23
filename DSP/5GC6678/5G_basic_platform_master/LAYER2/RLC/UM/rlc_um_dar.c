#define RLC_UM_MODULE 1
#define RLC_UM_DAR_C 1
#include "platform_types.h"
#include "assertions.h"
//-----------------------------------------------------------------------------
#include "rlc.h"
#include "rlc_um.h"
#include "rlc_primitives.h"
#include "list.h"


#if 1
//-----------------------------------------------------------------------------
signed int rlc_um_get_pdu_infos(
	const protocol_ctxt_t* const ctxt_pP,
	const rlc_um_entity_t* const rlc_pP,
	uint8_t   	         * const header_pP,
	const sdu_size_t             total_sizeP,
	rlc_um_pdu_info_t    * const pdu_info_pP)
{
  memset(pdu_info_pP, 0, sizeof (rlc_um_pdu_info_t));

  //AssertFatal( total_sizeP > 0 , "RLC UM PDU LENGTH %d", total_sizeP);
  if(total_sizeP <= 0)
  {
    printf("RLC UM PDU LENGTH %d\n", total_sizeP);
    return -1;
  }

  pdu_info_pP->si = (*header_pP >> 6) & 0x03;

  if(pdu_info_pP->si == RLC_SI_DATA_FIELD_CONTAINS_ALL_BYTES_OF_AN_RLC_SDU)
  {
	  pdu_info_pP->header_size = 1;
  }
  else
  {
	  if (rlc_pP->rx_sn_length == 12)
	  {
		pdu_info_pP->sn = *(header_pP + 1) + (((uint16_t)(*header_pP & 0x0F)) << 8);
		pdu_info_pP->header_size = 2;
		pdu_info_pP->so = *(header_pP + 3) + (((uint16_t)(*(header_pP + 2))) << 8);
		pdu_info_pP->header_size += 2;
	  }
	  else if (rlc_pP->rx_sn_length == 6)
	  {
		  pdu_info_pP->sn = *header_pP & 0x3F;
		  pdu_info_pP->header_size = 1;
		  pdu_info_pP->so = *(header_pP + 2) + (((uint16_t)(*(header_pP + 1))) << 8);
		  pdu_info_pP->header_size += 2;
	  }
	  else
	  {
		//AssertFatal( sn_lengthP == 5 || sn_lengthP == 10, "RLC UM SN LENGTH %d", sn_lengthP);
		if(!(rlc_pP->rx_sn_length == 12 || rlc_pP->rx_sn_length == 6))
		{
		  printf("RLC UM SN LENGTH %d\n", rlc_pP->rx_sn_length);
		  return -1;
		}
	  }
  }

  pdu_info_pP->payload      = header_pP + pdu_info_pP->header_size;
  pdu_info_pP->payload_size = total_sizeP - pdu_info_pP->header_size;

  return 0;
}
#else
//-----------------------------------------------------------------------------
signed int rlc_um_get_pdu_infos(
  const protocol_ctxt_t* const ctxt_pP,
  const rlc_um_entity_t* const rlc_pP,
  rlc_um_pdu_sn_10_t   * const header_pP,
  const sdu_size_t             total_sizeP,
  rlc_um_pdu_info_t    * const pdu_info_pP,
  const uint8_t                sn_lengthP)
{
  sdu_size_t         sum_li = 0;
  memset(pdu_info_pP, 0, sizeof (rlc_um_pdu_info_t));

  pdu_info_pP->num_li = 0;

  //AssertFatal( total_sizeP > 0 , "RLC UM PDU LENGTH %d", total_sizeP);
  if(total_sizeP <= 0) {
    LOG_E(RLC, "RLC UM PDU LENGTH %d\n", total_sizeP);
    return -1;
  }

  if (sn_lengthP == 10) {
    pdu_info_pP->fi           = (header_pP->b1 >> 3) & 0x03;
    pdu_info_pP->e            = (header_pP->b1 >> 2) & 0x01;
    pdu_info_pP->sn           = header_pP->b2 + (((uint16_t)(header_pP->b1 & 0x03)) << 8);
    pdu_info_pP->header_size  = 2;
    pdu_info_pP->payload      = &header_pP->data[0];
  } else if (sn_lengthP == 5) {
    pdu_info_pP->fi           = (header_pP->b1 >> 6) & 0x03;
    pdu_info_pP->e            = (header_pP->b1 >> 5) & 0x01;
    pdu_info_pP->sn           = header_pP->b1 & 0x1F;
    pdu_info_pP->header_size  = 1;
    pdu_info_pP->payload      = &header_pP->b2;
  } else {
    //AssertFatal( sn_lengthP == 5 || sn_lengthP == 10, "RLC UM SN LENGTH %d", sn_lengthP);
    if(!(sn_lengthP == 5 || sn_lengthP == 10)) {
      LOG_E(RLC, "RLC UM SN LENGTH %d\n", sn_lengthP);
      return -1;
    }
  }


  if (pdu_info_pP->e) {
    rlc_am_e_li_t      *e_li_p;
    unsigned int li_length_in_bytes  = 1;
    unsigned int li_to_read          = 1;

    e_li_p = (rlc_am_e_li_t*)(pdu_info_pP->payload);

    while (li_to_read)  {
      li_length_in_bytes = li_length_in_bytes ^ 3;

      if (li_length_in_bytes  == 2) {
        //AssertFatal( total_sizeP >= ((uint64_t)(&e_li_p->b2) - (uint64_t)header_pP),
        //             "DECODING PDU TOO FAR PDU size %d", total_sizeP);
        if(total_sizeP < ((uint64_t)(&e_li_p->b2) - (uint64_t)header_pP)) {
          LOG_E(RLC, "DECODING PDU TOO FAR PDU size %d\n", total_sizeP);
          return -1;
        }
        pdu_info_pP->li_list[pdu_info_pP->num_li] = ((uint16_t)(e_li_p->b1 << 4)) & 0x07F0;
        pdu_info_pP->li_list[pdu_info_pP->num_li] |= (((uint8_t)(e_li_p->b2 >> 4)) & 0x000F);
        li_to_read = e_li_p->b1 & 0x80;
        pdu_info_pP->header_size  += 2;
      } else {
        //AssertFatal( total_sizeP >= ((uint64_t)(&e_li_p->b3) - (uint64_t)header_pP),
        //             "DECODING PDU TOO FAR PDU size %d", total_sizeP);
        if(total_sizeP < ((uint64_t)(&e_li_p->b3) - (uint64_t)header_pP)) {
          LOG_E(RLC, "DECODING PDU TOO FAR PDU size %d\n", total_sizeP);
          return -1;
        }
        pdu_info_pP->li_list[pdu_info_pP->num_li] = ((uint16_t)(e_li_p->b2 << 8)) & 0x0700;
        pdu_info_pP->li_list[pdu_info_pP->num_li] |=  e_li_p->b3;
        li_to_read = e_li_p->b2 & 0x08;
        e_li_p++;
        pdu_info_pP->header_size  += 1;
      }

      //AssertFatal( pdu_info_pP->num_li <= RLC_UM_SEGMENT_NB_MAX_LI_PER_PDU,
      //             PROTOCOL_RLC_UM_CTXT_FMT"[GET PDU INFO]  SN %04d TOO MANY LIs ",
      //             PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
      //             pdu_info_pP->sn);
      if(pdu_info_pP->num_li > RLC_UM_SEGMENT_NB_MAX_LI_PER_PDU) {
        LOG_E(RLC, PROTOCOL_RLC_UM_CTXT_FMT"[GET PDU INFO]  SN %04d TOO MANY LIs \n",
                   PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                   pdu_info_pP->sn);
        return -1;
      }

      sum_li += pdu_info_pP->li_list[pdu_info_pP->num_li];
      pdu_info_pP->num_li = pdu_info_pP->num_li + 1;

      if (pdu_info_pP->num_li > RLC_UM_SEGMENT_NB_MAX_LI_PER_PDU) {
        return -2;
      }
    }

    if (li_length_in_bytes  == 2) {
      pdu_info_pP->payload = &e_li_p->b3;
    } else {
      pdu_info_pP->payload = &e_li_p->b1;
    }
  }

  pdu_info_pP->payload_size = total_sizeP - pdu_info_pP->header_size;

  if (pdu_info_pP->payload_size > sum_li) {
    pdu_info_pP->hidden_size = pdu_info_pP->payload_size - sum_li;
  }

  return 0;
}
#endif
//-----------------------------------------------------------------------------
int rlc_um_read_length_indicators(unsigned char**data_ppP, rlc_um_e_li_t* e_liP, unsigned int* li_array_pP, unsigned int *num_li_pP, sdu_size_t *data_size_pP)
{
  int          continue_loop = 1;
  unsigned int e1  = 0;
  unsigned int li1 = 0;
  unsigned int e2  = 0;
  unsigned int li2 = 0;
  *num_li_pP = 0;

  while ((continue_loop)) {
    //msg("[RLC_UM] e_liP->b1 = %02X\n", e_liP->b1);
    //msg("[RLC_UM] e_liP->b2 = %02X\n", e_liP->b2);
    e1 = ((unsigned int)e_liP->b1 & 0x00000080) >> 7;
    li1 = (((unsigned int)e_liP->b1 & 0x0000007F) << 4) + (((unsigned int)e_liP->b2 & 0x000000F0) >> 4);
    li_array_pP[*num_li_pP] = li1;
    *data_size_pP = *data_size_pP - li1 - 2;
    *num_li_pP = *num_li_pP +1;

    if ((e1)) {
      e2 = ((unsigned int)e_liP->b2 & 0x00000008) >> 3;
      li2 = (((unsigned int)e_liP->b2 & 0x00000007) << 8) + ((unsigned int)e_liP->b3 & 0x000000FF);
      li_array_pP[*num_li_pP] = li2;
      *data_size_pP = *data_size_pP - li2 - 1;
      *num_li_pP = *num_li_pP +1;

      if (!(*data_size_pP >= 0)) printf("Invalid data_size=%d! (pdu_size=%d loop=%d e1=%d e2=%d li2=%d e_liP=%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x)\n",
          *data_size_pP, *data_size_pP, continue_loop, e1, e2, li2,
          (e_liP-(continue_loop-1)+0)->b1,
          (e_liP-(continue_loop-1)+0)->b2,
          (e_liP-(continue_loop-1)+0)->b3,
          (e_liP-(continue_loop-1)+1)->b1,
          (e_liP-(continue_loop-1)+1)->b2,
          (e_liP-(continue_loop-1)+1)->b3,
          (e_liP-(continue_loop-1)+2)->b1,
          (e_liP-(continue_loop-1)+2)->b2,
          (e_liP-(continue_loop-1)+2)->b3);
      // AssertFatal(*data_size_pP >= 0, "Invalid data_size!");

      if (e2 == 0) {
        continue_loop = 0;
      } else {
        e_liP++;
        continue_loop++;
      }
    } else {
      if (!(*data_size_pP >= 0)) printf("Invalid data_size=%d! (pdu_size=%d loop=%d e1=%d li1=%d e_liP=%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x)\n",
          *data_size_pP, *data_size_pP, continue_loop, e1, li1,
          (e_liP-(continue_loop-1)+0)->b1,
          (e_liP-(continue_loop-1)+0)->b2,
          (e_liP-(continue_loop-1)+0)->b3,
          (e_liP-(continue_loop-1)+1)->b1,
          (e_liP-(continue_loop-1)+1)->b2,
          (e_liP-(continue_loop-1)+1)->b3,
          (e_liP-(continue_loop-1)+2)->b1,
          (e_liP-(continue_loop-1)+2)->b2,
          (e_liP-(continue_loop-1)+2)->b3);
      continue_loop = 0;
      // AssertFatal(*data_size_pP >= 0, "Invalid data_size!");
    }

    if (*num_li_pP > RLC_UM_SEGMENT_NB_MAX_LI_PER_PDU) {
      return -1;
    }
  }

  *data_ppP = *data_ppP + (((*num_li_pP*3) +1) >> 1);
  if (*data_size_pP > 0) {
    return 0;
  } else if (*data_size_pP == 0) {
    printf("Last RLC SDU size is zero!\n");
    return -1;
  } else {
    printf("Last RLC SDU size is negative %d!\n", *data_size_pP);
    return -1;
  }
}
//-----------------------------------------------------------------------------
#if 1
void
rlc_um_try_reassembly(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t *            rlc_pP,
  mem_block_t*			const pdu_pP,
  uint16_t sdu_size)
{
	mem_block_t*                cursor_p                     	= NULL;
	rlc_um_rx_pdu_management_t* rlc_am_rx_old_pdu_management 	= NULL;
	rlc_um_pdu_info_t* pdu_info_p								= NULL;
	rlc_sn_t            sn;
	int offset = 0;

	cursor_p = pdu_pP;
	pdu_info_p        = &((rlc_um_rx_pdu_management_t*)(cursor_p->data))->pdu_info;
	sn = pdu_info_p->sn;

// get all previous PDU with same SN
	while (cursor_p->previous != NULL)
	{
	  if (((rlc_um_rx_pdu_management_t*)(cursor_p->previous->data))->pdu_info.sn == sn)
	  {
		//list2_add_head(cursor_p->previous, &list);
		cursor_p = cursor_p->previous;
		//msg("rlc_am_rx_check_all_byte_segments(%d) @2\n",sn);
	  }
	  else
	  {
		break;
	  }
	}

	rlc_pP->output_sdu_in_construction = get_free_mem_block(sdu_size, __func__);

	if(rlc_pP->output_sdu_in_construction == NULL)
	{
		return;
	}
	else
	{
		rlc_pP->output_sdu_size_to_write = sdu_size;

		memset(rlc_pP->output_sdu_in_construction->data, 0, sdu_size);

		do
		{
			pdu_info_p = &((rlc_um_rx_pdu_management_t*)(cursor_p->data))->pdu_info;
			if(pdu_info_p->sn != sn)
			{
				break;
			}

			memcpy(rlc_pP->output_sdu_in_construction->data + offset, pdu_info_p->payload, pdu_info_p->payload_size);
			((rlc_um_rx_pdu_management_t*)(cursor_p->data))->segment_reassembled = 1;

			cursor_p = cursor_p->next;
		}
		while(cursor_p);

		rlc_um_send_sdu(ctxt_pP, rlc_pP);
	}
}
#else
void
rlc_um_try_reassembly(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t *            rlc_pP,
  rlc_sn_t                     start_snP,
  rlc_sn_t                     end_snP)
{
  mem_block_t        *pdu_mem_p              = NULL;
  struct mac_tb_ind  *tb_ind_p               = NULL;
  rlc_um_e_li_t      *e_li_p                 = NULL;
  unsigned char      *data_p                 = NULL;
  int                 e                      = 0;
  int                 fi                     = 0;
  sdu_size_t          size                   = 0;
  rlc_sn_t            sn                     = 0;
  unsigned int        continue_reassembly    = 0;
  unsigned int        num_li                 = 0;
  unsigned int        li_array[RLC_UM_SEGMENT_NB_MAX_LI_PER_PDU];
  int                 i                      = 0;
  int                 reassembly_start_index = 0;

  VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_RLC_UM_TRY_REASSEMBLY,VCD_FUNCTION_IN);

  if (end_snP < 0)   {
    end_snP   = end_snP   + rlc_pP->rx_sn_modulo;
  }

  if (start_snP < 0) {
    start_snP = start_snP + rlc_pP->rx_sn_modulo;
  }

#if TRACE_RLC_UM_DAR
  printf( PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY FROM PDU SN=%03d+1  TO  PDU SN=%03d   SN Length = %d bits (%s:%u)\n",
        PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
        rlc_pP->last_reassemblied_sn,
        end_snP,
        rlc_pP->rx_sn_length,
        __FILE__,
        __LINE__);
#endif

  // nothing to be reassemblied
  if (start_snP == end_snP) {
    VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_RLC_UM_TRY_REASSEMBLY,VCD_FUNCTION_OUT);
    return;
  }

  continue_reassembly = 1;
  //sn = (rlc_pP->last_reassemblied_sn + 1) % rlc_pP->rx_sn_modulo;
  sn = start_snP;

  //check_mem_area();

  while (continue_reassembly) {
    if ((pdu_mem_p = rlc_pP->dar_buffer[sn])) {

      if ((rlc_pP->last_reassemblied_sn+1)%rlc_pP->rx_sn_modulo != sn) {
#if TRACE_RLC_UM_DAR
        LOG_W(RLC,
              PROTOCOL_RLC_UM_CTXT_FMT" FINDING a HOLE in RLC UM SN: CLEARING OUTPUT SDU BECAUSE NEW SN (%03d) TO REASSEMBLY NOT CONTIGUOUS WITH LAST REASSEMBLIED SN (%03d) (%s:%u)\n",
              PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
              sn,
              rlc_pP->last_reassemblied_sn,
              __FILE__,
              __LINE__);
#endif
        rlc_um_clear_rx_sdu(ctxt_pP, rlc_pP);
      }

      rlc_pP->last_reassemblied_sn = sn;
      tb_ind_p = (struct mac_tb_ind *)(pdu_mem_p->data);

      if (rlc_pP->rx_sn_length == 10) {
#if TRACE_RLC_UM_DAR
        printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY 10 PDU SN=%03d\n (%s:%u)",
              PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
              sn,
              __FILE__,
              __LINE__);
#endif
        e  = (((rlc_um_pdu_sn_10_t*)(tb_ind_p->data_ptr))->b1 & 0x04) >> 2;
        fi = (((rlc_um_pdu_sn_10_t*)(tb_ind_p->data_ptr))->b1 & 0x18) >> 3;
        e_li_p = (rlc_um_e_li_t*)((rlc_um_pdu_sn_10_t*)(tb_ind_p->data_ptr))->data;
        size   = tb_ind_p->size - 2;
        data_p = &tb_ind_p->data_ptr[2];
      } else {
#if TRACE_RLC_UM_DAR
        printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY 5 PDU SN=%03d Byte 0=%02X (%s:%u)\n",
              PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
              sn,
              ((rlc_um_pdu_sn_5_t*)(tb_ind_p->data_ptr))->b1,
              __FILE__,
              __LINE__);
#endif
        e  = (((rlc_um_pdu_sn_5_t*)(tb_ind_p->data_ptr))->b1 & 0x00000020) >> 5;
        fi = (((rlc_um_pdu_sn_5_t*)(tb_ind_p->data_ptr))->b1 & 0x000000C0) >> 6;
        e_li_p = (rlc_um_e_li_t*)((rlc_um_pdu_sn_5_t*)(tb_ind_p->data_ptr))->data;
        size   = tb_ind_p->size - 1;
        data_p = &tb_ind_p->data_ptr[1];
#if TRACE_RLC_UM_DAR
        printf(PROTOCOL_RLC_UM_CTXT_FMT" e=%01X fi=%01X\n",
              PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
              e,
              fi,
              __FILE__,
              __LINE__);
#endif
      }
      //AssertFatal(size >= 0, "invalid size!");
      //AssertFatal((e==0) || (e==1), "invalid e!");
      //AssertFatal((fi >= 0) && (fi <= 3), "invalid fi!");
      if((size < 0) || ((e!=0) && (e!=1)) || ((fi < 0) || (fi > 3))){
        LOG_E(RLC, "invalid size %d, e %d, fi %d\n", size, e, fi);
        sn = (sn + 1) % rlc_pP->rx_sn_modulo;
        if ((sn == rlc_pP->RX_Next_Highest) || (sn == end_snP)) {
          continue_reassembly = 0;
        }
        continue;
      }

      if (e == RLC_E_FIXED_PART_DATA_FIELD_FOLLOW) {
        switch (fi) {
        case RLC_FI_1ST_BYTE_DATA_IS_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
          printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU NO E_LI FI=11 (00) (%s:%u)\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                __FILE__,
                __LINE__);
#endif
          // one complete SDU
          //LGrlc_um_send_sdu(rlc_pP,ctxt_pP->frame,ctxt_pP->enb_flag); // may be not necessary
          rlc_um_clear_rx_sdu(ctxt_pP, rlc_pP);
          rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
          rlc_um_send_sdu(ctxt_pP, rlc_pP);
          rlc_pP->reassembly_missing_sn_detected = 0;

          break;

        case RLC_FI_1ST_BYTE_DATA_IS_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_NOT_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
          printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU NO E_LI FI=10 (01) (%s:%u)\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                __FILE__,
                __LINE__);
#endif
          // one beginning segment of SDU in PDU
          //LG rlc_um_send_sdu(rlc_pP,ctxt_pP->frame,ctxt_pP->enb_flag); // may be not necessary
          rlc_um_clear_rx_sdu(ctxt_pP, rlc_pP);
          rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
          rlc_pP->reassembly_missing_sn_detected = 0;
          break;

        case RLC_FI_1ST_BYTE_DATA_IS_NOT_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
          printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU NO E_LI FI=01 (10) (%s:%u)\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                __FILE__,
                __LINE__);
#endif

          // one last segment of SDU
          if (rlc_pP->reassembly_missing_sn_detected == 0) {
            rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
            rlc_um_send_sdu(ctxt_pP, rlc_pP);
          } else {
            //clear sdu already done
            rlc_pP->stat_rx_data_pdu_dropped += 1;
            rlc_pP->stat_rx_data_bytes_dropped += tb_ind_p->size;
          }

          rlc_pP->reassembly_missing_sn_detected = 0;
          break;

        case RLC_FI_1ST_BYTE_DATA_IS_NOT_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_NOT_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
          printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU NO E_LI FI=00 (11) (%s:%u)\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                __FILE__,
                __LINE__);
#endif

          if (rlc_pP->reassembly_missing_sn_detected == 0) {
            // one whole segment of SDU in PDU
            rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
          } else {
#if TRACE_RLC_UM_DAR
            LOG_W(RLC, PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU NO E_LI FI=00 (11) MISSING SN DETECTED (%s:%u)\n",
                  PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                  __FILE__,
                  __LINE__);
#endif
            //printf("[MSC_NBOX][FRAME %05u][%s][RLC_UM][MOD %u/%u][RB %u][Missing SN detected][RLC_UM][MOD %u/%u][RB %u]\n",
            //      ctxt_pP->frame, rlc_pP->module_id,rlc_pP->rb_id, rlc_pP->module_id,rlc_pP->rb_id);
            rlc_pP->reassembly_missing_sn_detected = 1; // not necessary but for readability of the code
            rlc_pP->stat_rx_data_pdu_dropped += 1;
            rlc_pP->stat_rx_data_bytes_dropped += tb_ind_p->size;
#if RLC_STOP_ON_LOST_PDU
            AssertFatal( rlc_pP->reassembly_missing_sn_detected == 1,
                         PROTOCOL_RLC_UM_CTXT_FMT" MISSING PDU DETECTED (%s:%u)\n",
                         PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                         __FILE__,
                         __LINE__);
#endif
          }

          break;

        default:
          //AssertFatal( 0 , PROTOCOL_RLC_UM_CTXT_FMT" fi=%d! TRY REASSEMBLY SHOULD NOT GO HERE (%s:%u)\n",
          //             PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          //             fi,
          //             __FILE__,
          //             __LINE__);
          LOG_E(RLC, PROTOCOL_RLC_UM_CTXT_FMT" fi=%d! TRY REASSEMBLY SHOULD NOT GO HERE (%s:%u)\n",
                     PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP), fi, __FILE__, __LINE__);
          
        }
      } else {
        if (rlc_um_read_length_indicators(&data_p, e_li_p, li_array, &num_li, &size ) >= 0) {
          switch (fi) {
          case RLC_FI_1ST_BYTE_DATA_IS_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
            printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU FI=11 (00) Li=",
                  PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));

            for (i=0; i < num_li; i++) {
              printf("%d ",li_array[i]);
            }

            printf(" remaining size %d\n",size);
#endif
            // N complete SDUs
            //LGrlc_um_send_sdu(rlc_pP,ctxt_pP->frame,ctxt_pP->enb_flag);
            rlc_um_clear_rx_sdu(ctxt_pP, rlc_pP);

            for (i = 0; i < num_li; i++) {
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, li_array[i]);
              rlc_um_send_sdu(ctxt_pP, rlc_pP);
              data_p = &data_p[li_array[i]];
            }

            if (size > 0) { // normally should always be > 0 but just for help debug
              // data_p is already ok, done by last loop above
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
              rlc_um_send_sdu(ctxt_pP, rlc_pP);
            }

            rlc_pP->reassembly_missing_sn_detected = 0;
            break;

          case RLC_FI_1ST_BYTE_DATA_IS_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_NOT_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
            printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU FI=10 (01) Li=",
                  PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));

            for (i=0; i < num_li; i++) {
              printf("%d ",li_array[i]);
            }

            printf(" remaining size %d\n",size);
#endif
            // N complete SDUs + one segment of SDU in PDU
            //LG rlc_um_send_sdu(rlc_pP,ctxt_pP->frame,ctxt_pP->enb_flag);
            rlc_um_clear_rx_sdu(ctxt_pP, rlc_pP);

            for (i = 0; i < num_li; i++) {
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, li_array[i]);
              rlc_um_send_sdu(ctxt_pP, rlc_pP);
              data_p = &data_p[li_array[i]];
            }

            if (size > 0) { // normally should always be > 0 but just for help debug
              // data_p is already ok, done by last loop above
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
            }

            rlc_pP->reassembly_missing_sn_detected = 0;
            break;

          case RLC_FI_1ST_BYTE_DATA_IS_NOT_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
            printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU FI=01 (10) Li=",
                  PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));

            for (i=0; i < num_li; i++) {
              printf("%d ",li_array[i]);
            }

            printf(" remaining size %d\n",size);
#endif

            if (rlc_pP->reassembly_missing_sn_detected) {
              reassembly_start_index = 1;
              data_p = &data_p[li_array[0]];
              //rlc_pP->stat_rx_data_pdu_dropped += 1;
              rlc_pP->stat_rx_data_bytes_dropped += li_array[0];
            } else {
              reassembly_start_index = 0;
            }

            // one last segment of SDU + N complete SDUs in PDU
            for (i = reassembly_start_index; i < num_li; i++) {
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, li_array[i]);
              rlc_um_send_sdu(ctxt_pP, rlc_pP);
              data_p = &data_p[li_array[i]];
            }

            if (size > 0) { // normally should always be > 0 but just for help debug
              // data_p is already ok, done by last loop above
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
              rlc_um_send_sdu(ctxt_pP, rlc_pP);
            }

            rlc_pP->reassembly_missing_sn_detected = 0;
            break;

          case RLC_FI_1ST_BYTE_DATA_IS_NOT_1ST_BYTE_SDU_LAST_BYTE_DATA_IS_NOT_LAST_BYTE_SDU:
#if TRACE_RLC_UM_DAR
            printf(PROTOCOL_RLC_UM_CTXT_FMT" TRY REASSEMBLY PDU FI=00 (11) Li=",
                  PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));

            for (i=0; i < num_li; i++) {
              printf("%d ",li_array[i]);
            }

            printf(" remaining size %d\n",size);
#endif

            if (rlc_pP->reassembly_missing_sn_detected) {
#if TRACE_RLC_UM_DAR
              printf(PROTOCOL_RLC_UM_CTXT_FMT" DISCARD FIRST LI %d (%s:%u)",
                    PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                    li_array[0],
                    __FILE__,
                    __LINE__);
#endif
              reassembly_start_index = 1;
              data_p = &data_p[li_array[0]];
              //rlc_pP->stat_rx_data_pdu_dropped += 1;
              rlc_pP->stat_rx_data_bytes_dropped += li_array[0];
            } else {
              reassembly_start_index = 0;
            }

            for (i = reassembly_start_index; i < num_li; i++) {
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, li_array[i]);
              rlc_um_send_sdu(ctxt_pP, rlc_pP);
              data_p = &data_p[li_array[i]];
            }

            if (size > 0) { // normally should always be > 0 but just for help debug
              // data_p is already ok, done by last loop above
              rlc_um_reassembly (ctxt_pP, rlc_pP, data_p, size);
            } else {
              //AssertFatal( 0 !=0, PROTOCOL_RLC_UM_CTXT_FMT" size=%d! SHOULD NOT GO HERE (%s:%u)\n",
              //             PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
              //             size,
              //             __FILE__,
              //             __LINE__);
              LOG_E(RLC, PROTOCOL_RLC_UM_CTXT_FMT" size=%d! SHOULD NOT GO HERE (%s:%u)\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP), size, __FILE__, __LINE__);
              
              //rlc_pP->stat_rx_data_pdu_dropped += 1;
              rlc_pP->stat_rx_data_bytes_dropped += size;
            }

            rlc_pP->reassembly_missing_sn_detected = 0;
            break;

          default:
#if TRACE_RLC_UM_DAR
            LOG_W(RLC, PROTOCOL_RLC_UM_CTXT_FMT" Missing SN detected (%s:%u)\n",
                  PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                  __FILE__,
                  __LINE__);
#endif
            rlc_pP->stat_rx_data_pdu_dropped += 1;
            rlc_pP->stat_rx_data_bytes_dropped += tb_ind_p->size;

            rlc_pP->reassembly_missing_sn_detected = 1;
#if RLC_STOP_ON_LOST_PDU
            AssertFatal( rlc_pP->reassembly_missing_sn_detected == 1,
                         PROTOCOL_RLC_UM_CTXT_FMT" MISSING PDU DETECTED (%s:%u)\n",
                         PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                         __FILE__,
                         __LINE__);
#endif
          }
        } else {
          rlc_pP->stat_rx_data_pdu_dropped += 1;
          rlc_pP->stat_rx_data_bytes_dropped += tb_ind_p->size;
          rlc_pP->reassembly_missing_sn_detected = 1;

          LOG_W(RLC, "[SN %d] Bad RLC header! Discard this RLC PDU (size=%d)\n", sn, size);
        }
      }

#if TRACE_RLC_UM_DAR
      printf(PROTOCOL_RLC_UM_CTXT_FMT" REMOVE PDU FROM DAR BUFFER  SN=%03d (%s:%u)\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
            sn,
            __FILE__,
            __LINE__);
#endif
      free_mem_block(rlc_pP->dar_buffer[sn], __func__);
      rlc_pP->dar_buffer[sn] = NULL;
    } else {
      rlc_pP->last_reassemblied_missing_sn = sn;
#if TRACE_RLC_UM_DAR
      printf(PROTOCOL_RLC_UM_CTXT_FMT" Missing SN %04d detected, clearing RX SDU (%s:%u)\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
            sn,
            __FILE__,
            __LINE__);
#endif
      rlc_pP->reassembly_missing_sn_detected = 1;
      rlc_um_clear_rx_sdu(ctxt_pP, rlc_pP);
#if RLC_STOP_ON_LOST_PDU
      AssertFatal( rlc_pP->reassembly_missing_sn_detected == 1,
                   PROTOCOL_RLC_UM_CTXT_FMT" MISSING PDU DETECTED (%s:%u)\n",
                   PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                   __FILE__,
                   __LINE__);
#endif
    }

    sn = (sn + 1) % rlc_pP->rx_sn_modulo;

    if ((sn == rlc_pP->RX_Next_Highest) || (sn == end_snP)) {
      continue_reassembly = 0;
    }
  }

#if TRACE_RLC_UM_DAR
  printf(PROTOCOL_RLC_UM_CTXT_FMT" TRIED REASSEMBLY VR(UR)=%03d VR(UX)=%03d VR(UH)=%03d (%s:%u)\n",
        PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
        rlc_pP->RX_Next,
        rlc_pP->RX_Next_Reassembly,
        rlc_pP->RX_Next_Highest,
        __FILE__,
        __LINE__);
#endif

  VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_RLC_UM_TRY_REASSEMBLY,VCD_FUNCTION_OUT);
}
#endif
//-----------------------------------------------------------------------------
void rlc_um_stop_and_reset_timer_reordering(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_um_entity_t *            rlc_pP)
{
#if TRACE_RLC_UM_DAR
  printf(PROTOCOL_RLC_UM_CTXT_FMT" [T-REORDERING] STOPPED AND RESET\n",
        PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));
#endif
	rlc_pP->t_reassembly.running         = 0;
	rlc_pP->t_reassembly.ms_time_out     = 0;
	rlc_pP->t_reassembly.ms_start        = 0;
	rlc_pP->t_reassembly.timed_out       = 0;
}
//-----------------------------------------------------------------------------
void rlc_um_start_timer_reordering(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_um_entity_t *            rlc_pP)
{
	rlc_pP->t_reassembly.timed_out       = 0;

	if (rlc_pP->t_reassembly.ms_duration > 0) {
		rlc_pP->t_reassembly.running         = 1;
		rlc_pP->t_reassembly.ms_time_out      = PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) + rlc_pP->t_reassembly.ms_duration;
		rlc_pP->t_reassembly.ms_start        = PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP);
#if TRACE_RLC_UM_DAR
		printf(PROTOCOL_RLC_UM_CTXT_FMT" [T-REORDERING] STARTED (TIME-OUT = FRAME %05u)\n",
				PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
				rlc_pP->t_reassembly.ms_time_out);
#endif
	} else {
		printf("[T-REORDERING] NOT STARTED, CAUSE CONFIGURED 0 ms\n");
	}
}
//-----------------------------------------------------------------------------
void rlc_um_init_timer_reordering(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const rlc_pP,
  const uint32_t  ms_durationP)
{
  rlc_pP->t_reassembly.running         = 0;
  rlc_pP->t_reassembly.ms_time_out     = 0;
  rlc_pP->t_reassembly.ms_start        = 0;
  rlc_pP->t_reassembly.ms_duration     = ms_durationP;
  rlc_pP->t_reassembly.timed_out       = 0;
}
//-----------------------------------------------------------------------------
void rlc_um_check_timer_dar_time_out(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_um_entity_t * const rlc_pP)
{
  signed int     in_window;
  rlc_usn_t      old_RX_Next;


//  VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_RLC_UM_CHECK_TIMER_DAR_TIME_OUT,VCD_FUNCTION_IN);

  if ((rlc_pP->t_reassembly.running)) {
    if (
      // CASE 1:          start              time out
      //        +-----------+------------------+----------+
      //        |           |******************|          |
      //        +-----------+------------------+----------+
      //FRAME # 0                                     FRAME MAX
      ((rlc_pP->t_reassembly.ms_start < rlc_pP->t_reassembly.ms_time_out) &&
       ((PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) >= rlc_pP->t_reassembly.ms_time_out) ||
        (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) < rlc_pP->t_reassembly.ms_start)))                                   ||
      // CASE 2:        time out            start
      //        +-----------+------------------+----------+
      //        |***********|                  |**********|
      //        +-----------+------------------+----------+
      //FRAME # 0                                     FRAME MAX VALUE
      ((rlc_pP->t_reassembly.ms_start > rlc_pP->t_reassembly.ms_time_out) &&
       (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) < rlc_pP->t_reassembly.ms_start) &&
       (PROTOCOL_CTXT_TIME_MILLI_SECONDS(ctxt_pP) >= rlc_pP->t_reassembly.ms_time_out))
    ) {

      //if ((uint32_t)((uint32_t)rlc_pP->timer_reordering  + (uint32_t)rlc_pP->timer_reordering_init)   <= ctxt_pP->frame) {
      // 5.1.2.2.4   Actions when t-Reordering expires
      //  When t-Reordering expires, the receiving UM RLC entity shall:
      //  -update VR(UR) to the SN of the first UMD PDU with SN >= VR(UX) that has not been received;
      //  -reassemble RLC SDUs from any UMD PDUs with SN < updated VR(UR), remove RLC headers when doing so and deliver the reassembled RLC SDUs to upper layer in ascending order of the RLC SN if not delivered before;
      //  -if VR(UH) > VR(UR):
      //      -start t-Reordering;
      //      -set VR(UX) to VR(UH).
      rlc_pP->stat_timer_reordering_timed_out += 1;
#if TRACE_RLC_UM_DAR
      printf(PROTOCOL_RLC_UM_CTXT_FMT"*****************************************************\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));
      printf(PROTOCOL_RLC_UM_CTXT_FMT"*    T I M E  -  O U T                              *\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));
      printf(PROTOCOL_RLC_UM_CTXT_FMT"*****************************************************\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));
      printf(PROTOCOL_RLC_UM_CTXT_FMT" TIMER t-Reordering expiration\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP));
      printf(PROTOCOL_RLC_UM_CTXT_FMT" timer_reordering=%d frame=%d expire ms %d\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
            rlc_pP->t_reassembly.ms_duration,
            ctxt_pP->frame,
            rlc_pP->t_reassembly.ms_time_out);
      printf(PROTOCOL_RLC_UM_CTXT_FMT" set VR(UR)=%03d to",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
            rlc_pP->RX_Next);
#endif

#if 0
      if (pthread_mutex_trylock(&rlc_pP->lock_dar_buffer) == 0) {
        old_RX_Next   = rlc_pP->RX_Next;

        rlc_pP->RX_Next = rlc_pP->RX_Next_Reassembly;

        while (rlc_um_get_pdu_from_dar_buffer(ctxt_pP, rlc_pP, rlc_pP->RX_Next)) {
          rlc_pP->RX_Next = (rlc_pP->RX_Next+1)%rlc_pP->rx_sn_modulo;
        }

#if TRACE_RLC_UM_DAR
        printf(" %d", rlc_pP->RX_Next);
        printf("\n");
#endif
        rlc_um_try_reassembly(ctxt_pP, rlc_pP ,old_RX_Next, rlc_pP->RX_Next);

        in_window = rlc_um_in_window(ctxt_pP, rlc_pP, rlc_pP->RX_Next,  rlc_pP->RX_Next_Highest,  rlc_pP->RX_Next_Highest);

        if (in_window == 2) {
          rlc_um_start_timer_reordering(ctxt_pP, rlc_pP);
          rlc_pP->RX_Next_Reassembly = rlc_pP->RX_Next_Highest;
#if TRACE_RLC_UM_DAR
          printf(PROTOCOL_RLC_UM_CTXT_FMT" restarting t-Reordering set VR(UX) to %d (VR(UH)>VR(UR))\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                rlc_pP->RX_Next_Reassembly);
#endif
        } else {
#if TRACE_RLC_UM_DAR
          printf(PROTOCOL_RLC_UM_CTXT_FMT" STOP t-Reordering VR(UX) = %03d\n",
                PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
                rlc_pP->RX_Next_Reassembly);
#endif
          rlc_um_stop_and_reset_timer_reordering(ctxt_pP, rlc_pP);
        }

        RLC_UM_MUTEX_UNLOCK(&rlc_pP->lock_dar_buffer);
      }
#endif
    }
  }

//  VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_RLC_UM_CHECK_TIMER_DAR_TIME_OUT,VCD_FUNCTION_OUT);
}
//-----------------------------------------------------------------------------
#if 1
mem_block_t* rlc_um_remove_pdu_from_dar_buffer(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_um_entity_t * const rlc_pP)
{
	mem_block_t * pdu_p     = rlc_pP->pdus_from_mac_layer.head;
	rlc_um_pdu_info_t  *pdu_info_p        = &((rlc_um_rx_pdu_management_t*)(pdu_p->data))->pdu_info;
#if TRACE_RLC_UM_DAR
	printf(PROTOCOL_RLC_UM_CTXT_FMT" REMOVE PDU FROM DAR BUFFER  SN=%03d\n",
	PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
	snP);
#endif

	while(pdu_p) {
		if(rlc_um_in_reassembly_window(ctxt_pP, rlc_pP, pdu_info_p->sn) != 0) {
			list2_remove_head(&rlc_pP->pdus_from_mac_layer);
		} else {
			break;
		}

		pdu_p = list2_get_head(&rlc_pP->pdus_from_mac_layer);
	}

	return pdu_p;
}
#else
//-----------------------------------------------------------------------------
mem_block_t*
rlc_um_remove_pdu_from_dar_buffer(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const rlc_pP,
  rlc_usn_t snP)
{
  mem_block_t * pdu_p     = rlc_pP->dar_buffer[snP];
#if TRACE_RLC_UM_DAR
  printf(PROTOCOL_RLC_UM_CTXT_FMT" REMOVE PDU FROM DAR BUFFER  SN=%03d\n",
        PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
        snP);
#endif
  rlc_pP->dar_buffer[snP] = NULL;
  return pdu_p;
}
#endif
//-----------------------------------------------------------------------------
mem_block_t* rlc_um_get_pdu_from_dar_buffer(const protocol_ctxt_t* const ctxt_pP,
													rlc_um_entity_t * const rlc_pP,
													const rlc_usn_t snP)
{
	return rlc_pP->dar_buffer[snP];
}
//-----------------------------------------------------------------------------
#if 1
rlc_am_rx_pdu_status_t rlc_um_store_pdu_in_dar_buffer(
							  const protocol_ctxt_t* const ctxt_pP,
							  rlc_um_entity_t * const rlc_pP,
							  mem_block_t *pdu_pP)
{
	rlc_um_pdu_info_t* pdu_rx_info_p = &((rlc_um_rx_pdu_management_t*)(pdu_pP->data))->pdu_info;
	mem_block_t*       cursor_p                    = NULL;
	mem_block_t*       previous_cursor_p			 = NULL;
	rlc_am_pdu_info_t* pdu_info_cursor_p           = NULL;
	rlc_am_rx_pdu_status_t pdu_status = RLC_AM_DATA_PDU_STATUS_OK;

	cursor_p = rlc_pP->pdus_from_mac_layer.head;

//	如果缓冲链表为空，则插入数据在链表头
	if(cursor_p == NULL)
	{
		list2_add_head(pdu_pP, &rlc_pP->pdus_from_mac_layer);
		return pdu_status;
	}
	else
	{
//		当存储节点SN>接收数据SN或者SN相同，但是存储节点SO>=接收节点SO时，中断扫描
		do
		{
			pdu_info_cursor_p = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;

			if(((pdu_info_cursor_p->sn - (rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size)) % rlc_pP->rx_sn_modulo >
    				(pdu_rx_info_p->sn - (rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size)) % rlc_pP->rx_sn_modulo) ||
					((pdu_info_cursor_p->sn == pdu_rx_info_p->sn) && (pdu_info_cursor_p->so >= pdu_rx_info_p->so)))
			{
				break;
			}

			previous_cursor_p = cursor_p;
			cursor_p = cursor_p->next;
		}
		while(cursor_p != NULL);

//		存在前一个节点，数据插入前一个节点后
		if(previous_cursor_p)
		{
			list2_insert_after_element(pdu_pP, previous_cursor_p, &rlc_pP->pdus_from_mac_layer);
		}
		else // 插入当前节点前
		{
			list2_insert_before_element(pdu_pP, cursor_p, &rlc_pP->pdus_from_mac_layer);
		}
	}
}
#else
void
rlc_um_store_pdu_in_dar_buffer(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const rlc_pP,
  mem_block_t *pdu_pP,
  rlc_usn_t snP)
{
#if TRACE_RLC_UM_DAR
  printf(PROTOCOL_RLC_UM_CTXT_FMT" STORE PDU IN DAR BUFFER  SN=%03d  VR(UR)=%03d VR(UX)=%03d VR(UH)=%03d\n",
        PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
        snP,
        rlc_pP->RX_Next,
        rlc_pP->RX_Next_Reassembly,
        rlc_pP->RX_Next_Highest);
#endif
  rlc_pP->dar_buffer[snP] = pdu_pP;
}
#endif
//-----------------------------------------------------------------------------
uint16_t rlc_um_rx_check_all_byte_segments(
	const protocol_ctxt_t* const  ctxt_pP,
	rlc_um_entity_t* const rlc_pP,
	mem_block_t* const pdu_pP)
{
	rlc_um_pdu_info_t  *pdu_info_p        = &((rlc_um_rx_pdu_management_t*)(pdu_pP->data))->pdu_info;
	mem_block_t        *cursor_p        = NULL;
	mem_block_t        *first_cursor_p  = NULL;
	uint32_t            sn              = pdu_info_p->sn;
	sdu_size_t          next_waited_so;
	uint16_t           sdu_size = 0;

	cursor_p = pdu_pP;

// get all previous PDU with same SN
	while (cursor_p->previous != NULL)
	{
		if (((rlc_um_rx_pdu_management_t*)(cursor_p->previous->data))->pdu_info.sn == sn)
		{
		  //list2_add_head(cursor_p->previous, &list);
		  cursor_p = cursor_p->previous;
		  //msg("rlc_am_rx_check_all_byte_segments(%d) @2\n",sn);
		}
		else
		{
		  break;
		}
	}

	pdu_info_p = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;

	if (pdu_info_p->so != 0)
	{
		return 0;
	}

	next_waited_so = pdu_info_p->payload_size;
	first_cursor_p = cursor_p;

	while (cursor_p->next != NULL)
	{
		//msg("rlc_am_rx_check_all_byte_segments(%d) @4\n",sn);
		cursor_p = cursor_p->next;
		pdu_info_p = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;

		if (pdu_info_p->sn == sn)
		{
			if (pdu_info_p->so == next_waited_so)
			{
			  next_waited_so = next_waited_so + pdu_info_p->payload_size;
			  //msg("rlc_am_rx_check_all_byte_segments(%d) @6\n",sn);
			}
			else
			{ // assumed pdu_info_p->so + pdu_info_p->payload_size > next_waited_so
			  //next_waited_so = (next_waited_so + pdu_info_p->payload_size) - (next_waited_so - pdu_info_p->so);
			  //msg("rlc_am_rx_check_all_byte_segments(%d) @7\n",sn);
				return 0;
			}

			if (pdu_info_p->si == RLC_SI_DATA_FIELD_CONTAINS_THE_LAST_SEGMENT_OF_AN_RLC_SDU)
			{
				sdu_size = pdu_info_p->so + pdu_info_p->payload_size;
			  //msg("rlc_am_rx_check_all_byte_segments(%d) @8\n",sn);
			  rlc_um_rx_mark_all_segments_received(ctxt_pP, rlc_pP,  first_cursor_p);
			  return sdu_size;
			}
		}
		else
		{
		  //msg("rlc_am_rx_check_all_byte_segments(%d) @9\n",sn);
		  return 0;
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------
void rlc_um_rx_mark_all_segments_received(const protocol_ctxt_t* const  ctxt_pP,
													rlc_um_entity_t* const        rlc_pP,
													mem_block_t* const            fisrt_segment_tbP)
{
	rlc_um_pdu_info_t* pdu_info_p          = &((rlc_um_rx_pdu_management_t*)(fisrt_segment_tbP->data))->pdu_info;
	rlc_um_pdu_info_t* pdu_info_cursor_p = NULL;
	mem_block_t*       cursor_p          = NULL;
	rlc_sn_t           sn                = pdu_info_p->sn;

	cursor_p = fisrt_segment_tbP;

	if (cursor_p) {
		printf("[PROCESS RX PDU] ALL SEGMENTS RECEIVED SN %04d:\n", sn);

		do {
			pdu_info_cursor_p = &((rlc_am_rx_pdu_management_t*)(cursor_p->data))->pdu_info;

			if (pdu_info_cursor_p->sn == sn) {
				((rlc_am_rx_pdu_management_t*)(cursor_p->data))->all_segments_received = 1;
			} else {
				return;
			}

			cursor_p = cursor_p->next;
		} while (cursor_p != NULL);
	}
}
//-----------------------------------------------------------------------------
#if 1
// assumed the sn of the tb_p is equal to RX_Next_Reassembly, outside of the reassembly window,t-Reassembly expires
void rlc_um_rx_update_RX_Next_Reassembly(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_um_entity_t * const rlc_pP,
	mem_block_t* tb_pP,
	int8_t type)
{
	rlc_um_pdu_info_t* pdu_info_cursor_p = NULL;
	mem_block_t*       cursor_p;
	mem_block_t*       previous_cursor_p			 = NULL;

	cursor_p = tb_pP;

	if (cursor_p) {
		do {
			if(((rlc_um_rx_pdu_management_t*)(cursor_p->data))->all_segments_received) {
				rlc_pP->RX_Next_Reassembly = (pdu_info_cursor_p->sn + 1) % rlc_pP->rx_sn_modulo;
				cursor_p = cursor_p->next;
			} else {
				pdu_info_cursor_p = &((rlc_um_rx_pdu_management_t*)(cursor_p->data))->pdu_info;

				switch (type)
				{
				case 0:
					if(pdu_info_cursor_p->sn != rlc_pP->RX_Next_Reassembly) {
						rlc_pP->RX_Next_Reassembly = pdu_info_cursor_p->sn;
						return;
					}
					break;
				case 1:
					if(((pdu_info_cursor_p->sn - (rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size)) % rlc_pP->rx_sn_modulo) >=0) {
						rlc_pP->RX_Next_Reassembly = pdu_info_cursor_p->sn;
					}
					break;
				case 2:
					if(((pdu_info_cursor_p->sn - (rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size)) % rlc_pP->rx_sn_modulo) >=
							((rlc_pP->RX_Timer_Trigger - (rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size)) % rlc_pP->rx_sn_modulo)) {
						rlc_pP->RX_Next_Reassembly = pdu_info_cursor_p->sn;
					}
					break;
				default:
					break;
				}
			}

			previous_cursor_p = cursor_p;
			cursor_p = cursor_p->next;
		} while (cursor_p != NULL);
	}
}
#else
void
rlc_um_rx_update_RX_Next_Reassembly(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const rlc_pP,
  mem_block_t* tb_pP)
{
  rlc_um_pdu_info_t* pdu_info_cursor_p = NULL;
  mem_block_t*       cursor_p;

  cursor_p = tb_pP;

  if (cursor_p)
  {
    do
    {
      pdu_info_cursor_p = &((rlc_um_rx_pdu_management_t*)(cursor_p->data))->pdu_info;

      if ((((rlc_um_rx_pdu_management_t*)(cursor_p->data))->all_segments_received == 0) ||
          (rlc_pP->RX_Next_Reassembly != pdu_info_cursor_p->sn))
      {
#if TRACE_RLC_AM_RX
        printf(PROTOCOL_RLC_AM_CTXT_FMT"[UPDATE VR(MS)] UPDATED VR(MS) %04d -> %04d\n",
              PROTOCOL_RLC_AM_CTXT_ARGS(ctxt_pP,rlc_pP),
              rlc_pP->vr_ms, pdu_info_cursor_p->sn);
#endif
        rlc_pP->RX_Next_Reassembly = pdu_info_cursor_p->sn;

        break;
      }

      cursor_p = cursor_p->next;
    }
    while (cursor_p != NULL);

    rlc_pP->RX_Next_Reassembly = (rlc_pP->RX_Next_Reassembly + 1) % rlc_pP->rx_sn_modulo;
  }
}
#endif
//-----------------------------------------------------------------------------
// returns -2 if lower_bound  > sn
// returns -1 if higher_bound < sn
// returns  0 if lower_bound  < sn < higher_bound
// returns  1 if lower_bound  == sn
// returns  2 if higher_bound == sn
// returns  3 if higher_bound == sn == lower_bound
signed int rlc_um_in_window(
	const protocol_ctxt_t* const ctxt_pP,
	rlc_um_entity_t * const rlc_pP,
	rlc_sn_t lower_boundP,
	rlc_sn_t snP,
	rlc_sn_t higher_boundP)
{
  rlc_sn_t modulus = (rlc_sn_t)rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size;
#if TRACE_RLC_UM_RX
  rlc_sn_t     lower_bound  = lower_boundP;
  rlc_sn_t     higher_bound = higher_boundP;
  rlc_sn_t     sn           = snP;
#endif
  lower_boundP  = (lower_boundP  - modulus) % rlc_pP->rx_sn_modulo;
  higher_boundP = (higher_boundP - modulus) % rlc_pP->rx_sn_modulo;
  snP           = (snP           - modulus) % rlc_pP->rx_sn_modulo;

  if ( lower_boundP > snP) {
#if TRACE_RLC_UM_RX
    printf(PROTOCOL_RLC_UM_CTXT_FMT" %d not in WINDOW[%03d:%03d] (SN<LOWER BOUND)\n",
          PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          sn,
          lower_bound,
          higher_bound);
#endif
    return -2;
  }

  if ( higher_boundP < snP) {
#if TRACE_RLC_UM_RX
    printf(PROTOCOL_RLC_UM_CTXT_FMT" %d not in WINDOW[%03d:%03d] (SN>HIGHER BOUND) <=> %d not in WINDOW[%03d:%03d]\n",
          PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          sn,
          lower_bound,
          higher_bound,
          snP,
          lower_boundP,
          higher_boundP);
#endif
    return -1;
  }

  if ( lower_boundP == snP) {
    if ( higher_boundP == snP) {
#if TRACE_RLC_UM_RX
      printf(PROTOCOL_RLC_UM_CTXT_FMT" %d  in WINDOW[%03d:%03d] (SN=HIGHER BOUND=LOWER BOUND)\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
            sn,
            lower_bound,
            higher_bound);
#endif
      return 3;
    }

#if TRACE_RLC_UM_RX
    printf(PROTOCOL_RLC_UM_CTXT_FMT" %d  in WINDOW[%03d:%03d] (SN=LOWER BOUND)\n",
          PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          sn,
          lower_bound,
          higher_bound);
#endif
    return 1;
  }

  if ( higher_boundP == snP) {
#if TRACE_RLC_UM_RX
    printf(PROTOCOL_RLC_UM_CTXT_FMT" %d  in WINDOW[%03d:%03d] (SN=HIGHER BOUND)\n",
          PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          sn,
          lower_bound,
          higher_bound);
#endif
    return 2;
  }

  return 0;

}
//-----------------------------------------------------------------------------
signed int
rlc_um_in_reordering_window(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const rlc_pP,
  const rlc_sn_t snP)
{
  rlc_sn_t   modulus = (signed int)rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size;
  rlc_sn_t   sn_mod = (snP - modulus) % rlc_pP->rx_sn_modulo;

  if ( 0 <= sn_mod) {
    if (sn_mod < rlc_pP->rx_um_window_size) {
#if TRACE_RLC_UM_DAR
      printf(PROTOCOL_RLC_UM_CTXT_FMT" %d IN REORDERING WINDOW[%03d:%03d[ SN %d IN [%03d:%03d[ VR(UR)=%03d VR(UH)=%03d\n",
            PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
            sn_mod,
            0,
            rlc_pP->rx_um_window_size,
            snP,
            (signed int)rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size,
            rlc_pP->RX_Next_Highest,
            rlc_pP->RX_Next,
            rlc_pP->RX_Next_Highest);
#endif
      return 0;
    }
  }

#if TRACE_RLC_UM_DAR

  if (modulus < 0) {
    printf(PROTOCOL_RLC_UM_CTXT_FMT" %d NOT IN REORDERING WINDOW[%03d:%03d[ SN %d NOT IN [%03d:%03d[ VR(UR)=%03d VR(UH)=%03d\n",
          PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          sn_mod,
          modulus + 1024,
          rlc_pP->rx_um_window_size,
          snP,
          modulus + 1024 ,
          rlc_pP->RX_Next_Highest,
          rlc_pP->RX_Next,
          rlc_pP->RX_Next_Highest);
  } else {
    printf(PROTOCOL_RLC_UM_CTXT_FMT" %d NOT IN REORDERING WINDOW[%03d:%03d[ SN %d NOT IN [%03d:%03d[ VR(UR)=%03d VR(UH)=%03d\n",
          PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP, rlc_pP),
          sn_mod,
          modulus,
          rlc_pP->rx_um_window_size,
          snP,
          modulus ,
          rlc_pP->RX_Next_Highest,
          rlc_pP->RX_Next,
          rlc_pP->RX_Next_Highest);
  }

#endif
  return -1;
}
//-----------------------------------------------------------------------------
#define TRACE_RLC_UM_DAR 1
signed int
rlc_um_in_reassembly_window(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const rlc_pP,
  const rlc_sn_t snP)
{
  rlc_sn_t   modulus = (signed int)rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size;
  rlc_sn_t   sn_mod = (snP - modulus) % rlc_pP->rx_sn_modulo;

  if ( 0 <= sn_mod)
  {
    if (sn_mod < rlc_pP->rx_um_window_size)
    {
#if TRACE_RLC_UM_DAR
      printf(" %d IN REORDERING WINDOW[%03d:%03d[ SN %d IN [%03d:%03d\n",
            sn_mod,
            0,
            rlc_pP->rx_um_window_size,
            snP,
            (signed int)rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size,
            rlc_pP->RX_Next_Highest);
#endif
      return 0;
    }
  }

#if TRACE_RLC_UM_DAR

  if (modulus < 0)
  {
    printf(" %d NOT IN REORDERING WINDOW[%03d:%03d[ SN %d NOT IN [%03d:%03d[\n",
          sn_mod,
          modulus + 1024,
          rlc_pP->rx_um_window_size,
          snP,
          modulus + 1024 ,
          rlc_pP->RX_Next_Highest);
  }
  else
  {
    printf(" %d NOT IN REORDERING WINDOW[%03d:%03d[ SN %d NOT IN [%03d:%03d\n",
          sn_mod,
          modulus,
          rlc_pP->rx_um_window_size,
          snP,
          modulus ,
          rlc_pP->RX_Next_Highest);
  }

#endif
  return -1;
}

#undef TRACE_RLC_UM_DAR
//-----------------------------------------------------------------------------
void
rlc_um_receive_process_dar (
  const protocol_ctxt_t* const ctxt_pP,
  rlc_um_entity_t * const      rlc_pP,
  mem_block_t *                pdu_mem_pP,
  uint8_t * const   pdu_pP,
  const sdu_size_t             tb_sizeP)
{
//	3GPP 38.322 v15.6.0 5.2.2.2	Receive operations
//	5.2.2.2.1	General
//	The receiving UM RLC entity shall maintain a reassembly window according to state variable RX_Next_Highest as follows:
//		-	a SN falls within the reassembly window if (RX_Next_Highest – UM_Window_Size) <= SN <RX_Next_Highest;
//		-	a SN falls outside of the reassembly window otherwise.
//	When receiving an UMD PDU from lower layer, the receiving UM RLC entity shall:
//		-	either deliver the UMD PDU to upper layer after removing the RLC header, discard the received UMD PDU, or place it in the reception buffer (see sub clause 5.2.2.2.2);
//		-	if the received UMD PDU was placed in the reception buffer:
//			-	update state variables, reassemble and deliver RLC SDUs to upper layer and start/stop t-Reassembly as needed (see sub clause 5.2.2.2.3).
//	When t-Reassembly expires, the receiving UM RLC entity shall:
//		-	update state variables, discard RLC SDU segments and start t-Reassembly as needed (see sub clause 5.2.2.2.4).


//	5.2.2.2.2	Actions when an UMD PDU is received from lower layer
//	When an UMD PDU is received from lower layer, the receiving UM RLC entity shall:
//		-	if the UMD PDU header does not contain an SN:
//			-	remove the RLC header and deliver the RLC SDU to upper layer.
//		-	else if (RX_Next_Highest – UM_Window_Size) <= SN < RX_Next_Reassembly:
//			-	discard the received UMD PDU.
//		-	else:
//			-	place the received UMD PDU in the reception buffer.

  rlc_sn_t sn = -1;
  signed int in_window;
  rlc_um_pdu_info_t* pdu_info_pP = &((rlc_um_rx_pdu_management_t*)(pdu_mem_pP->data))->pdu_info;
  rlc_am_rx_pdu_status_t pdu_status		= RLC_AM_DATA_PDU_STATUS_OK;
  uint16_t sdu_size = 0;

//  VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME(VCD_SIGNAL_DUMPER_FUNCTIONS_RLC_UM_RECEIVE_PROCESS_DAR, VCD_FUNCTION_IN);

  if(rlc_um_get_pdu_infos(ctxt_pP, rlc_pP, pdu_pP, tb_sizeP, pdu_info_pP) >= 0)
  {
	  ((rlc_um_rx_pdu_management_t*)(pdu_mem_pP->data))->all_segments_received = 0;

//	  如果包含一个完整的RLC SDU，则直接上传
	  if(pdu_info_pP->si == RLC_SI_DATA_FIELD_CONTAINS_ALL_BYTES_OF_AN_RLC_SDU)
	  {
		  rlc_pP->output_sdu_in_construction = get_free_mem_block(pdu_info_pP->payload_size, __func__);

		  if(rlc_pP->output_sdu_in_construction)
		  {
			  rlc_pP->output_sdu_size_to_write = pdu_info_pP->payload_size;

			  memcpy(rlc_pP->output_sdu_in_construction->data, pdu_info_pP->payload, pdu_info_pP->payload_size);

			  rlc_um_send_sdu(ctxt_pP, rlc_pP);
		  }
		  else
		  {
			  printf("[REASSEMBLY]ERROR  OUTPUT SDU IS NULL\n");
		  }
	  }
	  else
	  {
		  in_window = rlc_um_in_window(ctxt_pP, rlc_pP, rlc_pP->RX_Next_Highest - rlc_pP->rx_um_window_size, pdu_info_pP->sn, rlc_pP->RX_Next_Reassembly);

//		  if (RX_Next_Highest – UM_Window_Size) <= SN < RX_Next_Reassembly:
//		  		-	discard the received UMD PDU.
		  if(in_window == 0 || in_window == 1)
		  {
			  rlc_pP->stat_rx_data_pdu_out_of_window   += 1;
			  rlc_pP->stat_rx_data_bytes_out_of_window += tb_sizeP;
			  free_mem_block(pdu_mem_pP, __func__);
			  pdu_mem_pP = NULL;
			  return;
		  }
		  else
		  {
			  pdu_status = rlc_um_store_pdu_in_dar_buffer(ctxt_pP, rlc_pP, pdu_mem_pP);

//			  5.2.2.2.3	Actions when an UMD PDU is placed in the reception buffer
//			  When an UMD PDU with SN = x is placed in the reception buffer, the receiving UM RLC entity shall:
//			  	-	if all byte segments with SN = x are received:
//			  		-	reassemble the RLC SDU from all byte segments with SN = x, remove RLC headers and deliver the reassembled RLC SDU to upper layer;
//			  		-	if x = RX_Next_Reassembly:
//			  			-	update RX_Next_Reassembly to the SN of the first SN > current RX_Next_Reassembly that has not been reassembled and delivered to upper layer.
//			  	-	else if x falls outside of the reassembly window:
//			  		-	update RX_Next_Highest to x + 1;
//			  		-	discard any UMD PDUs with SN that falls outside of the reassembly window;
//			  		-	if RX_Next_Reassembly falls outside of the reassembly window:
//			  			-	set RX_Next_Reassembly to the SN of the first SN >= (RX_Next_Highest – UM_Window_Size) that has not been reassembled and delivered to upper layer.
//			  	-	if t-Reassembly is running:
//			  		-	if RX_Timer_Trigger <= RX_Next_Reassembly; or
//			  		-	if RX_Timer_Trigger falls outside of the reassembly window and RX_Timer_Trigger is not equal to RX_Next_Highest; or
//			  		-	if RX_Next_Highest = RX_Next_Reassembly + 1 and there is no missing byte segment of the RLC SDU associated with SN = RX_Next_Reassembly before the last byte of all received segments of this RLC SDU:
//			  			-	stop and reset t-Reassembly.
//			  	-	if t-Reassembly is not running (includes the case when t-Reassembly is stopped due to actions above):
//			  		-	if RX_Next_Highest > RX_Next_Reassembly + 1; or
//			  		-	if RX_Next_Highest = RX_Next_Reassembly + 1 and there is at least one missing byte segment of the RLC SDU associated with SN = RX_Next_Reassembly before the last byte of all received segments of this RLC SDU:
//			  			-	start t-Reassembly;
//			  			-	set RX_Timer_Trigger to RX_Next_Highest.

			  sdu_size = rlc_um_rx_check_all_byte_segments(ctxt_pP, rlc_pP, pdu_mem_pP);

			  if(sdu_size)
			  {
				  rlc_um_try_reassembly(ctxt_pP, rlc_pP, pdu_mem_pP, sdu_size);

				  if(pdu_info_pP->sn == rlc_pP->RX_Next_Reassembly)
				  {
					  rlc_um_rx_update_RX_Next_Reassembly(ctxt_pP, rlc_pP, pdu_mem_pP, 0);
				  }
			  }

			  if(rlc_um_in_reassembly_window(ctxt_pP, rlc_pP, pdu_info_pP->sn) != 0)
			  {
				  rlc_pP->RX_Next_Highest = (pdu_info_pP->sn + 1) % (1 << rlc_pP->rx_sn_length);

				  rlc_um_remove_pdu_from_dar_buffer(ctxt_pP, rlc_pP);

				  if(rlc_um_in_reassembly_window(ctxt_pP, rlc_pP, rlc_pP->RX_Next_Reassembly) != 0)
				  {
//					  TODO 这个地方算法可能有问题，初步修复
					  rlc_um_rx_update_RX_Next_Reassembly(ctxt_pP, rlc_pP, pdu_mem_pP, 1);
				  }
			  }

			  if(rlc_pP->t_reassembly.running)
			  {
			  }

			  if(rlc_pP->t_reassembly.running == 0)
			  {
			  }
		  }
	  }
  }
  else
  {
	  pdu_status = RLC_AM_DATA_PDU_STATUS_HEADER_ERROR;
	  printf("[PROCESS RX PDU]  PDU DISCARDED BAD HEADER FORMAT SN=%d\n", pdu_info_pP->sn);
  }
}
