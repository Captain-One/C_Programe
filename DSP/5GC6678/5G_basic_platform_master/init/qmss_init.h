/*
 * qmss_init.h
 *
 *  Created on: 2019年4月24日
 *      Author: lin
 */

#ifndef INIT_QMSS_INIT_H_
#define INIT_QMSS_INIT_H_

#include <xdc/std.h>
#include "../common/common.h"

//#define NUM_MONOLITHIC_DESC     32
//#define SIZE_MONOLITHIC_DESC    64

#define FREE_DSC_QUEUE          500
#define TX_QUEUE                800
#define RX_QUEUE                704

#define NUM_HOST_DESC           128
#define SIZE_HOST_DESC          64

#define TX_CHANNEL              0

#define SIZE_RX_DATA_BUFFER     128
#define NUM_RX_DATA_BUFFER      NUM_HOST_DESC

#define CORE_ID                 0
#define MASTER_INIT_DONE        (1 << MASTER_CORE)
#define ALL_CORE_INIT_DONE      0x03   //8 core all init done


typedef struct Ps_st{
  uint8_t   src_core;  //源核号；
  uint8_t   des_core;  //目的核号；
  uint16_t  reserved;  //保留；
  uint32_t  pktLen;  //包总长度；
  uint32_t  DescNum;   //发送该数据包需要的描述符数量
  uint32_t  DecNo; //DescNum 大于1时有效，被拆分的数据包所属的描述符的编号，接收侧根据此编号按照顺序恢复数据包
  uint64_t  totalPktNum; //对某个核总发送的数据包的数值，没调用一次发包函数，且发送成功后该值加1；
}Ps_Info;


Int cppiInit(Void);
Int ipcInit(Void);

#endif /* INIT_QMSS_INIT_H_ */
