/*
 * TestCase.c
 *
 *  Created on: 2018年4月18日
 *      Author: pu
 */

//#include "testcase.h"
#include "code/rrc.h"
#include <stdint.h>
#include <stdlib.h>

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

	
#define ARRY_SIZE(a)  (int)sizeof(a)/sizeof(a[0])

/* Dump the buffer out to the specified FILE */
static int write_out(const void *buffer, size_t size, void *key) {
	FILE *fp = (FILE *)key;
	return (fwrite(buffer, 1, size, fp) == size) ? 0 : -1;
}


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
void Dcch_Message_Struct_Init(DL_DCCH_MessageType_t *mst);

int main()
{
	/*
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
    uint8_t dbuf1121[]= {0x08,0x20,0x49,0x3e,0xc5,0x53,0xcb,0x68,0x08,0x16,0x16,0xc8}; 
	
	uint8_t dbufxxx[] = {0x00,0x82,0x5c,0x31,0x18,0x6f,0xe0,0xac,0x68,0x05,0x8b,0x96,0xe2,0xd0,0x00,0x04,
0x01,0x26,0x02,0x4f,0x6c,0xb5,0x50,0x22,0x03,0x00,0xb2,0xf0,0x00,0x30,0xd0,0x00,
0xc0,0xa0,0x00,0x03,0x27,0xb0,0xda,0x36,0xbd,0x27,0x80,0xa0,0x9d,0xd2,0xf4,0x90,
0x00,0x00,0x00,0x00}; //si (sib2 sib3)  

    uint8_t dbuf122[] = {0x20,0x02,0x81,0x90,0x12,0xcc,0x11,0x01,0xc0,0x82,0x3f,0x0c,0xa1,0x98,0x33,0x86,
0x8c,0x33,0x06,0x70,0xd0,0x1a,0x49,0x43,0x80,0x0c,0xc7,0x70,0xb1,0x5f,0x0b,0xaf,
0x40,0x20,0x84,0x40};//reconfig 2ca,
*/
    uint8_t dbuf[] = {0x22,0x08,0x3d,0x58,0x94,0xd4,0x28,0x26,
    		0xba,0x5f,0xfe,0xe2,0xc6,0xd2,0xff,0x36,
    		0x18,0x06,0xab,0x2d,0x03,0x21,0x99,0x01,
    		0x81,0x69,0x00,0x99,0xdb,0x2d,0x45,0x79,
    		0x38,0x04,0x04,0xa3,0x40};//dl dcch reconfig;
 
	int dsize= ARRY_SIZE(dbuf);//36;//52;//12;//108;//39;//203; //解码原始数据的字节数
	RRC_Sdecode_Result_4_L2 *dresult = 0; //解码结果
	ProcH_t ch_info; //解码信道信息及上下行方向，BBData中获取

	//测试用DL_DCCH消息，手动指定信道信息
	ch_info.sptype.spktype_s.LCH = LCH_DCCH;
	ch_info.sptype.spktype_s.TrCH = TCH_DL_SCH;
	ch_info.carrier_info.carrier.DIR = E_UTRAN_TO_UE;//UE_TO_E_UTRAN;

	uint8_t ebuf[1000]; //编码数据存放buffer
	size_t esize = 0; //编码数据的字节数
	RRC_Encode_Result_t *eresult = 0;  //编码结果
	int rv = -1; //编解码返回值
	int i = 0;
	asn_enc_rval_t zz;

	DL_DCCH_MessageType_t Dcch_message_struct;
	memset(&Dcch_message_struct,0,sizeof(DL_DCCH_MessageType_t));

	RRC_Encode_Result_t xxxEnRe;
	uint8_t *xxxebuf;
	xxxebuf = malloc(1024);
	memset(xxxebuf,0,1024);

	xxxEnRe.data = xxxebuf;
	xxxEnRe.size = 0;

	dresult = malloc(sizeof(RRC_Sdecode_Result_4_L2));
	memset(dresult,0,sizeof(RRC_Sdecode_Result_4_L2));

	eresult = malloc(sizeof(RRC_Encode_Result_t));
	memset(eresult,0,sizeof(RRC_Encode_Result_t));
	memset(ebuf,0,1000);
	eresult->data = ebuf;  //
	
	//Dcch_Message_Struct_Init(&dresult->ulInformationTransfer.DL_DCCH_msg);
    printf("Decode Message is DL_DCCH\nStart Decode...\n");
   // dresult->uMsgType = eDL_DCCH;

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

/*
    FILE *fder;
    fder = fopen("aaa.dat","wb+");
    if(fder == NULL)
    {
    	printf("open file error\n");
    	return -1;
    }
    static asn_TYPE_descriptor_t *pduType = &asn_DEF_DL_DCCH_Message;
    void *structure = &Dcch_message_struct;
  //  xer_fprint(stdout, pduType, structure);
   // zz = der_encode(pduType, structure, write_out, fder);
    zz = uper_encode(pduType, structure, write_out, fder);
	if(zz.encoded < 0) {
		printf("error %d\n",zz.encoded);
		exit(EX_UNAVAILABLE);
	}
	fclose(fder);
	printf("encode OK!\n");
*/
/*
    xxxEnRe.size = uper_encode_to_new_buffer(&asn_DEF_DL_DCCH_Message, 0, &Dcch_message_struct,(void **)&xxxebuf);
    printf("enxode xxx size : %d\n",xxxEnRe.size);
    if(xxxEnRe.size < 0)
    {
      printf("encode xxx error: %d\n",xxxEnRe.size);
	  return -1;
    }
    printf("enxode xxx ok\n");
    //printf("enxode xxx size : %d\n",xxxEnRe.size);
    for(i = 0; i<xxxEnRe.size;i++)
	{
		printf("0x%02x ",*(xxxEnRe.data + i));
		if((i+1)%8 == 0)
		printf("\n");
	}
	printf("\n");
*/
	return 0;
}

void Dcch_Message_Struct_Init(DL_DCCH_MessageType_t *mst)
{
	printf("init message\n");
	C_RNTI_t c_rnti;
	uint16_t rnti = 0x4bd7;
	c_rnti.size = 2;
	c_rnti.buf = (void *)&rnti;
	c_rnti.bits_unused = 0;
	long additi = 1;
	long pmax = 23;

	P_Max_t	*p_Max;
	p_Max = &pmax;
	AdditionalSpectrumEmission_t	*additionalSpectrumEmission;
	additionalSpectrumEmission = &additi;

	struct MobilityControlInfo	*mobilityControlInfo;
	struct CarrierFreqEUTRA	*carrierFreq; //16;
	struct CarrierBandwidthEUTRA	*carrierBandwidth; //16
	struct AntennaInfoCommon	*antennaInfoCommon;//8
	struct PDSCH_ConfigCommon	*pdsch_ConfigCommon;//8
	struct PHICH_Config	*phich_Config;//8
	struct PRACH_ConfigInfo	*prach_ConfigInfo;
	struct PUCCH_ConfigCommon	*pucch_ConfigCommon;
	struct RACH_ConfigCommon	*rach_ConfigCommon;
	struct RACH_ConfigCommon__preambleInfo__preamblesGroupAConfig *preamblesGroupAConfig;
	struct SoundingRS_UL_ConfigCommon	*soundingRS_UL_ConfigCommon;
	struct TDD_Config	*tdd_Config;
	struct UplinkPowerControlCommon	*uplinkPowerControlCommon;
	struct UplinkPowerControlCommon_v1020	*uplinkPowerControlCommon_v1020;
	struct RACH_ConfigDedicated	*rach_ConfigDedicated;

	mobilityControlInfo = malloc(sizeof(struct MobilityControlInfo));
	carrierFreq = malloc(sizeof(struct CarrierFreqEUTRA));
	carrierBandwidth = malloc(sizeof(struct CarrierBandwidthEUTRA));
	antennaInfoCommon = malloc(sizeof(struct AntennaInfoCommon));
	pdsch_ConfigCommon = malloc(sizeof(struct PDSCH_ConfigCommon));
	phich_Config = malloc(sizeof(struct PHICH_Config));
	prach_ConfigInfo = malloc(sizeof(struct PRACH_ConfigInfo));
	pucch_ConfigCommon = malloc(sizeof(struct PUCCH_ConfigCommon));
	rach_ConfigCommon = malloc(sizeof(struct RACH_ConfigCommon));
	preamblesGroupAConfig = malloc(sizeof(struct RACH_ConfigCommon__preambleInfo__preamblesGroupAConfig));
	soundingRS_UL_ConfigCommon = malloc(sizeof(struct SoundingRS_UL_ConfigCommon));
	tdd_Config = malloc(sizeof(struct TDD_Config));
	uplinkPowerControlCommon = malloc(sizeof(struct UplinkPowerControlCommon));
	uplinkPowerControlCommon_v1020 = malloc(sizeof(struct UplinkPowerControlCommon_v1020));
	rach_ConfigDedicated = malloc(sizeof(struct RACH_ConfigDedicated));

	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo = mobilityControlInfo;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierFreq = carrierFreq;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierBandwidth = carrierBandwidth;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.antennaInfoCommon = antennaInfoCommon;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pdsch_ConfigCommon = pdsch_ConfigCommon;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.phich_Config = phich_Config;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.prach_Config.prach_ConfigInfo = prach_ConfigInfo;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pucch_ConfigCommon = pucch_ConfigCommon;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon = rach_ConfigCommon;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->preambleInfo.preamblesGroupAConfig = preamblesGroupAConfig;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon = soundingRS_UL_ConfigCommon;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.tdd_Config = tdd_Config;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon = uplinkPowerControlCommon;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon_v1020 = uplinkPowerControlCommon_v1020;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->rach_ConfigDedicated = rach_ConfigDedicated;

	mst->present = DL_DCCH_MessageType_PR_c1;
	mst->choice.c1.present = DL_DCCH_MessageType__c1_PR_rrcConnectionReconfiguration;
	mst->choice.c1.choice.rrcConnectionReconfiguration.rrc_TransactionIdentifier = 1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.present = RRCConnectionReconfiguration__criticalExtensions_PR_c1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.present = RRCConnectionReconfiguration__criticalExtensions__c1_PR_rrcConnectionReconfiguration_r8;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.dedicatedInfoNASList = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.measConfig = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.nonCriticalExtension = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.radioResourceConfigDedicated = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.securityConfigHO = NULL;

	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->targetPhysCellId = 172;
	//mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierFreq = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierFreq->dl_CarrierFreq = 38100;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierFreq->ul_CarrierFreq = NULL;
	//mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierBandwidth = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierBandwidth->dl_Bandwidth = CarrierBandwidthEUTRA__dl_Bandwidth_n100;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->carrierBandwidth->ul_Bandwidth = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->additionalSpectrumEmission = additionalSpectrumEmission;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->t304 = MobilityControlInfo__t304_ms500;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->newUE_Identity = c_rnti;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.antennaInfoCommon->antennaPortsCount = AntennaInfoCommon__antennaPortsCount_an2;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.p_Max = p_Max;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pdsch_ConfigCommon->p_b = 1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pdsch_ConfigCommon->referenceSignalPower = 15;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.phich_Config->phich_Duration = PHICH_Config__phich_Duration_normal;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.phich_Config->phich_Resource = PHICH_Config__phich_Resource_half;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.prach_Config.rootSequenceIndex = 707;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.prach_Config.prach_ConfigInfo->highSpeedFlag = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.prach_Config.prach_ConfigInfo->prach_ConfigIndex = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.prach_Config.prach_ConfigInfo->prach_FreqOffset = 85;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.prach_Config.prach_ConfigInfo->zeroCorrelationZoneConfig = 6;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pucch_ConfigCommon->deltaPUCCH_Shift = PUCCH_ConfigCommon__deltaPUCCH_Shift_ds1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pucch_ConfigCommon->n1PUCCH_AN = 180;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pucch_ConfigCommon->nCS_AN = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pucch_ConfigCommon->nRB_CQI = 3;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.pusch_ConfigBasic.enable64QAM = 1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.pusch_ConfigBasic.hoppingMode = PUSCH_ConfigCommon__pusch_ConfigBasic__hoppingMode_interSubFrame;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.pusch_ConfigBasic.n_SB = 1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.pusch_ConfigBasic.pusch_HoppingOffset = 12;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.ul_ReferenceSignalsPUSCH.cyclicShift = 3;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.ul_ReferenceSignalsPUSCH.groupAssignmentPUSCH = 3;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.ul_ReferenceSignalsPUSCH.groupHoppingEnabled = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.pusch_ConfigCommon.ul_ReferenceSignalsPUSCH.sequenceHoppingEnabled = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->maxHARQ_Msg3Tx = 5;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->powerRampingParameters.powerRampingStep = RACH_ConfigCommon__powerRampingParameters__powerRampingStep_dB2;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->powerRampingParameters.preambleInitialReceivedTargetPower = RACH_ConfigCommon__powerRampingParameters__preambleInitialReceivedTargetPower_dBm_100;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->preambleInfo.numberOfRA_Preambles = RACH_ConfigCommon__preambleInfo__numberOfRA_Preambles_n52;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->messagePowerOffsetGroupB = RACH_ConfigCommon__preambleInfo__preamblesGroupAConfig__messagePowerOffsetGroupB_dB8;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->messageSizeGroupA = RACH_ConfigCommon__preambleInfo__preamblesGroupAConfig__messageSizeGroupA_b56;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->preambleInfo.preamblesGroupAConfig->sizeOfRA_PreamblesGroupA = RACH_ConfigCommon__preambleInfo__preamblesGroupAConfig__sizeOfRA_PreamblesGroupA_n48;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->ra_SupervisionInfo.mac_ContentionResolutionTimer = RACH_ConfigCommon__ra_SupervisionInfo__mac_ContentionResolutionTimer_sf64;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->ra_SupervisionInfo.preambleTransMax = RACH_ConfigCommon__ra_SupervisionInfo__preambleTransMax_n8;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.rach_ConfigCommon->ra_SupervisionInfo.ra_ResponseWindowSize = RACH_ConfigCommon__ra_SupervisionInfo__ra_ResponseWindowSize_sf10;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon->present = SoundingRS_UL_ConfigCommon_PR_setup;
	//mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon->choice.release = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon->choice.setup.ackNackSRS_SimultaneousTransmission = 1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon->choice.setup.srs_BandwidthConfig = SoundingRS_UL_ConfigCommon__setup__srs_BandwidthConfig_bw0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon->choice.setup.srs_MaxUpPts = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.soundingRS_UL_ConfigCommon->choice.setup.srs_SubframeConfig = SoundingRS_UL_ConfigCommon__setup__srs_SubframeConfig_sc0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.tdd_Config->specialSubframePatterns = TDD_Config__specialSubframePatterns_ssp7;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.tdd_Config->subframeAssignment = TDD_Config__subframeAssignment_sa2;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.ul_CyclicPrefixLength = UL_CyclicPrefixLength_len1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->alpha = UplinkPowerControlCommon__alpha_al08;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->deltaFList_PUCCH.deltaF_PUCCH_Format1 = DeltaFList_PUCCH__deltaF_PUCCH_Format1_deltaF0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->deltaFList_PUCCH.deltaF_PUCCH_Format1b = DeltaFList_PUCCH__deltaF_PUCCH_Format1b_deltaF3;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->deltaFList_PUCCH.deltaF_PUCCH_Format2 = DeltaFList_PUCCH__deltaF_PUCCH_Format2_deltaF1;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->deltaFList_PUCCH.deltaF_PUCCH_Format2a = DeltaFList_PUCCH__deltaF_PUCCH_Format2a_deltaF2;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->deltaFList_PUCCH.deltaF_PUCCH_Format2b = DeltaFList_PUCCH__deltaF_PUCCH_Format2b_deltaF2;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->deltaPreambleMsg3 = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->p0_NominalPUCCH = -105;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon->p0_NominalPUSCH = -75;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon_v1020->deltaF_PUCCH_Format1bCS_r10 = UplinkPowerControlCommon_v1020__deltaF_PUCCH_Format1bCS_r10_deltaF2;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->radioResourceConfigCommon.uplinkPowerControlCommon_v1020->deltaF_PUCCH_Format3_r10 = UplinkPowerControlCommon_v1020__deltaF_PUCCH_Format3_r10_deltaF0;
	//mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->rach_ConfigDedicated = NULL;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->rach_ConfigDedicated->ra_PRACH_MaskIndex = 0;
	mst->choice.c1.choice.rrcConnectionReconfiguration.criticalExtensions.choice.c1.choice.rrcConnectionReconfiguration_r8.mobilityControlInfo->rach_ConfigDedicated->ra_PreambleIndex = 52;
}






