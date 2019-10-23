#define RLC_UM_MODULE 1
#define RLC_UM_REASSEMBLY_C 1
#include "platform_types.h"
//-----------------------------------------------------------------------------
#include <string.h>
#if ENABLE_ITTI
# include "platform_types.h"
# include "intertask_interface.h"
#endif
#include "assertions.h"
#include "rlc.h"
#include "rlc_um.h"
#include "rlc_primitives.h"
#include "list.h"
#include "mac_extern.h"


//-----------------------------------------------------------------------------
inline void rlc_um_clear_rx_sdu(const protocol_ctxt_t* const ctxt_pP, rlc_um_entity_t* rlc_pP)
{
	rlc_pP->output_sdu_size_to_write = 0;
}

//-----------------------------------------------------------------------------
void rlc_um_reassembly(const protocol_ctxt_t* const ctxt_pP, rlc_um_entity_t *rlc_pP, uint8_t * src_pP, int32_t lengthP)
{
	sdu_size_t      sdu_max_size;

	printf(PROTOCOL_RLC_UM_CTXT_FMT"[REASSEMBLY] reassembly()  %d bytes %d bytes already reassemblied\n",
			PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP,rlc_pP), lengthP, rlc_pP->output_sdu_size_to_write);

	if (lengthP <= 0) {
		return;
	}

	if ((rlc_pP->is_data_plane)) {
		sdu_max_size = RLC_SDU_MAX_SIZE_DATA_PLANE;
	} else {
		sdu_max_size = RLC_SDU_MAX_SIZE_CONTROL_PLANE;
	}

	if (rlc_pP->output_sdu_in_construction == NULL) {
		rlc_pP->output_sdu_in_construction = get_free_mem_block (sdu_max_size, __func__);
		rlc_pP->output_sdu_size_to_write = 0;
	}

	if ((rlc_pP->output_sdu_in_construction)) {
		// check if no overflow in size
		if ((rlc_pP->output_sdu_size_to_write + lengthP) <= sdu_max_size) {
			memcpy (&rlc_pP->output_sdu_in_construction->data[rlc_pP->output_sdu_size_to_write], src_pP, lengthP);
			rlc_pP->output_sdu_size_to_write += lengthP;
		} else {
			printf(PROTOCOL_RLC_UM_CTXT_FMT"[REASSEMBLY] [max_sdu size %d] ERROR  SDU SIZE OVERFLOW SDU GARBAGED\n",
			PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP,rlc_pP),
			sdu_max_size);
			// erase  SDU
			rlc_pP->output_sdu_size_to_write = 0;
		}
	} else {
		printf(PROTOCOL_RLC_UM_CTXT_FMT"[REASSEMBLY]ERROR  OUTPUT SDU IS NULL\n", PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP,rlc_pP));
	}
}
//-----------------------------------------------------------------------------
void rlc_um_send_sdu (const protocol_ctxt_t* const ctxt_pP, rlc_um_entity_t *rlc_pP)
{
	if ((rlc_pP->output_sdu_in_construction)) {
		printf(PROTOCOL_RLC_UM_CTXT_FMT" SEND_SDU to upper layers %d bytes sdu %p\n",
				PROTOCOL_RLC_UM_CTXT_ARGS(ctxt_pP,rlc_pP),
				rlc_pP->output_sdu_size_to_write, rlc_pP->output_sdu_in_construction);

		if (rlc_pP->output_sdu_size_to_write > 0) {
			rlc_pP->stat_rx_pdcp_sdu += 1;
			rlc_pP->stat_rx_pdcp_bytes += rlc_pP->output_sdu_size_to_write;

			rlc_data_ind (ctxt_pP,
							BOOL_NOT(rlc_pP->is_data_plane),
							0,
							rlc_pP->rb_id,
							rlc_pP->output_sdu_size_to_write,
							rlc_pP->output_sdu_in_construction);

			rlc_pP->output_sdu_in_construction = NULL;
		} else {
			printf("[SEND_SDU] ERROR SIZE <= 0 ... DO NOTHING, SET SDU SIZE TO 0\n");
		}

		rlc_pP->output_sdu_size_to_write = 0;
	}
}
