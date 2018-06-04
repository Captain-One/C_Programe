#include <sys/types.h>  
#include <dirent.h>
#include <stdio.h>

#include "list.h"


int main(int argc, char *argv[])
{
	DIR *datadir;
	char * path = argv[1];
	struct dirent *filename;
	List fnlsit;
	char *dfilename; 
	
	datadir = opendir(path);
	while(filename=readdir(datadir))
	{
	    lsit_insert_node(list,NULL,filename->d_name);
		printf("filename:%-10s\td_info:%ld\t d_reclen:%us\n",  
         filename->d_name,filename->d_ino,filename->d_reclen); 
	}
	filenum = lsit->count;
	
	closedir(datadir);
}