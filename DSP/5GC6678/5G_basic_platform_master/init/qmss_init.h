/*
 * qmss_init.h
 *
 *  Created on: 2019��4��24��
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
  uint8_t   src_core;  //Դ�˺ţ�
  uint8_t   des_core;  //Ŀ�ĺ˺ţ�
  uint16_t  reserved;  //������
  uint32_t  pktLen;  //���ܳ��ȣ�
  uint32_t  DescNum;   //���͸����ݰ���Ҫ������������
  uint32_t  DecNo; //DescNum ����1ʱ��Ч������ֵ����ݰ��������������ı�ţ����ղ���ݴ˱�Ű���˳��ָ����ݰ�
  uint64_t  totalPktNum; //��ĳ�����ܷ��͵����ݰ�����ֵ��û����һ�η����������ҷ��ͳɹ����ֵ��1��
}Ps_Info;


Int cppiInit(Void);
Int ipcInit(Void);

#endif /* INIT_QMSS_INIT_H_ */
