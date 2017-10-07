#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>



int N;
int width;
int height;
int rect_size;

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

void drawCell(int x, int y)
{
    glColor3f(1, 0, 0);
    glRecti(x, y,
        x+rect_size, y+rect_size);

}


/*
void timer(int)
{
    //glutPostRedisplay();
    display();
  //glutTimerFunc(500, timer, 0);
}
*/
