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

#define CORE_NUM                2
#define MASTER_CORE             0

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

#define CORE0_TXCH_NUM           800
#define CORE1_TXCH_NUM           800
#define CORE2_TXCH_NUM           800
#define CORE3_TXCH_NUM           800
#define CORE4_TXCH_NUM           800
#define CORE5_TXCH_NUM           800
#define CORE6_TXCH_NUM           800
#define CORE0_TXCH_NUM           800



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

//定义板卡信息联合数据类型
typedef union {
    struct {
        uint16_t slotid:5;      //源单板槽位号
        uint16_t src_bdtype:3;  //源单板类型
        uint16_t dst_rfbn:4;    //目的基带板槽位号，在dst_type ==0 时有效
        uint16_t dst_bdtype:3;  //目的单板类型
        uint16_t single:1;      //是否只包含一个子包
    } bdinfo_s;
    uint16_t bdinfo_u16;
} BDinfo_t;

//定义父包头结构
typedef struct FpkH_s {
    uint16_t mark;  //父包头标志，大端模式，固定为0xDCBA
    uint16_t flen;  //父包总长度
    BDinfo_t bdinfo;    //板间信息
    CARRIER_t carrier_info; //FIXME 载波信息，此字段必须经过大小端转换处理
} FpkH_t;



#endif /* COMMON_COMMON_H_ */
