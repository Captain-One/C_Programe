/*
 * srio_init.c
 *
 *  Created on: 2019Äê4ÔÂ26ÈÕ
 *      Author: pu
 */

#include "srio_init.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/family/c66/tci66xx/CpIntc.h>

/* CSL BootCfg Module */
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>

/* CSL Chip Functional Layer */
#include <ti/csl/csl_chip.h>

/* CSL Cache Functional Layer */
#include <ti/csl/csl_cacheAux.h>

/* CSL PSC Include Files */
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>

/* CSL Cache Functional Layer */
#include <ti/csl/csl_cacheAux.h>

/* CSL PSC Include Files */
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>

/* CSL SRIO Functional Layer */
#include <ti/csl/csl_srio.h>
#include <ti/csl/csl_srioAux.h>
#include <ti/csl/csl_device_interrupt.h>
#include <ti/csl/csl_srioAuxPhyLayer.h>

/* SRIO Driver Include File. */
#include <srio_osal.h>
#include <ti/drv/srio/srio_drv.h>

#include <srio_laneconfig.h>

#if !defined(CSL_CIC0_SRIO_INTDST0)
#define CSL_CIC0_SRIO_INTDST0   CSL_INTC0_INTDST0
#endif


uint32_t srio_device_ID1 = DSP_SRIO_8BIT_DEVICE_ID;           /* DSP */
uint32_t srio_device_ID2 = FPGA0_SRIO_8BIT_DEVICE_ID;           /* FPGA0  */
uint32_t srio_device_ID3 = FPGA0_SRIO_8BIT_DEVICE_ID;//DSP_SRIO_SECOND_8BIT_DEVICE_ID;           /* FPGA1 */

uint32_t srio_work_mode = srio_Normal_mode;//srio_Loopback_mode;
srioRefClockMhz_e srio_refClockMhz = srio_ref_clock_156p25Mhz;
srioLaneRateGbps_e  srio_laneSpeedGbps = srio_lane_rate_5p000Gbps;
srioLanesMode_e     srio_lanesMode = srio_lanes_form_two_2x_ports;
Int                srio_isBoardToBoard = 1;
Int                srio_usePolledMode = 0;

/* Consumer Management Socket. */
//Srio_SockHandle     mgmtSocket;
Srio_SockHandle       fpga0ControlSocket = NULL;
Srio_SockHandle       fpga1ControlSocket = NULL;

/* Global SRIO Driver Handle. */
Srio_DrvHandle      hAppManagedSrioDrv;


Int srioInit(Void)
{
    int32_t             eventId;
    Srio_DrvConfig      appCfg;
    int32_t  re;

    appCfg.bAppManagedConfig = FALSE;

    appCfg.u.drvManagedCfg.bIsRxCfgValid = FALSE;
    appCfg.u.drvManagedCfg.bIsTxCfgValid = FALSE;

#if 0
    /* The application managed configuration is capable of reception. */
    appCfg.u.appManagedCfg.bIsRxFlowCfgValid = 1;

    /* Configure the Receive Flow */
    appCfg.u.appManagedCfg.rxFlowCfg.flowIdNum          = -1;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_qnum       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_qmgr       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_sop_offset      = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_ps_location     = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_desc_type       = 0x1; /* Host Descriptor. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_error_handling  = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_psinfo_present  = 0x1; /* PS Information */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_einfo_present   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_lo     = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_hi     = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_lo      = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_hi      = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_lo_sel = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_hi_sel = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_lo_sel  = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_hi_sel  = 0x0;

    /* Disable Receive size thresholds. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh0_en = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh1_en = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh2_en = 0x0;

    /* Use the Application Receive Free Queue for picking all descriptors. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq1_qnum       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq1_qmgr       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq2_qnum       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq2_qmgr       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq3_qnum       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq3_qmgr       = 0;

    /* Use the Receive Queue for picking the SOP packet also. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz0_qnum   = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz0_qmgr   = 0;

    /* There are no size thresholds configured. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh0    = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh1    = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh2    = 0x0;

    /* The other threshold queues do not need to be configured */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz1_qnum   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz1_qmgr   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz2_qnum   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz2_qmgr   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz3_qnum   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz3_qmgr   = 0x0;

    if (srio_usePolledMode)
    {
        /* Polling Mode: So don't program the accumulator. */
        appCfg.u.appManagedCfg.bIsAccumlatorCfgValid = 0;
    }
    else
    {
        /* Program the accumulator. */
        appCfg.u.appManagedCfg.bIsAccumlatorCfgValid = 1;
    }

    /* Accumulator Configuration. */
    appCfg.u.appManagedCfg.accCfg.channel             = CSL_chipReadReg (CSL_CHIP_DNUM);
    appCfg.u.appManagedCfg.accCfg.command             = Qmss_AccCmd_ENABLE_CHANNEL;
    appCfg.u.appManagedCfg.accCfg.queueEnMask         = 0;
    appCfg.u.appManagedCfg.accCfg.queMgrIndex         = 0;
    appCfg.u.appManagedCfg.accCfg.maxPageEntries      = 0;
    appCfg.u.appManagedCfg.accCfg.timerLoadCount      = 0;
    appCfg.u.appManagedCfg.accCfg.interruptPacingMode = Qmss_AccPacingMode_LAST_INTERRUPT;
    appCfg.u.appManagedCfg.accCfg.listEntrySize       = Qmss_AccEntrySize_REG_D;
    appCfg.u.appManagedCfg.accCfg.listCountMode       = Qmss_AccCountMode_ENTRY_COUNT;
    appCfg.u.appManagedCfg.accCfg.multiQueueMode      = Qmss_AccQueueMode_SINGLE_QUEUE;

    /* Populate the rest of the configuration. */
    appCfg.u.appManagedCfg.rawRxFreeDrvBuffer = 0;
    appCfg.u.appManagedCfg.txQueueNum = 0;

    /* Set the PKTDMA TX channel priority to low */
    appCfg.u.appManagedCfg.srioPktDmaTxPrio = Srio_PktDma_Prio_Low;
#endif

    if (enable_srio () < 0)
    {
        System_printf ("Error: SRIO PSC Initialization Failed\n");
        return -1;
    }

    if (SrioDevice_init () < 0)
        return -1;

    re = Srio_init ();
    if (re < 0)
        return -1;

    /* Start the application Managed SRIO Driver. */
    hAppManagedSrioDrv = Srio_start (&appCfg);
    if (hAppManagedSrioDrv == NULL)
    {
        System_printf ("Error: Application Managed SRIO Driver failed to start\n");
        return -1;
    }

#if 0
    if(!srio_usePolledMode)
    {
        /* Hook up the SRIO interrupts with the core. */
        EventCombiner_dispatchPlug (48, (EventCombiner_FuncPtr)Srio_rxCompletionIsr, (UArg)hAppManagedSrioDrv, TRUE);
        EventCombiner_enableEvent (48);

        /* SRIO DIO: Interrupts need to be routed from the CPINTC0 to GEM Event.
         *  - We have configured DIO Interrupts to get routed to Interrupt Destination 0
         *    (Refer to the CSL_SRIO_SetDoorbellRoute API configuration in the SRIO Initialization)
         *  - We want this to mapped to Host Interrupt 8
         *
         *  Map the System Interrupt i.e. the Interrupt Destination 0 interrupt to the DIO ISR Handler. */
        CpIntc_dispatchPlug(CSL_CIC0_SRIO_INTDST0, myDIOIsr, (UArg)hAppManagedSrioDrv, TRUE);

        /* SRIO DIO: Configuration is for CPINTC0. We map system interrupt 112 to Host Interrupt 8. */
        CpIntc_mapSysIntToHostInt(0, CSL_CIC0_SRIO_INTDST0, 8);

        /* SRIO DIO: Enable the Host Interrupt. */
        CpIntc_enableHostInt(0, 8);

        /* SRIO DIO: Get the event id associated with the host interrupt. */
        eventId = CpIntc_getEventId(8);

        /* SRIO DIO: Plug the CPINTC Dispatcher. */
        EventCombiner_dispatchPlug (eventId, CpIntc_dispatch, 8, TRUE);
    }else{
        ;
    }
#endif

    /* Create the DIO Management Socket. */
    //mgmtSocket = createMgmtSocket ();
#if 1
    re = createControlSocket();
    if(re < 0)
        return -1;
#endif
    return 0;
}

int32_t SrioDevice_init (void)
{
    CSL_SrioHandle      hSrio;
    int32_t             i;
    SRIO_PE_FEATURES    peFeatures;
    SRIO_OP_CAR         opCar;
    Qmss_QueueHnd       queueHnd;
    uint8_t             isAllocated;
    uint32_t            gargbageQueue[] = { GARBAGE_LEN_QUEUE,  GARBAGE_TOUT_QUEUE,
                                            GARBAGE_RETRY_QUEUE,GARBAGE_TRANS_ERR_QUEUE,
                                            GARBAGE_PROG_QUEUE, GARBAGE_SSIZE_QUEUE };
    uint32_t            srioIDMask =  0xFF;  //8bit ID
    uint32_t            srio_primary_ID = srio_device_ID1;
    uint32_t            srio_secondary_ID = srio_device_ID3;


    /* Get the CSL SRIO Handle. */
    hSrio = CSL_SRIO_Open (0);
    if (hSrio == NULL)
        return -1;

    /* Enable reception of packets */
    hSrio->RIO_PCR = (hSrio->RIO_PCR & 0x7) | CSL_SRIO_RIO_PCR_RESTORE_MASK;

    /* Disable the SRIO Global block */
    CSL_SRIO_GlobalDisable (hSrio);

    /* Disable each of the individual SRIO blocks. */
    for(i = 0; i <= 9; i++)
        CSL_SRIO_DisableBlock (hSrio, i);

    /* Set boot complete to be 0; we are not done with the initialization. */
    CSL_SRIO_SetBootComplete (hSrio, 0);

    /* Set the sRIO shadow registers for 9/3/2/2 */
    CSL_SRIO_SetLSUShadowRegs (hSrio,0x19,0x19);

    CSL_SRIO_SetMAUSwappingMode(hSrio,0);
    CSL_SRIO_SetLSUSwappingMode(hSrio,0);
    CSL_SRIO_SetTXURXUSwappingMode(hSrio,0);

    CSL_SRIO_SetSupervisorPerms(hSrio, 0x00AD, 0xAD);

    /* Now enable the SRIO block and all the individual blocks also. */
    CSL_SRIO_GlobalEnable (hSrio);
    for (i = 0; i <= 9; i++)
        CSL_SRIO_EnableBlock (hSrio,i);

    if (srio_work_mode == srio_Loopback_mode)
    {
        /* Configure SRIO to operate in Loopback mode. */
        CSL_SRIO_SetLoopbackMode (hSrio,0);
        CSL_SRIO_SetLoopbackMode (hSrio,1);
        CSL_SRIO_SetLoopbackMode (hSrio,2);
        CSL_SRIO_SetLoopbackMode (hSrio,3);
    }
    else
    {
        /* Configure SRIO to operate in Normal mode. */
        CSL_SRIO_SetNormalMode (hSrio,0);
        CSL_SRIO_SetNormalMode (hSrio,1);
        CSL_SRIO_SetNormalMode (hSrio,2);
        CSL_SRIO_SetNormalMode (hSrio,3);
    }

    /* Enable Automatic Priority Promotion of response packets. */
    CSL_SRIO_EnableAutomaticPriorityPromotion (hSrio);

    /* Set the SRIO Prescalar select to operate in the range of 44.7 to 89.5 */
    CSL_SRIO_SetPrescalarSelect (hSrio, 0);

    /* Unlock the Boot Configuration Kicker */
    CSL_BootCfgUnlockKicker ();

    if (setEnableSrioPllRxTx(hSrio, srio_refClockMhz, srio_laneSpeedGbps, srio_work_mode) < 0)
        return -1;
#if !defined(DEVICE_K2K) && !defined(DEVICE_K2H) && !defined(SOC_K2K) && !defined(SOC_K2H)
    /* Loop around until the SERDES PLL is locked. */
#if 0
    CSL_BootCfgSetSRIOSERDESRxConfig(0,0x00440495);
    CSL_BootCfgSetSRIOSERDESRxConfig(1,0x00440495);
    CSL_BootCfgSetSRIOSERDESRxConfig(2,0x00440495);
    CSL_BootCfgSetSRIOSERDESRxConfig(3,0x00440495);

    CSL_BootCfgSetSRIOSERDESTxConfig(0,0x00180795);
    CSL_BootCfgSetSRIOSERDESTxConfig(1,0x00180795);
    CSL_BootCfgSetSRIOSERDESTxConfig(2,0x00180795);
    CSL_BootCfgSetSRIOSERDESTxConfig(3,0x00180795);
#endif
    while (1)
    {
        uint32_t    status;

        /* Get the SRIO SERDES Status */
        CSL_BootCfgGetSRIOSERDESStatus (&status);
        if (status & 0x1)
            break;
    }
#endif
    /* Clear the LSU pending interrupts. */
    CSL_SRIO_ClearLSUPendingInterrupt (hSrio, 0xFFFFFFFF, 0xFFFFFFFF);

    /* Set the Device Information */
    CSL_SRIO_SetDeviceInfo (hSrio, srio_primary_ID, DEVICE_VENDOR_ID, DEVICE_REVISION);

    /* Set the Assembly Information */
    CSL_SRIO_SetAssemblyInfo (hSrio, DEVICE_ASSEMBLY_ID, DEVICE_ASSEMBLY_VENDOR_ID,
                             DEVICE_ASSEMBLY_REVISION, DEVICE_ASSEMBLY_INFO);

    /* Configure the processing element features*/
    peFeatures.isBridge                          = 0;
    peFeatures.isEndpoint                        = 1;
    peFeatures.isProcessor                       = 0;
    peFeatures.isSwitch                          = 0;
    peFeatures.isMultiport                       = 0;
    peFeatures.isFlowArbiterationSupported       = 0;
    peFeatures.isMulticastSupported              = 0;
    peFeatures.isExtendedRouteConfigSupported    = 0;
    peFeatures.isStandardRouteConfigSupported    = 1;
    peFeatures.isFlowControlSupported            = 1;
    peFeatures.isCRFSupported                    = 0;
    peFeatures.isCTLSSupported                   = 1;
    peFeatures.isExtendedFeaturePtrValid         = 1;
    peFeatures.numAddressBitSupported            = 1;
    CSL_SRIO_SetProcessingElementFeatures (hSrio, &peFeatures);

    /* Configure the source operation CAR */
    memset ((void *) &opCar, 0, sizeof (opCar));
    opCar.portWriteOperationSupport = 1;
    opCar.atomicClearSupport        = 1;
    opCar.atomicSetSupport          = 1;
    opCar.atomicDecSupport          = 1;
    opCar.atomicIncSupport          = 1;
    opCar.atomicTestSwapSupport     = 1;
    opCar.doorbellSupport           = 1;
    opCar.dataMessageSupport        = 1;
    opCar.writeResponseSupport      = 1;
    opCar.streamWriteSupport        = 1;
    opCar.writeSupport              = 1;
    opCar.readSupport               = 1;
    opCar.dataStreamingSupport      = 1;
    CSL_SRIO_SetSourceOperationCAR (hSrio, &opCar);

    /* Configure the destination operation CAR */
    memset ((void *) &opCar, 0, sizeof (opCar));
    opCar.portWriteOperationSupport  = 1;
    opCar.doorbellSupport            = 1;
    opCar.dataMessageSupport         = 1;
    opCar.writeResponseSupport       = 1;
    opCar.streamWriteSupport         = 1;
    opCar.writeSupport               = 1;
    opCar.readSupport                = 1;
    CSL_SRIO_SetDestOperationCAR (hSrio, &opCar);

    /* Set the 16 bit and 8 bit identifier for the SRIO Device. */
    CSL_SRIO_SetDeviceIDCSR (hSrio, DSP_SRIO_8BIT_DEVICE_ID, DSP_SRIO_16BIT_DEVICE_ID);

    /* Enable TLM Base Routing Information for Maintainance Requests & ensure that
     * the BRR's can be used by all the ports. */
    CSL_SRIO_SetTLMPortBaseRoutingInfo (hSrio, 0, 1, 1, 1, 0);
    /* Only add additional route if doing core to core on the same board */
    if (!srio_isBoardToBoard)
    CSL_SRIO_SetTLMPortBaseRoutingInfo (hSrio, 0, 2, 1, 1, 0);

    /* Configure the Base Routing Register to ensure that all packets matching the
     * Device Identifier & the Secondary Device Id are admitted. */
    CSL_SRIO_SetTLMPortBaseRoutingPatternMatch (hSrio, 0, 1, srio_primary_ID, srioIDMask);
    /* Only add additional route if doing core to core on the same board */
    if (!srio_isBoardToBoard)
       CSL_SRIO_SetTLMPortBaseRoutingPatternMatch (hSrio, 0, 2, srio_secondary_ID, srioIDMask);

    /* We need to open the Garbage collection queues in the QMSS. This is done to ensure that
     * these queues are not opened by another system entity. */
#if 0
    for (i = 0; i < 6; i++)
    {
        /* Open the Garabage queues */
        queueHnd = Qmss_queueOpen (Qmss_QueueType_GENERAL_PURPOSE_QUEUE, gargbageQueue[i], &isAllocated);
        if (queueHnd < 0)
            return -1;

        /* Make sure the queue has not been opened already; we dont the queues to be shared by some other
         * entity in the system. */
        if (isAllocated > 1)
            return -1;
    }
#endif
    /* Set the Transmit Garbage Collection Information. */
    CSL_SRIO_SetTxGarbageCollectionInfo (hSrio, GARBAGE_LEN_QUEUE, GARBAGE_TOUT_QUEUE,
                                         GARBAGE_RETRY_QUEUE, GARBAGE_TRANS_ERR_QUEUE,
                                         GARBAGE_PROG_QUEUE, GARBAGE_SSIZE_QUEUE);

    /* Set the Host Device Identifier. */
    CSL_SRIO_SetHostDeviceID (hSrio, srio_primary_ID);

    /* Configure the component tag CSR */
    CSL_SRIO_SetCompTagCSR (hSrio, 0x00000000);

    /* Configure the PLM for all the ports. */
    for (i = 0; i < 4; i++)
    {
        /* Set the PLM Port Silence Timer. */
        CSL_SRIO_SetPLMPortSilenceTimer (hSrio, i, 0x2);

        /* TODO: We need to ensure that the Port 0 is configured to support both
         * the 2x and 4x modes. The Port Width field is read only. So here we simply
         * ensure that the Input and Output ports are enabled. */
        CSL_SRIO_EnableInputPort (hSrio, i);
        CSL_SRIO_EnableOutputPort (hSrio, i);

        /* Set the PLM Port Discovery Timer. */
        CSL_SRIO_SetPLMPortDiscoveryTimer (hSrio, i, 0x2);

        /* Reset the Port Write Reception capture. */
        CSL_SRIO_SetPortWriteReceptionCapture (hSrio, i, 0x0);
    }

    /* Set the Port link timeout CSR */
    // CSL_SRIO_SetPortLinkTimeoutCSR (hSrio, 0x000FFF);
    CSL_SRIO_SetPortLinkTimeoutCSR (hSrio, 0xFF0FFF);
    CSL_SRIO_SetPortResponseTimeoutCSR (hSrio, 0xFF0FFF);

    /* Set the Port General CSR: Only executing as Master Enable */
    CSL_SRIO_SetPortGeneralCSR (hSrio, 0, 1, 0);

    /* Clear the sticky register bits. */
    CSL_SRIO_SetLLMResetControl (hSrio, 1);

    /* Set the device id to be 0 for the Maintenance Port-Write operation
     * to report errors to a system host. */
    CSL_SRIO_SetPortWriteDeviceId (hSrio, 0x0, 0x0, 0x0);

    /* Set the Data Streaming MTU */
    CSL_SRIO_SetDataStreamingMTU (hSrio, 64);

    /* Configure the path mode for the ports. */
    if (setSrioLanes(hSrio, srio_lanesMode) < 0)
        return -1;

    /* Set the LLM Port IP Prescalar. */
    //CSL_SRIO_SetLLMPortIPPrescalar (hSrio, 0x21);
    CSL_SRIO_SetLLMPortIPPrescalar (hSrio, 0x1F);

    /* Configure the ingress watermarks */
    for (i = 0; i < 4; i++)
    {
        CSL_SRIO_SetPBMPortIngressPriorityWatermark (hSrio, i, 0, 0x24, 0x24);
        CSL_SRIO_SetPBMPortIngressPriorityWatermark (hSrio, i, 1, 0x1B, 0x1B);
        CSL_SRIO_SetPBMPortIngressPriorityWatermark (hSrio, i, 2, 0x12, 0x12);
        CSL_SRIO_SetPBMPortIngressPriorityWatermark (hSrio, i, 3, 0x9, 0x9);
    }

    /* Disable interrupt pacing for all interrupt destinations. */
    for (i = 0; i < 24; i++)
        CSL_SRIO_DisableInterruptPacing (hSrio, i);

    /* Set all the queues 0 to operate at the same priority level and to send packets onto Port 0 */
    for (i =0 ; i < 16; i++)
        CSL_SRIO_SetTxQueueSchedInfo (hSrio, i, 0, 0);

#if 0
    /* Set the Doorbell route to determine which routing table is to be used
     * This configuration implies that the Interrupt Routing Table is configured as
     * follows:-
     *  Interrupt Destination 0 - INTDST 16
     *  Interrupt Destination 1 - INTDST 17
     *  Interrupt Destination 2 - INTDST 18
     *  Interrupt Destination 3 - INTDST 19 */
    CSL_SRIO_SetDoorbellRoute (hSrio, 0);
#else
    /* Set the Doorbell route to determine which routing table is to be used
     * This configuration implies that the Interrupt Routing Table is configured as
     * follows:-
     *  Interrupt Destination 0 - INTDST 0
     *  Interrupt Destination 1 - INTDST 1
     *  Interrupt Destination 2 - INTDST 2
     *  Interrupt Destination 3 - INTDST 3 */
    CSL_SRIO_SetDoorbellRoute (hSrio, 1);
#endif

    /* Route the Doorbell interrupts.
     *  Doorbell Register 0 - All 16 Doorbits are routed to Interrupt Destination 0.
     *  Doorbell Register 1 - All 16 Doorbits are routed to Interrupt Destination 1.
     *  Doorbell Register 2 - All 16 Doorbits are routed to Interrupt Destination 2.
     *  Doorbell Register 3 - All 16 Doorbits are routed to Interrupt Destination 3. */
    for (i = 0; i < 16; i++)
    {
        CSL_SRIO_RouteDoorbellInterrupts (hSrio, 0, i, 0);
        CSL_SRIO_RouteDoorbellInterrupts (hSrio, 1, i, 1);
        CSL_SRIO_RouteDoorbellInterrupts (hSrio, 2, i, 2);
        CSL_SRIO_RouteDoorbellInterrupts (hSrio, 3, i, 3);
    }

    /* Enable the peripheral. */
    CSL_SRIO_EnablePeripheral (hSrio);

    /* Configuration has been completed. */
    CSL_SRIO_SetBootComplete (hSrio, 1);


    if (displaySrioLanesStatus(hSrio) < 0)
        return -1;

    /* Initialization has been completed. */
    return 0;
}


static int32_t enable_srio (void)
{
    /* Set SRIO Power domain to ON */
    CSL_PSC_enablePowerDomain (CSL_PSC_PD_SRIO);

    /* Enable the clocks too for SRIO */
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_SRIO, PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (CSL_PSC_PD_SRIO);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_SRIO));

    /* Return SRIO PSC status */
    if ((CSL_PSC_getPowerDomainState(CSL_PSC_PD_SRIO) == PSC_PDSTATE_ON) &&
        (CSL_PSC_getModuleState (CSL_PSC_LPSC_SRIO) == PSC_MODSTATE_ENABLE))
    {
        /* SRIO ON. Ready for use */
        return 0;
    }
    else
    {
        /* SRIO Power on failed. Return error */
        return -1;
    }
}


/**
 *  @b Description
 *  @n
 *      Application registered DIO ISR.
 *
 *  @retval
 *      Not Applicable.
 */
void myDIOIsr(UArg argument)
{
    uint8_t     intDstDoorbell[4];

    /* The Interrupt Destination Decode registers which need to be looked into.
     * Please refer to the SRIO Device Initialization code. */
    intDstDoorbell[0] = 0x0;
    intDstDoorbell[1] = 0x1;
    intDstDoorbell[2] = 0x2;
    intDstDoorbell[3] = 0x3;

    /* Pass the control to the driver DIO ISR handler. */
    Srio_dioCompletionIsr ((Srio_DrvHandle)argument, intDstDoorbell);
    return;
}

Int  createControlSocket(Void)
{
    Srio_SockBindAddrInfo   bindInfo;

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


    fpga0ControlSocket = Srio_sockOpen (hAppManagedSrioDrv, Srio_SocketType_DIO, TRUE);
    if (fpga0ControlSocket == NULL)
    {
        System_printf ("Error: DIO Control Socket open failed\n");
        return -1;
    }

    fpga1ControlSocket = Srio_sockOpen (hAppManagedSrioDrv, Srio_SocketType_DIO, TRUE);
    if (fpga1ControlSocket == NULL)
    {
        System_printf ("Error: DIO Control Socket open failed\n");
        return -1;
    }

    bindInfo.dio.outPortID      = 0;
    /* Bind the DIO socket. */
    if (Srio_sockBind (fpga0ControlSocket, &bindInfo) < 0)
    {
       System_printf ("Error: Binding the DIO Control Socket failed.\n");
       return -1;
    }

    bindInfo.dio.outPortID      = 1;
    /* Bind the DIO socket. */
    if (Srio_sockBind (fpga1ControlSocket, &bindInfo) < 0)
    {
       System_printf ("Error: Binding the DIO Control Socket failed.\n");
       return -1;
    }

    return 0;
}


Int srioSendData(uint8_t port, Void *buf, Int len, srioSendSet pa)
{
    Srio_SockHandle         controlSocket;
    Srio_SockAddrInfo       to;
    int32_t  re;

#if 0
    Srio_SockBindAddrInfo   bindInfo;

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
    bindInfo.dio.outPortID      = port;
#endif

    if(port == SRIO_PORT_0){
        controlSocket = fpga0ControlSocket;
        to.dio.dstID         = srio_device_ID2;
    }else{
        controlSocket = fpga1ControlSocket;
        to.dio.dstID         = srio_device_ID3;
    }

    switch(pa){
    case srio_Send_Data: to.dio.rapidIOLSB = 1024; break;
    case srio_Send_Param: to.dio.rapidIOLSB = 0; break;
    case srio_Send_ReadIndex: to.dio.rapidIOLSB = 32;break;
    default : break;
    }

    to.dio.rapidIOMSB    = 0x0;
    to.dio.ttype         = Srio_Ttype_Write_NWRITE;
    to.dio.ftype         = Srio_Ftype_SWRITE;

#if 0
    controlSocket = Srio_sockOpen (hAppManagedSrioDrv, Srio_SocketType_DIO, TRUE);
    if (controlSocket == NULL)
    {
        System_printf ("Error: DIO Control Socket open failed\n");
        return -1;
    }

    if (Srio_sockBind (controlSocket, &bindInfo) < 0)
    {
       System_printf ("Error: Binding the DIO Control Socket failed.\n");
       return -1;
    }
#endif
    re = Srio_sockSend (controlSocket, buf, len, &to);
    if (re < 0)
    {
        System_printf ("Error: Unable to send RX dropped packet message over DIO socket\n");
        return -1;
    }

    //sendMgmtPingReply();

  //  re = Srio_sockClose (controlSocket);

    return 0;
}





