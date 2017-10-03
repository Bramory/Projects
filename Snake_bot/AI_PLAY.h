#ifndef AI_PLAY_H_INCLUDED
#define AI_PLAY_H_INCLUDED

char AI_PLAY(snake *aSnake, object *cells, object *aFood);

// for the best results make heuristic steps
char perfectSnake(snake *aSnake, object *cells, object *aFood);

//simple algorithm for searching the shortest way
char shortestWay_Y(snake *aSnake, object *aFood);
char shortestWay_X(snake *aSnake, object *aFood);

//changing way and detecting a pregradu
int checkDir (snake *aSnake, object *cells);
char changeDir(snake *aSnake, object *cells, int currentDir);
int checkACircle(snake *aSnake, object *cells, object *aFood);

int makeClone(snake *aSrcSnake, snake *aDstSnake);

//for repeated moves
 void feature(snake *aSnake, object * cells,  object *aFood);
#endif // AI_PLAY_H_INCLUDED
