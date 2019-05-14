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
    Cppi_Desc   * mopDescPtr;
    Cppi_Desc   * sopDescPtr;
    Cppi_Desc   * prevDescPtr;

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

    sopDescPtr = (Cppi_Desc *) QMSS_DESC_PTR (sopDescPtr);
    Cppi_setTag(Cppi_DescType_HOST, sopDescPtr, &Tag);
    if(len <= SIZE_RX_DATA_BUFFER){
        Cppi_setData (Cppi_DescType_HOST, sopDescPtr, (uint8_t *)((uint32_t)(pbuf)), len);
        Cppi_setPacketLen (Cppi_DescType_HOST, sopDescPtr, len);
        goto push;
    }

    firstPktLen = SIZE_RX_DATA_BUFFER;
    endPktLen = len - (rePktCount - 1) * SIZE_RX_DATA_BUFFER;

    Cppi_setData (Cppi_DescType_HOST, sopDescPtr, (uint8_t *)((uint32_t)(pbuf)), firstPktLen);
    Cppi_setPacketLen (Cppi_DescType_HOST, sopDescPtr, firstPktLen);

    rePktCount --;
    pbuf += firstPktLen;

    mopDescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
    if(mopDescPtr == NULL){
        System_printf("rxQueHnd no data\n");
        return 1;
    }
    mopDescPtr = (Cppi_Desc *) QMSS_DESC_PTR (mopDescPtr);
    Cppi_setTag(Cppi_DescType_HOST, mopDescPtr, &Tag);
    Cppi_linkNextBD(Cppi_DescType_HOST, sopDescPtr, mopDescPtr);

    while(rePktCount > 1){
        Cppi_setData (Cppi_DescType_HOST, mopDescPtr, (uint8_t *)((uint32_t)(pbuf)), SIZE_RX_DATA_BUFFER);
        Cppi_setPacketLen (Cppi_DescType_HOST, mopDescPtr, SIZE_RX_DATA_BUFFER);

        prevDescPtr = mopDescPtr;
        pbuf += SIZE_RX_DATA_BUFFER;
        rePktCount --;
        mopDescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
        if(mopDescPtr == NULL){
            System_printf("rxQueHnd no data\n");
            return 1;
        }
        mopDescPtr = (Cppi_Desc *) QMSS_DESC_PTR (mopDescPtr);
        Cppi_setTag(Cppi_DescType_HOST, mopDescPtr, &Tag);
        Cppi_linkNextBD(Cppi_DescType_HOST, prevDescPtr, mopDescPtr);
    }

    Cppi_setData (Cppi_DescType_HOST, mopDescPtr, (uint8_t *)((uint32_t)(pbuf)), endPktLen);
    Cppi_setPacketLen (Cppi_DescType_HOST, mopDescPtr, endPktLen);
    Cppi_linkNextBD(Cppi_DescType_HOST, mopDescPtr, NULL);

push:
    //Qmss_queuePushDesc(txQueHnd, sopDescPtr);
    Qmss_queuePushDescSize (txQueHnd, sopDescPtr, 32);

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
        Cppi_Desc *curDescPtr;
        Cppi_Desc *prevDescPtr;

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
        curDescPtr = rxPkt;
        do{
            curDescPtr = (Cppi_Desc *) QMSS_DESC_PTR (curDescPtr);
            Cppi_getData (Cppi_DescType_HOST, curDescPtr, &data, &rxLen);
            memcpy(pBuf, data, rxLen);
            pBuf += rxLen;
            totalLen += rxLen;
            prevDescPtr = curDescPtr;
            curDescPtr = Cppi_getNextBD(Cppi_DescType_HOST, curDescPtr);
            Qmss_queuePushDesc (freeQueHnd, (uint32_t *) prevDescPtr);
        }while(curDescPtr != 0);

        *len = totalLen;
        //Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, rxPkt, &buf, &len);


        Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
        return 0;
}
