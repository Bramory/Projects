#include "tools.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

//return numbers from [a ... b]
int randomIntFromRange (int min, int max)
{
    return rand() % (max-min+1) + min;
}

int num_scan( void )
{
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

void read_matr(int x, int y, int matr[x][y])
{
	int i, j;
	  for(i = 0; i < x ; i++)
    {
        for(j = 0; j < y ; j++)
        {
            matr[i][j] = num_scan();
        }
    }
}


void print_matr(int x, int y, int matr[x][y])
{
	int i, j;
    for(i = 0; i < x ; i++)
    {
        for(j = 0; j < y ; j++)
        {
            printf("%i ", matr[i][j]);
        }
        printf("\n");
    }
}

int fact(int number)
{
    int theResult = 1;
    while (number > 1)
    {
        theResult *= number;
        number--;
    }
    return theResult;
}

int read_filename( char* inputFile, int aSize)
{
	memset(inputFile, '\0', aSize * sizeof(char));
	int In = 0;
	char sym = 'a';
	while( 1 )
	{
			if (In >= aSize)
		{
			free(inputFile);
			return -5;
		}
		sym = getchar();
		printf("%c", sym);
		if (sym != 10)
		inputFile[In] = sym;
		else break;
		In++;
	}
	return 0;
}

char random_char (char min, char max)
{
    return rand() % (max-min+1) + min;
}

void print_array(int size, char srcArray[size])
{
	int i;
	for (i = 0; srcArray[i] != '\0'; i++)
		printf("%c", srcArray[i] );

	printf("\n");
}

void fillArrayChar(char min, char max, int size, char srcArray[size])
{
	memset(srcArray, '\0', sizeof(char) * size );
	int i;
	  for (i = 0; i < size; i++)
      srcArray[i] = random_char(min, max);
}

char *scan_text(int *aSize, char *filename)
{
	FILE *aFile = fopen (filename, "r");
	if (NULL != aFile)
	{
		int i = 0, c;
		char *ptrArray = (char *) malloc(sizeof(char) * *aSize);
		memset (ptrArray, '\0', sizeof(char) * *aSize);
		while (1)
		{
			if (*aSize <= i) //overflow
			{
				*aSize = -1;
				break;
			}
			if (c == EOF) break; //end of file
			c = fgetc(aFile);
			if ( isalpha(c) )
			{
				ptrArray[i] = c;
				i++;
			}
		}
		fflush(aFile);
		fclose (aFile);
		return ptrArray;
	}

}

int fileWrite(char *name_of_sort, int size, char srcArray[size])
{
	int i;
	char *filename = (char *)malloc (sizeof(char) * 200);
	char *path = (char *)malloc (sizeof(char) * 100);
	getcwd(path, 100);
	strcpy(filename, path );
	strcat(filename, "\\Sorted_Arrays\\");
	strcat(filename, name_of_sort);
	strcat(filename, ".txt");
	FILE *aFile = fopen(filename, "w");
	if (NULL != aFile)
	{
		for(i = 0; srcArray[i] != '\0'; i ++ )
		fprintf (aFile, "%c",  srcArray[i]);

		free(filename);
		free(path);
		fflush(aFile);
		fclose(aFile);
		return 0;
	}
	else
	{
		free(filename);
		free(path);
		printf("Couldn't create output file..\n");
		return -1;
	}
}

