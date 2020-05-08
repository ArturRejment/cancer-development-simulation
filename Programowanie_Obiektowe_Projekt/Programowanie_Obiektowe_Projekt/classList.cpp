#include<iostream>
#include<time.h>
#include<cstdlib>
#include"classList.h"
using namespace std;


Map::Map(int size, int strong, int medium, int weak, int space)
{
	map = new Field[size];
	startingStrongCell = strong;
	startingMediumCell = medium;
	startingWeakCell = weak;
	spaceBetweenHealing = space;

	cout << map;
}

Field::Field()
{
	bonus_pointer = NULL;
	cell_pointer = NULL;
}

/*
Cell_strong::Cell_strong()
{
	hp = 500;
	divide_ratio = 8;
	position = setPosition();
}

Cell_medium::Cell_medium()
{
	hp = 300;
	divide_ratio = 5;
	position = setPosition();
}

Cell_weak::Cell_weak()
{
	hp = 150;
	divide_ratio = 3;
	position = setPosition();
}

*/