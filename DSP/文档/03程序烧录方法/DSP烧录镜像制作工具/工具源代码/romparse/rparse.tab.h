/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LBRACE = 258,
     RBRACE = 259,
     SECTION = 260,
     EQU = 261,
     VALUE = 262,
     STRING = 263,
     BOOT_MODE = 264,
     PARAM_INDEX = 265,
     OPTIONS = 266,
     MULTI_I2C_ID = 267,
     MY_I2C_ID = 268,
     I2C_CLK_FREQ_KHZ = 269,
     EXE_FILE = 270,
     PCI_PARMS = 271,
     NEXT_DEV_ADDR = 272,
     NEXT_DEV_ADDR_EXT = 273,
     ADDRESS_DELAY = 274,
     SWPLL_PREDIV = 275,
     SWPLL_MULT = 276,
     SWPLL_POSTDIV = 277,
     DEV_ADDR_EXT = 278,
     DEV_ADDR = 279,
     SWPLL_FLAGS = 280,
     TWOHEX = 281,
     COLON = 282,
     SRC_PORT = 283,
     DEST_PORT = 284,
     DEV_ID = 285,
     SGMII_CONFIG = 286,
     SGMII_CTL = 287,
     SGMII_ADV_ABILITY = 288,
     SGMII_TX_CFG = 289,
     SGMII_RX_CFG = 290,
     PKT_PLL = 291,
     MAC_ADDR = 292,
     MMAC_ADDR = 293,
     HMAC_ADDR = 294,
     KEYWORD = 295,
     LANE_SETUP = 296,
     CFG_INDEX = 297,
     NODE_ID = 298,
     SERDES_REF = 299,
     LINK_RATE = 300,
     PF_LOW = 301,
     PF_HIGH = 302,
     N_LANES = 303,
     SERDES_CFG = 304,
     SERDES_RX0_CFG = 305,
     SERDES_RX1_CFG = 306,
     SERDES_RX2_CFG = 307,
     SERDES_RX3_CFG = 308,
     SERDES_TX0_CFG = 309,
     SERDES_TX1_CFG = 310,
     SERDES_TX2_CFG = 311,
     SERDES_TX3_CFG = 312,
     ADDR_WIDTH = 313,
     WINDOW0_SIZE = 314,
     WINDOW1_SIZE = 315,
     WINDOW2_SIZE = 316,
     WINDOW3_SIZE = 317,
     VENDOR_ID = 318,
     DEVICE_ID = 319,
     CLASS_CODE_REVID = 320,
     SERDES_LANE0 = 321,
     SERDES_LANE1 = 322,
     N_PINS = 323,
     CSEL = 324,
     MODE = 325,
     C2T_DELAY = 326,
     BUS_FREQ_100KHZ = 327,
     NEXT_CSEL = 328,
     RSA_KEY = 329,
     AES_KEY = 330,
     KEYSIGN = 331,
     PORT_NUM = 332,
     SWPLL2_PREDIV = 333,
     SWPLL2_MULT = 334,
     SWPLL2_POSTDIV = 335,
     SWPLL2_FLAGS = 336,
     SYS_FREQ_MHZ = 337,
     CORE_FREQ_MHZ = 338,
     BOOT_MASTER = 339
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


