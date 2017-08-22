#include <stdio.h>
#include <stdlib.h>
#include "diceroll.h"

int roll_count = 0;

static int rollem(int sides) //可以不用写函数原型，因为这个函数只属于这个文件，并且这里没有main()函数
{
	int roll;
	
	roll = rand() % sides + 1;
	++roll_count;
	
	return roll;
}

int roll_n_dice(int sides,int dices)
{
	int total = 0;
	int d;
	
	if(sides < 2)
	{
		printf("Need at least 2 sides.\n");
		return -2;
	}	
	if(dices < 1)
	{
		printf("Need at least 1 dice.\n");
		return -1;
	}
	for(d = 0;d < dices;d++)
		total += rollem(sides);
	
	return total;
}
