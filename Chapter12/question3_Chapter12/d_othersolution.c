#define METRIC 0
#define US 1
#define USE_RECENT 2
void check_mode(int * pm);
void get_info(int mode, double * pd, double * pf);
void show_info(int mode, double distance, double fuel);

// pe12-3b.c

#include <stdio.h>
#include "pe12-3a.h"
int main(void)
{
	int mode;
	int prev_mode = METRIC;
	double distance, fuel;

	printf("Enter 0 for metric mode, 1 for US mode: ");
	scanf("%d", &mode);
	while (mode >= 0)
	{
		check_mode(&mode);
		if (mode == USE_RECENT)
			mode = prev_mode;
		prev_mode = mode;
		get_info(mode, &distance, &fuel);
		show_info(mode, distance, fuel);
		printf("Enter 0 for metric mode, 1 for US mode");
		printf(" (-1 to quit): ");
		scanf("%d", &mode);
	}
	printf("Done.\n");

	return 0;
}

// pe12-3a.c

#include <stdio.h>
#include "pe12-3a.h"
void check_mode(int * pm)
{
	if (*pm != METRIC && *pm != US)
	{
		printf("Invalid mode specified. Mode %d\n", *pm);
		printf("Previous mode will be used.\n");
		*pm = USE_RECENT;
	}
}

void get_info(int mode, double * pd, double * pf)
{
	if (mode == METRIC)
		printf("Enter distance traveled in kilometers: ");
	else
		printf("Enter distance traveled in miles: ");
	scanf("%lf",pd);
	if (mode == METRIC)
		printf("Enter fuel consumed in liters: ");
	else
		printf("Enter fuel consumed in gallons: ");
	scanf("%lf", pf);
}

void show_info(int mode, double distance, double fuel)
{
	printf("Fuel consumption is ");
	if (mode == METRIC)
		printf("%.2f liters per 100 km.\n", 100 * fuel / distance);
	else
		printf("%.1f miles per gallon.\n", distance / fuel);
}

