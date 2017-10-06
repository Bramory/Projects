//
//  tree.c

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

static int destroyNode(IntNode *aNode);
static IntNode *createIntNodeWithValue(int aValue);

IntTree *createIntTree(void)
{
	IntTree *theTree = (IntTree *)malloc(sizeof(IntTree));
	
	if (NULL != theTree)
	{
		theTree->root = NULL;
		theTree->count = 0;
	}
	
	return theTree;
}

void destroyIntTree(IntTree *aTree)
{
	if (NULL != aTree)
	{
		destroyNode(aTree->root);
		free(aTree);
	}
}

void insertIntValueToTree(IntTree *aTree, int aValue)
{
	if (NULL == aTree)
	{
		return;
	}

	IntNode *theNode = createIntNodeWithValue(aValue);
	if (NULL == theNode)
	{
		return;
	}
	
	//1. List is empty
	if (NULL == aTree->root)
	{
		aTree->root = theNode;
		aTree->count ++;
	}
	
	//2. Have a root at least
	else
	{
		IntNode *theCurrent = aTree->root;
		IntNode *theParent = NULL;

		while (1)
		{
			//tree doesn't have the same values
			if (aValue == theCurrent->value)
			{
				return;
			}
			
			theParent = theCurrent;
					
			if (aValue < theCurrent->value)
			{
				theCurrent = theCurrent->leftChild;
				if (NULL == theCurrent)
				{
					theParent->leftChild = theNode;
					break;
				}
			}
			else
			{
				theCurrent = theCurrent->rightChild;
				if (NULL == theCurrent)
				{
					theParent->rightChild = theNode;
					break;
				}
			}
		}
	
		aTree->count ++;
	}
}


IntNode *findNodeWithValue(IntTree *aTree, int aValue)
{
	IntNode *theCurrentNode = NULL;

	if (NULL != aTree)
	{
		theCurrentNode = aTree->root; //<! - start from root
		while (aValue != theCurrentNode->value) //<! - walk through the tree
		{
			theCurrentNode = (aValue < theCurrentNode->value)
						? theCurrentNode->leftChild
						: theCurrentNode->rightChild;

			if (NULL == theCurrentNode)
			{
				break;
			}
		}
	}

	return theCurrentNode;
}

IntNode *findParentOfTheNode(IntTree *aTree, IntNode *aNode)
{
    IntNode *theParent = NULL;

	if (NULL != aTree && NULL != aNode)
	{
        IntNode *theCurrentNode = NULL;
		theCurrentNode = aTree->root; //<! - start from root
		while (aNode->value != theCurrentNode->value) //<! - walk through the tree
		{
		    theParent = theCurrentNode;
			theCurrentNode = (aNode->value < theCurrentNode->value)
						? theCurrentNode->leftChild
						: theCurrentNode->rightChild;

			if (NULL == theCurrentNode)
			{
				break;
			}
		}
	}
	return theParent;
}

IntNode *findReceiver(IntTree *aTree, IntNode *aNodeToDestroy)
{
	if (NULL == aTree || NULL == aNodeToDestroy)
	{
	    return NULL;
	}
	    IntNode *aReceiver = aNodeToDestroy->rightChild;
		while ( 1 ) //<! - walk from aNodeToDestroy
		{
			if (NULL == aReceiver->leftChild)
			{
				break;
			}
			aReceiver = aReceiver->leftChild; // to the smallest Node
		}

	return aReceiver;
}


int deleteNodeWithValue(IntTree *aTree, int aValue)
{
    //bad tree
	if(NULL == aTree)
		return -1;

	//empty list
	if(aTree->root == NULL)
        return -1;

	IntNode *theCurrentNode = findNodeWithValue(aTree, aValue);
    IntNode *theParent = findParentOfTheNode(aTree, theCurrentNode);

	//Not found needed Value
	if (theCurrentNode == NULL || theParent == NULL)
        return -1;

    // 0. delete root
    if (theCurrentNode == aTree->root)
        return -1;

    //1. node == Leaf
    if (theCurrentNode->leftChild  == NULL &&
        theCurrentNode->rightChild == NULL)
    {
        if (theParent->leftChild == theCurrentNode)
            theParent->leftChild = NULL;
        else
            theParent->rightChild = NULL;
    }
    //2. Node have only 1 child
    if (theCurrentNode->leftChild == NULL ||
           theCurrentNode->rightChild == NULL)
    {
         if (theParent->leftChild == theCurrentNode)
         {
              if (NULL != theCurrentNode->leftChild)
                 theParent->leftChild = theCurrentNode->leftChild;
          else
              theParent->leftChild = theCurrentNode->rightChild;
         }
          else
         {
             if (NULL != theCurrentNode->leftChild)
                  theParent->rightChild = theCurrentNode->leftChild;
             else
                  theParent->rightChild = theCurrentNode->rightChild;
         }
    }
	//3. aNode have 2 children
	if (theCurrentNode->leftChild != NULL &&
	theCurrentNode->rightChild!= NULL)
	{
	IntNode *aReceiver = findReceiver(aTree, theCurrentNode);
	
	//receiver = left leaf
	if (theCurrentNode->rightChild != aReceiver)
	{
	    //rightChild of the Receiver take
	    //the ParentOfTheReceiver on the left
	    IntNode *theParentOfReceiver = findParentOfTheNode(aTree, aReceiver);
	    if (aReceiver->rightChild != NULL)
	        theParentOfReceiver->leftChild = aReceiver->rightChild;
	    else
	        theParentOfReceiver->leftChild = NULL;
	
	    //take left & right bunches by receiver
	    aReceiver->leftChild = theCurrentNode->leftChild;
	    aReceiver->rightChild = theCurrentNode->rightChild;
	
	}
	
	//receiver = rightChild of Deleted Node
	if (theCurrentNode->rightChild == aReceiver)
	{
	    aReceiver->leftChild = theCurrentNode->leftChild;
	}
	
	//new pointer on the receiver
	//from the parent of deletedNode
	if (theParent->leftChild == theCurrentNode)
	    theParent->leftChild = aReceiver;
	else
	    theParent->rightChild = aReceiver;
}

    free(theCurrentNode);
	return 0;
}

void mergeTrees(IntTree *aTreeDst, IntTree *aTreeSrc);

//print information from a Node
void printNode(IntNode *aNode)
{
	if (NULL != aNode)
		printf("(%d) ", aNode->value);
	else
		printf("nill");
}


void printTree(IntTree *aTree, void(*method)(IntNode *) ) 			
{
	if (NULL != aTree)
	{
		if (aTree->count > 0)
		{
			IntNode *aNode = aTree->root;
			method(aNode);
		}
		else
			printf("List is empty\n");
	}
	else
		printf("List is not exist");
}

// root - left - right
void straight(IntNode *aNode )		////
{
	printNode(aNode);
	if(aNode->leftChild != NULL)
		straight(aNode->leftChild);

	if(aNode->rightChild != NULL)
		straight(aNode->rightChild);
	
}

// from leaves to parents
void backward(IntNode *aNode)
{
			
		if(aNode->leftChild != NULL)
		backward(aNode->leftChild);
		

	if(aNode->rightChild != NULL)
		backward(aNode->rightChild);
		
		printNode(aNode);
}

//check nodes by recursion:  MIN -> {..} -> MAX value
void symmetry(IntNode *aNode)
{
		
	if(aNode->leftChild != NULL)
		symmetry(aNode->leftChild);
		printNode(aNode);

	if(aNode->rightChild != NULL)
		symmetry(aNode->rightChild);
	
}


int countNodesWithTree(IntTree *aTree);

#pragma mark -
int destroyNode(IntNode *aNode)
{
	if (NULL != aNode)
	{
		destroyNode(aNode->leftChild);
		destroyNode(aNode->rightChild);
	
		free(aNode);
	}
}

IntNode *createIntNodeWithValue(int aValue)
{
	IntNode *theNode = (IntNode *)malloc(sizeof(IntNode));
	
	if (NULL != theNode)
	{
		theNode->leftChild = NULL;
		theNode->rightChild = NULL;
		theNode->value = aValue;
	}
	
	return theNode;
}

//return numbers from [a ... b] 
int randomIntFromRange (int min, int max)
{
    return rand() % (max-min+1) + min;
}
