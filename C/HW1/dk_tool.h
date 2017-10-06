#ifndef dk_tool_h
#define dk_tool_h

/*
Return number what you type and ignore another symbols (non-digit).  
*/
int num_scan( void );

/*
Make transp_matrix from original matrix 
*/
void transp(int x, int y, int transp_matr[y][x], int matr[x][y]);

/*
Get the numbers into the matrix 
*/
void read_matr(int x, int y, int matr[x][y]);

/*
Show matrix on the screen 
*/
void print_matr(int x, int y, int matr[x][y]);

#endif


