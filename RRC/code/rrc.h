/*
 * rrc.h
 *
 *  Created on: 2016年12月9日
 *      Author: wanxs
 */

#ifndef PROTOCOL_RRC_RRC_H_
#define PROTOCOL_RRC_RRC_H_

//#define ENCODE_MAX_SIZE 1000

#ifndef RRC_API_TEST_CASE
#include "../COMMON/platform_types.h"
#endif

#include "asn1c/rrc_sencode4L2.h"
#include "asn1c/rrc_sdecode4L2.h"
//#include "rrc_msg.h"

/*
signed int create_rrc_ctxt(struct RRC_RLC_CONTEXT * const rrcctxtP,
		OSCTXT* const pctxtP,
		OSOCTET* const bufaddr,
		const size_t bufsiz,
		const OSRTFLAGS flags,
		const OSOCTET level,
		const int starbitoff,
		const int endbitoff,
		const enum CHANNEL_DIRE dir,
		const enum LOGICAL_CH_TYPE lch,
		const enum TRANSPORT_CH_TYPE trch,
		const OSBOOL aligned);
*/
signed int rrc_decode(const void* proinfoP,
		const void* sdataP,
		const int32_t sdlen,
		void* const resultP);

//int get_msg_value(RRC_Sdecode_Result_4_L2 *input);

int RRC_encode(RRC_Sdecode_Result_4_L2 *pinpdu, RRC_Encode_Result_t *result);



#endif /* PROTOCOL_RRC_RRC_H_ */
