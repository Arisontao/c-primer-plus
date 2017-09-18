#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40

//This program has a small problem,and you don't know why you can't use s_gets function to record the name of the array
//Mark here wait to be finished next time

int main(void)
{
	char name[MAX];
	FILE *fp;
	int ch; //You'd better use type "int" here
	
	printf("Enter name of the file you want to open:");
	s_gets(name,MAX);
	if((fp = fopen(name,"r")) == NULL)
	{
		fprintf(stderr,"Can't open %s\n",name);
		exit(EXIT_FAILURE);
	}
	if(setvbuf(fp,NULL,_IOFBF,BUFSIZE) != 0)
	{
		fputs("Can't create output buffer\n",stderr);
		exit(EXIT_FAILURE);
	}
	while((ch = getc(fp)) != EOF)
		putc(ch,stdout);
	if(fclose != 0)
	{
		fputs("Error in closing file!\n",stderr);
	}
	
	return 0;
}
