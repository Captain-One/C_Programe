#ifndef __RLC_AM_TIMER_STATUS_PROHIBIT_H__
#    define __RLC_AM_TIMER_STATUS_PROHIBIT_H__


/*! \fn void rlc_am_check_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Check if timer status-prohibit has timed-out, if so it is stopped and has the status "timed-out".
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
*/
void rlc_am_check_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP);

/*! \fn void rlc_am_stop_and_reset_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Stop and reset the timer status-prohibit.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
*/
void rlc_am_stop_and_reset_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP);

/*! \fn void rlc_am_start_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP)
* \brief      Re-arm (based on RLC AM config parameter) and start timer status-prohibit.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
*/
void rlc_am_start_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP);

/*! \fn void rlc_am_init_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP, const uint32_t time_outP)
* \brief      Initialize the timer status-prohibit with RLC AM time-out config parameter.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  time_outP         Time-out in frameP units.
*/
void rlc_am_init_timer_status_prohibit(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlc_pP, const uint32_t time_outP);
/** @} */
#endif
