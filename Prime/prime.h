#ifndef prime_h
#define prime_h


/*
**	Sieve for non-prime numbers
*/
void sieve ( int size, char numbers[size] );

/*
**	Print on the screen prime-numbers from the sieved array
*/
int prime_list(int size, char numbers[size] );


/*
**	Print prime-numbers in the file
*/
int prime_file(int size, char numbers[size] );

// fool-proof
int num_scan( void );
#endif


/*
	
*/
