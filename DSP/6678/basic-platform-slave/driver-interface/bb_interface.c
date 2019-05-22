/*
 * bb-interface.c
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
 *      Author: pu
 */

#include <bb_interface.h>
#include <srio_init.h>
#include <xdc/runtime/System.h>
#include <common.h>

uint32_t writeIndex;
uint32_t readIndex;
uint32_t eerorPktCount = 0;

Int getBbData(Int bbfpgaNo, Void *buf, Int len)
{
    FpkH_t  *fpkt;
    uint32_t  dataBlockCount;

    if(writeIndex == readIndex){
        return 0;
    }
  //cach
    dataBlockCount = writeIndex - readIndex;

    fpkt = (FpkH_t  *)(SRIO_DATA_BUF_ADDR + DATA_ALIGN * readIndex) ;

    if(fpkt->mark != 0xDCBA){
        eerorPktCount ++;
        readIndex ++;
        goto de;
    }else{
        //fpkt->flen
        memcpy(buf, fpkt, fpkt->flen);
    }
    //xie
de:
    writeBbReg(bbfpgaNo, &readIndex);
    return 0;
}

Int sendDataToBb(Int bbfpgaNo, Void *buf, Int len)
{
    Int  re;

    switch(bbfpgaNo){
    case BB_FPGA_NO_0: re = srioSendData(0, buf, len);break;
    case BB_FPGA_NO_1: re = srioSendData(1, buf, len);break;
    default : break;
    }

    if(re < 0){
        System_printf("srioSendData error\n");
        return -1;
    }

    return 0;
}


Int writeBbReg(Int bbfpgaNo, Void *buf)
{
    Int re;

    switch(bbfpgaNo){
    case BB_FPGA_NO_0:  re = srioSendData(0, buf, 256);break;
    case BB_FPGA_NO_1:  re = srioSendData(1, buf, 256);break;
    default : break;
    }
    if(re < 0){
        return -1;
    }
   return 0;
}


