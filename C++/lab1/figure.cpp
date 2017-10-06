#include <string.h>
#include <iostream>
#include "figure.h"
using namespace std;

Figure::Figure(char x_, int y_, char* aColor){
	x = x_;
	y = y_;
	color = new char [strlen(aColor) + 1];
	strcpy(color, aColor);
}

Figure::Figure(){
    x = 'F';
    y = 1;
    color = "nill";
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

char Figure::getCoord_x()const{
	return x;
}

int Figure::getCoord_y()const{
	return y;
}

char* Figure::getColor()const{
	return color;
}

void Figure::makeStep(char direct){
	if (direct == 'l'){
		y ++;
		x --;
	}
	else
	if (direct == 'r'){
		y++;
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

void Figure::setCoord_x(char newCoord){
	x = newCoord;
}

void Figure::setCoord_y(int newCoord){
	y = newCoord;
}
