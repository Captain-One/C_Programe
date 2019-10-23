#define RLC_UM_MODULE 1
#define RLC_UM_RECEIVER_C 1
#include "platform_types.h"
//-----------------------------------------------------------------------------
#include "rlc.h"
#include "rlc_um.h"
#include "rlc_um_structs.h"
#include "rlc_primitives.h"
#include "list.h"


//-----------------------------------------------------------------------------
void rlc_um_display_rx_window(const protocol_ctxt_t* const ctxt_pP,
									rlc_um_entity_t * const rlc_pP
)
{
	unsigned long sn = 0;
	unsigned long end_sn = 0;
	//  LOG_USEDINLOG_VAR(char,str[4]);
	char str[4];
	char          time_out_str[11];
	int           str_index;
	char          color[32];

	printf("\n");
	printf("+-------------------------------------------------------------------------------------------------------+");
	printf("\n");
	sprintf(time_out_str, "%010d", rlc_pP->t_reassembly.ms_duration);
	time_out_str[10] = 0;
	printf("| RLC UM RB %02d    VR(UR)=%03d    VR(UX)=%03d    VR(UH)=%03d    t-Reordering: %s %s %s             |",
	rlc_pP->rb_id, rlc_pP->RX_Next, rlc_pP->RX_Next_Reassembly, rlc_pP->RX_Next_Highest,
	(rlc_pP->t_reassembly.running)?" ON":"OFF",
	(rlc_pP->t_reassembly.running)?"Time-out frameP:":"               ",
	(rlc_pP->t_reassembly.running)?time_out_str:"          ");
	printf("\n");
	printf("+------+------------------------------------------------------------------------------------------------+");
	printf("\n");
	printf("|      |00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 |");
	printf("\n");
	printf("+------+------------------------------------------------------------------------------------------------+");
	printf("\n");

	if (rlc_pP->rx_sn_length == 10) {
		end_sn = RLC_UM_SN_10_BITS_MODULO;
	} else {
		end_sn = RLC_UM_SN_5_BITS_MODULO;
	}


	for (sn = 0; sn < end_sn; sn++) {
		str[0]    = ' ';
		str[1]    = ' ';
		str[2]    = ' ';
		str[3]    = 0;
		str_index = 0;

		if ((sn % 32) == 0) {
			if ((sn != 0)) {
				printf("%s%s|", RLC_FG_COLOR_DEFAULT, RLC_NORMAL_VIDEO);
				printf("\n");
			}

			printf("%s%s| %04lu |", RLC_FG_COLOR_DEFAULT, RLC_NORMAL_VIDEO, sn);
		}

		strcpy(color, RLC_FG_COLOR_DEFAULT);

		if (sn == rlc_pP->RX_Next) {
			str[str_index++] = 'R';
			strcpy(color, RLC_FG_COLOR_BLUE);
		}

		if (sn == rlc_pP->RX_Next_Reassembly) {
			str[str_index++] = 'X';
			strcpy(color, RLC_FG_COLOR_ORANGE);
		}

		if (sn == rlc_pP->RX_Next_Highest) {
			str[str_index++] = 'H';
			strcpy(color, RLC_FG_COLOR_RED);
		}

		if (rlc_um_get_pdu_from_dar_buffer(ctxt_pP, rlc_pP, sn)) {
//			test RLC_REVERSE_VIDEO
			if (str_index <= 2) {
				str[str_index] = '.';
			}

			printf("%s%s%s", color, RLC_REVERSE_VIDEO, str);
		} else {
			printf("%s%s%s", color, RLC_NORMAL_VIDEO, str);
		}
	}

	printf("%s%s|", RLC_FG_COLOR_DEFAULT, RLC_NORMAL_VIDEO);
	printf("\n");
	printf("+------+------------------------------------------------------------------------------------------------+");
	printf("\n");
}

//-----------------------------------------------------------------------------
void rlc_um_receive (const protocol_ctxt_t* const ctxt_pP, rlc_um_entity_t * const rlc_pP, struct mac_data_ind data_indP)
{
	mem_block_t        *tb_p             = NULL;
	uint8_t               *first_byte_p     = NULL;
	uint16_t               tb_size_in_bytes = 0;

	while ((tb_p = list_remove_head (&data_indP.data)))
	{
	first_byte_p = ((struct mac_tb_ind *) (tb_p->data))->data_ptr;
	tb_size_in_bytes = ((struct mac_tb_ind *) (tb_p->data))->size;

	rlc_pP->stat_rx_data_bytes += tb_size_in_bytes;
	rlc_pP->stat_rx_data_pdu   += 1;

	if (tb_size_in_bytes > 0) {
		rlc_um_receive_process_dar (ctxt_pP, rlc_pP, tb_p, (rlc_um_pdu_sn_10_t*)first_byte_p, tb_size_in_bytes);
	}
	}
}
