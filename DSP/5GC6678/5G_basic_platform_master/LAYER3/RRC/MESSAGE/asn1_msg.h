#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h> /* for atoi(3) */
#include <unistd.h> /* for getopt(3) */
#include <string.h> /* for strerror(3) */
#include <sysexits.h> /* for EX_* exit codes */
#include <errno.h>  /* for errno */

#include <asn_application.h>
#include <asn_internal.h> /* for _ASN_DEFAULT_STACK_MAX */

#include "rrc_defs.h"

/*
 * The variant of the above function which dumps the BASIC-XER (XER_F_BASIC)
 * output into the chosen string buffer.
 * RETURN VALUES:
 *       0: The structure is printed.
 *      -1: Problem printing the structure.
 * WARNING: No sensible errno value is returned.
 */
int xer_sprint(char *string, size_t string_size, struct asn_TYPE_descriptor_s *td, void *sptr);

uint16_t get_adjacent_cell_id(uint8_t Mod_id,uint8_t index);

uint8_t get_adjacent_cell_mod_id(uint16_t phyCellId);


/**
\brief Generate an RRCConnectionRequest UL-CCCH-Message (UE) based on random string or S-TMSI.  This
routine only generates an mo-data establishment cause.
@param buffer Pointer to PER-encoded ASN.1 description of UL-DCCH-Message PDU
@param rv 5 byte random string or S-TMSI
@returns Size of encoded bit stream in bytes*/

uint8_t do_RRCConnectionRequest(uint8_t Mod_id, uint8_t *buffer,uint8_t *rv);

/**
\brief Generate an SidelinkUEInformation UL-DCCH-Message (UE).
@param destinationInfoList Pointer to a list of destination for which UE requests E-UTRAN to assign dedicated resources
@param discTxResourceReq Pointer to  number of discovery messages for discovery announcements for which  UE requests E-UTRAN to assign dedicated resources
@param mode Indicates different requests from upper layers
@returns Size of encoded bit stream in bytes*/
//uint8_t do_SidelinkUEInformation(uint8_t Mod_id, uint8_t *buffer, LTE_SL_DestinationInfoList_r12_t  *destinationInfoList, long *discTxResourceReq, SL_TRIGGER_t mode);

/** \brief Generate an RRCConnectionSetupComplete UL-DCCH-Message (UE)
@param buffer Pointer to PER-encoded ASN.1 description of UL-DCCH-Message PDU
@returns Size of encoded bit stream in bytes*/
uint8_t do_RRCConnectionSetupComplete(uint8_t Mod_id, uint8_t *buffer, const uint8_t Transaction_id, const int dedicatedInfoNASLength,
                                      const char *dedicatedInfoNAS);

/** \brief Generate an RRCConnectionReconfigurationComplete UL-DCCH-Message (UE)
@param buffer Pointer to PER-encoded ASN.1 description of UL-DCCH-Message PDU
@returns Size of encoded bit stream in bytes*/
uint8_t do_RRCConnectionReconfigurationComplete(const protocol_ctxt_t *const ctxt_pP,
														uint8_t *buffer,
														const uint8_t Transaction_id
);


/**
\brief Generate an RRCConnectionRequest UL-CCCH-Message (UE) based on random string or S-TMSI.  This
routine only generates an mo-data establishment cause.
@param Mod_id Module ID of eNB
@param buffer Pointer to PER-encoded ASN.1 description of UL-DCCH-Message PDU
@param transaction_id Transaction index
@returns Size of encoded bit stream in bytes*/

uint8_t do_RRCConnectionRelease(uint8_t Mod_id, uint8_t *buffer,int Transaction_id);

uint8_t do_MeasurementReport(uint8_t Mod_id, uint8_t *buffer,int measid,int phy_id,long rsrp_s,long rsrq_s,long rsrp_t,long rsrq_t);

//uint8_t do_DLInformationTransfer(uint8_t Mod_id, uint8_t **buffer, uint8_t transaction_id, uint32_t pdu_length, uint8_t *pdu_buffer);

//uint8_t do_Paging(uint8_t Mod_id, uint8_t *buffer, ue_paging_identity_t ue_paging_identity, cn_domain_t cn_domain);

uint8_t do_ULInformationTransfer(uint8_t **buffer, uint32_t pdu_length, uint8_t *pdu_buffer);

//int do_HandoverPreparation(char *ho_buf, int ho_size, UE_EUTRA_Capability_t *ue_eutra_cap, int rrc_size);

int do_HandoverCommand(char *ho_buf, int ho_size, char *rrc_buf, int rrc_size);

WXS_UECapability_t *fill_ue_capability(char *LTE_UE_EUTRA_Capability_xer);

