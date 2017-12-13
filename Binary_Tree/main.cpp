//main.cpp
// Visualization of Binary Tree
//**********************************
//Created by Bramory 18.05.17
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "binary_tree.h"
#include "draw.h"
#include "List.h"
#include "keyboard.h"
#include "mouse.h"
#include "const.h"

void Initialize (){
    glClearColor(0, 0, 0, 0);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //draw lines, nodes, values
    DrawTree(aTree->root, 0, drawTreeLine);
    DrawTree(aTree->root, 0, drawTreeNode);
    //in the left up corner show coordinates
    Show_XY_pos(x,y);
    glutSwapBuffers();
}

void MyIdle(){
    display();
    Sleep(sleep);
    //glutSetWindowTitle("NothingToBeDone");
}

void timer(int a){
    glutPostRedisplay();
    glutTimerFunc(500, timer, 0);
}

//void Reshape(int new_width, int new_height)
//{
//  glViewport(0, 0, new_width, new_height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glOrtho(0, width, height, 0, -1, 1);
//  glMatrixMode(GL_MODELVIEW);
//
// width = new_width;
// height = new_height;
//}

//// Функція обробки події, що виникає при масштабуванні вікна
//void reshape(int width, int height)
//{
// // Обчислення відношення сторін вікна нового розміру
// if (height == 0) // Перевірка для уникнення ділення на 0
// height = 1;
// GLfloat aspect = (GLfloat)width / (GLfloat)height;
// // Встановлення розміру поля огляду відповідно до нових розмірів вікна
// glViewport(0, 0, width, height);
// // Встановлення параметрів проекційної матриці
// glMatrixMode(GL_PROJECTION); // Вибір матриці проекції
// glLoadIdentity(); // Скидання матриці
// // Використання перспективної проекції з
// // параметрами fovy = 45, aspect, zNear = 0.1 та zFar = 100
// gluPerspective(45.0f, aspect, 0.1f, 100.0f);
//}


int main(int argc, char **argv){
    srand(time(0));
    aTree = getIntTreeWithRandValues(amount, 0);
    aList = CreateIntList();

    //Initialization
    glutInit(&argc, argv);
    width = glutGet(GLUT_SCREEN_WIDTH) ;
    height = glutGet(GLUT_SCREEN_HEIGHT) *0.91;
    printf("w = %d, h = %d", width, height);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("Binary_Tree");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    glutTimerFunc(500, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    //glutReshapeFunc(Reshape);
    glutMainLoop();

    destroyIntTree(aTree);
    DestroyIntList(aList);
    return 0;
}
