#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

// Node description
typedef struct tagNode IntNode;

struct tagNode
{
	IntNode *prev;
	IntNode *next;
	int value;
	int mark;
};

// List description
typedef struct tagList
{
	IntNode *head;
	IntNode *tail;
	int count;
}IntList;


//return numbers from [a ... b]
int randomIntFromRange (int min, int max);

IntList *CreateIntList( void );
void DestroyIntList(IntList *aList);
IntNode *FindTheNodeAtIndex(IntList *aList, int anIndex);
int AddIntValueToList(IntList *aList, int anIntValue);
int IntValueAtIndex(IntList *aList, int anIndex);
int InsertIntValueAtIndex(IntList *aList, int anIntValue, int anIndex);
void PrintList(IntList *aList);
int DeleteIntValueAtIndex(IntList *aList, int anIndex);

//return 0 if sucsess
//otherwsise -1
int DeleteMarksElements( IntList *aList );

IntList *getIntListWithRandValues( int amount, bool state );



#endif // LIST_H_INCLUDED
