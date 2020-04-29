#include<iostream>
#include "classList.h"
using namespace std;

Map::Map()
{
	cout << "Enter width and height of the map:" << endl;	
	cout << "width = "; cin >> width;
	cout << "height = "; cin >> height;
	cout << "Enter the interval of giving drugs (in iteratoin): ";
	cin >> spaceBetweenHealing;
	cout << "Enter the max amount of iterations: ";
	cin >> maxIterations;
	cout << "Enter the amount of cells: " << endl;
	cout << "Strong = "; cin >> startingStrongCell;
	cout << "Medium = "; cin >> startingMediumCell;
	cout << "Weak = "; cin >> startingWeakCell;

	
}

void Map::isFreeFunction(int x, int y)
{
	if ();
}

void Drug_strong::healing(){

}

Bonus::Bonus()
{
	bool isFree;

	do
	{

	} while (isFree == false);
}