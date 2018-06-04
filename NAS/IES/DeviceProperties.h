/*
 * DeviceProperties.h
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: pu
 */

#ifndef IES_DEVICEPROPERTIES_H_
#define IES_DEVICEPROPERTIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "OctetString.h"

#define DEVICE_PROPERTIES_MINIMUM_LENGTH 1
#define DEVICE_PROPERTIES_MAXIMUM_LENGTH 1

typedef struct DeviceProperties_tag {
#define MS_IS_NOT_CONFIGURED_FOR_NAS_SIGNALLING_LOW_PRIORITY 0
#define MS_IS_CONFIGURED_FOR_NAS_SIGNALLING_LOW_PRIORITY    1
  uint8_t  lowpriority:1;
  uint8_t  spare:3;
} DeviceProperties;

//int encode_detach_type(DetachType *detachtype, uint8_t iei, uint8_t *buffer, uint32_t len);

//void dump_detach_type_xml(DetachType *detachtype, uint8_t iei);

//uint8_t encode_u8_detach_type(DetachType *detachtype);

int decode_device_properties(DeviceProperties *deviceproperties, uint8_t iei, uint8_t *buffer, uint32_t len);

//int decode_u8_detach_type(DetachType *detachtype, uint8_t iei, uint8_t value, uint32_t len);


#endif /* IES_DEVICEPROPERTIES_H_ */
