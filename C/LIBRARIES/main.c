//
// Start at 12.05.2017 0:14
// HardWork at 13.05.17 {13:00:00} - 14.05.17 {01:00:00}
// Finish = 18.05.2017 00:00
//
//Created by Bramory
//
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "List.h"
#include "keyboard.h"
#include "draw.h"
#include "mouse.h"


int N = 10;
int x_position = 0;
int y_position = 0;
int width  = 1320;
int height = 704;
#define CELL_WIDTH  width/N
#define CELL_HEIGHT height/N


void Initialize ()
{
    glClearColor(1, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void MyIdle()
{
    display();
    Sleep(10);
}

IntList *aList;

int main(int argc, char **argv)
{
    srand(time(0));

    aList = getIntListWithRandValues(N*N, 1);

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("Sieve");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutMainLoop();

    DestroyIntList(aList);
    return 0;
}


//void timer ( int);
