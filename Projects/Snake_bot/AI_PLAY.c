#include <GL/glut.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "snake.h"
#include "game_tools.h"
#include "AI_PLAY.h"
#include "keyboard.h"
#include "const.h"

char AI_PLAY(snake *aSnake, object *cells, object *aFood){
     if (NULL == aSnake || NULL == aFood){
        printf("\nAI_PLAY = False\n");
        return 'G';
     }

    int key = -1;
    //  check danger with a circle
    if (!DeepMind){
        if (!Simulation)
            key = checkACircle(aSnake, cells, aFood);
    }
    else{
        key = checkACircle(aSnake, cells, aFood);
    }


    if ( key == -1  ){
        //find shortest way
        key = shortestWay_X(aSnake, aFood);
//        printf("SHORTEST_WAY\n");
    }
    else{
        if(Debug)
        printf("\nEscape from aCircle = (%c|%d)\n ", key, key);
        //system("pause");
    }
    KeyPressed(aSnake, key);
    //check this move and change if require
    if (-1 == checkDir(aSnake, cells)){
        //printf("\nChanGE\n");
        key = changeDir(aSnake, cells, key);
    }

    //accept legal move
    KeyPressed(aSnake, key);
    return key;
}

char shortestWay_X(snake *aSnake, object *aFood){
    char key = currentDir(aSnake);
    char oppositeDir = opposite(currentDir(aSnake));
    if (aSnake->body[0]%N < aFood->value%N){
        if ('d' != oppositeDir || aSnake->total == 1)
            key = 'd';
        else
             key = shortestWay_Y(aSnake, aFood);
    }
    else{
        if (aSnake->body[0]%N > aFood->value%N)
        {
            if ('a' != oppositeDir || aSnake->total == 1)
                key = 'a';
            else
                key = shortestWay_Y(aSnake, aFood);
        }
        else{
             if (aSnake->body[0]%N == aFood->value%N)
                key = shortestWay_Y(aSnake, aFood);
        }

    }
    return key;
}

char changeDir(snake *aSnake, object *cells, int currentDir){
    int i;
    for ( i = 0; i < 4; i++ ){ //?
        //find non oldWayToDeath
        if ( l_moves[i] != currentDir){
            //CHOOSE NEW_WAY
            KeyPressed(aSnake, l_moves[i]);
            if ( 0 == checkDir(aSnake, cells)){
//                printf("\ncurrentDir:  %c\n", currentDir);
//                printf("\nopposite  %c\n", oppositeDir);
//                if (!Simulation){ // debugger
//                    printf("\nFind solution:  %c\n", l_moves[i]);
//                    system("pause");
//                }

//                system("cls");
                return l_moves[i];
            }
//            else{
//               // printf("\nWrong sol :  %c\n", l_moves[i]);
//            }
        }
        //continue from the variant
    }
    //all 4 variants incorrect
    //printf("\nHARAKIRI!\n");
    //system("pause");
    return currentDir;
}

// optimal implementation for snake with cells
int checkDir (snake *aSnake, object *cells){
    //so long -> can bite yourself
    if (aSnake->total > 4){
        //make a possible step
        int placeForBite = aSnake->body[0] + aSnake->speed;
        correctPos(&placeForBite, aSnake->speed);

        if (cells[placeForBite].value == N*N){
            //need to change direct
            return -1;
        }
    }
    //safe move
    return 0;
}


int makeClone(snake *aSrcSnake, snake *aDstSnake){
    if (NULL == aSrcSnake || NULL == aDstSnake){
        printf("\nmakeClone = False\n");
        return -1;
    }

    //memset(aDstSnake->body, 0, sizeof(int) * MAX_SNAKE_LEN); //?

    aDstSnake->lives = 1;//aSrcSnake->lives;
    aDstSnake->total = aSrcSnake->total;
    aDstSnake->backDir = aSrcSnake->backDir;
    aDstSnake->speed = aSrcSnake->speed;
    for(int n = 0; n < aDstSnake->total; n ++){
        aDstSnake->body[n] = aSrcSnake->body[n];
    }
    return 0;
}


int checkACircle(snake *aSnake, object *cells, object *aFood){
    if (NULL == aSnake || NULL == aFood)
        return -1;

    //can turn into a Circle
    if (aSnake->total > 7 ){

     char curDir = currentDir(aSnake);
        if ( (aSnake->body[0] == 0)     ||
             (aSnake->body[0] == N-1)   ||
             (aSnake->body[0] == N*N-1) ||
             (aSnake->body[0] == N*(N-1)) ){
//                system("cls");
//                printf("\n \t\tnon-correct values!!\n");
//                printf("leftEdge = %d\n", leftEdge);
//                printf("rightEdge = %d\n", rightEdge);
//                printf("leftSpace = %d\n", leftSpace);
//                printf("strSpace = %d\n", strSpace);
//                printf("rightSpace = %d\n", rightSpace);
//                 printf("\n\ncurDir  (%d||%c)\n", curDir, curDir);
//                system("pause");
                return -1;
        }

        int leftEdge, rightEdge;
        int leftSpace, rightSpace, strSpace;
        int leftMove, rightMove;

        //modeling next step for a fake-snake (head)
        leftSpace = rightSpace = aSnake->body[0];
        leftEdge = rightEdge = strSpace = aSnake->body[0] + aSnake->speed;
        correctPos(&leftEdge, aSnake->speed);
        correctPos(&strSpace, aSnake->speed);
        correctPos(&rightEdge, aSnake->speed);

        //find direct with turn in 90 degrees in the right and his index
        int i = 0;
        while (i < 4){
            if (curDir == l_moves[i++]){
                i %= 4; //index for right turn move
                rightMove = l_moves[i];
                break;
            }
        }
        int correctStep = leftMove = opposite(l_moves[i]);// from the left a head

        int speed = moveIntoSpeed(leftMove);
        leftEdge += speed;
        leftSpace += speed;
        correctPos(&leftEdge, speed);
        correctPos(&leftSpace, speed);

        speed = moveIntoSpeed(rightMove);
        rightEdge += speed;
        rightSpace += speed;
        correctPos(&rightEdge, speed);
        correctPos(&rightSpace, speed);

        int spaces = 0;
        if (cells[leftSpace].value != N*N)
            spaces ++;
        if (cells[rightSpace].value != N*N)
            spaces ++;
        if (cells[strSpace].value != N*N)
            spaces ++;

        // circle a real danger
        if(cells[leftEdge].value == N*N && cells[rightEdge].value == N*N){
            if (spaces < 2)
                return -1;

            if (Debug){
                printf("\nDouble:\n");
            }
            goto SIMULATION;
        }

        if (cells[leftEdge].value == N*N && cells[leftSpace].value != N*N){
            if (Debug){
                printf("\nLeft:\n");
            }
            goto SIMULATION;
        }
        if(cells[rightEdge].value == N*N && cells[rightSpace].value != N*N){
            if (Debug){
                printf("\nRight:\n");
            }
            goto SIMULATION;
        }
        else{
            if (Debug){
                printf("\nNOTHING:\n");
            }
            return -1;
        }

    SIMULATION:
    {
        Simulation = 1;
        if (Debug){
            printf("\nSPACES = %d\n", spaces);
            printf("\nleftEdge   = %d\n", leftEdge);
            printf("rightEdge  = %d\n",  rightEdge);
            printf("left_space = %d\n",  leftSpace);
            printf("str_space = %d\n",  strSpace);
            printf("right_space = %d\n",  rightSpace);
            printf("\nleftEdgeMove  (%c|%d)", leftMove, leftMove);
            printf("\nrightEdgeMove  (%c|%d)\n", rightMove, rightMove);
            printf("\n\ncurDir  (%d||%c)\n", curDir, curDir);
            system("pause");
        }

        // choose which way is a longer
        object *cellsCopy = (object *)malloc(sizeof(object)*N*N);
        snake *aSnakeCopy = (snake*)malloc(sizeof(snake));
        if (NULL == aSnakeCopy){
            printf("\nTHERE is no aFake Snakes\n");
            return -1;
        }
        aSnakeCopy->body  = (int*)malloc(sizeof(int) * MAX_SNAKE_LEN);

        int max_steps = 0;
        for(int n = 0; n < 3; n++){
//          printf("Initialization START:\n");
            makeClone(aSnake, aSnakeCopy);
            setCells(cellsCopy); //?
            cellsUpdate(aSnakeCopy, cellsCopy);
            KeyPressed(aSnakeCopy, opposite(l_moves[i])); //from the left direct
            if (Debug){
                printf("\n\naSnake-direction (%d):\n", n);
                printf("body[0] = %d\n", aSnakeCopy->body[0]);
                printf("lives = %d\n", aSnakeCopy->lives);
                printf("total = %d\n", aSnakeCopy->total);
                printf("speed = %c\n", currentDir(aSnakeCopy));
                printf("opposite = %c\n\n\n", opposite(currentDir(aSnakeCopy)));
                printf("Initialization.\n");
                system("pause");
             }

            int currentSteps = 0;
            while(aSnakeCopy->lives > 0){
                snakeGrow(aSnakeCopy);
                snakeUpdate(aSnakeCopy);
                snakeDeath(aSnakeCopy, cellsCopy);
                cellsUpdate(aSnakeCopy, cellsCopy);

                //visualizing of simulation
//                 if (Debug){
//                    printf("\n\nSimulation %d", n);
//                    printf("\n\nsnake[%d]:\n", n);
//                    printf("body[0] = %d\n",0, aSnakeCopy->body[0]);
//                    printf("lives = %d\n", aSnakeCopy->lives);
//                    printf("total = %d\n", aSnakeCopy->total);
//                    printf("speed = %c\n", currentDir(aSnakeCopy));
//                    printf("\n\n\n\n\n\n\n");
//
//                    glClear(GL_COLOR_BUFFER_BIT);
//                    glColor3f(0, 0, 0); // for the head
//                    snakeDraw(aSnakeCopy);
//                    glutSwapBuffers();
//                    system("pause");
//                 }

                currentSteps++;
                if (currentSteps > (N*N-aRealSnake->total)/2){//?
                    snakeFree(aSnakeCopy);
                    if (Debug){
                        printf("\nFREE STEPS = %d\n", currentSteps);
                        printf("way = %c\n", opposite(l_moves[i]));
                    }
                    return opposite(l_moves[i]);
                }
                char key = AI_PLAY(aSnakeCopy, cellsCopy, aFood);
                 //if (Debug){
                    //printf("Move in simulation: (%c)\n", key);
//                    system("pause");
//                    system("cls");
                   // }
                }
//                 if (Debug)
//                printf("\n.........SNAKE[%d] is DEAD..........\n", n);

//              this way is longer => remember direction
            if (currentSteps > max_steps){
                max_steps = currentSteps;
                correctStep = opposite(l_moves[i]);
            }
            i = (i+1) % 4;
            currentSteps = 0; // simulate another way
        }
        free(cellsCopy);
        snakeFree(aSnakeCopy);
        if (Debug){
            printf("\ns Correct step = (%c) \n", correctStep);
            system("pause");
        }

            return correctStep;
    }

    } //amount control for making a circle
    return -1;
}

char shortestWay_Y(snake *aSnake, object *aFood){
    char key = currentDir(aSnake);
    char oppositeDir = opposite(currentDir(aSnake));

    if (aSnake->body[0]/N < aFood->value/N){
        if ('s' != oppositeDir || aSnake->total == 1)
            key = 's';
    }
    else{
         if (aSnake->body[0]/N > aFood->value/N){
            if ('w' != oppositeDir || aSnake->total == 1)
                key = 'w';
        }
    }
    return key;
}

char perfectSnake(snake *aSnake, object *cells, object *aFood){
//    if (aSnake->total >= 0.8*N){
//
//    }
    if(Debug)
    printf("\nTry\n");

    if (aSnake->body[0] % N == 0 && aSnake->speed == -1){
        KeyPressed(aSnake, 's');
        return 's';
    }
    else
        if (aSnake->body[0] % N == 0 && aSnake->speed == N){
            KeyPressed(aSnake, 'd');
            return 'd';
        }
        else
            if (aSnake->body[0] % N == N-1 && aSnake->speed == 1){
                KeyPressed(aSnake, 's');
                return 's';
            }
            else
                if (aSnake->body[0] % N == N-1 && aSnake->speed == N){
                    KeyPressed(aSnake, 'a');
                    return 'a';
                }
    return '\0';
}

void display();

 void feature(snake *aSnake, object * cells,  object *aFood){ //?
    if (NULL == aSnake || NULL == aFood){
        printf("\nAI_PLAY = False\n");
        return;
     }
    if (!Simulation)
    if (aStepsWithoutFood > aRecordWithoutFood)
        aRecordWithoutFood = aStepsWithoutFood;

    if (aStepsWithoutFood >= 1.1*N*N){
        printf("\nMOVES REPEATED %d steps\n", aStepsWithoutFood);
        //system("pause"); //?
        aStepsWithoutFood = 0;
        AI_STATE = 1;
    }
}
