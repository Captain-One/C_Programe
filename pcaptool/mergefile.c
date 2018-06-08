#include <stdio.h>
#include <stdint.h>
#include "type.h"

int main()
{
	FILE *fddat,*fdidx,*fdmerge;
	fddat = fopen("2_0.dat","rb+");
	if(fddat == NULL)
	{
		perror("open dat file error:");
		return -1;
	}
	fdidx = fopen("2_0.idx","rb+");
	if(fddat == NULL)
	{
		perror("open idx file error:");
		return -1;
	}
	fdmerge = fopen("mergedat.dat","wb+");
	if(fddat == NULL)
	{
		perror("open merge file error:");
		return -1;
	}
	
	uint8_t buf[65536];
	int errorcount = 0;
	int i;
	int idxflen;
	if(fdidx == NULL)
	{
		perror("openfile:");
		return -1;
	}
    fseek(fdidx,0,SEEK_END);
	idxflen = ftell(fdidx)/sizeof(Pnode_t);
	printf("node number is %d \n",idxflen);
	fseek(fdidx,0,SEEK_SET);
	//uint8_t buff[16];
	int rs = 0;
    printf("sizeof(Pnode_t) len is %ld \n",sizeof(Pnode_t));
	Pnode_t node;
	//node = malloc(sizeof(Pnode_t));
	for(i=0;i<idxflen;i++)
	{
		rs = fread(&node,1,sizeof(Pnode_t),fdidx);
		//printf("read len is 0x%d \n",rs);
		//node = (Pnode_t *)buf;
		//printf("pk len is 0x%02x \n",node->plen);
		//printf("fnum len is 0x%02x \n",node->fnum);
		//printf("offset len is 0x%04x \n",node->offset);
		//printf("sn len is 0x%08x \n",node->sn.sn_u64);
		fseek(fddat,node.offset,SEEK_SET);
		rs = fread(buf,1,node.plen,fddat);
		if(rs != node.plen)
		{
			errorcount ++ ;
			break;
		}		
		fwrite(buf,1,node.plen,fdmerge);
	}
	printf("errorcount is %d \n",errorcount);
	fclose(fdidx);
	fclose(fddat);
	fclose(fdmerge);
}
