#include <sys/types.h>  
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

#include "list.h"



//数据包索引号结构体
typedef union seqnum_u
{
	struct {
		uint64_t sn:60;
		uint64_t RFBN:4;
		} sn1;
	struct {
		uint32_t sn_l;
		uint32_t sn_h;
	} sn2;
	uint64_t sn_u64;
} SN_t;

//包结点结构体
typedef struct pnode_s
{
	uint16_t plen;		//节点数据长度
	uint16_t fnum;		//数据存放的文件编号，以前的设计，当一次存储的数据文件超过2G时，会把数据存储到下一个文件，这个是指数据文件序号
	uint32_t offset;
	SN_t sn;
} Pnode_t;


typedef struct merge_node_t{
	uint8_t frbn;
	uint8_t pkcount;
}merge_node;

int Data_File_Handle(void *idxnodebuf, int idxnodenum, uint8_t rfbn,FILE *fdmerge,char *path);
int Merge_File_Handle(FILE *fd,List *list,char *path);
int mergedata(merge_node *mergenode,List *list,FILE * fdidx,char *path);
int Search_Same_File(List *list,char *str);
int close_idx_file(FILE *rfbn_fd_p[]);

#define  MAX_PATH_LEN    22

#define  MAX_MERGE_FILENAME_LEN   13   //merge_xxx.idx

#define  MAX_OPEN_FILE_NAME_LEN    MAX_PATH_LEN + MAX_MERGE_FILENAME_LEN

#define  MERGE_DATA_FILE_NAME_LEN  13

FILE *fdMergedata;

int main(int argc, char *argv[])
{
	DIR *datadir;
	char * path = argv[1];
	char mergedatafilename[MAX_PATH_LEN + MERGE_DATA_FILE_NAME_LEN];
	struct dirent *filename;
	char *dfilename; 
    char merge[] = {"merge_"};
	int mergenumber;
	int filenum;
	int rv;
	int i;
	char mergefilename[MAX_OPEN_FILE_NAME_LEN];
	FILE *fd;
	List fnlist;
	sprintf(mergedatafilename,"./%s/mergedata.dat",path);
	fdMergedata = fopen(mergedatafilename,"wb+");
	if(fdMergedata == NULL)
	{
		printf("open mergedata.dat file error !\n");
		return 0;
	}
	List_Init(&fnlist);
	
	datadir = opendir(path);
	printf("%s\n",path);
	
	while(filename=readdir(datadir))
	{
	    rv = List_Add(&fnlist,fnlist.tail,filename->d_name);
		if(rv < 0)
		{
			printf("add list error\n");
		}
		printf("filename:%-10s\n",filename->d_name);//,filename->d_ino,filename->d_reclen d_info:%ld\t d_reclen:%us           
	}
	filenum = fnlist.count;
	printf("find %d file!\n",filenum);
	
	mergenumber = Search_Same_File(&fnlist,merge);
	if(mergenumber < 0)
	{
		printf("can not find merge_x.idx file \n");
		fclose(fdMergedata);
		closedir(datadir);
		return -1;
	}
	printf("find %d merge file\n",mergenumber);
	
	for(i=0;i<mergenumber;i++)
	{
		sprintf(mergefilename,"./%s/merge_%d.idx",path,i);
		printf("%s \n",mergefilename);
		
		fd = fopen(mergefilename,"rb+");
		if(fd == NULL)
	    {
		    printf("merge_x.idx file open error!\n");
			fclose(fdMergedata);
			closedir(datadir);
		    return -1;
	    }
		rv = Merge_File_Handle(fd,&fnlist,path);
		if(rv < 0)
		{
			printf("File Handle Error!!!\n");
			fclose(fdMergedata);
			fclose(fd);
			closedir(datadir);
			return -1;
		}
        fclose(fd);
	}
	closedir(datadir);
	fclose(fdMergedata);
}

#define MAX_RFBN_NUM    11

int Merge_File_Handle(FILE *fd,List *list,char *path)
{
	int size,resize ;
	int i;
	int mergenodecount=0;
	char idxfilename[MAX_OPEN_FILE_NAME_LEN];
	int idxfilenum;
	merge_node mergenode;
	int rv;
	int pkcount;
	
	uint8_t rfbn_mark[MAX_RFBN_NUM];
	uint8_t rfbn_idx_file_num[MAX_RFBN_NUM];
	uint8_t rfbn_idx_file_count[MAX_RFBN_NUM];
	int rfbn_idx_file_size[MAX_RFBN_NUM];
	uint32_t rfbn_idx_read_count[MAX_RFBN_NUM];
	FILE *rfbn_fd_p[MAX_RFBN_NUM];
	
	memset(rfbn_mark,0,MAX_RFBN_NUM*sizeof(uint8_t));
	memset(rfbn_idx_file_num,0,MAX_RFBN_NUM*sizeof(uint8_t));
	memset(rfbn_idx_file_count,0,MAX_RFBN_NUM*sizeof(uint8_t));
	memset(rfbn_idx_file_size,0,MAX_RFBN_NUM*sizeof(int));
	memset(rfbn_idx_read_count,0,MAX_RFBN_NUM*sizeof(uint32_t));
	memset(rfbn_fd_p,0,MAX_RFBN_NUM*sizeof(FILE *));
	
	//printf("into Merge_File_Handle \n");
	fseek(fd,0,SEEK_END);
	size = ftell(fd)-2;
	fseek(fd,2,SEEK_SET); //
	printf("mergeidx size %d\n",size);
	if(size < 0)
	{
		printf("get merge_xx file size error !\n");
		return -1;
	}
    
	for(i=0;i<size/2;i++)
	{
		resize = fread(&mergenode,1,sizeof(merge_node),fd);
		if(resize != sizeof(merge_node))
		{
			printf("read merge dat error !\n");
		}
		if(rfbn_mark[mergenode.frbn] == 0)
		{
			rfbn_mark[mergenode.frbn] = 1;
			sprintf(idxfilename,"%d_*.idx",mergenode.frbn);
	        idxfilenum = Search_Same_File(list,idxfilename);
			if(idxfilenum < 0)
			{
				printf("Search %s file error\n",idxfilename);
				return -1;
			}
			rfbn_idx_file_num[mergenode.frbn] = idxfilenum;
			printf("find %d idx file\n",idxfilenum);
			
			sprintf(idxfilename,"./%s/%d_0.idx",path,mergenode.frbn);
            rfbn_fd_p[mergenode.frbn] = fopen(idxfilename,"rb+");			
			if(rfbn_fd_p[mergenode.frbn] == NULL)
			{
				printf("open %s error\n",idxfilename);
				//close other file?;
				return -1;
			}
			
            fseek(rfbn_fd_p[mergenode.frbn],0,SEEK_END);
            rfbn_idx_file_size[mergenode.frbn] = ftell(rfbn_fd_p[mergenode.frbn]);
            fseek(rfbn_fd_p[mergenode.frbn],0,SEEK_SET);	
            printf("%s size is %d, has %d node\n",idxfilename,rfbn_idx_file_size[mergenode.frbn],rfbn_idx_file_size[mergenode.frbn]/16);			
		}	
		
		if((rfbn_idx_read_count[mergenode.frbn]) > rfbn_idx_file_size[mergenode.frbn])
		{
			pkcount = mergenode.pkcount;
			mergenode.pkcount = rfbn_idx_file_size[mergenode.frbn] - ftell(rfbn_fd_p[mergenode.frbn]);
			rv = mergedata(&mergenode,list,rfbn_fd_p[mergenode.frbn],path);
			//error check;
			fclose(rfbn_fd_p[mergenode.frbn]);
			rfbn_idx_file_count[mergenode.frbn] ++;
			if(rfbn_idx_file_count[mergenode.frbn] < rfbn_idx_file_num[mergenode.frbn])
			{
			  printf(idxfilename,"./%s/%d_%d.idx",path,mergenode.frbn,rfbn_idx_file_count[mergenode.frbn]);
			  rfbn_fd_p[mergenode.frbn] =  fopen(idxfilename,"rb+");
			  fseek(rfbn_fd_p[mergenode.frbn],0,SEEK_END);
              rfbn_idx_file_size[mergenode.frbn] = ftell(rfbn_fd_p[mergenode.frbn]);
              fseek(rfbn_fd_p[mergenode.frbn],0,SEEK_SET);
			  mergenode.pkcount = pkcount - mergenode.pkcount;
			  rv =  mergedata(&mergenode,list,rfbn_fd_p[mergenode.frbn],path);
			}else{
				printf("no more idx file for %d rfbn\n",mergenode.frbn);
			}
		}else{
			rv = mergedata(&mergenode,list,rfbn_fd_p[mergenode.frbn],path);
		}	    		
		rfbn_idx_read_count[mergenode.frbn] = rfbn_idx_read_count[mergenode.frbn] + mergenode.pkcount*sizeof(Pnode_t);
        printf("%d rfbn_idx_read_count[%d] %d \n",i,mergenode.frbn,rfbn_idx_read_count[mergenode.frbn]);
		mergenodecount ++;       		
	}
	close_idx_file(rfbn_fd_p);
	printf("mergenodecount %d\n",mergenodecount);
}

int close_idx_file(FILE *rfbn_fd_p[])
{
	int i;
	for(i=0;i<MAX_RFBN_NUM;i++)
	{
		if(rfbn_fd_p[i] != NULL)
		{
			fclose(rfbn_fd_p[i]);
		}
	}
	return 0;
}

#define MAX_IDX_FILENAME_LEN    10//xx_nnn.idx

int mergedata(merge_node *mergenode,List *list,FILE * fdidx,char *path)
{
	int readsize,rv;
	void *idxnodebuf;
	//printf("into mergedata \n");
	
	idxnodebuf = malloc(mergenode->pkcount*sizeof(Pnode_t));
	if(idxnodebuf == NULL)
	{
		printf("malloc idxnode buf error \n");
		return -1;
	}
	readsize = fread(idxnodebuf,1,mergenode->pkcount*sizeof(Pnode_t),fdidx);		 
	if(readsize != mergenode->pkcount*sizeof(Pnode_t))	
	{
		printf("read idx data error \n");
		free(idxnodebuf);
		return -1;
	}	
	rv = Data_File_Handle(idxnodebuf,mergenode->pkcount,mergenode->frbn,fdMergedata,path);
	if(rv < 0)
		printf("Data File Handle Error !\n");
	free(idxnodebuf);	
}

#define MAX_DATA_FILENAME_LEN    10//xx_nnn.dat

int Data_File_Handle(void *idxnodebuf, int idxnodenum, uint8_t rfbn,FILE *fdmerge,char *path)
{
	FILE *fd;	
	int i,j,rsize,rv;
	uint8_t *buf;
	//int8_t *idxbuf = idxnodebuf;
	char datafilename[MAX_OPEN_FILE_NAME_LEN];

	for(i=0;i<idxnodenum;i++)
	{
		sprintf(datafilename,"./%s/%d_%d.dat",path,rfbn,((Pnode_t *)idxnodebuf)->fnum);
		fd = fopen(datafilename,"rb+");	
		if(fd == NULL)
		{
			printf("open %s file error !!! \n",datafilename);
			return -1;		
		}
		
		buf = malloc(((Pnode_t *)idxnodebuf)->plen);
		if(buf == NULL)
		{
			printf("malloc data buf error !\n");
			fclose(fd);
			return -1;			
		}
		
		fseek(fd,((Pnode_t *)idxnodebuf)->offset,SEEK_SET);
		rsize = fread(buf,1,((Pnode_t *)idxnodebuf)->plen,fd);
		if(((Pnode_t *)idxnodebuf)->offset == 0x03fffc)
		{
			for(j=0;j<((Pnode_t *)idxnodebuf)->plen;j++)
			{
				printf("0x%02x ",(uint8_t *)buf[j]);
				if(j%8 == 0)
				{
					printf("\n");
				}
			}
			printf("\n");
		}
		if(((Pnode_t *)idxnodebuf)->offset == 0x008efee0)
		{
			for(j=0;j<((Pnode_t *)idxnodebuf)->plen;j++)
			{
				printf("0x%02x ",(uint8_t *)buf[j]);
				if(j%8 == 0)
				{
					printf("\n");
				}
			}
			printf("\n");
		}
		if(((Pnode_t *)idxnodebuf)->offset == 0x040014)
		{
			for(j=0;j<((Pnode_t *)idxnodebuf)->plen;j++)
			{
				printf("0x%02x ",(uint8_t *)buf[j]);
				if(j%8 == 0)
				{
					printf("\n");
				}			
			}
			printf("\n");
		}
		if(rsize != ((Pnode_t *)idxnodebuf)->plen)
		{
			printf("read %s file data package error, \npackage len : %d, offset : 0x%04x\n",datafilename,((Pnode_t *)idxnodebuf)->plen,((Pnode_t *)idxnodebuf)->offset);
		}	
         fflush(fdmerge);		
		fwrite(buf,1,((Pnode_t *)idxnodebuf)->plen,fdmerge);
		
		idxnodebuf += sizeof(Pnode_t);
		free(buf);
		fclose(fd);			
	}
	
}

#define MAX_FILENAME_LEN  13
int Search_Same_File(List *list,char *str)
{
	//va_list ap;
    //va_start(ap, str); //初始化变元指针
	char *fn;
	int count = 0;
	int i;
	void *w1,*w2;
	char *ret;
	char tem[MAX_FILENAME_LEN];
	char c = '*';
	
	Node *tnode = list->head;
	
	if(list == NULL)
	{
		printf("list is NULL\n");
		return -1;
	}
	if(str == NULL)
	{
		return list->count;
	}
	
    ret = strchr(str,c);
	
	if(ret != NULL)
	{
	   strncpy(tem,str,ret-str);
	   tem[ret-str] = '\0';
	   str = ret + 1;
	}
		
	for(i = 0;i<list->count;i++)
	{
		fn = tnode->data;
		w1 = strstr(fn,str);
		if(ret != NULL)
		{
		    w2 = strstr(fn,tem);
			if((w1 != NULL) && (w2 != NULL))
			{
				count ++;
			}
		}else{
			if(w1 != NULL)
			{
				count ++;
			}
		}
		tnode = tnode->next;
	}	
    return count;	
}













