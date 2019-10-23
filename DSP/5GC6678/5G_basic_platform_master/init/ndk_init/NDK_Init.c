/*
 * NDK_Init.c
 *
 *  Created on: 2019Äê10ÔÂ14ÈÕ
 *      Author: Pu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* BIOS6 include */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

#include <ti/ndk/inc/netmain.h>

#include <ti/csl/csl_chipAux.h>
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>
#include <ti/ndk/inc/_stack.h>
#include <ti/ndk/inc/tools/console.h>
#include <ti/ndk/inc/tools/servers.h>

/* PASS RL file */
#include <ti/csl/cslr_pa_ss.h>

#include <ti/drv/pa/pa.h>

#include <ti/drv/QMSS/QMSS_drv.h>
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>
#include <ti/drv/cppi/cppi_osal.h>


#include <qmss_init.h>
#include <xdc/runtime/System.h>

#include <nimu_cppi_qmss_iface.h>


/* PA definitions */
#define     MAX_NUM_L2_HANDLES          10
#define     MAX_NUM_L3_HANDLES          20
#define     MAX_NUM_L4_HANDLES          40

#define     BUFSIZE_PA_INST             512
#define     BUFSIZE_L2_TABLE            1000
#define     BUFSIZE_L3_TABLE            4000


#define CACHE_LINESZ (128)

#define NIMU_testLog printf



char *HostName    = "tidsp";
char *LocalIPAddr = "192.168.1.4";
char *LocalIPMask = "255.255.255.0";    // Not used when using DHCP
char *GatewayIP   = "192.168.1.1";    // Not used when using DHCP
char *DomainName  = "demo.net";         // Not used when using DHCP
char *DNSServer   = "0.0.0.0";          // Used when set to anything but zero

// Simulator EMAC Switch does not handle ALE_LEARN mode, so please configure the
// MAC address of the PC where you want to launch the webpages and initiate PING to NDK */

Uint8 clientMACAddress [6] = {0xd4, 0xbe, 0xd9, 0x3d, 0xb6, 0xb8}; /* MAC address for my PC */

#if 0
int dtask_udp_hello( SOCKET s, uint32_t unused )
{
    struct sockaddr_in sin1;
    struct timeval     to;
    int                i,tmp;
    char               *pBuf;
    void*             hBuffer;

    (void)unused;

    // Configure our socket timeout to be 3 seconds
    to.tv_sec  = 3;
    to.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

    for(;;)
    {
        tmp = sizeof( sin1 );
        i = (int)recvncfrom( s, (void **)&pBuf, 0, &sin1, &tmp, &hBuffer );

        // Spit any data back out
        if( i >= 0 )
        {
            sendto( s, pBuf, i, 0, &sin1, sizeof(sin1) );
            recvncfree( hBuffer );
        }
        else
            break;
    }

    // Since the socket is still open, return "1"
    // (we need to leave UDP sockets open)
    return(1);
}


static void* hHello=0;

//
// NIMU_testNetworkOpen
//
// This function is called after the configuration has booted
//
static void NIMU_testNetworkOpen()
{
    // Create our local server
    hHello = DaemonNew( SOCK_DGRAM, 0, 7, dtask_udp_hello,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 1 );
}


//
// NIMU_testNetworkClose
//
// This function is called when the network is shutting down,
// or when it no longer has any IP addresses assigned to it.
//
static void NIMU_testNetworkClose()
{
    DaemonFree( hHello );

    // Kill any active console
    ConsoleClose();
}
#endif

//
// NIMU_testNetworkIpAddr
//
// This function is called whenever an IP address binding is
// added or removed from the system.
//
static void NIMU_testNetworkIpAddr( uint32_t IPAddr, uint32_t IfIdx, uint32_t fAdd )
{
    uint32_t IPTmp;

    if( fAdd )
        printf("Network Added: ");
    else
        printf("Network Removed: ");

    // Print a message
    IPTmp = NDK_ntohl( IPAddr );
    printf("If-%d:%d.%d.%d.%d\n", IfIdx,
            (uint8_t)(IPTmp>>24)&0xFF, (uint8_t)(IPTmp>>16)&0xFF,
            (uint8_t)(IPTmp>>8)&0xFF, (uint8_t)IPTmp&0xFF );
}



int32_t NDK_config(void)
{
    int32_t re;
    int               rc;
    int               i;
    void *            hCfg;
    CI_SERVICE_TELNET telnet;
    CI_SERVICE_HTTP   http;

    NIMU_QMSS_CFG_T      qmss_cfg;
    NIMU_CPPI_CFG_T      cppi_cfg;


    qmss_cfg.max_num_desc       = MAX_NUM_NIMU_DESC;
    qmss_cfg.desc_size          = MAX_DESC_SIZE;
    qmss_cfg.mem_region         = Qmss_MemRegion_MEMORY_REGION1;
    if (NIMU_initQmss (&qmss_cfg) != 0)
    {
        NIMU_testLog ("Failed to initialize the QMSS subsystem \n");
        return -1;
    }
    else
    {
        NIMU_testLog ("QMSS successfully initialized \n");
    }


    cppi_cfg.dma_num            = Cppi_CpDma_PASS_CPDMA;
    cppi_cfg.num_tx_queues      = NUM_PA_TX_QUEUES;
    cppi_cfg.num_rx_channels    = NUM_PA_RX_CHANNELS;
    if (NIMU_initCppi (&cppi_cfg) != 0)
    {
        NIMU_testLog ("Failed to initialize CPPI subsystem \n");
        return -1;
    }
    else
    {
        NIMU_testLog ("CPPI successfully initialized \n");
    }


    re = Nimu_testInitPASS();
    if(re != 0){
        return -1;
    }

    rc = NC_SystemOpen( NC_PRIORITY_LOW, NC_OPMODE_INTERRUPT );
    if( rc )
    {
        NIMU_testLog("NC_SystemOpen Failed (%d)\n",rc);
        return -2;
    }

    hCfg = CfgNew();
    if( !hCfg )
    {
        NIMU_testLog("Unable to create configuration\n");
        return -3;
    }

    // We better validate the length of the supplied names
    if( strlen( DomainName ) >= CFG_DOMAIN_MAX ||
        strlen( HostName ) >= CFG_HOSTNAME_MAX )
    {
        NIMU_testLog("Names too long\n");
        return -4;
    }

    // Add our global hostname to hCfg (to be claimed in all connected domains)
    CfgAddEntry( hCfg, CFGTAG_SYSINFO, CFGITEM_DHCP_HOSTNAME, 0,
                 strlen(HostName), (uint8_t *)HostName, 0 );


    CI_IPNET NA;
    CI_ROUTE RT;
    uint32_t      IPTmp;

    NIMU_testLog("StackTest: using localIp\n");
    // Setup manual IP address
    bzero( &NA, sizeof(NA) );
    NA.IPAddr  = inet_addr(LocalIPAddr);
    NA.IPMask  = inet_addr(LocalIPMask);
    strcpy( NA.Domain, DomainName );
    NA.NetType = 0;

    // Add the address to interface 1
    CfgAddEntry( hCfg, CFGTAG_IPNET, 1, 0,
                       sizeof(CI_IPNET), (uint8_t *)&NA, 0 );

    // Add the default gateway. Since it is the default, the
    // destination address and mask are both zero (we go ahead
    // and show the assignment for clarity).
    bzero( &RT, sizeof(RT) );
    RT.IPDestAddr = 0;
    RT.IPDestMask = 0;
    RT.IPGateAddr = inet_addr(GatewayIP);

    // Add the route
    CfgAddEntry( hCfg, CFGTAG_ROUTE, 0, 0,
                       sizeof(CI_ROUTE), (uint8_t *)&RT, 0 );

    // Manually add the DNS server when specified
    IPTmp = inet_addr(DNSServer);
    if( IPTmp )
        CfgAddEntry( hCfg, CFGTAG_SYSINFO, CFGITEM_DHCP_DOMAINNAMESERVER,
                     0, sizeof(IPTmp), (uint8_t *)&IPTmp, 0 );


    //
    // Configure IPStack/OS Options
    //

    // We don't want to see debug messages less than WARNINGS
    rc = DBG_WARN;
    CfgAddEntry( hCfg, CFGTAG_OS, CFGITEM_OS_DBGPRINTLEVEL,
                 CFG_ADDMODE_UNIQUE, sizeof(uint32_t), (uint8_t *)&rc, 0 );

    //
    // This code sets up the TCP and UDP buffer sizes
    // (Note 8192 is actually the default. This code is here to
    // illustrate how the buffer and limit sizes are configured.)
    //

    // UDP Receive limit
    rc = 8192;
    CfgAddEntry( hCfg, CFGTAG_IP, CFGITEM_IP_SOCKUDPRXLIMIT,
                 CFG_ADDMODE_UNIQUE, sizeof(uint32_t), (uint8_t *)&rc, 0 );


    rc = 4096; // increase stack size
    CfgAddEntry(hCfg, CFGTAG_OS, CFGITEM_OS_TASKSTKBOOT,
    CFG_ADDMODE_UNIQUE, sizeof(uint32_t), (uint8_t *)&rc, 0 );


    // Boot the system using this configuration
    //
    // We keep booting until the function returns 0. This allows
    // us to have a "reboot" command.
    //
    do
    {
        rc = NC_NetStart( hCfg, NULL, NULL, NIMU_testNetworkIpAddr );
    } while( rc != 0 );

    CfgFree( hCfg );

    NC_SystemClose();

    return 0;
}




