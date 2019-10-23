#ifndef __RLC_AM_TIMER_POLL_RETRANSMIT_H__
#    define __RLC_AM_TIMER_POLL_RETRANSMIT_H__

/*! \fn void rlc_am_check_timer_poll_retransmit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Check if timer Poll-retransmit has timed-out, if so it is stopped and has the status "timed-out".
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.

*/
void rlc_am_check_timer_poll_retransmit(
    const protocol_ctxt_t* const ctxt_pP,
    rlc_am_entity_t* const       rlc_pP);

/*! \fn int  rlc_am_is_timer_poll_retransmit_timed_out(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Boolean function, check if timer Poll-retransmit has timed-out.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \return     1 if timer Poll-retransmit has timed-out, else 0.
*/
int  rlc_am_is_timer_poll_retransmit_timed_out(
    const protocol_ctxt_t* const ctxt_pP,
    rlc_am_entity_t* const       rlc_pP);

/*! \fn void rlc_am_stop_and_reset_timer_poll_retransmit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Stop and reset the timer Poll-retransmit.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.

*/
void rlc_am_stop_and_reset_timer_poll_retransmit(
    const protocol_ctxt_t* const ctxt_pP,
    rlc_am_entity_t* const       rlc_pP);

/*! \fn void rlc_am_start_timer_poll_retransmit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Re-arm (based on RLC AM config parameter) and start timer Poll-retransmit.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  frame             Frame index
*/
void rlc_am_start_timer_poll_retransmit(
    const protocol_ctxt_t* const ctxt_pP,
    rlc_am_entity_t* const       rlc_pP);

/*! \fn void rlc_am_init_timer_poll_retransmit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP, const uint32_t time_outP)
* \brief      Initialize the timer Poll-retransmit with RLC AM time-out config parameter.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  time_outP         Time-out in frame units.
*/
void rlc_am_init_timer_poll_retransmit(
    const protocol_ctxt_t* const ctxt_pP,
    rlc_am_entity_t* const       rlc_pP,
    const uint32_t               time_outP);
/** @} */
#endif
