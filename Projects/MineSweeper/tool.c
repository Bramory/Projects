#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tool.h"
#include "draw.h"

int N;
int width;
int height;
int SizeOfSquare;

void setMines(field *aField, int mines)
{
    if (NULL == aField)
        return;

	int i, j;
    while(mines > 0)
	{
		i = rand() % N;
		j = rand() % N ;
//		printf("i= %d\n", i);
//		printf("j = %d\n",j);
//		printf("N = %d\n",N);
//		printf("i*N + j = %d\n", i*N + j);
		if ( aField->cells[i*N + j].value == 0 )
		{
			aField->cells[i*N + j].value = -1;// set mine
			mines --;
		}
	}
}

//around mines
void setNum(field *aField)
{
	int i, j, mines = 0;

    for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			if (aField->cells[i*N + j].value != -1)
			{
				int n,m;
				for(n = i-1; n < i+2; n++)
				{
					for(m = j-1; m<j+2; m++)
					{
						if (m < 0)
							m++;
						if (n < 0)
							n++;

						if (m >= N)
						continue;
						if (n >= N )
						continue;

						if (aField->cells[n*N + m].value == -1)
						mines ++;
					}
				}
				aField->cells[i*N + j].value = mines;
				mines = 0;
			}
		}

	}

}

int updateField(field *aField, int theResult )
{
	int game_state;
	if(theResult == -1)
        game_state = -1;

    //open all nearest fields
	if( theResult == 0 )
	{
		int i, j, flag;
		do
		{
			flag = 0;
			for(i = 0; i < N; i++)
			{
				for(j = 0; j < N; j++)
				{
				    //open cell and zero value
					if (aField->cells[i*N+j].view == 1 &&
						aField->cells[i*N+j].value == 0 )
					{
						int n,m;
						for(n = i-1; n < i+2; n++)
						{
							for(m = j-1; m<j+2; m++)
							{
								if (m < 0)
									m++;
								if (n < 0)
									n++;

								if (m >= N)
									continue;
								if (n >= N )
									continue;

								if (aField->cells[n*N+m].view == 0)
								{
								    //repeat
									flag = 1;
									aField->cells[n*N+m].view = 1;//open
								}
							}
						}
					}
				}
			}
		}while(flag == 1);
	}
	return game_state;
}

int checkFree(field *aField )
{
	int i, j, open = 0;
	for(i = 0; i < N; i ++)
	{
		for(j = 0; j < N; j++)
		{
			if(aField->cells[i*N + j].view == 1)
			open ++;
		}
	}
    return open;
}

// -3 already open cell
// -2 error with parameters
// -1 game_over
// 0 excellent
int openCell (int x, int y, field *aField)
{
    if (NULL == aField)
        return -2;

    if (x<=0 || y<=0 ||
        x>=width || y>=height)
        return -2;

    cell *aCell = NULL;

    int x_pos = x/SizeOfSquare;
    int y_pos = y/SizeOfSquare;

//    system("cls");
//    printf("x = %d\n", x);
//    printf("y = %d\n", y);
//    printf("x_pos = %d\n", x_pos);
//    printf("y_pos = %d\n", y_pos);
//    printf("SizeOfSquare = %d\n", SizeOfSquare);
//    printf("Coordinate = %d\n", y_pos*N + x_pos);

    aCell = &aField->cells[y_pos*N + x_pos];
    if (aCell->view != 0)
        return -3;
    //             close
    if (aCell->view == 0)
    {//        to open
        aCell->view = 1;
    }
    if (aCell->value == -1)
    {
        return -1;
    }
    return 0;
}

int markCell(int x, int y, field *aField)
{
     if (NULL == aField)
        return -2;

    if (x<=0 || y<=0 ||
        x>=width || y>=height)
        return -2;

    int x_pos = x / SizeOfSquare;
    int y_pos = y / SizeOfSquare;

    cell *aCell = &aField->cells[y_pos*N + x_pos];
    if (aCell->view == 0)
        aCell->view = 2;
    else
    {
        if (aCell->view == 2)
            aCell->view = 0;
    }
    return 0;
}
