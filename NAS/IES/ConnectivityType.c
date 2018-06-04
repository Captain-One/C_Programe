/*
 * ConnectivityType.c
 *
 *  Created on: 2018Äê5ÔÂ4ÈÕ
 *      Author: pu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "../UTIL/TLVEncoder.h"
#include "../UTIL/TLVDecoder.h"
#include "ConnectivityType.h"


int decode_connectivity_type(ConnectivityType *connectivitytype, uint8_t iei, uint8_t *buffer, uint32_t len)
{
	int decoded = 0;
	  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, CONNECTIVITY_TYPE_MINIMUM_LENGTH, len);

	  if (iei > 0) {
	    CHECK_IEI_DECODER((*buffer & 0xf0), iei);
	  }

	  *connectivitytype = *buffer & 0xf;
	  decoded++;
	/*#if defined (NAS_DEBUG)
	  dump_csfb_response_xml(csfbresponse, iei);
	#endif*/
	  return decoded;
}
