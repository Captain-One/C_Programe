/*
 * GprsTimer3.c
 *
 *  Created on: 2018Äê4ÔÂ29ÈÕ
 *      Author: pu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "../UTIL/TLVEncoder.h"
#include "../UTIL/TLVDecoder.h"
#include "GprsTimer3.h"

int decode_gprs_timer3(GprsTimer3 *gprstimer3, uint8_t iei, uint8_t *buffer, uint32_t len)
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

  gprstimer3->unit = (*(buffer + decoded) >> 5) & 0x7;
  gprstimer3->timervalue = *(buffer + decoded) & 0x1f;
  decoded++;
/*#if defined (NAS_DEBUG)
  dump_gprs_timer_xml(gprstimer3, iei);
#endif*/
  return decoded;
}




