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
    --amount;
    delete [] color;
	cout << "Checker has been deleted." << endl;
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
    for (int i = 0; i < this->getCount(); i ++){ //test for unique location
        if (  check[i].get_x() == this->get_x() &&
              check[i].get_y() == this->get_y() &&
              i != this->getIndex() -1 ) //not the present checker
        {
            check[i].setIndex(-1); //in global array mark dead-checker
            cout << "HIT!" << endl;
            this->makeStep(dir); // jump over the checker
            break; //all done
        }
    }
}

//operators
ostream& operator << (ostream &s, Checker &obj){
    cout << "X = " << obj.get_x() << endl;
    cout << "Y = " << obj.get_y() << endl;
    cout << "Color = " << obj.getColor() << endl;
    cout << "Index = " << obj.getIndex() << endl;
    return s;
}

istream& operator >> (istream &s, Checker &obj){
    int x_, y_, index_;
    char* color_ = new char[10];// = new char[10];   ????
    cout << "Please, set parameters for checker:" << endl;
    cout << "X = ";
    cin >> x_;
    obj.set_x(x_);

    cout << "Y = ";
    cin >> y_;
    obj.set_y(y_);

//    cout << "Index = ";
//    cin >> index_;
//    obj.set_index(index_);
    cout << "Color = ";
    cin >> color_;
    obj.setColor(color_);

    cout << "END!"<< endl;
    return s;
}

Checker& Checker::operator =(const Checker& right){
    //self-assignment test
    if (this == &right) {
        return *this;
    }
    x = right.get_x();
    y = right.get_y();
    this->setColor(right.getColor());
    index = right.getIndex();
    return *this;
}

//Convert Checker -> King
Checker& Checker::operator ++ (int){
    King NewCrown;
    //cout << King << endl; ???
    Checker *ptr = &NewCrown;
    return *ptr;
}

//Checker Checker::operator / (Checker const &rhs){
//    return *this;
//}


//replacement function ??!!
void King::draw(void){
    chooseColor(this);
    int x0 = x * CELL_WIDTH  + CELL_WIDTH/2; // center of the cell
    int y0 = y * CELL_HEIGHT + CELL_HEIGHT/2;

    //glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x0-15, y0-10);
    glVertex2f(x0, y0-20);
    glVertex2f(x0+15, y0-10);
    glVertex2f(x0+10, y0+10);
    glVertex2f(x0-10, y0+10);
    glEnd();

    glColor3f(1, 1, 0);
    renderBitmapString(x0, y0, GLUT_BITMAP_HELVETICA_18, "KING");
}

King::~King(){
    //dtor
}
