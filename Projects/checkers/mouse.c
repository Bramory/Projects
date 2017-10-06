#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "List.h"
#include "mouse.h"
#include "draw.h"

#include "const.h"

void MousePressed(int button, int state, int x, int y)
{

        switch(button)
        {
            case GLUT_LEFT_BUTTON:

                break;

            case GLUT_MIDDLE_BUTTON:
                glutSetWindowTitle("MiddleButtonPressed");

                break;

            case GLUT_RIGHT_BUTTON:
                glutSetWindowTitle("RightButtonPressed");

                break;
        }
}

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


void MousePressedMove(int ax, int ay)
{
    glutSetWindowTitle("MousePressedMove");
}
