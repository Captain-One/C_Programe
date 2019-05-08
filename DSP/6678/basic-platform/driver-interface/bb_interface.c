/*
 * bb-interface.c
 *
 *  Created on: 2019Äê5ÔÂ8ÈÕ
 *      Author: pu
 */

#include <bb_interface.h>


Int getBbData(Int bbfpgaNo, Void *bufu, Int len)
{
    //read srio buf;

    return 0;
}

Int sendDataToBb(Int bbfpgaNo, Void *bufu, Int len)
{
    Int  re;

    switch(bbfpgaNo){
    case BB_FPGA_NO_0: re = srioSendData(0, bufu, len);break;
    case BB_FPGA_NO_1: re = srioSendData(1, bufu, len);break;
    default : break;
    }

    if(re < 0){
        System_printf("srioSendData error\n");
        return -1;
    }

    return 0;
}


Int srioSendData(uint8_t port, Void *bufu, Int len)
{
    Srio_SockHandle         controlSocket;
    Srio_SockBindAddrInfo   bindInfo;
    Srio_SockAddrInfo       to;


    if(!port){
        to.dio.rapidIOLSB    = 0;
        to.dio.dstID         = srio_device_ID2;
        bindInfo.dio.outPortID      = SRIO_PORT_NUM;
    }else{
        to.dio.rapidIOLSB    = 0;
        to.dio.dstID         = srio_device_ID3;
        bindInfo.dio.outPortID      = SRIO_PORT_NUM;
    }

    to.dio.rapidIOMSB    = 0x0;
    to.dio.ttype         = Srio_Ttype_Write_NWRITE;
    to.dio.ftype         = Srio_Ftype_WRITE;

    /* DIO Binding Information: */
    bindInfo.dio.doorbellValid  = 0;
    bindInfo.dio.intrRequest    = 0;
    bindInfo.dio.supInt         = 0;
    bindInfo.dio.xambs          = 0;
    bindInfo.dio.priority       = 0;
    bindInfo.dio.idSize         = 0;
    bindInfo.dio.srcIDMap       = 0;
    bindInfo.dio.hopCount       = 0;
    bindInfo.dio.doorbellReg    = 0;
    bindInfo.dio.doorbellBit    = 0;

    controlSocket = Srio_sockOpen (hAppManagedSrioDrv, Srio_SocketType_DIO, TRUE);
    if (controlSocket == NULL)
    {
        System_printf ("Error: DIO Control Socket open failed\n");
        return -1;
    }


    /* Bind the DIO socket. */
    if (Srio_sockBind (controlSocket, &bindInfo) < 0)
    {
       System_printf ("Error: Binding the DIO Control Socket failed.\n");
       return -1;
    }

    if (Srio_sockSend (controlSocket, buf, len, &to) < 0)
    {
        System_printf ("Error: Unable to send RX dropped packet message over DIO socket\n");
        return -1;
    }

    //sendMgmtPingReply();

    Srio_sockClose (controlSocket);
    return 0;
}

