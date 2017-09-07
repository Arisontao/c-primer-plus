#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE *fa,*fp;
	int ch;
	int cha;
	//In this program,we need to note the newline character in the end of the file,which affects the output of the program
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
		if(feof(fa))
        {
            cha = getc(fp);
			putc(cha,stdout);
			goto a; //Here I use goto statement to skip the case when fa equals EOF
        }
		putc(ch,stdout);
		a: while(ch == '\n')
		{
			cha = getc(fp);
			if(feof(fp))
			{
				ch = getc(fa);
                putc(ch,stdout);
                continue;
			}
			putc(cha,stdout);
			if(cha == '\n')
				break;
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
