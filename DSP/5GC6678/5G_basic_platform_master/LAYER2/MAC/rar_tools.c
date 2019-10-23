#include "mac.h"
#include "mac_proto.h"
#include "mac_extern.h"


#define DEBUG_RAR
#undef DEBUG_RAR



//------------------------------------------------------------------------------
uint16_t process_rar(const module_id_t module_idP,
							const int CC_id,
							const frame_t frameP,
							const sub_frame_t subframe,
							const slot_t slot,
							const rnti_t ra_rnti,
							uint8_t * const dlsch_buffer,
							sdu_size_t const dlen,
							rnti_t * const t_crnti,
							const PREAMBLE_IND preamble_index,
							uint8_t * selected_rar_buffer	// output argument for storing the selected RAR header and RAR payload
)
//------------------------------------------------------------------------------
{
	uint16_t ret = 0;		// return value

	RA_HEADER_BI* bi;

	RA_HEADER_RAPID *rarh;

	uint8_t *rar;
	int offset = 0;

//	get the last RAR payload for working with CMW500
	uint8_t n_rarpy = 0;	// number of RAR payloads

	uint8_t best_rx_rapid = -1;	// the closest RAPID receive from all RARs

	while (dlen > offset) {
		rarh = (RA_HEADER_RAPID *)(dlsch_buffer + offset);

		if(rarh->T == 0) {// MAC subPDU (BI only)，偏移1字节
			bi = (RA_HEADER_BI *)dlsch_buffer;

			printf("BI = %d, backoff = %d\n", bi->BI, BACKOFF[bi->BI]);

			offset += 1;
		} else {// MAC subPDU RAPID or RAPID and RAR
			offset += 1;

			if(rarh->RAPID == preamble_index.PreambleID) {
				if(preamble_index.T == Random_Access) {
					rar = (uint8_t *)(dlsch_buffer + offset);

					*t_crnti = (uint16_t) rar[6] + (((uint16_t)rar[5]) << 8);	//rar->t_crnti;

					memcpy(selected_rar_buffer, (uint8_t *)rarh, 1);
					memcpy(selected_rar_buffer + 1, (uint8_t *)rar, 7);

					offset += 7;

					n_rarpy++;
				} else if(preamble_index.T == NO_Random_Access) {
					rar = (uint8_t *)(dlsch_buffer + offset);

					*t_crnti = (uint16_t) rar[6] + (((uint16_t)rar[5]) << 8);	//rar->t_crnti;
					ue_mac_inst[module_idP].cs_RNTI = *t_crnti;

					memcpy(selected_rar_buffer, (uint8_t *)rarh, 1);
					memcpy(selected_rar_buffer + 1, (uint8_t *)rar, 7);

					offset += 7;
					n_rarpy++;
				} else if(preamble_index.T == SI_REQUEST_RA) {
					printf("SI request success!\n");
				} else {
					printf("Can't match preamble indentity!\n");
					offset += 7;
				}
			} else {

			}
		}
	}

	printf("number of RAR subheader %d; number of RAR pyloads %d\n", n_rarpy, n_rarpy);

	printf("[UE %d][RAPROC] Frame %d Received RAR (%02x|%02x.%02x.%02x.%02x.%02x.%02x.%02x) for preamble %d/%d\n",
			module_idP, frameP, *(uint8_t *) rarh, rar[0], rar[1], rar[2],
			rar[3], rar[4], rar[5], rar[6], rarh->RAPID, preamble_index);

	return ret;
}
