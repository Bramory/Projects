#include <GL/glut.h>
#include <string.h>
#include <iostream>
#include "figure.h"
using namespace std;


//int Figure::getCount()const{
//   return count;
//}
//
//void Figure::setCount(int num){
//    count = num;
//}

Figure::Figure(int x_, int y_, char* aColor){
	x = x_;
	y = y_;
	color = new char [strlen(aColor) + 1];
	strcpy(color, aColor);
}

Figure::Figure(){
    x = 0;
    y = 0;
    color = "None";
	cout << "Figure has successfully created!" << endl;
}

Figure::Figure (const Figure &src){
    cout << "Copy constructor" << endl;
    x = src.x;
    y = src.y;
    color = new char[strlen(src.color) + 1]; //really
    strcpy(color, src.color);
}

Figure::~Figure(){
    delete [] color;
	cout << "Figure has been deleted." << endl;
}

int Figure::get_x()const{
	return x;
}

int Figure::get_y()const{
	return y;
}

char* Figure::getColor()const{
	return color;
}

void Figure::makeStep(char direct){
	if (direct == 'l'){
		y --;
		x --;
	}
	else
	if (direct == 'r'){
		y--;
		x++;
	}
}

void Figure::setColor(char* aColor){
    if (color) {
        delete [] color;
    }
	color = new char [strlen(aColor) + 1];
	strcpy(color, aColor);
}

void Figure::set_x(char newCoord){
	x = newCoord;
}

void Figure::set_y(int newCoord){
	y = newCoord;
}
