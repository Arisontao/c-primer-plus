#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40
int stoit(char * st);
char * s_gets(int n,char * st);
int main(void)
{
	char name[MAX];
	puts("Please enter the string:");
	s_gets(MAX,name);
	printf("The result is %d.\n",stoit(name));

	return 0;
}
int stoit(char * st)
{
	int i;
	int num = 0;
	for(i = 0;i < MAX;i++,num <<= 1)
	{
		if(st[i])
			num |= (int) st[i] - 48;
		if(st[i + 1] == '\0')
			break;
	}
	return num;
}
char * s_gets(int n,char * st)
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
