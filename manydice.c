#include <stdio.h>
#include "diceroll.h"

int main(void)
{
	int dices;
	int sides;
	int status;
	char ch;
	int roll;

	printf("Enter the number of sides per dice(0 to stop): ");
	while(scanf("%d",&sides) == 1 && sides > 0)
	{
		printf("How many dices do you want?");
		while((status = scanf("%d",&dices)) != 1)
		{
			if(status == EOF)
				break;
			else
			{
				while((ch = getchar()) != '\n')
					putchar(ch);
				puts(" is not an integer,please Enter again.");
				puts("Please enter 0 to stop.");
				if(dices == 0)
					goto a;
			}
		}
		roll = roll_n_dice(sides,dices); //这里改变了roll的值，以前是随机值，这里通过roll_n_dice把它变成了总和
		printf("You have rolled a %d using %d %d-sided dice.\n",roll,dices,sides);
		printf("How many sdies? Enter 0 to stop.\n");
	}
	printf("The rollem() function was called %d times.\n",roll_count);
	puts("GOOD FORTUNE TO YOU!\n");
	a: printf("You don't have enter a number for dice,exit function failure!\n");

	return 0;
}
