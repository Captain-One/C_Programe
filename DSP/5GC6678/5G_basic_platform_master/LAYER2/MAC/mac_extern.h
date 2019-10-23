#include "mac_defs.h"

extern NR_UE_MAC_INST_t *ue_mac_inst;

extern const uint32_t BSR5_TABLE[BSR5_TABLE_SIZE];
extern const uint32_t BSR8_TABLE[BSR8_TABLE_SIZE];

extern const uint16_t BACKOFF[16];

extern const int32_t table_38213_13_1_c2[16];
extern const int32_t table_38213_13_1_c3[16];
extern const int32_t table_38213_13_1_c4[16];

extern const int32_t table_38213_13_2_c2[16];
extern const int32_t table_38213_13_2_c3[16];
extern const int32_t table_38213_13_2_c4[16];

extern const int32_t table_38213_13_3_c2[16];
extern const int32_t table_38213_13_3_c3[16];
extern const int32_t table_38213_13_3_c4[16];

extern const int32_t table_38213_13_4_c2[16];
extern const int32_t table_38213_13_4_c3[16];
extern const int32_t table_38213_13_4_c4[16];

extern const int32_t table_38213_13_5_c2[16];
extern const int32_t table_38213_13_5_c3[16];
extern const int32_t table_38213_13_5_c4[16];

extern const int32_t table_38213_13_6_c2[16];
extern const int32_t table_38213_13_6_c3[16];
extern const int32_t table_38213_13_6_c4[16];

extern const int32_t table_38213_13_7_c2[16];
extern const int32_t table_38213_13_7_c3[16];
extern const int32_t table_38213_13_7_c4[16];

extern const int32_t table_38213_13_8_c2[16];
extern const int32_t table_38213_13_8_c3[16];
extern const int32_t table_38213_13_8_c4[16];

extern const int32_t table_38213_13_9_c2[16];
extern const int32_t table_38213_13_9_c3[16];
extern const int32_t table_38213_13_9_c4[16];

extern const int32_t table_38213_13_10_c2[16];
extern const int32_t table_38213_13_10_c3[16];
extern const int32_t table_38213_13_10_c4[16];

extern const float   table_38213_13_11_c1[16];
extern const int32_t table_38213_13_11_c2[16];
extern const float   table_38213_13_11_c3[16];
extern const int32_t table_38213_13_11_c4[16];

extern const float   table_38213_13_12_c1[16];
extern const int32_t table_38213_13_12_c2[16];
extern const float   table_38213_13_12_c3[16];

extern const int32_t table_38213_10_1_1_c2[5];

//  DCI extraction
//  for PUSCH from TS 38.214 subclause 6.1.2.1.1
extern uint8_t table_6_1_2_1_1_2_time_dom_res_alloc_A[16][3];
//  for PDSCH from TS 38.214 subclause 5.1.2.1.1
extern uint8_t table_5_1_2_1_1_2_time_dom_res_alloc_A[16][3];
