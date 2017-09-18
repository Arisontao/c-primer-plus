#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 40

int main(void)
{
	FILE *in,*out;
	int ch;
	char name[LEN];
	char file[LEN];
	int count = 0;

	printf("Enter the file you want to copy:\n");
	fscanf(stdin,"%40s",file);
	if((in = fopen(file,"r")) == NULL)
	{
		fprintf(stderr,"Can't open %s\n",file);
		exit(EXIT_FAILURE);
	}
	strncpy(name,file,LEN - 5);
	name[LEN - 5] = '\0';
	strcat(name,".red");
	if((out = fopen(name,"w")) == NULL)
	{
		fprintf(stderr,"Can't open %s\n",file);
		exit(EXIT_FAILURE);
	}
	while((ch = getc(in)) != EOF)
	{
		if(count++ % 3 == 0)
			putc(ch,out);
	}
	if(fclose(in) || fclose(out))
		fprintf(stderr,"Error in closing files\n");

	return 0;
}
