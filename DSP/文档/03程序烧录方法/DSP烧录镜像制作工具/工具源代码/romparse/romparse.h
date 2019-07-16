/*
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
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
*/
#ifndef _ROMPARSE_H
#define _ROMPARSE_H
/*************************************************************************************
 * FILE PURPOSE: Define boot data structures
 *************************************************************************************
 * FILE NAME: romparse.h
 *
 * DESCRIPTION: Defines the structures used to create the boot parameter
 *				table
 *
 *************************************************************************************/
 
/* tiboot.h defines the boot parameters structure that will be created */
typedef short BOOL;
#include "tiboot.h"

/* Boot modes for Appleton */
#define BOOT_MODE_ETH               10
#define BOOT_MODE_RAPIDIO           20
#define BOOT_MODE_PCIE              30
#define BOOT_MODE_I2C               40
#define BOOT_MODE_I2C_PASSIVE       41
#define BOOT_MODE_I2C_MASTER_WRITE  42
#define BOOT_MODE_SPI               50
#define BOOT_MODE_VUSR              60
#define BOOT_MODE_EMIF25            70
#define BOOT_MODE_NAND              80
#define BOOT_MODE_BOOTP_TFTP        90
#define BOOT_MODE_SLEEP            100
#define BOOT_MODE_UART             110


typedef int bool;
#define FALSE 0
#define TRUE  1

/* Secure boot temporarily not supported */
#define chipSleepUntilEvent_secure(x)       ;


/* Define the number of boot parameter tables that will be put on the rom */
#define NUM_BOOT_PARAM_TABLES       8
#define NUM_SEC_BOOT_PARAM_TABLES    4

/* Define the size reserved for the PCI configuration table */
#define PCI_EEAI_PARAM_SIZE    0x00

/* Define a structure mapping the boot parameter table number to a program file
 * to an eeprom byte address */
#define MAX_FNAME_LEN        132
#define MAX_DATA_LEN_32bit   32768*1024
typedef struct {
  char fname[MAX_FNAME_LEN];
  int  sizeBytes;
  int  addressBytes;
  unsigned int data[MAX_DATA_LEN_32bit];
} progFile_t;

/* Define the PCI parameter structure */
#define PCI_DATA_LEN_32bit  8
typedef struct {
  char fname[MAX_FNAME_LEN];
  int sizeBytes;
  int addressBytes;
  unsigned int data[PCI_DATA_LEN_32bit];
} pciFile_t;


/* Secure block sizes */
#define KEYSIGN_SIZE_BYTES      0x280
#define SEC_TABLE_SIZE_BYTES    0x200



#endif /* ROMPARSE_H */
