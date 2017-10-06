#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "mouse.h"

#define CELL_WIDTH  (width/N)
#define CELL_HEIGHT (height/N)
int N;
int width;
int height;
int MAX_AMOUNT;
int x;
int y;


void mouse(int button, int state, int ax, int ay){
    x = ax;
    y = ay;
    //down = state == GLUT_LEFT_BUTTON;
}

void motion(int ax, int ay){
    x = ax;
    y = ay;
}
