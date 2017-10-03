//**********************************
// EUCLID_SIEVE
//**********************************
//
//Created by Bramory 18.05.17
//

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "List.h"
#include "keyboard.h"
#include "draw.h"
#include "mouse.h"

#include "const.h"


//window position
int N = 8;
int x_position = 950;
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
IntList *aList;


void Initialize ()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void swap(int *a, int *b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);

    int amount = 0;
    int col1 = 1, col2 = 0;
    IntNode *aNode = aList->head;
    int x, y;
    for (y = 0; y < N; y++){
        for (x = 0; x < N; x++){
            if (amount % 2 == 0)
                glColor3f(col1, col1, col1);
            else
                glColor3f(col2, col2, col2);

            if ( x == N-1 && N%2 == 0 )
                swap(&col1, &col2);
            drawCell(x, y , aNode);
            aNode = aNode->next;
            amount++;
        }
    }
    glutSwapBuffers();
}

void MyIdle()
{
    display();
    //Sleep(sleep);
}

int main(int argc, char **argv)
{
    srand(time(0));

    aList = getIntListWithRandValues(N*N, 1);

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    width  = 400;//glutGet(GLUT_SCREEN_WIDTH);
    height = 400;//glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("Checkers");

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
