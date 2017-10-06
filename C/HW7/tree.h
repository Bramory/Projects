//
//  tree.h
#ifndef tree_h
#define tree_h

typedef struct __tagNode
{
	int value;
	struct __tagNode *leftChild;
	struct __tagNode *rightChild;
} IntNode;

typedef struct __tagTree
{
	IntNode *root;
	int count;
} IntTree;

// interface
IntTree *createIntTree();
void insertIntValueToTree(IntTree *aTree, int aValue);
IntNode *findNodeWithValue(IntTree *aTree, int aValue);
IntNode *findReceiver(IntTree *aTree, IntNode *aNodeToDestroy);
IntNode *findParentOfTheNode(IntTree *aTree, IntNode *aNode);

int countNodesWithTree(IntTree *aTree);

void destroyIntTree(IntTree *aTree);
int deleteNodeWithValue(IntTree *aTree, int aValue);

//methods for print binary tree
void printNode(IntNode *aNode);
void printTree(IntTree *aTree, void(*method)(IntNode *) );
void symmetry(IntNode *aNode);
void straight(IntNode *aNode);
void backward(IntNode *aNode);

//cool functions
void mergeTrees(IntTree *aTreeDst, IntTree *aTreeSrc);




int randomIntFromRange (int min, int max);
#endif /* tree_h */
