/**
 *   @file  c6678/src/TransportQmss_device.c
 *
 *   @brief   
 *      This file contains the device specific configuration data
 *      for QMSS IPC Transport.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2015, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  \par
*/

/* QMSS includes */
#include <ti/drv/qmss/qmss_qm.h>

/* CSL includes */
#include <ti/csl/csl_qm_queue.h>

/* Transport QMSS includes */
#include <ti/transport/ipc/c66/qmss/TransportQmss.h>

#define MAX_DSP_CORES      8
#define MAX_PDSPS          2
#define MAX_ACCUM_CHANNELS 32

/* Contains the system event to accumulator channel mappings for INTD1 for
 * each DSP core */
static UInt8 intd1ChanToEventMap[MAX_DSP_CORES * MAX_ACCUM_CHANNELS] = {
    /* Core 0 mappings */
    48, 0, 0, 0, 0, 0, 0, 0,49, 0, 0, 0, 0, 0, 0, 0,
    50, 0, 0, 0, 0, 0, 0, 0,51, 0, 0, 0, 0, 0, 0, 0,
    /* Core 1 mappings */
     0,48, 0, 0, 0, 0, 0, 0, 0,49, 0, 0, 0, 0, 0, 0,
     0,50, 0, 0, 0, 0, 0, 0, 0,51, 0, 0, 0, 0, 0, 0,
    /* Core 2 mappings */
     0, 0,48, 0, 0, 0, 0, 0, 0, 0,49, 0, 0, 0, 0, 0,
     0, 0,50, 0, 0, 0, 0, 0, 0, 0,51, 0, 0, 0, 0, 0,
    /* Core 3 mappings */
     0, 0, 0,48, 0, 0, 0, 0, 0, 0, 0,49, 0, 0, 0, 0,
     0, 0, 0,50, 0, 0, 0, 0, 0, 0, 0,51, 0, 0, 0, 0,
    /* Core 4 mappings */
     0, 0, 0, 0,48, 0, 0, 0, 0, 0, 0, 0,49, 0, 0, 0,
     0, 0, 0, 0,50, 0, 0, 0, 0, 0, 0, 0,51, 0, 0, 0,
    /* Core 5 mappings */
     0, 0, 0, 0, 0,48, 0, 0, 0, 0, 0, 0, 0,49, 0, 0,
     0, 0, 0, 0, 0,50, 0, 0, 0, 0, 0, 0, 0,51, 0, 0,
    /* Core 6 mappings */
     0, 0, 0, 0, 0, 0,48, 0, 0, 0, 0, 0, 0, 0,49, 0,
     0, 0, 0, 0, 0, 0,50, 0, 0, 0, 0, 0, 0, 0,51, 0,
    /* Core 7 mappings */
     0, 0, 0, 0, 0, 0, 0,48, 0, 0, 0, 0, 0, 0, 0,49,
     0, 0, 0, 0, 0, 0, 0,50, 0, 0, 0, 0, 0, 0, 0,51
};

/* PDSP configuration */
static TransportQmss_pdspCfg pdspCfg[MAX_PDSPS] = {
    {0, &intd1ChanToEventMap[0]}, /* PDSP 1 */
    {0, &intd1ChanToEventMap[0]}, /* PDSP 2 */
};

/* CIC0 secondary interrupt to QMSS Qpend queue mappings */
static TransportQmss_intcQInfo cic0QInfo[] = {
    { 652,  47,  1},
    { 653,  91,  1},
    { 654,  93,  1},
    { 655,  95,  1},
    { 656,  97,  1},
    { 657, 151,  9},
    /* Last entry must be {-1, 0, 0} to signify end of list */
    {  -1,   0,  0}
};

/* CIC1 secondary interrupt to QMSS Qpend queue mappings */
static TransportQmss_intcQInfo cic1QInfo[] = {
    { 658,  47,  1},
    { 659,  91,  1},
    { 660,  93,  1},
    { 661,  95,  1},
    { 662,  97,  1},
    { 663, 151,  9},
    /* Last entry must be {-1, 0, 0} to signify end of list */
    {  -1,   0,  0}
};

/* DSP to INTC configurations */
static TransportQmss_dspIntcCfg dspIntcCfg[MAX_DSP_CORES] = {
    {0, &cic0QInfo[0]}, /* DSP 0 */
    {0, &cic0QInfo[0]}, /* DSP 1 */
    {0, &cic0QInfo[0]}, /* DSP 2 */
    {0, &cic0QInfo[0]}, /* DSP 3 */
    {1, &cic1QInfo[0]}, /* DSP 4 */
    {1, &cic1QInfo[0]}, /* DSP 5 */
    {1, &cic1QInfo[0]}, /* DSP 6 */
    {1, &cic1QInfo[0]}  /* DSP 7 */
};

/* This table maps a DSP core system (or GEM) event to a CIC Host interrupt
 * number.  The mappings are pulled directly from Table 7-32 System Event
 * Mapping in tms320c6678.pdf */
static TransportQmss_hostIntMod hostIntMods[] = {
    { 21, 32, 11},
    { 22, 33, 11},
    { 23, 34, 11},
    { 24, 35, 11},
    { 25, 36, 11},
    { 26, 37, 11},
    { 27, 38, 11},
    { 28, 39, 11},
    { 29, 40, 11},
    { 30, 41, 11},
    { 31, 42, 11},
    { 62,  2,  8},
    { 63,  3,  8},
    { 92,  4,  8},
    { 93,  5,  8},
    { 94,  6,  8},
    { 95,  7,  8},
    {102,  0,  0},
    {103,  1,  0},
    {104,  8,  0},
    {105,  9,  0},
    {106, 16,  0},
    {107, 17,  0},
    {108, 24,  0},
    {109, 25,  0},
    /* Last entry must be {-1, 0, 0} to signify end of list */
    { -1,  0,  0}
};

/* TransportQmss initialization parameters */
TransportQmss_DeviceConfigParams qmssTransCfgParams =
{
    /* Maximum number of QMSS PDSPs */
    MAX_PDSPS,
    /* QMSS infrastructure queue block base */
    QMSS_INFRASTRUCTURE_QUEUE_BASE,
    /* Max QMSS infrastructure queues */
    QMSS_MAX_INFRASTRUCTURE_QUEUE,
    /* Number of accumulator channels on device */
    MAX_ACCUM_CHANNELS,
    /* Pointer to PDSP configuration table */
    &pdspCfg[0],
    /* Pointer to INTC configuration table for each DSP */
    &dspIntcCfg[0],
    /* Additive and multiplicative modifiers used to calculate System (GEM)
     * event to CIC Host interrupt mappings.  These modifiers are common across
     * all DSP cores */
    &hostIntMods[0]
};

