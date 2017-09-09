#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 255
int main(int argc,char * argv[])
{
	FILE *fp;
	char words[MAX];

	if(argc < 3)
	{
		fprintf(stderr,"Usage: %s filname\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if((fp = fopen(argv[2],"r")) == NULL)
	{
		fprintf(stderr,"Can't open %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}
	while(fgets(words,MAX,fp) != NULL)
		if(strstr(words,argv[1]) != NULL)
			printf("%s",words);

	return 0;
}
