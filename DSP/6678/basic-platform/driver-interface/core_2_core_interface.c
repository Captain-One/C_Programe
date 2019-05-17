/*
 * core_2_core_interface.c
 *
 *  Created on: 2019年5月8日
 *      Author: pu
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <qmss_init.h>

#include <stdlib.h>

//CPPI & QMSS
#include <ti/drv/QMSS/QMSS_drv.h>
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>
#include <ti/drv/cppi/cppi_osal.h>

extern Int core_id;

extern Qmss_QueueHnd freeQueHnd;
extern Qmss_QueueHnd rxQueHnd[CORE_NUM - 1];
extern Qmss_QueueHnd txQueHnd;

extern Ps_Info  ps_info;

#pragma DATA_SECTION(totalSendPktNum, ".L2RAM")
uint64_t totalSendPktNum[7] = {0};
#pragma DATA_SECTION(totalGetPktNum, ".L2RAM")
uint64_t totalGetPktNum[7] = {0};


Int sendDataToCoreN(Int core_num, Void *buf, uint32_t len)
{
    Cppi_DescTag  Tag = {0};
    Cppi_Desc   * sopDescPtr;

    uint32_t      rePktCount;
    uint32_t      freeDescCount;
    uint32_t      reLen;
    uint32_t      sendLen;

    uint8_t     * pbuf = buf;

    Tag.srcTagLo = core_num << 3 + core_id;  //rx flow id

    if((len % SIZE_RX_DATA_BUFFER) == 0){
        rePktCount = len / SIZE_RX_DATA_BUFFER;
    }else{
        rePktCount = len / SIZE_RX_DATA_BUFFER + 1;
    }

    freeDescCount = Qmss_getQueueEntryCount (freeQueHnd);
    if(freeDescCount < rePktCount){
       System_printf("Not enough Dec is freeQue %d\n", freeQueHnd);
       return -1;
    }

    ps_info.des_core = core_num;
    ps_info.pktLen = len;
    ps_info.DecNo = 0;
    ps_info.DescNum = rePktCount;
    ps_info.totalPktNum = totalSendPktNum[core_num] + 1;
    reLen = len;

    while(rePktCount){
        sopDescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
        if(sopDescPtr == NULL){
            System_printf("Qmss_queuePop error\n");
            totalSendPktNum[core_num] -= 1;
            return -2;
        }
        sopDescPtr = (Cppi_Desc *) QMSS_DESC_PTR (sopDescPtr);

        if(reLen > SIZE_RX_DATA_BUFFER){
            sendLen = SIZE_RX_DATA_BUFFER;
        }else{
            sendLen = reLen;
        }

        ps_info.DecNo = ps_info.DecNo + 1;

        Cppi_setTag(Cppi_DescType_HOST, sopDescPtr, &Tag);
        Cppi_setPSData (Cppi_DescType_HOST, sopDescPtr, (uint8_t *) &ps_info, sizeof(Ps_Info));
        Cppi_setData (Cppi_DescType_HOST, sopDescPtr, (uint8_t *)((uint32_t)(pbuf)), sendLen);
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, sopDescPtr, (uint8_t *)((uint32_t)(pbuf)), sendLen);
        Cppi_setPacketLen (Cppi_DescType_HOST, sopDescPtr, sendLen);
        Qmss_queuePushDescSize (txQueHnd, sopDescPtr, SIZE_HOST_DESC);

        pbuf += sendLen;
        reLen -= sendLen;
        rePktCount--;
    }
    return 0;
}


Int getDataFromCoreN(Int core_num, Void *buf, uint32_t *len, Int isBlock)
{
        uint32_t rx_count;
        uint32_t rxLen;
        uint32_t totalLen = 0;
        uint8_t  *data;
        Ps_Info  *ps_data;
        uint32_t ps_len;
        uint8_t  *pBuf = buf;

        Cppi_Desc *rxPkt;

        uint32_t descCount;
        uint32_t pktLen;

        if(buf == NULL){
            return -2;
        }

        if(core_num == core_id){
            return -3;
        }

        rx_count = Qmss_getQueueEntryCount (rxQueHnd[core_num]);
        if(rx_count == 0){
            System_printf("rxQueHnd no data\n");
            return 1;
        }

        rxPkt = (Cppi_Desc *) Qmss_queuePop (rxQueHnd[core_num]);
        if(rxPkt == NULL){
            System_printf("Qmss_queuePop rxPkt is NULL !!!!!\n");
            return -1;
        }

        rxPkt = (Cppi_Desc *)QMSS_DESC_PTR (rxPkt);
        Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, rxPkt, (uint8_t **)(&ps_data), &ps_len);
        descCount = ps_data->DescNum;
        pktLen = ps_data->pktLen;
        if(descCount > 1){
            rx_count = Qmss_getQueueEntryCount (rxQueHnd[core_num]);
            if(rx_count < descCount - 1){
               if(isBlock){
                   while(rx_count < descCount - 1)
                   {
                       rx_count = Qmss_getQueueEntryCount (rxQueHnd[core_num]);
                   }
               }else{
                   //处理push回原处 //buffer?
                   Qmss_queuePush(rxQueHnd[core_num], rxPkt, SIZE_RX_DATA_BUFFER, SIZE_HOST_DESC, Qmss_Location_HEAD);
                   return 2;
               }
            }
        }else{

        }

        Cppi_getData (Cppi_DescType_HOST, rxPkt, &data, &rxLen);
        memcpy(pBuf, data, rxLen);
        //cache
        //Cppi_setPSData (Cppi_DescType_HOST, rxPkt, (uint8_t *) &ps_info, sizeof(Ps_Info));
        Cppi_setData (Cppi_DescType_HOST, rxPkt, (uint8_t *)((uint32_t)(data)), SIZE_RX_DATA_BUFFER);
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, rxPkt, (uint8_t *)((uint32_t)(data)), SIZE_RX_DATA_BUFFER);
        Cppi_setPacketLen (Cppi_DescType_HOST, rxPkt, SIZE_RX_DATA_BUFFER);
        Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);

        pBuf += rxLen;
        totalLen += rxLen;
        descCount --;
        while(descCount){
            rxPkt = (Cppi_Desc *) Qmss_queuePop (rxQueHnd[core_num]);
            if(rxPkt == NULL){
                System_printf("Qmss_queuePop rxPkt is NULL !!!!!\n");
                return -1;
            }

            rxPkt = (Cppi_Desc *)QMSS_DESC_PTR (rxPkt);
            Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, rxPkt, (uint8_t **)(&ps_data), &ps_len);
            Cppi_getData (Cppi_DescType_HOST, rxPkt, &data, &rxLen);
            memcpy(pBuf, data, rxLen);
            //cache
            //Cppi_setPSData (Cppi_DescType_HOST, rxPkt, (uint8_t *) &ps_info, sizeof(Ps_Info));
            Cppi_setData (Cppi_DescType_HOST, rxPkt, (uint8_t *)((uint32_t)(data)), SIZE_RX_DATA_BUFFER);
            Cppi_setOriginalBufInfo (Cppi_DescType_HOST, rxPkt, (uint8_t *)((uint32_t)(data)), SIZE_RX_DATA_BUFFER);
            Cppi_setPacketLen (Cppi_DescType_HOST, rxPkt, SIZE_RX_DATA_BUFFER);
            Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
            totalLen += rxLen;
            pBuf += rxLen;
            descCount--;
        }
        if(totalLen != pktLen){
            return -5;
        }
        *len = totalLen;
        return 0;
}
