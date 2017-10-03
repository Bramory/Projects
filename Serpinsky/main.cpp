//**********************************
// Triangle
//**********************************
//
//Created by Bramory 18.05.17
//
//
#include <GL/glut.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <vector>

#include "draw.h"
using namespace std;

//window parameters
int width =  1000;
int height = 700;
int x_position = 0;
int y_position = 0;
int rect_size = 1;

//points
int MAX_AMOUNT = 10000;
int current_amount = 100;
int pause = 1;

//square for animation
int leftUp_x = 0;
int leftUp_y = 0;
int leftDown_x = 0;
int leftDown_y = height;

int rightUp_x = width;
int rightUp_y = 0;
int rightDown_x = width;
int rightDown_y = height;

int leftSpeed = 0;
int rightSpeed = 0;
int speed = 8;

//let right border trigger
int trigger = 1;
int mainPoints = 3;
//color marks
float r = 1;
float g = 1;
float b = 1;

vector <point> points(MAX_AMOUNT);

void drawPoint(vector <point> &points)
{
    for(int i = 0; i < current_amount; i++)
    {
        r = rand() % 100 / 100.0;
        g = rand() % 100 / 100.0;
        b = rand() % 100 / 100.0;


        glColor3f(r,g,b);
        glRecti(points[i].x_pos, points[i].y_pos,
                points[i].x_pos + rect_size, points[i].y_pos+rect_size);
    }


    if (current_amount < MAX_AMOUNT)
        current_amount ++;
}


void move_square()
{
    //Sleep(pause);
    r = 0;
    g = 0;
    b = 0;

//    system("cls");
//    printf("r = %.2f\n", r);
//    printf("g = %.2f\n", g);
//    printf("b = %.2f\n", b);

    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(leftUp_x, leftUp_y);
    glVertex2f(rightUp_x, rightUp_y);
    glVertex2f(rightDown_x, rightDown_y);
    glVertex2f(leftDown_x, leftDown_y);
    glEnd();

    leftUp_x   += leftSpeed;
    leftDown_x += leftSpeed;

    rightUp_x   += rightSpeed;
    rightDown_x += rightSpeed;

    //begin_position
    if (leftUp_x  <= 0 && rightUp_x >= width)
    {
        if (trigger == 1)
        {
            leftSpeed = speed;
            rightSpeed = 0;
        }
        else
        {
            rightSpeed = -speed;
            leftSpeed = 0;
        }
    }

    //get the border
    if (leftUp_x >= width || rightUp_x <= 0)
    {
        if (trigger == 1)
        {
            leftSpeed = -speed;
        }
        else
        {
            rightSpeed = speed;
        }
        trigger = -trigger;
    }


}

//void mouse()
//{
//
//}

//void paint()
//{
//    while ()
//    {
//
//    }
//}

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

    //Sleep(pause);
    drawPoint(points );
    //move_square();

   glutSwapBuffers();
}

void MyIdle()
{
    display();
}

int main(int argc, char **argv)
{
    srand(time(0));

    points[0].x_pos = width/2;
    points[0].y_pos = height/8;
    points[0].value = 0;

    points[1].x_pos = width/8;
    points[1].y_pos = height*7/8;
    points[1].value = 1;//1;

    points[2].x_pos = width*7/8;
    points[2].y_pos = height*7/8;
    points[2].value = 2;

    points[3].x_pos = width/2;
    points[3].y_pos = height/2;
    points[3].value = 0;

    for (int i = 4; i < points.size(); i++)
    {
        int somePoint = rand() % mainPoints;
        points[i].x_pos = (points[i-1].x_pos + points[somePoint].x_pos) / 2;
        points[i].y_pos = (points[i-1].y_pos + points[somePoint].y_pos) / 2;
        points[i].value = i;
    }



    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    width = 300;//glutGet(GLUT_SCREEN_WIDTH);
//    height = 300; //glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
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
    //glutMotionFunc(MousePressedMove);
    glutMainLoop();
    return 0;
}
