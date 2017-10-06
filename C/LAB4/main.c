/*
Варіант 5 
В кільцевому списку видаляти кожний третій елемент, 
поки не залишиться менше трьох. 
Відобразити процес на екрані
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include <time.h>

#include "List.h"
#include "sort.h"


int main( void )
{
	srand(time(0));
	unsigned int const count = pow(10, 1);
	
	IntList *theList = CreateIntList();
	if (NULL == theList)
	{
		return -1;
	}

	int z;
	for( z = 0; z < count;  z++)
	{
		AddIntValueToList(theList, random(9999) );
	}
	
	DeleteMultiplesElements(theList, 3);
	
	DestroyIntList(theList); // ???
	return 0;
}

