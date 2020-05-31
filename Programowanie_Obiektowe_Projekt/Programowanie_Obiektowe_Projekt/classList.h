#include<iostream>
using namespace std;


class Bonus {
private:
	int position;
	bool attitude; // Defines the relation (positive or negative) between bonus and cell
public:
	static bool drawAttitude(); //draw bonus attitude(negative or positive)
	bool getAttitude();
	Bonus(int,bool);
};


// Abstract class of cell
class Cell {
protected:
	int hp;
	int position;
	int divideRatio;

public:
	virtual void divideCheck() = 0; // Checking if the cell is going to divide in current iteration
	int getHp();
	void setHp(int hp);
	bool stillAlive();
	virtual ~Cell() {};
};

// Three types of cells
class CellStrong :public Cell {
public:
	CellStrong(int=300, int=1, int=10);
	void divideCheck() {};
	~CellStrong();
};

class CellMedium :public Cell {
public:
	CellMedium(int=200, int=1, int=5);
	void divideCheck() {};
	~CellMedium();
};

class CellWeak :public Cell {
public:
	CellWeak(int=100, int=1, int=2);
	void divideCheck() {};
	~CellWeak();
};

class Field {
private:
	Cell* cellPointer;
	Bonus* bonusPointer;
public:
	Field();
	Cell* getCellPointer();
	Bonus* getBonusPointer();
	void setCellPointer(Cell*);
	void setBonusPointer(Bonus*);
};

class Map {
private:

	Field *map; // Array holds the information about restored type of object
	int startingStrongCell, startingMediumCell, startingWeakCell; // Amount of every cell at the beginnig of simulation given by user
	int spaceBetweenHealing;
	int startingBonus;
	int size;
public:
	Map(int=4, int=1, int=1, int=1, int=1, int=1);
	
	int getStartingCellStrong() ; 
	int getStartingCellMedium() ;
	int getStartingCellWeak() ;
	int getStartingBonus();
	int getSpaceBetweenHealing() ;
	int getSize();
	Field* getMap() ;
};

// Abstract class of drugs
class Drug {
protected:
	int power;
	Map map1;
public:
	static bool drawDrugsLevel(); // Draws type of drug used in healing iteration
	virtual void healing(Map *map1, int power) = 0; // Try to heal (substract hp if it's a cancer cell) every cell on the map in particular iterations
	int getPower();
};


// Two types of drugs
class DrugStrong :public Drug {
public:
	DrugStrong(int=100);
	void healing(Map *map1, int power);
};

class DrugMedium :public Drug {
public:
	DrugMedium(int=50);
	void healing(Map *map1, int power);

};


class Simulation {
private:
	static Simulation* instance;
	Simulation(Map map1, int maxIteration);
	int maxIter;
	int currentIteration;
	Map map1;
public:
	static Simulation* getInstance(Map map1, int maxIter);
	bool endCheck() ; // Checking after every iteration if the simutalion should end 
	int setCellPosition();
	int setBonusPosition();
	void extraDivide() {};
	void instantCure() {};
	void runSimulation();
	
};

