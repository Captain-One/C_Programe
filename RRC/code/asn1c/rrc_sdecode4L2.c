/*
 * 
 * 2018.03.26
 * puxingqiao
 * 
 * 
 * 
 * 
 */
#ifdef	HAVE_CONFIG_H
#include <config.h>
#endif

#include "rrc_sdecode4L2.h"


int CYDD_EXPORT RRC_sdecode(ProcH_t* proch_infoP, void *data, size_t size, RRC_Sdecode_Result_4_L2 *output)
{
	int stat = -1;
    asn_dec_rval_t rv; //asn1c解码函数返回值变量    
	static asn_TYPE_descriptor_t  *pdu = 0;
    ProcH_t *ch_info = proch_infoP;
    void * Message = 0;
    
	switch (ch_info->sptype.spktype_s.LCH)//Logical_CHT
	{
	case LCH_BCCH:
	{
		switch (ch_info->sptype.spktype_s.TrCH)//Transport_CHT
		{
		case TCH_BCH:
		{   
			pdu = &asn_DEF_BCCH_BCH_Message;
			Message = &(output->ulInformationTransfer.BCCH_BCH_msg);
			rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
		    if(rv.code == RC_FAIL)
		    {		    
      	      return -1;
		    }		    
			output->uMsgType = eBCCH_BCH;
			stat = 0;
		}
		break;
		case TCH_DL_SCH:
		{
			pdu = &asn_DEF_BCCH_DL_SCH_Message;
			Message = &(output->ulInformationTransfer.BCCH_DL_SCH_msg);
			rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
		    if(rv.code == RC_FAIL)
		    {
      	      return -1;
		    }		    
			output->uMsgType = eBCCH_DL_SCH;
			stat = 0;
		}
		break;
		default:
			//ACE_ERROR((LM_ERROR, "RRC_sdecode Unknown Transport Channel %d Under Logical Channel %d\n",
			//	context->Transport_CHT, context->Logical_CHT));
			stat = -2;
			break;
		}
	}
	break;
//	FIXME 2017.2.10 增加NAS解码后输出代码
	case LCH_CCCH:
	{
		switch (ch_info->carrier_info.carrier.DIR)//CH_DIRE
		{
		case E_UTRAN_TO_UE:
		{
			pdu = &asn_DEF_DL_CCCH_Message;
			Message = &(output->ulInformationTransfer.DL_CCCH_msg);
			rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
		    if(rv.code == RC_FAIL)
		    {
      	      return -1;
		    }		    
			output->uMsgType = eDL_CCCH;
			stat = 0;
		}
		break;
		case UE_TO_E_UTRAN:
		{
			pdu = &asn_DEF_UL_CCCH_Message;
			Message = &(output->ulInformationTransfer.UL_CCCH_msg);
			rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
		    if(rv.code == RC_FAIL)
		    {
      	      return -1;
		    }
			output->uMsgType = eUL_CCCH;
			stat = 0;
		}
		break;
		default:
			//ACE_ERROR((LM_ERROR, "RRC_sdecode Unknown Direction Under Logical Channel CCCH\n"));
			stat = -2;
			break;
		}
	}
	break;
	case LCH_DCCH:
	{
		switch (ch_info->carrier_info.carrier.DIR)//CH_DIRE
		{
		case E_UTRAN_TO_UE:
		{
			pdu = &asn_DEF_DL_DCCH_Message;
			Message = &(output->ulInformationTransfer.DL_DCCH_msg);
			rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
			if(rv.code == RC_FAIL)
		    {
      	      return -1;
		    }	
			output->uMsgType = eDL_DCCH;
			stat = 0;
		}
		break;
		case UE_TO_E_UTRAN:
		{
			pdu = &asn_DEF_UL_DCCH_Message;
			Message = &(output->ulInformationTransfer.UL_DCCH_msg);
			rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
			if(rv.code == RC_FAIL)
		    {
      	      return -1;
		    }	
			output->uMsgType = eUL_DCCH;
			stat = 0;
		}
		break;
		default:
			stat = -2;
			break;
		}
	}
	break;
	case LCH_MCCH:
	{
		pdu = &asn_DEF_MCCH_Message;
		Message = &(output->ulInformationTransfer.MCCH_msg);
		rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
		if(rv.code == RC_FAIL)
	    {
  	      return -1;
	    }	
		output->uMsgType = eMCCH;
		stat = 0;
	}
	break;
	case LCH_PCCH:
	{
		pdu = &asn_DEF_PCCH_Message;
		Message = &(output->ulInformationTransfer.PCCH_msg);
		rv = uper_decode_complete(0,pdu,(void **)&Message,data,(size_t)size);
		if(rv.code == RC_FAIL)
	    {
  	      return -1;
	    }	
		output->uMsgType = ePCCH;
		stat = 0;
	}
	break;
	default:
		stat = -3;
		break;
	}

	return stat;
}

