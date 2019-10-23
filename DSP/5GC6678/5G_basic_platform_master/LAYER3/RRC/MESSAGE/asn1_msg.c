#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h> /* for atoi(3) */
#include <unistd.h> /* for getopt(3) */
#include <string.h> /* for strerror(3) */
//#include <sysexits.h> /* for EX_* exit codes */
#include <errno.h>  /* for errno */
#include <asn_application.h>
#include <asn_internal.h> /* for _ASN_DEFAULT_STACK_MAX */
#include <per_encoder.h>
#include "assertions.h"
#include "RRCSetupRequest.h"
#include "UL-CCCH-Message.h"
#include "UL-DCCH-Message.h"
#include "DL-CCCH-Message.h"
#include "DL-DCCH-Message.h"
#include "PCCH-Message.h"
//#include "UTILS/conversions.h"
#include "EstablishmentCause.h"
#include "RRCSetup.h"
#include "SRB-ToAddModList.h"
#include "DRB-ToAddModList.h"
#include "rrc_defs.h"
//#include "rrc_extern.h"
#include "RRCSetupComplete.h"
#include "RRCReconfigurationComplete.h"
#include "RRCReconfiguration.h"
#include "MIB.h"
#include "SystemInformation.h"
#include "SIB1.h"
#include "BCCH-DL-SCH-Message.h"
#include "MeasurementReport.h"
#include "MeasObjectToAddModList.h"
#include "ReportConfigToAddModList.h"
#include "MeasIdToAddModList.h"


#if defined(ENABLE_ITTI)
  #include "intertask_interface.h"
#endif

//#include "secu_defs.h"

#if !defined (msg)
  #define msg printf
#endif


typedef struct xer_sprint_string_s {
  char *string;
  size_t string_size;
  size_t string_index;
} xer_sprint_string_t;


uint16_t two_tier_hexagonal_cellIds[7] = {0,1,2,4,5,7,8};
uint16_t two_tier_hexagonal_adjacent_cellIds[7][6] = {{1,2,4,5,7,8},    // CellId 0
						      {11,18,2,0,8,15}, // CellId 1
						      {18,13,3,4,0,1},  // CellId 2
						      {2,3,14,6,5,0},   // CellId 4
						      {0,4,6,16,9,7},   // CellId 5
						      {8,0,5,9,17,12},  // CellId 7
						      {15,1,0,7,12,10}
};// CellId 8

/*
 * This is a helper function for xer_sprint, which directs all incoming data
 * into the provided string.
 */
static int xer__print2s (const void *buffer, size_t size, void *app_key) {
  xer_sprint_string_t *string_buffer = (xer_sprint_string_t *) app_key;
  size_t string_remaining = string_buffer->string_size - string_buffer->string_index;

  if (string_remaining > 0) {
    if (size > string_remaining) {
      size = string_remaining;
    }

    memcpy(&string_buffer->string[string_buffer->string_index], buffer, size);
    string_buffer->string_index += size;
  }

  return 0;
}

int xer_sprint (char *string, size_t string_size, asn_TYPE_descriptor_t *td, void *sptr) {
  asn_enc_rval_t er;
  xer_sprint_string_t string_buffer;
  string_buffer.string = string;
  string_buffer.string_size = string_size;
  string_buffer.string_index = 0;
  er = xer_encode(td, sptr, XER_F_BASIC, xer__print2s, &string_buffer);

  if (er.encoded < 0) {
    printf("xer_sprint encoding error (%zd)!", er.encoded);
    er.encoded = string_buffer.string_size;
  } else {
    if (er.encoded > string_buffer.string_size) {
      printf("xer_sprint string buffer too small, got %zd need %zd!", string_buffer.string_size, er.encoded);
      er.encoded = string_buffer.string_size;
    }
  }

  return er.encoded;
}

uint16_t get_adjacent_cell_id(uint8_t Mod_id,uint8_t index) {
  return(two_tier_hexagonal_adjacent_cellIds[Mod_id][index]);
}
/* This only works for the hexagonal topology...need a more general function for other topologies */

uint8_t get_adjacent_cell_mod_id(uint16_t phyCellId) {
  uint8_t i;

  for(i=0; i<7; i++) {
    if(two_tier_hexagonal_cellIds[i] == phyCellId) {
      return i;
    }
  }

  printf("\nCannot get adjacent cell mod id! Fatal error!\n");
  return 0xFF; //error!
}


uint8_t do_RRCSetupRequest(uint8_t Mod_id, uint8_t *buffer,uint8_t *rv)
{
	asn_enc_rval_t enc_rval;
	uint8_t buf[5],buf2=0;
	UL_CCCH_Message_t ul_ccch_msg;
	RRCSetupRequest_t *rrcConnectionRequest;
	memset((void *)&ul_ccch_msg, 0, sizeof(UL_CCCH_Message_t));
	ul_ccch_msg.message.present           = UL_CCCH_MessageType_PR_c1;
	ul_ccch_msg.message.choice.c1.present = UL_CCCH_MessageType__c1_PR_rrcSetupRequest;
	rrcConnectionRequest          = &ul_ccch_msg.message.choice.c1.choice.rrcSetupRequest;
//	rrcConnectionRequest->criticalExtensions.present = RRCConnectionRequest__criticalExtensions_PR_rrcConnectionRequest_r8;
//
//	if (1) {
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.present = InitialUE_Identity_PR_randomValue;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.size = 5;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.bits_unused = 0;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf = buf;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf[0] = rv[0];
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf[1] = rv[1];
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf[2] = rv[2];
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf[3] = rv[3];
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.randomValue.buf[4] = rv[4];
//	} else {
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.present = InitialUE_Identity_PR_s_TMSI;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.mmec.size = 1;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.mmec.bits_unused = 0;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.mmec.buf = buf;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.mmec.buf[0] = 0x12;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.size = 4;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.bits_unused = 0;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.buf = &buf[1];
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.buf[0] = 0x34;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.buf[1] = 0x56;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.buf[2] = 0x78;
//		rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.ue_Identity.choice.s_TMSI.m_TMSI.buf[3] = 0x9a;
//	}
//
//	rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.establishmentCause = EstablishmentCause_mo_Signalling; //EstablishmentCause_mo_Data;
//	rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.spare.buf = &buf2;
//	rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.spare.size = 1;
//	rrcConnectionRequest->criticalExtensions.choice.rrcConnectionRequest_r8.spare.bits_unused = 7;
//
//	if ( LOG_DEBUGFLAG(DEBUG_ASN1) ) {
//		xer_fprint(stdout, &asn_DEF_UL_CCCH_Message, (void *)&ul_ccch_msg);
//	}

	enc_rval = uper_encode_to_buffer(&asn_DEF_UL_CCCH_Message,
											NULL,
											(void *)&ul_ccch_msg,
											buffer,
											100);
	AssertFatal (enc_rval.encoded > 0, "ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);

	printf("[UE] RRCConnectionRequest Encoded %zd bits (%zd bytes)\n", enc_rval.encoded, (enc_rval.encoded+7)/8);

	return((enc_rval.encoded+7)/8);
}




uint8_t do_RRCConnectionSetupComplete(uint8_t Mod_id, uint8_t *buffer, const uint8_t Transaction_id, const int dedicatedInfoNASLength, const char *dedicatedInfoNAS)
{
	asn_enc_rval_t enc_rval;
	UL_DCCH_Message_t ul_dcch_msg;
	RRCSetupComplete_t *rrcConnectionSetupComplete;
	memset((void *)&ul_dcch_msg,0,sizeof(UL_DCCH_Message_t));
//	ul_dcch_msg.message.present           = UL_DCCH_MessageType_PR_c1;
//	ul_dcch_msg.message.choice.c1.present = UL_DCCH_MessageType__c1_PR_rrcConnectionSetupComplete;
//	rrcConnectionSetupComplete            = &ul_dcch_msg.message.choice.c1.choice.rrcConnectionSetupComplete;
//	rrcConnectionSetupComplete->rrc_TransactionIdentifier = Transaction_id;
//	rrcConnectionSetupComplete->criticalExtensions.present = RRCConnectionSetupComplete__criticalExtensions_PR_c1;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.present = RRCConnectionSetupComplete__criticalExtensions__c1_PR_rrcConnectionSetupComplete_r8;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.nonCriticalExtension = CALLOC(1,
//			sizeof(*rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.nonCriticalExtension));
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.selectedPLMN_Identity= 1;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME = NULL;//calloc(1,sizeof(*rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME));
//	/*
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->plmn_Identity=NULL;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmegi.buf = calloc(2,1);
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmegi.buf[0] = 0x0;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmegi.buf[1] = 0x1;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmegi.size=2;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmegi.bits_unused=0;
//	*/
//	memset(&rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.dedicatedInfoNAS,0,sizeof(OCTET_STRING_t));
//
//	OCTET_STRING_fromBuf(&rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.dedicatedInfoNAS,
//			dedicatedInfoNAS, dedicatedInfoNASLength);
//
//	/*
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmec.buf = calloc(1,1);
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmec.buf[0] = 0x98;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmec.size=1;
//	rrcConnectionSetupComplete->criticalExtensions.choice.c1.choice.rrcConnectionSetupComplete_r8.registeredMME->mmec.bits_unused=0;
//	*/
//	if ( LOG_DEBUGFLAG(DEBUG_ASN1) ) {
//		xer_fprint(stdout, &asn_DEF_UL_DCCH_Message, (void *)&ul_dcch_msg);
//	}
//
//	enc_rval = uper_encode_to_buffer(&asn_DEF_UL_DCCH_Message,
//											NULL,
//											(void *)&ul_dcch_msg,
//											buffer,
//											100);
//	AssertFatal (enc_rval.encoded > 0, "ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);
//
//	printf("RRCConnectionSetupComplete Encoded %zd bits (%zd bytes)\n",enc_rval.encoded,(enc_rval.encoded+7)/8);

	return((enc_rval.encoded+7)/8);
}

//------------------------------------------------------------------------------
uint8_t do_RRCConnectionReconfigurationComplete(const protocol_ctxt_t *const ctxt_pP,
														uint8_t *buffer,
														const uint8_t Transaction_id
)
//------------------------------------------------------------------------------
{
	asn_enc_rval_t enc_rval;
	UL_DCCH_Message_t ul_dcch_msg;
	RRCReconfigurationComplete_t *rrcConnectionReconfigurationComplete;
	memset((void *)&ul_dcch_msg,0,sizeof(UL_DCCH_Message_t));
	ul_dcch_msg.message.present                     = UL_DCCH_MessageType_PR_c1;
//	ul_dcch_msg.message.choice.c1.present           = UL_DCCH_MessageType__c1_PR_rrcConnectionReconfigurationComplete;
//	rrcConnectionReconfigurationComplete            = &ul_dcch_msg.message.choice.c1.choice.rrcConnectionReconfigurationComplete;
//	rrcConnectionReconfigurationComplete->rrc_TransactionIdentifier = Transaction_id;
//	rrcConnectionReconfigurationComplete->criticalExtensions.present =
//	RRCConnectionReconfigurationComplete__criticalExtensions_PR_rrcConnectionReconfigurationComplete_r8;
//	rrcConnectionReconfigurationComplete->criticalExtensions.choice.rrcConnectionReconfigurationComplete_r8.nonCriticalExtension=NULL;
//
//	if ( LOG_DEBUGFLAG(DEBUG_ASN1) ) {
//		xer_fprint(stdout, &asn_DEF_UL_DCCH_Message, (void *)&ul_dcch_msg);
//	}

	enc_rval = uper_encode_to_buffer(&asn_DEF_UL_DCCH_Message,
											NULL,
											(void *)&ul_dcch_msg,
											buffer,
											100);
	AssertFatal (enc_rval.encoded > 0, "ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);

	printf("RRCConnectionReconfigurationComplete Encoded %zd bits (%zd bytes)\n",enc_rval.encoded,(enc_rval.encoded+7)/8);

	return((enc_rval.encoded+7)/8);
}


uint8_t do_MeasurementReport(uint8_t Mod_id, uint8_t *buffer,int measid,int phy_id,long rsrp_s,long rsrq_s,long rsrp_t,long rsrq_t)
{
	asn_enc_rval_t enc_rval;
	UL_DCCH_Message_t ul_dcch_msg;
	MeasurementReport_t  *measurementReport;
	ul_dcch_msg.message.present                     = UL_DCCH_MessageType_PR_c1;
//	ul_dcch_msg.message.choice.c1.present           = UL_DCCH_MessageType__c1_PR_measurementReport;
//	measurementReport            = &ul_dcch_msg.message.choice.c1.choice.measurementReport;
//	measurementReport->criticalExtensions.present = MeasurementReport__criticalExtensions_PR_c1;
//	measurementReport->criticalExtensions.choice.c1.present = MeasurementReport__criticalExtensions__c1_PR_measurementReport_r8;
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.nonCriticalExtension=CALLOC(1,
//			sizeof(*measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.nonCriticalExtension));
//
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measId=measid;
//
//#if (RRC_VERSION < MAKE_VERSION(15, 0, 0))
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultPCell.rsrpResult = rsrp_s;
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultPCell.rsrqResult = rsrq_s;
//#else
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultServCell.rsrpResult = rsrp_s;
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultServCell.rsrqResult = rsrq_s;
//#endif
//
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultNeighCells = CALLOC(1,
//			sizeof(*measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultNeighCells));
//
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultNeighCells->present = MeasResults__measResultNeighCells_PR_measResultListEUTRA;
//
//	MeasResultListEUTRA_t  *measResultListEUTRA2;
//
//	measResultListEUTRA2 = CALLOC(1,sizeof(*measResultListEUTRA2));
//
//	struct MeasResultEUTRA *measresulteutra2;
//
//	measresulteutra2 = CALLOC(1,sizeof(*measresulteutra2));
//
//	measresulteutra2->physCellId = phy_id;//1;
//
//	struct MeasResultEUTRA__cgi_Info *measresult_cgi2;
//
//	measresult_cgi2 = CALLOC(1,sizeof(*measresult_cgi2));
//
//	memset(&measresult_cgi2->cellGlobalId.plmn_Identity, 0, sizeof(measresult_cgi2->cellGlobalId.plmn_Identity));
//	// measresult_cgi2->cellGlobalId.plmn_Identity.mcc=CALLOC(1,sizeof(measresult_cgi2->cellGlobalId.plmn_Identity.mcc));
//	measresult_cgi2->cellGlobalId.plmn_Identity.mcc = CALLOC(1, sizeof(*measresult_cgi2->cellGlobalId.plmn_Identity.mcc));
//
//	asn_set_empty(&measresult_cgi2->cellGlobalId.plmn_Identity.mcc->list);//.size=0;
//
//	MCC_MNC_Digit_t dummy;
//	dummy=2;
//	ASN_SEQUENCE_ADD(&measresult_cgi2->cellGlobalId.plmn_Identity.mcc->list,&dummy);
//	dummy=6;
//	ASN_SEQUENCE_ADD(&measresult_cgi2->cellGlobalId.plmn_Identity.mcc->list,&dummy);
//	dummy=2;
//	ASN_SEQUENCE_ADD(&measresult_cgi2->cellGlobalId.plmn_Identity.mcc->list,&dummy);
//
//	measresult_cgi2->cellGlobalId.plmn_Identity.mnc.list.size=0;
//	measresult_cgi2->cellGlobalId.plmn_Identity.mnc.list.count=0;
//	dummy=8;
//	ASN_SEQUENCE_ADD(&measresult_cgi2->cellGlobalId.plmn_Identity.mnc.list,&dummy);
//
//	dummy=0;
//	ASN_SEQUENCE_ADD(&measresult_cgi2->cellGlobalId.plmn_Identity.mnc.list,&dummy);
//
//	measresult_cgi2->cellGlobalId.cellIdentity.buf=MALLOC(8);
//	measresult_cgi2->cellGlobalId.cellIdentity.buf[0]=0x01;
//	measresult_cgi2->cellGlobalId.cellIdentity.buf[1]=0x48;
//	measresult_cgi2->cellGlobalId.cellIdentity.buf[2]=0x0f;
//	measresult_cgi2->cellGlobalId.cellIdentity.buf[3]=0x03;
//	measresult_cgi2->cellGlobalId.cellIdentity.size=4;
//	measresult_cgi2->cellGlobalId.cellIdentity.bits_unused=4;
//	measresult_cgi2->trackingAreaCode.buf = MALLOC(2);
//	measresult_cgi2->trackingAreaCode.buf[0]=0x00;
//	measresult_cgi2->trackingAreaCode.buf[1]=0x10;
//	measresult_cgi2->trackingAreaCode.size=2;
//	measresult_cgi2->trackingAreaCode.bits_unused=0;
//	measresulteutra2->cgi_Info=measresult_cgi2;
//	struct MeasResultEUTRA__measResult meas2;
//	//    int rsrp_va=10;
//	meas2.rsrpResult = &(rsrp_t);
//	//&rsrp_va;
//	meas2.rsrqResult = &(rsrq_t);
//	meas2.ext1 = NULL;
//	measresulteutra2->measResult=meas2;
//	ASN_SEQUENCE_ADD(&measResultListEUTRA2->list, measresulteutra2);
//
//	measurementReport->criticalExtensions.choice.c1.choice.measurementReport_r8.measResults.measResultNeighCells->choice.measResultListEUTRA=*(measResultListEUTRA2);
//
//	if ( LOG_DEBUGFLAG(DEBUG_ASN1) ) {
//		xer_fprint(stdout, &asn_DEF_UL_DCCH_Message, (void *)&ul_dcch_msg);
//	}
//
//	enc_rval = uper_encode_to_buffer(&asn_DEF_UL_DCCH_Message,
//											NULL,
//											(void *)&ul_dcch_msg,
//											buffer,
//											100);
//
//	if(enc_rval.encoded == -1) {
//		printf("[eNB AssertFatal]ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);
//		free(measResultListEUTRA2);
//		measResultListEUTRA2 = NULL;
//		return -1;
//	}
//
//	free(measResultListEUTRA2);
//	measResultListEUTRA2 = NULL;

	return((enc_rval.encoded+7)/8);
}


uint8_t do_ULInformationTransfer(uint8_t **buffer, uint32_t pdu_length, uint8_t *pdu_buffer)
{
	ssize_t encoded;
	UL_DCCH_Message_t ul_dcch_msg;
	memset(&ul_dcch_msg, 0, sizeof(UL_DCCH_Message_t));
	ul_dcch_msg.message.present           = UL_DCCH_MessageType_PR_c1;
//	ul_dcch_msg.message.choice.c1.present = UL_DCCH_MessageType__c1_PR_ulInformationTransfer;
//	ul_dcch_msg.message.choice.c1.choice.ulInformationTransfer.criticalExtensions.present = ULInformationTransfer__criticalExtensions_PR_c1;
//	ul_dcch_msg.message.choice.c1.choice.ulInformationTransfer.criticalExtensions.choice.c1.present = DLInformationTransfer__criticalExtensions__c1_PR_dlInformationTransfer_r8;
//	ul_dcch_msg.message.choice.c1.choice.ulInformationTransfer.criticalExtensions.choice.c1.choice.ulInformationTransfer_r8.dedicatedInfoType.present =
//	ULInformationTransfer_r8_IEs__dedicatedInfoType_PR_dedicatedInfoNAS;
//	ul_dcch_msg.message.choice.c1.choice.ulInformationTransfer.criticalExtensions.choice.c1.choice.ulInformationTransfer_r8.dedicatedInfoType.choice.dedicatedInfoNAS.size = pdu_length;
//	ul_dcch_msg.message.choice.c1.choice.ulInformationTransfer.criticalExtensions.choice.c1.choice.ulInformationTransfer_r8.dedicatedInfoType.choice.dedicatedInfoNAS.buf = pdu_buffer;

	encoded = uper_encode_to_new_buffer (&asn_DEF_UL_DCCH_Message, NULL, (void *) &ul_dcch_msg, (void **) buffer);

	return encoded;
}


WXS_UECapability_t *fill_ue_capability(char *UE_EUTRA_Capability_xer_fname)
{
	static WXS_UECapability_t UECapability; /* TODO declared static to allow returning this has an address should be allocated in a cleaner way. */
//	static SupportedBandEUTRA_t Bandlist[4]; // the macro ASN_SEQUENCE_ADD() does not copy the source, but only stores a reference to it
//	static InterFreqBandInfo_t InterFreqBandInfo[4][4]; // the macro ASN_SEQUENCE_ADD() does not copy the source, but only stores a reference to it
//	static BandInfoEUTRA_t BandInfoEUTRA[4]; // the macro ASN_SEQUENCE_ADD() does not copy the source, but only stores a reference to it
//	asn_enc_rval_t enc_rval;
//	asn_dec_rval_t dec_rval;
//	long maxNumberROHC_ContextSessions = PDCP_Parameters__maxNumberROHC_ContextSessions_cs16;
//	int i;
//	UE_EUTRA_Capability_t *UE_EUTRA_Capability;
//	char UE_EUTRA_Capability_xer[8192];
//	size_t size;
//	printf("Allocating %zu bytes for UE_EUTRA_Capability\n",sizeof(*UE_EUTRA_Capability));
//
//	UE_EUTRA_Capability = CALLOC(1, sizeof(*UE_EUTRA_Capability));
//	assert(UE_EUTRA_Capability);
//
//	if (!UE_EUTRA_Capability_xer_fname)  {
//		Bandlist[0].bandEUTRA  = 3;  // UL 1710-1785, DL 1805-1880 FDD
//		Bandlist[0].halfDuplex = 0;
//		Bandlist[1].bandEUTRA  = 20;  // UL 824-849 , DL 869-894 FDD
//		Bandlist[1].halfDuplex = 0;
//		Bandlist[2].bandEUTRA  = 7;   // UL 2500-2570, DL 2620-2690 FDD
//		Bandlist[2].halfDuplex = 0;
//		Bandlist[3].bandEUTRA  = 38;  // UL/DL 2570-2620, TDD
//		Bandlist[3].halfDuplex = 0;
//		memset((void *)InterFreqBandInfo, 0, sizeof(InterFreqBandInfo));
//		memset((void *)BandInfoEUTRA, 0, sizeof(BandInfoEUTRA));
//		InterFreqBandInfo[0][0].interFreqNeedForGaps = 0;
//		InterFreqBandInfo[0][1].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[0][2].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[0][3].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[1][0].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[1][1].interFreqNeedForGaps = 0;
//		InterFreqBandInfo[1][2].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[1][3].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[2][0].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[2][1].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[2][2].interFreqNeedForGaps = 0;
//		InterFreqBandInfo[2][3].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[3][0].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[3][1].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[3][2].interFreqNeedForGaps = 1;
//		InterFreqBandInfo[3][3].interFreqNeedForGaps = 0;
//		UE_EUTRA_Capability->accessStratumRelease = 0;//AccessStratumRelease_rel8;
//		UE_EUTRA_Capability->ue_Category          = 4;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0001_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0002_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0003_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0004_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0006_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0101_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0102_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0103_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.supportedROHC_Profiles.profile0x0104_r15=0;
//		UE_EUTRA_Capability->pdcp_Parameters.maxNumberROHC_ContextSessions = &maxNumberROHC_ContextSessions;
//		UE_EUTRA_Capability->phyLayerParameters.ue_TxAntennaSelectionSupported = 0;
//		UE_EUTRA_Capability->phyLayerParameters.ue_SpecificRefSigsSupported    = 0;
//		UE_EUTRA_Capability->rf_Parameters.supportedBandListEUTRA.list.count                          = 0;
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->rf_Parameters.supportedBandListEUTRA.list,(void *)&Bandlist[0]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->rf_Parameters.supportedBandListEUTRA.list,(void *)&Bandlist[1]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->rf_Parameters.supportedBandListEUTRA.list,(void *)&Bandlist[2]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->rf_Parameters.supportedBandListEUTRA.list,(void *)&Bandlist[3]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list,(void *)&BandInfoEUTRA[0]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list,(void *)&BandInfoEUTRA[1]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list,(void *)&BandInfoEUTRA[2]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list,(void *)&BandInfoEUTRA[3]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[0]->interFreqBandList.list,(void *)&InterFreqBandInfo[0][0]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[0]->interFreqBandList.list,(void *)&InterFreqBandInfo[0][1]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[0]->interFreqBandList.list,(void *)&InterFreqBandInfo[0][2]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[0]->interFreqBandList.list,(void *)&InterFreqBandInfo[0][3]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[1]->interFreqBandList.list,(void *)&InterFreqBandInfo[1][0]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[1]->interFreqBandList.list,(void *)&InterFreqBandInfo[1][1]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[1]->interFreqBandList.list,(void *)&InterFreqBandInfo[1][2]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[1]->interFreqBandList.list,(void *)&InterFreqBandInfo[1][3]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[2]->interFreqBandList.list,(void *)&InterFreqBandInfo[2][0]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[2]->interFreqBandList.list,(void *)&InterFreqBandInfo[2][1]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[2]->interFreqBandList.list,(void *)&InterFreqBandInfo[2][2]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[2]->interFreqBandList.list,(void *)&InterFreqBandInfo[2][3]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[3]->interFreqBandList.list,(void *)&InterFreqBandInfo[3][0]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[3]->interFreqBandList.list,(void *)&InterFreqBandInfo[3][1]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[3]->interFreqBandList.list,(void *)&InterFreqBandInfo[3][2]);
//		ASN_SEQUENCE_ADD(&UE_EUTRA_Capability->measParameters.bandListEUTRA.list.array[3]->interFreqBandList.list,(void *)&InterFreqBandInfo[3][3]);
//
//		// UE_EUTRA_Capability->measParameters.bandListEUTRA.list.count                         = 0;  // no measurements on other bands
//		// UE_EUTRA_Capability->featureGroupIndicators  // null
//
//		if (get_softmodem_params()->usim_test == 1) {
//		// featureGroup is mandatory for CMW tests
//		// featureGroup is filled only for usim-test mode
//		BIT_STRING_t *bit_string = CALLOC(1, sizeof(*bit_string));
//		char featrG[4]           = { 0x00, 0x08, 0x00, 0x04 };
//		bit_string->buf          = CALLOC(1, 4);
//		memcpy(bit_string->buf, featrG, 4);
//		bit_string->size         = 4;
//		bit_string->bits_unused  = 0;
//		UE_EUTRA_Capability->featureGroupIndicators = bit_string;
//		}
//
//		// UE_EUTRA_Capability->interRAT_Parameters     // null
//	} else {
//		FILE *f = fopen(UE_EUTRA_Capability_xer_fname, "r");
//		assert(f);
//		size = fread(UE_EUTRA_Capability_xer, 1, sizeof UE_EUTRA_Capability_xer, f);
//		fclose(f);
//
//		if (size == 0 || size == sizeof UE_EUTRA_Capability_xer) {
//			printf("UE Capabilities XER file %s is too large\n", UE_EUTRA_Capability_xer_fname);
//			free( UE_EUTRA_Capability);
//			return(NULL);
//		}
//
//		dec_rval = xer_decode(0, &asn_DEF_UE_EUTRA_Capability, (void *)UE_EUTRA_Capability, UE_EUTRA_Capability_xer, size);
//		assert(dec_rval.code == RC_OK);
//	}
//
//	UECapability.UE_EUTRA_Capability = UE_EUTRA_Capability;
//
//	if ( LOG_DEBUGFLAG(DEBUG_ASN1) ) {
//		xer_fprint(stdout,&asn_DEF_UE_EUTRA_Capability,(void *)UE_EUTRA_Capability);
//	}
//
//	enc_rval = uper_encode_to_buffer(&asn_DEF_UE_EUTRA_Capability,
//											NULL,
//											(void *)UE_EUTRA_Capability,
//											&UECapability.sdu[0],
//											MAX_UE_CAPABILITY_SIZE);
//
//	AssertFatal (enc_rval.encoded > 0, "ASN1 message encoding failed (%s, %lu)!\n", enc_rval.failed_type->name, enc_rval.encoded);
//
//	UECapability.sdu_size = (enc_rval.encoded + 7) / 8;
//	printf("[RRC]UE Capability encoded, %d bytes (%zd bits)\n",
//	UECapability.sdu_size, enc_rval.encoded + 7);
//
//	{
//	char *sdu;
//	sdu = malloc(3 * UECapability.sdu_size + 1 /* For '\0' */);
//
//	for (i = 0; i < UECapability.sdu_size; i++) {
//		sprintf (&sdu[3 * i], "%02x.", UECapability.sdu[i]);
//	}
//
//	printf("[RRC]UE Capability encoded, %s\n", sdu);
//	free(sdu);
//	}

	return(&UECapability);
}

