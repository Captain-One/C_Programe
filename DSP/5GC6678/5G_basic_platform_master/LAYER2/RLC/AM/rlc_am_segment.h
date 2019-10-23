#ifndef __RLC_AM_SEGMENT_H__
#define __RLC_AM_SEGMENT_H__
//-----------------------------------------------------------------------------

/*! \fn void rlc_am_pdu_polling (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t *const rlcP, rlc_am_pdu_sn_10_t *pduP, int16_t payload_sizeP,boolean_t is_new_pdu)
* \brief      Set or not the poll bit in the PDU header depending on RLC AM protocol variables.
* \param[in]  ctxt_pP          Running context.
* \param[in]  rlcP           RLC AM protocol instance pointer.
* \param[in]  pduP           Pointer on the header of the PDU in order to be able to set the poll bit if necessary.
* \param[in]  payload_sizeP  Size of the payload of the PDU.
*/
//void rlc_am_pdu_polling (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t *const rlcP, rlc_am_pdu_sn_10_t *pduP, int16_t payload_sizeP,boolean_t is_new_pdu);

void rlc_am_pdu_polling (
  const protocol_ctxt_t* const  ctxt_pP,
  rlc_am_entity_t *const rlc_pP,
  uint8_t *const pdu_pP,
  const int16_t payload_sizeP,
  boolean_t is_new_pdu);

/*! \fn void rlc_am_segment_10 (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t * const rlcP)
* \brief      Segment a PDU with 10 bits sequence number, based on segmentation information given by MAC (size to transmit).
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
*/
void rlc_am_segment_10 (const protocol_ctxt_t* const  ctxt_pP,rlc_am_entity_t *const rlcP);
/** @} */
#    endif
