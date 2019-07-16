#include <stdio.h>
#include <malloc.h>

int main()
{
	FILE *fin, *fout,*fpara;
	unsigned int v, b0, b1, b2, b3;
	int a, b, c, d, n;
	int i;
	char iline[132];

    fpara = fopen ("ParaTable.map", "r");

	
	fin = fopen ("simple.i2c.ccs", "r");

	fout = fopen ("i2crom.ccs", "w");


	/* Read the CCS data file header, change the ddr start address and length*/
	fgets (iline, 132, fin);
	sscanf (iline, "%x %x %x %x %x", &a, &b, &c, &d, &n);
	c = 0x80000000;
	n = n + 256;
	fprintf (fout, "%x %x %x %x %x\n", a, b, c, d, n);

	
	/*Write the parameter table*/
	for (i = 0; i < 256; i++)  
	{
		fgets (iline, 132, fpara);
		fputs (iline, fout);
	}
	
	/*Write the data*/
	fprintf(fout,"\n");
	for (i = 0; i < n-256; i++)  
	{
		fgets (iline, 132, fin);
		fputs (iline, fout);
	}

	fclose (fout);
	fclose (fin);
	fclose(fpara);

	return (0);

}

