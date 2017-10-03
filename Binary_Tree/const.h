#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED
#include "binary_tree.h"
#include "List.h"

//Maximum amount of elements in a Tree
extern int amount;

// for graphics functions, MyIdle, etc...
extern int sleep;

//limits of rand VALUES
extern int min;
extern int max;

//height between cells in "y" ax
extern int deltaY;
extern int SizeOfSquare;
extern int rootPosition_Y;
extern int MAX_DEPTH;
//mouse
extern int x;
extern int y;

//window parameters
extern int width;
extern int height;
extern int x_position;
extern int y_position;


//global TREE and LIST
extern IntTree *aTree;
extern IntList *aList;


#endif // CONST_H_INCLUDED
