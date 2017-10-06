#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

void MarkIndexToDelete(int MultipleIndex, bool markFirst);
void renderBitmapString(float x, float y, void *font, char *string);
void drawCell(int x, int y, IntNode *aNode );
void display();


#endif // DRAW_H_INCLUDED
