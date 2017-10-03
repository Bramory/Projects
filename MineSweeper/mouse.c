#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tool.h"
#include "draw.h"
#include "mouse.h"

int N;
int game_state;
int mines;
int x;
int y;
int width;
int height;
int sleep;
field *aField;

#define GAMEOVER -1
#define WIN 1

void MousePressed(int button, int state, int x, int y)
{
    bool down = false;
    int check;
    if (state == down )
    {
        system("cls");
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                //glutSetWindowTitle("LeftButtonPressed");
                check = openCell(x, y, aField);
                if(-1 == check)
                {
                    game_state = GAMEOVER;
                }
                updateField(aField, check); //open border zeros
                check = checkFree(aField);
                if (check == N*N - mines)
                {
                    game_state = WIN;
                }

                break;

            case GLUT_MIDDLE_BUTTON:
                //glutSetWindowTitle("MiddleButtonPressed");

                break;

            case GLUT_RIGHT_BUTTON:
                //glutSetWindowTitle("RightButtonPressed");
                markCell(x, y, aField);

                break;
        }
    }
}


void MouseMove(int ax, int ay)
{
    //glutSetWindowTitle("MouseMove");
    x = ax;
    y = ay;
//    printf("X = %d\n", x);
//    printf("Y = %d\n", y);
    Sleep(sleep);
}

//
//void MousePressedMove(int ax, int ay)
//{
//    x = ax;
//    y = ay;
//    //glutSetWindowTitle("MousePressedMove");
//}
