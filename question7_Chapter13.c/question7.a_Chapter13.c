#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE *fa,*fp;
	int ch;
	int cha;

	if((fa = fopen("b.txt","r")) == NULL)
	{
		fprintf(stderr,"Can't open b.txt\n");
		exit(EXIT_FAILURE);
	}
	if((fp = fopen("c.txt","r")) == NULL)
	{
		fprintf(stderr,"Can't open c.txt\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		ch = getc(fa);
		putc(ch,stdout);
		while(ch == '\n')
		{
			cha = getc(fp);
			if(feof(fp))
			{
				ch = getc(fa);
                putc(ch,stdout);
			}
			putc(cha,stdout);
			if(cha == '\n')
				break;
		}
		if(feof(fa))
        {
            while((cha = getc(fp)) != EOF);
				putc(cha,stdout);
        }
		if(feof(fa) && feof(fp))
			break;
	}
	if(fclose(fa) || fclose(fp))
	{
		fputs("Error in closing file.\n",stderr);
		exit(EXIT_FAILURE);
	}

	return 0;
}
