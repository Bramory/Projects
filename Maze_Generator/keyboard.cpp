#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "keyboard.h"
#include "draw.h"
#include "const.h"

///window position
int x_position = 300;
int y_position = 50;
int width;
int height;

//for mouse coordinate
int x = 0;
int y = 0;

///size of the square chose N*N size
int w = 20;

int cols;
int rows;
int pause = 1;

int MIN_VALUE;
int MAX_VALUE;


cell *cells;
cell *current;

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
        if (Me->i -1 >= 0 && !cells[index(Me->i-1, Me->j)].right)
            Me->i -= 1;
        break;

    case GLUT_KEY_RIGHT:
        if (Me->i +1 < rows && !cells[index(Me->i+1, Me->j)].left)
            Me->i += 1;
        break;

    case GLUT_KEY_UP:
        if (Me->j -1 >= 0 && !cells[index(Me->i, Me->j-1)].bottom)
            Me->j -= 1;
        break;

    case GLUT_KEY_DOWN:
        if (Me->j +1 < cols && !cells[index(Me->i, Me->j+1)].top)
            Me->j += 1;
        break;
    }
}
