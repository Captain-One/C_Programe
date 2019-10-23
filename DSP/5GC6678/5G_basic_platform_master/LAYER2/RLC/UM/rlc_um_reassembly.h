#ifndef __RLC_UM_REASSEMBLY_PROTO_EXTERN_H__
#define __RLC_UM_REASSEMBLY_PROTO_EXTERN_H__
//-----------------------------------------------------------------------------
#include "rlc_um_entity.h"
//-----------------------------------------------------------------------------
/*! \fn void rlc_um_clear_rx_sdu (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP)
* \brief    Erase the SDU in construction.
* \param[in]  ctxtP       Running context.
* \param[in]  rlcP        RLC UM protocol instance pointer.
*/
void rlc_um_clear_rx_sdu (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP);

/*! \fn void rlc_um_reassembly (uint8_t * srcP, int32_t lengthP, rlc_um_entity_t *rlcP, frame_t frame)
* \brief    Reassembly lengthP bytes to the end of the SDU in construction.
* \param[in]  ctxtP       Running context.
* \param[in]  rlcP        RLC UM protocol instance pointer.
* \param[in]  srcP        Pointer on data to be reassemblied.
* \param[in]  lengthP     Length to reassembly.
*/
void rlc_um_reassembly (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP, uint8_t * srcP, int32_t lengthP);

/*! \fn void rlc_um_send_sdu (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP)
* \brief    Send SDU if any reassemblied to upper layer.
* \param[in]  ctxtP       Running context.
* \param[in]  rlcP        RLC UM protocol instance pointer.
*/
void rlc_um_send_sdu (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP);
/** @} */
#endif
