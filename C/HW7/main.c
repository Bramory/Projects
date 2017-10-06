#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"


int main(int argc, char *argv[]) 
{
	srand(time(0));
	printf("HELLO, WORLD!\n\n");
		
	IntTree *aTree = createIntTree();
	if (NULL == aTree)
	{
		return -1;
	}
	
	//filling array with random numbers
//	unsigned const int count = 100;
//	int numbers[count+1], i;
//	for(i = 0; i < count; i++)
//		numbers[i] = randomIntFromRange(100 - 1, 999);
	
//	//adding numbers in the binary tree
//	for(i = 0; i < count; i++)
//		insertIntValueToTree(aTree, numbers[i] );
		
	insertIntValueToTree(aTree, 5);
    insertIntValueToTree(aTree, 10);
    insertIntValueToTree(aTree, 8);
    insertIntValueToTree(aTree, 21);
    insertIntValueToTree(aTree, 19);
    insertIntValueToTree(aTree, 25);


	deleteNodeWithValue(aTree, 10);	
		
	insertIntValueToTree(aTree, 99);
//	deleteNodeWithValue(aTree, 3);

	//fantastic, callback function it's powerful thing!
	printf("Symmetry method\n");
	printTree(aTree, symmetry);
//	
//	printf("\nStraight method\n");
//	printTree(aTree, straight);
//	
//	printf("\nBackward method\n");
//	printTree(aTree, backward);
//	
	
	printf("\nYour Node = ");
	
	IntNode *aNode = findNodeWithValue(aTree, 99);
	printNode(aNode);
	
	IntNode *aParentNode = findParentOfTheNode(aTree, aNode);
	printf("\nYour Parent Node = ");
		printNode(aParentNode);
	
	
	
	destroyIntTree(aTree);
	return 0;
}
