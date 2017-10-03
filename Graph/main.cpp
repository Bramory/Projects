//**********************************
// Graph
//**********************************
//
//Created by Bramory 18.05.17
//
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <vector>

#include "mouse.h"

using namespace std;

typedef struct tagpoint{
    int value;
    float x_pos;
    float y_pos;
}point;

//window parameters
int width =  800;
int height = 800;
int x_position = 0;
int y_position = 0;

//points
int MAX_AMOUNT = width*2;
int current_amount = 1;
int pause = 2;
int x = 0;
int y = 0;

//color marks
float r = 0;
float g = 0;
float b = 0;

float SCALE = 0.015625;
float Period = 64;

vector <point> points(MAX_AMOUNT);

void MousePressed(int button, int state, int x, int y){
    bool down = false;
    if (state == down )    {
        system("cls");

        switch(button)        {
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
    }
}

void drawPoint(vector <point> &points){
    //float square = 0;
    //int sigma = 1;

    for(int i = 0; i < width*2; i ++){
        points[i].x_pos = (-width + i)/150; //from left -> right corner
        points[i].y_pos = log(points[i].x_pos)/150; //cos(points[i].x_pos / Period) / SCALE; //pow(points[i].x_pos, 3) / SCALE;
        points[i].value = 0;

        glColor3f(1,1,1);

        glBegin(GL_POINTS);
        glVertex2f(points[i].x_pos, points[i].y_pos );
        glEnd();

//        if (points[i].y_pos > 0 || (points[i].y_pos < 0 && (int)points[i].y_pos % sigma == 0))
//        {
//            square += points[i].y_pos * sigma;
//            glColor3f(0,0.8,0);
//            glRecti(points[i].x_pos, points[i].y_pos,
//                    points[i].x_pos + sigma, 1);
//        }
    }
     //printf("square  = %f\n", square);
}

//void mouse()
//{
//
//}

void Initialize (){
    glClearColor(0,0,0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);
}

void draw_net(void){
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2f(-width, 0);
    glVertex2f(width, 0);

    glVertex2f(0, -height);
    glVertex2f(0, height);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //Sleep(pause); //??????????????????????????????????????????????????????????????????????????????????????????????
    drawPoint(points);
    draw_net();

   glutSwapBuffers();
}

void MyIdle(){
    display();
}

void MouseMove(int ax, int ay){
    glutSetWindowTitle("MouseMove");
    x = ax;
    y = ay;

}

void MousePressedMove(int ax, int ay){
    glutSetWindowTitle("MousePressedMove");
    x = ax;
    y = ay;

}

void Keyboard(unsigned char key, int x, int y){
    switch (key)
    {
    case 'e':
        exit(0);
        break;

        case 'z':
        Period += 10;
        printf("Y = %f\n", Period );
        break;

        case 'x':
        Period  -= 10;
        printf("Y = %f\n", Period );
        break;

        case '.':
        SCALE *= 2;
        printf("SCALE = %f\n", SCALE);
        break;

        case ',':
        SCALE /= 2;
        printf("SCALE = %f\n", SCALE);
        break;
    }
}

int main(int argc, char **argv){
    srand(time(0));

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    width = 300;//glutGet(GLUT_SCREEN_WIDTH);
//    height = 300; //glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("graph");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
   glutKeyboardFunc(Keyboard);
//    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutMainLoop();
    return 0;
}
