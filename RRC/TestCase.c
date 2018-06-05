/*
 * TestCase.c
 *
 *  Created on: 2018年4月18日
 *      Author: pu
 */

//#include "testcase.h"
#include "code/rrc.h"
#include <stdint.h>

#ifdef  RRC_API_TEST_CASE_XML_PRINT
#include "code/asn1c/asn_application.h"
#include "code/asn1c/asn_internal.h"	/* for ASN__DEFAULT_STACK_MAX */

#include "code/asn1c/BCCH-BCH-Message.h"
#include "code/asn1c/BCCH-BCH-MessageType.h"

#include "code/asn1c/BCCH-DL-SCH-Message.h"
#include "code/asn1c/BCCH-DL-SCH-MessageType.h"

#include "code/asn1c/DL-CCCH-Message.h"
#include "code/asn1c/DL-CCCH-MessageType.h"


#include "code/asn1c/UL-CCCH-Message.h"
#include "code/asn1c/UL-CCCH-MessageType.h"


#include "code/asn1c/DL-DCCH-Message.h"
#include "code/asn1c/DL-DCCH-MessageType.h"


#include "code/asn1c/UL-DCCH-Message.h"
#include "code/asn1c/UL-DCCH-MessageType.h"


#include "code/asn1c/MCCH-Message.h"
#include "code/asn1c/MCCH-MessageType.h"


#include "code/asn1c/PCCH-Message.h"
#include "code/asn1c/PCCH-MessageType.h"

	
//xml打印函数，可以将解码详细信息打印出来
int XerPrint(RRC_Sdecode_Result_4_L2 *input)
{
  int rv = 0;
  RRC_Sdecode_Result_4_L2 *temp = input;
  asn_TYPE_descriptor_t *pdu;
  switch (input->uMsgType)
  {
   case eBCCH_BCH:
	     pdu = &asn_DEF_BCCH_BCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.BCCH_BCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
	     break;
  case eBCCH_DL_SCH:
	     pdu = &asn_DEF_BCCH_DL_SCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.BCCH_DL_SCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
	     break;
  case eDL_CCCH:
	     pdu = &asn_DEF_DL_CCCH_Message;
		  if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.DL_CCCH_msg))
		  {
			printf("xer print fail !!!\n");
			rv = -1;
		  }
         break;
  case eUL_CCCH:
         pdu = &asn_DEF_UL_CCCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.UL_CCCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
         break;
  case eDL_DCCH:
         pdu = &asn_DEF_DL_DCCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.DL_DCCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
         break;
  case eUL_DCCH:
         pdu = &asn_DEF_UL_DCCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.UL_DCCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
         break;
  case eMCCH:
         pdu = &asn_DEF_MCCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.MCCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
         break;
  case ePCCH:
         pdu = &asn_DEF_PCCH_Message;
	     if(xer_fprint(stdout, pdu, &temp->ulInformationTransfer.PCCH_msg))
		 {
		   printf("xer print fail !!!\n");
		   rv = -1;
		 }
         break;
  }  
  return rv;
}
#endif


//#define RRC_API_TEST_CASE

int main()
{
	uint8_t dbuf11[203] = {0x20,0x16,0x15,0xa8,0x00,0x10,0x00,0xfa,0x50,
						0x00,0x80,0x14,0x90,0x4b,0xc7,0x84,0x0a,0x08,
						0x25,0xe3,0xc2,0x00,0x00,0x20,0x0b,0x32,0x12,
						0x20,0x08,0x09,0x3e,0x10,0x11,0xe4,0xec,0x58,
						0xda,0x32,0xc0,0x40,0xe8,0x40,0x49,0x20,0xc8,
						0x0c,0x9e,0x02,0x19,0x30,0x80,0x0d,0x6a,0x46,
						0x78,0x21,0x21,0x1f,0xff,0xff,0xff,0xe0,0x00,
						0x00,0x00,0x03,0x20,0xa6,0x6c,0xed,0xcc,0xae,
						0x80,0xcd,0xad,0xcc,0x66,0x06,0x06,0x20,0xcd,
						0xac,0x6c,0x66,0x86,0xc6,0x00,0x8c,0xee,0x0e,
						0x4e,0x60,0xa0,0x35,0xc0,0x00,0x0c,0x0b,0xa0,
						0x2a,0x06,0x02,0x03,0x92,0x43,0xee,0x72,0xdf,
						0xdf,0xce,0xe9,0x7f,0xff,0xe0,0x13,0xc0,0x13,
						0xc0,0x0b,0xc0,0x9f,0xdf,0xd3,0xd3,0xcb,0x06,
						0x44,0xe3,0xf0,0x10,0x04,0x22,0x00,0x60,0x00,
						0x02,0x10,0x20,0xd8,0x15,0x01,0x6c,0x90,0x60,
						0xce,0x4e,0x4e,0x4e,0x40,0x01,0xa0,0x98,0x15,
						0x01,0x6c,0x80,0x00,0xa0,0x20,0x4a,0x01,0x7e,
						0xcc,0x9e,0x02,0x10,0x00,0x40,0x18,0x01,0x96,
						0xcb,0x0c,0x80,0x20,0x3e,0x0d,0x4e,0x04,0x7e,
						0xa8,0x1c,0xc9,0xc0,0x0f,0xa8,0x1b,0xc3,0x45,
						0xd5,0x03,0x86,0x02,0x52,0xe4,0x21,0xf6,0xa0,
						0x23,0x66,0x00,0x02,0x7a}; //DL_DCCH,解码原始数据buffer
		uint8_t dbufxx[] =	{0x20,0x00,0xcc,0x0e,0x82,0xe4,0x10,0x92,0x0c,
							 0x20,0x00,0x00,0x00,0x41,0x22,0x0b,0xe0,0xe1,
							 0x80,0x80,0x32,0x00,0x54,0x04,0x67,0xa0,0x63,
							 0xa2,0x4e,0x47,0x01,0x00,0x42,0x20,0x02,0x00,
							 0x00,0x21,0x02,0x0c,0x00,0x00,0x00,0x01,0x06,
							 0x0c,0x00,0x00,0x00,0x00,0x00,0x1a,0x00,0x00,
							 0x06,0x00,0x00,0x14,0x00,0x00,0x0a,0x00,0x00,
							 0x20,0x00,0xb8,0x14,0x00,0x62,0x07,0xcb,0xc0,
							 0x7d,0x20,0x22,0x06,0xae,0xb1,0x4c,0x40,0x14,
							 0xc0,0x28,0x09,0xc5,0x23,0x02,0x1e,0x34,0x3c,
							 0xa0,0x80,0x10,0x00,0x00,0x00,0x08,0x04,0xc0,
							 0x08,0x00,0x04,0x3e,0x04,0xba,0x02,0x05,0x82};
	uint8_t dbuf21[] = {0x68,0x13, 0x98 ,0x0b ,0x5d ,0xd2, 0x21, 0x83 ,0xc0, 0xba ,0x08 ,0x7e ,0x13, 0x3f, 0xfa ,0x90,
                   0x8f, 0x86 ,0x55, 0x15 ,0xb1 ,0x42 ,0xb6, 0x60 ,0x00 ,0x1a, 0x98 ,0x04, 0x0f, 0x80 ,0xa0 ,0x90,
                   0x1e, 0x02 ,0x40 ,0x44 ,0x80 ,0x00 ,0x00};
	uint8_t dbuf12[] = {0x68, 0x13, 0x98 ,0x0b ,0x5d, 0xd2, 0x21 ,0x83 ,
0xc0, 0xba ,0x08 ,0x7e ,0x13 ,0x3f ,0xfa ,0x90, 
0x8f, 0x86 ,0x55 ,0x15 ,0xb1 ,0x42 ,0xb6 ,0x60, 
0x00, 0x1a, 0x98 ,0x04 ,0x0f ,0x80 ,0xa0 ,0x90 ,
0x1e ,0x0d, 0x40 ,0x00 ,0x04 ,0x00};  
    uint8_t dbuf[]= {0x08,0x20,0x49,0x3e,0xc5,0x53,0xcb,0x68,0x08,0x16,0x16,0xc8}; 

	int dsize= 12;//108;//39;//203; //解码原始数据的字节数
	RRC_Sdecode_Result_4_L2 *dresult = 0; //解码结果
	ProcH_t ch_info; //解码信道信息及上下行方向，BBData中获取

	//测试用DL_DCCH消息，手动指定信道信息
	ch_info.sptype.spktype_s.LCH = LCH_DCCH;
	ch_info.carrier_info.carrier.DIR = E_UTRAN_TO_UE;//UE_TO_E_UTRAN;

	uint8_t ebuf[1000]; //编码数据存放buffer
	size_t esize = 0; //编码数据的字节数
	RRC_Encode_Result_t *eresult = 0;  //编码结果

	int rv = -1; //编解码返回值

	int i = 0;

	dresult = malloc(sizeof(RRC_Sdecode_Result_4_L2));
	memset(dresult,0,sizeof(RRC_Sdecode_Result_4_L2));

	eresult = malloc(sizeof(RRC_Encode_Result_t));
	memset(eresult,0,sizeof(RRC_Encode_Result_t));
	memset(ebuf,0,1000);
	eresult->data = ebuf;  //
	
    printf("Decode Message is DL_DCCH\nStart Decode...\n");
    
	rv = rrc_decode(&ch_info, dbuf, dsize, dresult);  //解码
	if(rv < 0) //解码失败
	{
	   printf("RRC Decode fail!!!\n");
       return -1;
	}
	
    printf("Decode OK!\n");

#ifdef  RRC_API_TEST_CASE_XML_PRINT	
	rv = XerPrint(dresult); //以xml形式打印解码信息
	if(rv < 0) //编码码失败
	{
	   printf("XML print fail!\n");
	   return -1;
	}
#endif
	
    printf("Start Encode...\n");
    
	rv = RRC_encode(dresult, eresult);  //编码
	if(rv < 0) //编码码失败
	{
	   printf("RRC Encode fail!\n");
	   return -1;
	}
	
    printf("Encode OK!\n");
	printf("Encode size is %ld \n",eresult->size);
	printf("Encode data is : \n");

	//打印编码数据
	for(i = 0; i<eresult->size;i++)
	{
		printf("0x%02x ",*(eresult->data + i));
		if((i+1)%8 == 0)
		printf("\n");
	}
	printf("\n");

	return 0;
}
