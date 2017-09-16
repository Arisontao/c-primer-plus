#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31
typedef struct{
	char monname[MAX];
	char monabb[MAX];
	int mondays;
	int monnum; //Note that you cannot initialize the structure when you define it because there is no memory allocated yet
}Month;
int add_mondays(Month ptr[],char * st,int n,int m);
char * s_gets(char * st,int n);

int main(void)
{
	char name[MAX];
	int year;
	int days;
	Month num[12] = {{"January","Jan",31,1},{"Feburary","Feb",28,2},{"March","Mar",31,3},{"April","Apr",30,4},{"May","May",31,5},{"June","Jun",30,6},
					 {"July","Jul",31,7},{"August","Aug",31,8},{"September","Sep",30,9},{"October","Oct",31,10},{"November","Nov",30,11},{"December","Dec",31,12}
	};

	puts("Enter the year:");
	scanf("%d",&year);
	getchar(); //There is a line break here,so we should clean it away.
	printf("Enter the abbreviation of month name or the month name or the number of month:\n");
	s_gets(name,MAX);
	puts("Enter the days:");
	scanf("%d",&days);
	printf("The sum of days is %d\n",add_mondays(num,name,days,year));

	return 0;
}

int add_mondays(Month ptr[],char * st,int n,int m)
{
	char monnumber[2];
	int i,j;
	int flag = -1; //To mark the month name which is been found
	int sum = 0;

	if(m % 4 == 0 || m % 400 == 0)
		ptr[1].mondays += 1; //If it is a leap year,add one day in Feburary
	for(i = 0;i < 12;i++)
	{
		sprintf(monnumber,"%d",ptr[i].monnum); //Converts the number to a string using the sprintf function, converting the string into a number using the strtol function
		if(strcmp(ptr[i].monabb,st) == 0 || strcmp(ptr[i].monname,st) == 0 || strcmp(monnumber,st) == 0)
        {
            flag = i;
            break;
        }

	}
	if(flag == -1)
	{
		printf("Sorry,I can't find it.\n");
		exit(1);
	}
	for(j = 0;j <= flag;j++)
		sum += ptr[j].mondays;
	if((ptr[flag].mondays - n) >= 0)
		sum = sum - (ptr[flag].mondays - n);

	return sum;
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

