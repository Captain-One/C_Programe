/*
 * GprsTimer2.c
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: pu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "../UTIL/TLVEncoder.h"
#include "../UTIL/TLVDecoder.h"
#include "GprsTimer2.h"

int decode_gprs_timer2(GprsTimer2 *gprstimer2, uint8_t iei, uint8_t *buffer, uint32_t len)
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

  gprstimer2->gprstimer2value = *(buffer + decoded);
  decoded++;
/*#if defined (NAS_DEBUG)
  dump_gprs_timer_xml(gprstimer2, iei);
#endif*/
  return decoded;
}






