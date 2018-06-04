/*
 * NetworkResourceIdentifierContainer.c
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: pu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "../UTIL/TLVEncoder.h"
#include "../UTIL/TLVDecoder.h"
#include "NetworkResourceIdentifierContainer.h"

int decode_network_resource_identifier_container(NetworkResourceIdentifierContainer *networkresourceidentifiercontainer, \
		                                         uint8_t iei, uint8_t *buffer, uint32_t len)
{
	  int decoded = 0;
      int ielen = 0;
	  if (iei > 0) {
	    CHECK_IEI_DECODER(iei, *buffer);
	    decoded++;
	  }
	  ielen = *(buffer + decoded);
	  decoded++;
	  CHECK_LENGTH_DECODER(len - decoded, ielen);

	  networkresourceidentifiercontainer->nricontainervalue = (*(buffer + decoded)) << 2;
	  decoded++;
	  networkresourceidentifiercontainer->nricontainervalue |= (*(buffer +decoded) & 0xC0) >> 6;
	  networkresourceidentifiercontainer->spare = *(buffer +decoded) & 0x3f;
	  decoded++;
	/*#if defined (NAS_DEBUG)
	  dump_nas_security_algorithms_xml(nassecurityalgorithms, iei);
	#endif*/
	  return decoded;
}







