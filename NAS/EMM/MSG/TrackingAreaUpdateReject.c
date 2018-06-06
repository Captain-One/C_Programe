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
#include "TrackingAreaUpdateReject.h"

int decode_tracking_area_update_reject(tracking_area_update_reject_msg *tracking_area_update_reject, uint8_t *buffer, uint32_t len)
{
  uint32_t decoded = 0;
  int decoded_result = 0;

  // Check if we got a NULL pointer and if buffer length is >= minimum length expected for the message.
  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, TRACKING_AREA_UPDATE_REJECT_MINIMUM_LENGTH, len);

  /* Decoding mandatory fields */
  if ((decoded_result = decode_emm_cause(&tracking_area_update_reject->emmcause, 0, buffer + decoded, len - decoded)) < 0)
    return decoded_result;
  else
    decoded += decoded_result;
  while(len - decoded > 0) {
	 uint8_t ieiDecoded = *(buffer + decoded);

     /* Type | value iei are below 0x80 so just return the first 4 bits */
     if (ieiDecoded >= 0x80)
	   ieiDecoded = ieiDecoded & 0xf0;

     switch(ieiDecoded) {
     case TRACKING_AREA_UPDATE_REJECT_T3346_VALUE_IEI:
    	 if((decoded_result = decode_gprs_timer2(&tracking_area_update_reject->t3346value,
    			                                 TRACKING_AREA_UPDATE_REJECT_T3346_VALUE_IEI,
				                                 buffer + decoded, len-decoded)) <= 0)
    	 {
    		 return decoded_result;
    	 }
    	 decoded += decoded_result;
    	 tracking_area_update_reject->presencemask |= TRACKING_AREA_UPDATE_REJECT_T3346_VALUE_PRESENT;
    	 break;
     }
  }

  return decoded;
}

int encode_tracking_area_update_reject(tracking_area_update_reject_msg *tracking_area_update_reject, uint8_t *buffer, uint32_t len)
{
  int encoded = 0;
  int encode_result = 0;

  /* Checking IEI and pointer */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, TRACKING_AREA_UPDATE_REJECT_MINIMUM_LENGTH, len);

  if ((encode_result =
         encode_emm_cause(&tracking_area_update_reject->emmcause, 0, buffer +
                          encoded, len - encoded)) < 0)        //Return in case of error
    return encode_result;
  else
    encoded += encode_result;

  return encoded;
}

