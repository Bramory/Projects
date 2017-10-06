#include <stdio.h>
#include <conio.h>
#include "dk_tool.h"

int main()
{
    int A, B = -1, C;
    float Q;
    printf("Type values: A, B[>=0], C\n");
    printf("Type 1 number each time: \n");
   	
   	//read only numbers
        A = num_scan();
        do
        {
        	B = num_scan();
        	if (B >= 0) break;
			printf("B must be >= 0");
    	}
    	while (1);
		C = num_scan();
  

    Q = ((A*A) + (B*B)) / (float)(B + power(5, C)) + fact(B) ;
    printf("      (%i^2 + %i^2)               + %i!     = %.5f - [Q]\n", A, B, B, Q);
    printf("----------------------------\n");
    printf("   (%i + 5^%i)",B, C);

    getch();
    return 0;
}
