#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>
#include "figure.h"


class Checker : public Figure{
        static int amount;
        int index;
    public:
        //constructors
        Checker(int x_, int y_, char* aColor) : Figure(x_, y_, aColor), index(++amount){}
        Checker(): Figure(), index(++amount){}
        Checker(const Checker& src);
        virtual ~Checker();

//        void setCount(int );
		int getCount()const;
		int getIndex()const;
		void setIndex(int);
        void draw(void);
        void Hit(char);

        friend std::ostream & operator << (std::ostream &s, Checker &obj);
        friend std::istream & operator >>  (std::istream &s, Checker &obj);
        Checker& operator ++ (int);
        Checker& operator =(const Checker& right);
        Checker operator / (Checker const &rhs);
};
class King : public Checker{
        int index;
    public:
        King(char x, int y, char* aColor): Checker(x, y, aColor){}
        King() : Checker(){}
        virtual ~King();
        King(const King& other);
        void draw(void);
};


#endif // CHECKER_H
