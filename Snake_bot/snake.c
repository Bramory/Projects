//
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "snake.h"
#include "game_tools.h"
#include "const.h"

int sumOfLength = 0;

snake *createSnake(int startPosition){
    if (startPosition < 0 || startPosition >= N*N){
        printf("\nstartPosition = false\n");
        return NULL;
    }

    snake *aSnake = (snake*)malloc(sizeof(snake));

    if (NULL == aSnake){
        printf("SNAKE_START");
        return NULL;
    }

    aSnake->body = (int*)malloc(sizeof(int) * MAX_SNAKE_LEN);
    //snake characters
    aSnake->speed = 1;
    aSnake->total = 1; // mb more?
    aSnake->lives = 1;
    aSnake->backDir = opposite(currentDir(aSnake)); //?
    //for(int i = 0; i < aSnake->total; i ++)
    aSnake->body[0] = startPosition;

    return aSnake;
}

//change direction for moving
void snakeChangeDir(snake *aSnake, int x){
    if (aSnake == NULL)
        return;

    aSnake->speed = x;
}

/*
void snakeUpdate(snake *aSnake){
     //horizontal
   if (aSnake->body[0].x_pos + aSnake->speed*scl < 0 || (aSnake->body[0].x_pos+scl)+aSnake->speed*scl > width)
    {
        aSnake->body[0].x_pos = aSnake->body[0].x_pos * N;
        aSnake->body[0].y_pos = aSnake->body[0].y_pos * N;
        //snakeChangeDir(aSnake, 0, 0);
        //snakeDeath(aSnake);
    }

    //vertical
    if (aSnake->body[0].y_pos + aSnake->speed*scl < 0 || (aSnake->body[0].y_pos+scl)+aSnake->speed*scl > height)
    {
        snakeChangeDir(aSnake, 0, 0);
        snakeDeath(aSnake);
    }

    for(int i = aSnake->total; i > 0; i--)
    {
        aSnake->body[i].x_pos = aSnake->body[i-1].x_pos;
        aSnake->body[i].y_pos = aSnake->body[i-1].y_pos;
    }

    //move the head
    aSnake->body[0].x_pos += aSnake->speed * scl;
    aSnake->body[0].y_pos += aSnake->speed * scl;
}
*/

int correctPos(int *aHeadPos, int speed){
    if (aHeadPos == NULL || speed == 0)
        return -1;

    if ( *aHeadPos % N == 0 && speed == 1 ){
        *aHeadPos -= N;
        return 0;
        //printf("right\n");
    }
    else
         if ( (*aHeadPos % N == N-1 && speed == -1) || (*aHeadPos == -1 && speed == -1) ){
            *aHeadPos += N;
            return 0;
            //printf("left\n");
        }
        else
             if ( *aHeadPos < 0){
                *aHeadPos += N*N;
                return 0;
                //printf("up\n");
            }
            else
                 if ( *aHeadPos >= N*N){
                    *aHeadPos -= N*N;
                    return 0;
                    //printf("down\n");
                }
    //didn't go throw a border
    return -1;
}

//change location
void snakeUpdate(snake *aSnake){
    if (NULL == aSnake)
        return;

    if (!Simulation)
        moveCounter++;
    //change location from the tail
    for(int i = aSnake->total; i > 0; i--){
        aSnake->body[i] = aSnake->body[i-1]; //or delete tail ?
    }
    //move head
    aSnake->body[0] += aSnake->speed;

    //make correction if require
    correctPos(&aSnake->body[0], aSnake->speed);
    aSnake->backDir = opposite(currentDir(aSnake)); //it is useful?
}

//visualizing
void snakeDraw (snake *aSnake){
    if (aSnake == NULL)
        return;

    //draw head
    int in = aSnake->body[0];
    glRecti(cells[in].x_pos    , cells[in].y_pos,
            cells[in].x_pos+scl, cells[in].y_pos+scl);
    //draw body
    glColor3f(1, 1, 0);
    for(int i = 1; i < aSnake->total; i++){
        in = aSnake->body[i];
        if (in >= 0 && in < N*N){
             glRecti(cells[in].x_pos, cells[in].y_pos,
                     cells[in].x_pos+scl, cells[in].y_pos+scl);
        }
    }
}

void snakeGrow(snake *aSnake){
    if (aSnake->total < MAX_SNAKE_LEN-1){ //?
        aSnake->total ++;
        aSnake->body[aSnake->total-1] = aSnake->body[aSnake->total-2];
        //hook on the tail
    }

}

void snakeEat(snake *aSnake, object *aFood){
    if (aSnake == NULL || aFood == NULL )
        return;

    if(aSnake->body[0] == aFood->value){
        aFruitsEaten ++;
        snakeGrow(aSnake);
        score += (float) award * aSnake->total;
        aStepsWithoutFood = 1;
        setFood(aSnake, aFood);
    }
    else
        if (!Simulation)
            aStepsWithoutFood ++;
}

void snakeDeath(snake *aSnake, object *cells){
    if (aSnake == NULL)
        return;

    if (aSnake->total > 4){
        //snake really bite yourself!
        if(cells[aSnake->body[0]].value == N*N){
            if (!Simulation ){
                // visual effect
                //draw the head
                int in = aSnake->body[0];
                glRecti(cells[in].x_pos, cells[in].y_pos,
                        cells[in].x_pos+scl, cells[in].y_pos+scl);
                //draw the body
                glColor3f(1,0,0);
                for(int i = 1; i < aSnake->total; i++){
                    in = aSnake->body[i];
                    glRecti(cells[in].x_pos, cells[in].y_pos,
                            cells[in].x_pos+scl, cells[in].y_pos+scl);
                }

                if (aSnake->total > aRecordLength)
                    aRecordLength = aSnake->total;

                sumOfLength += aSnake->total;
                aSnake->total = 1; //? what if total == 0
            }
            aSnake->lives --;
        }
    }
}

char opposite(char key){
    char antiKey;
    switch(key)
    {
        case 's':
            antiKey = 'w';
            break;

         case 'a':
            antiKey = 'd';
            break;

         case 'w':
            antiKey = 's';
            break;

        case 'd':
            antiKey = 'a';
            break;
    }
    return antiKey;
}

char currentDir(snake *aSnake){
    char currentDir;

    if ( aSnake->speed == -N )
        currentDir = 'w';

    if ( aSnake->speed == -1 )
        currentDir = 'a';

    if ( aSnake->speed == N )
        currentDir = 's';

    if ( aSnake->speed == 1 )
        currentDir = 'd';

    return currentDir;
}

int moveIntoSpeed(char move){
    int speed;

    if ( move == 'w' )
        speed = -N;

    if ( move == 'a' )
        speed = -1;

    if ( move == 's' )
        speed = N;

    if ( move == 'd' )
        speed = 1;

    return speed;
}

//return index of the snake
//otherwise -1
int snakeBodyIndex(snake *aSnake, int aValue){
    if (aValue < 0 || aValue >= N*N )
        return -1;

    for(int in = 0; in < aSnake->total; in++){
        if(aSnake->body[in] == aValue){
            return in;
        }
    }
    return -1;
}

void snakeFree(snake *aSnake){
    if (NULL != aSnake){
        if(NULL != aSnake->body)
            free(aSnake->body);

        free(aSnake);
    }
}
