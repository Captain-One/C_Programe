#include "mac_defs.h"

#define reserved 0xffff



const uint16_t BACKOFF[16] = {5, 10, 20, 30, 40, 60, 80, 120, 160, 240, 320, 480, 960, 1920, reserved, reserved};

const uint32_t BSR5_TABLE[BSR5_TABLE_SIZE] ={
		0, 10, 14, 20, 28, 38, 53, 74,
		102, 142, 198, 276, 384, 535, 745, 1038,
		1446, 2014, 2806, 3909, 5446, 7587, 10570, 14726, 20516, 28581,
		39818, 77284, 107669, 150000, 150000};

// bsr table for 8-bit Buffer Size field
const uint32_t BSR8_TABLE[BSR8_TABLE_SIZE] = {
		0,10,11,12,13,14,15,16,17,18,19,20,22,23,25,26,28,30,32,34,36,38,40,43,46,49,52,55,59,62,66,71,75,80,85,91,97,103,110,117,124,132,141,150,160,170,181,193,205,218,233,248,264,281,299,318,339,361,384,409,436,464,494,
		560,597,635,677,720,767,817,870,926,987,1051,1119,1191,1269,1351,1439,1532,1631,1737,1850,1970,2098,2234,2379,2533,2698,2873,3059,3258,3469,3694,3934,4189,4461,4751,5059,5387,5737,6109,6506,6928,7378,7857,8367,8910,9488,10104,10760,11458,12202,12994,13838,14736,15692,16711,17795,18951,20181,21491,22885,24371,25953,27638,
		31342,33376,35543,37850,40307,42923,45709,48676,51836,55200,58784,62599,66663,70990,75598,80505,85730,91295,97221,103532,110252,117409,125030,133146,141789,150992,160793,171231,182345,194182,206786,220209,234503,249725,265935,283197,301579,321155,342002,364202,387842,413018,439827,468377,498780,531156,565634,602350,641449,683087,727427,774645,824928,878475,935498,996222,1060888,1129752,1203085,1281179,1364342,1452903,1547213,
		1754595,1868488,1989774,2118933,2256475,2402946,2558924,2725027,2901912,3090279,3290873,3504487,3731968,3974215,4232186,4506902,4799451,5110989,5442750,5796046,6172275,6572925,6999582,7453933,7937777,8453028,9001725,9586039,10208280,10870913,11576557,12328006,13128233,13980403,14887889,15854280,16883401,17979324,19146385,20389201,21712690,23122088,24622972,26221280,27923336,29735875,31666069,33721553,35910462,38241455,40723756,43367187,46182206,49179951,52372284,55771835,59392055,63247269,67352729,71724679,76380419,81338368,81338368
};

const uint16_t RECOMMENDED_BITRATE_TABLE[64] ={
		0,	9,	11,	13,	17,	21,	25,	29,	32,	36,	40,	48,	56,
		72,	88,	104,	120,	140,	160,	180,	200,
		220,	240,	260,	280,	300,	350,		400,
		450,	500,	600,	700,	800,	900,	1000,	1100,
		1200,	1300,	1400,	1500,	1750,	2000,	2250,
		2500,	2750,	3000,	3500,	4000,	4500,	5000,
		5500,	6000,	6500,	7000,	7500,	8000};
//	specification mapping talbe, table_38$x_$y_$z_c$a
//	- $x: specification
//	- $y: subclause-major
//	- $z: subclause-minor
//	- $a: ($a)th of column in table, start from zero
const int32_t table_38213_13_1_c2[16] = {24, 24, 24, 24, 24, 24, 48, 48, 48, 48, 48, 48, 96, 96, 96, reserved}; // index 15 reserved
const int32_t table_38213_13_1_c3[16] = { 2,  2,  2,  3,  3,  3,  1,  1,  2,  2,  3,  3,  1,  2,  3, reserved}; // index 15 reserved
const int32_t table_38213_13_1_c4[16] = { 0,  2,  4,  0,  2,  4, 12, 16, 12, 16, 12, 16, 38, 38, 38, reserved}; // index 15 reserved

const int32_t table_38213_13_2_c2[16] = {24, 24, 24, 24, 24, 24, 24, 24, 48, 48, 48, 48, 48, 48, reserved, reserved}; // index 14-15 reserved
const int32_t table_38213_13_2_c3[16] = { 2,  2,  2,  2,  3,  3,  3,  3,  1,  1,  2,  2,  3,  3, reserved, reserved}; // index 14-15 reserved
const int32_t table_38213_13_2_c4[16] = { 5,  6,  7,  8,  5,  6,  7,  8, 18, 20, 18, 20, 18, 20, reserved, reserved}; // index 14-15 reserved

const int32_t table_38213_13_3_c2[16] = {48, 48, 48, 48, 48, 48, 96, 96, 96, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 09-15 reserved
const int32_t table_38213_13_3_c3[16] = { 1,  1,  2,  2,  3,  3,  1,  2,  3, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 09-15 reserved
const int32_t table_38213_13_3_c4[16] = { 2,  6,  2,  6,  2,  6, 28, 28, 28, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 09-15 reserved

const int32_t table_38213_13_4_c2[16] = {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 48, 48, 48, 48, 48, 48};
const int32_t table_38213_13_4_c3[16] = { 2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  1,  1,  1,  2,  2,  2};
const int32_t table_38213_13_4_c4[16] = { 0,  1,  2,  3,  4,  0,  1,  2,  3,  4, 12, 14, 16, 12, 14, 16};

const int32_t table_38213_13_5_c2[16] = {48, 48, 48, 96, 96, 96, 96, 96, 96, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 09-15 reserved
const int32_t table_38213_13_5_c3[16] = { 1,  2,  3,  1,  1,  2,  2,  3,  3, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 09-15 reserved
const int32_t table_38213_13_5_c4[16] = { 4,  4,  4,  0, 56,  0, 56,  0, 56, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 09-15 reserved

const int32_t table_38213_13_6_c2[16] = {24, 24, 24, 24, 48, 48, 48, 48, 48, 48, reserved, reserved, reserved, reserved, reserved, reserved}; // index 10-15 reserved
const int32_t table_38213_13_6_c3[16] = { 2,  2,  3,  3,  1,  1,  2,  2,  3,  3, reserved, reserved, reserved, reserved, reserved, reserved}; // index 10-15 reserved
const int32_t table_38213_13_6_c4[16] = { 0,  4,  0,  4,  0, 28,  0, 28,  0, 28, reserved, reserved, reserved, reserved, reserved, reserved}; // index 10-15 reserved

const int32_t table_38213_13_7_c2[16] = {48, 48, 48, 48, 48, 48, 96, 96, 48, 48, 96, 96, reserved, reserved, reserved, reserved}; // index 12-15 reserved
const int32_t table_38213_13_7_c3[16] = { 1,  1,  2,  2,  3,  3,  1,  2,  1,  1,  1,  1, reserved, reserved, reserved, reserved}; // index 12-15 reserved
const int32_t table_38213_13_7_c4[16] = { 0,  8,  0,  8,  0,  8, 28, 28,-41, 49,-41, 97, reserved, reserved, reserved, reserved}; // index 12-15 reserved, condition A as default

const int32_t table_38213_13_8_c2[16] = { 1,  1,  1,  1,  3,  3,  3,  3, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 15 reserved
const int32_t table_38213_13_8_c3[16] = {24, 24, 48, 48, 24, 24, 48, 48, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 15 reserved
const int32_t table_38213_13_8_c4[16] = { 0,  4, 14, 14,-20, 24,-20, 48, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 15 reserved, condition A as default

const int32_t table_38213_13_9_c2[16] = {96, 96, 96, 96, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 04-15 reserved
const int32_t table_38213_13_9_c3[16] = { 1,  1,  2,  2, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 04-15 reserved
const int32_t table_38213_13_9_c4[16] = { 0, 16,  0, 16, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 04-15 reserved

const int32_t table_38213_13_10_c2[16] = {48, 48, 48, 48, 24, 24, 48, 48, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 08-15 reserved
const int32_t table_38213_13_10_c3[16] = { 1,  1,  2,  2,  1,  1,  1,  1, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 08-15 reserved
const int32_t table_38213_13_10_c4[16] = { 0,  8,  0,  8,-41, 25,-41, 49, reserved, reserved, reserved, reserved, reserved, reserved, reserved, reserved}; // index 08-15 reserved, condition A as default

const float   table_38213_13_11_c1[16] = { 0,  0,  2,  2,  5,  5,  7,  7,  0,  5,  0,  0,  2,  2,  5,  5};	//	O
const int32_t table_38213_13_11_c2[16] = { 1,  2,  1,  2,  1,  2,  1,  2,  1,  1,  1,  1,  1,  1,  1,  1};
const float   table_38213_13_11_c3[16] = { 1, 0.5f, 1, 0.5f, 1, 0.5f, 1, 0.5f,  1,  1,  1,  1,  1,  1,  1,  1};	//	M
const int32_t table_38213_13_11_c4[16] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  1,  2,  1,  2};	// i is even as default

const float   table_38213_13_12_c1[16] = { 0, 0, 2.5f, 2.5f, 5, 5, 0, 2.5f, 5, 7.5f, 7.5f, 7.5f, 0, 5, reserved, reserved}; // O, index 14-15 reserved
const int32_t table_38213_13_12_c2[16] = { 1,  2,  1,  2,  1,  2,  2,  2,  2,  1,  2,  2,  1,  1,  reserved,  reserved}; // index 14-15 reserved
const float   table_38213_13_12_c3[16] = { 1, 0.5f, 1, 0.5f, 1, 0.5f, 0.5f, 0.5f, 0.5f, 1, 0.5f, 0.5f, 1, 1,  reserved,  reserved}; // M, index 14-15 reserved

const int32_t table_38213_10_1_1_c2[5] = { 0, 0, 4, 2, 1 };

/*
 #define mu_pusch 1
// definition table j Table 6.1.2.1.1-4
 #define j ((mu_pusch==3)?3:(mu_pusch==2)?2:1)
 uint8_t table_6_1_2_1_1_2_time_dom_res_alloc_A[16][3]={ // for PUSCH from TS 38.214 subclause 6.1.2.1.1
  {j,  0,14}, // row index 1
  {j,  0,12}, // row index 2
  {j,  0,10}, // row index 3
  {j,  2,10}, // row index 4
  {j,  4,10}, // row index 5
  {j,  4,8},  // row index 6
  {j,  4,6},  // row index 7
  {j+1,0,14}, // row index 8
  {j+1,0,12}, // row index 9
  {j+1,0,10}, // row index 10
  {j+2,0,14}, // row index 11
  {j+2,0,12}, // row index 12
  {j+2,0,10}, // row index 13
  {j,  8,6},  // row index 14
  {j+3,0,14}, // row index 15
  {j+3,0,10}  // row index 16
  };

 #define dmrs_typeA_pos 2
 uint8_t table_5_1_2_1_1_2_time_dom_res_alloc_A[16][3]={ // for PDSCH from TS 38.214 subclause 5.1.2.1.1
  {0,(dmrs_typeA_pos == 2)?2:3, (dmrs_typeA_pos == 2)?12:11}, // row index 1
  {0,(dmrs_typeA_pos == 2)?2:3, (dmrs_typeA_pos == 2)?10:9},  // row index 2
  {0,(dmrs_typeA_pos == 2)?2:3, (dmrs_typeA_pos == 2)?9:8},   // row index 3
  {0,(dmrs_typeA_pos == 2)?2:3, (dmrs_typeA_pos == 2)?7:6},   // row index 4
  {0,(dmrs_typeA_pos == 2)?2:3, (dmrs_typeA_pos == 2)?5:4},   // row index 5
  {0,(dmrs_typeA_pos == 2)?9:10,(dmrs_typeA_pos == 2)?4:4},   // row index 6
  {0,(dmrs_typeA_pos == 2)?4:6, (dmrs_typeA_pos == 2)?4:4},   // row index 7
  {0,5,7},  // row index 8
  {0,5,2},  // row index 9
  {0,9,2},  // row index 10
  {0,12,2}, // row index 11
  {0,1,13}, // row index 12
  {0,1,6},  // row index 13
  {0,2,4},  // row index 14
  {0,4,7},  // row index 15
  {0,8,4}   // row index 16
  };
*/
