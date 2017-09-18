#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ** mal_arr(int num);

int main(void)
{
	int words;
	char ** st;
	int i;

	printf("How many words do you wish to enter? ");
	while(scanf("%d",&words) == 1 && words > 0)
	{
		printf("Enter %d words now:\n",words);
		st = mal_arr(words);
		printf("Here are your words:\n");
		for(i = 0;i < words;i++)
			puts(st[i]);
		free(st);
		printf("How many words do you wish to enter(enter q to quit)? ");
	}
	printf("Bye!\n");

	return 0;
}

char ** mal_arr(int num)
{
	char ** ptr;
	char * temp;
	int i,len;

	ptr = (char **) malloc(num * sizeof(char *)); //The address has been assigned and is fixed
	if(ptr == NULL) //Especially careful here is the difference between ptr and "ptr == NULL"
		exit(EXIT_FAILURE);
	temp = (char *) malloc(num * sizeof(char)); //This is the allocation of memory space for the temporary array
	for(i = 0; i < num; i++)
    {
        scanf("%s", temp); //Note that this is temp[i] not temp[i]
		len = strlen(temp);
		ptr[i] = (char *) malloc((len + 1) * sizeof(char)); //Assign memory space for every ptr[i],and add the space of '\0'
		strcpy(ptr[i],temp);
		//ptr[i] = &temp[i],this is wrong because the address of ptr[i] is fixed,we need to set the sensing of ptr[i]
    }
	free(temp); //Note that the memory space of temporary array is to be release here

	return ptr;
}

