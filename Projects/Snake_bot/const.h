#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

//#include <GL/glut.h>
//#include <stdio.h>
//#include <memory.h>
//#include <stdlib.h>
//#include <time.h>

//#include "snake.h"
//#include "AI_PLAY.h"
//#include "keyboard.h"
//#include "game_tools.h"

//window parameters
extern int width;
extern int height;
extern int x_position;
extern int y_position;

//snake constants
extern snake *aRealSnake;
extern object *aFood;
extern object *cells;
extern object *aShield;
extern int MAX_SNAKE_LEN;
extern int moveCounter;
extern char* l_moves; //legal

//game settings
extern int N;
extern int scl;
extern int difficulty;
extern float score;
extern float award;
extern int pause;

//triggers
extern int AI_STATE;
extern int interfaceState;
extern int triggerShield;
extern int LIVES;
extern int MODE;
extern int Debug;
extern int aStepsWithoutFood;
extern int aFruitsEaten;
extern int aRecordLength;
extern int aRecordWithoutFood;
extern int Simulation;
extern float start_time;
extern int sumOfLength;
int DeepMind;

extern float r;
extern float g;
extern float b;

#endif // CONST_H_INCLUDED
