#ifndef __RLC_AM_RX_LIST_H__
#define __RLC_AM_RX_LIST_H__

#include "mem_block.h"
//-----------------------------------------------------------------------------
#include "platform_types.h"
#include "platform_constants.h"
//#include "PHY/defs.h"

//-----------------------------------------------------------------------------
/*! \fn rlc_am_rx_pdu_status_t rlc_am_rx_list_check_duplicate_insert_pdu(const protocol_ctxt_t* const  ctxt_pP,rlc_am_entity_t* const rlc_pP,mem_block_t* const tb_pP)
* \brief      Insert a PDU in the RX buffer after removing byte duplicate (implemented with a list).
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
* \param[in]  tbP          A PDU embedded in a mem_block_t.
* \return     Zero if the PDU could be inserted in the RX buffer, a negative value if the PDU could not be inserted.
*/
rlc_am_rx_pdu_status_t rlc_am_rx_list_check_duplicate_insert_pdu(const protocol_ctxt_t* const  ctxt_pP,rlc_am_entity_t* const rlc_pP,mem_block_t* const tb_pP);

/*! \fn signed int rlc_am_rx_list_insert_pdu(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP , mem_block_t* const tbP)
* \brief      Insert a PDU in the RX buffer (implemented with a list).
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
* \param[in]  tbP          A PDU embedded in a mem_block_t.
* \return     Zero if the PDU could be inserted in the RX buffer, a negative value if the PDU could not be inserted.
*/
signed int rlc_am_rx_list_insert_pdu(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP,  mem_block_t* const tbP);

/*! \fn boolean_t rlc_am_rx_check_vr_reassemble(const protocol_ctxt_t* const ctxt_pP,const rlc_am_entity_t* const rlc_pP)
* \brief      Check if reassembly taking into account potential new vrR value
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
* \return     TRUE if reassembly must be done, FALSE else
*/
boolean_t rlc_am_rx_check_vr_reassemble(const protocol_ctxt_t* const ctxt_pP,const rlc_am_entity_t* const rlc_pP);

/*! \fn void rlc_am_rx_check_all_byte_segments(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP, mem_block_t* const tbP)
* \brief      Check if all sub-segments of a PDU are received, if yes then call rlc_am_rx_mark_all_segments_received() procedure.
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
* \param[in]  tbP          A PDU embedded in a mem_block_t.
*/
void rlc_am_rx_check_all_byte_segments(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP, mem_block_t* const tbP);

/*! \fn void rlc_am_rx_mark_all_segments_received (const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP, mem_block_t* const  first_segment_tbP)
* \brief      Mark all PDUs having the same sequence number as first_segment_tbP with the information that all segments have been received.
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
* \param[in]  first_segment_tbP   A PDU embedded in a mem_block_t, it is the first PDU in the RX buffer (list) that have its sequence number.
*/
void rlc_am_rx_mark_all_segments_received(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP, mem_block_t* const first_segment_tbP);

/*! \fn void rlc_am_rx_list_reassemble_rlc_sdus(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP)
* \brief      Reassembly all SDUS that it is possible to reassembly by parsing the RX buffer and looking for PDUs having the flag 'all segments received'.
* \param[in]  ctxt_pP        Running context.
* \param[in]  rlcP         RLC AM protocol instance pointer.
*/
void rlc_am_rx_list_reassemble_rlc_sdus(const protocol_ctxt_t* const ctxt_pP, rlc_am_entity_t* const rlcP, mem_block_t* const tb_pP);

/*! \fn mem_block_t* list2_insert_before_element (mem_block_t * element_to_insertP, mem_block_t * elementP, list2_t * listP)
* \brief      Insert a PDU embedded in a mem_block_t in a list at a position before a designated element of the list.
* \param[in]  element_to_insertP    Element to insert in the list listP, before elementP position.
* \param[in]  elementP              Element in the list.
* \param[in]  listP                 List where elements are linked.
*/
mem_block_t* list2_insert_before_element (mem_block_t * element_to_insertP, mem_block_t * elementP, list2_t * listP);

/*! \fn mem_block_t* list2_insert_after_element (mem_block_t * element_to_insertP, mem_block_t * elementP, list2_t * listP)
* \brief      Insert a PDU embedded in a mem_block_t in a list at a position after a designated element of the list.
* \param[in]  element_to_insertP    Element to insert in the list listP, after elementP position.
* \param[in]  elementP              Element in the list.
* \param[in]  listP                 List where elements are linked.
*/
mem_block_t* list2_insert_after_element (mem_block_t * element_to_insertP, mem_block_t * elementP, list2_t * listP);

/*! \fn void rlc_am_rx_list_display (const rlc_am_entity_t* const rlcP, char* messageP)
* \brief      Display the dump of the RX buffer.
* \param[in]  rlcP         RLC AM protocol instance pointer.
* \param[in]  messageP     Message to be displayed along with the display of the dump of the RX buffer.
*/
void rlc_am_rx_list_display (const rlc_am_entity_t* const rlcP, char* messageP);
/** @} */
#endif
