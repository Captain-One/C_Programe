#    ifndef __RLC_AM_WINDOWS_H__
#        define __RLC_AM_WINDOWS_H__
//-----------------------------------------------------------------------------

/*! \fn signed int rlc_am_in_tx_window(const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t snP)
* \brief      Boolean function, check if sequence number is VT(A) <= snP < VT(MS).
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  snP               Sequence number.
* \return 1 if snP in tx window, else 0.
*/
//signed int rlc_am_in_tx_window(
//                           const protocol_ctxt_t* const  ctxt_pP,
//                           const rlc_am_entity_t* const rlc_pP,
//                           const rlc_sn_t snP);

signed int rlc_am_in_tx_window(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const uint32_t snP);

/*! \fn signed int rlc_am_in_rx_window(const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t snP)
* \brief      Boolean function, check if sequence number is VR(R) <= snP < VR(MR).
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  snP               Sequence number.
* \return 1 if snP in rx window, else 0.
*/
//signed int rlc_am_in_rx_window(
//                           const protocol_ctxt_t* const  ctxt_pP,
//                           const rlc_am_entity_t* const rlc_pP,
//                           const rlc_sn_t snP);

signed int
rlc_am_in_rx_window(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const uint32_t snP);

/*! \fn signed int rlc_am_sn_gte_vr_h (const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t snP)
* \brief      Boolean function, check if sequence number is greater than or equal VR(R).
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  snP               Sequence number.
* \return 1 if sequence number is greater than or equal VR(R), else 0.
*/
signed int rlc_am_sn_gte_vr_h (
                           const protocol_ctxt_t* const  ctxt_pP,
                           const rlc_am_entity_t* const rlc_pP,
                           const rlc_sn_t snP);

/*! \fn signed int rlc_am_sn_gte_vr_x (const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t snP)
* \brief      Boolean function, check if sequence number is greater than or equal VR(X).
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  snP               Sequence number.
* \return 1 if sequence number is greater than or equal VR(X), else 0.
*/
signed int rlc_am_sn_gte_vr_x (
                           const protocol_ctxt_t* const  ctxt_pP,
                           const rlc_am_entity_t* const rlc_pP,
                           const rlc_sn_t snP);

/*! \fn signed int rlc_am_sn_gt_vr_ms (const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t snP)
* \brief      Boolean function, check if sequence number is greater than VR(MS).
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  snP               Sequence number.
* \return 1 if sequence number is greater than VR(MS), else 0.
*/
signed int rlc_am_sn_gt_vr_ms(
                           const protocol_ctxt_t* const  ctxt_pP,
                           const rlc_am_entity_t* const rlc_pP,
                           const rlc_sn_t snP);

/*! \fn signed int rlc_am_tx_sn1_gt_sn2 (const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t sn1P, const rlc_sn_t sn2P)
* \brief      Boolean function, in the context of the tx window, check if sn1P is greater than sn2P.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  sn1P              Sequence number.
* \param[in]  sn2P              Sequence number.
* \return 1 if sn1P is greater than sn2P, else 0.
*/
signed int rlc_am_tx_sn1_gt_sn2(
                           const protocol_ctxt_t* const  ctxt_pP,
                           const rlc_am_entity_t* const rlc_pP,
                           const rlc_sn_t sn1P,
                           const rlc_sn_t sn2P);

/*! \fn signed int rlc_am_rx_sn1_gt_sn2(const protocol_ctxt_t* const  ctxt_pP,const rlc_am_entity_t* const rlc_pP, const rlc_sn_t sn1P, const rlc_sn_t sn2P)
* \brief      Boolean function, in the context of the rx window, check if sn1P is greater than sn2P.
* \param[in]  ctxt_pP           Running context.
* \param[in]  rlc_pP            RLC AM protocol instance pointer.
* \param[in]  sn1P              Sequence number.
* \param[in]  sn2P              Sequence number.
* \return 1 if sn1P is greater than sn2P, else 0.
*/
signed int rlc_am_rx_sn1_gt_sn2(
                           const protocol_ctxt_t* const  ctxt_pP,
                           const rlc_am_entity_t* const rlc_pP,
                           const rlc_sn_t sn1P,
                           const rlc_sn_t sn2P);
/** @} */
#    endif
