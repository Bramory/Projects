#ifndef CHECKER_H
#define CHECKER_H

#include "figure.h"

class Checker : public Figure{
        static int amount;
        int index;
    public:
        Checker(int x_, int y_, char* aColor) : Figure(x_, y_, aColor), index(++amount){}
        Checker(): Figure(), index(++amount){}
        ~Checker();
        Checker(const Checker& src);
//        void setCount(int );
		int getCount()const;
		int getIndex()const;
		void setIndex(int);
        void draw(void);

        void Hit(char);
};


class King : public Checker{
        //static int amount;
        int index;
    public:
        King(char x, int y, char* aColor): Checker(x, y, aColor){}
        King() : Checker(){}
        ~King();
        King(const King& other);
        void draw(void);
};




#endif // CHECKER_H
