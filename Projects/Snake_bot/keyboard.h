#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

void Keyboard(unsigned char key, int x, int y);
char KeyPressed (snake *aSnake, unsigned char key);
char specialKeys(snake *aSnake, unsigned char key);
//for user input
int num_scan( void );
#endif // KEYBOARD_H_INCLUDED
