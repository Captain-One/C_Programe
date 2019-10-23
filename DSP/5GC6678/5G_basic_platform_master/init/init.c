/*
 * init.c
 *
 *  Created on: 2019年4月24日
 *      Author: pu
 */

#include <stdio.h>
#include "qmss_init.h"
#include "srio_init.h"
#include "bb_interface.h"
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <NDK_init.h>

#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>

/* CSL power includes */
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>

/* PASS RL file */
#include <ti/csl/cslr_pa_ss.h>

/* Platform utilities include */
#include <ti/platform/platform.h>

// Power definitions
#define PSC_BASE            0x02350000
#define PSC_PTCMD           *( unsigned int* )( PSC_BASE+0x120 )
#define PSC_PTSTAT          *( unsigned int* )( PSC_BASE+0x128 )
#define PSC_PDCTL_BASE      ( PSC_BASE+0x300 )
#define PSC_MDSTAT_BASE     ( PSC_BASE+0x800 )
#define PSC_MDCTL_BASE      ( PSC_BASE+0xA00 )

//PDSP ADDR
#define PASS_PDSP0      0x02001000
#define PASS_PDSP1      0x02001100
#define PASS_PDSP2      0x02001200
#define PASS_PDSP3      0x02001300
#define PASS_PDSP4      0x02001400
#define PASS_PDSP5      0x02001500


void setDomainAndModulePower(unsigned int module, unsigned int domain, unsigned int state)
{
    while(!CSL_PSC_isStateTransitionDone (domain));

    if(state)
    {
        CSL_PSC_enablePowerDomain(domain);
        CSL_PSC_setModuleNextState(module, PSC_MODSTATE_ENABLE );
    }
    else
    {
        CSL_PSC_disablePowerDomain(domain);
        CSL_PSC_setModuleNextState(module, PSC_MODSTATE_SWRSTDISABLE );
    }

    CSL_PSC_startStateTransition(domain);

    while(!CSL_PSC_isStateTransitionDone (domain));

    return;
}

void setModulePower(unsigned int module, unsigned int domain, unsigned int state)
{
    while(!CSL_PSC_isStateTransitionDone (domain));

    if(state)
        CSL_PSC_setModuleNextState(module, PSC_MODSTATE_ENABLE );
    else
        CSL_PSC_setModuleNextState(module, PSC_MODSTATE_SWRSTDISABLE );

    CSL_PSC_startStateTransition(domain);

    while(!CSL_PSC_isStateTransitionDone (domain));

    return;
}

int Set_PSC_State(unsigned int pd,unsigned int id,unsigned int state)
{
    unsigned int* mdctl;
    unsigned int* mdstat;
    unsigned int* pdctl;
    int ret=0;

    mdctl = ( unsigned int* )(PSC_MDCTL_BASE + ( 4 * id ));
    mdstat = ( unsigned int* )( PSC_MDSTAT_BASE + ( 4 * id ));
    pdctl = ( unsigned int* )(PSC_PDCTL_BASE + ( 4 * pd ));

    // If state is already set, do nothing
    if ( ( *mdstat & 0x1f ) == state )
    {
        return(0);
    }

    platform_delay(1500);
    // Check if we got timeout error while waiting
    if (PSC_PTSTAT & (0x1 << pd))
    {
        printf( "Set_PSC_State... Timeout Error #01 pd=%d, md=%d!\n",pd, id);
        ret=1;
    }
    else
    {
        // Set power domain control
        *pdctl = (*pdctl) | 0x00000001;

        // Set MDCTL NEXT to new state
        *mdctl = ((*mdctl) & ~(0x1f)) | state;

        // Start power transition by setting PTCMD GO to 1
        PSC_PTCMD = (PSC_PTCMD) | (0x1<<pd);

        // Wait for PTSTAT GOSTAT to clear
        platform_delay(1500);
        if ((PSC_PTSTAT & (0x1 << pd)) != 0 ) {
            printf( "Set_PSC_State... Timeout Error #02 pd=%d, md=%d!\n",pd, id);
            return 1;
        }

        // Verify state changed
        platform_delay(1500);
        if(( *mdstat & 0x1f ) != state ) {
            if ((pd == 2) && (id == 9) ) {
                printf( "Security Accelerator disabled!\n");
            } else {
                printf( "Set_PSC_State... Timeout Error #03 pd=%d, md=%d!\n",pd, id);
            }
            return 1;
        }
    }

    return(ret);
}


int paHwReset(void)
{
    platform_init_flags     sFlags;
    platform_init_config    sConfig;
    /* Status of the call to initialize the platform */
    int32_t pform_status;
#if 0
    /* Disabling PA PDSP to prepare for power down */
    volatile unsigned int *passPDSP;
    passPDSP = (unsigned int*)PASS_PDSP0;
    *passPDSP &= 0xFFFFFFFD;

    passPDSP = (unsigned int*)PASS_PDSP1;
    *passPDSP &= 0xFFFFFFFD;

    passPDSP = (unsigned int*)PASS_PDSP2;
    *passPDSP &= 0xFFFFFFFD;

    passPDSP = (unsigned int*)PASS_PDSP3;
    *passPDSP &= 0xFFFFFFFD;

    passPDSP = (unsigned int*)PASS_PDSP4;
    *passPDSP &= 0xFFFFFFFD;

    passPDSP = (unsigned int*)PASS_PDSP5;
    *passPDSP &= 0xFFFFFFFD;
#endif
    Set_PSC_State(CSL_PSC_PD_NETCP, CSL_PSC_LPSC_SA, PSC_MODSTATE_SWRSTDISABLE);
    Set_PSC_State(CSL_PSC_PD_NETCP, CSL_PSC_LPSC_CPGMAC, PSC_MODSTATE_SWRSTDISABLE);
    Set_PSC_State(CSL_PSC_PD_NETCP, CSL_PSC_LPSC_PA, PSC_MODSTATE_SWRSTDISABLE);

    platform_delay(500000);
    platform_delay(500000);
    platform_delay(500000);
    //Then power on:

    Set_PSC_State(CSL_PSC_PD_NETCP, CSL_PSC_LPSC_PA, PSC_MODSTATE_ENABLE);
    Set_PSC_State(CSL_PSC_PD_NETCP, CSL_PSC_LPSC_CPGMAC, PSC_MODSTATE_ENABLE);
    Set_PSC_State(CSL_PSC_PD_NETCP, CSL_PSC_LPSC_SA, PSC_MODSTATE_ENABLE);

    platform_delay(500000);
    platform_delay(500000);

#if 0
    //power off
    do{
        CSL_PSC_disablePowerDomain(CSL_PSC_PD_NETCP);
        CSL_PSC_setModuleNextState(CSL_PSC_LPSC_PA, PSC_MODSTATE_SWRSTDISABLE);
        CSL_PSC_setModuleNextState(CSL_PSC_LPSC_CPGMAC, PSC_MODSTATE_SWRSTDISABLE);
        CSL_PSC_setModuleNextState(CSL_PSC_LPSC_SA, PSC_MODSTATE_SWRSTDISABLE);
        CSL_PSC_startStateTransition(CSL_PSC_PD_NETCP);
        platform_delay(5000);
    }while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_NETCP));

#if 0
    setModulePower(CSL_PSC_LPSC_PA, CSL_PSC_PD_PASS, 0);
    setModulePower(CSL_PSC_LPSC_CPGMAC, CSL_PSC_PD_PASS, 0);  //SGMII
    setModulePower(CSL_PSC_LPSC_SA, CSL_PSC_PD_PASS, 0);
#endif
    //延时
    platform_delay(50000);

    //power on
    do{
        CSL_PSC_enablePowerDomain(CSL_PSC_PD_NETCP);
        CSL_PSC_setModuleNextState(CSL_PSC_LPSC_PA, PSC_MODSTATE_ENABLE);
        CSL_PSC_setModuleNextState(CSL_PSC_LPSC_CPGMAC, PSC_MODSTATE_ENABLE);
        CSL_PSC_setModuleNextState(CSL_PSC_LPSC_SA, PSC_MODSTATE_ENABLE);
        CSL_PSC_startStateTransition(CSL_PSC_PD_NETCP);
        platform_delay(5000);
    }while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_NETCP));


#if 0
    setDomainAndModulePower(CSL_PSC_LPSC_PA, CSL_PSC_PD_PASS, 1);
    setModulePower(CSL_PSC_LPSC_SA, CSL_PSC_PD_PASS, 1);
    setModulePower(CSL_PSC_LPSC_CPGMAC, CSL_PSC_PD_PASS, 1);
#endif
#endif

#if 0
    setModulePower(CSL_PSC_LPSC_CPGMAC, CSL_PSC_PD_PASS, 0);
    setModulePower(CSL_PSC_LPSC_Crypto, CSL_PSC_PD_PASS, 0);
    setDomainAndModulePower(CSL_PSC_LPSC_PKTPROC, CSL_PSC_PD_PASS, 0);
#endif


    memset( (void *) &sFlags,  0, sizeof(platform_init_flags));
    memset( (void *) &sConfig, 0, sizeof(platform_init_config));

    sFlags.pll  = 0;    /* PLLs for clocking    */
    sFlags.ddr  = 0;    /* External memory      */
    sFlags.tcsl = 1;    /* Time stamp counter   */

    sFlags.phy  = 1;    /* Ethernet             */

    sFlags.ecc  = 0;    /* Memory ECC           */

    sConfig.pllm = 0;   /* Use libraries default clock divisor */

    pform_status = platform_init(&sFlags, &sConfig);
    if(pform_status != Platform_EOK)
        return -1;

    return 0;
}

void taskNdkInit(UArg a0, UArg a1)
{
    int re;

    //PA模块硬件复位，意外关闭或者终止调试后PA可能没有释放资源导致不断电的情况下复位后网络部分不能用
    re = paHwReset();

    re = NDK_config();
    if(re != 0){
        System_printf("NDK Init error\n");
    }
}


Int  sysInit(Void)
{
    Task_Handle task;
    Error_Block eb;

    Int re;

#if 1
    re = ipcInit();
    if(re < 0){
        System_printf("IPC Init error\n");
        return -1;
    }

    re = cppiInit();
    if(re < 0){
        System_printf("cppi Init error\n");
        return -1;
    }
#endif

#if 0
    re = srioInit();
    if(re < 0){
          return re;
    }

    //配置DSP参数到FPGA
    re = configSrioParameterToFPGA(BB_FPGA_NO_1);
    //re = configSrioParameterToFPGA(BB_FPGA_NO_0);
    if(re != 0){
        return -1;
    }
    //等待FPGA初始化完成 待确认

#endif

#if 1
    Error_init(&eb);
    task = Task_create(taskNdkInit, NULL, &eb);
    if (task == NULL) {
        System_printf("create() taskNdkInit failed!\n");
        return -1;
    }

    Task_yield();
#endif
    return 0;
}
