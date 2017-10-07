#include "prime.h"
#include <stdio.h>

void sieve ( int size, char *numbers )
{
	int i, j;
	for (i = 3; i * i <= size; i+=2)
		if ( numbers[i] != 0)
			for(j = i+i; j <= size; j += i )
				numbers[j] = 0;
}


int prime_list(int size, char *numbers )
{
	int i, counter = 1;
		printf ("2 ");//'cause 2 is prime
		for(i = 3; i <= size; i +=2 )
		{
			if ( numbers[i] != 0) 
			{
			printf ("%i ", i );
			counter++;
			}
		}
	return counter;
}

int prime_file(int size, char *numbers)
{
	int i, counter = 1;
	FILE *file = fopen("Prime.txt", "w");
	if (NULL != file)
	{
			fprintf (file, "2 " );
		for(i = 3; i <= size; i += 2 )
		{
			if ( numbers[i] != 0) 
			{
			fprintf (file, "%i ", i );
			counter++;
			}
		}
	close(file);
	return counter;
	}
	else printf("Smth went wrong..");
	return -1;
}

int num_scan( void )
{
	int num = 0, proof = 0;
    do
    {
		proof = scanf("%d", &num);
		if(proof == 1) break;
		printf("Incorrect input, enter int\n");
		fflush(stdin);
    }
    while (1);
return num;
}

