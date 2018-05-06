//**********************************
// SNAKE
//**********************************
//
//Created by Bramory 10.06.17
//
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>

#include "snake.h"
#include "game_tools.h"
#include "keyboard.h"
#include "AI_PLAY.h"
#include "const.h"

int N = 10; //amount of cells on a one side
int scl = 30;
int AI_STATE = 1; // on AI
int interfaceState = 1; //off console info
int Debug = 0;
int LIVES = 3;
int MODE = 0; // default difficult

//for simulate inside simulating
int DeepMind = 1;

void Initialize (float r, float g, float b){
    glClearColor(r, g, b, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}

void display(){
    //clean screen buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //pause = 50;
    char key;
    //key = perfectSnake(aRealSnake, cells, aFood);
    if (AI_STATE == 1){
            key = AI_PLAY(aRealSnake, cells, aFood);
    }
        Simulation = 0;
    if (interfaceState == 1)
        interface(aRealSnake, aFood );

     //processing
    snakeUpdate(aRealSnake);
    glColor3f(0,0,0); // for the head
    snakeDeath(aRealSnake, cells);

    if (aRealSnake->lives <= 0){
    //system("pause");
    GameOver();
    }
    snakeEat(aRealSnake, aFood);  // ? at this moment, where is a food?
            effects(aRealSnake, aFood, difficulty); // for random mode
    cellsUpdate(aRealSnake, cells);  // for detect a snake-circle

    //drawing
    glColor3f(r + 0.3, g + 0.3, b + 0.3);
    snakeDraw(aRealSnake);
    drawFood(aFood);
    drawNet();
    if (Debug)
        drawCells(cells); // debug
   if (triggerShield)
       drawShield(aShield);

    feature(aRealSnake, cells, aFood); //for repeating moves
    glutSwapBuffers();
}


void timer(int a){
    glutPostRedisplay();
    glutTimerFunc(pause, timer, 0);
}

int main(int argc, char **argv){
    srand(time(0)); //?
    start_game();
    start_time = clock();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("SnakE");

    //Registration
    glutDisplayFunc(display);
    Initialize(r,g,b);
    glutKeyboardFunc(Keyboard);
//    glutSpecialFunc(SKeyboard);
//    glutIdleFunc(MyIdle);
    glutTimerFunc(500, timer, 0);
//    glutMouseFunc(MousePressed);
//    glutPassiveMotionFunc(MouseMove);
//    glutMotionFunc(MousePressedMove);
//    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}
