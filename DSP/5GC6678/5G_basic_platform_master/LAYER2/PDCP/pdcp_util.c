#include <assert.h>
#include "pdcp_util.h"

/*
 * Prints incoming byte stream in hexadecimal and readable form
 *
 * @param component Utilised as with macros defined in UTIL/LOG/log.h
 * @param data unsigned char* pointer for data buffer
 * @param size Number of octets in data buffer
 * @return none
 */
void util_print_hex_octets(unsigned char* data, unsigned long size)
{
	if (data == NULL) {
		printf("Incoming buffer is NULL! Ignoring...\n");
		return;
	}

	unsigned long octet_index = 0;

	printf("     |  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f |\n");
	printf("-----+-------------------------------------------------|\n");
	printf(" 000 |");

	for (octet_index = 0; octet_index < size; ++octet_index) {
		/*
		* Print every single octet in hexadecimal form
		*/
		printf("%02x.", data[octet_index]);

		/*
		* Align newline and pipes according to the octets in groups of 2
		*/
		if (octet_index != 0 && (octet_index + 1) % 16 == 0) {
			printf(" |\n");
			printf(" %03lu |", octet_index);
		}
	}

	/*
	* Append enough spaces and put final pipe
	*/
	unsigned char index;

	for (index = octet_index; index < 16; ++index) {
		printf("   ");
	}

	printf(" \n");
}

void util_flush_hex_octets(unsigned char* data, unsigned long size)
{
	if (data == NULL) {
		printf("Incoming buffer is NULL! Ignoring...\n");
		return;
	}

	printf("[PDCP]");

	unsigned long octet_index = 0;

	for (octet_index = 0; octet_index < size; ++octet_index) {
		//printf("%02x.", data[octet_index]);
		printf("%02x.", data[octet_index]);
	}

	//printf(" \n");
	printf(" \n");
}

/*
 * Prints binary representation of given octet prepending
 * passed log message
 *
 * @param Octet as an unsigned character
 * @return None
 */
void util_print_binary_representation(unsigned char* message, uint8_t octet)
{
	unsigned char index = 0;
	unsigned char mask = 0x80;

	printf("%s", message);

	for (index = 0; index < 8; ++index) {
		if (octet & mask) {
			printf("1");
		} else {
			printf("0");
		}

		mask /= 2;
	}

	printf("\n");
}

/*
 * Sets the bit of given octet at `index'
 *
 * @param octet 8-bit data
 * @param index Index of bit to be set
 * @return TRUE on success, FALSE otherwise
 */
boolean_t util_mark_nth_bit_of_octet(uint8_t* octet, uint8_t index)
{
	uint8_t mask = 0x80;

	assert(octet != NULL);

	/*
	* Prepare mask
	*/
	mask >>= index;

	/*
	* Set relevant bit
	*/
	*octet |= mask;

	return TRUE;
}

