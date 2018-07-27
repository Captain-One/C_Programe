#include <stdio.h>
#include <stdlib.h>

#include "rfcn-fr.h"

int main()
{
	FILE *fd;
	char buf[200];
	char r;
	float ca_freq;
	int i;
	int band = 0;
	float rfcn = -1;
	int mode = 0;
	float Band_Ca_Freq_Max;
	float Band_Ca_Freq_Min;
	float in_rfcn;
	float out_ca_fr;
	char cc;

	do
	{
		printf("1:  RFCN--->Carrier Frequency\n2:  Carrier Frequency--->RFCN\n");
		scanf("%d",&mode);
		if(mode == 1)
		{
			printf("Input RFCN:");
			scanf("%f",&in_rfcn);
			for(i = 0;i<44;i++)
			{
				if((in_rfcn >= BAND(i).Range_Min) && (in_rfcn <= BAND(i).Range_Max))
				{
					out_ca_fr = BAND(i).F_low + (in_rfcn - BAND(i).N_offs)/10;
					printf("Carrier Frequency:	%.3f\nBand			%d\n",out_ca_fr,i+1);
					break;
				}
			}	
		}
		if(mode == 2)
		{
			printf("Input Carrier Frequency:");
			scanf("%f",&ca_freq);
			for(i = 0;i<44;i++)
			{
				Band_Ca_Freq_Max = BAND(i).F_low + 0.1*(BAND(i).Range_Max - BAND(i).N_offs);
				Band_Ca_Freq_Min = BAND(i).F_low + 0.1*(BAND(i).Range_Min - BAND(i).N_offs);
				if((ca_freq >= Band_Ca_Freq_Min) && (ca_freq <= Band_Ca_Freq_Max))
				{
					rfcn = (ca_freq - BAND(i).F_low)*10 + BAND(i).N_offs;			
					if((rfcn >= BAND(i).Range_Min) && (rfcn <= BAND(i).Range_Max))
					{
						printf("RFCN:	%.3f\nBand	%d\n",rfcn,i+1);
						break;
					}else{
						printf("Error\n");
					}		
				}
			}
			if(rfcn == -1)
				printf("Input Frequency Error\n");
		}
        printf("Input 'q' Quit,Other Continue:");
		cc = getchar();
	    cc = getchar();
	}while(cc != 'q');
}