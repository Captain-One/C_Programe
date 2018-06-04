/*
 * ConnectivityType.h
 *
 *  Created on: 2018Äê5ÔÂ4ÈÕ
 *      Author: pu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "OctetString.h"

#ifndef IES_CONNECTIVITYTYPE_H_
#define IES_CONNECTIVITYTYPE_H_

#define CONNECTIVITY_TYPE_MINIMUM_LENGTH 1
#define CONNECTIVITY_TYPE_MAXIMUM_LENGTH 1

typedef uint8_t ConnectivityType;

int decode_connectivity_type(ConnectivityType *connectivitytype, uint8_t iei, uint8_t *buffer, uint32_t len);

#endif /* IES_CONNECTIVITYTYPE_H_ */
