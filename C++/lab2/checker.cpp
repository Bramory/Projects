#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include "checker.h"
#include "const.h"
#include "draw.h"
using namespace std;

int Checker::getCount()const{
   return amount;
}

int Checker::getIndex()const{
   return index;
}

void Checker::setIndex(int num){
    this->index = num;
}


Checker::~Checker(){
    //dtor
}

void Checker::draw(void){
    chooseColor(this);
    int x0 = x * CELL_WIDTH  + CELL_WIDTH/2;
    int y0 = y * CELL_HEIGHT + CELL_HEIGHT/2;
    int r = CELL_WIDTH*2/5; //radius
    drawCircle( x0, y0, r,  15);
}

void Checker::Hit(char dir){
    this->makeStep(dir);
    for (int i = 0; i < this->getCount(); i ++){
        if (  check[i].get_x() == this->get_x() &&
              check[i].get_y() == this->get_y() &&
              i != this->getIndex() -1 ) //not origin checker
        {
            check[i].setIndex(-1); //in global array mark dead-checker
            cout << "HIT!" << endl;
            this->makeStep(dir);
            break; //all done
        }
    }
}

void King::draw(void){
    chooseColor(this);
    int x0 = x * CELL_WIDTH  + CELL_WIDTH/2; // center of the cell
    int y0 = y * CELL_HEIGHT + CELL_HEIGHT/2;
    int r = CELL_WIDTH*2/5; //radius
    glColor3f(1, 0, 0);
    //drawCircle( x0, y0, r,  15);

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x0-10, y0-10);
    glVertex2f(x0, y0-20);
    glVertex2f(x0+10, y0-10);
    glVertex2f(x0+10, y0+10);
    glVertex2f(x0-10, y0+10);
    glEnd();


}

King::~King(){
    //dtor
}
