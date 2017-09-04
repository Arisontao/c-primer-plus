#include <stdio.h>
#include <stdlib.h>

//Note that when you open a file,you need to use the absolute path of the file.
int main(int argc,char *argv[])
{
	FILE *fa;
	FILE *fs;
	int ch;
	
	if(argc < 3)
	{
		fprintf(stderr,"Usage: %s filename\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if((fa = fopen(argv[1],"r")) == NULL)
	{
		fprintf(stderr,"Can't open %s.\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	if((fs = fopen(argv[2],"w")) == NULL)
	{
		fprintf(stderr,"Can't open %s.\n",argv[2]);
		exit(EXIT_FAILURE);
	}
	while((ch = getc(fa)) != EOF)
		putc(ch,fs);
	if(fclose(fa) != 0 || fclose(fs) != 0)
		fprintf(stderr,"Error in closing files.\n");

	return 0;
}