#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	int num[1000];
	int arr[10];
	int i;
	int k,m;
	int key;
	int j = 0;
	int n;
	int a = 10;
	int q;

	srand((unsigned int) time(0));
	for(i = 0;i < 1000;i++)
	{
		num[i] = rand() % 10 + 1;
	}
	for(k = 1;k < 1000;k++)
	{
		key = num[k];
		for(m = k - 1;m >= 0 && num[m] > key;m--)
		{
			num[m + 1] = num[m];
		}
		num[m + 1] = key;
	}
	for(n = 0;n < 1000;n++)
	{
		if(num[n] != num[n + 1])
		{
			arr[j] = n + 1; //这里出了问题，记得修改
			j++;
		}
	}
	for(j = 0;j < 10;j++)
		printf("%d ",arr[j]);
	for(j = 9;j > 0;j--)	
		arr[j] = arr[j] - arr[j - 1];
	for(q = 0;q < 10;q++)
	{
		printf("%d出现了%d次\n",a,arr[q]);
		a--;
	}

	return 0;
}
