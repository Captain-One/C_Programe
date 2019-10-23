#ifndef __RLC_UM_FSM_PROTO_EXTERN_H__
#define __RLC_UM_FSM_PROTO_EXTERN_H__
//-----------------------------------------------------------------------------
#include "platform_types.h"
#include "rlc_um_entity.h"
//-----------------------------------------------------------------------------
/*! \fn int rlc_um_fsm_notify_event (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP, uint8_t eventP)
* \brief    Send an event to the RLC UM finite state machine.
* \param[in]  ctxtP       Running context.
* \param[in]  rlcP        RLC UM protocol instance pointer.
* \param[in]  eventP      Event (#RLC_UM_RECEIVE_CRLC_CONFIG_REQ_ENTER_NULL_STATE_EVENT,
*                         #RLC_UM_RECEIVE_CRLC_CONFIG_REQ_ENTER_DATA_TRANSFER_READY_STATE_EVENT,
*                         #RLC_UM_RECEIVE_CRLC_SUSPEND_REQ_EVENT,
*                         #RLC_UM_TRANSMIT_CRLC_SUSPEND_CNF_EVENT,
*                         #RLC_UM_RECEIVE_CRLC_RESUME_REQ_EVENT).
* \return     1 if no error was encountered, 0 if the event was not processed.
* \Note       This FSM is not LTE 9.3.0 compliant, it has to be modified or removed.
*/
int rlc_um_fsm_notify_event (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP, uint8_t eventP);
/** @} */
#endif
