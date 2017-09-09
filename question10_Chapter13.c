#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 41

int main(void)
{
	FILE *fp;
	char name[MAX];
	int location;
	int ch;

	printf("Please enter the name of the file:\n");
	while(fscanf(stdin,"%40s",name) == 1)
	{
		if((fp = fopen(name,"r")) == NULL)
		{
			fprintf(stderr,"Can't open %s\n",name);
			exit(EXIT_FAILURE);
		}
		printf("Enter the location you want to show in the file:\n");
		while(scanf("%d",&location) == 1 && location >= 0)
		{
			fseek(fp,(double) location,SEEK_SET);
			while((ch = getc(fp)) != '\n')
				putc(ch,stdout);
            putchar('\n');
            printf("Enter again or q(< 0) to quit:\n");
		}
		if(fclose(fp))
		{
			fprintf(stderr,"Error in closing file\n");
			exit(EXIT_FAILURE);
		}
		printf("Please enter the name of the file again:\n");
	}
	printf("Bye!\n");

	return 0;
}

