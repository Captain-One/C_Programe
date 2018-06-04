/*
 * NetworkResourceIdentifierContainer.h
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: pu
 */

#ifndef IES_NETWORKRESOURCEIDENTIFIERCONTAINER_H_
#define IES_NETWORKRESOURCEIDENTIFIERCONTAINER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "OctetString.h"

#define NETWORK_RESOURCE_IDENTIFIER_CONTAINER_MINIMUM_LENGTH 4
#define NETWORK_RESOURCE_IDENTIFIER_CONTAINER_MAXIMUM_LENGTH 4

typedef struct NetworkResourceIdentifierContainer_tag{
	uint16_t  nricontainervalue:10;
	uint16_t  spare:6;
}NetworkResourceIdentifierContainer;

int decode_network_resource_identifier_container(NetworkResourceIdentifierContainer *networkresourceidentifiercontainer, \
		                                         uint8_t iei, uint8_t *buffer, uint32_t len);

#endif /* IES_NETWORKRESOURCEIDENTIFIERCONTAINER_H_ */
