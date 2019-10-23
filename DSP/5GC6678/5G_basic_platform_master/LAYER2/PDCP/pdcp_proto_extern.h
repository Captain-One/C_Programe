#ifndef __PDCP_PROTO_EXTERN_H__
#    define __PDCP_PROTO_EXTERN_H__

//#    include "pdcp_entity.h"
#    include "mem_block.h"



extern boolean_t     pdcp_data_ind(module_id_t module_idP,
										rb_id_t rab_idP,
										sdu_size_t data_sizeP,
										mem_block_t * sduP,
										uint8_t is_data_plane);

extern boolean_t     pdcp_data_req(module_id_t module_id,
										uint32_t frame,
										uint8_t eNB_flag,
										rb_id_t rab_id,
										uint32_t muiP,
										uint32_t confirmP,
										sdu_size_t sdu_buffer_size,
										unsigned char* sdu_buffer,
										uint8_t is_data_pdu
#if (RRC_VERSION < MAKE_VERSION(15, 0, 0))
									   ,const uint32_t * const sourceL2Id
									   ,const uint32_t * const destinationL2Id
#endif
																	   );
//extern BOOL     pdcp_data_req (struct pdcp_entity *pdcpP, mem_block * sduP);
extern void     send_pdcp_control_primitive (struct pdcp_entity *pdcpP, mem_block_t * cprimitiveP);
extern void     control_pdcp (struct pdcp_entity *pdcpP);
extern void     pdcp_process_input_sdus_am (struct pdcp_entity *pdcpP);
extern void     pdcp_process_output_sdus (struct pdcp_entity *pdcpP, mem_block_t * sduP, uint8_t rb_idP);
extern void     pdcp_process_input_sdus_um (struct pdcp_entity *pdcpP);
extern void     pdcp_process_input_sdus_tr (struct pdcp_entity *pdcpP);
extern void     init_pdcp (struct pdcp_entity *pdcpP, struct rb_dispatcher *rbP, uint8_t rb_idP);
extern void    *pdcp_tx (void *argP);

extern void pdcp_pc5_socket_init(void);

#endif
