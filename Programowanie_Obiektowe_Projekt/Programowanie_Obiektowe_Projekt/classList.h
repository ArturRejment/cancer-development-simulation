#include<iostream>


class Bonus {
private:
	int position;
	bool attitude; // Defines the relation (positive or negative) between bonus and cell
public:
	bool getAttitude() { return this->attitude; };
	Bonus(int,bool);
};


// Abstract class of cell
class Cell {
protected:
	int hp;
	int position;
	int divide_ratio;

public:
	virtual void divideCheck() = 0; // Checking if the cell is going to divide in current iteration
	virtual bool stillAlive() = 0; // Checking if cells hp is still positive 
};

// Three types of cells
class Cell_strong :public Cell {
public:
	Cell_strong(int=300, int=1, int=10);
	void divideCheck() {};
	bool stillAlive() {return true; };
};

class Cell_medium :public Cell {
public:
	Cell_medium(int=200, int=1, int=5);
	void divideCheck() {};
	bool stillAlive() { return true; };
};

class Cell_weak :public Cell {
public:
	Cell_weak(int=100, int=1, int=2);
	void divideCheck() {};
	bool stillAlive() { return true; };
};

class Field {
private:
	Cell* cell_pointer;
	Bonus* bonus_pointer;
public:
	Field();
	Cell* getCellPointer() { return this->cell_pointer; };
	Bonus* getBonusPointer() { return this->bonus_pointer; };
	void setCellPointer(Cell*);
	void setBonusPointer(Bonus*);
};

// Abstract class of drugs
class Drug {
protected:
	int power;
public:
	virtual void healing() = 0; // Try to heal (substract hp if it's a cancer cell) every cell on the map in every iteration
};

// Two types of drugs
class Drug_strong :private Drug {
public:
	Drug_strong() {};
	void healing();
};

class Drug_medium :private Drug {
public:
	Drug_medium() {};
	void healing();

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
	void drawDrugsLevel() {}; // Draws type of drug used in healing iteration
	int getStartingCellStrong() ; 
	int getStartingCellMedium() ;
	int getStartingCellWeak() ;
	int getStartingBonus();
	int getSpaceBetweenHealing() ;
	int getSize();
	Field* getMap() ;
};

class Simulation {
private:
	int maxIter;
	int cancerCellAmount;
	Map map1;
public:
	bool endCheck() {}; // Checking after every iteration if the simutalion should end 
	int setCellPosition();
	int setBonusPosition();
	void extraDivide() {};
	void instantCure() {};
	void runSimulation();
	bool drawAttitude(); //draw bonus attitude(negative or positive)
	Simulation(Map map1, int maxIteration) ;
};

