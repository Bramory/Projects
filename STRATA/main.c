//**********************************
// Mnemo
//**********************************
//
//Created by Bramory 18.05.17
//

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

#include "List.h"
#include "keyboard.h"
#include "draw.h"
#include "mouse.h"

//window position
int N = 32;
int x_position = 900;
int y_position = 70;
int width;
int height;

//for random filling
int MIN_VALUE = 0;
int MAX_VALUE = 999;

//for mouse coordinate
int x = 0;
int y = 0;

//for objects
int rect_size = 10;

int min = 00;
int max = 99;
int buffer = 100;
char* string;
int RES;
int pause = 1300;

IntList *aList;
IntNode *aNode;


void Initialize ()
{
    glClearColor(1, 1, 0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glViewport(60, 60, 60, 60);
    glOrtho(0, width, height, 0, -1, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    x = width/2;
    y = height/2;
    Sleep(pause);
    if (pause < 900)
    {
        pause -= 2;
    }
    else
    {
        pause -= 10;
    }
//    x = randomIntFromRange(30, width - 30);
//    y = randomIntFromRange(30, height - 30);


    RES = randomIntFromRange(min, max);
    itoa(RES, string, 10);

    renderBitmapString(x, y, GLUT_BITMAP_TIMES_ROMAN_24, aNode->word);
   // renderBitmapString(x, y, GLUT_BITMAP_TIMES_ROMAN_24, string);
    aNode = aNode->next;
    glutSwapBuffers();
}

void MyIdle()
{
    display();
}


void readingWords(IntList *aList)
{
    //system("dir");
    char *path = (char*)malloc(sizeof(char) * 100);
    getcwd(path, 100);
    strcat(path, "\\1-1000.txt");
    printf("%s\n", path);

    FILE *aFile = fopen(path, "r");
    if (NULL == aFile)
    {
        printf("there is NO file");
         return;
    }
    else
    {
        printf("OPEN file\n\n\n");
    }
    printf("\nstart reading\n");


	char *aString = (char*) malloc(sizeof(char) * buffer);
    memset(aString, 0, buffer);

    char *word = "QWERTY";
	int c, wordCount = 0, i = 0;

	do
	{
        c = fgetc(aFile);
		if ( isalpha(c) )
		{
			aString[i] = c;
			i++;
            printf(aString);
            printf("\n");
		}
		else
		{
		    int length = strlen(aString);
//		    strcpy(word, aString);
            AddIntValueToList(aList, wordCount, word);
            memset(aString, 0, length);
            wordCount ++;
            i = 0;
		}

	}while ( c != EOF );


    free(aString);
    fclose(aFile);
}

int main(int argc, char **argv)
{
    string = (char*)malloc(sizeof(char)*buffer);
    srand(time(0));

    aList = CreateIntList();
    readingWords(aList);
    char* aWord = "WORD";
//    AddIntValueToList(aList, 0, "Hello");
    AddIntValueToList(aList, 0, aWord);
    aNode = aList->head;

    PrintList(aList);


    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    width = 300;//glutGet(GLUT_SCREEN_WIDTH);
    height = 300;//glutGet(GLUT_SCREEN_HEIGHT) * 0.91;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("STRATA");

    //Registration
    glutDisplayFunc(display);
    Initialize();
    //glutTimerFunc(500, timer, 0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MousePressed);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MousePressedMove);
    glutMainLoop();

    return 0;
}
