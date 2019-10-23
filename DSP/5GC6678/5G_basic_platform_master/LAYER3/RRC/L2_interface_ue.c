#include "rrc_defs.h"
#include "rrc_proto.h"
#include "assertions.h"

typedef uint32_t channel_t;

int8_t nr_mac_rrc_data_ind_ue(
    const module_id_t     module_id,
    const int             CC_id,
    const uint8_t         gNB_index,
    const channel_t       channel,
    const uint8_t*        pduP,
    const sdu_size_t      pdu_len)
{
    switch(channel){
        case NR_BCCH_BCH:
//            AssertFatal( nr_rrc_ue_decode_NR_BCCH_BCH_Message( module_id, gNB_index, (uint8_t*)pduP, pdu_len) == 0, "UE decode BCCH-BCH error!\n");
            break;
        default:
            break;
    }


    return(0);

}
