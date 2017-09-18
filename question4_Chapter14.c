#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct {
	char lname[MAX];
	char midname[MAX];
	char fname[MAX];
}NAME;
typedef struct {
	int socnum;
	NAME people;
}SOCIAL;
char * s_gets(char * st,int n);
void show_struct(SOCIAL * ptr[],int n);

int main(void)
{
	int i;
	SOCIAL * pt[5];
	SOCIAL person[5] = {{1112,{"tao","","huang"}},{1113,{"tao","huang","Arison"}},
						{11144,{"Flossie","","Dribble"}},{555,{"Kate","Jason","Docate"}},{9996,{"July","Amand","Tom"}}
	};

	for(i = 0;i < 5;i++)
		pt[i] = &person[i];
	show_struct(pt,5);

	return 0;
}

void show_struct(SOCIAL * ptr[],int n)
{
	int i;

	for(i = 0;i < n;i++)
		if(ptr[i]->people.midname[0] != '\0')
			printf("%s, %s %c. -- %d\n",ptr[i]->people.fname,ptr[i]->people.lname,ptr[i]->people.midname[0],ptr[i]->socnum);
		else
			printf("%s, %s -- %d\n",ptr[i]->people.fname,ptr[i]->people.lname,ptr[i]->socnum);
}
