#include <unistd.h>

int main(int argc, char *argv[])
{
	extern char *optarg;
	extern int optind, opterr, optopt;
	int ch;  //getopt()返回值为int型
	while((ch == getopt(argc,argv,"a:b:c::d:ef:g::")) != -1)
	{
		switch(ch){
			case 'a':printf("a argument is %s\n",optarg);break;
			case 'b':printf("b argument is %s\n",optarg);break;
			case 'c':printf("c argument is %s\n",optarg);break;
			case 'd':printf("d argument is %s\n",optarg);break;
			case 'e':printf("e argument is %s\n",optarg);break;
			case 'f':printf("f argument is %s\n",optarg);break;
			case 'g':printf("g argument is %s\n",optarg);break;
			case '?':printf("input opt:-%c no this opt \n",optopt);break;
			case ':':printf("%c missing argument\n",otopt);
			default:printf("ch is %c \n",ch);
		}
	}
}