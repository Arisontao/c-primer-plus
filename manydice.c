#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diceroll.h"

int main(void)
{
	int dices; //number of dice
	int sides; //number of dice's sides
	int status;
	char ch;
	int sets; //number of set rolls
	int roll; //sum of all random numbers
	int i;

	srand((unsigned int) time(0));
	printf("Enter the number of sets(enter 0 to stop): ");
	while(scanf("%d",&sets) == 1 && sets > 0)
	{
		printf("How many dices and how many sides(enter 0 for both dices and sides to stop): ");
		while((status = scanf("%d%d",&sides,&dices)) != 2 || sides <= 0 || dices <= 0)
		{
			if(sides == 0 || dices == 0)
			{
				puts("BYE!");
				exit(EXIT_SUCCESS);
			}
			if(status == EOF)
				break;
			else
			{
				while((ch = getchar()) != '\n')
					putchar(ch);
				puts(" is not an integer,please Enter again.");
				puts("Enter 0 for both sides and dices to stop.");
				if(dices == 0 || sides == 0)
				{
					printf("You don't have enter numbers correctly,exit function failure!\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		printf("Here are %d sets of %d %d-sided throws.\n",sets,dices,sides);
		for(i = 0;i < sets;i++)
		{
			roll = roll_n_dice(sides,dices);
			printf("%d ",roll); //Changing the value of roll from random numbers to the sum of random numbers
			if(i % 14 == 0 && i != 0) //Warning here,you should care about the case i isn't equal to 0,it will print a line break.
				putchar('\n');
		}
		printf("\nHow many sets? Enter q to stop: ");
			continue;
	}
	printf("The rollem() function was called %d times.\n",roll_count);
	puts("GOOD FORTUNE TO YOU!\n");

	return 0;
}
