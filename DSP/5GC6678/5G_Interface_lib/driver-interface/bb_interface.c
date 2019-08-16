/*
 * bb-interface.c
 *
 *  Created on: 2019年5月8日
 *      Author: pu
 */

#include <bb_interface.h>
#include <srio_init.h>
#include <xdc/runtime/System.h>
//#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_cacheAux.h>
#include <common.h>

#if 0
#pragma DATA_SECTION(fpga0WriteIndex, ".L2RAM")
volatile uint32_t fpga0WriteIndex = 0;
#endif

#pragma DATA_SECTION(fpga0EerorPktCount, ".L2RAM")
volatile uint32_t fpga0EerorPktCount = 0;

#pragma DATA_SECTION(fpga0ReadIndex, ".L2RAM")
volatile uint32_t fpga0ReadIndex = 0;

#if 0
#pragma DATA_SECTION(fpga1WriteIndex, ".L2RAM")
volatile uint32_t fpga1WriteIndex = 0;
#endif

#pragma DATA_SECTION(fpga1EerorPktCount, ".L2RAM")
volatile uint32_t fpga1EerorPktCount = 0;

#pragma DATA_SECTION(fpga1ReadIndex, ".L2RAM")
volatile uint32_t fpga1ReadIndex = 0;

uint32_t const fpga0BufCount = SRIO_FPGA0_DATA_BUF_COUNT;   //size/256;
uint32_t const fpga1BufCount = SRIO_FPGA1_DATA_BUF_COUNT;

Int getBbData(Int bbfpgaNo, Void *buf, uint32_t *len)
{
    Int  re;
    uint8_t *pdata;
    uint64_t *pbuf;
  //FpkH_t  *pdata;
    uint32_t  dataBlockCount;
    uint32_t  allBufCount;
    uint32_t  writeIndex;
    uint32_t  readIndex;
    uint32_t  bufAddr;
    uint32_t  readLen;

    if(bbfpgaNo == BB_FPGA_NO_0){
        pbuf = (uint64_t *)DSP_SRIO_FPGA0_CFG_REG_BASE_ADDR;
        CACHE_invL1d ((void *)pbuf, 8, CACHE_WAIT);
        writeIndex = *pbuf;
        bufAddr = SRIO_FPGA0_DATA_BUF_ADDR >> 8;
        readIndex = fpga0ReadIndex;
        allBufCount = fpga0BufCount;
    }else{
        pbuf = (uint64_t *)DSP_SRIO_FPGA1_CFG_REG_BASE_ADDR;
        CACHE_invL1d ((void *)pbuf, 8, CACHE_WAIT);
        writeIndex = *pbuf;
        bufAddr = SRIO_FPGA1_DATA_BUF_ADDR >> 8;
        readIndex = fpga1ReadIndex;
        allBufCount = fpga1BufCount;
    }

    if(writeIndex < bufAddr)
        return 0;

    writeIndex = writeIndex - bufAddr;

    if(writeIndex == readIndex){
        return 0;
    }

    if(readIndex > writeIndex){   // readIndex > writeIndex  有翻转
        dataBlockCount =  allBufCount - readIndex + writeIndex;
    }else{
        dataBlockCount = writeIndex - readIndex;
    }

    if(dataBlockCount*256 > 8*1024)
      readLen = 8*1024;
    else
      readLen = dataBlockCount * 256;

    pdata = (uint8_t *)(SRIO_FPGA0_DATA_BUF_ADDR + (readIndex << 8));

    CACHE_invL1d ((void *)pdata, readLen, CACHE_WAIT);
   // memcpy(buf, pdata, readLen);
    //CACHE_wbL1d ((void *)buf, 256, CACHE_WAIT);

#if 0
    fpkt = (FpkH_t  *)(SRIO_DATA_BUF_ADDR + DATA_ALIGN * readIndex) ;

    if(fpkt->mark != 0xDCBA){
        eerorPktCount ++;
        readIndex ++;
        goto de;
    }else{
        //fpkt->flen
        memcpy(buf, fpkt, fpkt->flen);
    }
#endif
    //xie

    readIndex += readLen/256;
    if(readIndex == allBufCount)
        readIndex = 0;
    if(bbfpgaNo == BB_FPGA_NO_0){
        fpga0ReadIndex = readIndex;
    }else{
        fpga1ReadIndex = readIndex;
    }
    //readIndex  = *(uint32_t *)l2_global_address((uint32_t)(&readIndex));
    re = writeReadIndex(bbfpgaNo, readIndex);
    if(re < 0)
        return -3;



    *len = readLen;
    return readLen;
}

Int sendDataToBb(Int bbfpgaNo, Void *buf, Int len)
{
    Int  re = -1;

    len = (len + (256 - 1)) & (~ (256 - 1));  //256 align

    switch(bbfpgaNo){
    case BB_FPGA_NO_0: re = srioSendData(0, buf, len, srio_Send_Data);break;
    case BB_FPGA_NO_1: re = srioSendData(2, buf, len, srio_Send_Data);break;
    default : break;
    }

    return re;
}


Int writeBbReg(Int bbfpgaNo, Void *buf)
{
    Int re = -1;
    uint32_t len;

    len = sizeof(srioConfigParameter);

    switch(bbfpgaNo){
    case BB_FPGA_NO_0:  re = srioSendData(0, buf,len , srio_Send_Param);break;
    case BB_FPGA_NO_1:  re = srioSendData(2, buf,len , srio_Send_Param);break;
    default : break;
    }

   return re;
}


Int configSrioParameterToFPGA(Int bbfpgaNo)
{
    Int re = 0;
    srioConfigParameter cfgParam;

    if(bbfpgaNo){
        cfgParam.dspcfgstartaddr = (uint64_t)(DSP_SRIO_FPGA1_CFG_REG_BASE_ADDR >> 8);
        cfgParam.dspcfgendaddr = (uint64_t)(DSP_SRIO_FPGA1_CFG_REG_BASE_END_ADDR  >> 8);
        cfgParam.dspdatastartaddr = (uint64_t)(SRIO_FPGA1_DATA_BUF_ADDR  >> 8);
        cfgParam.dspdataendaddr = (uint64_t)(SRIO_FPGA1_DATA_BUF_END_ADDR  >> 8);
        cfgParam.dspreadindexaddr = (uint64_t)(SRIO_FPGA1_DATA_BUF_ADDR >> 8 + fpga1ReadIndex);
    }else{
        cfgParam.dspcfgstartaddr = (uint64_t)(DSP_SRIO_FPGA0_CFG_REG_BASE_ADDR >> 8);
        cfgParam.dspcfgendaddr = (uint64_t)(DSP_SRIO_FPGA0_CFG_REG_BASE_END_ADDR  >> 8);
        cfgParam.dspdatastartaddr = (uint64_t)(SRIO_FPGA0_DATA_BUF_ADDR  >> 8);
        cfgParam.dspdataendaddr = (uint64_t)(SRIO_FPGA0_DATA_BUF_END_ADDR  >> 8);
        cfgParam.dspreadindexaddr = (uint64_t)(SRIO_FPGA0_DATA_BUF_ADDR >> 8 + fpga0ReadIndex);
    }

    CACHE_wbL1d ((void *) &cfgParam, sizeof(srioConfigParameter), CACHE_WAIT);

    re = writeBbReg(bbfpgaNo, (void *) &cfgParam);

    return re;
}

Int writeReadIndex(Int bbfpgaNo, uint32_t readIndex)
{
    Int re = -1;
    uint64_t data = 0;

    switch(bbfpgaNo){
    case BB_FPGA_NO_0:
        data = (uint64_t)((SRIO_FPGA0_DATA_BUF_ADDR >> 8) + readIndex);
        CACHE_wbL1d ((void *) &data, 8, CACHE_WAIT);
        re = srioSendData(0, &data, 8 , srio_Send_ReadIndex);
        break;
    case BB_FPGA_NO_1:
        data = (uint64_t)((SRIO_FPGA1_DATA_BUF_ADDR >> 8) + readIndex);
        CACHE_wbL1d ((void *) &data, 8, CACHE_WAIT);
        re = srioSendData(2, &data, 8 , srio_Send_ReadIndex);
        break;
    default : break;
    }

    return re;
}


