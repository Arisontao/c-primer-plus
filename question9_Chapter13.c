#include <stdio.h>
#include <stdlib.h>
#define MAX 47
int main(void)
{
	FILE *fp;
	char words[MAX];
	int wordct = 0;
	if ((fp = fopen("wordy.txt", "a+")) == NULL)
	{
		fprintf(stderr,"Can't open \"words\" file.\n");
		exit(EXIT_FAILURE);
	}
	// determine current number of lines
	rewind(fp);
	while (fgets(words, MAX, fp) != NULL)//How does this line's code to konw that it reads a line break?
		wordct++; //I suggest that the fgets function ends with a line break,and includinig the line break,so it can be used to count the number of words
	rewind(fp);

	puts("Enter words to add to the file; press the #");
	puts("key at the beginning of a line to terminate.");
	while ((fscanf(stdin,"%40s", words) == 1) && (words[0] != '#'))
		fprintf(fp, "%3d: %s\n", ++wordct, words);
	puts("File contents:");
	rewind(fp); // go back to beginning of file
	while (fgets(words, MAX, fp) != NULL) // read line including number
		fputs(words, stdout);
	if (fclose(fp) != 0)
		fprintf(stderr,"Error closing file\n");
	puts("Done");
	
	return 0;
}