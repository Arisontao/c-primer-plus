#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char *argv[])
{
	FILE *fp;
	int i;
	int j = 0;
	int ch;

	if(argc <= 2)
	{
		fprintf(stderr,"Usage: %s filename\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if(argc > 2)
	{
		for(i = 2;i < argc;i++)
		{
			if((fp = fopen(argv[i],"r")) == NULL)
			{
				fprintf(stderr,"Can't open %s\n",argv[i]);
				exit(EXIT_FAILURE);
			}
			while((ch = getc(fp)) != EOF)
				if(ch == *(argv[1]))
					j++;
			printf("The character has appeared %d times in %s\n",j,argv[i]);
			j = 0; //Remember to set j to 0 after a loop
		}
		if(fclose(fp))
		{
			fprintf(stderr,"Error in closing %s\n",argv[i]);
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
