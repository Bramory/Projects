//  tool.c
//  dz3
//
#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

//return index of the Circle if it found, else -1
/*int binary_search(int key, FigureList *aList)
{
    int left = 0, right = aList->current_size - 1, middle;
//    	printf(" %i",  key );
    while (left<=right)
    {
    	middle = left + (right - left) / 2;
     if (aList->circles[middle].radius == key) 
	 	return middle; //find
	 else if (aList->circles[middle].radius < key)
     		right = middle - 1;			//num in the right half
        else
     		left = middle + 1;			//num in the left half
    }
    return -1;
}
*/
void swap (IntNode *var1, IntNode *var2)
{
	IntNode temp = *var1;
	*var1 = *var2;
    *var2 = temp;
}

void swapAddress(IntNode *aNodeC, IntNode *aNodeB, int aLeftIn, int aRightIn)	
{
	if(NULL == aNodeC || NULL == aNodeB)
	{
		return;
	}
	// a [c] ... |z| ... [b] e  (sort) = a (b) z (c) e
	if ( (aRightIn - aLeftIn) > 1 )
	{
		IntNode *aNextNode = aNodeC->next;
		IntNode *aPrevNode = aNodeB->prev; 
		
		aNodeC->next = aNodeB->next;
		aNodeB->prev = aNodeC->prev;
		
		aNodeC->next->prev = aNodeC;	
		aNodeB->prev->next = aNodeB;
		
		aNodeB->next = aNextNode; 
		aNodeC->prev = aPrevNode; 	
		
		aPrevNode -> next = aNodeC;
		aNextNode -> prev = aNodeB;
	}
	
	// a [c] [b] d  (sort) = a b c d
	else	
	{
//		if ( aNodeB->prev != NULL && aNodeC->next != NULL)
		{
			// a b c d  = acb
			aNodeB->next = aNodeC->next; // b->d
			aNodeC->prev = aNodeB->prev;//  a <-c
			
			aNodeC->next = aNodeB;	// c->b 
			aNodeB->prev = aNodeC;	// b <- c
			
			aNodeC->prev->next = aNodeC; // a -> c	
			aNodeB->next->prev = aNodeB; // c -> b
		}
		
		//	border element  [a] [b] c d e
//		else
//		{
//			aNodeB->next->prev = aNodeB->prev;
//			aNodeB->next = aNodeC->prev;
//			
//			aNodeC->next = aNodeB;
//			aNodeB->prev = aNodeC;
//			
//			aNodeC->prev -> next = aNodeC;
//			aNodeB->next -> prev = aNodeB;
//		}
		
	}
	
}

int num_scan( void )
{
	int num = 0, proof = 0;
    do
    {
        proof = scanf("%d", &num);
      if(proof == 1) break; 
	  printf("Incorrect input, try again");
	  fflush(stdin);
    }
    while (1);
return num;
}

