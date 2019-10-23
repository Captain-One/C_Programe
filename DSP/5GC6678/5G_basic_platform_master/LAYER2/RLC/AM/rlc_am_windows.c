#define RLC_AM_MODULE 1
#define RLC_AM_WINDOWS_C 1
//-----------------------------------------------------------------------------
#include <assert.h>
//-----------------------------------------------------------------------------
#include "platform_types.h"
//-----------------------------------------------------------------------------
#include "rlc_am.h"

//-----------------------------------------------------------------------------
signed int rlc_am_in_tx_window(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const uint32_t snP)
{
	uint32_t shifted_sn;
	uint32_t upper_bound;

  if (snP >= rlc_pP->tx_sn_modulo) {
    return 0;
  }

  shifted_sn  = ((uint32_t)(snP - rlc_pP->TX_Next_Ack)) % rlc_pP->rx_sn_modulo;
  upper_bound = ((uint32_t)(rlc_pP->TX_Next + rlc_pP->tx_am_window_size - rlc_pP->TX_Next)) % rlc_pP->rx_sn_modulo;

  if ((shifted_sn >= 0) && (shifted_sn < upper_bound))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
#if 1
//-----------------------------------------------------------------------------
signed int
rlc_am_in_rx_window(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const uint32_t snP)
{
  uint32_t shifted_sn;
  uint32_t upper_bound;

  if (snP >= rlc_pP->rx_sn_modulo)
  {
    return 0;
  }

  shifted_sn  = (snP - rlc_pP->RX_Next) % rlc_pP->rx_sn_modulo;
  upper_bound = (rlc_pP->RX_Next + rlc_pP->rx_am_window_size - rlc_pP->RX_Next) % rlc_pP->rx_sn_modulo;

  if ((shifted_sn >= 0) && (shifted_sn < upper_bound))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
#else
//-----------------------------------------------------------------------------
signed int
rlc_am_in_rx_window(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const rlc_sn_t snP)
{
  rlc_usn_t shifted_sn;
  rlc_usn_t upper_bound;

  if (snP >= RLC_AM_SN_MODULO) {
    return 0;
  }

  shifted_sn  = ((rlc_usn_t)(snP - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;
  upper_bound = ((rlc_usn_t)(rlc_pP->vr_mr - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;

  if ((shifted_sn >= 0) && (shifted_sn < upper_bound)) {
    return 1;
  } else {
    return 0;
  }
}
#endif
//-----------------------------------------------------------------------------
// returns  0 if numA < numB
// returns  1 if numA > numB
// returns  2 if numA == numB
signed int
rlc_am_modular_comparison(
  const protocol_ctxt_t* const ctxt_pP,
  rlc_am_entity_t * const rlc_pP,
  boolean_t transmit,
  int32_t numA,
  int32_t numB)
{
  int32_t modulus = transmit ? rlc_pP->TX_Next_Ack : rlc_pP->RX_Next;
  int32_t modulo = transmit ? rlc_pP->tx_sn_modulo : rlc_pP->rx_sn_modulo;
#if TRACE_RLC_UM_RX
  rlc_sn_t     lower_bound  = lower_boundP;
  rlc_sn_t     higher_bound = higher_boundP;
  rlc_sn_t     sn           = snP;
#endif
  int modA, modB;

  modA = (numA - modulus) % modulo;
  modB = (numB - modulus) % modulo;

  if ( modA > modB)
  {
    return 1;
  }
  else if(modA == modB)
  {
	  return 2;
  }
  else
  {
	  return 0;
  }


  return 0;
}
//-----------------------------------------------------------------------------
signed int
rlc_am_sn_gte_vr_h(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const rlc_sn_t snP)
{
  rlc_usn_t shifted_sn;
  rlc_usn_t upper_bound;

  if (snP >= RLC_AM_SN_MODULO) {
    return 0;
  }

  shifted_sn  = ((rlc_usn_t)(snP - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;
  upper_bound = ((rlc_usn_t)(rlc_pP->RX_Next_Highest - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;

  if (shifted_sn >= upper_bound) {
    return 1;
  } else {
    return 0;
  }
}
//-----------------------------------------------------------------------------
signed int rlc_am_sn_gte_vr_x(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const rlc_sn_t snP)
{
  rlc_usn_t shifted_sn;
  rlc_usn_t upper_bound;

  if (snP >= RLC_AM_SN_MODULO) {
    return 0;
  }

  shifted_sn  = ((rlc_usn_t)(snP - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;
  upper_bound = ((rlc_usn_t)(rlc_pP->RX_Next_Highest - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;

  if (shifted_sn >= upper_bound) {
    return 1;
  } else {
    return 0;
  }
}
//-----------------------------------------------------------------------------
signed int
rlc_am_sn_gt_vr_ms(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const rlc_sn_t snP)
{
  rlc_usn_t shifted_sn;
  rlc_usn_t upper_bound;

  if (snP >= RLC_AM_SN_MODULO) {
    return 0;
  }

  shifted_sn  = ((rlc_usn_t)(snP - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;
  upper_bound = ((rlc_usn_t)(rlc_pP->RX_Next_Status_Trigger - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;

  if (shifted_sn > upper_bound) {
    return 1;
  } else {
    return 0;
  }
}
//-----------------------------------------------------------------------------
signed int
rlc_am_tx_sn1_gt_sn2(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const rlc_sn_t sn1P,
  const rlc_sn_t sn2P)
{
  rlc_usn_t shifted_sn;
  rlc_usn_t upper_bound;

  if ((sn1P >= RLC_AM_SN_MODULO) || (sn2P >= RLC_AM_SN_MODULO)) {
    return 0;
  }

  shifted_sn  = ((rlc_usn_t)(sn1P - rlc_pP->vt_a)) % RLC_AM_SN_MODULO;
  upper_bound = ((rlc_usn_t)(sn2P - rlc_pP->vt_a)) % RLC_AM_SN_MODULO;

  if (shifted_sn > upper_bound) {
    return 1;
  } else {
    return 0;
  }
}
//-----------------------------------------------------------------------------
signed int
rlc_am_rx_sn1_gt_sn2(
  const protocol_ctxt_t* const  ctxt_pP,
  const rlc_am_entity_t* const rlc_pP,
  const rlc_sn_t sn1P,
  const rlc_sn_t sn2P)
{
  rlc_usn_t shifted_sn;
  rlc_usn_t upper_bound;

  if ((sn1P >= RLC_AM_SN_MODULO) || (sn2P >= RLC_AM_SN_MODULO)) {
    return 0;
  }

  shifted_sn  = ((rlc_usn_t)(sn1P - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;
  upper_bound = ((rlc_usn_t)(sn2P - rlc_pP->RX_Next)) % RLC_AM_SN_MODULO;

  if (shifted_sn > upper_bound) {
    return 1;
  } else {
    return 0;
  }
}
