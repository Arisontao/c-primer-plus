#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int i;
	FILE *fp;
	int ch;

	if(argc < 1)
	{
		fprintf(stderr,"Usage: %s filename\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	for(i = 1;i < argc;i++)
	{
		if((fp = fopen(argv[i],"r")) == NULL)
		{
			fprintf(stderr,"Can't open %s\n",argv[i]);
			exit(EXIT_FAILURE);
		}
		while((ch = getc(fp)) != EOF)
			putc(ch,stdout);
		if(ferror(fp))
			fprintf(stderr,"Error in reading file %s\n",argv[i]);
		if(fclose(fp))
		{
			fprintf(stderr,"Error in closing %s\n",argv[i]);
			exit(EXIT_FAILURE);
		}
		putchar('\n');
	}
	printf("Done displaying.\n");

	return 0;
}
