#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 81
#define BUFSIZE 4096

int main(void)
{
	FILE *fp;
	FILE *fa;
	char name[MAX];
	int ch;

	//这里我打开了两个关联name文件的文件流，说明了只能一个流用来打开，一个流用来写入函数,现在要解决的问题就是怎么清空以前的文字
	printf("Enter the name of the file you want to open:\n");
	scanf("%80s",name);
	if((fp = fopen(name,"r+")) == NULL)
	{
		fprintf(stderr,"Can't open %s.\n",name);
		exit(EXIT_FAILURE);
	}
	if((fa = fopen(name,"w+")) == NULL)
	{
		fprintf(stderr,"Can't open %s.\n",name);
		exit(EXIT_FAILURE);
	}
	while((ch = getc(fp)) != EOF)
		putc(toupper(ch),fa);
    if(fclose(fp) != 0 || fclose(fa) != 0)
	{
		fputs("Error in closing file.\n",stderr);
		exit(EXIT_FAILURE);
	}

	return 0;
}
