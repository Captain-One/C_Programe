#ifndef __RLC_UM_RECEIVER_PROTO_EXTERN_H__
#define __RLC_UM_RECEIVER_PROTO_EXTERN_H__
#include "rlc_um_entity.h"

/*! \fn void rlc_um_display_rx_window(const protocol_ctxt_t* const ctxtP,rlc_um_entity_t * const rlc_pP)
* \brief    Display the content of the RX buffer, the output stream is targeted to TTY terminals because of escape sequences.
* \param[in]  ctxtP       Running context.
* \param[in]  rlc_pP      RLC UM protocol instance pointer.
*/
void rlc_um_display_rx_window(const protocol_ctxt_t* const ctxtP, rlc_um_entity_t * const rlc_pP);

/*! \fn void rlc_um_receive (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t * const rlc_pP, struct mac_data_ind data_indP)
* \brief    Handle the MAC data indication, retreive the transport blocks and send them one by one to the DAR process.
* \param[in]  ctxtP       Running context.
* \param[in]  rlc_pP      RLC UM protocol instance pointer.
* \param[in]  data_indP   Data indication structure containing transport block received from MAC layer.
*/
void rlc_um_receive (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t * const rlc_pP, struct mac_data_ind data_indP);
/** @} */
#endif
