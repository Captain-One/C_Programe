/*
 * bb-interface.h
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
 *      Author: pu
 */

#ifndef DRIVER_INTERFACE_BB_INTERFACE_H_
#define DRIVER_INTERFACE_BB_INTERFACE_H_

#include <xdc/std.h>

#define BB_FPGA_NO_0            0
#define BB_FPGA_NO_1            1

typedef struct bbSrioInfo_{
    uint8_t     srioPort;
    uint16_t    dstID;
};


#endif /* DRIVER_INTERFACE_BB_INTERFACE_H_ */
