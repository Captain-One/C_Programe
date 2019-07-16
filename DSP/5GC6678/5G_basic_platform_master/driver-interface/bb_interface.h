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


#define SRIO_FPGA0_DATA_BUF_ADDR                  0x80000800//0x10878400//
#define SRIO_FPGA0_DATA_BUF_END_ADDR              0x814007FF//0x1087ABFF//
#define SRIO_FPGA0_DATA_BUF_LEN                   0x01400000//0x00002800//  //20MB
#define SRIO_FPGA0_DATA_BUF_COUNT                 SRIO_FPGA0_DATA_BUF_LEN/DATA_ALIGN

#define SRIO_FPGA1_DATA_BUF_ADDR                  0x81400800
#define SRIO_FPGA1_DATA_BUF_END_ADDR              0x828007FF
#define SRIO_FPGA1_DATA_BUF_LEN                   0x01400000  //20MB
#define SRIO_FPGA1_DATA_BUF_COUNT                 SRIO_FPGA1_DATA_BUF_LEN/DATA_ALIGN


#define DSP_SRIO_FPGA0_CFG_REG_BASE_ADDR          0x80000000//0x10878000
#define DSP_SRIO_FPGA0_CFG_REG_BASE_END_ADDR      0x800003FF//0x108783FF
#define DSP_SRIO_FPGA0_CFG_REG_SPACE_LEN          0x00000400  //1KB

#define DSP_SRIO_FPGA1_CFG_REG_BASE_ADDR          0x80000400
#define DSP_SRIO_FPGA1_CFG_REG_BASE_END_ADDR      0x800007FF
#define DSP_SRIO_FPGA1_CFG_REG_SPACE_LEN          0x00000400  //1KB


typedef struct _
{
    uint64_t dspcfgstartaddr;
    uint64_t dspcfgendaddr;
    uint64_t dspdatastartaddr;
    uint64_t dspdataendaddr;
    uint64_t dspreadindexaddr;
}srioConfigParameter;


Int writeBbReg(Int bbfpgaNo, Void *buf);
Int sendDataToBb(Int bbfpgaNo, Void *buf, Int len);
Int getBbData(Int bbfpgaNo, Void *buf, uint32_t *len);
Int configSrioParameterToFPGA(Int bbfpgaNo);
Int writeReadIndex(Int bbfpgaNo, uint32_t readIndex);

#endif /* DRIVER_INTERFACE_BB_INTERFACE_H_ */
