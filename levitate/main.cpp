//**********************************
// gravitate
//**********************************
//
//Created by Bramory 18.05.17
//
//
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <vector>

#include "mouse.h"

using namespace std;

typedef struct tagpoint
{
    int value;
    int x_pos;
    int y_pos;
    float vx;
    float vy;
}point;

//window parameters
int width =  800;
int height = 500;
int x_position = 0;
int y_position = 0;
float G = 0.04;
float SLOW_MO = 1;

//points
int MAX_AMOUNT = 30;
int current_amount = 1;
int pause = 25;
int x = 0;
int y = 0;

int speed = 1;
int rect_size = 10;

//color marks
float r = 0;
float g = 1;
float b = 0;

vector <point> points(MAX_AMOUNT);

void drawPoint(vector <point> &points)
{
    for(int i = 0; i < MAX_AMOUNT; i++)
    {
        r = rand() % 100 / 100.0;
        g = rand() % 100 / 100.0;
        b = rand() % 100 / 100.0;

        glColor3f(r,g,b);

        glRectf(points[i].x_pos, points[i].y_pos,
                points[i].x_pos + rect_size, points[i].y_pos + rect_size);
    }
}

void moving()
{
    for(int i = 0; i < MAX_AMOUNT; i++)
    {
        //in the air
        if (points[i].y_pos < height-rect_size)
        {
                //going down
                points[i].vy += (float)G*SLOW_MO;
                points[i].y_pos += points[i].vy;

                //dist between mouse and the point
                int dist = sqrt((points[i].x_pos - x)*(points[i].x_pos - x) +
                            (points[i].y_pos - y)*(points[i].y_pos - y));
                if (dist <= 200)
                {
                    if (points[i].x_pos > x)
                    {
                        points[i].vx += 200/dist;
                    }
                    else
                    {
                        points[i].vx += -200/dist;
                    }
                }
                    points[i].x_pos += points[i].vx;

        }


            //on the ground
            if (points[i].y_pos >= height-rect_size)
            {
                int position = rand() % width - rect_size;
                points[i].y_pos = -position;
                points[i].x_pos = position;
                points[i].vy = 0;
                points[i].vx = 0;
            }
        }
}

void MousePressed(int button, int state, int x, int y)
{
    bool down = false;
 //   printf("STATE = %d", state);

 SLOW_MO = 0;

    if (state == down )
    {
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
        //printf("IndexToMark = %d\n", indexToDelete);
    }
}


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

    //Sleep(pause); ????

    drawPoint(points );

    glutSwapBuffers();
}

void MyIdle()
{
    moving();
    display();
}

void MouseMove(int ax, int ay)
{
    glutSetWindowTitle("MouseMove");
    x = ax;
    y = ay;
    SLOW_MO = y/100.0;
  //  printf("%.3f\n", SLOW_MO);
}

void magnet(void)
{

        for(int i = 0; i < MAX_AMOUNT; i++)
    {
        //in the air
        if (points[i].y_pos < height-rect_size)
        {
            int dist = sqrt((points[i].x_pos - x)*(points[i].x_pos - x) +
            (points[i].y_pos - y)*(points[i].y_pos - y));

                if (points[i].x_pos <= x)
                {
                    points[i].vx += dist/200;
                    points[i].x_pos += points[i].vx;
                }
                else
                {
                    points[i].vx += -dist/200;
                    points[i].x_pos += points[i].vx;
                }


                if (points[i].y_pos <= y)
                {
                    points[i].vy += dist/200;
                    points[i].y_pos += points[i].vy;
                }
                else
                {
                    points[i].vy += -dist/200;
                    points[i].y_pos += points[i].vy;
                }

                if (dist <= 50)
                {
                    points[i].x_pos = x + rand()% 20;
                    points[i].y_pos = y + rand()% 20;
                    points[i].vy = 0;
                    points[i].vx = 0;
                }
        }

    }
}

void MousePressedMove(int ax, int ay)
{
    glutSetWindowTitle("MousePressedMove");
    x = ax;
    y = ay;

    magnet();


}



int main(int argc, char **argv)
{
    srand(time(0));

    for(int i = 0; i < MAX_AMOUNT; i ++)
    {
        points[i].x_pos = rand() % width;
        points[i].y_pos = -(rand() % height)-rect_size;
        points[i].vy = 0;
        points[i].vx = 0;
        points[i].value = 0;
    }

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    width = 300;//glutGet(GLUT_SCREEN_WIDTH);
//    height = 300; //glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("Earth Gravitation");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
//    glutKeyboardFunc(Keyboard);
//    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutMainLoop();
    return 0;
}
