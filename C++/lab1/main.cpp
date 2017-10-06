#include <iostream>
#include <cstdlib>

#include "figure.h"
using namespace std;

int main(){
	Figure aFigure('B', 2, "Black");
	Figure zFigure[10];

	cout << "Color: " << aFigure.getColor() << endl;
	cout << "Coordinates: " << aFigure.getCoord_x() << aFigure.getCoord_y() << endl << endl;

    cout << "Color: " << zFigure.getColor() << endl;
	cout << "Coordinates: " << zFigure.getCoord_x() << zFigure.getCoord_y() << endl;

	int a;
    cin >> a;


	aFigure.setColor("White");
	aFigure.makeStep('u');
	cout << "\nchange color and make a step \n\n";

	cout << "Color: " << aFigure.getColor() << endl;
	cout << "Coordinates: " << aFigure.getCoord_x() << aFigure.getCoord_y() << endl;
	return 0;
}
