#ifndef __NR_RRC_VARS_H__
#define __NR_RRC_VARS_H__

#include "rrc_defs.h"
#include "rrc_defs_LTE.h"
#include "rlc.h"
#include "mac_rrc_primitives.h"
#include "mac.h"
#include "mac_extern.h"

NR_UE_RRC_INST_t *ue_rrc_inst;

UE_PF_PO_t UE_PF_PO[MAX_MOBILES];


#if 0
struct LogicalChannelConfig__ul_SpecificParameters LCSRB1 =  {1,
			LogicalChannelConfig__ul_SpecificParameters__prioritisedBitRate_infinity,
			0,
			&logicalChannelGroup0
};
struct LogicalChannelConfig__ul_SpecificParameters LCSRB2 =  {3,
			LogicalChannelConfig__ul_SpecificParameters__prioritisedBitRate_infinity,
			0,
			&logicalChannelGroup0
};


#if (RRC_VERSION < MAKE_VERSION(15, 0, 0))
struct LTE_LogicalChannelConfig__ext1 logicalChannelSR_Mask_r9_ext1 = {
         logicalChannelSR_Mask_r9: &logicalChannelSR_Mask_r9
};
#endif

// These are the default SRB configurations from 36.331 (Chapter 9, p. 176-179 in v8.6)
LogicalChannelConfig_t  SRB1_logicalChannelConfig_defaultValue = {ul_SpecificParameters: &LCSRB1
#if (RRC_VERSION >= MAKE_VERSION(15, 0, 0))
                                                                  ,
                                                                  ext1: &logicalChannelSR_Mask_r9_ext1
#endif
                                                                 };

LogicalChannelConfig_t SRB2_logicalChannelConfig_defaultValue = {ul_SpecificParameters: &LCSRB2
#if (RRC_VERSION < MAKE_VERSION(9, 0, 0))
                                                                 ,
                                                                 ext1: &logicalChannelSR_Mask_r9_ext1
#endif
							}
#endif


//CONSTANTS
rlc_info_t Rlc_info_um, Rlc_info_am_config;
uint16_t RACH_FREQ_ALLOC;
//uint8_t NB_RACH;
LCHAN_DESC BCCH_LCHAN_DESC,CCCH_LCHAN_DESC,DCCH_LCHAN_DESC,DTCH_DL_LCHAN_DESC,DTCH_UL_LCHAN_DESC;
MAC_MEAS_T BCCH_MEAS_TRIGGER,CCCH_MEAS_TRIGGER,DCCH_MEAS_TRIGGER,DTCH_MEAS_TRIGGER;
MAC_AVG_T BCCH_MEAS_AVG, CCCH_MEAS_AVG,DCCH_MEAS_AVG, DTCH_MEAS_AVG;


// timers 3GPP 38.331 R15
uint16_t T300[8] = {100, 200, 300, 400, 600, 1000, 1500, 2000};
uint16_t T301[8] = {100, 200, 300, 400, 600, 1000, 1500, 2000};
uint32_t T304[8] = {50, 100, 150, 200, 500, 1000, 2000, 10000};
uint16_t T310[8] = {0, 50, 100, 200, 500, 1000, 2000};
uint16_t N310[8] = {1, 2, 3, 4, 6, 8, 10, 20};
uint16_t N311[8] = {1, 2, 3, 4, 6, 8, 10, 20};
uint16_t T319[8] = {100, 200, 300, 400, 600, 1000, 1500, 2000};

// TimeToTrigger enum mapping table (38.331 TimeToTrigger IE)
uint32_t timeToTrigger_ms[16] = {0, 40, 64, 80, 100, 128, 160, 256, 320, 480, 512, 640, 1024, 1280, 2560, 5120};

/* 38.133-f60_s0-11.doc Section 10.1.6 RSRP Measurement Report Mapping, Table: 10.1.6.1-1 */
float RSRP_meas_mapping_quantity[128] = {
	-156, -155, -154, -153, -152, -151, -150, -149, -148, -147, -146, -145, -144, -143, -142, -141, -140, -139, -138, -137, -136, -135, -134, -133, -132,
	-131, -130, -129, -128, -127, -126, -125, -124, -123, -122, -121, -120, -119, -118, -117, -116, -115, -114, -113, -112, -111, -110, -109, -108, -107,
	-106, -105, -104, -103, -102, -101, -100, -99, -98, -97, -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79,
	-78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49,
	-48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33, -32, -31, 0xFFFFFFFF};

/* 38.133-f60_s0-11.doc Section 10.1.6 RSRP Measurement Report Mapping, Table: 10.1.6.1-2 */
float RSRP_meas_mapping_differential[16] = {-2, -4, -6, -8, -10, -12, -14, -16, -18, -20, -22, -24, -26, -28, -30};

/* 38.133-f60_s0-11.doc Section 10.1.11 RSRQ Measurement Report Mapping, Table: 10.1.11.1-1 */
float RSRQ_meas_mapping[128] = {-43, -42.5, -42, -41.5, -41, -40.5, -40, -39.5, -39, -38.5, -38, -37.5, -37, -36.5, -36, -35.5, -35,
		-34.5, -34, -33.5, -33, -32.5, -32, -31.5, -31, -30.5, -30, -29.5, -29, -28.5, -28, -27.5, -27, -26.5, -26, -25.5, -25, -24.5, -24, -23.5, -23,
		-22.5, -22, -21.5, -21, -20.5, -20, -19.5, -19, -18.5, -18, -17.5, -17, -16.5, -16, -15.5, -15, -14.5, -14, -13.5, -13, -12.5, -12, -11.5, -11,
		-10.5, -10, -9.5, -9, -8.5, -8, -7.5, -7, -6.5, -6, -5.5, -5, -4.5, -4, -3.5, -3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5,
		5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20};

#endif
