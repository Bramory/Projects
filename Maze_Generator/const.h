#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#include <stack>
using namespace std;
//window position
extern int x_position;
extern int y_position;
extern int width;
extern int height;
extern int w;

//for mouse coordinate
extern int x;
extern int y;

extern int pause;

//for objects
extern int cols;
extern int rows;

extern cell *cells;
extern cell *current;
extern stack <cell> stack_;

extern cell *Me;



#endif // CONST_H_INCLUDED
