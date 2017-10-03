#include <GL/glut.h>
#include <vector>
#include "draw.h"


void drawPoint(vector <point> &points)
{
    for(int i = 0; i < MAX_AMOUNT; i++)
    {
        glColor3f(r,g,b);
        glRectf(points[i].x_pos, points[i].y_pos,
                points[i].x_pos + rect_size, points[i].y_pos + rect_size);
    }
}
