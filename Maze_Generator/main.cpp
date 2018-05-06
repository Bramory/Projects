//**********************************
// MAZE_GENERATOR
//**********************************
//
//Created by Bramory 03.06.17
//

//Recursive backtracker
//Recursive backtracker on a hexagonal grid
//The depth-first search algorithm of maze generation is frequently implemented using backtracking:
//
//Make the initial cell the current cell and mark it as visited
//While there are unvisited cells
//If the current cell has any neighbours which have not been visited
//Choose randomly one of the unvisited neighbours
//Push the current cell to the stack
//Remove the wall between the current cell and the chosen cell
//Make the chosen cell the current cell and mark it as visited
//Else if stack is not empty
//Pop a cell from the stack
//Make it the current cell

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <windows.h> /// for Sleep()

#include "keyboard.h"
#include "draw.h"
#include "mouse.h"
#include "const.h"

using namespace std;

stack <cell> stack_;

cell *Me;


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    ///all work is done!
    //if(current->value == 0 && cells[index(rows-1, cols-1)].visited){
      for(int i = 0; i < rows*cols; i++ ){
                glColor3f(0.2, 0.2, 0.2);
                drawCell(&cells[i]);
            }
        glColor3f(1,0,1);
        highlight(current->i, current->j);

        glColor3f(0, 1, 1);
        highlight(Me->i, Me->j);
        //glutSwapBuffers();
    //}
    /// continue building...
    //else{
        ///Step 1
        cell *next = checkNeighbors(current);

        /// have neighbors
        if (next){
            ///Step 2
            stack_.push(*current);

            ///Step 3
            removeWalls(&cells[index(current->i, current->j)],
                        &cells[index(next->i   ,    next->j)]);

            ///Step 4
            current = next;
            cells[index(current->i, current->j)].visited = 1;
        }
        else
            if( !stack_.empty() ){
                current = &stack_.top();
                stack_.pop();
            }
        //}

/// for visualizing how it works
glutSwapBuffers();
}

void timer(int a){
    glutPostRedisplay();
    glutTimerFunc(pause, timer, 0);
}

//void MyIdle(){
//    display();
//    Sleep(pause);
//}

int main(int argc, char **argv){
    srand(time(0));

    width  = glutGet(GLUT_SCREEN_HEIGHT)*0.8;
    height = glutGet(GLUT_SCREEN_HEIGHT)*0.8;
    cols = width/w;
    rows = height/w;
    printf("cols = %d\n", cols);
    printf("rows = %d\n", rows);
    cells = (cell*)malloc(sizeof(cell)* (cols*rows));
    Me = (cell*)malloc(sizeof(cell)* 1);

    ///Initializing cells with 4 walls
    for(int i = 0; i < rows; i++ ){
        for(int j = 0; j < cols; j++ ){
            int in = j * cols + i;
            cells[in].i = i;
            cells[in].j = j;
            cells[in].top = 1;
            cells[in].right = 1;
            cells[in].bottom = 1;
            cells[in].left = 1;

            cells[in].visited = 0;
            cells[in].value = in;
        }
    }
    current = &cells[0];
    current->visited = 1;

    Me->i = 0;
    Me->j = 0;
    Me->value = 1;
    Me->visited = 1;

    ///Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("MAZE");

    ///Registration
    glutDisplayFunc(display);
    Initialize();
    glutTimerFunc(pause, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
//    glutIdleFunc(MyIdle);
//    glutMouseFunc(MousePressed);
//    glutPassiveMotionFunc(MouseMove);
//    glutMotionFunc(MousePressedMove);
    glutMainLoop();

    free(cells);
    return 0;
}
