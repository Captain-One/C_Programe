/*
 * Copyright (c) 2015, EURECOM (www.eurecom.fr)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "../../UTIL/TLVEncoder.h"
#include "../../UTIL/TLVDecoder.h"
#include "TrackingAreaUpdateAccept.h"

int decode_tracking_area_update_accept(tracking_area_update_accept_msg *tracking_area_update_accept, uint8_t *buffer, uint32_t len)
{
  uint32_t decoded = 0;
  int decoded_result = 0;

  // Check if we got a NULL pointer and if buffer length is >= minimum length expected for the message.
  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, TRACKING_AREA_UPDATE_ACCEPT_MINIMUM_LENGTH, len);

  /* Decoding mandatory fields */
  if ((decoded_result = decode_u8_eps_update_result(&tracking_area_update_accept->epsupdateresult, 0, *(buffer + decoded) >> 4, len - decoded)) < 0)
    return decoded_result;

  decoded++;

  /* Decoding optional fields */
  while(len - decoded > 0) {
    uint8_t ieiDecoded = *(buffer + decoded);

    /* Type | value iei are below 0x80 so just return the first 4 bits */
    if (ieiDecoded >= 0x80)
      ieiDecoded = ieiDecoded & 0xf0;

    switch(ieiDecoded) {
    case TRACKING_AREA_UPDATE_ACCEPT_T3412_VALUE_IEI:
      if ((decoded_result =
             decode_gprs_timer(&tracking_area_update_accept->t3412value,
                               TRACKING_AREA_UPDATE_ACCEPT_T3412_VALUE_IEI, buffer +
                               decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_T3412_VALUE_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_GUTI_IEI:
      if ((decoded_result =
             decode_eps_mobile_identity(&tracking_area_update_accept->guti,
                                        TRACKING_AREA_UPDATE_ACCEPT_GUTI_IEI, buffer + decoded, len
                                        - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_GUTI_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_TAI_LIST_IEI:
      if ((decoded_result =
             decode_tracking_area_identity_list(&tracking_area_update_accept->tailist,
                 TRACKING_AREA_UPDATE_ACCEPT_TAI_LIST_IEI, buffer + decoded,
                 len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_TAI_LIST_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_EPS_BEARER_CONTEXT_STATUS_IEI:
      if ((decoded_result =
             decode_eps_bearer_context_status(&tracking_area_update_accept->epsbearercontextstatus,
                                              TRACKING_AREA_UPDATE_ACCEPT_EPS_BEARER_CONTEXT_STATUS_IEI,
                                              buffer + decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_EPS_BEARER_CONTEXT_STATUS_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_LOCATION_AREA_IDENTIFICATION_IEI:
      if ((decoded_result =
             decode_location_area_identification(&tracking_area_update_accept->locationareaidentification,
                 TRACKING_AREA_UPDATE_ACCEPT_LOCATION_AREA_IDENTIFICATION_IEI,
                 buffer + decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_LOCATION_AREA_IDENTIFICATION_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_MS_IDENTITY_IEI:
      if ((decoded_result =
             decode_mobile_identity(&tracking_area_update_accept->msidentity,
                                    TRACKING_AREA_UPDATE_ACCEPT_MS_IDENTITY_IEI, buffer +
                                    decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_MS_IDENTITY_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_EMM_CAUSE_IEI:
      if ((decoded_result =
             decode_emm_cause(&tracking_area_update_accept->emmcause,
                              TRACKING_AREA_UPDATE_ACCEPT_EMM_CAUSE_IEI, buffer +
                              decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_EMM_CAUSE_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_T3402_VALUE_IEI:
      if ((decoded_result =
             decode_gprs_timer(&tracking_area_update_accept->t3402value,
                               TRACKING_AREA_UPDATE_ACCEPT_T3402_VALUE_IEI, buffer +
                               decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_T3402_VALUE_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_T3423_VALUE_IEI:
      if ((decoded_result =
             decode_gprs_timer(&tracking_area_update_accept->t3423value,
                               TRACKING_AREA_UPDATE_ACCEPT_T3423_VALUE_IEI, buffer +
                               decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_T3423_VALUE_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_EQUIVALENT_PLMNS_IEI:
      if ((decoded_result =
             decode_plmn_list(&tracking_area_update_accept->equivalentplmns,
                              TRACKING_AREA_UPDATE_ACCEPT_EQUIVALENT_PLMNS_IEI, buffer +
                              decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_EQUIVALENT_PLMNS_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_EMERGENCY_NUMBER_LIST_IEI:
      if ((decoded_result =
             decode_emergency_number_list(&tracking_area_update_accept->emergencynumberlist,
                                          TRACKING_AREA_UPDATE_ACCEPT_EMERGENCY_NUMBER_LIST_IEI,
                                          buffer + decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_EMERGENCY_NUMBER_LIST_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_IEI:
      if ((decoded_result =
             decode_eps_network_feature_support(&tracking_area_update_accept->epsnetworkfeaturesupport,
                 TRACKING_AREA_UPDATE_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_IEI,
                 buffer + decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_ADDITIONAL_UPDATE_RESULT_IEI:
      if ((decoded_result =
             decode_additional_update_result(&tracking_area_update_accept->additionalupdateresult,
                                             TRACKING_AREA_UPDATE_ACCEPT_ADDITIONAL_UPDATE_RESULT_IEI,
                                             buffer + decoded, len - decoded)) <= 0)
        return decoded_result;

      decoded += decoded_result;
      /* Set corresponding mask to 1 in presencemask */
      tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_ADDITIONAL_UPDATE_RESULT_PRESENT;
      break;

    case TRACKING_AREA_UPDATE_ACCEPT_T3412_EXTENDED_VALUE_IEI:
    	if((decoded_result = decode_gprs_timer3(&tracking_area_update_accept->t3412extendedvalue,
    			                                TRACKING_AREA_UPDATE_ACCEPT_T3412_EXTENDED_VALUE_IEI,
				                                buffer + decoded, len - decoded))<= 0)
    	{
    		return decoded_result;
    	}
    	decoded += decoded_result;
    	tracking_area_update_accept->presencemask |= TRACKING_AREA_UPDATE_ACCEPT_T3412_EXTENDED_VALUE_PRESENT;
      break;

    default:
      errorCodeDecoder = TLV_DECODE_UNEXPECTED_IEI;
      return TLV_DECODE_UNEXPECTED_IEI;
    }
  }

  return decoded;
}

int encode_tracking_area_update_accept(tracking_area_update_accept_msg *tracking_area_update_accept, uint8_t *buffer, uint32_t len)
{
  int encoded = 0;
  int encode_result = 0;

  /* Checking IEI and pointer */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, TRACKING_AREA_UPDATE_ACCEPT_MINIMUM_LENGTH, len);

  *(buffer + encoded) = ((encode_u8_eps_update_result(&tracking_area_update_accept->epsupdateresult) & 0x0f) << 4) | 0x00;
  encoded++;

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_T3412_VALUE_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_T3412_VALUE_PRESENT) {
    if ((encode_result =
           encode_gprs_timer(&tracking_area_update_accept->t3412value,
                             TRACKING_AREA_UPDATE_ACCEPT_T3412_VALUE_IEI, buffer + encoded, len
                             - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_GUTI_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_GUTI_PRESENT) {
    if ((encode_result =
           encode_eps_mobile_identity(&tracking_area_update_accept->guti,
                                      TRACKING_AREA_UPDATE_ACCEPT_GUTI_IEI, buffer + encoded, len -
                                      encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_TAI_LIST_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_TAI_LIST_PRESENT) {
    if ((encode_result =
           encode_tracking_area_identity_list(&tracking_area_update_accept->tailist,
               TRACKING_AREA_UPDATE_ACCEPT_TAI_LIST_IEI, buffer + encoded, len -
               encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_EPS_BEARER_CONTEXT_STATUS_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_EPS_BEARER_CONTEXT_STATUS_PRESENT) {
    if ((encode_result =
           encode_eps_bearer_context_status(&tracking_area_update_accept->epsbearercontextstatus,
                                            TRACKING_AREA_UPDATE_ACCEPT_EPS_BEARER_CONTEXT_STATUS_IEI, buffer
                                            + encoded, len - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_LOCATION_AREA_IDENTIFICATION_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_LOCATION_AREA_IDENTIFICATION_PRESENT) {
    if ((encode_result =
           encode_location_area_identification(&tracking_area_update_accept->locationareaidentification,
               TRACKING_AREA_UPDATE_ACCEPT_LOCATION_AREA_IDENTIFICATION_IEI,
               buffer + encoded, len - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_MS_IDENTITY_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_MS_IDENTITY_PRESENT) {
    if ((encode_result =
           encode_mobile_identity(&tracking_area_update_accept->msidentity,
                                  TRACKING_AREA_UPDATE_ACCEPT_MS_IDENTITY_IEI, buffer + encoded, len
                                  - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_EMM_CAUSE_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_EMM_CAUSE_PRESENT) {
    if ((encode_result =
           encode_emm_cause(&tracking_area_update_accept->emmcause,
                            TRACKING_AREA_UPDATE_ACCEPT_EMM_CAUSE_IEI, buffer + encoded, len -
                            encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_T3402_VALUE_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_T3402_VALUE_PRESENT) {
    if ((encode_result =
           encode_gprs_timer(&tracking_area_update_accept->t3402value,
                             TRACKING_AREA_UPDATE_ACCEPT_T3402_VALUE_IEI, buffer + encoded, len
                             - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_T3423_VALUE_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_T3423_VALUE_PRESENT) {
    if ((encode_result =
           encode_gprs_timer(&tracking_area_update_accept->t3423value,
                             TRACKING_AREA_UPDATE_ACCEPT_T3423_VALUE_IEI, buffer + encoded, len
                             - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_EQUIVALENT_PLMNS_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_EQUIVALENT_PLMNS_PRESENT) {
    if ((encode_result =
           encode_plmn_list(&tracking_area_update_accept->equivalentplmns,
                            TRACKING_AREA_UPDATE_ACCEPT_EQUIVALENT_PLMNS_IEI, buffer +
                            encoded, len - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_EMERGENCY_NUMBER_LIST_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_EMERGENCY_NUMBER_LIST_PRESENT) {
    if ((encode_result =
           encode_emergency_number_list(&tracking_area_update_accept->emergencynumberlist,
                                        TRACKING_AREA_UPDATE_ACCEPT_EMERGENCY_NUMBER_LIST_IEI, buffer +
                                        encoded, len - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_PRESENT) {
    if ((encode_result =
           encode_eps_network_feature_support(&tracking_area_update_accept->epsnetworkfeaturesupport,
               TRACKING_AREA_UPDATE_ACCEPT_EPS_NETWORK_FEATURE_SUPPORT_IEI,
               buffer + encoded, len - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  if ((tracking_area_update_accept->presencemask & TRACKING_AREA_UPDATE_ACCEPT_ADDITIONAL_UPDATE_RESULT_PRESENT)
      == TRACKING_AREA_UPDATE_ACCEPT_ADDITIONAL_UPDATE_RESULT_PRESENT) {
    if ((encode_result =
           encode_additional_update_result(&tracking_area_update_accept->additionalupdateresult,
                                           TRACKING_AREA_UPDATE_ACCEPT_ADDITIONAL_UPDATE_RESULT_IEI, buffer +
                                           encoded, len - encoded)) < 0)
      // Return in case of error
      return encode_result;
    else
      encoded += encode_result;
  }

  return encoded;
}

