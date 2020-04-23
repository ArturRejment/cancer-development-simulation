#include<iostream>


//Abstract class of cell
class Cell {
protected:
	int hp;
	int position_x, position_y;
	int divide_ratio;

public:
	virtual void setPosition() = 0; //Seting position on the map, also chceking if there is a bonus on this position
	virtual void divideCheck() = 0; //Checking if the cell is going to divide in current iteration
	virtual bool stillAlive() = 0; //Checking if cells hp is still positive 
	virtual void drawCellLevel() = 0;
}; 

//Three types of cells
class Cell_strong :private Cell {
	Cell_strong();
};

class Cell_medium :private Cell {
	Cell_medium();
};

class Cell_weak :private Cell {
	Cell_weak();
};

//Abstract class of drugs
class Drug {
protected:
	int power;
public:
	virtual void healing() = 0; //Try to heal (substract hp if it's a cancer cell) every cell on the map in every iteration
};

//Two types of drugs
class Drug_strong :private Drug {
public:
	Drug_strong() {};
};

class Drug_medium :private Drug {
public:
	Drug_medium() {};
};

class Map {
private:
	int width, height;
	int startingStrongCell, startingMediumCell, startingWeakCell; // Amount of every cell at the beginnig of simulation given by user
	int spaceBetweenHealing;
public:
	void drawDrugsLevel() {};
	void getMesurements() {};
	void createMap() {};
	void endCheck() {}; // Checking after every iteration if the simutalion should end 
};

class Bonus {
private:
	int position_x, position_y;
	bool positive; //Defines the relation (positive or negative) between bonus and cell
public:
	void setBonusPosition() {}; //Seting positions of every bonus at the beginning of simulation
	void extraDivide() {};
	void instantCure() {};
};