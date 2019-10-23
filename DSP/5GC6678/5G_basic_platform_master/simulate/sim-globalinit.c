#include "mem_block.h"
#include "list.h"
#include "hashtable.h"
#include "MAC/mac.h"
#include "MAC/mac_defs.h"
#include "MAC/mac_proto.h"
#include "RLC/rlc.h"
#include "PDCP/pdcp.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int main(void)
{
	nr_l2_init_ue(1, NULL, 1, 1);
	rrc_top_init_ue_nr();
}
