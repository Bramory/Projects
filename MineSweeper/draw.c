#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "draw.h"
#include "mouse.h"

int N;
int width;
int height;
int game_state;
int SizeOfSquare;


void gameOver(void)
{
    glColor3f(0,0,0);

    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(width,0);
    glVertex2f(width, height);
    glVertex2f(0,height);
    glEnd();

    glColor3f(1,1,1);
    renderBitmapString(width/2, height/2, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
}

void youWin(void)
{
    glColor3f(1,1,1);

    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(width,0);
    glVertex2f(width, height);
    glVertex2f(0,height);
    glEnd();

    glColor3f(0,0,0);
    renderBitmapString(width/2, height/2, GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN");

}

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

void draw_field(field *aField )
{
    draw_net();
    cell *aCell;
    for(int y = 0;  y < N; y++ )
    {
        for(int x = 0; x < N; x++)
        {
            aCell = &aField->cells[y*N + x];
            drawCell(x, y, aCell);
        }
    }
}


void drawCell(int x, int y, cell *aCell )
{
    switch(aCell->view)
    {
        //close
        case 0:
        glColor3f(0, 0.2, 0.8);
        break;

        //open
        case 1:
        glColor3f(0.6, 0.6, 0.6);
        break;

        //mark by flag
        case 2:
            glColor3f(0.8, 0, 0);
            break;
    }

     //Print All numbers
    glBegin(GL_QUAD_STRIP);
    glVertex2f( x    * SizeOfSquare +1, y    * SizeOfSquare);
    glVertex2f((x+1) * SizeOfSquare, y    * SizeOfSquare);
    glVertex2f( x    * SizeOfSquare +1,(y+1) * SizeOfSquare - 1);
    glVertex2f((x+1) * SizeOfSquare,(y+1) * SizeOfSquare - 1);
    glEnd();

    if (aCell->view == 1)
    {
        switch(aCell->value)
        {
            case 0: break;
            case 1:
                    glColor3f(0, 0, 1);
                    break;
            case 2:
                   glColor3f(0, 1, 0);
                    break;
            case 3:
                   glColor3f(1, 0, 0);
                    break;
            case 4:
                    glColor3f(0, 0, 0.5);
                    break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                    glColor3f(1, 1, 0);
                    break;
        }
        char *str = (char*)malloc(sizeof(char)*10);
        itoa(aCell->value, str, 10);

        renderBitmapString((x * SizeOfSquare + SizeOfSquare/2 - 1),
                           (y * SizeOfSquare + SizeOfSquare/2 + 4),
                            GLUT_BITMAP_9_BY_15,
                            str);
        free(str);
    }

    if (aCell->view == 2)
    {
        //color for label
        glColor3f(0, 0, 0.9);
        renderBitmapString((x * SizeOfSquare + SizeOfSquare/2 - 1),
                           (y * SizeOfSquare + SizeOfSquare/2 + 4),
                            GLUT_BITMAP_9_BY_15,
                            "M");
    }

}


void draw_net(void)
{
    glColor3f(0,0,0);
        glBegin(GL_LINES);
    for (int i = 1; i < N; ++i) //vertical
    {
        glVertex2f(i * SizeOfSquare, 0);
        glVertex2f(i * SizeOfSquare,  height);
    }

    for (int i = 1; i < N; ++i) //horizontal
    {
        glVertex2f(0, i * SizeOfSquare);
        glVertex2f(width, i * SizeOfSquare);
    }
    glEnd();
}
