 #include <stdint.h>
 
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
