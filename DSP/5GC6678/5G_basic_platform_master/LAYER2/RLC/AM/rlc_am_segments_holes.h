#ifndef __RLC_AM_SEGMENT_HOLES_H__
#define __RLC_AM_SEGMENT_HOLES_H__
//-----------------------------------------------------------------------------
/*! \fn void rlc_am_clear_holes (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t * const rlcP, rlc_sn_t snP)
* \brief      Remove all marked holes for PDU with sequence number "snP".
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP           RLC AM protocol instance pointer.
* \param[in]  snP            Sequence number.
*/
void rlc_am_clear_holes (
                                  const protocol_ctxt_t* const  ctxt_pP,
                                  rlc_am_entity_t *const rlcP,
                                  const rlc_sn_t snP);

/*! \fn void rlc_am_remove_hole (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t * const rlcP,  rlc_sn_t snP, sdu_size_t so_startP, sdu_size_t so_stopP)
* \brief      Remove for PDU with sequence number "snP" a NACK for byte segment offset [so_startP, so_stopP].
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP           RLC AM protocol instance pointer.
* \param[in]  snP            Sequence number.
* \param[in]  so_startP      Start of segment offset.
* \param[in]  so_stopP       End of segment offset.
*/
void rlc_am_remove_hole (
                                  const protocol_ctxt_t* const  ctxt_pP,
                                  rlc_am_entity_t *const rlcP,
                                  const rlc_sn_t   snP,
                                  const sdu_size_t so_startP,
                                  const sdu_size_t so_stopP);

/*! \fn void rlc_am_get_next_hole (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t * const rlcP, rlc_sn_t snP, sdu_size_t* so_startP, sdu_size_t* so_stopP)
* \brief      Get for PDU with sequence number "snP" the first hole start and stop parameters.
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP           RLC AM protocol instance pointer.
* \param[in]  snP            Sequence number.
* \param[in,out]  so_startP  Start of segment offset.
* \param[in,out]  so_stopP   End of segment offset.
*/
void rlc_am_get_next_hole (
                                  const protocol_ctxt_t* const  ctxt_pP,
                                  rlc_am_entity_t *const rlcP,
                                  const rlc_sn_t snP,
                                  sdu_size_t* const so_startP,
                                  sdu_size_t* const so_stopP);

/*! \fn void rlc_am_add_hole (const protocol_ctxt_t* const  ctxt_pP, rlc_am_entity_t * const rlcP, rlc_sn_t snP, sdu_size_t so_startP, sdu_size_t so_stopP)
* \brief      Mark for PDU with sequence number "snP" a NACK for byte segment offset [so_startP, so_stopP].
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP           RLC AM protocol instance pointer.
* \param[in]  snP            Sequence number.
* \param[in,out]  so_startP  Start of segment offset.
* \param[in,out]  so_stopP   End of segment offset.
*/
void rlc_am_add_hole (
                                  const protocol_ctxt_t* const  ctxt_pP,
                                  rlc_am_entity_t *const rlcP,
                                  const rlc_sn_t snP,
                                  const sdu_size_t so_startP,
                                  sdu_size_t so_stopP);
/** @} */
#endif
