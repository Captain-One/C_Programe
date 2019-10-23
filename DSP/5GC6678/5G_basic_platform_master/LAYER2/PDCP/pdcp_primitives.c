#include "platform_types.h"
#include "platform_constants.h"
#include "pdcp.h"
#include "pdcp_primitives.h"

extern boolean_t util_mark_nth_bit_of_octet(uint8_t* octet, uint8_t index);

/*
 * Parses data/control field out of buffer of User Plane PDCP Data PDU with
 * long PDCP SN (12-bit)
 *
 * @param pdu_buffer PDCP PDU buffer
 * @return 1 bit dc
 */
uint8_t pdcp_get_dc_filed(unsigned char* pdu_buffer)
{
	uint8_t dc = 0x00;

	if (pdu_buffer == NULL) {
		return 0;
	}

	dc = (uint8_t)pdu_buffer[0] & 0x80;
	dc >>= 7;

	return dc;
}

/*
 * Parses sequence number out of buffer of User Plane PDCP Data PDU with
 * long PDCP SN (18-bit)
 *
 * @param pdu_buffer PDCP PDU buffer
 * @return 18-bit sequence number
 */
uint32_t pdcp_get_sequence_number_of_pdu_with_sn18(unsigned char* pdu_buffer)
{
	uint32_t sequence_number = 0x00000000;

	if (pdu_buffer == NULL) {
		return 0;
	}

	/*
	* First octet carries the first 2 bits of SN (see 6.2.2.3)
	*/
	sequence_number = (uint8_t)pdu_buffer[0] & 0x03; // Reset D/C field
	sequence_number <<= 8;
	/*
	* Second octet carries the second part (8-bit) of SN (see 6.2.2.3)
	*/
	sequence_number |= (uint8_t)pdu_buffer[1] & 0xFF;
	sequence_number <<= 8;
	/*
	* Third octet carries the thrid part (8-bit) of SN (see 6.2.2.3)
	*/
	sequence_number |= (uint8_t)pdu_buffer[2] & 0xFF;

	return sequence_number;
}

/*
 * Parses sequence number out of buffer of User Plane PDCP Data PDU with
 * short PDCP SN (12-bit)
 *
 * @param pdu_buffer PDCP PDU buffer
 * @return 12-bit sequence number
 */
uint32_t pdcp_get_sequence_number_of_pdu_with_sn12(unsigned char* pdu_buffer)
{
	if (pdu_buffer == NULL) {
		return 0;
	}

	uint32_t sequence_number = 0;

	/*
	* Start 2 octet carries all 12 bits of SN (see 6.2.2.2)
	*/
	sequence_number = (*pdu_buffer) & 0x0F;
	sequence_number <<= 8;
	sequence_number |= *(pdu_buffer + 1);

	return sequence_number;
//	return (uint32_t)((((uint32_t)(pdu_buffer[0] & 0x0000000F)) << 8) | pdu_buffer[1]); // Reset D/C field
}
/*
 * Parses sequence number out of buffer of Control Plane PDCP Data PDU with
 * short PDCP SN (12-bit)
 *
 * @param pdu_buffer PDCP PDU buffer
 * @return 12-bit sequence number
 */
uint32_t pdcp_get_sequence_number_of_pdu_with_SRB_sn(unsigned char* pdu_buffer)
{

	return pdcp_get_sequence_number_of_pdu_with_sn12(pdu_buffer);

#if 0
	if (pdu_buffer == NULL) {
		return 0;
	}

	/*
	* Start 2 octet carries all 12 bits of SN (see 6.2.2.1)
	*/
	return (uint32_t)((((uint32_t)(pdu_buffer[0] & 0x0000000F)) << 8) | pdu_buffer[1]);
#endif
}
/*
 * Fills the incoming buffer with the fields of the header for srb sn
 *
 * @param pdu_buffer PDCP PDU buffer
 * @return TRUE on success, FALSE otherwise
 */
boolean_t pdcp_serialize_control_plane_data_pdu_with_SRB_sn_buffer(unsigned char* pdu_buffer,
																			pdcp_control_plane_data_pdu_header* pdu)
{
	if (pdu_buffer == NULL || pdu == NULL) {
		return FALSE;
	}

	/*
	* Fill the Sequence Number field
	*/
	uint32_t sequence_number = pdu->sn;
	pdu_buffer[1] = sequence_number & 0x000000FF;// Second 8bit sn
	sequence_number >>= 8;
	pdu_buffer[0] = sequence_number & 0x0000000F;// First 4bit sn

	return TRUE;
}

/*
 * Fills the incoming buffer with the fields of the header for 12bit-sn
 *
 * @param pdu_buffer PDCP PDU buffer
 * @return TRUE on success, FALSE otherwise
 */
boolean_t pdcp_serialize_user_plane_data_pdu_with_sn12_buffer(unsigned char* pdu_buffer,
																			pdcp_user_plane_data_pdu_header_with_sn12* pdu)
{
	if (pdu_buffer == NULL || pdu == NULL) {
		return FALSE;
	}

	/*
	* Fill the Sequence Number field
	*/
	uint32_t sequence_number = pdu->sn;
	pdu_buffer[1] = sequence_number & 0x000000FF;
	sequence_number >>= 8;
	pdu_buffer[0] = sequence_number & 0x0000000F;

	/*
	* Fill Data or Control field
	*/
	if (pdu->dc == PDCP_DATA_PDU_BIT_SET) {
		printf("Setting PDU as a DATA PDU\n");
		pdu_buffer[0] |= 0x80; // set the first bit as 1
	}

	return TRUE;
}

boolean_t pdcp_serialize_user_plane_data_pdu_with_DRB_sn_buffer(unsigned char* pdu_buffer, uint8_t seq_size,
																			pdcp_user_plane_data_pdu_header* pdu)
{
	if (pdu_buffer == NULL || pdu == NULL || ((seq_size != 12) && (seq_size != 18))) {
		return FALSE;
	}

	/*
	* Fill the Sequence Number field
	*/
	if(seq_size == 12) {
		uint32_t sequence_number = pdu->sn;
		pdu_buffer[1] = sequence_number & 0x000000FF;
		sequence_number >>= 8;
		pdu_buffer[0] = sequence_number & 0x0000000F;
	}
	else {
		uint32_t sequence_number = pdu->sn;
		pdu_buffer[2] = sequence_number & 0x000000FF;
		sequence_number >>= 8;
		pdu_buffer[1] = sequence_number & 0x000000FF;
		sequence_number >>= 8;
		pdu_buffer[0] = sequence_number & 0x00000003;
	}

	/*
	* Fill Data or Control field
	*/
	if (pdu->dc == PDCP_DATA_PDU_BIT_SET) {
		printf("Setting PDU as a DATA PDU\n");
		pdu_buffer[0] |= 0x80; // set the first bit as 1
	}

	return TRUE;
}

/*
 * Fills the incoming PDU buffer with with given control PDU
 *
 * @param pdu_buffer The buffer that PDU will be serialized into
 * @param pdu A status report header
 * @return TRUE on success, FALSE otherwise
 */
boolean_t pdcp_serialize_control_pdu_for_pdcp_status_report(unsigned char* pdu_buffer,
																		uint8_t bitmap[512],
																		pdcp_control_pdu_for_pdcp_status_report* pdu)
{
	if (pdu_buffer == NULL || pdu == NULL) {
		return FALSE;
	}

	/*
	* Data or Control field and PDU type (already 0x00, noop)
	*
	* Set leftmost bit to set this PDU as `Control PDU'
	*/
	util_mark_nth_bit_of_octet(((uint8_t*)&pdu_buffer[0]), 1);

	/*
	* Fill `First Missing PDU SN' field
	*/
	pdu_buffer[0] |= ((pdu->first_missing_count >> 8) & 0xFF);
	pdu_buffer[1] |= (pdu->first_missing_count & 0xFF);

	/*
	* Append `bitmap'
	*/
	memcpy(pdu_buffer + 2, bitmap, 512);

	return TRUE;
}

