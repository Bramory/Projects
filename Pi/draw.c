#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "draw.h"

int N;
int width;
int height;
int cell_size;

cell *cells;
cell *current;


void renderBitmapString(float x, float y, void *font, char *string){
  char *c;
  int aLength = strlen(string);
  int i;
  for (i = 0; i < aLength; i++)  {
        x -= 4; //for every digit
  }
  glRasterPos2f(x, y);
  for (c = string; *c != '\0'; c++)    {
        glutBitmapCharacter(font, *c);
    }
}

void drawPoint(cell *point){
    glBegin(GL_POINTS);
    glVertex2f(point->x, point->y);
    glEnd();
}

//return numbers from [a ... b]
int randomIntFromRange (int min, int max){
    return rand() % (max-min+1) + min;
}
