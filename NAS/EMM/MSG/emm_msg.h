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
/*****************************************************************************
Source    emm_msg.h

Version   0.1

Date    2012/09/27

Product   NAS stack

Subsystem EPS Mobility Management

Author    Frederic Maurel

Description Defines EPS Mobility Management messages and functions used
    to encode and decode

*****************************************************************************/
#ifndef __EMM_MSG_H__
#define __EMM_MSG_H__

#include "emm_msgDef.h"

#include "AttachRequest.h"
#include "AttachAccept.h"
#include "AttachComplete.h"
#include "AttachReject.h"
#include "DetachRequest.h"
#include "DetachAccept.h"
#include "TrackingAreaUpdateRequest.h"
#include "TrackingAreaUpdateAccept.h"
#include "TrackingAreaUpdateComplete.h"
#include "TrackingAreaUpdateReject.h"
#include "ExtendedServiceRequest.h"
#include "ServiceRequest.h"
#include "ServiceReject.h"
#include "GutiReallocationCommand.h"
#include "GutiReallocationComplete.h"
#include "AuthenticationRequest.h"
#include "AuthenticationResponse.h"
#include "AuthenticationReject.h"
#include "AuthenticationFailure.h"
#include "IdentityRequest.h"
#include "IdentityResponse.h"
#include "NASSecurityModeCommand.h"
#include "NASSecurityModeComplete.h"
#include "SecurityModeReject.h"
#include "EmmStatus.h"
#include "EmmInformation.h"
#include "DownlinkNasTransport.h"
#include "UplinkNasTransport.h"
#include "CsServiceNotification.h"

#include <stdint.h>

/****************************************************************************/
/*********************  G L O B A L    C O N S T A N T S  *******************/
/****************************************************************************/

/****************************************************************************/
/************************  G L O B A L    T Y P E S  ************************/
/****************************************************************************/

/*
 * Structure of EMM plain NAS message
 * ----------------------------------
 */
typedef union {
  emm_msg_header_t header;
  attach_request_msg attach_request;
  attach_accept_msg attach_accept;
  attach_complete_msg attach_complete;
  attach_reject_msg attach_reject;
  detach_request_msg detach_request;
  detach_accept_msg detach_accept;
  tracking_area_update_request_msg tracking_area_update_request;
  tracking_area_update_accept_msg tracking_area_update_accept;
  tracking_area_update_complete_msg tracking_area_update_complete;
  tracking_area_update_reject_msg tracking_area_update_reject;
  extended_service_request_msg extended_service_request;
  service_request_msg service_request;
  service_reject_msg service_reject;
  guti_reallocation_command_msg guti_reallocation_command;
  guti_reallocation_complete_msg guti_reallocation_complete;
  authentication_request_msg authentication_request;
  authentication_response_msg authentication_response;
  authentication_reject_msg authentication_reject;
  authentication_failure_msg authentication_failure;
  identity_request_msg identity_request;
  identity_response_msg identity_response;
  security_mode_command_msg security_mode_command;
  security_mode_complete_msg security_mode_complete;
  security_mode_reject_msg security_mode_reject;
  emm_status_msg emm_status;
  emm_information_msg emm_information;
  downlink_nas_transport_msg downlink_nas_transport;
  uplink_nas_transport_msg uplink_nas_transport;
  cs_service_notification_msg cs_service_notification;
} EMM_msg;


/****************************************************************************/
/********************  G L O B A L    V A R I A B L E S  ********************/
/****************************************************************************/

/****************************************************************************/
/******************  E X P O R T E D    F U N C T I O N S  ******************/
/****************************************************************************/

int emm_msg_decode(EMM_msg *msg, uint8_t *buffer, uint32_t len);

int emm_msg_encode(EMM_msg *msg, uint8_t *buffer, uint32_t len);

#endif /* __EMM_MSG_H__ */
