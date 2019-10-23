/*
 * bb-interface.c
 *
 *  Created on: 2019��5��8��
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

Int getBbData(Int bbfpgaNo, Void *buf, uint16_t *len)
{
    Int  re;
    uint8_t   *pdata;
    uint8_t   *pbuf;
    uint64_t  *pwriteIndex;
    packet_t  *ppktbuf;
    uint32_t  dataBlockCount;
    uint32_t  tailDataLen;
    uint32_t  allBufCount;
    uint32_t  writeIndex;
    uint32_t  readIndex;
    uint32_t  dataBufStartIndex;
    uint32_t  dataBufEndtIndex;
    uint32_t  readLen;

    pbuf = buf;

    if(bbfpgaNo == BB_FPGA_NO_0){
        pwriteIndex = (uint64_t *)DSP_SRIO_FPGA0_CFG_REG_BASE_ADDR;   //��ȡдָ���ַ
        CACHE_invL1d ((void *)pwriteIndex, 8, CACHE_WAIT);
        writeIndex = *pwriteIndex;  //��ȡдָ��ֵ
        writeIndex = swp64(*pwriteIndex);  //дָ����ڸ�32λ
        dataBufStartIndex = SRIO_FPGA0_DATA_BUF_ADDR >> 8;  //���ݴ洢����ʼ��������ʼ��ַ/256
        dataBufEndtIndex = SRIO_FPGA0_DATA_BUF_END_ADDR >> 8;  //���ݴ洢����������
        readIndex = fpga0ReadIndex;  //��ȡ��ָ�룬ȫ�ֱ���
        allBufCount = fpga0BufCount;  //��ȡ�������ݴ洢��256�ֽ����ݿ�Ŀ���
        pdata = (uint8_t *)(SRIO_FPGA0_DATA_BUF_ADDR + (readIndex << 8));  //��ȡ���ݻ������׵�ַ��
    }else{
        pwriteIndex = (uint64_t *)DSP_SRIO_FPGA1_CFG_REG_BASE_ADDR;
        CACHE_invL1d ((void *)pwriteIndex, 8, CACHE_WAIT);
        writeIndex = swp64(*pwriteIndex);  //дָ����ڸ�32λ
        dataBufStartIndex = SRIO_FPGA1_DATA_BUF_ADDR >> 8;
        dataBufEndtIndex = SRIO_FPGA1_DATA_BUF_END_ADDR >> 8;
        readIndex = fpga1ReadIndex;
        allBufCount = fpga1BufCount;
        pdata = (uint8_t *)(SRIO_FPGA1_DATA_BUF_ADDR + (readIndex << 8));  //��ȡ���ݻ������׵�ַ��
    }

    if((writeIndex < dataBufStartIndex) || (writeIndex > dataBufEndtIndex))  //дָ�����򳬷�Χ
        return 0;

    writeIndex = writeIndex - dataBufStartIndex;  //����дָ����������дָ���ַ��ʽת����0��1��2��3����ʽ�����ڼ�������

    if(writeIndex == readIndex){  //��дָ����ȣ�����δ��ʼ����
        return 0;
    }

    //���㻺������Ч�����ݿ�����
    if(readIndex > writeIndex){   // readIndex > writeIndex  �з�ת
        dataBlockCount =  allBufCount - readIndex + writeIndex;
        tailDataLen = (allBufCount - readIndex) << 8;   //��������תǰ��β�����ݿ鳤��
    }else{
        dataBlockCount = writeIndex - readIndex;
        tailDataLen = dataBlockCount << 8;   //δ��ת��β�����ݳ��ȵ�����Ч���ݳ���
    }

    ppktbuf = (packet_t *)pdata;
//�ж�����mark�Ͱ����Ƿ���ȷ
    if((ppktbuf->header.mark != 0xBADC) || (swap16(ppktbuf->header.len) > 40000)){
        readLen = 256;   //���ݰ�����
        ppktbuf->header.len = 0; //���ݰ��������÷��ذ���0��ָʾ��ȡ��ʧ��
        goto wi;  //��ת�������ָ�룬д��ָ�봦��������ȡ�����ݿ�
    }

    if(swap16(ppktbuf->header.len) > (dataBlockCount << 8)){  //���ݰ�δ�������,ֱ�ӷ���
        return 0;
    }

    readLen = (swap16(ppktbuf->header.len) + (256 - 1)) & (~ (256 - 1));  //256 align

    if(readLen > tailDataLen)  //�жϸ����ݰ��Ƿ�ת
    {
        //�з�ת���ȿ���β��
        CACHE_invL1d ((void *)pdata, tailDataLen, CACHE_WAIT);
        memcpy(pbuf, pdata, tailDataLen);
        CACHE_wbL1d ((void *)pbuf, tailDataLen, CACHE_WAIT);

        pbuf = pbuf + tailDataLen;
        pdata = (uint8_t *)(dataBufStartIndex << 8);
        //����ʣ��
        CACHE_invL1d ((void *)pdata, readLen - tailDataLen, CACHE_WAIT);
        memcpy(pbuf, pdata, swap16(ppktbuf->header.len) - tailDataLen);
        CACHE_wbL1d ((void *)pbuf, swap16(ppktbuf->header.len) - tailDataLen, CACHE_WAIT);
    }else{
        //�޷�ת
        CACHE_invL1d ((void *)pdata, readLen, CACHE_WAIT);
        memcpy(pbuf, pdata, swap16(ppktbuf->header.len));
        CACHE_wbL1d ((void *)pbuf, swap16(ppktbuf->header.len), CACHE_WAIT);
    }

wi:
    readIndex += readLen >> 8;  // readLen/256 ���㶼ָ��
    if(readIndex >= allBufCount){  //��ָ����ڵ����ܵ����ݿ���ʱ�����¼����ָ��
        readIndex = readIndex - allBufCount;
    }
    if(bbfpgaNo == BB_FPGA_NO_0){
        fpga0ReadIndex = readIndex;
    }else{
        fpga1ReadIndex = readIndex;
    }

    //readIndex  = *(uint32_t *)l2_global_address((uint32_t)(&readIndex));
    re = writeReadIndex(bbfpgaNo, readIndex);
    if(re < 0)
        return -3;

    *len = swap16(ppktbuf->header.len);
    return swap16(ppktbuf->header.len);
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
        cfgParam.dspcfgstartaddr = swp64((uint64_t)(DSP_SRIO_FPGA1_CFG_REG_BASE_ADDR >> 8));
        cfgParam.dspcfgendaddr = swp64((uint64_t)(DSP_SRIO_FPGA1_CFG_REG_BASE_END_ADDR  >> 8));
        cfgParam.dspdatastartaddr = swp64((uint64_t)(SRIO_FPGA1_DATA_BUF_ADDR  >> 8));
        cfgParam.dspdataendaddr = swp64((uint64_t)(SRIO_FPGA1_DATA_BUF_END_ADDR  >> 8));
        cfgParam.dspreadindexaddr = swp64((uint64_t)(SRIO_FPGA1_DATA_BUF_ADDR >> 8 + fpga1ReadIndex));
    }else{
        cfgParam.dspcfgstartaddr = swp64((uint64_t)(DSP_SRIO_FPGA0_CFG_REG_BASE_ADDR >> 8));
        cfgParam.dspcfgendaddr = swp64((uint64_t)(DSP_SRIO_FPGA0_CFG_REG_BASE_END_ADDR  >> 8));
        cfgParam.dspdatastartaddr = swp64((uint64_t)(SRIO_FPGA0_DATA_BUF_ADDR  >> 8));
        cfgParam.dspdataendaddr = swp64((uint64_t)(SRIO_FPGA0_DATA_BUF_END_ADDR  >> 8));
        cfgParam.dspreadindexaddr = swp64((uint64_t)(SRIO_FPGA0_DATA_BUF_ADDR >> 8 + fpga0ReadIndex));
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
        data = swp64((uint64_t)((SRIO_FPGA0_DATA_BUF_ADDR >> 8) + readIndex));
        CACHE_wbL1d ((void *) &data, 8, CACHE_WAIT);
        re = srioSendData(0, &data, 8 , srio_Send_ReadIndex);
        break;
    case BB_FPGA_NO_1:
        data = swp64((uint64_t)((SRIO_FPGA1_DATA_BUF_ADDR >> 8) + readIndex));
        CACHE_wbL1d ((void *) &data, 8, CACHE_WAIT);
        re = srioSendData(2, &data, 8 , srio_Send_ReadIndex);
        break;
    default : break;
    }

    return re;
}


void bbInterfaceVariableInit(void)
{
    uint64_t  *pwrite_index;

    //��ʼ��DSP��ָ��
    fpga0ReadIndex = 0;
    fpga1ReadIndex = 0;

    //��ʼ��FPGAдָ��
    pwrite_index = (uint64_t *)DSP_SRIO_FPGA0_CFG_REG_BASE_ADDR;
    *pwrite_index = swp64((uint64_t)(SRIO_FPGA0_DATA_BUF_ADDR >> 8));

    pwrite_index = (uint64_t *)DSP_SRIO_FPGA1_CFG_REG_BASE_ADDR;
    *pwrite_index = swp64((uint64_t)(SRIO_FPGA1_DATA_BUF_ADDR >> 8));

    //����ͳ������
    fpga0EerorPktCount = 0;
    fpga1EerorPktCount = 0;
}



