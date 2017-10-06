#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

//Snake
typedef struct _tagSnake
{
    //snake characters
    int speed;
    int total;
    int lives;
    int backDir;// for tail jump in a head(optimal way)
    int *body;
}snake;

//another "objects"
typedef struct _tagObject
{
    int x_pos;
    int y_pos;
    int value;
}object;

//it's for the class "Snake"
snake *createSnake(int startPosition);
void snakeGrow(snake *aSnake);
void snakeUpdate(snake *aSnake);
void snakeDeath(snake *aSnake, object *cells);
void snakeChangeDir(snake *aSnake, int x);
void snakeDraw (snake *aSnake);
int  snakeBodyIndex(snake *aSnake, int aValue);
void snakeEat(snake *aSnake, object *aFood);
void snakeFree(snake *aSnake);

// helping functions
int moveIntoSpeed(char move);
int correctPos(int *aHeadPos, int speed);
char currentDir(snake *aSnake);
char opposite(char key);
#endif // SNAKE_H_INCLUDED
