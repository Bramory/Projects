//**********************************
// MINESWEEPER
//**********************************
//
//Created by Bramory 19.05.17
//

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

#include "draw.h"
#include "tool.h"
#include "mouse.h"
#include "keyboard.h"


//Maximum amount of elements in a Tree
int N;

//window parameters
int width = 400;
int height = 400;
int x_position = 600;
int y_position = 0;
int SizeOfSquare;


// for graphics functions, MyIdle, etc...
int sleep = 10;
int game_state = 0;
int mines;
char temp;

//mouse
int x = 0;
int y = 0;

field *aField;


void Initialize ()
{
    glClearColor(1, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    switch(game_state)
    {
        case -1:
            gameOver();
            break;

        case 0:
            draw_field(aField);
            break;

        case 1:
            youWin();
            break;
    }
    glutSwapBuffers();
}

void MyIdle()
{
    display();
    Sleep(sleep);
    //glutSetWindowTitle("NothingToBeDone");
}



int main(int argc, char **argv)
{
    srand(time(0));

    printf("Welcome! Choose game field:\n");
	printf("(e)asy, (h)ard, (i)mpossible\n");
	do
	{
		temp = getch();
	}
	while(temp != 'e' && temp != 'h' && temp != 'i');

	switch(temp)
	{
		case 'e': N = 9; mines = 10; break;
		case 'h': N = 16; mines = 40; break;
		case 'i': N = 30; mines = 99; break;
	}

	SizeOfSquare = width/N;
    aField = (field*) malloc(sizeof(field));
    aField->cells = (cell*)malloc(sizeof(cell)* N*N);


    for (int i = 0; i < N*N; i++)
    {
        aField->cells[i].view = 0;
        aField->cells[i].value = 0;
    }

	setMines(aField, mines);
	setNum(aField);

	///////////////////////////////////////////////////////////////////////////
	//first click
//    while (1)
//    {
//        int i = rand() % N;
//        int j = rand() % N;
//        printf("i = %d\n", i);
//        printf("j = %d\n", j);
//        printf("value in the cell = %d\n", aField->cells[i*N + j].value);
//        if (aField->cells[i*N + j].value != -1)
//        {
//            int check = openCell(i*SizeOfSquare, j*SizeOfSquare, aField);
//            updateField(aField, check);
//            break;
//        }
//    }
    ///////////////////////////////////////////////////////////////////////////

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("MINESWEEPER");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
//    glutMotionFunc(MousePressedMove);
    glutMainLoop();
    return 0;
}
