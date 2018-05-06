#include <GL/glut.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "draw.h"
#include "const.h"


void renderBitmapString(float x, float y, void *font, char *string){
  char *c;
  int aLength = strlen(string);
  int i;
  for (i = 0; i < aLength; i++){
        x -= 4; //for every digit
  }
  glRasterPos2f(x, y);
  for (c = string; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}

void highlight (int i, int j){
    int x = i * w + w/2;
    int y = j * w + w/2;
    int r = w/2 - 2;
    int amountSegments = 16;

    glBegin(GL_TRIANGLE_FAN);
    for(int n = 0; n < amountSegments; n++){
        float angle = (float) 2.0 * 3.1415926 * (n) / amountSegments;
        float dx = r * cosf(angle);
        float dy = r * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawCell(cell *aCell){
    int x = aCell->i * w;
    int y = aCell->j * w;

    if(aCell->visited){
        glRecti(x, y,
                x + w, y + w);
    }


    glColor3f(1, 1, 0);

    ///show value inside cell
    //printf("%d value \n", aCell->value);

//    char *str =(char *)malloc(sizeof(char)*4);
//    itoa(aCell->value, str, 10);
//     renderBitmapString(x + w/2, y + w/2,
//                       GLUT_BITMAP_9_BY_15,
//                       str);
//    free(str);

    glBegin(GL_LINES);
    if (aCell->top){
        glVertex2f(x, y);
        glVertex2f(x + w, y);
    }

    if (aCell->right){
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + w);
    }

    if (aCell->bottom){
        glVertex2f(x + w, y + w);
        glVertex2f(x, y + w);
    }

    if (aCell->left){
        glVertex2f(x, y + w);
        glVertex2f(x, y);
    }
    glEnd();
}

///return numbers from [a ... b]
int randomIntFromRange (int min, int max){
    return rand() % (max-min+1) + min;
}

int index (int i, int j){
    if (i < 0      || j < 0 ||
        i > rows-1 || j > cols-1)
        return -1;

    return j * cols + i;
}

cell *checkNeighbors(cell *aCell){
    cell *neighbors = (cell*)malloc(sizeof(cell) * 4);

    cell *top    = &cells[index(aCell->i, aCell->j-1)];
    cell *right  = &cells[index(aCell->i+1,   aCell->j)];
    cell *bottom = &cells[index(aCell->i, aCell->j+1)];
    cell *left   = &cells[index(aCell->i-1,   aCell->j)];

    int i = 0;
    ///exist => index[0, N*N-1]
    if (top && !top->visited ){
        neighbors[i++] = *top;
    }
    if (right && !right->visited ){
        neighbors[i++] = *right;
    }
    if (bottom && !bottom->visited ){
        neighbors[i++] = *bottom;
    }
    if (left && !left->visited ){
        neighbors[i++] = *left;
    }
    //printf("amount of Neighbours: %d\n", i);

    if (i > 0){
        int r = randomIntFromRange(0, i-1);
//        printf("r = %d\n", r);
//        system("pause");
        return &neighbors[r];
    }
    else{
        free(neighbors);
        return NULL;
    }
}


void draw_net(void){

    glColor3f(1,0,0);
    glBegin(GL_LINES);

    int i;
    for(i = 0; i < cols; i ++){
        glVertex2f(i * w, 0 );
        glVertex2f(i * w, height );
    }

    for(i = 0; i < cols; i ++){
        glVertex2f(0,     i * w);
        glVertex2f(width, i * w);
    }
    glEnd();
}
