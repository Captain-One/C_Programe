/*
 * GprsTimer2.h
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: pu
 */

#ifndef IES_GPRSTIMER2_H_
#define IES_GPRSTIMER2_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "OctetString.h"

#define GPRS_TIMER2_MINIMUM_LENGTH 3
#define GPRS_TIMER2_MAXIMUM_LENGTH 3

typedef struct GprsTimer2_tag {
  uint8_t  gprstimer2value;
} GprsTimer2;

//int encode_gprs_timer(GprsTimer *gprstimer, uint8_t iei, uint8_t *buffer, uint32_t len);

//void dump_gprs_timer_xml(GprsTimer *gprstimer, uint8_t iei);

int decode_gprs_timer2(GprsTimer2 *gprstimer2, uint8_t iei, uint8_t *buffer, uint32_t len);

//long gprs_timer_value(GprsTimer *gprstimer);

#endif /* IES_GPRSTIMER2_H_ */
