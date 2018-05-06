#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

typedef struct _tagCell
{
    int i;
    int j;

    int top;
    int right;
    int bottom;
    int left;

    int visited;
    int value;
}cell;

cell *checkNeighbors(cell *aCell);
int index (int i, int j);
void renderBitmapString(float x, float y, void *font, char *string);
void drawCell(cell *aCell);
void draw_net(void);
void highlight (int i, int j);

#endif // DRAW_H_INCLUDED
