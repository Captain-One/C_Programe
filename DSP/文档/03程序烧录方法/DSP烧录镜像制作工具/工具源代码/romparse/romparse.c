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
/*************************************************************************************
 * FILE PURPOSE: Create an I2C rom with multiple boot parameter sections and
 *               programs
 *************************************************************************************
 * FILE NAME: romparse.c
 *
 * DESCRIPTION: Creates a ccs hex file which contains the i2c eprom boot parameter 
 *              tables as well as any code.
 *
 *************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "rparse.tab.h"
#include "romparse.h"
#include "secutil.h"

/*************************************************************************************
 * Definition: fixed i2c map locations
 *************************************************************************************/
#define PCI_PARAM_BASE  (NUM_BOOT_PARAM_TABLES * 0x80)
#define DATA_BASE       (PCI_PARAM_BASE + PCI_EEAI_PARAM_SIZE)

#define DATA_BASE_SECURE (NUM_SEC_BOOT_PARAM_TABLES * 0x480)



/*************************************************************************************
 * Declaration: The flex input file is assigned based on the command line
 *************************************************************************************/
extern FILE *yyin;

/*************************************************************************************
 * Declaration: Memory used for storing array input (for mac addresses)
 *************************************************************************************/
int pArray[100];
int nArray;

/*************************************************************************************
 * Declaration: Line currently being parsed
 *************************************************************************************/
int cline = 1;

/*************************************************************************************
 * Declaration: Secure boot enable
 *************************************************************************************/
bool secureBoot = FALSE;

/*************************************************************************************
 * Declaration: The default number of boot parameter tables is the maximum
 *************************************************************************************/
int num_boot_param_tables = NUM_BOOT_PARAM_TABLES;

/*************************************************************************************
 * Declaration: If PCI config is included
 *************************************************************************************/
int pciTable = 1;

/*************************************************************************************
 * Declaration: The flag which indicates that the length/checksum field is not 
 *              included in the output
 *************************************************************************************/
int noHdr = 0;

/*************************************************************************************
 * Declaration: The boot parameter tables. The current table is copied into position
 *              when the section parse is complete.
 *************************************************************************************/
BOOT_PARAMS_T boot_params[NUM_BOOT_PARAM_TABLES];
BOOT_PARAMS_T current_table;
int           ctable_index = -1;  /* Destination of current table */

/* Secure mode values */
char  aes_key_file[NUM_SEC_BOOT_PARAM_TABLES][MAX_FNAME_LEN];
char  rsa_key_file[NUM_SEC_BOOT_PARAM_TABLES][MAX_FNAME_LEN];
char key_sign_file[NUM_SEC_BOOT_PARAM_TABLES][MAX_FNAME_LEN];

char  cur_aes_key_file[MAX_FNAME_LEN];
char  cur_rsa_key_file[MAX_FNAME_LEN];
char cur_key_sign_file[MAX_FNAME_LEN];


/************************************************************************************
 * Declaration: The structure storing the program data files, and the number of
 *              programs used.
 ************************************************************************************/
progFile_t progFile[NUM_BOOT_PARAM_TABLES];
int        nProgFiles = 0;

/************************************************************************************
 * Declaration: The PCI parameter structure
 ************************************************************************************/
pciFile_t pciFile;
int       pciSet = 0;

/*************************************************************************************
 * Declaration: The next free address in the ROM for general data usage. For the
 *              start address there is room for the initial boot parameter tables, 
 *              plus room for the PCI eeai config. In secure mode the start is
 *              at the end of the encrypted parameter tables
 *************************************************************************************/
int romBase;

/*************************************************************************************
 * FUNCTION PURPOSE: flex/bison required support functions.
 *************************************************************************************
 * DESCRIPTION: yyerror and yywrap are required to support flex and/or bison parsing
 *              of the parameter description file. yyerror directly reports the
 *              error, yywrap is unused.
 *************************************************************************************/
void yyerror (char *s)
{
  fprintf (stderr, "flex/bison error is %s, line %d\n", s, cline);
} /* yyerror */

void yywrap (void)
{
} /* yywrap */

/*************************************************************************************
 * FUNCTION PURPOSE: Initialize a boot table
 *************************************************************************************
 * DESCRIPTION: Sets a boot parameter table to 0s
 *************************************************************************************/
void initTable (BOOT_PARAMS_T *current_table)
{
  memset (current_table, 0, sizeof(BOOT_PARAMS_T));
}

/**************************************************************************************
 * FUNCTION PURPOSE: Add two numbers in ones complement
 **************************************************************************************
 * DESCRIPTION: The ones complement addition of two values is returned
 **************************************************************************************/
unsigned short onesComplementAdd (unsigned short value1, unsigned short value2)
{
  unsigned int result;

  result = (unsigned int)value1 + (unsigned int)value2;

  result = (result >> 16) + (result & 0xFFFF); /* add in carry   */
  result += (result >> 16);                    /* maybe one more */
  return ((unsigned short)result);

} 


/*************************************************************************************
 * FUNCTION PURPOSE: Ones complement checksum over an array
 *************************************************************************************
 * DESCRIPTION: The ones complement checksum is computed
 *************************************************************************************/
unsigned short onesCompCheckSum (unsigned short *p_data, int len)
{
  unsigned short chksum = 0;

  while (len > 0)
  {
    chksum = onesComplementAdd(chksum, *p_data);
    p_data++;
    len--;
  }
  return chksum;
} 


/*************************************************************************************
 * FUNCTION PURPOSE: Complete a section
 *************************************************************************************
 * DESCRIPTION: The parser has detected a complete section. Copy the section into
 *              it's correct table location.
 *************************************************************************************/
void section (void)
{
  /* It's an error if no section value has been declared */
  if (ctable_index == -1)  {
    fprintf (stderr, "romparse: the section did not have a boot paramter index specified\n");
    exit (-1);
  }

  /* Make sure the table is in range */
  if (secureBoot == FALSE)  {

    if (ctable_index >= NUM_BOOT_PARAM_TABLES)  {
        fprintf (stderr, "romparse: The section index is too large (max %d)\n", NUM_BOOT_PARAM_TABLES-1);
        exit (-1);
    }

  }  else  {

    if (ctable_index >= NUM_SEC_BOOT_PARAM_TABLES)  {
        fprintf (stderr, "romparse: The section index is too large (max %d)\n", NUM_SEC_BOOT_PARAM_TABLES-1);
        exit (-1);
    }
  }


  /* The length must be set. Base it on the boot mode */
  switch (current_table.common.boot_mode)  {

    case BOOT_MODE_ETH: current_table.common.length = sizeof(BOOT_PARAMS_ETHERNET_T);
                        break;

    case BOOT_MODE_RAPIDIO: current_table.common.length = sizeof(BOOT_PARAMS_RIO_T);
                            break;

    case BOOT_MODE_PCIE: current_table.common.length = sizeof(BOOT_PARAMS_PCIE_T);
                         break;

    case BOOT_MODE_I2C:
    case BOOT_MODE_I2C_PASSIVE:
    case BOOT_MODE_I2C_MASTER_WRITE: current_table.common.length = sizeof(BOOT_PARAMS_I2C_T);
                                     break;

    case BOOT_MODE_SPI: current_table.common.length = sizeof(BOOT_PARAMS_SPI_T);
	                        break;

    case BOOT_MODE_VUSR: current_table.common.length = sizeof(BOOT_PARAMS_VUSR_T);
                         break;

    default: fprintf (stderr, "Boot mode %d unknown. Setting parameter table size to %d\n", sizeof(BOOT_PARAMS_T));
             current_table.common.length = sizeof(BOOT_PARAMS_T);
  }

  current_table.common.checksum = 0;


  /* Copy the table */
  memcpy (&boot_params[ctable_index], &current_table, sizeof (BOOT_PARAMS_T));
  initTable (&current_table);

  if (secureBoot)  {

    strcpy (aes_key_file[ctable_index],  cur_aes_key_file);
    strcpy (rsa_key_file[ctable_index],  cur_rsa_key_file);
    strcpy (key_sign_file[ctable_index], cur_key_sign_file);

    memset (cur_aes_key_file,  0, sizeof (cur_aes_key_file));
    memset (cur_rsa_key_file,  0, sizeof (cur_rsa_key_file));
    memset (cur_key_sign_file, 0, sizeof (cur_key_sign_file));

  }


  ctable_index = -1;

} /* section */

/***************************************************************************************
 * FUNCTION PURPOSE: Open a ccs hex file and read in the data.
 ***************************************************************************************
 * DESCRIPTION: Reads a ccs hex format data file, loads the file into the
 *              next program file structure. Returns the index of the just loaded
 *              table.
 ***************************************************************************************/
int openProgFile (char *fname)
{
  FILE *str;
  int a, b, c, d, e;
  int i;
  char iline[132];

  /* Store the file name */
  strcpy (progFile[nProgFiles].fname, fname);

  /* Open the data file */
  str = fopen (fname, "r");
  if (str == NULL)  {
    fprintf (stderr, "romparse: Could not open file %s\n", fname);
    exit (-1);
  }

  /* Put the section at the next available i2c rom address */
  progFile[nProgFiles].addressBytes = romBase;

  /* Read the one line ccs header. The length field in terms of lines */
  fgets (iline, 132, str);
  sscanf (iline, "%x %x %x %x %x", &a, &b, &c, &d, &e);
  progFile[nProgFiles].sizeBytes = e * 4; /* Length was in 4 byte words */

  /* Read in the data */
  for (i = 0; i < e; i++)  {
    fgets (iline, 132, str);
    sscanf (&(iline[2]), "%x", &((progFile[nProgFiles]).data[i]));
  }

  fclose (str);

  /* Update the next free rom base */
  romBase = romBase + progFile[nProgFiles].sizeBytes;

  i = nProgFiles;
  nProgFiles += 1;

  return (i);

} /* openProgFile */

/***************************************************************************************
 * FUNCTION PURPOSE: Load the PCI paramter section
 ***************************************************************************************
 * DESCRIPTION: Loads the PCI parameter section and stores it in the rom. */
int setPciParams (char *fname)
{
  FILE *str;
  int a, b, c, d, e;
  int i;
  char iline[132];
  char *z;

  if (pciSet)  {
    fprintf (stderr, "romparse: PCI parameters specified more then once\n");
    exit (-1);
  }

  /* the input string still contains the quotes. Remove them here */
  z = &fname[1];
  *strchr (z, '"') = '\0';

  /* Store the file name */
  strcpy (pciFile.fname, z);

  /* Open the data file */
  str = fopen (z, "r");
  if (str == NULL)  {
    fprintf (stderr, "romparse: Could not open pci file %s\n", fname);
    exit (-1);
  }

  /* The address of the pci params is currently fixed */
  pciFile.addressBytes = PCI_PARAM_BASE;

  /* Read the one line ccs header. The length field is in terms of lines */
  fgets (iline, 132, str);
  sscanf (iline, "%x %x %x %x %x", &a, &b, &c, &d, &e);
  pciFile.sizeBytes = e * 4;  /* Convert length to bytes */

  /* Read in the data */
  for (i = 0; i < e; i++)  {
    fgets (iline, 132, str);
    sscanf (&(iline[2]), "%x", &(pciFile.data[i]));
  }

  pciSet = 1;

  return (0);

} /* setPciParams */


/***************************************************************************************
 * FUNCTION PURPOSE: Store an array assignement
 ***************************************************************************************
 * DESCRIPTION: Stores an array value into the parameter table.
 ***************************************************************************************/
void assignArray (int field, int *array, int n)
{
  switch (field)  {

    case MAC_ADDR: 
            if (current_table.common.boot_mode != BOOT_MODE_ETH)  {
              fprintf (stderr, "Error (line %d): MAC_ADDR specified but current boot mode is not ethernet\n", __LINE__);
              exit (-1);
            }

            if (n != 6)  {
              fprintf (stderr, "Error (line %d): Invalid mac address specification\n", __LINE__);
              exit (-1);
            }
            current_table.eth.mac_addr_h = (array[0] << 8) | array[1];
            current_table.eth.mac_addr_m = (array[2] << 8) | array[3];
            current_table.eth.mac_addr_l = (array[4] << 8) | array[5];
            break;

    case MMAC_ADDR:
            if (current_table.common.boot_mode != BOOT_MODE_ETH)  {
              fprintf (stderr, "Error (line %d): MMAC_ADDR specified but current boot mode is not ethernet\n", __LINE__);
              exit (-1);
            }

            if (n != 6)  {
              fprintf (stderr, "Error (line %d): Invalid mac address specification\n", __LINE__);
              exit (-1);
            }
            current_table.eth.mmac_addr_h = (array[0] << 8) | array[1];
            current_table.eth.mmac_addr_m = (array[2] << 8) | array[3];
            current_table.eth.mmac_addr_l = (array[4] << 8) | array[5];
            break;

    case HMAC_ADDR:
            if (current_table.common.boot_mode != BOOT_MODE_ETH)  {
              fprintf (stderr, "Error (line %d): HMAC_ADDR specified but current boot mode is not ethernet\n", __LINE__);
              exit (-1);
            }

            if (n != 6)  {
              fprintf (stderr, "Error (line %d): Invalid mac address specification\n", __LINE__);
              exit (-1);
            }
            current_table.eth.hmac_addr_h = (array[0] << 8) | array[1];
            current_table.eth.hmac_addr_m = (array[2] << 8) | array[3];
            current_table.eth.hmac_addr_l = (array[4] << 8) | array[5];
            break;

    default:
        fprintf (stderr, "Error (line %d): assignArray called with invalid key value %d\n", __LINE__, field);
        exit (-1);
        break;

  }

}
 

/***************************************************************************************
 * FUNCTION PURPOSE: Store an assignment
 ***************************************************************************************
 * DESCRIPTION: Stores an assigned value into the current boot parameter table
 ***************************************************************************************/
void assignKeyVal (int field, int value)
{

  /* Common fields */
  if (field == BOOT_MODE)  {
    current_table.common.boot_mode = value;
    return;
  }
  if (field == PORT_NUM)  {
    current_table.common.portNum = value;
    return;
  }
  if (field == SWPLL_PREDIV)  {
    current_table.common.swPllCfg_lsw = current_table.common.swPllCfg_lsw & 0x00ff;
    current_table.common.swPllCfg_lsw = current_table.common.swPllCfg_lsw | ((value & 0x00ff) << 8);
    return;
  }
  if (field == SWPLL_MULT)  {
    current_table.common.swPllCfg_msw = current_table.common.swPllCfg_msw | (value & 0x3fff);
    return;
  }
  if (field == SWPLL_FLAGS)  {
    current_table.common.swPllCfg_msw = current_table.common.swPllCfg_msw & 0x3fff;
    current_table.common.swPllCfg_msw = current_table.common.swPllCfg_msw | ((value & 0x3) << 14);
    return;
  }
  if (field == SWPLL_POSTDIV)  {
    current_table.common.swPllCfg_lsw = current_table.common.swPllCfg_lsw & 0xff00;
    current_table.common.swPllCfg_lsw = current_table.common.swPllCfg_lsw | (value & 0xff);
    return;
  }
  if (field == SWPLL2_PREDIV)  {
    current_table.common.swPll2Cfg_lsw = current_table.common.swPll2Cfg_lsw & 0x00ff;
    current_table.common.swPll2Cfg_lsw = current_table.common.swPll2Cfg_lsw | ((value & 0x00ff) << 8);
    return;
  }
  if (field == SWPLL2_MULT)  {
    current_table.common.swPll2Cfg_msw = current_table.common.swPll2Cfg_msw | (value & 0x3fff);
    return;
  }
  if (field == SWPLL2_FLAGS)  {
    current_table.common.swPll2Cfg_msw = current_table.common.swPll2Cfg_msw & 0x3fff;
    current_table.common.swPll2Cfg_msw = current_table.common.swPll2Cfg_msw | ((value & 0x3) << 14);
    return;
  }
  if (field == SWPLL2_POSTDIV)  {
    current_table.common.swPll2Cfg_lsw = current_table.common.swPll2Cfg_lsw & 0xff00;
    current_table.common.swPll2Cfg_lsw = current_table.common.swPll2Cfg_lsw | (value & 0xff);
    return;
  }
  if (field == SYS_FREQ_MHZ)  {
    current_table.common.sysFreqMhz = value;
    return;
  }
  if (field == CORE_FREQ_MHZ)  {
    current_table.common.coreFreqMhz = value;
    return;
  }
  if (field == BOOT_MASTER)  {
    current_table.common.bootMaster = value;
    return;
 }
  if (field == PARAM_INDEX)  {
    ctable_index = value;
    return;
  }



  switch (current_table.common.boot_mode)  {

    case BOOT_MODE_I2C:
        switch (field)  {

          case OPTIONS:          current_table.i2c.options = value;
                                 break;

          case MULTI_I2C_ID:     current_table.i2c.multi_i2c_id = value;
                                 break;

          case MY_I2C_ID:        current_table.i2c.my_i2c_id = value;
                                 break;

          case I2C_CLK_FREQ_KHZ: current_table.i2c.i2c_clk_freq_khz = value;
                                 break;

          case NEXT_DEV_ADDR:    current_table.i2c.next_dev_addr = value;
                                 break;

          case NEXT_DEV_ADDR_EXT: current_table.i2c.next_dev_addr_ext = value;
                                  break;

          case ADDRESS_DELAY:    current_table.i2c.address_delay = value;
                                 break;

          case SWPLL_POSTDIV:    current_table.i2c.swPllCfg_lsw = current_table.i2c.swPllCfg_lsw & 0xff00;
                                 current_table.i2c.swPllCfg_lsw = current_table.i2c.swPllCfg_lsw | (value & 0xff);
                                 break;

          case DEV_ADDR_EXT:     current_table.i2c.dev_addr_ext = value;
                                 break;

          case DEV_ADDR:         current_table.i2c.dev_addr = value;
                                 break;

          default: fprintf (stderr, "unrecognized I2C configuration (token = %d, value = %d, line %d)\n", field, value, cline);
                        break;

        }
        break;


    case BOOT_MODE_ETH:
        switch (field)  {


          case OPTIONS:   current_table.eth.options = value;
                          break;

          case SRC_PORT:  current_table.eth.src_port = value;
                          break;

          case DEST_PORT: current_table.eth.dest_port = value;
                          break;

          case DEV_ID:    current_table.eth.device_id_12 = value >> 16;
                          current_table.eth.device_id_34 = value & 0xffff;
                          break;

          case SGMII_CONFIG:  current_table.eth.sgmiiConfig = value;
                              break;

          case SGMII_CTL: current_table.eth.sgmiiControl = value;
                          break;

          case SGMII_ADV_ABILITY:  current_table.eth.sgmiiMr_Adv_Ability = value;
                                   break;

          case SGMII_TX_CFG:  current_table.eth.sgmiiTx_Cfg_h = value >> 16;
                              current_table.eth.sgmiiTx_Cfg_l = value & 0xffff;
                              break;

          case SGMII_RX_CFG:  current_table.eth.sgmiiRx_Cfg_h = value >> 16;
                              current_table.eth.sgmiiRx_Cfg_l = value & 0xffff;
                              break;

          case PKT_PLL:   current_table.eth.pktPllCfg_msw = value >> 16;
                          current_table.eth.pktPllCfg_lsw = value & 0xffff;
                          break;

          default: fprintf (stderr, "unrecognized ETH configuration (token = %d, value = %d, line %d)\n", field, value, cline);
                        break;

     }
     break;


    case BOOT_MODE_RAPIDIO:
        switch (field)  { 
        
          case OPTIONS: current_table.rio.options = value;
                        break;

          case LANE_SETUP: current_table.rio.lane_port_setup = value;
                           break;

#if 0
          case CFG_INDEX: current_table.rio.cfg_index = value;
                          break;
#endif

          case NODE_ID: current_table.rio.node_id = value;
                        break;

          case SERDES_REF: current_table.rio.serdes_ref_clk = value;
                           break;

          case LINK_RATE: current_table.rio.link_rate = value;
                          break;

          case PF_LOW: current_table.rio.pf_low = value;
                       break;

          case PF_HIGH: current_table.rio.pf_high = value;
                        break;

          default: fprintf (stderr, "unrecognized SRIO configuration (token = %d, value = %d, line %d)\n", field, value, cline);
                        break;
      }
      break;


    case BOOT_MODE_VUSR:
        switch (field)  {

          case OPTIONS: current_table.vusr.options = value;
                        break;

          case N_LANES: current_table.vusr.nLanes = value;
                        break;

          case SERDES_CFG: current_table.vusr.serdesCfgMsw = value >> 16;
                           current_table.vusr.serdesCfgLsw = value & 0xffff;
                           break;

          case SERDES_RX0_CFG: current_table.vusr.serdesCfgRxLane0Msw = value >> 16;
                               current_table.vusr.serdesCfgRxLane0Lsw = value & 0xffff;
                               break;

          case SERDES_RX1_CFG: current_table.vusr.serdesCfgRxLane1Msw = value >> 16;
                               current_table.vusr.serdesCfgRxLane1Lsw = value & 0xffff;
                               break;

          case SERDES_RX2_CFG: current_table.vusr.serdesCfgRxLane2Msw = value >> 16;
                               current_table.vusr.serdesCfgRxLane2Lsw = value & 0xffff;
                               break;

          case SERDES_RX3_CFG: current_table.vusr.serdesCfgRxLane3Msw = value >> 16;
                               current_table.vusr.serdesCfgRxLane3Lsw = value & 0xffff;
                               break;

          case SERDES_TX0_CFG: current_table.vusr.serdesCfgTxLane0Msw = value >> 16;
                               current_table.vusr.serdesCfgTxLane0Lsw = value & 0xffff;
                               break;

          case SERDES_TX1_CFG: current_table.vusr.serdesCfgTxLane1Msw = value >> 16;
                               current_table.vusr.serdesCfgTxLane1Lsw = value & 0xffff;
                               break;

          case SERDES_TX2_CFG: current_table.vusr.serdesCfgTxLane2Msw = value >> 16;
                               current_table.vusr.serdesCfgTxLane2Lsw = value & 0xffff;
                               break;

          case SERDES_TX3_CFG: current_table.vusr.serdesCfgTxLane3Msw = value >> 16;
                               current_table.vusr.serdesCfgTxLane3Lsw = value & 0xffff;
                               break;

          default: fprintf (stderr, "unrecognized VUSR configuration (token = %d, value = %d, line %d)\n", field, value, cline);
                   break;

      }
      break;

      case BOOT_MODE_PCIE:
          switch (field)  {

            case OPTIONS:  current_table.pcie.options = value;
                           break;

            case ADDR_WIDTH: current_table.pcie.addressWidth = value;
                             break;

            case LINK_RATE: current_table.pcie.linkRateMhz = value;
                            break;

            case SERDES_REF: current_table.pcie.refClock10kHz = value;
                             break;

#if 0
            case WINDOW0_SIZE: current_table.pcie.window0Size = value;
                               break;
#endif

            case WINDOW1_SIZE: current_table.pcie.window1Size = value;
                               break;

            case WINDOW2_SIZE: current_table.pcie.window2Size = value;
                               break;

            case WINDOW3_SIZE: current_table.pcie.window3Size = value;
                               break;

            case VENDOR_ID: current_table.pcie.vendorId = value;
                            break;

            case DEVICE_ID: current_table.pcie.deviceId = value;
                            break;

            case CLASS_CODE_REVID: current_table.pcie.classCodeRevId_Msw = value >> 16;
                                   current_table.pcie.classCodeRevId_Lsw = value & 0xffff;
                                   break;

            case SERDES_CFG: current_table.pcie.serdesCfgMsw = value >> 16;
                             current_table.pcie.serdesCfgLsw = value & 0xffff;
                             break;

            case SERDES_LANE0: current_table.pcie.serdesCfgLane0Msw = value >> 16;
                               current_table.pcie.serdesCfgLane0Lsw = value & 0xffff;
                               break;

            case SERDES_LANE1: current_table.pcie.serdesCfgLane1Msw = value >> 16;
                               current_table.pcie.serdesCfgLane1Lsw = value & 0xffff;
                               break;

            default: fprintf (stderr, "unrecognized PCIe configuration (token = %d, value = %d, line %d)\n", field, value, cline);
                        break;

        } 
        break;

    case BOOT_MODE_SPI:
        switch (field)  {

          case OPTIONS:          current_table.spi.options = value;
                                 break;

          case ADDR_WIDTH:       if ((value != 16) && (value != 24)) 
                                   fprintf (stderr, "Warning: Invalid address width specified (%d) for SPI (line %d)\n", value, cline);
                                 current_table.spi.addrWidth = value;
                                 break;

          case N_PINS:           if ((value != 4) && (value != 5))
                                    fprintf (stderr, "Warning: Invalid number of pins specified (%d) for SPI (line %d)\n", value, cline);
                                 current_table.spi.nPins = value;
                                 break;

          case CSEL:             if ((value < 0) || (value > 3))
                                    fprintf (stderr, "Warning: Invalid csel value specified (%d) for SPI (line %d)\n", value, cline);
                                 current_table.spi.csel = value;
                                 break;

          case MODE:             if ((value < 0) || (value > 3))
                                    fprintf (stderr, "Warning: Invalid mode specified (%d) for SPI (line %d)\n", value, cline);

                                 current_table.spi.mode = value;
                                 break;

          case C2T_DELAY:        current_table.spi.c2tdelay = value;
                                 break;


          case BUS_FREQ_100KHZ:  current_table.spi.busFreq100Khz = value;
                                 break;

          case NEXT_DEV_ADDR:    current_table.spi.next_read_addr_msw = value >> 16;
                                 current_table.spi.next_read_addr_lsw = value & 0xffff;
                                 break;

          case NEXT_CSEL:        if ((value != 2) && (value != 1))
                                    fprintf (stderr, "Warning: Invalid next csel value specified (%d) for SPI (line %d)\n", value, cline);
                                 current_table.spi.next_csel = value;
                                 break;


          case DEV_ADDR:         current_table.spi.read_addr_msw = value >> 16;
                                 current_table.spi.read_addr_lsw = value & 0xffff;
                                 break;

            default: fprintf (stderr, "unrecognized SPI configuration (token = %d, value = %d, line %d)\n", field, value, cline);
                        break;
        }                                
        break;                

  }


} /* assignKeyVal */

/*******************************************************************************
 * FUNCTION PURPOSE: Load an i2c blocked exe file
 *******************************************************************************
 * DESCRIPTION: The specified file is opened and read.
 *******************************************************************************/
void addExeFile (char *fname)
{
  int i;

  /* Check if the file name is already open */
  for (i = 0; i < nProgFiles; i++)  {

    if (!strcmp (fname, progFile[i].fname))  {
      /* Found a match - copy the address */
      if (current_table.common.boot_mode == BOOT_MODE_I2C)
        current_table.i2c.dev_addr     = progFile[i].addressBytes & 0xffff;
      
      else if (current_table.common.boot_mode == BOOT_MODE_SPI)  {
        current_table.spi.read_addr_msw = (progFile[i].addressBytes >> 16) & 0xffff;
        current_table.spi.read_addr_lsw = progFile[i].addressBytes & 0xffff;
      }
      return;
    }

  }

  /* Open and read the ccs file, set the ROM address */
  i = openProgFile (fname);
  if (i >= 0) {
      if (current_table.common.boot_mode == BOOT_MODE_I2C)
        current_table.i2c.dev_addr     = progFile[i].addressBytes & 0xffff;

      else if (current_table.common.boot_mode == BOOT_MODE_SPI)  {
        current_table.spi.read_addr_msw = (progFile[i].addressBytes >> 16) & 0xffff;
        current_table.spi.read_addr_lsw = progFile[i].addressBytes & 0xffff;
      }
  }

}

/********************************************************************************
 * FUNCTION PURPOSE: Convert a 16 bit value to the big endian byte representation
 ********************************************************************************
 * DESCRIPTION: A two byte value representing the big endian format of the input
 *              16 bit value is returned
 ********************************************************************************/
unsigned short be16bytes (unsigned short v)
{
  unsigned short v1;

  v1 = (((v >> 8) & 0xff) << 8) | (v & 0xff);

  return (v1);

}

#if 0
/*******************************************************************************
 * FUNCTION PURPOSE: sign, encrypt a boot parameter table
 *******************************************************************************
 * DESCRIPTION: The boot parameter table is signed and encrypted. The 1st 4 bytes
 *              are not included (these are the i2c header)
 *
 *              Returns the number of 4 byte lines written to the output file
 *
 *        Note: The encrypt function called here are taken from secboot.c 
 *              which resides in secboottbl directory
 *******************************************************************************/
int signEncryptWriteTable (int idx, FILE *str, char *rsaKeyName, char *aesKeyName)
{

    char            aesKey[132];
    unsigned char  *block;
    unsigned char  *eblock;
    unsigned short *sblock;
    unsigned int   *iblock;
    unsigned int    v;
    int             size;
    int             esize;
    int             i, j, p;
    FILE           *fp;
    FILE           *bout;


    /* Create an ouput file containing only the signed/encrypted boot parameter table
     * which can be used in the simulator */
    sprintf (aesKey, "param_%d_enctable.ccs", idx);
    bout = fopen (aesKey, "w");
    if (bout == NULL)  {
      fprintf (stderr, "Failed to open output file %s\n", aesKey);
      return (-1);
    }

    /* Allocate the data block to hold the unencrypted block. It is based on 
     * the size of the boot table, but without the 4 byte i2c header. The
     * size is rounded up to a multiple of 16 bytes;
     * size is */
    size = boot_params[idx].common.length - 4;
    size = (size + 15) & ~15;

    block = malloc (BOOT_PARAMS_SIZE_IN_BYTES);
    if (block == NULL)
        return (-1);

    /* Copy the boot table to the block */
    memset (block, 0, size);

    /* Must handle the data as byte array. Skip the 1st two 16 bit params (the i2c header)
     * because these values are not encyrpted. */
    for (i = p = 0; i < (BOOT_PARAMS_SIZE_IN_BYTES >> 1); i++, p += 2)  {
        v = boot_params[idx].parameter[i+2];
        block[p+0] = (v >> 8) & 0xff;
        block[p+1] = v & 0xff;
    }
        

    /* Now open the aes key file and read in the key. It is an ascii string */
    fp = fopen (aesKeyName, "r");
    if (fp == NULL)  {
        fprintf (stderr, "Failed to open AES key file %s, fatal error\n", aesKeyName);
        return (-1);
    }

    fgets (aesKey, 132, fp);
    fclose (fp);

    /* sign and encrypt the block */
    esize = size;
    eblock = bootSignEncrypt (block, &esize, rsaKeyName, aesKey);

    if (eblock == NULL)  {
        fprintf (stderr, "Encryption function reported a failure, exiting\n");
        return (-1);
    }

    /* Write out the ccs header for the sim file. Add one line for the i2c header  */
    fprintf (bout, "1651 1 10000 1 %x\n", (esize >> 2) + 1);

    /* Write out the header. The ones complement checksum is based on 16 bit
     * values, so a scratch version must be created. Add 3 bytes to round
     * to the a 4 byte boundary, and add 4 bytes for the i2c header */
    size = (esize + 3 + 4) & ~3;
    sblock = malloc (size);
    if (sblock == NULL)  {
        fprintf (stderr, "malloc failed on sblock (size = %d)\n", size);
        return (-1);
    }

    sblock[0] = size;
    sblock[1] = 0;

    for (i = 2, p = 0; i < size/2; i++, p += 2)
        sblock[i] = (eblock[p+0] << 8) + eblock[p+1];

    sblock[1] = ~onesCompCheckSum (sblock, size/2);

    /* Now write out the 4 byte CCS header */
    v = (sblock[0] << 16) | sblock[1];
    fprintf (str, "0x%08x\n", v);
    fprintf (bout, "0x%08x\n", v);

    free (sblock);

    
    
    /* Write the data out in ccs format. Form the words in big endian format */
    size = (esize / 4) ;  /* esize is the block size, does not include the i2c header */
    for (i = p = 0; i < size; i++)  {

        v = 0 + (eblock[p++] << 24);
        v = v + (eblock[p++] << 16);
        v = v + (eblock[p++] <<  8);
        v = v + (eblock[p++] <<  0);

        fprintf (str, "0x%08x\n", v);
        fprintf (bout, "0x%08x\n", v);

    }

    /* There should not be any left over bytes, but just in case, write them out */
    if ((esize & 0x3) != 0)  {
        v = 0;
        for (j = 24; p < esize; p++, j = j - 8)
            v = v + (eblock[p] << j);
        fprintf (str, "0x%08x\n", v);
        fprintf (bout, "0x%08x\n", v);
        i = i + 1;
    }

    free (eblock);
    free (block);
    fclose (bout);
    fclose (fp);

    /* Add one line for the i2c header which was written out first */
    return (i+1);

}

#endif

/*******************************************************************************
 * FUNCTION PURPOSE: Parse a string input.
 *******************************************************************************
 * DESCRIPTION: Takes a string input and assigns it to the current table
 *******************************************************************************/
void assignKeyStr (int value, char *y)
{
  char *z;


  /* the input string still contains the quotes. Remove them here */
  z = &y[1];
  *strchr (z, '"') = '\0';


  switch (value)  {


     case EXE_FILE:
            addExeFile (z);
            break;

     case RSA_KEY:
            strcpy (cur_rsa_key_file, z);
            break;

     case AES_KEY:
            strcpy (cur_aes_key_file, z);
            break;

     case KEYSIGN:
            strcpy (cur_key_sign_file, z);
            break;

     default:
            fprintf (stderr, "Invalid string assignment (%s) to token %d at line %d\n", y, value, cline);
            break;

    }

}


/************************************************************************************
 * FUNCTION PURPOSE: Opens and writes the output file
 ************************************************************************************
 * DESCRIPTION: Creates the output file in ccs format.
 ************************************************************************************/
void createOutput (void)
{
  FILE *str;
  int   totalLenBytes;
  int   i, j;
  unsigned int value, v1, v2;

  str = fopen ("i2crom.ccs", "w");
  if (str == NULL)  {
    fprintf (stderr, "romparse: Could not open output file i2crom.ccs for writing\n");
    exit (-1);
  }


  /* Compute the total size of the i2c prom. Include all the i2c boot paramater tables,
   * as well as the PCI parameter table, (which is not necessarily present).
   * If the noHdr option is set then the 4 byte length/checksum is not included */
  totalLenBytes = num_boot_param_tables * (0x80 - (noHdr * 4));
  if (pciTable != 0)
    totalLenBytes += PCI_EEAI_PARAM_SIZE;


  for (i = 0; i < nProgFiles; i++)
    totalLenBytes += progFile[i].sizeBytes;

  /* Write out the ccs header */
  fprintf (str, "1651 1 10000 1 %x\n", totalLenBytes >> 2);

  /* Write out the boot parameter tables. 0x80 bytes will be written out.
   * There are 16 bits in every parameter field, which is why the index
   * is from 0 to 0x40 */
  for (i = 0; i < num_boot_param_tables; i++)  {
    for (j = noHdr * 2; j < (0x80 >> 1); j += 2)  {
      v1 = boot_params[i].parameter[j];
      v2 = boot_params[i].parameter[j+1];
      value = (v1 << 16) | v2;
      fprintf (str, "0x%08x\n", value);
    }
  }

  /* Write out the PCI parameter base. If none was included then zeros will be
   * written out */
  if (pciTable != 0)  {
    for (i = 0; i < PCI_DATA_LEN_32bit; i++)  {
      fprintf (str, "0x%08x\n", pciFile.data[i]);
    }
  }
                                

  /* Write out each of the program files */
  for (i = 0; i < nProgFiles; i++)
    for (j = 0; j < progFile[i].sizeBytes >> 2; j++)
      fprintf (str, "0x%08x\n", (progFile[i]).data[j]);


  /* Close the input file */
  fclose (str);

} /* createOutput  */

#if 0
/************************************************************************************
 * FUNCTION PURPOSE: Encrypt the boot parameter tables, write the output file
 ************************************************************************************
 * DESCRIPTION: The boot parameter tables are encrypted, and the i2c image is
 *              output.
 ************************************************************************************/
void createSecureOutput (void)
{
  FILE *str;
  FILE *strin;
  FILE *bout;
  int   totalLenBytes;
  int   i, j, k;
  unsigned int value, v1, v2;
  int a, b, c, d, e;
  char iline[132];

  str = fopen ("i2csecrom.ccs", "w");
  if (str == NULL)  {
    fprintf (stderr, "romparse: Could not open ouput file i2csecrom.ccs for writing\n");
    exit (-1);
  }

  /* Compute the total size of the i2c eeprom. Include all the i2c boot parameter tables */
  totalLenBytes = DATA_BASE_SECURE;

  for (i = 0; i < nProgFiles; i++)
    totalLenBytes += progFile[i].sizeBytes;

  /* Write out the ccs header */
  fprintf (str, "1651 1 10000 1 %x\n", totalLenBytes >> 2);

  /* Write out the signed keys, then the encrypted boot parameter tables. */
  for (i = 0; i < NUM_SEC_BOOT_PARAM_TABLES; i++)  {

    if (  (key_sign_file[i][0] == 0)  ||
          ( aes_key_file[i][0] == 0)  ||
          ( rsa_key_file[i][0] == 0)  )   {

       /* No secure data for this table, write out 0s */
       for (j = 0; j < (KEYSIGN_SIZE_BYTES + SEC_TABLE_SIZE_BYTES) >> 2; j++)
          fprintf (str, "0x00000000\n");

    }  else  {

       /* There is valid key data. Read in then write out the keysign data. */
       strin = fopen (key_sign_file[i], "r");
       if (strin == NULL)  {
          fprintf (stderr, "Failed to open signed key file %s, exiting\n", key_sign_file[i]);
          fclose (str);
          exit (-1);
       }

       /* Create a seperate output file to be used in the sim */
       sprintf (iline, "param_%d_i2ckeykeysign.ccs", i);
       bout = fopen (iline, "w");
       if (bout == NULL)  {
          fprintf (stderr, "Failed to open output file %s to store the i2c blocked key/keysign info\n");
          exit (-1);
       }

       /* Read in the ccs header */
       fgets (iline, 132, strin);
       sscanf (iline, "%x %x %x %x %x", &a, &b, &c, &d, &e);

       if (e > (KEYSIGN_SIZE_BYTES >> 2))  {
          fprintf (stderr, "Keyfile %s has a size of 0x%04x lines, but the max key section size is 0x%04x bytes, exiting\n",
                            key_sign_file[i], e, KEYSIGN_SIZE_BYTES >> 2);
          fclose (strin);
          fclose (str);
          exit (-1);
       }

       /* The sim out file will have one more line then the input file */
       fprintf (bout, "%x %x %x %x %x\n", a, b, c, d, e+1);

       /* Write out the CCS header, leave the ones complement checksum off.
        * The MSW is the size of the block, in bytes, the LSW is the ones complement
        * checksum */
       a = KEYSIGN_SIZE_BYTES << 16;
       fprintf (str, "0x%08x\n", a);
       fprintf (bout, "0x%08x\n", a);


       for (j = 1; j  <= e; j++)  {
          fgets (iline, 132, strin);
          fputs (iline, str);
          fputs (iline, bout);
       }

       fclose (strin);
       fclose (bout);

       /* Fill in any remaining gap with 0s */
       for (  ; j < KEYSIGN_SIZE_BYTES >> 2;  j++)
         fprintf (str, "0x00000000\n");


       /* Now the parameter table must be signed and encrypted */
       j = signEncryptWriteTable (i, str, rsa_key_file[i], aes_key_file[i]);


       /* Fill in any remaining gap with 0s */
       for (  ;  j < SEC_TABLE_SIZE_BYTES >> 2; j++)
           fprintf (str, "0x00000000\n");

     }
  }
   
  /* Write out each of the program files */
  for (i = 0; i < nProgFiles; i++)
    for (j = 0; j < progFile[i].sizeBytes >> 2; j++)
      fprintf (str, "0x%08x\n", (progFile[i]).data[j]);


  fclose (str);


}

#endif

/************************************************************************************
 * FUNCTION PURPOSE: Initialize the pci paramter table
 ************************************************************************************
 * DESCRIPTION: Zeros the pci parameters
 ************************************************************************************/
void initPciParams (void)
{
  memset (&pciFile, 0, sizeof(pciFile_t));
} /* initPciParams */


/************************************************************************************
 * FUNCTION PURPOSE: Read an integer arg
 ************************************************************************************
 * DESCRIPTION: The arg could be hex or int
 ************************************************************************************/
int readInt (char *c)
{
    int v;

    if ((c[0] == '0') && (c[1] == 'x'))
        sscanf (&c[2], "%x", &v);
    else
        sscanf (c, "%d", &v);


    return (v);

}

/************************************************************************************
 * FUNCTION PURPUSE: Return the progrm usage
 ************************************************************************************
 * DESCRIPTION: The usage is printed
 ************************************************************************************/
char *usage (char *c)
{
    fprintf (stderr, "usage: %s [-h] [-secure] [-nTables num_param_tables] [-noPci] [-noHdr] inputfile\n", c);
    return (NULL);

}


/************************************************************************************
 * FUNCTION PURPOSE: Parse the input args
 ************************************************************************************
 * DESCRIPTION: The usage is:
 *              romparse [-h] [-secure] [-nTables num_param_tables] [-noPci] inputfile
 *
 *              Returns the pointer to the input file on success, NULL on failure
 ************************************************************************************/
char *parseArgs (int argc, char *argv[])
{
    int i;
    char *inname = NULL;

    for (i = 1; i < argc; )  {
        
        if (!strcmp (argv[i], "-secure"))  {
            secureBoot = TRUE;
            i = i + 1;
            continue;
        }

        if (!strcmp (argv[i], "-h"))
            return (usage (argv[0]));

        if (!strcmp (argv[i], "-nTables"))  {
            num_boot_param_tables = readInt (argv[i+1]);
            i = i + 2;
            continue;
        }

        if (!strcmp (argv[i], "-noPci"))  {
            pciTable = 0;
            i = i + 1;
            continue;
        }

        if (!strcmp (argv[i], "-noHdr"))  {
            noHdr = 1;
            i = i + 1;
            continue;
        }


        if (inname == NULL)  {
            inname = argv[i];
            i = i + 1;
            continue;
        }

        fprintf (stderr, "%s: Unkown argument %s\n", argv[0], argv[i]);
        break;
    }

    return (inname);

}


/************************************************************************************
 * FUNCTION PURPOSE: main function
 ************************************************************************************
 * DESCRIPTION: Performs the processing sequence.
 ************************************************************************************/

int main (int argc, char *argv[])
{
  int i;
  char *inname;

  /* Parse the command arguments */
  inname = parseArgs (argc, argv);
  if (inname == NULL)
    return (-1);

  /* Initialize the tables */
  for (i = 0; i < NUM_BOOT_PARAM_TABLES; i++)
    initTable(&boot_params[i]);

  initTable (&current_table);

  /* Initialize the PCI param table */
  initPciParams ();


  if (secureBoot == TRUE)
    romBase = DATA_BASE_SECURE;
  else
    romBase = (num_boot_param_tables * 0x80) + (pciTable * PCI_EEAI_PARAM_SIZE);


  /* Initialize the secure key info */
  for (i = 0; i < NUM_SEC_BOOT_PARAM_TABLES; i++)  {
    aes_key_file[i][0]  = 0;
    rsa_key_file[i][0]  = 0;
    key_sign_file[i][0] = 0;
  }

  memset (cur_aes_key_file,  0, sizeof (cur_aes_key_file));
  memset (cur_rsa_key_file,  0, sizeof (cur_rsa_key_file));
  memset (cur_key_sign_file, 0, sizeof (cur_key_sign_file));
  
  yyin = fopen (inname, "r");
  if (yyin == NULL)  {
    fprintf (stderr, "%s: could not open file %s\n", argv[0], inname);
    return (-1);
  }

  /* Parse the input description file */
  yyparse();

  createOutput ();

#if 0
  /* Create the output file */
  if (secureBoot == FALSE)
    createOutput ();
  else
    createSecureOutput ();
#endif

  return (0);
}



