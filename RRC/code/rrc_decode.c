/*
 * rrc_decode.c
 *
 *  Created on: 2016年12月9日
 *      Author: wanxs
 *  modify :2018年4月9日
        puxingqiao
 */


#include "rrc.h"

signed int rrc_decode(const void* proinfoP,
		const void* sdataP,
		const int32_t sdlen,
		void* const resultP)
{
	signed int err = 0;

	ProcH_t* proch_infoP = (ProcH_t*)proinfoP;
	
	void *data = sdataP;
	size_t dsize = sdlen;

#ifdef PCMode
	printf("Enter %s %s()!\n", __FILE__, __FUNCTION__);
#endif

	memset(resultP, 0, sizeof(RRC_Sdecode_Result_4_L2));
	
	err = RRC_sdecode(proch_infoP,data,dsize,(RRC_Sdecode_Result_4_L2 *)resultP);

#ifdef PCMode
	printf("RRC_sdecode = %d, uMsgType = %d\n", err, ((RRC_Sdecode_Result_4_L2 *)resultP)->uMsgType);
#endif

	return err;
}

