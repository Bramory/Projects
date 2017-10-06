#include <GL/glut.h>
#include <iostream>
#include "keyboard.h"
#include "checker.h"
#include "const.h"
using namespace std;

void Keyboard(unsigned char key, int x, int y){
    switch (key){
    case 'e':
        exit(0);
        break;
    }
}

void SKeyboard(int key, int x, int y){
    switch (key){

    case GLUT_KEY_LEFT:
        //    if (check[0].get_x() - 1  >= 'A' && check[0].get_y() - 1 >= 0 )
        check[0].Hit('l');
        cout << "LEFT" << endl;
        cout << "X = " << check[0].get_x() <<  endl;
        cout << "Y = " << check[0].get_y() <<  endl;
        cout << "INDEX = " << check[1].getIndex() <<  endl;
        break;

    case GLUT_KEY_RIGHT:
        //   if (check[0].get_x() + 1 >= 'H' && check[0].get_y() - 1 >= 7 )
        check[0].Hit('r');
//        cout << "RIGHT" << endl;
//        cout << "X = " << check[0].get_x() <<  endl;
//        cout << "Y = " << check[0].get_y() <<  endl;
//        cout << "INDEX 1 = " << check[1].getIndex() <<  endl;
//        cout << "INDEX 0 = " << check[0].getIndex() <<  endl;
        break;

    case GLUT_KEY_UP:
        break;

    case GLUT_KEY_DOWN:
        break;
    }
}
