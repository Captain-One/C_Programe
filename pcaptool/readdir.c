#include <sys/types.h>  
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include "list.h"

#define  MAX_MERGE_FILENAME_LEN   13   //merge_xxx.idx

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
int mergedata(merge_node *mergenode,List *list,char *path);
int Search_Same_File(List *list,char *str,...);


int main(int argc, char *argv[])
{
	DIR *datadir;
	char * path = argv[1];
	struct dirent *filename;
	char *dfilename; 
    char merge[] = {"merge_"};
	int mergenumber;
	int filenum;
	int rv;
	int i;
	char *mergefilename;
	FILE *fd;
	List fnlist;
	
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
		closedir(datadir);
		return -1;
	}
	printf("find %d merge file\n",mergenumber);
	
	mergefilename = malloc(MAX_MERGE_FILENAME_LEN);
	for(i=0;i<mergenumber;i++)
	{
		sprintf(mergefilename,"%s/merge_%d.idx",path,i);
		printf("%s \n",mergefilename);
		fd = fopen(mergefilename,"rb+");
		if(fd == NULL)
	    {
		    printf("merge_x.idx file open error!\n");
			closedir(datadir);
		    return -1;
	    }
		rv = Merge_File_Handle(fd,&fnlist,path);
		if(rv < 0)
		{
			printf("File Handle Error!!!\n");
			fclose(fd);
			closedir(datadir);
			return -1;
		}	
	}
	closedir(datadir);
}


int Merge_File_Handle(FILE *fd,List *list,char *path)
{
	int size,resize ;
	int i;
	merge_node mergenode;
	
	fseek(fd,0,SEEK_END);
	size = ftell(fd);
	fseek(fd,0,SEEK_SET);
	
	if(size < 0)
	{
		printf("get merge_xx file size error !\n");
		return -1;
	}
    
	for(i=0;i<size;i++)
	{
		resize = fread(&mergenode,1,sizeof(merge_node),fd);
		if(resize != sizeof(merge_node))
		{
			printf("read merge dat error !\n");
			//return -1;
		}
        mergedata(&mergenode,list,path);		
	}
}

#define MAX_IDX_FILENAME_LEN    10//xx_nnn.idx

int mergedata(merge_node *mergenode,List *list,char *path)
{
	FILE *fd,*fdmerge;
	char *idxfilename;
	int i,idxfilenum,readsize,rv,j;
	void *idxnodebuf;
	
	fdmerge = fopen("mergedata.dat","wb+");
	if(fdmerge == NULL)
	{
		printf("open merge data file error !\n");
		return -1;
	}
	idxfilename = malloc(MAX_IDX_FILENAME_LEN);
	if(idxfilename == NULL)
	{
		printf("malloc idx filenam space error !\n");
		fclose(fdmerge);
		return -1;
	}
	
	sprintf(idxfilename,"%d_x.idx",mergenode->frbn);
	//need 
	//idxfilenum = List_Match(list,idxfilename);
	if(idxfilenum < 0)
	{
		//error handle;
	}
	
	for(i = 0;i<idxfilenum;i++)
	{
		sprintf(idxfilename,"%s/%d_%d.idx",path,mergenode->frbn,i);
		fd = fopen(idxfilename,"rb+");
		if(fd == NULL)
		{
			printf("open %s file error \n",idxfilename);
			fclose(fdmerge);
			free(idxfilename);
			return -1;
		}		
		idxnodebuf = malloc(mergenode->pkcount*sizeof(Pnode_t));
		readsize = fread(idxnodebuf,1,mergenode->pkcount*sizeof(Pnode_t),fd);		
        for(j=0;j<readsize;j++)
		{
			rv = Data_File_Handle(idxnodebuf,readsize,mergenode->frbn,fdmerge,path);
			if(rv < 0)
				printf("Data File Handle Error !\n");
		}
        free(idxnodebuf);
        fclose(fd);		
	}
    fclose(fdmerge);
    free(idxfilename);	
}

#define MAX_DATA_FILENAME_LEN    10//xx_nnn.dat

int Data_File_Handle(void *idxnodebuf, int idxnodenum, uint8_t rfbn,FILE *fdmerge,char *path)
{
	Pnode_t *node = (Pnode_t *)idxnodebuf;
	FILE *fd;
	char *datafilename;
	int i,rsize,rv;
	uint8_t *buf;
	datafilename = malloc(MAX_DATA_FILENAME_LEN);
	if(datafilename == NULL)
	{
		printf("malloc data file name space error !\n");
		return -1;
	}
	sprintf(datafilename,"%s/%d_%d.dat",path,rfbn,node->fnum);
	fd = fopen(datafilename,"rb+");
	if(fd == NULL)
	{
		printf("open %s file error !!! \n",datafilename);
		free(datafilename);
		return -1;		
	}
	for(i=0;i<idxnodenum;i++)
	{
		buf = malloc(node->plen);
		if(buf == NULL)
		{
			printf("malloc data buf error !\n");
			fclose(fd);
			free(datafilename);
			return -1;			
		}
		fseek(fd,node->offset,SEEK_SET);
		rsize = fread(buf,1,node->plen,fd);
		if(rsize != node->plen)
		{
			printf("read %s file data package error, \npackage len : %d, offset : 0x%04x\n",datafilename,node->plen,node->offset);
		}
		node += node->plen;
		rv = fwrite(buf,1,node->plen,fdmerge);
		free(buf);
	}
    fclose(fd);	
	free(datafilename);
}

int Search_Same_File(List *list,char *str,...)
{
	va_list ap;
    va_start(ap, str); //初始化变元指针
	
	char *fn;
	int count = 0;
	int i;
	void *w;
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
	for(i = 0;i<list->count;i++)
	{
		fn = tnode->data;
		w = strstr(fn,str);
		if(w != NULL)
		{
			count ++;
		}
		tnode = tnode->next;
	}	
    return count;	
}













