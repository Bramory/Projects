#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"
#include "const.h"

void renderBitmapString(float x, float y, void *font, char *string)
{
  char *c;
  int aLength = strlen(string);
  int i;
  for (i = 0; i < aLength; i++)
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
    //chessboard
    glRecti(x    * CELL_WIDTH +1, y    * CELL_HEIGHT,
           (x+1) * CELL_WIDTH,   (y+1) * CELL_HEIGHT);
}

/*
void timer(int)
{
    //glutPostRedisplay();
    display();
  //glutTimerFunc(500, timer, 0);
}
*/
