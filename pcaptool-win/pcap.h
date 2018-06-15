#ifndef  __PCAP_H
#define  __PCAP_H

#include <stdint.h>
#define X_16(x) ((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8)) 

#define X_32(x) ((((x) & 0x00ff0000) >> 8) \
	| (((x) & 0x0000ff00) << 8) \
	| (((x) & 0xff000000) >> 24) \
	| (((x) & 0x000000ff) << 24))
	
#pragma pack(1)
	
typedef struct MAC_PDU_FrameHeader
{
    uint16_t    PH_MARK;
    uint16_t    LEN;

    uint8_t     SLOTID : 4;
    uint8_t     BD_TYPE : 4;

    uint8_t		DST_RFBN : 4;
    uint8_t     DST_BD_TYPE : 3;
    uint8_t     IS_SINGLE_SUBPACKET : 1;

    uint8_t     PCI_8 : 1;
    uint8_t     RFB_DIR : 1;
    uint8_t     REV1 : 2;
    uint8_t     RFBN : 4;

    uint8_t     PCI_7_0;
}fpackheader_t;


typedef struct tv_s {
	uint32_t tvsec;
	union{
		struct{
			uint32_t tvusec:24;
	        uint32_t Res3:8;
		}tvusec_t;
		uint32_t tvusec_u;
	}u_usec;
} tv_t;

union subtype_tag{
	struct{
		uint16_t LCH:4;
		uint16_t TrCH:4;
		uint16_t PCH:4;
		uint16_t subtype:3;
		uint16_t res:1;
	}subtype_t;
	uint16_t subtype_u;
};

struct subpackheader_tv_t{
	uint16_t  len;
	union subtype_tag  subtype;	
	tv_t tv;
};

typedef union subpackage_header_t {
	uint16_t len;
	union subtype_tag subtype;
    struct subpackheader_tv_t subpackheader_tv;
}subpcakage_header;

typedef struct pcap_header_t{
	uint32_t	magic;
	uint16_t    major;
    uint16_t	minor;
	uint32_t    thiszone;
	uint32_t    sigfigs;
	uint32_t    snaplen;
	uint32_t    linktype;
}pcap_header;


typedef struct packet_header_t{
	uint32_t   timestamph;
	uint32_t   timestampl;
	uint32_t   caplen;
	uint32_t   len;
#define FDD 1
#define TDD 2
	uint8_t     radiotype;  //1:fdd,2:tdd
#define UPLINK 0
#define DOWNLINK 1
	uint8_t     direction;
#define NO_RNTI   0
#define P_RNTI	  1
#define RA_RNTI	  2
#define C_RNTI    3
#define SI_RNTI   4
#define SPS_RNTI  5
#define M_RNTI   6
#define SL_BCH_RNTI 7
#define SL_RNTI  8
#define SC_RNTI  9
#define G_RNTI   10
 	uint8_t     rntitype;
	uint8_t     rnti_tag; //0x02
	uint16_t    rnti;
	uint8_t     ueid_tag; //0x03
	uint16_t    ueid;
	uint8_t     frame_subframe_tag; //0x04
	union {
		struct {
			uint16_t    subframe:4;	
			uint16_t    systemframe:12;			
		}u16_frame_subframe_t;
		uint16_t    u16_frame_subframe;
	}frame_subframe;
	uint8_t     predefined_data_tag; //0x05
	uint8_t     predefined_data;
	uint8_t     crc_status_tag; //0x07
	uint8_t     crc_status;  //
	uint8_t     lte_payload_tag; //0x01
}packet_header;
#pragma pack() 

int data_pro(uint8_t *buf,FILE *fd,uint8_t direction,uint8_t radiotype);
int data_2_pcap(FILE *fd,uint8_t radiotype,char *filename);

#endif