//
// Start at 12.05.2017 0:14
// Finish = 18.05.2017 00:00
//
//Created by Bramory
//
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <limits.h>

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

IntList *aList;

int N = 32;
int x_position = 0;
int y_position = 0;
int width  = 1320;
int height = 704;
const float CELL_WIDTH  = width/N;
const float CELL_HEIGHT = height/N;

//return numbers from [a ... b]
int randomIntFromRange (int min, int max)
{
    return rand() % (max-min+1) + min;
}

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
		return NULL;
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
		theNode->mark = 0;
	}

	return theNode;
}


void PrintList(IntList *aList)
{
	if (NULL == aList || 0 == aList->count)
	{
		printf(" empty\n");
		return;
	}

	printf("\nList with count (%d):   ", aList->count);
	IntNode *theNode = aList->head;
	do
	{
		printf("(%d|%d) ", theNode->value, theNode->mark);
		theNode = theNode->next;

	}while (aList->head != theNode);

	printf ("\n");
}


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
	aList->count--;
	return theResult;
}

//return 0 if sucsess
//otherwsise -1
int DeleteMarksElements( IntList *aList )
{
    if (aList == NULL)
    {
        return -1;
    }
    int theResult = -1;
	IntNode *aNode = aList->head;
	int IndexToDelete = 0;

	while (IndexToDelete < aList-> count)
    {
        if (aNode->mark)  //different states
        {
            aNode = aNode->next;
            DeleteIntValueAtIndex(aList, IndexToDelete);
            theResult = 0;
        }
        else
        {
            aNode = aNode->next;
            IndexToDelete++;
        }

        if (aNode == NULL)
            break;
    }
    //PrintList (aList); //finish result
return theResult;
}


void display ( void);
//void timer ( int);

float x = 0; // ??float
float y = 0;

void mouse(int button, int state, int ax, int ay)
{
    x = ax;
    y = ay;
    //down = state == GLUT_LEFT_BUTTON;
}

void motion(int ax, int ay)
{
    int x = ax;
    int y = ay;
}

void Initialize ()
{
    glClearColor(1, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

IntList *getIntListWithRandValues( int amount, bool state )
{
    IntList *aList = CreateIntList();
    if(NULL == aList)
        return NULL;
    int i;

    //sequence for Euclid's Sieve
    if(state  == 1)
    {
        for (i = 0; i < amount; i++)
            AddIntValueToList(aList, i+1);
    }
    else
    {
        for (i = 0; i < amount; i++)
            AddIntValueToList(aList, randomIntFromRange(0, MAXINT_PTR));
    }
    return aList;
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'e':
        exit(0);
        break;
    }
}

void SKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
            DeleteIntValueAtIndex(aList, 0);
        break;
    case GLUT_KEY_RIGHT:
        if (aList->count < N*N)
            AddIntValueToList(aList, randomIntFromRange(0, 9));
        break;
    case GLUT_KEY_UP:
            while (aList->count < N*N)
                AddIntValueToList(aList, randomIntFromRange(0, 9));
        break;
    case GLUT_KEY_DOWN:
            while (aList->count > 0)
                DeleteIntValueAtIndex(aList, 0);
        break;
    }
}

void MyIdle()
{
    display();
    Sleep(10);
}

void MouseMove(int ax, int ay)
{
    glutSetWindowTitle("MouseMove");
    x = ax;
    y = ay;
}

void MarkIndexToDelete(int MultipleIndex, bool markFirst)
{
    if (MultipleIndex > aList->count - 1 || MultipleIndex < 0)
    {
        return;
    }

    int IndexToMark;
    IntNode *aNode = aList->head;

    //mark all cells
    if (MultipleIndex == 0)
    {
        if(markFirst)
        {
            IndexToMark = MultipleIndex;
        }
        //without first element
        else
        {
            IndexToMark = 1;
            aNode = aNode->next;
        }

         for(IndexToMark; IndexToMark < aList->count; IndexToMark++)
        {
            aNode->mark = (aNode->mark + 1) % 2; // different states
            aNode = aNode->next;
        }
    }

    //mark multiples cells
    else
    {
        (markFirst) ? IndexToMark = MultipleIndex // within
                    : IndexToMark = 2 * MultipleIndex+1; //without chosen element

        while(IndexToMark < aList->count)
        {
            aNode = FindTheNodeAtIndex(aList, IndexToMark);
            if (aNode == NULL)
                break;

            IndexToMark += MultipleIndex+1;
            if (!markFirst)
            {
                if (aNode->mark == 0)               //temporary line
                    aNode->mark = (aNode->mark + 1) % 2; // different states
            }
            else
            {
                aNode->mark = (aNode->mark + 1) % 2; // different states
            }


        }
    }

}

void MousePressed(int button, int state, int x, int y)
{
    bool down = false;
    if (state == down )
    {
        system("cls");
        int indexToDelete = (N * (int)(y/CELL_HEIGHT) + (int)(x/CELL_WIDTH +1)) - 1;
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                glutSetWindowTitle("LeftButtonPressed");
                MarkIndexToDelete(indexToDelete, 1);
                printf("IndexToMark = %d", indexToDelete);
                printf("MAX INDEX = %d", aList->count - 1 );
                display();
                //PrintList(aList);
                break;

            case GLUT_MIDDLE_BUTTON:
                glutSetWindowTitle("MiddleButtonPressed");
                printf("Coordinate = %i\n\n", indexToDelete+1);
                if (0 != DeleteMarksElements(aList) )
                    DeleteIntValueAtIndex(aList, indexToDelete);
                break;

            case GLUT_RIGHT_BUTTON:
                glutSetWindowTitle("RightButtonPressed");
                MarkIndexToDelete(indexToDelete, 0);
                printf("IndexToMark = %d", indexToDelete);
                printf("MAX INDEX = %d", aList->count - 1 );
                display();
                //PrintList(aList);

                break;
        }
    }
}

void MousePressedMove(int ax, int ay)
{
    glutSetWindowTitle("MousePressedMove");
}


int main(int argc, char **argv)
{
    srand(time(0));

    aList = getIntListWithRandValues(N*N, 1);

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("Sieve");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutMainLoop();

    //DestroyIntList(aList);
    return 0;
}

void renderBitmapString(float x, float y, void *font, char *string)
{
  char *c;
  int aLength = strlen(string);
  for (int i = 0; i < aLength; i++)
  {
        x -= 4; //for every digit
  }
  glRasterPos2f(x, y);
  for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawCell(int x, int y, IntNode *aNode )
{
    switch(aNode->mark)
    {
        //non-chosen
        case false:
        glColor3f(1, 1, 0);
        break;

        //chosen cells
        case true:
        glColor3f(0, 0.6, 1);
        break;
    }

     //Print All numbers
    glBegin(GL_QUAD_STRIP);
    glVertex2f( x    * CELL_WIDTH +1, y    * CELL_HEIGHT);
    glVertex2f((x+1) * CELL_WIDTH, y    * CELL_HEIGHT);
    glVertex2f( x    * CELL_WIDTH +1,(y+1) * CELL_HEIGHT - 1);
    glVertex2f((x+1) * CELL_WIDTH,(y+1) * CELL_HEIGHT - 1);
    glEnd();

    glColor3f(0, 0, 0);
    char *string = (char*)malloc(sizeof(char)*10);
    itoa (aNode->value, string, 10);
    renderBitmapString(x * CELL_WIDTH  + CELL_WIDTH /2 - 1,
                       y * CELL_HEIGHT + CELL_HEIGHT/2 + 4,
                       GLUT_BITMAP_9_BY_15, string);
    free(string);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    int i;
    for (i = 1; i < N; ++i) //vertical
    {
        glVertex2f(i * CELL_WIDTH, 0);
        glVertex2f(i * CELL_WIDTH,  height);
    }
    for (i = 1; i < N; ++i) //vertical
    {
        glVertex2f(0, i * CELL_HEIGHT);
        glVertex2f(width, i * CELL_HEIGHT);
    }
    glEnd();

    //NUMBERS
    int amount = 0;
    IntNode *aNode = aList->head;

        for (int y = 0; y < N; y++)
        {
             for (int x = 0; x < N; x++)
            {
                if(amount < aList->count)
                {
                    drawCell(x, y , aNode);
                    aNode = aNode->next;
                    amount++;
                }
            }
        }
    glutSwapBuffers();
}


/*
void timer(int)
{
    //glutPostRedisplay();
    display();
  //glutTimerFunc(500, timer, 0);
}
*/
