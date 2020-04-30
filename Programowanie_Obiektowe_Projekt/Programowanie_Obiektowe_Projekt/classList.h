#include<iostream>


class Simulation {
private:
	int maxIter;
public:
	void endCheck() {}; // Checking after every iteration if the simutalion should end 
	void runSimulation() {};
	Simulation();
};

class Field {
private:
	Bonus* bonus_pointer;
	Cell* cell_pointer;
public:
	Field();
};

// Abstract class of cell
class Cell {
protected:
	int hp;
	int position;
	int divide_ratio;

public:
	virtual void setPosition() = 0; // Seting position on the map, also chceking if there is a bonus on this position
	virtual void divideCheck() = 0; // Checking if the cell is going to divide in current iteration
	virtual bool stillAlive() = 0; // Checking if cells hp is still positive 
};

// Three types of cells
class Cell_strong :private Cell {
	Cell_strong();
	void divideCheck(); 
	void setPosition();
	bool stillAlive();
};

class Cell_medium :private Cell {
	Cell_medium();
	void divideCheck();
	void setPosition();
	bool stillAlive();
};

class Cell_weak :private Cell {
	Cell_weak();
	void divideCheck();
	void setPosition();
	bool stillAlive();
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
	Field *map; // Array holds the information about restored type of object ( 'c' if it is cell or 'b' if it is bonus)
	int startingStrongCell, startingMediumCell, startingWeakCell; // Amount of every cell at the beginnig of simulation given by user
	int spaceBetweenHealing;
public:
	Map();
	void drawDrugsLevel() {}; // Draws type of drug used in healing iteration
	void getMesurements() {}; // Read number of cells
};

class Bonus {
private:
	int position;
	bool positive; // Defines the relation (positive or negative) between bonus and cell
public:
	void setBonusPosition() {}; // Seting positions of every bonus at the beginning of simulation
	void extraDivide() {};
	void instantCure() {};
};