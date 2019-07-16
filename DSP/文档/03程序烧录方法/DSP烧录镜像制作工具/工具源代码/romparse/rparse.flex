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
/* Lexical analyzer for the eeprom boot builder */
%{
#include "rparse.tab.h"
extern int cline;
%}
%%

"//".*\n    cline++;

"{" return (LBRACE);	
"}" return (RBRACE);   
"=" return (EQU);	    
":" return (COLON);

section           { yylval = SECTION;           return (SECTION); }
boot_mode         { yylval = BOOT_MODE;         return (KEYWORD); }
param_index       { yylval = PARAM_INDEX;       return (KEYWORD); }
options           { yylval = OPTIONS;           return (KEYWORD); }
multi_i2c_id      { yylval = MULTI_I2C_ID;      return (KEYWORD); }
my_i2c_id         { yylval = MY_I2C_ID;         return (KEYWORD); }
i2c_clk_freq_khz  { yylval = I2C_CLK_FREQ_KHZ;  return (KEYWORD); }
exe_file          { yylval = EXE_FILE;          return (KEYWORD); }
pci_parm		  { yylval = PCI_PARMS;         return (KEYWORD); }
dev_addr		  { yylval = DEV_ADDR;			return (KEYWORD); }
dev_addr_ext	  { yylval = DEV_ADDR_EXT;		return (KEYWORD); }
next_dev_addr     { yylval = NEXT_DEV_ADDR;     return (KEYWORD); }
next_dev_addr_ext { yylval = NEXT_DEV_ADDR_EXT; return (KEYWORD); }
address_delay     { yylval = ADDRESS_DELAY;     return (KEYWORD); }
sw_pll_prediv	  { yylval = SWPLL_PREDIV;		return (KEYWORD); }
sw_pll_mult	      { yylval = SWPLL_MULT;		return (KEYWORD); }
sw_pll_postdiv    { yylval = SWPLL_POSTDIV;     return (KEYWORD); }
sw_pll_flags      { yylval = SWPLL_FLAGS;		return (KEYWORD); }
sw_pll2_prediv	  { yylval = SWPLL2_PREDIV;		return (KEYWORD); }
sw_pll2_mult	  { yylval = SWPLL2_MULT;		return (KEYWORD); }
sw_pll2_postdiv   { yylval = SWPLL2_POSTDIV;    return (KEYWORD); }
sw_pll2_flags     { yylval = SWPLL2_FLAGS;		return (KEYWORD); }
portNum			  { yylval = PORT_NUM;			return (KEYWORD); }
sysFreqMhz		  { yylval = SYS_FREQ_MHZ;		return (KEYWORD); }
coreFreqMhz		  { yylval = CORE_FREQ_MHZ;	    return (KEYWORD); }
bootMaster		  { yylval = BOOT_MASTER;		return (KEYWORD); }

rsa_priv_key_file { yylval = RSA_KEY;			return (KEYWORD); }
aes_key_file	  { yylval = AES_KEY;			return (KEYWORD); }
key_keysign_file  { yylval = KEYSIGN;			return (KEYWORD); }

n_pins			  { yylval = N_PINS;			return (KEYWORD); }
csel			  { yylval = CSEL;				return (KEYWORD); }
mode			  { yylval = MODE;				return (KEYWORD); }
c2t_delay		  { yylval = C2T_DELAY;			return (KEYWORD); }
bus_freq_100khz	  { yylval = BUS_FREQ_100KHZ;	return (KEYWORD); }
next_csel		  { yylval = NEXT_CSEL;		    return (KEYWORD); }


src_port          { yylval = SRC_PORT;          return (KEYWORD); }
dest_port         { yylval = DEST_PORT;         return (KEYWORD); }
dev_id            { yylval = DEV_ID;            return (KEYWORD); }
mac_addr          { yylval = MAC_ADDR;          return (KEYWORD); }
mmac_addr         { yylval = MMAC_ADDR;         return (KEYWORD); }
hmac_addr         { yylval = HMAC_ADDR;         return (KEYWORD); }
sgmii_config      { yylval = SGMII_CONFIG;      return (KEYWORD); }
sgmii_ctl         { yylval = SGMII_CTL;         return (KEYWORD); }
sgmii_adv_ability { yylval = SGMII_ADV_ABILITY; return (KEYWORD); }
sgmii_tx_cfg      { yylval = SGMII_TX_CFG;      return (KEYWORD); }
sgmii_rx_cfg      { yylval = SGMII_RX_CFG;      return (KEYWORD); }
pkt_pll           { yylval = PKT_PLL;           return (KEYWORD); }

lane_setup        { yylval = LANE_SETUP;        return (KEYWORD); }
cfg_index         { yylval = CFG_INDEX;		    return (KEYWORD); }
node_id           { yylval = NODE_ID;           return (KEYWORD); }
serdes_ref        { yylval = SERDES_REF;        return (KEYWORD); }
link_rate         { yylval = LINK_RATE;         return (KEYWORD); }
pf_low            { yylval = PF_LOW;            return (KEYWORD); }
pf_high           { yylval = PF_HIGH;           return (KEYWORD); }

n_lanes			  { yylval = N_LANES;			return (KEYWORD); }
serdes_cfg        { yylval = SERDES_CFG;		return (KEYWORD); }
serdes_rx0_cfg    { yylval = SERDES_RX0_CFG;    return (KEYWORD); }
serdes_rx1_cfg    { yylval = SERDES_RX1_CFG;    return (KEYWORD); }
serdes_rx2_cfg    { yylval = SERDES_RX2_CFG;    return (KEYWORD); }
serdes_rx3_cfg    { yylval = SERDES_RX3_CFG;    return (KEYWORD); }
serdes_tx0_cfg    { yylval = SERDES_TX0_CFG;    return (KEYWORD); }
serdes_tx1_cfg    { yylval = SERDES_TX1_CFG;    return (KEYWORD); }
serdes_tx2_cfg    { yylval = SERDES_TX2_CFG;    return (KEYWORD); }
serdes_tx3_cfg    { yylval = SERDES_TX3_CFG;    return (KEYWORD); }

addr_width        { yylval = ADDR_WIDTH;        return (KEYWORD); }
window0_size      { yylval = WINDOW0_SIZE;      return (KEYWORD); }
window1_size      { yylval = WINDOW1_SIZE;      return (KEYWORD); }
window2_size      { yylval = WINDOW2_SIZE;      return (KEYWORD); }
window3_size      { yylval = WINDOW3_SIZE;      return (KEYWORD); }
vendor_id         { yylval = VENDOR_ID;         return (KEYWORD); }
device_id         { yylval = DEVICE_ID;         return (KEYWORD); }
class_code_revid  { yylval = CLASS_CODE_REVID;  return (KEYWORD); }
serdes_lane0      { yylval = SERDES_LANE0;      return (KEYWORD); }
serdes_lane1      { yylval = SERDES_LANE1;      return (KEYWORD); }


[0-9a-fA-F][0-9a-fA-F]		{ sscanf (yytext, "%x", &yylval); return (TWOHEX);  }
[0-9]+ 		 { yylval = atoi(yytext); return (VALUE);  }
0x[0-9a-f]+ { sscanf (&yytext[2], "%x", &yylval); return (VALUE);  }


\".*\"		return (STRING);

[ \t]+		;
[\n]		cline++ ;


%%




