/*
 * pdcp_rx_list.h
 *
 *  Created on: 2019年6月20日
 *      Author: wanxs
 */

#ifndef LAYER2_PDCP_NR15_5_0_PDCP_RX_LIST_H_
#define LAYER2_PDCP_NR15_5_0_PDCP_RX_LIST_H_



boolean_t pdcp_rx_list_check_duplicate_insert_sdu(
					const protocol_ctxt_t* const  ctxt_pP,
					pdcp_t* const pdcp_entity,
					mem_block_t* tb_pP);



#endif /* LAYER2_PDCP_NR15_5_0_PDCP_RX_LIST_H_ */
