#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "List.h"
#include "mouse.h"
#include "draw.h"


int N = 10;
int width  = 1320;
int height = 704;
#define CELL_WIDTH  width/N
#define CELL_HEIGHT height/N
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
    x = ax;
    y = ay;
}

void MouseMove(int ax, int ay)
{
    glutSetWindowTitle("MouseMove");
    x = ax;
    y = ay;
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


