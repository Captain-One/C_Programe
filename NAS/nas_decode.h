/*
 * nas_decode.h
 *
 *  Created on: 2018Äê4ÔÂ26ÈÕ
 *      Author: pu
 */

#ifndef NAS_DECODE_H_
#define NAS_DECODE_H_

#include "nas_message.h"

typedef struct nas_decode_result{
	uint8_t message_type;
	nas_message_t msg;
}nas_decode_result_t;

#endif /* NAS_DECODE_H_ */
