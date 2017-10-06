// List.c

#include "List.h"
#include <limits.h>
#include <stdlib.h>

IntNode *createIntNodeWithValue(int anIntValue);
IntNode *FindTheNodeAtIndex(IntList *aList, int anIndex);

IntList *CreateIntList( void )
{
	IntList *theList = (IntList *)malloc(sizeof(IntList));
	
	if (NULL != theList)
	{
		theList->head = NULL;
		theList->tail = NULL;
		theList->count = 0;
	}
	
	return theList;
}

void DestroyIntList(IntList *aList)
{
	if (NULL == aList)
	{
		return;
	}

	if (NULL != aList->head)
	{
		int anIndex = aList->count - 1;
		
		do
		{
		IntNode *theNodeToDelete = FindTheNodeAtIndex(aList, anIndex);
		free (theNodeToDelete);
		anIndex--;		
		}while (anIndex >= 0);
	
		free(aList);
	}
}

IntNode *FindTheNodeAtIndex(IntList *aList, int anIndex)
{
	if(aList == NULL || anIndex < 0 || aList->count < anIndex )
	{
		return;
	}
	
	int i = 0;
	IntNode *theNode = aList->head;
	do
	{
		if (i == anIndex)
		{
			break;
		}
	
		theNode = theNode->next;
		i++;
	
	}while (theNode != aList->head);
	
	return theNode;
}


int AddIntValueToList(IntList *aList, int anIntValue)
{
	int theResult = -1;
	
	if (NULL != aList)
	{
		IntNode *theNode = createIntNodeWithValue(anIntValue);
	
		if (NULL != theNode)
		{
			// lets to add to the end of the list
			//1. The list is empty
			if (NULL == aList->head)
			{
				aList->head = theNode;
				aList->head->next = aList->head->prev = aList->head; //self recursion
			}
			else
			{
				//2. Have 2 or more elements
				if (aList->head->next != aList->head)
				{
					// (head) a b(tail)  + c => (head) a b c (tail)
					aList->tail->next = theNode; // b->c
					theNode->prev = aList->tail; // b<-c
					
					aList->tail = theNode;	// New tail
					
					aList->tail->next = aList->head; // c->a
					aList->head->prev = aList->tail; // c<-a
				}
				else
				{
					//3. Have only 1 element
					// (head) a  +  b  =>  (head) a b (tail)
					aList->tail = theNode;
					aList->head->next = aList->head->prev = aList->tail;
					aList->tail->next = aList->tail->prev = aList->head;	
				}
			}
		
			aList->count ++;
			theResult = 0;
		}
	}
	return theResult;
}

int IntValueAtIndex(IntList *aList, int anIndex)
{
	int theResult = INT_MAX;
	
	//list is empty   or   typed wrong index  
	if (NULL == aList || anIndex >= aList->count || anIndex < 0)
	{
		return theResult;
	}
	
	IntNode *theNode = FindTheNodeAtIndex(aList, anIndex);
	
	return theNode->value;
}

void PrintList(IntList *aList)
{
	if (NULL == aList || 0 == aList->count)
	{
		printf(" empty\n");
		return;
	}

	printf("List with count (%d):   ", aList->count);
	IntNode *theNode = aList->head;
	do
	{
		printf("(%d) ", theNode->value);
		theNode = theNode->next;
	
	}while (aList->head != theNode);
	
	printf ("\n");
}


int InsertIntValueAtIndex(IntList *aList, int anIntValue, int anIndex)
{
	int theResult = -1;
	
	if (NULL == aList || anIndex >= aList->count || anIndex < 0)
	{
		return theResult;
	}
	
	IntNode *theNewNode = createIntNodeWithValue(anIntValue);
	IntNode *theNode = FindTheNodeAtIndex(aList, anIndex);
	
	// Can't create theNewNode
	if (NULL == theNewNode)
	{
		return theResult;
	}
	
	//1. Have 1 element {b} => {a, b}
	if ( aList->count == 1 )
	{
		aList->tail = aList->head;
		aList->head = theNewNode;
		
		aList->head->next = aList->head->prev = aList->tail;
		aList->tail->next = aList->tail->prev = aList->head;
	}
	
	else
	// 2. For the first element {b,c} => {a,b,c}
	if (anIndex == 0)
	{
		IntNode *thePrevHead = aList->head;
		
		aList->tail->next = theNewNode;
		theNewNode->prev = aList->tail;
		
		aList->head = theNewNode;
		
		aList->head->next = thePrevHead;
		aList->head->prev = aList->tail;
	}
	
	//2. adding in the middle
	else
	{
		IntNode *theANode = theNode;
		
		// b c a d ^ z(2) = b->c->z->a->z
		theANode->prev->next = theNewNode; // c->z 
		theNewNode->prev = theANode;	   // z<-a
		
		theNewNode->next = theANode;		// z->a
		theANode-> prev = theNewNode;		// z<-a
	}	
	
	aList->count ++;
	theResult = 0;
	
	return theResult;
}

IntNode *createIntNodeWithValue(int anIntValue)
{
	IntNode *theNode = (IntNode *)malloc(sizeof(IntNode));
	if (NULL != theNode)
	{
		theNode->next = NULL;
		theNode->prev = NULL;
		theNode->value = anIntValue;
	}
	
	return theNode;
}


// continue ...
int DeleteIntValueAtIndex(IntList *aList, int anIndex)
{
	int theResult = -1;
	
	if (NULL == aList || anIndex >= aList->count || anIndex < 0)
	{
		return theResult;
	}
	
	IntNode *theNodeToDelete = FindTheNodeAtIndex(aList, anIndex);
	
	//1. for list with 1 element: {a} => {empty}
	if (aList->count == 1)	
	{
		free(theNodeToDelete);
		aList->count = 0;
		aList->head = NULL;
		aList->tail = NULL;
		theResult = 0;
		return theResult;
	}
	
	//2. for the head: {a, b, c} => {b, c}
	if (theNodeToDelete == aList->head)	
	{
		IntNode *theNextNode = aList->head->next;
		aList->head = theNextNode; 		//change the head
		aList->head->next = theNextNode->next; 
		aList->head->prev = aList->tail;
		
		aList->tail->next = aList->head;
		theResult = 0;
	}
	else
		//3. for the tail {a, b, c} => {a, b}
		if (theNodeToDelete == aList->tail)	
		{
			aList->tail = aList->tail->prev; //change the tail
			aList->tail->next = aList->head;
			aList->head->prev = aList->tail;
			theResult = 0;
		}
			else
			//3. delete from the middle {a, b, c} => {a, c} 
			{
				theNodeToDelete->prev->next = theNodeToDelete->next;
				theNodeToDelete->next->prev = theNodeToDelete->prev;
				theResult = 0;
			}
	
	free(theNodeToDelete);
	aList->count--;;
	return theResult;
}

void DeleteMultiplesElements(IntList *aList, int N)
{
	if (NULL == aList || N > aList->count - 1 || N < 1)
	{
		return;
	}
	
	int step;					 // begin from '0'
	int IndexToDelete, iteration;
	
	while (aList->count >= N )
	{
		printf("\nAfter %d iteration:\n", iteration);
		PrintList (aList);
		step = 0;
		IndexToDelete = N * (step+1) - step - 1;
		
		//while we can find multiple index
		while( aList->count - 1 >= IndexToDelete )
		{
			DeleteIntValueAtIndex(aList, IndexToDelete ); 
			step ++;
			IndexToDelete = N * (step+1) - step - 1;
		}
		
		iteration ++;
	}
		printf("\nAfter %d iteration:\n", iteration); 
		PrintList (aList); //finish result
}


//return numbers from [0...n-1] area
int random(int N)
{
	return rand() % N;
}
