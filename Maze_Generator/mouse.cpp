#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "mouse.h"
#include "draw.h"
#include "const.h"

void Initialize (){
    glClearColor(0,0,0, 1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void removeWalls(cell *a, cell *b){
     ///left-right parts
    int x = a->i - b->i;
    if (x == -1){
        a->right = 0;
        b->left = 0;
    }
    if (x == 1){
        a->left = 0;
        b->right = 0;
    }

    ///top-bottom parts
    int y = a->j - b->j;
    if (y == -1){
        a->bottom = 0;
        b->top = 0;
    }
    if (y == 1){
        a->top = 0;
        b->bottom = 0;
    }
}

void MousePressed(int button, int state, int x, int y)
{
    bool down = false;
    if (state == down )
    {
        system("cls");


        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                glutSetWindowTitle("LeftButtonPressed");

                break;

            case GLUT_MIDDLE_BUTTON:
                glutSetWindowTitle("MiddleButtonPressed");

                break;

            case GLUT_RIGHT_BUTTON:
                glutSetWindowTitle("RightButtonPressed");

                break;
        }
    }
}

void mouse(int button, int state, int ax, int ay)
{
    x = ax;
    y = ay;
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


void MousePressedMove(int ax, int ay)
{
    glutSetWindowTitle("MousePressedMove");
}
