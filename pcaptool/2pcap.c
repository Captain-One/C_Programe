#include <stdio.h>
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
}fpackheader;


typedef struct tv_s {
	uint32_t tvsec;
	uint32_t Res3:8;
	uint32_t tvusec:24;
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
#define C-RNTI    3
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
			uint16_t    systemframe:4;
	        uint16_t    subframe:12;	        
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


int main(int argc, char * argv[])
{
	int i;
	for(i=0;i<argc;i++)
	{
		printf("%s \n",argv[i]);
	}
	FILE *fddata,*fdpcap;
	//fddata = fopen("","rb");
	fdpcap = fopen("pcap.pcap","wb+");
	uint8_t data[4] = {0,0,0,0};
	
	printf("sub is %d \n",sizeof(subpcakage_header)); 
	
	pcap_header pcapheader = {.magic = 0xa1b2c3d4,.major = 2,.minor = 4,.thiszone = 0,.sigfigs = 0,.snaplen = 0xffff,.linktype = 0x93};
	packet_header packetheader = {.timestamph = 0,.timestampl = 0,.caplen = 0x15,.len = 0x15,.direction = 0,.rntitype = 1,
	                              .rnti_tag = 2,.ueid_tag = 3,.frame_subframe_tag = 4,.predefined_data_tag = 5,.crc_status_tag = 7,.lte_payload_tag = 1}; //.radiotype = 2

    packetheader.radiotype = argv[1] - '0';
	rv = read_data(filename,buf);
	if(rv < 0)
	{
		printf("read pack data error!!!\n");
		errorpackcount ++;
	}
	
	packetheader.direction = ((fpackheader *)buf)->RFB_DIR;
	
	
	packetheader.rnti = X_16(12);
	packetheader.ueid = X_16(12);
	packetheader.frame_subframe.u16_frame_subframe_t.subframe = 3;
	packetheader.frame_subframe.u16_frame_subframe_t.systemframe  = 0b1111;
	packetheader.frame_subframe.u16_frame_subframe = X_16(packetheader.frame_subframe.u16_frame_subframe);
	packetheader.predefined_data = 0;
	packetheader.crc_status = 1;
	//packetheader.lte_payload = data;
	printf("ueid = 0x%02x \n",packetheader.ueid);
	//printf("subframe = 0x%02x \n",packetheader.subframe);
	fwrite(&pcapheader,1,sizeof(pcap_header),fdpcap);
	fwrite(&packetheader,1,sizeof(packet_header),fdpcap);
	fwrite(data,1,4,fdpcap);
	//char i;
	for(i=1;i<50;i++)
	{
		packetheader.rntitype = i;
		//fwrite(&pcapheader,1,sizeof(pcap_header),fdpcap);
	    fwrite(&packetheader,1,sizeof(packet_header),fdpcap);
	    fwrite(data,1,4,fdpcap);
	}
	fclose(fdpcap);
	0;
}

int read_data(char *filename , void *buf)
{
	FILE *fd ;
	int rtsize;
	int errorpackcount = 0;
	void *subbuf;
	subpcakage_header *psubheader;
	
	fd = fopen("filename","rb+");
	fpackheader fpheader;
	rtsize = fread(&fpheader,1,sizeof(fpackheader),fd);
	if(rtsize != sizeof(fpackheader))
	{
		return -1;
	}
    subbuf = malloc(fpheader.LEN - sizeof(fpackheader));
	if(subbuf == NULL)
	{
		return -2;
	}
	rtsize = fread(subbuf,1,(fpheader.LEN - sizeof(fpackheader)),fd);
	if(rtsize != (fpheader.LEN - sizeof(fpackheader)))
	{
		return -1;
	}
	psubheader = (subpcakage_header *)subbuf;
	switch(psubheader->subtype.subtype_u)
	{
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
		case 7:break;
		case 8:break;
		case 9:break;
		default :break;
	}
	printf("subtype is 0x%02x \n ",psubheader->subtype.subtype_u);
	
}


























