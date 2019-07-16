#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define maxSize  1024*1024*30
#define MAX_INPUT_FILE		8
#define OUT_PUT_FILE		1

#define X32(x)                          (((x) & 0x000000FF) << 24) | (((x) & 0x0000FF00) << 8) |\
                                        (((x) & 0x00FF0000) >> 8) | (((x) & 0xFF000000) >> 24)

#define BOOT_TABLE_END		0x00000000

typedef struct core_info{
	uint32_t    file_size;
	uint32_t	entry_point;
}Core_info_s;

typedef struct my_boot_head{
	uint32_t   all_size;
	uint32_t    core_count;
	Core_info_s core_info[0];	
}My_Boot_Head_s;

My_Boot_Head_s  *boot_head;
uint32_t Boot_End = BOOT_TABLE_END;

int toNum (unsigned char c)
{
  if ((c >= '0') && (c <= '9'))
    return (c - '0');

  return (c - 'A' + 10);

}

int asciiByte (unsigned char c)
{
  if ((c >= '0') && (c <= '9'))
    return (1);

  if ((c >= 'A') && (c <= 'F'))
    return (1);

  return (0);
}

int read_data(FILE *f_in, uint8_t *data)
{
	unsigned char x, y;
    int byteCount = 0;
	
	while(1)
	{
		/* read the 1st ascii char */
		do  {
			x = fgetc (f_in);
			if (x == (unsigned char)EOF)
				return (byteCount);

		} while (!asciiByte(x));

		/* Read the next ascii char */
		y = fgetc (f_in);
		if (y == (unsigned char)EOF)
			return (byteCount);
		if (asciiByte(y))
			data[byteCount++] = (toNum(x) << 4) | toNum (y);

		if (byteCount >= maxSize)  {
			fprintf (stderr, "Max input array size exceeded\n");
			return (-1);
		}
	}
}

int data_parse(FILE *f_in, FILE *f_out, int i)
{	
	char line[132];
	int  read_byte_count;
	uint8_t *data;

	data = (uint8_t *)malloc(maxSize);
	if(data == NULL)
	{
		printf("malloc data buff error\n");
		return -1;
	}

	fgets(line, 132, f_in);
	fgets(line, 132, f_in);

	read_byte_count = read_data(f_in, data);
	if(read_byte_count < 0){
		printf("read_data error\n");
		free(data);
		return -1;
	}

	if(read_byte_count%4 != 0){
		printf("read_byte_count not 4 byte align\n");
		return -1;
	}

    if(To_little_32(data, read_byte_count) < 0)
	{
		printf("To_little_32 error \n");
	}

	boot_head->core_info[i].entry_point = (*(uint32_t *)data);

	if(fwrite(data + 4, 1, read_byte_count - 8, f_out) != (read_byte_count - 8))
	{
		printf("write data to file error\n");
		free(data);
		return -1;
	}
	boot_head->core_info[i].file_size = read_byte_count - 8;
	boot_head->all_size += boot_head->core_info[i].file_size;
	
	free(data);
	return 0;
}

int To_little_32(uint8_t *data, int size)
{
	uint8_t tmp;
	int i = 0;

	while(i != size)
	{
		tmp = data[i];
		data[i] = data[i + 3];
		data[i + 3] = tmp;
		tmp = data[i + 1];
		data[i + 1] = data[i + 2];
		data[i + 2] = tmp;
		i += 4;
	}
	return 0;
}
/*
int get_file_len(FILE *fp)
{
	int len;
	fseek(fp,0,SEEK_END);
    len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	return len;
}*/

int main(int argc, char *argv[])
{
	FILE *in_fp;
	FILE *out_fp;
	int status;
	int in_file_num;
	int i = 0;	
	int boot_head_size;

	if(argc < 3)
	{
		printf("input  parameter eeror\n");
		return 0;
	}
	if(argc > (MAX_INPUT_FILE + 2))
	{
		printf("input  parameter more\n");
		return 0;
	}

	in_file_num = argc - 2;

	boot_head_size = sizeof(My_Boot_Head_s) + in_file_num * sizeof(Core_info_s);

	boot_head = (My_Boot_Head_s *)malloc(boot_head_size);
	if(boot_head == NULL){
		printf("malloc boot_head error\n");
		return 0;
	}

	out_fp = fopen(argv[1 + in_file_num],"wb");
	if(out_fp == NULL){
		printf("open %s file error",argv[1 + in_file_num]);
		return 0;
	}

	boot_head->all_size = 0;
	boot_head->core_count = in_file_num;

	if(fwrite(boot_head, 1, boot_head_size, out_fp) != boot_head_size)
	{
		printf("write data to file error\n");
		free(boot_head);
		return 0;
	}

	while(i < in_file_num){
		in_fp = fopen(argv[1 + i],"r");
		if(in_fp == NULL){
			printf("open %s file error",argv[1 + i]);
			return 0;
		}

		status = data_parse(in_fp, out_fp, i);
		if(status < 0){
			printf("data_parse error: %d\n", status);
		}
		fclose(in_fp);
		i ++;
	}
	fwrite(&Boot_End, 1, 4, out_fp);
	fseek(out_fp,0,SEEK_SET);
	boot_head->all_size += boot_head_size + 4;
	//printf("boot_head->all_size: %u\n", boot_head->all_size);
	fwrite(boot_head, 1, boot_head_size, out_fp);
	fclose(out_fp);
	return 0;
}



