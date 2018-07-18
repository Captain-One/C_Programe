#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "pcap.h"

#define ARRY_SIZE(a)   sizeof(a)/sizeof(a[0])

int main(int argc, char *argv[])
{
	FILE *fpcap;

	uint8_t direction = 0;
	uint8_t radiotype = 2;

	uint8_t data[] = {0x22,0x08,0x3d,0x58,0x94,0xd4,0x28,0x26,
					  0xba,0x5f,0xfe,0xe2,0xc6,0xd2,0xff,0x36,
					  0x18,0x06,0xab,0x2d,0x03,0x21,0x99,0x01,
					  0x81,0x69,0x00,0x99,0xdb,0x2d,0x45,0x79,
					  0x38,0x04,0x04,0xa3,0x40}; //dl dcch;

	int data_len = ARRY_SIZE(data);
   // printf("data len %d\n",data_len);
	pcap_header pcapheader;
	packet_header packetheader;

	fpcap = fopen("rrc_data.pcap","wb+");
	if(fpcap == NULL)
	{
		perror("open *.pcap file error: ");
		return -1;
	}
	pcapheader.linktype = 0x94;
	pcapheader.magic = 0xa1b2c3d4;
	pcapheader.major = 2;
	pcapheader.minor = 4;
	pcapheader.sigfigs = 0;
	pcapheader.snaplen = 0xffff;
	pcapheader.thiszone = 0x7080; //GMT beijing 8h

	fwrite(&pcapheader,1,sizeof(pcap_header),fpcap);

	packetheader.len = sizeof(packet_header) - 16 + data_len;
	packetheader.caplen = packetheader.len;
	packetheader.timestamph = 0;
	packetheader.timestampl = 0;

	fwrite(&packetheader,1,sizeof(packet_header),fpcap);
	fwrite(data,1,data_len,fpcap);
	fclose(fpcap);
}
