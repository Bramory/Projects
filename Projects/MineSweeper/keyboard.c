#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


#include "tool.h"
#include "draw.h"

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'e':
        exit(0);
        break;
    }
}

void SKeyboard(int key, int x, int y)
{

    switch (key)
    {
        case GLUT_KEY_LEFT:


            break;

        case GLUT_KEY_RIGHT:

            break;

        case GLUT_KEY_UP:


            break;

        case GLUT_KEY_DOWN:

            break;
    }
}
