#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	int num[20][30];
	const char trans[11]={' ','.','\'',':','~','*','=','&','%','#'};
	int i,j;
	int ch;

	if((fp = fopen("c.txt","r")) == NULL)
	{
		fprintf(stderr,"Can't open \"b.txt\"\n"); //有几个问题没有解决，一个是在最后打印一个空格，还有一个是老问题了，怎么清空以前的文字来继续打印
		exit(EXIT_FAILURE); 
	}
	for(i = 0;i < 20;i++)
		for(j = 0;j < 30;j++)
		{
			if((ch = getc(fp)) != EOF)
			{
				if(ch == ' ' || ch == '\n')
				{
					j = j - 1;
					continue;
				}
				else
					num[i][j] = ch;
			}
		}
	for(i = 0;i < 20;i++)
		for(j = 0;j < 30;j++)
		{
			if(j % 30 == 0)
				putchar('\n');
			printf("%c",trans[num[i][j] - 48]);
		}
	if(fclose(fp))
	{
		fprintf(stderr,"Error in closing \"b.txt\"\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
