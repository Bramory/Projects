#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

typedef struct __tagCell
{
    int value;
    int view;
}cell;

typedef struct __tagField
{
    cell *cells;
}field;

void draw_net(void);
void drawCell(int x, int y, cell *aCell );
void renderBitmapString(float x, float y, void *font, char *string);
void draw_field(field *aField );
void youWin(void);
void gameOver(void);


#endif // DRAW_H_INCLUDED
