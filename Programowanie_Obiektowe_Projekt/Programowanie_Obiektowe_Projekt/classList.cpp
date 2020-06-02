#include<iostream>
#include<time.h>
#include<cstdlib>
#include"classList.h"
using namespace std;

int cancerCellAmount = 0;
int cancerStrongAmount = 0;
int cancerMediumAmount = 0;
int cancerWeakAmount = 0;
int bonusAmount = 0;
Bonus* bonusHolder = new Bonus(-1,1);


/*
template<typename Base, typename T>
inline bool instanceof(const T*) {
	return is_base_of<Base, T>::value;
}
*/


////////////////// BONUS IMPLEMENTATION /////////////////////////
Bonus::Bonus(int position, bool setAttitude)
{
	this->position = position;
	this->attitude = setAttitude;
	bonusAmount++;
}

Bonus::~Bonus()
{
	bonusAmount--;
}

void Bonus::extraDivide(int position, Map* map1, string type)
{
	delete ((map1->getMap()+position)->getBonusPointer());
	(map1->getMap() + position)->setBonusPointer(bonusHolder);
	Simulation::createObject(type, map1);
	(map1->getMap() + position)->setBonusPointer(NULL);
	return;
}

void Bonus::instantCure(int position, Map* map1)
{
	delete ((map1->getMap() + position)->getBonusPointer());
	(map1->getMap() + position)->setBonusPointer(NULL);
	return;
}

bool Bonus::getAttitude() { return this->attitude; }

bool Bonus::drawAttitude()
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

int Bonus::setBonusPosition(Map map1)
{
	srand(time(NULL));
	int pos;
	do
	{
		pos = rand() % map1.getSize() + 1;
		if (((map1.getMap() + pos)->getCellPointer() == NULL) && ((map1.getMap() + pos)->getBonusPointer() == NULL))
		{
			return pos;
		}
	} while (true);
}


////////////////// CELL IMPLEMENTATION /////////////////////////
CellStrong::CellStrong(int position, int hp, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
	cancerStrongAmount++;
}

string CellStrong::getType()
{
	return "strong";
}

CellMedium::CellMedium(int position, int hp, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
	cancerMediumAmount++;
}

string CellMedium::getType()
{
	return "medium";
}

CellWeak::CellWeak(int position, int hp, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
	cancerWeakAmount++;
}

string CellWeak::getType()
{
	return "weak";
}

int Cell::setCellPosition(Map* map1, string type)
{
	if (map1->getSize() <= cancerCellAmount + bonusAmount) return -1;
	srand(time(NULL));
	int pos;
	bool currentAttitude;
	do
	{
		pos = rand() % map1->getSize();
		if (((map1->getMap() + pos)->getCellPointer() == NULL) && ((map1->getMap() + pos)->getBonusPointer() == NULL))
		{
			return pos;
		}
		else if (((map1->getMap() + pos)->getBonusPointer() != NULL))
		{
			if ((map1->getMap() + pos)->getBonusPointer() == bonusHolder)
			{
				cout << " TU JEST BONUS HOLDER" <<endl;
				continue;
			}
			if ((map1->getMap() + pos)->getBonusPointer()->getAttitude() == true)
			{
				cout << " EXTRA DIVIDE "<<endl;
				Bonus::extraDivide(pos, map1, type);
				return pos;
			}
			else
			{
				cout << "INSTANT CURE"<<endl;
				Bonus::instantCure(pos, map1);
				return -1;
			}

		}
	} while (true);
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

int Cell::getHp() { return this->hp; }

void CellStrong::divideCheck(Map* map1)
{
	if (cancerStrongAmount > 0.5 * (map1->getSize())) this->divideRatio = 15;
	else this->divideRatio = 10;

	int random = rand() % (this->divideRatio);

	if(random == 1)
	{
		Simulation::createObject("strong", map1);
	}
}

void CellMedium::divideCheck(Map* map1)

{
	if (cancerMediumAmount > 0.5 * cancerCellAmount) this->divideRatio = 3;
	else this->divideRatio = 5;

	int random = rand() % (this->divideRatio);

	if(random == 1)
	{
		Simulation::createObject("medium", map1);
	}
}

void CellWeak::divideCheck(Map* map1)
{
	int random = rand() % (this->divideRatio);

	if(random == 1)
	{
		Simulation::createObject("weak", map1);
	}
}



CellStrong::~CellStrong()
{
	cancerCellAmount--;
	cancerStrongAmount--;
}

CellMedium::~CellMedium()
{
	cancerCellAmount--;
	cancerMediumAmount--;
}

CellWeak::~CellWeak()
{
	cancerCellAmount--;
	cancerWeakAmount--;
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

Cell* Field::getCellPointer() { return this->cellPointer; }

Bonus* Field::getBonusPointer() { return this->bonusPointer; }


////////////////// DRUG IMPLEMENTATION /////////////////////////
DrugStrong::DrugStrong(int power)
{
	this->power = power;
}

DrugMedium::DrugMedium(int power)
{
	this->power = power;
}

int Drug::getPower() { return this->power; }

bool Drug::drawDrugsLevel()
{
	int level;
	level = rand() % 3;
	if (level == 0)
		return 0; //drug strong
	else
		return 1; //drug medium
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

int Map::getSize() { return this->size; }

Field* Map::getMap() { return this->map; }

int Map::getStartingCellStrong() { return this->startingStrongCell; }
int Map::getStartingCellMedium() { return this->startingMediumCell; }
int Map::getStartingCellWeak() { return this->startingWeakCell; }
int Map::getSpaceBetweenHealing() { return this->spaceBetweenHealing; }
int Map::getStartingBonus() { return this->startingBonus; }


////////////////// SIMULATION IMPLEMENTATION //////////////////////
Simulation* Simulation::instance = 0;

Simulation* Simulation::getInstance(Map map1, int maxIter)
{
	if (instance == 0)
	{
		instance = new Simulation(map1,maxIter);
	}
	return instance;
}

Simulation::Simulation(Map map1, int maxIteration)
{
	this->map1 = map1;
	this->maxIter = maxIteration;
	currentIteration = 1;
}

void Simulation::createObject(string type, Map* map1)
{
	int pos;
	bool attitude;
	Cell* cellStrong;
	Cell* cellMedium;
	Cell* cellWeak;
	Bonus* bonus;

	if (type == "strong")
	{
		pos = Cell::setCellPosition(map1, type);
		if (pos == -1) return;
		cellStrong = new CellStrong(pos);
		(map1->getMap() + pos)->setCellPointer(cellStrong);
	}
	else if (type == "medium")
	{
		pos = Cell::setCellPosition(map1, type);
		if (pos == -1) return;
		cellMedium = new CellMedium(pos);
		(map1->getMap() + pos)->setCellPointer(cellMedium);
	}
	else if (type == "weak")
	{
		pos = Cell::setCellPosition(map1, type);
		if (pos == -1) return;
		cellWeak = new CellWeak(pos);
		(map1->getMap() + pos)->setCellPointer(cellWeak);
	}
	else if (type == "bonus")
	{
		pos = Bonus::setBonusPosition(*map1);
		if (pos == -1) return;
		attitude = Bonus::drawAttitude();
		bonus = new Bonus(pos, attitude);
		(map1->getMap() + pos)->setBonusPointer(bonus);
	}
	else if (type == "drugStrong")
	{
		Drug* drugStrong = new DrugStrong(100);
		int power = drugStrong->getPower();
		drugStrong->healing(map1, power);
		delete drugStrong;
	}
	else
	{
		Drug* drugMedium = new DrugMedium(50);
		int power = drugMedium->getPower();
		drugMedium->healing(map1, power);
		delete drugMedium;
	}
}


int Simulation::endCheck()
{
	float taken = float(map1.getSize()) * 0.9;
	if (taken < float(cancerCellAmount)) return 3;
	if (cancerCellAmount == 0) return 2;
	if (currentIteration < maxIter) return 1;
	else return 4;
}

void Simulation::runSimulation()
{
	int i;
	cout << "BONUS HOLDER = " << bonusHolder <<endl;
	

	for (i = 0; i < map1.getStartingCellStrong(); i++)
	{
		Simulation::createObject("strong", &map1);
	}

	for (i = 0; i < map1.getStartingCellMedium(); i++)
	{
		Simulation::createObject("medium", &map1);
	}

	for (i = 0; i < map1.getStartingCellWeak(); i++)
	{
		Simulation::createObject("weak", &map1);
	}

	for(i = 0 ; i < map1.getStartingBonus(); i++)
	{
		Simulation::createObject("bonus", &map1);
	}


	do//MAIN SIMULATION LOOP
	{

		if (currentIteration % (map1.getSpaceBetweenHealing()) == 0)
		{
			bool level = Drug::drawDrugsLevel();
			if(level == 0) //drugStrong
			{
				Simulation::createObject("drugStrong", &map1);
			}
			else //drugMedium
			{
				Simulation::createObject("drug", &map1);
			}
		}
		for (i = 0; i < map1.getSize(); i++)
		{
			if ((map1.getMap() + i)->getCellPointer() != NULL)
			{
				if ((map1.getMap() + i)->getCellPointer()->stillAlive() == false)
				{
					delete (map1.getMap() + i)->getCellPointer();
					(map1.getMap() + i)->setCellPointer(NULL);
				}
			}
		}

		//DIVIDE CELLS
		for (i = 0; i < map1.getSize(); i++)
		{
			if ((map1.getMap() + i)->getCellPointer() != NULL)
			{
				((map1.getMap() + i)->getCellPointer())->divideCheck(&map1);
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
				printf("%3d ", (map1.getMap() + i)->getCellPointer()->getHp());
			}
			else if ((map1.getMap() + i)->getBonusPointer() != NULL)
			{
				printf("%3s ", "B");
			}
			else
			{
				printf("%3s ", "0");
			}
			
		}
		cout << endl;
	

		
		
		//cout << cancerCellAmount <<endl;
		currentIteration++;
	} while (endCheck()==1);
	
	cout << "Koniec";
	return;
}








