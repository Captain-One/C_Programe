#include "pdcp.h"
#include "pdcp_primitives.h"
#include "pdcp_list.h"



boolean_t pdcp_rx_list_check_duplicate_insert_sdu(
	const protocol_ctxt_t* const  ctxt_pP,
	pdcp_t* const pdcp_entity,
	mem_block_t* tb_pP)
{
	pdcp_pdu_info_t* pdu_rx_info_p = NULL;
	mem_block_t*       cursor_p = NULL;
	uint32_t cursor_count;
	uint32_t rcvd_count;

	pdu_rx_info_p = (pdcp_pdu_info_t*)tb_pP->data;
	cursor_p = pdcp_entity->reception_buffer.head;
	rcvd_count = pdu_rx_info_p->count;

	if(rcvd_count < pdcp_entity->RX_NEXT)
	{
		return FALSE;
	}

	if(cursor_p == NULL)
	{
		list2_add_head(tb_pP, &pdcp_entity->reception_buffer);
		return TRUE;
	}

	while(cursor_p)
	{
		cursor_count = ((pdcp_pdu_info_t*)cursor_p)->count;

		if(cursor_count == rcvd_count)
		{
			return FALSE;
		}
		else if(cursor_count > rcvd_count)
		{
			list2_insert_before_element(tb_pP, cursor_p, &pdcp_entity->reception_buffer);
		}

		cursor_p = cursor_p->next;
	}

	list2_add_tail(tb_pP, pdcp_entity->reception_buffer.tail);

	return TRUE;
}
