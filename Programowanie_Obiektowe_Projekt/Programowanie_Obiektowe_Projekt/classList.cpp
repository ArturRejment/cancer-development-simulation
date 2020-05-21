#include<iostream>
#include<time.h>
#include<cstdlib>
#include"classList.h"
using namespace std;


////////////////// FIELD IMPLEMENTATION /////////////////////////
Field::Field()
{
	bonus_pointer = NULL;
	cell_pointer = NULL;
}

void Field::setCellPointer(Cell* newPointer)
{
	this->cell_pointer = newPointer;
}

void Field::setBonusPointer(Bonus* newPointer)
{
	this->bonus_pointer = newPointer;
}

////////////////// BONUS IMPLEMENTATION /////////////////////////

Bonus::Bonus(int position, bool setAttitude)
{
	this->position = position;
	this->attitude = setAttitude;
}



////////////////// CELL IMPLEMENTATION /////////////////////////

Cell_strong::Cell_strong(int hp, int position, int divide)
{
	this->hp = hp;
	this->position = position;
	divide_ratio = divide;
}

Cell_medium::Cell_medium(int hp, int position, int divide)
{
	this->hp = hp;
	this->position = position;
	divide_ratio = divide;
}

Cell_weak::Cell_weak(int hp, int position, int divide)
{
	this->hp = hp;
	this->position = position;
	divide_ratio = divide;
}

///////////////// MAP IMPLEMENTATION ///////////////////////
Map::Map(int size, int strong, int medium, int weak, int bonus, int space)
{
	
	this->size = size;
	map = new Field[size];
	startingStrongCell = strong;
	startingMediumCell = medium;
	startingWeakCell = weak;
	spaceBetweenHealing = space;
	startingBonus = bonus;
} 


int Map::getSize()
{
	return this->size;
}

Field* Map::getMap()
{
	return this->map;
}

int Map::getStartingCellStrong() { return this->startingStrongCell; }
int Map::getStartingCellMedium() { return this->startingMediumCell; }
int Map::getStartingCellWeak() { return this->startingWeakCell; }
int Map::getSpaceBetweenHealing() { return this->spaceBetweenHealing; }
int Map::getStartingBonus() { return this->startingBonus; }

////////////////// SIMULATION IMPLEMENTATION //////////////////////
Simulation::Simulation(Map map1, int maxIteration)
{
	this->map1 = map1;
	this->maxIter = maxIteration;
	cancerCellAmount = 0;
}

bool Simulation::drawAttitude()
{
	int random = rand() % 2;
	if (random == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Simulation::setCellPosition()
{
	srand(time(NULL));
	int pos;
	bool currentAttitude;
	do
	{
		pos = rand() % map1.getSize()+1;
		if (((map1.getMap()+pos)->getCellPointer() == NULL) && ((map1.getMap()+pos)->getBonusPointer() == NULL))
		{
			return pos;
		}
		else if (((map1.getMap() + pos)->getBonusPointer() != NULL)) //Nietestowane
		{
			if ((map1.getMap() + pos)->getBonusPointer()->getAttitude() == true)
			{
				extraDivide();
			}
			else
			{
				instantCure();
			}
			
		}
	} while (true);
}

int Simulation::setBonusPosition()
{
	srand(time(NULL));
	int pos;
	do
	{
		pos = rand() % map1.getSize()+1;
		if (((map1.getMap()+pos)->getCellPointer() == NULL) && ((map1.getMap()+pos)->getBonusPointer() == NULL))
		{
			return pos;
		}
	} while (true);
}

void Simulation::runSimulation()
{
	int pos, i;
	bool attitude;

	for (i = 0; i < map1.getStartingCellStrong(); i++)
	{
		pos = setCellPosition();
		Cell_strong *cellStrong = new Cell_strong(300, pos, 10);
		(map1.getMap() + pos)->setCellPointer(cellStrong);
	}

	for (i = 0; i < map1.getStartingCellMedium(); i++)
	{
		pos = setCellPosition();
		Cell_medium *cellMedium = new Cell_medium(200, pos, 5);
		(map1.getMap() + pos)->setCellPointer(cellMedium);
	}

	for (i = 0; i < map1.getStartingCellWeak(); i++)
	{
		pos = setCellPosition();
		Cell_weak *cellWeak = new Cell_weak(100, pos, 2);
		(map1.getMap() + pos)->setCellPointer(cellWeak);
	}

	for(i = 0 ; i < map1.getStartingBonus(); i++)
	{
		pos = setBonusPosition();
		attitude = drawAttitude();
		Bonus* bonus = new Bonus(pos, attitude);
		(map1.getMap() + pos)->setBonusPointer(bonus);
	}
/*
	for (i = 0; i < map1.getSize(); i++)
	{

		if ((map1.getMap() + i)->getCellPointer() != NULL)
		{
			cout << (map1.getMap() + i)->getCellPointer() << endl;
		}
		else if ((map1.getMap() + i)->getBonusPointer() != NULL)
		{
			cout << (map1.getMap() + i)->getBonusPointer() << endl;
		}
		else
		{
			cout << (map1.getMap() + i)->getCellPointer() << endl;
		}
	}
*/

	do//G£ÓWNA PÊTLA SYMULACJI
	{

		//is healing iteration?
		//drawDrugLevel
		//heal
		//stillAlive
		//divideCheck

	} while (endCheck());
	
	
}








