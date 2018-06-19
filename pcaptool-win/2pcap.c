#include <stdio.h>
#include <stdlib.h>
#include "mergedata.h"
#include "pcap.h"

int data_2_pcap(FILE *fd,uint8_t radiotype,char *filename)
{
	int fsize;
	fpackheader_t  fpkheader;
	int rs;
	int rv;
	int arsize = 0;
	uint8_t *subpkbuf;
	FILE *fpcap;
	uint8_t direction;
	int i = 0;
	uint8_t t;
	pcap_header pcapheader;

	fpcap = fopen(filename,"wb");
	if(fpcap == NULL)
	{
		perror("open *.pcap file error: ");
		return -1;
	}
	pcapheader.linktype = 0x93;
	pcapheader.magic = 0xa1b2c3d4;
	pcapheader.major = 2;
	pcapheader.minor = 4;
	pcapheader.sigfigs = 0;
	pcapheader.snaplen = 0xffff;
	pcapheader.thiszone = 0x7080; //GMT beijing 8h

	rv = fwrite(&pcapheader,1,sizeof(pcap_header),fpcap);

	fsize = get_file_size(fd);
	if(fsize < 0)
	{
		printf("get file size error\n");
		return -1;
	}
	printf("mergedata size : %d \n",fsize);
	
	while(arsize < fsize)//fsize
	{
		rs = fread(&fpkheader,1,sizeof(fpackheader_t),fd);
		if(rs != sizeof(fpackheader_t))
		{
			printf("read f data error\n");
			return -1;
		}
		if(fpkheader.PH_MARK != 0xbadc)
		{
			printf("i: %d fpkheader.PH_MARK 0x%04x\n",i,fpkheader.PH_MARK);
			arsize+=8;
			return -1;
		}
		//printf("X_16(fpkheader.LEN) : 0x%04x\n",X_16(fpkheader.LEN));
		subpkbuf = (uint8_t *)malloc(X_16(fpkheader.LEN)-sizeof(fpackheader_t));
		if(subpkbuf == NULL)
		{
			printf("malloc subpkbuf error\n");
			return -1;
		}
		rs = fread(subpkbuf,1,X_16(fpkheader.LEN)-sizeof(fpackheader_t),fd);		
		if(rs != (X_16(fpkheader.LEN)-sizeof(fpackheader_t)))
		{
			perror("read error:");
			printf("read sub data error\n");
			return -1;
		}
		i++;
	/*	for(i=0;i<(X_16(fpkheader.LEN)-sizeof(fpackheader_t));i++)
		{
			printf("0x%02x ",*(subpkbuf+i));
		}
		printf("\n");*/
		direction = fpkheader.RFB_DIR;
		rv = data_pro(subpkbuf,fpcap,direction,radiotype);
		arsize += X_16(fpkheader.LEN);
		free(subpkbuf);
	}
	fclose(fpcap);
}

int mib_count = 0;
int sib_count = 0;

int data_pro(uint8_t *buf,FILE *fd,uint8_t direction,uint8_t radiotype)
{
	
	packet_header packetheader;
	subpcakage_header *subpackheader;
	uint16_t subtype;
	uint8_t pass = 0;

	subpackheader = (subpcakage_header *)buf;

	packetheader.len = sizeof(packet_header) - 16 + X_16(subpackheader->len) - sizeof(subpcakage_header) + 2;
	packetheader.caplen = packetheader.len;	

    //printf("subpackheader->len:0x%04x\n",X_16(subpackheader->len));
	// printf("packetheader.len:0x%04x\n",packetheader.len);
	packetheader.radiotype = radiotype;
	packetheader.direction = direction ^ 0x01;
	packetheader.timestamph = X_32(subpackheader->subpackheader_tv.tv.tvsec);
	packetheader.timestampl = X_32(subpackheader->subpackheader_tv.tv.u_usec.tvusec_u) & 0x0fffffff;

	packetheader.lte_payload_tag = 0x01;
	packetheader.rnti_tag = 0x02;
	packetheader.rntitype = 0;  //
	packetheader.rnti = 0;
	packetheader.ueid_tag = 0x03;
	packetheader.ueid = 0;
	packetheader.frame_subframe_tag = 0x04;
	packetheader.frame_subframe.u16_frame_subframe = 0;
	packetheader.predefined_data_tag = 0x05;
	packetheader.predefined_data = 0;
	packetheader.crc_status_tag = 0x07;
	packetheader.crc_status = 1;

	subtype = X_16(subpackheader->subpackheader_tv.subtype.subtype_u) &0x0fff;
	buf += sizeof(subpcakage_header);

	switch(subtype)
	{
	    case 0x0111:packetheader.rntitype = 0;
			        mib_count++;
					if(mib_count > 10)
						pass = 1;
	                break;//BCCH
		case 0x0522:break;//PCCH
		case 0x0853:break;//CCCH UL
		case 0x0533:break;//CCCH DL
		case 0x0854:break;//DCCH DL
		case 0x0534:break;//DCCH DL
		case 0x0855:break;//DTCH UL
		case 0x0535:break;//DTCH DL
		case 0x0966:break;//MCCH
		case 0x0967:break;//MTCH
		case 0x0640:packetheader.frame_subframe.u16_frame_subframe_t.subframe = (X_16(*(uint16_t *)buf) & 0x3c00)>>10;
					packetheader.frame_subframe.u16_frame_subframe_t.systemframe = X_16(*(uint16_t *)buf) & 0x03ff;
					packetheader.frame_subframe.u16_frame_subframe = X_16(packetheader.frame_subframe.u16_frame_subframe);	
			        //printf("packetheader.frame_subframe.u16_frame_subframe: 0x%02x\n",(X_16(*(uint16_t *)buf) & 0x3c00)>>10);
			        packetheader.rnti = X_16(*((uint16_t *)(buf+2)));
					//printf("packetheader.rnti 0x%02x\n", X_16(*((uint16_t *)buf+2)));
					packetheader.ueid = packetheader.rnti;
					packetheader.len = packetheader.len-4;
					packetheader.caplen = packetheader.len;
					buf += 4;break;//RACH
		case 0x0300:break;//PHICH
		case 0x0200:break;//PCFICH
		case 0x0400:break;//PDCCH
		case 0x0700:break;//PUCCH
		case 0x0530:packetheader.frame_subframe.u16_frame_subframe_t.subframe = (X_16(*(uint16_t *)buf) & 0x3c00)>>10;
					packetheader.frame_subframe.u16_frame_subframe_t.systemframe = X_16(*(uint16_t *)buf) & 0x03ff;
					packetheader.frame_subframe.u16_frame_subframe = X_16(packetheader.frame_subframe.u16_frame_subframe);			
			        //printf("packetheader.frame_subframe.u16_frame_subframe: 0x%02x\n",packetheader.frame_subframe.u16_frame_subframe_t.systemframe);
			        packetheader.rnti = X_16(*((uint16_t *)(buf+2)));
					//printf("packetheader.rnti 0x%02x\n", X_16(*((uint16_t *)(buf+2))));
					packetheader.ueid = packetheader.rnti;
					if(packetheader.rnti == 0xffff)
					{
						packetheader.rntitype = 4;
						sib_count ++;
						if(sib_count > 10)
							pass = 1;
					}else{
						packetheader.rntitype = 3;
					}
					packetheader.len = packetheader.len-4;
					packetheader.caplen = packetheader.len;
					buf += 4;	
					break;//DL-SCH
		case 0x0850:packetheader.frame_subframe.u16_frame_subframe = X_16(*(uint16_t *)buf);
			        packetheader.rnti = X_16(*((uint16_t *)(buf+2)));
					packetheader.ueid = packetheader.rnti;
					packetheader.rntitype = 3;
					packetheader.len = packetheader.len-4;
					packetheader.caplen = packetheader.len;
					buf += 4;	
					break;//UL-SCH
		default:break;
	}	
	if(!pass)
	{
		fwrite(&packetheader,1,sizeof(packet_header),fd);
		fwrite(buf,1,packetheader.len-(sizeof(packet_header)-16),fd);
	}
}