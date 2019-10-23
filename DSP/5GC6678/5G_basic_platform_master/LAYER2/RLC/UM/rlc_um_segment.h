#ifndef __RLC_UM_SEGMENT_PROTO_EXTERN_H__
#define __RLC_UM_SEGMENT_PROTO_EXTERN_H__
//-----------------------------------------------------------------------------
#include "rlc_um_entity.h"
#include "rlc_um_structs.h"
#include "rlc_um_constants.h"
#include "list.h"
//-----------------------------------------------------------------------------
/*! \fn void rlc_um_segment_10 (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP)
* \brief    Segmentation procedure with 10 bits sequence number, segment the first SDU in buffer and create a PDU of the size (nb_bytes_to_transmit) requested by MAC if possible and put it in the list "pdus_to_mac_layer".
* \param[in]  ctxtP       Running context.
* \param[in]  rlcP        RLC UM protocol instance pointer.
*/
void rlc_um_segment_10 (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP);


/*! \fn void rlc_um_segment_5 (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP)
* \brief    Segmentation procedure with 5 bits sequence number, segment the first SDU in buffer and create a PDU of the size (nb_bytes_to_transmit) requested by MAC if possible and put it in the list "pdus_to_mac_layer".
* \param[in]  ctxtP       Running context.
* \param[in]  rlcP        RLC UM protocol instance pointer.
*/
void rlc_um_segment_5 (const protocol_ctxt_t* const ctxtP, rlc_um_entity_t *rlcP);
/** @} */
#endif
