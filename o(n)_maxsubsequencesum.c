#include <stdio.h>

int main(void)
{
	int num[8] = {6,3,-5,-12,11,-2,-6,9};
	int thissum,maxsum,i;

	thissum = maxsum = 0;
	for(i = 0;i < 8;i++)
	{
		thissum += num[i];
		if(thissum > maxsum)
			maxsum = thissum;
		else if(thissum < 0) //Set thissum to 0 
			thissum = 0;
	}
	printf("The maxsum is %d\n",maxsum);

	return 0;
}
