#    ifndef __RLC_AM_TEST_H__
#        define __RLC_AM_TEST_H__
rlc_am_entity_t       g_am_tx;
rlc_am_entity_t       g_am_rx;

void rlc_am_v9_3_0_test_windows();
void rlc_am_v9_3_0_test_read_write_bit_field();
void rlc_am_v9_3_0_test_data_conf(module_id_t module_idP, rb_id_t rb_idP, mui_t muiP, rlc_tx_status_t statusP);
void rlc_am_v9_3_0_test_send_sdu(rlc_am_entity_t *am_txP, int sdu_indexP);
void rlc_am_v9_3_0_test_exchange_pdus(rlc_am_entity_t *am_txP,rlc_am_entity_t *am_RxP,
                      uint16_t bytes_txP,uint16_t bytes_rxP);
void rlc_am_v9_3_0_test_mac_rlc_loop (struct mac_data_ind *data_indP,  struct mac_data_req *data_requestP, int* drop_countP, int *tx_packetsP, int* dropped_tx_packetsP);
void rlc_am_v9_3_0_test_data_ind (module_id_t module_idP, rb_id_t rb_idP, sdu_size_t sizeP,
                      mem_block_t *sduP);
void rlc_am_v9_3_0_test_tx_rx();
void rlc_am_v9_3_0_test_print_trace (void);
void rlc_am_v9_3_0_test();
#    endif
