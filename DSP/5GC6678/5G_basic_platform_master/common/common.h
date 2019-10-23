/*
 * common.h
 *
 *  Created on: 2019年5月5日
 *      Author: pu
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <xdc/std.h>
#include <ti/ipc/MessageQ.h>

#define swap16(s) ((((s) & 0xff) << 8) | (((s) >> 8) & 0xff))
#define swap32(l) (((l) >> 24) | \
          (((l) & 0x00ff0000) >> 8)  | \
          (((l) & 0x0000ff00) << 8)  | \
          ((l) << 24))


#define swp8(data)      (((data) << 4 )| ((data) >> 4))
#define swp16(data)     ((((data) << 8) & 0xFF00) | (((data) >> 8) & 0x00FF))
#define swp32(data)     ((swp16(data) << 16) | swp16((data) >> 16))
#define swp64(data)     ((swp32(data) << 32) | swp32((data) >> 32))

#define CORE_NUM                8
#define MASTER_CORE             0

#define RUN_MULTI_CORE          0

#define MASTER_MSGQ_NAME         "masterMsgQ";

#define CORE0_TXQ_NUM           800
#define CORE1_TXQ_NUM           800
#define CORE2_TXQ_NUM           800
#define CORE3_TXQ_NUM           800
#define CORE4_TXQ_NUM           800
#define CORE5_TXQ_NUM           800
#define CORE6_TXQ_NUM           800
#define CORE0_TXQ_NUM           800

#define CORE0_RXQ_NUM           800
#define CORE1_RXQ_NUM           800
#define CORE2_RXQ_NUM           800
#define CORE3_RXQ_NUM           800
#define CORE4_RXQ_NUM           800
#define CORE5_RXQ_NUM           800
#define CORE6_RXQ_NUM           800
#define CORE7_RXQ_NUM           800

#define CORE0_RXCH_NUM          800
#define CORE1_RXCH_NUM          800
#define CORE2_RXCH_NUM          800
#define CORE3_RXCH_NUM          800
#define CORE4_RXCH_NUM          800
#define CORE5_RXCH_NUM          800
#define CORE6_RXCH_NUM          800
#define CORE7_RXCH_NUM          800

#define CORE0_TXCH_NUM          800
#define CORE1_TXCH_NUM          800
#define CORE2_TXCH_NUM          800
#define CORE3_TXCH_NUM          800
#define CORE4_TXCH_NUM          800
#define CORE5_TXCH_NUM          800
#define CORE6_TXCH_NUM          800
#define CORE0_TXCH_NUM          800


#define DSP_LED_0               15


typedef struct  notify_msg{
    MessageQ_MsgHeader  header;
    Int     initDone;
}Notifye_Msg;

//定义载波信息联合数据结构
typedef union carrier_u {
    struct {
        uint16_t physCellId9:9;
        uint16_t DIR:1;
        uint16_t en:1;
        uint16_t Res:1;
        uint16_t RFBN:4;
    } carrier;
    struct {
        uint16_t PhysCellID:8;
        uint16_t PhyCellIDmsb:1;
        uint16_t DIR:1;
        uint16_t en:1;
        uint16_t Res:1;
        uint16_t RFBN:4;
    } carrier_2pid;
    uint16_t carrier_u16;
} CARRIER_t;

/*****************SRTUCT******************/
#pragma pack(1)

typedef struct packet_header_{
    uint16_t    mark;   //mark 0xDCBA
    uint16_t    len;    //packet len
    uint16_t    type;   //packet type
    uint8_t     src;    //packet source addr 0:PL, 1:HL
    uint8_t     dst;    //packet destination  addr 0:PL, 1:HL
    uint64_t    res;    //reserved
}packetHeader_t;

typedef struct packet_{
    packetHeader_t   header;   //packet header
    uint8_t          payload[0];  //payload
}packet_t;

#pragma pack()

uint32_t l2_global_address (uint32_t addr);

#endif /* COMMON_COMMON_H_ */

#define  USE_UART_PRINT

#ifdef  USE_UART_PRINT
#define MYPRINTF     UART_mutex_printf
#else
#define MYPRINTF     System_printf
#endif

#define SRIO_DEBUG_FPGA1

//#define SRIO_RECEIVE_PERFORMANCE_TEST
//#define SRIO_TRANSMIT_PERFORMANCE_TEST
//#define SRIO_RECEIVE_AND_TRANS_PERFORMANCE_TEST
#define SRIO_PROTOCOL_TEST

#ifdef SRIO_RECEIVE_AND_TRANS_PERFORMANCE_TEST
#define SRIO_RECEIVE_PERFORMANCE_TEST
#define SRIO_TRANSMIT_PERFORMANCE_TEST
#endif

#if defined(SRIO_RECEIVE_PERFORMANCE_TEST) || defined(SRIO_TRANSMIT_PERFORMANCE_TEST)
#define SRIO_PERFORMANCE_TEST
#endif

