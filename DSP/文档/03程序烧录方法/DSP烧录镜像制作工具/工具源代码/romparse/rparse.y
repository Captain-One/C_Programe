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
/* Parse the parameter spec */
%{
#define YYERROR_VERBOSE
extern char *yytext;
extern int pArray[];
extern int nArray;
%}
%token LBRACE RBRACE SECTION EQU VALUE STRING BOOT_MODE PARAM_INDEX OPTIONS 
%token MULTI_I2C_ID MY_I2C_ID I2C_CLK_FREQ_KHZ 
%token EXE_FILE PCI_PARMS NEXT_DEV_ADDR NEXT_DEV_ADDR_EXT ADDRESS_DELAY SWPLL_PREDIV
%token SWPLL_MULT SWPLL_POSTDIV DEV_ADDR_EXT DEV_ADDR SWPLL_FLAGS TWOHEX COLON
%token SRC_PORT DEST_PORT DEV_ID SGMII_CONFIG SGMII_CTL SGMII_ADV_ABILITY
%token SGMII_TX_CFG SGMII_RX_CFG PKT_PLL MAC_ADDR MMAC_ADDR HMAC_ADDR KEYWORD
%token LANE_SETUP CFG_INDEX NODE_ID SERDES_REF LINK_RATE PF_LOW PF_HIGH
%token N_LANES SERDES_CFG SERDES_RX0_CFG SERDES_RX1_CFG SERDES_RX2_CFG SERDES_RX3_CFG
%token SERDES_TX0_CFG SERDES_TX1_CFG SERDES_TX2_CFG SERDES_TX3_CFG
%token ADDR_WIDTH WINDOW0_SIZE WINDOW1_SIZE WINDOW2_SIZE WINDOW3_SIZE VENDOR_ID DEVICE_ID
%token CLASS_CODE_REVID SERDES_LANE0 SERDES_LANE1
%token N_PINS CSEL MODE C2T_DELAY BUS_FREQ_100KHZ NEXT_CSEL
%token RSA_KEY AES_KEY KEYSIGN PORT_NUM SWPLL2_PREDIV SWPLL2_MULT SWPLL2_POSTDIV SWPLL2_FLAGS
%token SYS_FREQ_MHZ CORE_FREQ_MHZ BOOT_MASTER
%%

promspec   : bootParams
		   | promspec bootParams
 		   ;

bootParams : SECTION LBRACE assigns RBRACE
			 { section (); }
		   | PCI_PARMS EQU STRING
		     { setPciParams (yytext); }
		   ;


assigns    : assign
		   | assigns assign
		   ;

assign     : KEYWORD EQU VALUE
			 { assignKeyVal ($1, $3); }
		   | KEYWORD EQU STRING
		     { assignKeyStr ($1, yytext); }
		   | KEYWORD EQU TWOHEX
		     { assignKeyVal ($1, (($3 >> 4) * 10) + ($3 & 0xf));  }
		   | KEYWORD EQU hexArray
		     { assignArray ($1, pArray, nArray);  }
		   ;



hexArray   : TWOHEX COLON TWOHEX
             {  pArray[0] = $1; pArray[1] = $3; nArray = 2; }
		   | hexArray COLON TWOHEX
		     {  pArray[nArray++] = $3; }
		   ;


%%


