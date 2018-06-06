
#include "rrc_sencode4L2.h"

int CYDD_EXPORT RRC_sencode(RRC_Sdecode_Result_4_L2 *input, void *output, size_t *size)
{
   static asn_TYPE_descriptor_t  *pdu = 0;
   void *structure;
   void *ebuf = 0;
   asn_enc_rval_t rv;
   size_t *esize = size;
   
   switch(input->uMsgType)
   {
     case eBCCH_BCH: 
     {
       pdu = &asn_DEF_BCCH_BCH_Message;      
       structure = (void *)(&(input->ulInformationTransfer.BCCH_BCH_msg));
       *esize = uper_encode_to_new_buffer(pdu, 0, (void *)structure,(void **)&ebuf);           
        if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     case eBCCH_DL_SCH:
     {
       pdu = &asn_DEF_BCCH_DL_SCH_Message;
       structure = &(input->ulInformationTransfer.BCCH_DL_SCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     case eDL_CCCH:
     {
       pdu = &asn_DEF_DL_CCCH_Message;
       structure = &(input->ulInformationTransfer.DL_CCCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
       ebuf = NULL;
     }break;
     case eUL_CCCH:
     {
       pdu = &asn_DEF_UL_CCCH_Message;
       structure = &(input->ulInformationTransfer.UL_CCCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     case eDL_DCCH:
     {
       
       pdu = &asn_DEF_DL_DCCH_Message;
       structure = &(input->ulInformationTransfer.DL_DCCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     case eUL_DCCH:
     {
       pdu = &asn_DEF_UL_DCCH_Message;
       structure = & (input->ulInformationTransfer.UL_DCCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     case eMCCH:
     {
       pdu = &asn_DEF_MCCH_Message;
       structure = &(input->ulInformationTransfer.MCCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     case ePCCH:
     {
       pdu = &asn_DEF_PCCH_Message;
       structure = &(input->ulInformationTransfer.PCCH_msg);
       *esize = uper_encode_to_new_buffer(pdu, 0, structure,(void **)&ebuf);
       if(*esize < 0)
       {
         return -1;
       }
       memmove(output,ebuf,*esize);
       free(ebuf);
     }break;
     default : return -2 ; break;
   }
   return 0;
}

