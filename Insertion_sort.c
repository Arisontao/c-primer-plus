//Here comes the insertion_sort algorithm
//I describe it with C language
#include <stdio.h>

int main(void)
{
  int i,j; //loop variables
  int num[5] = {5,6,7,2,1};
  int key; //tag variable
  int temp; // swap variable

  for(i = 1;i < 5;i++)
  {
    key = num[i];
    for(j = i - 1;j >= 0 && num[j] > key;j--)
      num[j + 1] = num[j];
    num[j + 1] = key; //This method is equal to delete a number of an array, and in the last performing an assignment to the first number
  }
   
  return 0;
}
