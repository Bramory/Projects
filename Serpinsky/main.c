//**********************************
// Triangle
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
#include <vector>

#include "draw.h"

usind namespace std;

vector <point> points(100);

void Initialize ()
{
    glClearColor(1, 0, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

   drawPoints(aList);
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

    points[0].x_pos = width/2;
    points[0].y_pos = height/4;
    points[0].value = 0;

    points[1].x_pos = width/4;
    points[1].y_pos = height*3/4;
    points[1].value = 1;

    points[2].x_pos = width*3/4;
    points[2].y_pos = height*3/4;
    points[2].value = 2;

    points[3].x_pos = 150;
    points[3].y_pos = 150;
    points[3].value = 0;

    int somePoint = 0;
    for (int i = 4; i < points.size(); i++)
    {
        somePoint = rand(3);

        points[i].x_pos = (points[i-1].x_pos + points[somePoint].x_pos) / 2;
        points[i].y_pos = (points[i-1].y_pos + points[somePoint].y_pos) / 2;
        points[i].value = i;
    }



    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    width = 300;//glutGet(GLUT_SCREEN_WIDTH);
    height = 300; //glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("No_square");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
//    glutKeyboardFunc(Keyboard);
//    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
//    glutMouseFunc(MousePressed);
//    glutPassiveMotionFunc(MouseMove);
//    glutMotionFunc(MousePressedMove);
    glutMainLoop();

    DestroyIntList(aList);
    return 0;
}
