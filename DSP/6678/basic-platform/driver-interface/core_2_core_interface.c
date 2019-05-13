/*
 * core_2_core_interface.c
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
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


extern Qmss_QueueHnd freeQueHnd;
extern Qmss_QueueHnd rxQueHnd;
extern Qmss_QueueHnd txQueHnd;

Int sendDataToCoreN(Int core_num, Void *buf, uint32_t len)
{
    Cppi_DescTag  Tag;
    Cppi_Desc   ** mopDescPtrArray;
    Cppi_Desc   * sopDescPtr;

    uint32_t      rePktCount;
    uint32_t      firstPktLen;
    uint32_t      endPktLen;

    uint8_t     * pbuf = buf;

    Tag.srcTagLo = core_num;  //rx flow id

    if((len % SIZE_RX_DATA_BUFFER) == 0){
        rePktCount = len / SIZE_RX_DATA_BUFFER;
    }else{
        rePktCount = len / SIZE_RX_DATA_BUFFER + 1;
    }

    sopDescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
    if(sopDescPtr == NULL){
        System_printf("rxQueHnd no data\n");
        return 1;
    }
    Cppi_setTag(Cppi_DescType_HOST, sopDescPtr, &Tag);

    if(len <= SIZE_RX_DATA_BUFFER){
        Cppi_setData (Cppi_DescType_HOST, sopDescPtr, (uint8_t *)((uint32_t)(pbuf)), len);
        Cppi_setPacketLen (Cppi_DescType_HOST, sopDescPtr, len);
        goto push;
    }else{

    }

    firstPktLen = SIZE_RX_DATA_BUFFER;
    endPktLen = len - (rePktCount - 1) * SIZE_RX_DATA_BUFFER;

    Cppi_setData (Cppi_DescType_HOST, sopDescPtr, (uint8_t *)((uint32_t)(pbuf)), firstPktLen);
    Cppi_setPacketLen (Cppi_DescType_HOST, sopDescPtr, firstPktLen);

    rePktCount --;
    pbuf += firstPktLen;

    mopDescPtrArray = (Cppi_Desc **)malloc(sizeof(Cppi_Desc *) * rePktCount);
    if(mopDescPtrArray == NULL){
        System_printf("melloc Cppi_Desc ** error\n");
        return -1;
    }

    *mopDescPtrArray = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
    if(*mopDescPtrArray == NULL){
        System_printf("rxQueHnd no data\n");
        return 1;
    }
    Cppi_linkNextBD(Cppi_DescType_HOST, sopDescPtr, *mopDescPtrArray);

    while(rePktCount > 1){
        Cppi_setData (Cppi_DescType_HOST, *mopDescPtrArray, (uint8_t *)((uint32_t)(pbuf)), SIZE_RX_DATA_BUFFER);
        Cppi_setPacketLen (Cppi_DescType_HOST, *mopDescPtrArray, SIZE_RX_DATA_BUFFER);

        mopDescPtrArray ++;
        pbuf += SIZE_RX_DATA_BUFFER;
        rePktCount --;
        *mopDescPtrArray = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
        if(*mopDescPtrArray == NULL){
            System_printf("rxQueHnd no data\n");
            return 1;
        }
        Cppi_linkNextBD(Cppi_DescType_HOST, *(mopDescPtrArray--), *mopDescPtrArray);
    }

    Cppi_setData (Cppi_DescType_HOST, *mopDescPtrArray, (uint8_t *)((uint32_t)(pbuf)), endPktLen);
    Cppi_setPacketLen (Cppi_DescType_HOST, *mopDescPtrArray, endPktLen);
    free(mopDescPtrArray);

push:
    Qmss_queuePushDescSize (txQueHnd, (Ptr) sopDescPtr, 32);

    return 0;
}


Int getDataFromCoreN(Int core_num, Void *buf, uint32_t *len)
{
    uint32_t rx_count;
    uint32_t rxLen;
    uint32_t totalLen = 0;
    uint8_t  *data;
    uint8_t  *pBuf = buf;

    Cppi_Desc *rxPkt;
    Cppi_Desc *nexRxPkt;

    if(buf == NULL){
        return -2;
    }

    rx_count = Qmss_getQueueEntryCount (rxQueHnd);
    if(rx_count == 0){
        System_printf("rxQueHnd no data\n");
        return 1;
    }

    rxPkt = (Cppi_Desc *) Qmss_queuePop (rxQueHnd);
    if(rxPkt == NULL){
        System_printf("Qmss_queuePop rxPkt is NULL !!!!!\n");
        return -1;
    }
    nexRxPkt = rxPkt;
    do{
        nexRxPkt = (Cppi_Desc *) QMSS_DESC_PTR (nexRxPkt);
        Cppi_getData (Cppi_DescType_HOST, nexRxPkt, &data, &rxLen);
        memcpy(pBuf, data, rxLen);
        pBuf += rxLen;
        totalLen += rxLen;
        Qmss_queuePushDesc (freeQueHnd, (uint32_t *) nexRxPkt);
        nexRxPkt = Cppi_getNextBD(Cppi_DescType_HOST, nexRxPkt);
    }while(nexRxPkt != 0);

    *len = totalLen;
    //Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, rxPkt, &buf, &len);

    Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
    return 0;
}
