#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int ch1, ch2;
	FILE * f1;
	FILE * f2;
	if(argc != 3)
	{
		printf("Usage: %s file1 file2\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if ((f1 = fopen(argv[1], "r")) == NULL)
	{
		printf("Could not open file %s for input\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if((f2 = fopen(argv[2], "r")) == NULL)
	{
		printf("Could not open file %s for input\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	ch1 = getc(f1);
	ch2 = getc(f2);
	while(ch1 != EOF || ch2 != EOF)
	{
		while(ch1 != EOF && ch1 != '\n') /* skipped after EOF reached */
		{
			putchar(ch1);
			ch1 = getc(f1);
		}
		if(ch1 != EOF)
		{
			ch = getc(f1);
		}
		while(ch2 != EOF && ch2 != '\n') /* skipped after EOF reached */
		{
			putchar(ch2);
			ch2 = getc(f2);
		}
		if(ch2 != EOF)
		{
			putchar('\n');
			ch2 = getc(f2);
		}
	}
	if(fclose(f1) != 0)
		printf("Could not close file %s\n", argv[1]);
	if(fclose(f2) != 0)
		printf("Could not close file %s\n", argv[2]);

	return 0;
}