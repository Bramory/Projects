#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "List.h"

int N = 10;
int width  = 1320;
int height = 704;
#define CELL_WIDTH  width/N
#define CELL_HEIGHT height/N


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
                    : (IndexToMark = 2 * MultipleIndex+1); //without chosen element

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
    int y,x;
        for (y = 0; y < N; y++)
        {
             for (x = 0; x < N; x++)
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
