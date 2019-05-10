/*
 * bb-interface.h
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
 *      Author: pu
 */

#ifndef DRIVER_INTERFACE_BB_INTERFACE_H_
#define DRIVER_INTERFACE_BB_INTERFACE_H_

#include <xdc/std.h>

#define BB_FPGA_NO_0                        0
#define BB_FPGA_NO_1                        1


#define DATA_ALIGN                          0x100  //256

#define FPGA_CFG_REG_BASE_ADDR              0x00000000  //0
#define FPGA_DATA_BASE_ADDR                 0x00000400  //1024

#define FPGA_DSP_CFG_ADDR_OFFSET            0
#define FPGA_DSP_CFG_LEN_OFFSET             8
#define FPGA_DSP_CFG_SPACE_LEN_OFFSET       16
#define FPGA_DSP_DATA_ADDR_OFFSET           24
#define FPGA_DSP_DATA_BUF_LEN_OFFSET        32
#define DSP_READ_INDEX                      40


#define SRIO_DATA_BUF_ADDR                  0x80100000
#define SRIO__DATA_BUF_LEN                  0x05000000  //80MB

#define DSP_SRIO_CFG_REG_BASE_ADDR          0x80000000
#define DSP_SRIO_CFG_REG_SPACE_LEN          0x00100000  //1MB

#define FPGA_WRITE_INDEX_OFFSET             0

Int writeBbReg(Int bbfpgaNo, Void *buf);
Int sendDataToBb(Int bbfpgaNo, Void *buf, Int len);
Int getBbData(Int bbfpgaNo, Void *buf, Int len);

#endif /* DRIVER_INTERFACE_BB_INTERFACE_H_ */
