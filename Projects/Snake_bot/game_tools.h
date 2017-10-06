#ifndef GAME_TOOLS_H_INCLUDED
#define GAME_TOOLS_H_INCLUDED

//
void Initialize (float r, float g, float b);

//begin settings like:
//calculate width/height of the window
//create aSnake, set aFood, choose Color,
//setCells, choose a Scale for window
void  start_game (void);

void setCells(object *cells);
void setFood (snake *aSnake,object *aFood);
void setShield(object *aShield);

// show: score, lives to the player
void interface(snake *aSnake, object *aFood );
void cellsUpdate(snake *aSnake, object *cells);

//graphic functions
void drawShield(object *aShield);
void drawFood (object *aFood);
void drawCells(object *cells);
void drawNet(void);

//return numbers from [a ... b]
int randomIntFromRange (int min, int max);


//just for fun
void effects(snake *aSnake, object *aFood, int diff);

void sound(int msec);
void GameOver(void);
#endif // GAME_TOOLS_H_INCLUDED
