/*
 * qmss_init.h
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: lin
 */

#ifndef INIT_QMSS_INIT_H_
#define INIT_QMSS_INIT_H_

#include <xdc/std.h>
#include "../common/common.h"

#define NUM_HOST_DESC           32
#define NUM_MONOLITHIC_DESC     32

#define SIZE_HOST_DESC          64
#define SIZE_MONOLITHIC_DESC    64

#define SIZE_DATA_BUFFER        128
#define NUM_DATA_BUFFER         128

#define CORE_NUM                2
#define MASTER_CORE             0
#define CORE_ID                 1
#define MASTER_INIT_DONE        (1 << MASTER_CORE)
#define INIT_DONE               (1 << CORE_ID)
#define ALL_CORE_INIT_DONE      0x03   //8 core all init done

Int cppiInit(Void);
Int ipcInit(Void);

#endif /* INIT_QMSS_INIT_H_ */
