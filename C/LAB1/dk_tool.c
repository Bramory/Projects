#include <stdio.h>
#include "dk_tool.h"
 
int fact(int number)
{
    int theResult = 1;
    while (number > 1)
    {
        theResult *= number;
        number--;
    }
    return theResult;
}


int power (int number, int power)
{
    int theResult = 1;
    while (power > 0)
    {
        theResult = theResult * number;
        power--;
    }
    return	theResult;
}

int num_scan( void )
{
	int num = 0, proof = 0;
    do
    {
        proof = scanf("%d", &num);
      if(proof == 1) break; 
	  printf("Incorrect input, try again");
    }
    while (1);
return num;
}
