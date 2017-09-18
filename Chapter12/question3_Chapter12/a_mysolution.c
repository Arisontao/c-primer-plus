#include <stdio.h>
#include "pe12-2a.h"
#define USE_RECENT 2

int main(void)
{
	int mode;
	int prev_mode;
	int distance,fuel_consume;
	
	printf("Enter 0 for metric mode, 1 for US mode: ");
	scanf("%d",&mode);
	while(mode >= 0)
	{
		set_mode(&mode);
		if(mode == USE_RECENT)
			mode = prev_mode; //Using the previous mode
		prev_mode = mode; //TO record the previous mode
		get_info(mode,&distance,&fuel_consume); //Pass in the address of auto variables distance and fuel_consume,then read the numbers for the next function 
		show_info(mode,distance,fuel_consume);
		printf("Enter 0 for metric mode, 1 for US mode: ");
		printf("(-1 to quit): ");
		scanf("%d",&mode);
	}

	return 0;
}

