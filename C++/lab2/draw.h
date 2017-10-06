#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
//y#include "checker.h"
void renderBitmapString(float x, float y, void *font, char *string);
void drawBoard(void);
void drawCircle(float x, float y, float r, int amountSegments);
void chooseColor (Checker *Check);

#endif // DRAW_H_INCLUDED

