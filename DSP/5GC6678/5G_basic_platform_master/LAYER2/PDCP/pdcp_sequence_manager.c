#include "pdcp_sequence_manager.h"
#include "pdcp_util.h"

/*
 * Initializes sequence numbering state
 * @param pdcp_entity The PDCP entity to be initialized
 * @return boolean_t TRUE on success, FALSE otherwise
 */
boolean_t pdcp_init_seq_numbers(pdcp_t* pdcp_entity)
{
	if (pdcp_entity == NULL) {
	return FALSE;
	}

	/* Sequence number state variables */

	// TX and RX window
//	pdcp_entity->next_pdcp_tx_sn = 0;
	pdcp_entity->next_pdcp_rx_sn = 0;

	// TX and RX Hyper Frame Numbers
	pdcp_entity->tx_hfn = 0;
	pdcp_entity->rx_hfn = 0;

	// SN of the last PDCP SDU delivered to upper layers
	// Shall UE and eNB behave differently on initialization? (see 7.1)
	pdcp_entity->last_submitted_pdcp_rx_sn = pdcp_entity->seq_num_size == 12 ? 4095 : 262143;

	return TRUE;
}

boolean_t pdcp_is_seq_num_size_valid(pdcp_t* pdcp_entity)
{
	if (pdcp_entity == NULL) {
		return FALSE;
	}

	// Check if the size of SN is valid (see 3GPP TS 38.323 v15.6.0 item 6.3.2)
	if (pdcp_entity->seq_num_size != 12 && pdcp_entity->seq_num_size != 18) {
		printf("Incoming SN size is invalid! (Expected: {12 | 18}, Received: %d\n", pdcp_entity->seq_num_size);
		return FALSE;
	}

	return TRUE;
}

/**
 * Check if SN number is in the range according to SN size
 */
boolean_t pdcp_is_seq_num_valid(uint32_t seq_num, uint8_t seq_num_size)
{
	if (seq_num >= 0 && seq_num <= pdcp_calculate_max_seq_num_for_given_size(seq_num_size)) {
		return TRUE;
	}

	return FALSE;
}

uint32_t pdcp_calculate_max_seq_num_for_given_size(uint8_t seq_num_size)
{
	uint32_t max_seq_num = 1;

	max_seq_num <<= seq_num_size;

	return max_seq_num - 1;
}

uint32_t pdcp_get_next_tx_seq_number(pdcp_t* pdcp_entity)
{
//	if (pdcp_is_seq_num_size_valid(pdcp_entity) == FALSE) {
//		return -1;
//	}

//	At reception of a PDCP SDU from upper layers, the transmitting PDCP entity shall:
//		-	start the discardTimer associated with this PDCP SDU (if configured).
//	For a PDCP SDU received from upper layers, the transmitting PDCP entity shall:
//		-	associate the COUNT value corresponding to TX_NEXT to this PDCP SDU;
//	NOTE 1:	Associating more than half of the PDCP SN space of contiguous PDCP SDUs with PDCP SNs, when e.g., the PDCP SDUs are discarded or transmitted without acknowledgement, may cause HFN desynchronization problem. How to prevent HFN desynchronization problem is left up to UE implementation.
//		-	perform header compression of the PDCP SDU as specified in the clause 5.7.4;
//		-	perform integrity protection, and ciphering using the TX_NEXT as specified in the clause 5.9 and 5.8, respectively;
//		-	set the PDCP SN of the PDCP Data PDU to TX_NEXT modulo 2[pdcp-SN-SizeUL];
//		-	increment TX_NEXT by one;
//		-	submit the resulting PDCP Data PDU to lower layer as specified below.
//	When submitting a PDCP PDU to lower layer, the transmitting PDCP entity shall:
//		-	if the transmitting PDCP entity is associated with one RLC entity:
//			-	submit the PDCP PDU to the associated RLC entity;
//		-	else, if the transmitting PDCP entity is associated with two RLC entities:
//			-	if the PDCP duplication is activated:
//				-	if the PDCP PDU is a PDCP Data PDU:
//					-	duplicate the PDCP Data PDU and submit the PDCP Data PDU to both associated RLC entities;
//				-	else:
//					-	submit the PDCP Control PDU to the primary RLC entity;
//			-	else:
//				-	if the two associated RLC entities belong to the different Cell Groups; and
//				-	if the total amount of PDCP data volume and RLC data volume pending for initial transmission (as specified in TS 38.322 [5]) in the two associated RLC entities is equal to or larger than ul-DataSplitThreshold:
//					-	submit the PDCP PDU to either the primary RLC entity or the secondary RLC entity;
//				-	else:
//					-	submit the PDCP PDU to the primary RLC entity.
//	NOTE 2:	If the transmitting PDCP entity is associated with two RLC entities, the UE should minimize the amount of PDCP PDUs submitted to lower layers before receiving request from lower layers and minimize the PDCP SN gap between PDCP PDUs submitted to two associated RLC entities to minimize PDCP reordering delay in the receiving PDCP entity.

	// Sequence number should be incremented after it is assigned for a PDU
	uint32_t pdcp_seq_num = pdcp_entity->TX_NEXT % (2 << pdcp_entity->pdcp_SN_SizeUL);

	pdcp_entity->TX_NEXT++;

	return pdcp_seq_num;
}

boolean_t pdcp_advance_rx_window(pdcp_t* pdcp_entity)
{
	if (pdcp_is_seq_num_size_valid(pdcp_entity) == FALSE) {
		return FALSE;
	}

	/*
	* Update sequence numbering state and Hyper Frame Number if SN has already reached
	* its max value (see 5.1 PDCP Data Transfer Procedures)
	*/
	printf( "Advancing RX window...\n");

	if (pdcp_entity->next_pdcp_rx_sn == pdcp_calculate_max_seq_num_for_given_size(pdcp_entity->seq_num_size)) {
		pdcp_entity->next_pdcp_rx_sn = 0;
		pdcp_entity->rx_hfn++;
	} else {
		pdcp_entity->next_pdcp_rx_sn++;
	}

	return TRUE;
}

boolean_t pdcp_mark_current_pdu_as_received(uint32_t seq_num, pdcp_t* pdcp_entity)
{
	/*
	* Incoming sequence number and PDCP entity were already
	* validated in pdcp_is_rx_seq_number_valid() so we don't
	* check here
	*/

	/*
	* Find relevant octet
	*/
	uint16_t octet_index = seq_num / 8;
	/*
	* Set relevant bit
	*/
	printf( "Marking %d. bit of %d. octet of status bitmap\n", (seq_num % 8) + 1, octet_index);

	util_mark_nth_bit_of_octet(&pdcp_entity->missing_pdu_bitmap[octet_index], seq_num % 8);

	util_print_binary_representation((uint8_t*)"Current state of relevant octet: ", pdcp_entity->missing_pdu_bitmap[octet_index]);

	return TRUE;
}
