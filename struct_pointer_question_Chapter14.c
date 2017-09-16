#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 31
typedef struct{
	char monname[MAX];
	char monabb[MAX];
	int mondays;
	int monnum[5];
}Month;
int add_mondays(const Month * ptr,int n);

int main(void)
{
	Month num = {
		"January",
		"Jan",
		3,
		{3,2,3,4,5}
	};
	int a;

	printf("Enter the month number:");
	scanf("%d",&a);
	printf("The sum of months days is %d\n",add_mondays(&num,a));

	return 0;
}

int add_mondays(const Month * ptr,int n)
{
	int i;
	int sum = 0;

	for(i = 0;i < n;i++)
		sum += ptr->monnum[i]; //Learn how to use sturct pointer in function

	return sum;
}
