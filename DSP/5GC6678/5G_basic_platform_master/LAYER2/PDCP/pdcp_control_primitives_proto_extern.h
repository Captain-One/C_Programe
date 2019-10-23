#ifndef PDCP_CONTROL_PRIMITIVES_PROTO_EXTERN_H
#    define PDCP_CONTROL_PRIMITIVES_PROTO_EXTERN_H
#    include "pdcp.h"
void            rrc_configure_pdcp (struct pdcp_entity *pdcpP, void *rlcP, uint8_t rlc_sap_typeP, uint8_t header_compression_typeP);
#endif
