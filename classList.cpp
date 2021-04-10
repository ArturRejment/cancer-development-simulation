#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <Windows.h>
#include <cstring>
#include "classList.h"

#define _CRT_SECURE_NO_WARNINGS

int cancerCellAmount = 0;
int cancerStrongAmount = 0;
int cancerMediumAmount = 0;
int cancerWeakAmount = 0;
int bonusAmount = -1;
int cellsDividedIteration = 0;
int cellsHealedIteration = 0;
int cellsDividedAll = 0;
int cellHealedAll = 0;
Bonus *bonusHolder = new Bonus(-1, 1);
FILE *simOutput;
Simulation *Simulation::instance = 0;

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

////////////////// BONUS IMPLEMENTATION /////////////////////////

Bonus::Bonus(int position, bool setAttitude)
{
	this->position = position;
	this->attitude = setAttitude;
	bonusAmount++;
}

Bonus::~Bonus() { bonusAmount--; }

void Bonus::extraDivide(int position, Map *map1, std::string type)
{
	delete ((map1->getMap() + position)->getBonusPointer());
	(map1->getMap() + position)->setBonusPointer(bonusHolder);
	Simulation::createObject(type, map1);
	(map1->getMap() + position)->setBonusPointer(NULL);
	return;
}

void Bonus::instantCure(int position, Map *map1)
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
	if (map1.getSize() <= cancerCellAmount + bonusAmount)
		return -1;
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

CellMedium::CellMedium(int position, int hp, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
	cancerMediumAmount++;
}

CellWeak::CellWeak(int position, int hp, int divide)
{
	this->hp = hp;
	this->position = position;
	divideRatio = divide;
	cancerCellAmount++;
	cancerWeakAmount++;
}

int Cell::setCellPosition(Map *map1, std::string type)
{
	if (map1->getSize() <= cancerCellAmount + bonusAmount)
		return -1;
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
				continue;
			}
			if ((map1->getMap() + pos)->getBonusPointer()->getAttitude() == true)
			{
				Bonus::extraDivide(pos, map1, type);
				return pos;
			}
			else
			{
				Bonus::instantCure(pos, map1);
				return -1;
			}
		}
	} while (true);
}

void Cell::setHp(int hp)
{
	this->hp = hp;
	return;
}

void Cell::stillAlive(int pos, Map *map1)
{
	if ((map1->getMap() + pos)->getCellPointer()->hp < 0)
	{
		delete (map1->getMap() + pos)->getCellPointer();
		(map1->getMap() + pos)->setCellPointer(NULL);
		cellsHealedIteration++;
		cellHealedAll++;
	}
}

int Cell::getHp() { return this->hp; }

void CellStrong::divideCheck(Map *map1)
{
	if (cancerStrongAmount > 0.5 * (map1->getSize()))
		this->divideRatio = 15;
	else
		this->divideRatio = 10;

	int random = rand() % (this->divideRatio);

	if (random == 1)
	{
		cellsDividedAll++;
		cellsDividedIteration++;
		Simulation::createObject("strong", map1);
	}
	return;
}

void CellMedium::divideCheck(Map *map1)

{
	if (cancerMediumAmount > 0.5 * cancerCellAmount)
		this->divideRatio = 3;
	else
		this->divideRatio = 5;

	int random = rand() % (this->divideRatio);

	if (random == 1)
	{
		cellsDividedAll++;
		cellsDividedIteration++;
		Simulation::createObject("medium", map1);
	}
	return;
}

void CellWeak::divideCheck(Map *map1)
{
	int random = rand() % (this->divideRatio);

	if (random == 1)
	{
		cellsDividedAll++;
		cellsDividedIteration++;
		Simulation::createObject("weak", map1);
	}
	return;
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

void Field::setCellPointer(Cell *newPointer)
{
	this->cellPointer = newPointer;
	return;
}

void Field::setBonusPointer(Bonus *newPointer)
{
	this->bonusPointer = newPointer;
	return;
}

Cell *Field::getCellPointer() { return this->cellPointer; }

Bonus *Field::getBonusPointer() { return this->bonusPointer; }

////////////////// DRUG IMPLEMENTATION /////////////////////////
DrugStrong::DrugStrong(int power) { this->power = power; }

DrugMedium::DrugMedium(int power) { this->power = power; }

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
	Cell *pointer;
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
	return;
}

void DrugMedium::healing(Map *map1, int power)
{
	int i, size = map1->getSize(), newHp;
	Cell *pointer;
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
	return;
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

Field *Map::getMap() { return this->map; }

int Map::getStartingCellStrong() { return this->startingStrongCell; }
int Map::getStartingCellMedium() { return this->startingMediumCell; }
int Map::getStartingCellWeak() { return this->startingWeakCell; }
int Map::getSpaceBetweenHealing() { return this->spaceBetweenHealing; }
int Map::getStartingBonus() { return this->startingBonus; }

////////////////// SIMULATION IMPLEMENTATION //////////////////////

Simulation *Simulation::getInstance(Map map1, int maxIter)
{
	if (instance == 0)
	{
		instance = new Simulation(map1, maxIter);
	}
	return instance;
}

Simulation::Simulation(Map map1, int maxIteration)
{
	this->map1 = map1;
	this->maxIter = maxIteration;
	currentIteration = 1;
}

void Simulation::createObject(std::string type, Map *map1)
{
	int pos;
	bool attitude;
	Cell *cell;
	Bonus *bonus;
	Drug *drug;

	if (type == "strong")
	{
		pos = Cell::setCellPosition(map1, type);
		if (pos == -1)
			return;
		cell = new CellStrong(pos);
		(map1->getMap() + pos)->setCellPointer(cell);
	}
	else if (type == "medium")
	{
		pos = Cell::setCellPosition(map1, type);
		if (pos == -1)
			return;
		cell = new CellMedium(pos);
		(map1->getMap() + pos)->setCellPointer(cell);
	}
	else if (type == "weak")
	{
		pos = Cell::setCellPosition(map1, type);
		if (pos == -1)
			return;
		cell = new CellWeak(pos);
		(map1->getMap() + pos)->setCellPointer(cell);
	}
	else if (type == "bonus")
	{
		pos = Bonus::setBonusPosition(*map1);
		if (pos == -1)
			return;
		attitude = Bonus::drawAttitude();
		bonus = new Bonus(pos, attitude);
		(map1->getMap() + pos)->setBonusPointer(bonus);
	}
	else if (type == "drugStrong")
	{
		Drug *drug = new DrugStrong(100);
		int power = drug->getPower();
		drug->healing(map1, power);
		delete drug;
	}
	else
	{
		Drug *drug = new DrugMedium(50);
		int power = drug->getPower();
		drug->healing(map1, power);
		delete drug;
	}
	return;
}

int Simulation::endCheck()
{
	float taken = float(map1.getSize()) * 0.9;
	if (taken < float(cancerCellAmount))
		return 3;
	if (cancerCellAmount == 0)
		return 2;
	if (currentIteration <= maxIter)
		return 1;
	else
		return 4;
}

void Simulation::printToFile(int endNumber, int currentIteration, char healingLevel[9])
{
	int i;
	if (endNumber == -1)
	{
		for (i = 0; i < 97; i++)
			fprintf(simOutput, "-");
		fprintf(simOutput, "\n| ITERATION | HEALING | STRONG CELLS | MEDIUM CELLS | WEAK CELLS | HEALED CELLS | DIVIDED CELLS |\n");
		for (i = 0; i < 97; i++)
			fprintf(simOutput, "-");
		return;
	}
	if (endNumber == 0)
	{
		fprintf(simOutput, "\n|%5d      |%8s |%7d       |%7d       |%6d      |%7d       |%7d        |\n", currentIteration, healingLevel, cancerStrongAmount, cancerMediumAmount, cancerWeakAmount, cellsHealedIteration, cellsDividedIteration);
		for (i = 0; i < 97; i++)
			fprintf(simOutput, "-");
		return;
	}
	if (endNumber == 2)
	{
		fprintf(simOutput, "\n\nIN THIS SIMULATION DRUGS HEALED ALL THE CANCER CELLS!");
	}
	else if (endNumber == 3)
	{
		fprintf(simOutput, "\n\nIN THIS SIMULATION CANCER CELLS TOOK OVER AT LEAST 90%% OF THE ORGANISM!");
	}
	else
	{
		fprintf(simOutput, "\n\nTHIS SIMULATION ENDED BECAUSE OF TOO MANY ITERATIONS!");
	}

	fprintf(simOutput, "\nIN ALL ITERATIONS %d CANCER CELLS WERE HEALED,\nAND %d CANCER CELLS WERE DIVIDED", cellHealedAll, cellsDividedAll);
	fprintf(simOutput, "\nSIMULATION ENDED IN %d ITERATION\n", currentIteration - 1);
	return;
}

void Simulation::printToScreen(Map map1)
{
	for (int i = 1; i < map1.getSize() + 1; i++)
	{

		if ((map1.getMap() + i - 1)->getCellPointer() != NULL)
		{

			color(12);
			printf("C ");
			color(7);
		}
		else if ((map1.getMap() + i - 1)->getBonusPointer() != NULL)
		{
			color(2);
			printf("B ");
			color(7);
		}
		else
		{
			printf("0 ");
		}
		if (i % 40 == 0 && i != 0)
			printf("\n");
	}
	return;
}

void Simulation::runSimulation()
{
	int i;
	char healingLevel[9];
	simOutput = fopen("simulationProcess.txt", "w");
	printToFile(-1, currentIteration, healingLevel);

	//CREATING STARTING OBJECTS
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

	for (i = 0; i < map1.getStartingBonus(); i++)
	{
		Simulation::createObject("bonus", &map1);
	}

	//MAIN SIMULATION LOOP
	do
	{

		cellsHealedIteration = 0;
		cellsDividedIteration = 0;

		//HEALING
		if (currentIteration % (map1.getSpaceBetweenHealing()) == 0)
		{
			bool level = Drug::drawDrugsLevel();
			if (level == 0) //drugStrong
			{
				Simulation::createObject("drugStrong", &map1);
				strcpy_s(healingLevel, "STRONG");
			}
			else //drugMedium
			{
				Simulation::createObject("drug", &map1);
				strcpy_s(healingLevel, "MEDIUM");
			}
		}
		else
			strcpy_s(healingLevel, "NO");

		//STILL ALIVE
		if (strcmp(healingLevel, "NO") != 0)
		{
			for (i = 0; i < map1.getSize(); i++)
			{
				if ((map1.getMap() + i)->getCellPointer() != NULL)
				{
					Cell::stillAlive(i, &map1);
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

		printToFile(0, currentIteration, healingLevel);
		gotoxy(0, 0);
		printToScreen(map1);
		Sleep(500);

		currentIteration++;
	} while (endCheck() == 1);

	if (endCheck() == 2)
		printToFile(2, currentIteration, healingLevel);
	else if (endCheck() == 3)
		printToFile(3, currentIteration, healingLevel);
	else
		printToFile(4, currentIteration, healingLevel);
	fclose(simOutput);

	return;
}