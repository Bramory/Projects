#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

#include "draw.h"


// root - left - right
void DrawTree(TreeNode *aNode, int direct, void(*func)(TreeNode *, int) ){
	func(aNode, direct);

	if(aNode->leftChild != NULL)    {
        DrawTree(aNode->leftChild, -1, func );
    }
    //give left up point of the figure
	if(aNode->rightChild != NULL)    {
        DrawTree(aNode->rightChild, 1, func );
    }
}


void drawTreeLine(TreeNode *aNode, int direct){
    //Levels for visualizing == 6
    if (aNode->level > MAX_DEPTH || NULL == aNode)
        return;

    int x = getNodePos_X(aTree, aNode);
    int y = getNodePos_Y(aTree, aNode);

    //tree lines
    if (direct == -1 || direct == 1)    {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        // move from the left up corner
        // to point in the center of the current element
        glVertex2f( x + SizeOfSquare/2, y + SizeOfSquare/2);

        // draw line in the center of the previous element
        glVertex2f( x - (width/(2 << aNode->level ))*direct + SizeOfSquare/2, y-deltaY + SizeOfSquare/2 );
        glEnd();
    }
}

void drawCircle(float x, float y, float r, int amountSegments){
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < amountSegments; i++){
        float angle = 2.0 * 3.1415926 * (float)(i) / (float)amountSegments;
        float dx = r * cosf(angle);
        float dy = r * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawTreeNode(TreeNode *aNode, int direct ){
    //Levels for visualizing == 6
    if (aNode->level > MAX_DEPTH || NULL == aNode)
        return;

    int x = getNodePos_X(aTree, aNode);
    int y = getNodePos_Y(aTree, aNode);

    //Print Shape
    if (aNode->mark == 1)
        glColor3f(0.1, 0.1, 0.8); //marked
    else
        glColor3f(1, 1, 0); //non-marked

//    glBegin(GL_QUADS);
//    glVertex2f(x, y);
//    glVertex2f(x+SizeOfSquare, y);
//    glVertex2f(x+SizeOfSquare, y+SizeOfSquare);
//    glVertex2f(x, y + SizeOfSquare);
//    glEnd();

    drawCircle( x+SizeOfSquare/2, y+SizeOfSquare/2, 17, 12);

//    Print Information (digits)
    char *string = (char*)malloc(sizeof(char)*10);

    itoa (aNode->value, string, 10);
    glColor3f(0, 0, 0);
    renderBitmapString(x + SizeOfSquare/2 - 1,
                       y + SizeOfSquare/2 + 4,
                       GLUT_BITMAP_9_BY_15,
                       string);
    free(string);
}

void renderBitmapString(float x, float y, void *font, char *string){
  char *c;
  int aLength = strlen(string);
  for (int i = 0; i < aLength; i++)  {
        x -= 4; //for every digit
  }

  glRasterPos2f(x, y);
  for (c = string; *c != '\0'; c++)    {
        glutBitmapCharacter(font, *c);
    }
}





// like in the Paint
void Drawing(int x, int y, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
