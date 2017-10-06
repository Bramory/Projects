#ifndef _FIGURE_H_
#define _FIGURE_H_

class Figure{
	public:
		Figure (char x_, int y_, char* aColor); // constructor
		Figure (const Figure &);				// copy constr
		Figure ();								// default
		~Figure();								// destructor

		char getCoord_x() const; // print horizontal coordinate
		int  getCoord_y() const; // print  vertical  coordinate
		void setCoord_x(char);
		void setCoord_y(int);

		char* getColor() const;  // print chosen color
		void setColor(char*);

		void makeStep(char direct); // change figure's location
	private:
		char x;
		char y;
		char* color;
};

#endif // _FIGURE_H_
