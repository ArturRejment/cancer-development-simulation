#include<iostream>
#include<time.h>
#include<cstdlib>
#include"classList.h"
using namespace std;

int cancerCellAmount = 0;


////////////////// BONUS IMPLEMENTATION /////////////////////////
Bonus::Bonus(int position, bool setAttitude)
{
	this->position = position;
	this->attitude = setAttitude;
}


////////////////// CELL IMPLEMENTATION /////////////////////////
CellStrong::CellStrong(int hp, int position, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
}

CellMedium::CellMedium(int hp, int position, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
}

CellWeak::CellWeak(int hp, int position, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
}

void Cell::setHp(int hp)
{
	this->hp = hp;
}

bool Cell::stillAlive()
{
	if (this->hp > 0) return true;
	else return false;
}


CellStrong::~CellStrong()
{
	cancerCellAmount--;
}

CellMedium::~CellMedium()
{
	cancerCellAmount--;
}

CellWeak::~CellWeak()
{
	cancerCellAmount--;
}


////////////////// FIELD IMPLEMENTATION /////////////////////////
Field::Field()
{
	bonusPointer = NULL;
	cellPointer = NULL;
}

void Field::setCellPointer(Cell* newPointer)
{
	this->cellPointer = newPointer;
}

void Field::setBonusPointer(Bonus* newPointer)
{
	this->bonusPointer = newPointer;
}


////////////////// DRUG IMPLEMENTATION /////////////////////////
DrugStrong::DrugStrong(int power)
{
	this->power = power;
}

DrugMedium::DrugMedium(int power)
{
	this->power = power;
}

void DrugStrong::healing(Map *map1, int power)
{
	int i, size = map1->getSize(), newHp;
	Cell* pointer;
	for (i = 0; i < size; i++)
	{
		pointer = (map1->getMap() + i)->getCellPointer();
		if (pointer != NULL)
		{
			newHp = pointer->getHp();
			newHp -= power;
			pointer->setHp(newHp);
		}
	}
}

void DrugMedium::healing(Map *map1, int power)
{
	int i, size = map1->getSize(), newHp;
	Cell* pointer;
	for (i = 0; i < size; i += 2)
	{
		pointer = (map1->getMap() + i)->getCellPointer();
		if (pointer != NULL)
		{
			newHp = pointer->getHp();
			newHp -= power;
			pointer->setHp(newHp);
		}
	}
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
	currentIteration = 1;
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
		pos = rand() % map1.getSize();
		if (((map1.getMap()+pos)->getCellPointer() == NULL) && ((map1.getMap()+pos)->getBonusPointer() == NULL))
		{
			return pos;
		}
		else if (((map1.getMap() + pos)->getBonusPointer() != NULL)) //Untested
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

bool Simulation::drawDrugsLevel()
{
	int level;
	level = rand() % 3;
	if (level == 0)
		return 0; //drug strong
	else
		return 1; //drug medium
}

bool Simulation::endCheck()
{
	if (currentIteration < maxIter) return 1;
	else return 0;
}

void Simulation::runSimulation()
{
	int pos, i;
	bool attitude;

	for (i = 0; i < map1.getStartingCellStrong(); i++)
	{
		pos = setCellPosition();
		Cell *cellStrong = new CellStrong(300, pos, 10);
		(map1.getMap() + pos)->setCellPointer(cellStrong);
	}

	for (i = 0; i < map1.getStartingCellMedium(); i++)
	{
		pos = setCellPosition();
		Cell *cellMedium = new CellMedium(200, pos, 5);
		(map1.getMap() + pos)->setCellPointer(cellMedium);
	}

	for (i = 0; i < map1.getStartingCellWeak(); i++)
	{
		pos = setCellPosition();
		Cell *cellWeak = new CellWeak(100, pos, 2);
		(map1.getMap() + pos)->setCellPointer(cellWeak);
	}

	for(i = 0 ; i < map1.getStartingBonus(); i++)
	{
		pos = setBonusPosition();
		attitude = drawAttitude();
		Bonus* bonus = new Bonus(pos, attitude);
		(map1.getMap() + pos)->setBonusPointer(bonus);
	}


	do//MAIN SIMULATION LOOP
	{

		if (currentIteration % (map1.getSpaceBetweenHealing()) == 0)
		{
			bool level = drawDrugsLevel();
			if(level == 0) //drugStrong
			{
				DrugStrong* drugStrong = new DrugStrong(100);
				int power = drugStrong->getPower();
				drugStrong->healing(&map1, power);
				delete drugStrong;
			}
			else //drugMedium
			{
				DrugMedium* drugMedium = new DrugMedium(50);
				int power = drugMedium->getPower();
				drugMedium->healing(&map1, power);
				delete drugMedium;
			}
		}
		for (i = 0; i < map1.getSize(); i++)
		{
			if ((map1.getMap() + i)->getCellPointer() != NULL)
			{
				if ((map1.getMap() + i)->getCellPointer()->stillAlive() == false)
				{
					
					//cancerCellAmount--;
					delete (map1.getMap() + i)->getCellPointer();
					(map1.getMap() + i)->setCellPointer(NULL);
				}
			}
		}
/*
		for (i = 0; i < map1.getSize(); i++)
		{

			if ((map1.getMap() + i)->getCellPointer() != NULL)
			{
				cout << (map1.getMap() + i)->getCellPointer() << " ";
			}
			else if ((map1.getMap() + i)->getBonusPointer() != NULL)
			{
				cout << (map1.getMap() + i)->getBonusPointer() << " ";
			}
			else
			{
				cout << "0 ";
			}
		}
*/
		
		for (i = 0; i < map1.getSize(); i++)
		{
			if ((map1.getMap() + i)->getCellPointer() != NULL)
			{
				cout << (map1.getMap() + i)->getCellPointer()->getHp()<<" ";
			}
			else
			{
				cout << "0 ";
			}
			
		}
		
		
		cout << cancerCellAmount <<endl;
		currentIteration++;
	} while (endCheck());
	
}








