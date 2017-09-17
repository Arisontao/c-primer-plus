#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * s_gets(char *st,int n);
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100

struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};
char * s_gets(char *st,int n);
void alpha_sort(struct book * ptr[],int n);
void show_struct(struct book * ptr[],int n);
void price_sort(struct book *ptr[],int n);

int main(void)
{
	struct book library[MAXBKS];
	struct book *pt[MAXBKS]; //An array which includes poninters to structure 
	int count = 0;
	int index;

	printf("Please enter the book title.\n");
	printf("Press [enter] at the start of a line to stop.\n");
	while(count < MAXBKS && s_gets(library[count].title,MAXTITL) != NULL && library[count].title[0] != '\0')
	{
		printf("Now enter the author.\n");
		s_gets(library[count].author,MAXAUTL);
		printf("Now enter the value.\n");
		scanf("%f",&library[count++].value);
		while(getchar() != '\n')
			continue;
		if(count < MAXBKS)
			printf("Enter the next title.\n");
	}
	if(count > 0)
	{
		printf("Here is the list of your books:\n");
		for(index = 0;index < count;index++)
		{
			printf("%s by %s: $%.2f\n",library[index].title,library[index].author,library[index].value);
			pt[index] = &library[index];
		}
		putchar('\n');
		alpha_sort(pt,count);
		show_struct(pt,count);
		putchar('\n');
		price_sort(pt,count);
		show_struct(pt,count);
	}
	else
		printf("No books? Too bad.\n");

	return 0;
}

void alpha_sort(struct book * ptr[],int n)
{
	int i,j;
	struct book *temp; //A temporary structure pointer

	for(i = 0;i < n - 1;i++)
		for(j = i + 1;j < n;j++)
		{
			if(strcmp(ptr[i]->title,ptr[j]->title) > 0) //It lacks one important step here is to set the pointer point to the structure  
			{
				temp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = temp;
			}
		}

}

void price_sort(struct book * ptr[],int n)
{
	int i,j;
	struct book *temp;
	
	for(i = 0;i < n - 1;i++)
		for(j = i + 1;j < n;j++)
		{
			if(ptr[i]->value > ptr[j]->value)
			{
				temp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = temp;
			}
		}
}

void show_struct(struct book *ptr[],int n)
{
	int i;

	for(i = 0;i < n;i++)
		printf("%s by %s: $%.2f\n",ptr[i]->title,ptr[i]->author,ptr[i]->value);
}

char * s_gets(char *st,int n)
{
	char *ret_val;
	char * find;

	ret_val = fgets(st,n,stdin);
	if(ret_val)
	{
		find = strchr(st,'\n');
		if(find)
			*find = '\0';
		else
			while(getchar() != '\n')
				continue;
	}
	return ret_val;
}
