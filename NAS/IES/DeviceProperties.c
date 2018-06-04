/*
 * DeviceProperties.c
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: pu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "../UTIL/TLVEncoder.h"
#include "../UTIL/TLVDecoder.h"
#include "DeviceProperties.h"

int decode_device_properties(DeviceProperties *deviceproperties, uint8_t iei, uint8_t *buffer, uint32_t len)
{
	 int decoded = 0;
	  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, DEVICE_PROPERTIES_MINIMUM_LENGTH, len);

	  if (iei > 0) {
	    CHECK_IEI_DECODER((*buffer & 0xf0), iei);
	  }

	  deviceproperties->lowpriority = *buffer & 0x1;
	  deviceproperties->spare = (*buffer & 0xE) >> 1;
	  decoded++;
	/*#if defined (NAS_DEBUG)
	  dump_eps_attach_result_xml(epsattachresult, iei);
	#endif*/
	  return decoded;

}
