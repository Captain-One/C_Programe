/*
 * Copyright (c) 2015, EURECOM (www.eurecom.fr)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "OctetString.h"

#ifndef EPS_NETWORK_FEATURE_SUPPORT_H_
#define EPS_NETWORK_FEATURE_SUPPORT_H_

#define EPS_NETWORK_FEATURE_SUPPORT_MINIMUM_LENGTH 3
#define EPS_NETWORK_FEATURE_SUPPORT_MAXIMUM_LENGTH 3

//typedef uint8_t EpsNetworkFeatureSupport;
typedef struct EpsNetworkFeatureSupport_tag{
#define IMS_VOPS_IN_S1_MODE_SUPPORT  0b1
#define IMS_VOPS_IN_S1_MODE_NOT_SUPPORT 0b0
	uint8_t imsvops:1;
#define EMERGENCY_BEARER_SERVICES_IN_S1_MODE_SUPPORTED 0b1
#define EMERGENCY_BEARER_SERVICES_IN_S1_MODE_NOT_SUPPORTED 0b0
	uint8_t emcbs:1;
#define LOCATION_SERVICES_VIA_EPC_SUPPORTED 0b1
#define LOCATION_SERVICES_VIA_EPC_SUPPORTED 0b0
	uint8_t epclcs:1;
#define NO_INFORMATION_SUPPORT_OF_LOCATION_SERVICES_VIA__CS_DOMAIN 0b00
#define LOCATION_SERVICES_VIA_CS_DOMAIN_SUPPORT 0b01
#define LOCATION_SERVICES_VIA_CS_DOMAIN_NOT_SUPPORT 0b10
#define RESERVED 0b11
	uint8_t cslcs:2;
#define NOT_SUPPORT_USE_OF_EXTENDED_SERVICE_REQUEST 0b0
#define SUPPORT_USE_OF_EXTENDED_SERVICE_REQUEST 0b1
	uint8_t esrps:1;
}EpsNetworkFeatureSupport;

int encode_eps_network_feature_support(EpsNetworkFeatureSupport *epsnetworkfeaturesupport, uint8_t iei, uint8_t *buffer, uint32_t len);

int decode_eps_network_feature_support(EpsNetworkFeatureSupport *epsnetworkfeaturesupport, uint8_t iei, uint8_t *buffer, uint32_t len);

void dump_eps_network_feature_support_xml(EpsNetworkFeatureSupport *epsnetworkfeaturesupport, uint8_t iei);

#endif /* EPS NETWORK FEATURE SUPPORT_H_ */

