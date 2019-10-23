#define RLC_UM_MODULE 1
#define RLC_UM_SEGMENT_C 1
//-----------------------------------------------------------------------------
#include "platform_types.h"
#include "platform_constants.h"
//-----------------------------------------------------------------------------
#include <assert.h>
#include "assertions.h"
#include "list.h"
#include "rlc_um.h"
#include "rlc_primitives.h"


//-----------------------------------------------------------------------------
void rlc_um_segment(const protocol_ctxt_t* const ctxt_pP, rlc_um_entity_t *rlc_pP)
{
	list_t              pdus;
	signed int          pdu_remaining_size;
	signed int          test_pdu_remaining_size;

	int                 nb_bytes_to_transmit = rlc_pP->nb_bytes_requested_by_mac;
	rlc_um_pdu_sn_10_t *pdu_p;
	struct mac_tb_req  *pdu_tb_req_p;
	mem_block_t        *pdu_mem_p;
	char               *data;
	char               *data_sdu_p;
	rlc_um_e_li_t      *e_li_p;
	struct rlc_um_tx_sdu_management *sdu_mngt_p;
	unsigned int       li_length_in_bytes;
	unsigned int       test_li_length_in_bytes;
	unsigned int       test_remaining_size_to_substract;
	unsigned int       test_remaining_num_li_to_substract;
	unsigned int       continue_fill_pdu_with_sdu;
	unsigned int       num_fill_sdu;
	unsigned int       test_num_li;
	unsigned int       fill_num_li;
	mem_block_t        *sdu_in_buffer = NULL;
	unsigned int       data_pdu_size;

	unsigned int       fi_first_byte_pdu_is_first_byte_sdu;
	unsigned int       fi_last_byte_pdu_is_last_byte_sdu;
	unsigned int       fi;
	unsigned int       max_li_overhead;
	int32_t headerL = 0;

	if (nb_bytes_to_transmit < ((rlc_pP->tx_sn_length == 12) ? 4 : 3)) {
		return;
	}

	list_init (&pdus, NULL);    // param string identifying the list is NULL
	pdu_mem_p = NULL;

	// not fine locking
//	RLC_UM_MUTEX_LOCK(&rlc_pP->lock_input_sdus, ctxt_pP, rlc_pP);

	while((sdu_in_buffer = list2_get_head(&rlc_pP->input_sdus)) && nb_bytes_to_transmit > 0) {
		sdu_mngt_p = ((struct rlc_um_tx_sdu_management *) (sdu_in_buffer->data));

		headerL += 1; // 只存在SI参数，完整数据包

		if((sdu_mngt_p->sdu_size != sdu_mngt_p->sdu_remaining_size) ||
				((sdu_mngt_p->sdu_remaining_size + 1) > nb_bytes_to_transmit)) {
			headerL += 2; // SO部分长度

			headerL += (rlc_pP->tx_sn_length == 12) ? 1 : 0; // SN部分长度
		}

		if(nb_bytes_to_transmit < headerL) {
			return;
		}

		if(nb_bytes_to_transmit >= sdu_mngt_p->sdu_remaining_size + headerL) {
			data_pdu_size = sdu_mngt_p->sdu_remaining_size + headerL;
		} else {
			data_pdu_size = nb_bytes_to_transmit;
		}

		if (!(pdu_mem_p = get_free_mem_block (data_pdu_size + sizeof(struct mac_tb_req), __func__))) {
//			RLC_UM_MUTEX_UNLOCK(&rlc_pP->lock_input_sdus);
			return;
		}

		memset(pdu_mem_p->data, 0, sizeof(struct mac_tb_req));

//		包含一个完整的SDU，不存在SN及SO字段
		if(headerL == 1) {
			memcpy(pdu_mem_p->data + sizeof(struct mac_tb_req) + headerL, sdu_mngt_p->first_byte, sdu_mngt_p->sdu_size);

//			设置SI字段为0
			*(pdu_mem_p->data + sizeof(struct mac_tb_req)) = 0;

//			 计算分片长度及生于数据长度
			sdu_mngt_p->sdu_segmented_size += data_pdu_size - headerL;
			sdu_mngt_p->sdu_remaining_size -= data_pdu_size - headerL;
		} else {// 数据需要分段，首先判断分段位置（头部，中间段或者尾段）
//			设置SI字段值
			if(sdu_mngt_p->sdu_segmented_size == 0) {// 当前SDU第一个分段，头部
				if(rlc_pP->tx_sn_length == 12) {
					((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->si = RLC_SI_DATA_FIELD_CONTAINS_THE_FIRST_SEGMENT_OF_AN_RLC_SDU;
				} else {
					((rlc_um_pdu_so_6_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->si = RLC_SI_DATA_FIELD_CONTAINS_THE_FIRST_SEGMENT_OF_AN_RLC_SDU;
				}
			} else if(data_pdu_size == (sdu_mngt_p->sdu_remaining_size + headerL)) {// 当前SDU最后一个分段，尾部
				if(rlc_pP->tx_sn_length == 12) {
					((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->si = RLC_SI_DATA_FIELD_CONTAINS_THE_LAST_SEGMENT_OF_AN_RLC_SDU;
				} else {
					((rlc_um_pdu_so_6_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->si = RLC_SI_DATA_FIELD_CONTAINS_THE_LAST_SEGMENT_OF_AN_RLC_SDU;
				}
			}
			else {// 中间分段
				if(rlc_pP->tx_sn_length == 12) {
					((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->si = RLC_SI_DATA_FIELD_CONTAINS_NEITHER_THE_FIRST_NOR_LAST_SEGMENT_OF_AN_RLC_SDU;
				} else {
					((rlc_um_pdu_so_6_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->si = RLC_SI_DATA_FIELD_CONTAINS_NEITHER_THE_FIRST_NOR_LAST_SEGMENT_OF_AN_RLC_SDU;
				}
			}

//			设置SN及SO字段
			if(rlc_pP->tx_sn_length == 12) {
				((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->snh = (rlc_pP->TX_Next >> 8) & 0x000F;
				((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->snl = (uint8_t)(rlc_pP->TX_Next & 0x00FF);

				((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->soh = (sdu_mngt_p->sdu_segmented_size >> 8) & 0x00FF;
				((rlc_um_pdu_so_12_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->sol = sdu_mngt_p->sdu_segmented_size & 0x00FF;
			} else {
				((rlc_um_pdu_so_6_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->sn = rlc_pP->TX_Next & 0x3F;

				((rlc_um_pdu_so_6_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->soh = (sdu_mngt_p->sdu_segmented_size >> 8) & 0x00FF;
				((rlc_um_pdu_so_6_t*)(pdu_mem_p->data + sizeof(struct mac_tb_req)))->sol = sdu_mngt_p->sdu_segmented_size & 0x00FF;
			}

//			拷贝数据
			memcpy(pdu_mem_p->data + sizeof(struct mac_tb_req) + headerL, sdu_mngt_p->first_byte + sdu_mngt_p->sdu_segmented_size, data_pdu_size - headerL);

//			计算分片长度及生于数据长度
			sdu_mngt_p->sdu_segmented_size += data_pdu_size - headerL;
			sdu_mngt_p->sdu_remaining_size -= data_pdu_size - headerL;
		}

//		插入数据至链表尾部
		list2_add_tail(pdu_mem_p, &rlc_pP->pdus_to_mac_layer);

//		判断当前SDU发送完成
		if(sdu_mngt_p->sdu_remaining_size == 0) {
//			移除头部节点
			list2_remove_head(&rlc_pP->input_sdus);

//			计算下一个分片SDU的SN值
			if(headerL > 1) {
				rlc_pP->TX_Next = (rlc_pP->TX_Next + 1) % rlc_pP->tx_sn_modulo;
			}
		}

		nb_bytes_to_transmit -= data_pdu_size;
		rlc_pP->nb_bytes_requested_by_mac -= data_pdu_size;
	}

//	RLC_UM_MUTEX_UNLOCK(&rlc_pP->lock_input_sdus);
}
