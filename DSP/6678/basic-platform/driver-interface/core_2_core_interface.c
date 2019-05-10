/*
 * core_2_core_interface.c
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
 *      Author: pu
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <qmss_init.h>

//CPPI & QMSS
#include <ti/drv/QMSS/QMSS_drv.h>
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>
#include <ti/drv/cppi/cppi_osal.h>


extern Qmss_QueueHnd freeQueHnd;
extern Qmss_QueueHnd rxQueHnd;
extern Qmss_QueueHnd txQueHnd;

Int sendDataToCoreN(Int core_id, Void *buf, uint32_t len)
{
    Cppi_DescTag            Tag;
    Cppi_Desc *             DescPtr;

    Tag.srcTagLo = core_id;  //rx flow id

    DescPtr = (Cppi_Desc *) Qmss_queuePop (freeQueHnd);
    if(DescPtr == NULL){
        System_printf("rxQueHnd no data\n");
        return 1;
    }

    //????
    Cppi_setData (Cppi_DescType_HOST, DescPtr, (uint8_t *)((uint32_t)(buf)), len);
    Cppi_setTag(Cppi_DescType_HOST, DescPtr, &Tag);
    Cppi_setPacketLen (Cppi_DescType_HOST, DescPtr, len);

    Qmss_queuePushDescSize (txQueHnd, (Ptr) DescPtr, 32);
    return 0;
}


Int getDataFromCoreN(Int core_id, Void *buf, uint32_t len)
{
    uint32_t rx_count;
    uint8_t  *data;

    Cppi_Desc *rxPkt;

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

    rxPkt = (Cppi_Desc *) QMSS_DESC_PTR (rxPkt);
    //Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, rxPkt, &buf, &len);
    Cppi_getData (Cppi_DescType_HOST, rxPkt, &data, &len);

    memcpy(buf, data, len);

    Qmss_queuePushDesc (freeQueHnd, (uint32_t *) rxPkt);
    return 0;
}
