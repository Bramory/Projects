#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

typedef struct _tagCell
{
    int x;
    int y;

}cell;

void renderBitmapString(float x, float y, void *font, char *string);

//return numbers from [a ... b]
int randomIntFromRange (int min, int max);
void drawPoint(cell *point);

#endif // DRAW_H_INCLUDED

