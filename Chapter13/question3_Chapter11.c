#include <stdio.h>
#include <ctype.h>
#define LEN 80
char * getword(char * str);

int main(void)
{
	char input[LEN];

	while (getword(input) != NULL)
		puts(input);
	puts("Done.\n");

	return 0;
}

char * getword(char * str)
{
	int ch;
	char * orig = str;

	// skip over initial whitespace
	while ((ch = getchar()) != EOF && isspace(ch))
		continue;
	if (ch == EOF)
		return NULL;
	else
		*str++ = ch; // first character in word
	// get rest of word
	while ((ch = getchar()) != EOF && !isspace(ch))
		*str++ = ch;
	*str = '\0';
	if (ch == EOF)
		return NULL;
	else
	{
		while((ch = getchar()) != '\n')
            continue;
        return orig;
	}
}
