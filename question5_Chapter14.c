#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40
typedef struct{
	char fname[MAX];
	char lname[MAX];
}NAME;

typedef struct{
	NAME fellow;
	double grade[3];
	double a;
}STUDENT; //The pointer to the structure array is the pointer to the structure
char * s_gets(char * st,int n);
void ave_sum(STUDENT * ptr);
//void show_struct(STUDENT * ptr);
//void show_avegrade(STUDENT * ptr);

int main(void)
{
	STUDENT num[4];
	int i,j;

	for(i = 0;i < 4;i++)
	{
		printf("Enter the first name of student %d:\n",i + 1);
		s_gets(num[i].fellow.fname,MAX);
		printf("Enter the last name of students %d:\n",i + 1);
		s_gets(num[i].fellow.lname,MAX);
		printf("Enter three grades of students %d:\n",i + 1);
		for(j = 0;j < 3;j++)
			scanf("%lf",&num[i].grade[j]);
		getchar(); //To clear line break
	}
	ave_sum(&num);
	puts("The average scores of each students as follows:");
	show_avegrade(&num);
	puts("The detail of each struct as follows:");
	show_struct(&num);

	return 0;
}

void ave_sum(STUDENT * ptr)
{
	int i,j;
	double sum = 0;

	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 3;j++)
			sum += ptr->grade[j];
		ptr->a = sum / 3;
		ptr++;
		sum = 0;
	}
}

void show_struct(STUDENT * ptr)
{
	int i,j;

	for(i = 0;i < 4;i++)
	{
		printf("%s\n",ptr->fellow.fname);
		printf("%s\n",ptr->fellow.lname);
		for(j = 0;j < 3;j++)
			printf("%.2lf ",ptr->grade[j]);
		putchar('\n');
		printf("%.2lf \n",ptr->a);
		ptr++;
		putchar('\n');
	}
}

void show_avegrade(STUDENT * ptr)
{
	int i;

	for(i = 0;i < 4;i++)
	{
		printf("%.2lf ",ptr->a);
		ptr++;
	}
	putchar('\n');
}

char * s_gets(char * st,int n)
{
	char * ret_val;
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
