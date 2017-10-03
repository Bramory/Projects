#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "snake.h"
#include "game_tools.h"
#include "keyboard.h"
#include "const.h"

//window parameters
int width;
int height;
int x_position = 800;
int y_position = 100;

//snake constants
snake *aRealSnake;
object *aFood;
object *cells;
object *aShield;
int moveCounter = 0;
//legal
char* l_moves;

//game settings
int difficulty;
int MAX_SNAKE_LEN;
float score = 0;
float award = 0;
int pause;

//triggers
int triggerShield = 0;
int aRecordLength = 0;
int aStepsWithoutFood = 1;
int aRecordWithoutFood = 0;
int aFruitsEaten = 0;
int Simulation = 0;
float start_time;

float r;
float g;
float b;


void interface(snake *aSnake, object *aFood ){
    if (aSnake == NULL || aFood == NULL )
        return;

    system("cls");
    if (pause)
        printf("FPS: %.0f\n", 1000.0/pause);

    printf("Your Lives: %d\n", aSnake->lives);
    printf("Your Score: %.1f\n", score);
    printf("ALL_Moves: %d\n", moveCounter);
    printf("Your Length: %d\n",aSnake->total);
    printf("currentDir: %c\n", currentDir(aSnake));
    printf("aSnake->backDir: %c\n", opposite(currentDir(aSnake)) );
    if (AI_STATE == 1)
        printf("\tAI_ON");
    //printf("Mode: %d\n", difficulty);
    //printf("Your Award: %.0f\n", award);
    //printf("N: %d\n", N);
    //printf("SCL: %d\n", scl);
    //printf("pause: %.0d\n", pause);
}

void renderBitmapString(float x, float y, void *font, char *string){
    char *c;
    int aLength = strlen(string);
    int i;
    for (i = 0; i < aLength; i++){
        x -= 4; //for every char
    }
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}

//find out optimal way to do it
void cellsUpdate(snake *aSnake, object *cells){
    if (NULL == aSnake || NULL == cells)
        return;

    int in;
    for(int j = 0; j < N*N; j++){
        cells[j].value = 0;    //memset??
        if(Debug)
            cells[j].value = j;
    }

    // mark if the snake in it for detection a circle
    for(int i = 0; i < aSnake->total; i++)
    {
        in = aSnake->body[i];
        cells[in].value = N*N;
//        printf("\nbackDir = (%c|%d)\n", aSnake->backDir);
//        system("pause");
//
//        in = aSnake->body[aSnake->total-1] + aSnake->backDir;
//        cells[in].value = 0;//already yet
    }
}

void drawCells(object *cells){
    if (NULL == cells )
        return;

    glColor3f(0,0,0);
    int in = aRealSnake->body[0];
        renderBitmapString(cells[in].x_pos +scl/2, cells[in].y_pos+scl/2,
                           GLUT_BITMAP_HELVETICA_12, "HEAD");
    int buffer = 5;
    char *str = (char*)malloc(sizeof(char) * buffer);
    for(int i = 0; i < N*N; i++)
    {
        //memset(str, 0, sizeof(str)); //mb itoa already do it?
        itoa(cells[i].value, str, 10);

        glColor3f(1,0,0);
        renderBitmapString(cells[i].x_pos +scl/2, cells[i].y_pos+scl/2,
                           GLUT_BITMAP_9_BY_15, str); //"0" + cells[i].value
    }
     free(str);
        //put outside "}"
}

void setCells(object *cells){
    if (NULL == cells)
        return;

    for(int i = 0; i < N; i++){
         for(int j = 0; j < N; j++){
             //empty cell
            int in = j*N + i;
            cells[in].x_pos = i * scl % width;
            cells[in].y_pos = j * scl % height;
        }
    }
}

void drawShield(object *aShield){
    if (NULL == aShield)
        return;
    glColor3f(1, 0, 1);
    glRecti(aShield->x_pos, aShield->y_pos,
            aShield->x_pos + aShield->value * scl, aShield->y_pos + aShield->value * scl);
}

void setShield(object *aShield){
    if (NULL == aShield)
        return;
    aShield->x_pos = randomIntFromRange(0, width/scl - 1) * scl;
    aShield->y_pos = randomIntFromRange(0, height/scl - 1)* scl;
    aShield->value = randomIntFromRange(1, N/2);
}

void setFood (snake *aSnake, object *aFood){
    if (aSnake == NULL || aFood == NULL ){
        printf("\nSET_FOOD :: false\n");
        return;
    }

    if (aSnake->total >= N*N){
        //system("cls");
        printf("\n\n\n\n\n \n");
        printf("\t\t\t Perfect-Snake \n");
        //system("pause");
        return;
        //exit(123);
    }
    int in;
    //renew location
start:
     in = randomIntFromRange(0, N*N - 1);
    //food inside aSnake->body
    if (cells[in].value == N*N)
        goto start;

    aFood->value = in;
}

void drawFood (object *aFood){
    if(NULL == aFood)
    {
        printf("Fruit is not set!");
        return;
    }
    glColor3f(1, 0, 1);
    int in = aFood->value;
    glRecti(cells[in].x_pos    , cells[in].y_pos,
            cells[in].x_pos+scl, cells[in].y_pos+scl);
}

//return numbers from [a ... b]
int randomIntFromRange (int min, int max){
    if (min <= INT_MIN || max >= INT_MAX)
        return INT_MAX;

    return rand() % (max-min+1) + min;
}

int num_scan( void ){
	int num = 0, proof = 0;
    do
    {
        proof = scanf("%d", &num);
        if(proof == 1) break;
        printf("Incorrect input, try again");
        fflush(stdin);
    }
    while (1);
return num;
}


void drawNet(void){
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    for(int i = 1; i <= width/scl; i ++)
    {
        glVertex2f(i * scl, 0 );
        glVertex2f(i * scl, height );
    }

    for(int i = 1; i <= width/scl; i ++)
    {
        glVertex2f(0, i * scl);
        glVertex2f(width, i * scl);
    }
    glEnd();
}


 void start_game(void){
    MAX_SNAKE_LEN = N*N + 2;//?
    aRealSnake  = createSnake(0);//randomIntFromRange(0, N*N-1)); //?
    aRealSnake->lives = LIVES;
    aFood   = (object *)malloc(sizeof(object) );
    aShield = (object *)malloc(sizeof(object) );
    cells   = (object *)malloc(sizeof(object)*MAX_SNAKE_LEN);

    l_moves = (char*)malloc(sizeof(char) * 4);
    l_moves[0] = 'w';
    l_moves[1] = 'd';
    l_moves[2] = 's';
    l_moves[3] = 'a';

    r = rand() % 100 / 100.0;
    g = rand() % 100 / 100.0;
    b = rand() % 100 / 100.0;

    do
    {
        system("cls");
        printf("Choose difficulty:\n");
        printf("1.Novice\n");
        printf("2.Expert\n");
        printf("3.Pro-mode\n");
        printf("4.Hardcore-mode\n");
        printf("5._GODDAMN_\n");
        printf("6.+=random=+\n");
        if (!MODE)
            difficulty = num_scan();
        else
            difficulty = MODE;
    }
    while (difficulty <= 0 || difficulty > 6);

    pause = (float) 180 / difficulty;
    award = 36;
    width  = N*scl;
    height = N*scl;
    setFood(aRealSnake, aFood);
    setCells(cells);
 }

 // fun =)
 void effects(snake *aSnake, object *aFood, int diff){
     //for "random" difficulty
     if (diff != 6)
         return;

    //give an extra life for every 1000 steps
    if (moveCounter % 1000 == 0)
        aSnake->lives ++;

    //% chance for "SHIT_HAPPENS"
    int percent = 5;
    if ( rand() % 100 >= percent)
        return;

    AGAIN:{
         int effect = rand() % 10;
    //     effect = 6; //debug effects
         switch (effect)
         {
            //nothing to do
            case 0:
                break;

            //add length
            case 1:
                effect = randomIntFromRange(1, (N*N - aSnake->total)/4);
                if(aSnake->total + effect > MAX_SNAKE_LEN/2)
                    goto AGAIN;

                for(int i = 0; i < effect; i ++)
                    snakeGrow(aSnake);
                break;

            //change FPS (gameSpeed)
            case 2:
                effect = randomIntFromRange(-1, 1) * 40;
                if (pause + effect > 170 || pause + effect < 20 || effect == 0)
                    goto AGAIN;

                pause += effect;
                break;

            //Shield on the screen
            case 3:
                effect = rand() % 2;
                triggerShield = effect; // ON/OFF

                if (triggerShield)
                    setShield(aShield);
                break;

            //change coordinates N*N square
            case 4:
//                effect = randomIntFromRange(-2, 2);
//
//                if ( (N <= 12 && effect < 0) || (N >= 25 && effect > 0) || effect == 0 )
//                    goto AGAIN;
//
//                MAX_SNAKE_LEN = N*N;
//                if ( aSnake->total >= MAX_SNAKE_LEN / 2)
//                    goto AGAIN;
//
//                N += effect;
//                width  = N*scl;
//                height = N*scl;
//                Initialize(r, g, b);
//                setCells(cells); //?
//                for(int i = 0; i < aSnake->total; i++){
//                    aSnake->body[i] = 0;
//                }
//
//                if(aFood->value > N*N)
//                    setFood(aSnake, aFood);
//                break;

            //change location for food
            case 5:
                setFood(aSnake, aFood);
                break;

            //
            case 6:

                break;

            case 7:

                break;

            //add award for "snakeEat Food"
            case 8:
                effect = randomIntFromRange(-3, 5);
                if (award + effect < 0 || effect == 0)
                    goto AGAIN;

                award += effect;
                break;

            //new random background
            case 9:
                r = rand() % 100 / 100.0;
                g = rand() % 100 / 100.0;
                b = rand() % 100 / 100.0;
                Initialize(r, g, b);
                break;
         }
    }
 }

void sound(int msec){
    printf("\a");
    //Sleep(msec);
 }

 void GameOver(void) {
    system("cls");

    printf("\t\t\tGAME_OVER\n");
    printf("Your Score: %.1f\n", score);
    printf("All Moves: %d\n", moveCounter);
    printf("effectively %.1f\n", (float)score/moveCounter);
    printf("Fruits ate = %d\n", aFruitsEaten);
    printf("Steps/fruit = %.2f\n", aFruitsEaten == 0 ? 0 :(float) moveCounter/aFruitsEaten);
    printf("MaxLength = %d\n", aRecordLength);
    printf("averageLength = %.1f\n", (float)sumOfLength/LIVES );
    printf("NoFoodRecord = %d\n", aRecordWithoutFood);
    printf("PlayTime = %.2fs\n", (clock() - start_time)/1000.0 );

    glutSwapBuffers(); //? red background
    //memory free
    snakeFree(aRealSnake); //
    free(aShield);
    free(cells);
    system("pause");
    exit(0);
 }
