/*
 * common.h
 *
 *  Created on: 2019Äê5ÔÂ5ÈÕ
 *      Author: pu
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <xdc/std.h>
#include <ti/ipc/MessageQ.h>

#define CORE_NUM                2
#define MASTER_CORE             0

#define MASTER_MSGQ_NAME         "masterMsgQ";

typedef struct  notify_msg{
    MessageQ_MsgHeader  header;
    Int     initDone;
}Notifye_Msg;

#endif /* COMMON_COMMON_H_ */
