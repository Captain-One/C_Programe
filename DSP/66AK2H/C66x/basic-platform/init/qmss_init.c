/*
 * qmss_init.c
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: lin
 */

#include "qmss_init.h"

#include <xdc/runtime/System.h>

//CPPI & QMSS
#include <ti/drv/CPPI/CPPI_drv.h>
#include <ti/drv/QMSS/QMSS_drv.h>

//IPC
#include <ti/ipc/Ipc.h>
#include <ti/sdo/ipc/Notify.h>

extern Qmss_GlobalConfigParams qmssGblCfgParams;
extern Cppi_GlobalConfigParams cppiGblCfgParams;
extern UInt16 core_id;

/* linking RAM */
#pragma DATA_ALIGN (linkingRAM0, 16)
uint64_t            linkingRAM0[NUM_HOST_DESC + NUM_MONOLITHIC_DESC];

/* Descriptor pool [Size of descriptor * Number of descriptors] */
#pragma DATA_ALIGN (hostDesc, 16)
uint8_t             hostDesc[SIZE_HOST_DESC * NUM_HOST_DESC];
#pragma DATA_ALIGN (monolithicDesc, 16)
uint8_t             monolithicDesc[SIZE_MONOLITHIC_DESC * NUM_MONOLITHIC_DESC];
#pragma DATA_ALIGN (dataBuff, 16)
uint8_t             dataBuff[SIZE_DATA_BUFFER * NUM_DATA_BUFFER];



Int cppiInit(Void)
{
    Qmss_Result  re_qmss;
    Cppi_Result  re_cppi;
    Qmss_InitCfg cfg;

    cfg.linkingRAM0Base = 0;
    cfg.linkingRAM0Size = 0;
    cfg.linkingRAM1Base = 0;
    cfg.maxDescNum = 0;
    //cfg.mode = 0;
    //cfg.pdspFirmware = NULL;
    cfg.qmssHwStatus = 0;
    //cfg.splitLinkingRAMs = 1;

    re_qmss = Qmss_init(&cfg, &qmssGblCfgParams);
    if(re_qmss != QMSS_SOK){
        System_printf("Qmss init error\n");
        return re_qmss;
    }

    re_qmss = Qmss_start();
    if(re_qmss != QMSS_SOK){
        System_printf("core %d Qmss start error\n", core_id);
        return re_qmss;
    }

    re_cppi = Cppi_init(&cppiGblCfgParams);
    if(re_cppi != CPPI_SOK){
        System_printf("Cppi init error\n");
        return re_cppi;
    }



    return 0;
}
