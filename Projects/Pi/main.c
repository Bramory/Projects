//**********************************
// PI CALCULATE
//**********************************
//Created by Bramory 03.06.17

#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "keyboard.h"
#include "draw.h"
#include "mouse.h"

double M_PI = 3.1415926535897932384626433832795;
//window position
int x_position = 800;
int y_position = 50;
int width  = 500;
int height = 500;
int scl;
//for mouse coordinate
int x = 0;
int y = 0;

int pause = 10;

int amount = 10000;
int N = 1;
cell *points;

void Initialize (){
    glClearColor(0,0,0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width, width, height, -height, -1, 1);
}

void setPoints(void);

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    setPoints();
    int ptsInside = 0;
    float SumPI = 0;

    for(int i = 0; i < N; i++ )    {
        ptsInside = 0;
        for(int j = 0; j < amount; j++ )        {
            int dist = sqrt( pow( (0 - points[j].x), 2) +
                             pow( (0 - points[j].y), 2) );

            //printf("\n DIST = %.1f", dist);
            if (dist < width){
                ptsInside ++;
                glPointSize(1);
                glColor3f(1,1,1);
                drawPoint(&points[j]);
            }
            else            {
                if (dist > width)                {
                    glPointSize(1);
                    glColor3f(1,0,0);
                    drawPoint(&points[j]);
                }
                else
                    if (dist == width)                    {
                        glColor3f(0,0,1);
                        glPointSize(4);
                        drawPoint(&points[j]);
                    }

            }

        }
        SumPI += (float) ptsInside/amount;
    }

    //center Point
    glColor3f(0,0,1);
    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex2f(0, 0);
    glEnd();

    printf("\nSUM = %.6f", SumPI);
    printf("\nptsInside = %d", ptsInside);

    float exp_PI = (float) SumPI/N * 4;
    printf("\nM_PI   = %.6f", M_PI);
    printf("\nexp_PI = %.6f", exp_PI);
    float delta = (float) (exp_PI - M_PI) / M_PI * 100;
    if (delta < 0)
        delta *= -1;
    printf("\nPrecision = %.6f %%\n", (float) 100 - delta);

    glutSwapBuffers();
    system("pause");
}


void timer(int a){
    glutTimerFunc(pause, timer, 0);
}

void setPoints(void){
    for(int i = 0; i < amount -1; i++ )    {
        points[i].x = randomIntFromRange(-width, width);
        points[i].y = randomIntFromRange(-height, height);
    }
}

int main(int argc, char **argv){
    srand(time(0));
    scl = width;
    points = (cell*)malloc(sizeof(cell) * amount);
    setPoints();

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //width = glutGet(GLUT_SCREEN_WIDTH);
    //height = glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("MAZE");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
//    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutTimerFunc(10, timer, 0);
    glutMainLoop();

    return 0;
}
