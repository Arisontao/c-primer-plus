#include <stdio.h>
#include "pe12-2a.h"

static int flag; //标记上一次的模式
static double distance;
static double fuel_consume;
static int mode;

void set_mode(int n)
{
	mode = n;
	if(n != 0 && n != 1 && flag == 0)
	{	
		printf("Invalid mode specified. Mode 0(metric) used.\n");
		mode = 0;
	}
	if(flag == 1 && n != 0 && n != 1)	
	{
		printf("Invalid mode specified. Mode 1(US) used.\n");
		mode = 1;
	}
}

void get_info(void)
{
	if(mode == 0)
	{
		flag = 0;
		printf("Enter distance traveled in kilometers: ");
		scanf("%lf",&distance);
		while(distance == 0)
        {
            printf("distance can't not be 0,please enter again: ");
            scanf("%lf",&distance);
        }
		printf("Enter fuel consumed in liters: ");
		scanf("%lf",&fuel_consume);
	}
	if(mode == 1)
	{
		flag = 1;
		printf("Enter distance traveled in miles: ");
		scanf("%lf",&distance);
		printf("Enter fuel consumed in gallons: ");
		if(scanf("%lf",&fuel_consume))
        while(fuel_consume == 0)
        {
            printf("fuel_consume can't not be 0,please enter again: ");
            scanf("%lf",&fuel_consume);
        }
	}
}

void show_info(void)
{
	if(mode == 0)
		printf("Fuel consumption is %.2lf litters per 100 km.\n",fuel_consume / (distance / 100));
	if(mode == 1)
		printf("Fuel consumption is %.1lf miles per gallon.\n",distance / fuel_consume);
}

