/*
 * qmss_init.h
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: lin
 */

#ifndef INIT_QMSS_INIT_H_
#define INIT_QMSS_INIT_H_

#include <xdc/std.h>

#define NUM_HOST_DESC           32
#define NUM_MONOLITHIC_DESC     32

#define SIZE_HOST_DESC          64
#define SIZE_MONOLITHIC_DESC    64

#define SIZE_DATA_BUFFER        128
#define NUM_DATA_BUFFER         128

static Void cbFxn(UInt16 procId, UInt16 lineId, UInt32 eventId, UArg arg, UInt32 payload);
Int cppiInit(Void);

#endif /* INIT_QMSS_INIT_H_ */
