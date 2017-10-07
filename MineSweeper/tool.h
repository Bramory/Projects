#ifndef tool_h
#define tool_h

#include "draw.h"

void setMine( field *aField, int mines);
void setMines(field *aField, int mines);
void setNum(field *aField);
int openCell (int x, int y, field *aField);
int updateField(field *aField, int theResult );
int checkFree(field *aField );
int markCell(int x, int y, field *aField);

#endif


/*

*/
