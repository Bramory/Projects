#include <stdio.h>
#include <stdlib.h>

#include "snake.h"
#include "keyboard.h"
#include "game_tools.h"
#include "const.h"

int highLimit = 300;
int change = 10;
int lowLimit  = 5;

void Keyboard(unsigned char key, int x, int y){
    KeyPressed(aRealSnake, key);
    specialKeys(aRealSnake, key);

}

 char KeyPressed(snake *aSnake, unsigned char key){
    //if aSnake->total == 1 can turn in the back direction
    if (key != aSnake->backDir || aSnake->total == 1)
        switch (key){
            case 'w':
            //can't turn inside yourself
            snakeChangeDir(aSnake, -N);
        //    printf("W");
            break;

        case 'a':
            snakeChangeDir(aSnake, -1);
        //                printf("A");
            break;

        case 's':
            snakeChangeDir(aSnake, N);
         //printf("S");
            break;

        case 'd':
            snakeChangeDir(aSnake, 1);
//          printf("D");
            break;

//        default:
//            printf("\nDEFAULT: (%c||%d)", key, key);
//            break;
    }
return key;
}

char specialKeys(snake *aSnake, unsigned char key){
    switch (key){
        case 'b':
                r = rand() % 100 / 100.0;
                g = rand() % 100 / 100.0;
                b = rand() % 100 / 100.0;
                Initialize(r, g, b);
            break;

            break;
        case 'p':
            system("pause");
            break;

        case 'q':
            AI_STATE *= -1;
            printf(" 'q' => on/off AI_PLAY\n");
            break;

        case 'i':
            interfaceState *= -1;
            printf(" 'i' => on/off interface\n");
            break;

        case ',':

            if (pause+change < highLimit)
                pause += change;
            break;

        case '.':

            if (pause-change > lowLimit)
                pause -= change;
            break;

        case 'g':
                snakeGrow(aSnake);
            break;

        case '/':
            GameOver();
            break;

    }
return key;
}
