/*
 * GprsTimer3.h
 *
 *  Created on: 2018Äê4ÔÂ29ÈÕ
 *      Author: pu
 */

#ifndef IES_GPRSTIMER3_H_
#define IES_GPRSTIMER3_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "OctetString.h"

#define GPRS_TIMER3_MINIMUM_LENGTH 3
#define GPRS_TIMER3_MAXIMUM_LENGTH 3

typedef struct GprsTimer3_tag {
#define GPRS_TIMER_UNIT_600S  0b000 /* 10 minutes  */
#define GPRS_TIMER_UNIT_1H 0b001 /* 1 hour */
#define GPRS_TIMER_UNIT_10H  0b010 /* 10 hour  */
#define GPRS_TIMER_UNIT_0S  0b111 /* deactivated  */
  uint8_t  unit:3;
  uint8_t  timervalue:5;
} GprsTimer3;

//int encode_gprs_timer(GprsTimer *gprstimer, uint8_t iei, uint8_t *buffer, uint32_t len);

//void dump_gprs_timer_xml(GprsTimer *gprstimer, uint8_t iei);

int decode_gprs_timer3(GprsTimer3 *gprstimer3, uint8_t iei, uint8_t *buffer, uint32_t len);

//long gprs_timer_value(GprsTimer *gprstimer);

#endif /* IES_GPRSTIMER3_H_ */
