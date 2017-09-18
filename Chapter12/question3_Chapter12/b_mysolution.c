#include <stdio.h>
#include "pe12-2a.h"

void set_mode(int * num)
{
	if(*num != 0 && *num != 1)
	{	
		printf("Invalid mode specified. Mode %d\n", *num);
		printf("Previous mode will be used.\n");
		*num = USE_RECENT; //Change the value with the address so that it doesn't disappear automatically like an automatic variable
	}
}

void get_info(int mode,double *pt,double *ptr)
{
	if(mode == 0)
	{
		printf("Enter distance traveled in kilometers: ");
		scanf("%lf",pt);
		while(*pt == 0)
        {
            printf("distance can't not be 0,please enter again: ");
            scanf("%lf",pt);
        }
		printf("Enter fuel consumed in liters: ");
		scanf("%lf",ptr);
	}
	if(mode == 1)
	{
		printf("Enter distance traveled in miles: ");
		scanf("%lf",pt);
		printf("Enter fuel consumed in gallons: ");
		if(scanf("%lf",ptr))
        while(*ptr == 0)
        {
            printf("fuel_consume can't not be 0,please enter again: ");
            scanf("%lf",ptr);
        }
	}
}

void show_info(int mode,double distance,double fuel_consume)
{
	if(mode == 0)
		printf("Fuel consumption is %.2lf litters per 100 km.\n",fuel_consume / (distance / 100));
	if(mode == 1)
		printf("Fuel consumption is %.1lf miles per gallon.\n",distance / fuel_consume);
}

