/*
*********************************************************************************************************
*                                                uC/FS
*                                      The Embedded File System
*
*                         (c) Copyright 2008-2019; Silicon Laboratories Inc.,
*                                400 W. Cesar Chavez, Austin, TX 78701
*
*                   All rights reserved. Protected by international copyright laws.
*
*                  Your use of this software is subject to your acceptance of the terms
*                  of a Silicon Labs Micrium software license, which can be obtained by
*                  contacting info@micrium.com. If you do not agree to the terms of this
*                  license, you may not use this software.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available. Your honesty is greatly appreciated.
*
*                    You can find our product's documentation at: doc.micrium.com
*
*                          For more information visit us at: www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      FILE SYSTEM DEVICE DRIVER
*
*                                          NOR FLASH DEVICES
*                      ST MICROELECTRONICS M25 SERIAL NOR PHYSICAL-LAYER DRIVER
*
* Filename : fs_dev_nor_stm25.h
* Version  : v4.07.06
*********************************************************************************************************
* Note(s)  : (1) Supports Numonyx/ST's M25 & M45 serial NOR flash memories, as described in various
*                datasheets at Numonyx (http://www.numonyx.com).  This driver has been tested with
*                or should work with the following devices :
*
*                    M25P05-A [*]     M25PE10 [*]     M25PX80     M45PE10
*                    M25P10-A         M25PE20 [*]     M25PX16     M45PE20
*                    M25P20   [*]     M25PE40 [*]     M25PX32     M45PE40
*                    M25P40   [*]     M25PE80 [*]     M25PX64     M45PE80
*                    M25P80           M25PE16 [*]                 M45PE16
*                    M25P16   [*]
*                    M25P32   [*]
*                    M25P64   [*]
*                    M25P128
*
*                         [*} Devices tested
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  FS_DEV_NOR_STM25_PRESENT
#define  FS_DEV_NOR_STM25_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   FS_DEV_NOR_STM25_MODULE
#define  FS_DEV_NOR_STM25_EXT
#else
#define  FS_DEV_NOR_STM25_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "../../../Source/fs_dev.h"
#include  "../fs_dev_nor.h"


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

extern  const  FS_DEV_NOR_PHY_API  FSDev_NOR_STM25;


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of NOR STM25 module include.                     */
