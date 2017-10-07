#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "prime.h"

unsigned int N = pow(10, 7); //default value
//	counter = prime_list (N, numbers);

int main() 
{
	int i, j, counter = 0;
	double AllTime = 0;	
	printf ("Enter the N: ");
	N = num_scan();
	
	float time = clock();
	unsigned char *numbers = (char *) malloc(sizeof(char) * N + 1);
	time = clock() - time;
	printf ("\n Time for malloc  -  %.3f sec", time/1000);
	AllTime += time;

	time = clock();
	memset (numbers, 1, sizeof(char) * N);
	time = clock() - time;
	printf ("\n Time for memset  -  %.3f sec", time/1000);
	AllTime += time;
	
	time = clock();
	sieve(N, numbers );
	time = clock() - time;
	printf ("\n Time for sieve   -  %.3f sec", time/1000);
	AllTime += time;
	
	time = clock();
	counter = prime_file(N, numbers);
	time = clock() - time;
	printf ("\n Time for output  -  %.3f sec", time/1000);
	AllTime += time;
	printf ("\n Time for process -  %.3f sec", AllTime/1000);
		
	printf ("\n Primes -  %i", counter);
	printf ("\n Memory usage -  %.3f Mb\n", (float) sizeof(char)*N  * pow(10, -6) );	
	
	printf ("See all the numbers in \"Primes.txt\"\n");
	free(numbers);
return 0;
}
