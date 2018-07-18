
#include <stdint.h>
#include <stdio.h>
#include "list.h"
//���ݰ������Žṹ��
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

//�����ṹ��
typedef struct pnode_s
{
	uint16_t plen;		//�ڵ����ݳ���
	uint16_t fnum;		//���ݴ�ŵ��ļ���ţ���ǰ����ƣ���һ�δ洢�������ļ�����2Gʱ��������ݴ洢����һ���ļ��������ָ�����ļ����
	uint32_t offset;
	SN_t sn;
} Pnode_t;


typedef struct merge_node_t{
	uint8_t frbn;
	uint8_t pkcount;
}merge_node;

typedef struct file_info_t{
	char name[260];
	uint32_t size;
}File_info;

int Data_File_Handle(uint8_t *idxnodebuf, int idxnodenum, uint8_t rfbn,FILE *fdmerge,char *path);
int Merge_File_Handle(FILE *fd,List *list,char *path);
int mergedata(merge_node *mergenode,List *list,FILE * fdidx,char *path);
int Search_Same_File(List *list,char *str);
int close_idx_file(FILE *rfbn_fd_p[]);
int get_file_size(FILE *fd);

#define  MAX_PATH_LEN    260

#define  MAX_MERGE_FILENAME_LEN   13   //merge_xxx.idx

#define  MAX_OPEN_FILE_NAME_LEN    MAX_PATH_LEN + MAX_MERGE_FILENAME_LEN

#define  MERGE_DATA_FILE_NAME_LEN  13

#define  ARRAY_SIZE( ARRAY ) (sizeof (ARRAY) / sizeof (ARRAY[0]))