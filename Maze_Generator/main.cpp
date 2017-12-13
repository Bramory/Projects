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
#include <windows.h> // for Sleep()

#include "keyboard.h"
#include "draw.h"
#include "mouse.h"
#include "const.h"

//window position
int x_position = 800;
int y_position = 100;
int width;
int height;

//for mouse coordinate
int x = 0;
int y = 0;

//size of the square
int w = 40;

//for objects
int N = 10;
int cols;
int rows;
int pause = 1000;

int MIN_VALUE;
int MAX_VALUE;

cell *stack;
cell *cells;
cell *current;

void Initialize (){
    glClearColor(0,0,0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void removeWalls(cell *a, cell *b){
     //left-right parts
    int x = a->j - b->j;
//    printf("a->i = %d\n", a->i);
//    printf("a->j = %d\n", a->j);
//    printf("b->i = %d\n", b->i);
//    printf("b->j = %d\n", b->j);
//    system("pause");
    if (x == -1){
        a->right = 0;
        b->left = 0;
    }
    else
        if (x == 1){
            a->left = 0;
            b->right = 0;
        }

    //top-bottom parts
    int y = a->i - b->i;
    if (y == 1){
        a->top = 0;
        b->bottom = 0;
    }
    else
        if (y == -1){
            a->bottom = 0;
            b->top = 0;
        }
}

void highlight (cell *aCell){
    int x = aCell->i * w;
    int y = aCell->j * w;

    glColor3f(1,0,1);
    glRecti(x,y,
           x+w, y+w);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < N*N; i++ )
        drawCell(&cells[i]);


    highlight(current);
    //Step 1
    cell *next = checkNeighbors(current);

    // have neighbors
    if (next){
        //Step 2

        //Step 3
        removeWalls(current, next);

        //Step 4
        cells[index(current->i, current->j)].visited = 1;
        current = next;
//        printf("current #%d\n", current->value);
//        printf("visited #%d\n", current->visited);
    }
    else{

    }
    glutSwapBuffers();
}

void timer(int a){
    glutPostRedisplay();
    glutTimerFunc(pause, timer, 0);
}

void MyIdle(){
    display();
    Sleep(pause);
}

int main(int argc, char **argv){
    srand(time(0));

    width  = 400;//glutGet(GLUT_SCREEN_WIDTH);
    height = 400;//glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    cols = width/w;
    rows = height/w;
    printf("cols = %d\n", cols);
    printf("rows = %d\n", rows);
    cells = (cell*)malloc(sizeof(cell)* (N*N));

    //Initializing cells with 4 walls
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

    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("MAZE");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    glutTimerFunc(pause, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutTimerFunc(200, timer, 0);
    glutMainLoop();

    return 0;
}
