//**********************************
// MAZE_GENERATOR
//**********************************
//
//Created by Bramory 03.06.17
//

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "keyboard.h"
#include "draw.h"
#include "mouse.h"

//window position
int N = 32;
int x_position = 0;
int y_position = 0;
int width;
int height;

//for random filling
int MIN_VALUE = 0;
int MAX_VALUE = 999;

//for mouse coordinate
int x = 0;
int y = 0;

//for graphics
int sleep = 10;

//for objects
int rect_size = 10;



void Initialize ()
{
    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);


    glutSwapBuffers();
}

void MyIdle()
{
    display();
    Sleep(sleep);
}

int main(int argc, char **argv)
{
    srand(time(0));

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    width = glutGet(GLUT_SCREEN_WIDTH);
    height = glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("MAZE");

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

    return 0;
}
