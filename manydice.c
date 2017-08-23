#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diceroll.h"

int main(void)
{
	int dices; //骰子数
	int sides; //面数
	int status;
	char ch; //错误输入的输出
	int sets; //摇色子的次数
	int roll; //摇出的数字总和
	int i; //打印数字

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
		for(i = 0;i < sets;i++) //为什么这里打印的时候会出现这样的错误呢？我是真的不知道啊
		{
			roll = roll_n_dice(sides,dices);
			printf("%d ",roll);// 这里改变了roll的值，以前是随机值，这里通过roll_n_dice把它变成了总和
			if(i % 14 == 0 && i != 0)
				putchar('\n');
		}
		printf("\nHow many sets? Enter q to stop: ");
			continue;
	}
	printf("The rollem() function was called %d times.\n",roll_count);
	puts("GOOD FORTUNE TO YOU!\n");

	return 0;
}
