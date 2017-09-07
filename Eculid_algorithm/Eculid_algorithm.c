#include <stdio.h>
unsigned int gcd(unsigned int m,unsigned int n);
int main(void)
{
	int a = 1959;
	int b = 1590;
	
	printf("The greatest common divisor is: %d\n",gcd(a,b));

	return 0;
}

unsigned int gcd(unsigned int m,unsigned int n)
{
	return (n == 0 ? m : gcd(n,m % n));  //Use recurion to write this gcd function,which is the simplest method
}