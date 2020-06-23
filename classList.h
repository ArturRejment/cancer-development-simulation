#include<iostream>

void gotoxy(int, int);
int menu(int*);
class Map;

/// Class that interacts with cells 
class Bonus {
private:
	int position;
	/// Define the relation (positive or negative) between bonus and cell
	bool attitude; 
public:
	static int setBonusPosition(Map map1);
	/// Draw bonus attitude (negative or positive)
	static bool drawAttitude(); 
	/// Called when cell meets positive bonus
	/// @see attitude
	static void extraDivide(int pos, Map* map1, std::string type);
	/// Called when cell meets negative bonus
	/// @see attitude
	static void instantCure(int pos, Map* map1);
	bool getAttitude();
	Bonus(int, bool);
	~Bonus();
};


/// Abstract class of cancer cells
class Cell {
protected:
	int hp;
	int position;
	/// Ratio that defines the probability of cell division
	int divideRatio;
public:
	/// Checking after healing if cancer cell is alive 
	static void stillAlive(int pos, Map* map1);
	/// @param type holds an information about the type of dividing cell
	static int setCellPosition(Map* map1, std::string type);
	/// Checking if the cell is going to divide in current iteration
	virtual void divideCheck(Map* map1) = 0; 
	int getHp();
	void setHp(int hp);
	virtual ~Cell() {};
};

class CellStrong :public Cell {
public:
	CellStrong(int = 1, int = 200, int = 10);
	void divideCheck(Map* map1);
	~CellStrong();
};

class CellMedium :public Cell {
public:
	CellMedium(int = 1, int = 130, int = 5);
	void divideCheck(Map* map1);
	~CellMedium();
};

class CellWeak :public Cell {
public:
	CellWeak(int = 1, int = 70, int = 2);
	void divideCheck(Map* map1);
	~CellWeak();
};

/// A class holding the information about stored type of object on the map
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

/// Class that represents human organism
class Map {
private:
	/// Array holding objects from class Field
	Field* map; 
	/// Amount of every cell and bonus at the beginning of simulation given by user
	int startingStrongCell, startingMediumCell, startingWeakCell, startingBonus;
	/// Space between healing iterations given by user 
	int spaceBetweenHealing;
	int size;
public:
	Map(int = 4, int = 1, int = 1, int = 1, int = 1, int = 1);
	int getStartingCellStrong();
	int getStartingCellMedium();
	int getStartingCellWeak();
	int getStartingBonus();
	int getSpaceBetweenHealing();
	int getSize();
	Field* getMap();
};

/// An abstract class of Drugs used to cure the cancer cells
class Drug {
protected:
	int power;
	Map map1;
public:
	/// Draw type of drug used in healing iteration
	static bool drawDrugsLevel();
	// Heal (substract hp if it's a cancer cell) every cell on the map in specific iterations
	virtual void healing(Map *map1, int power) = 0; 
	int getPower();
};

class DrugStrong :public Drug {
public:
	DrugStrong(int=100);
	/// Heal every cell on the map
	void healing(Map *map1, int power);
};

class DrugMedium :public Drug {
public:
	DrugMedium(int=50);
	/// Heal every second cell on the map
	void healing(Map *map1, int power);

};

/// The class that contains the logic of the simulation 
///
/// Built as a singleton and facade design pattern
class Simulation {
private:
	/// The only instance of class Simulation
	static Simulation* instance;
	Simulation(Map map1, int maxIteration);
	int maxIter;
	int currentIteration;
	Map map1;
public:
	/// @returns return existing object or create new instance
	static Simulation* getInstance(Map map1, int maxIter);
	/// Create specific type of object
	/// @param type holds an information about the type of creating object 
	static void createObject(std::string type, Map* map1);
	/// A function responsible for printing a simulation process to the file
	///
	/// @param endNumber contains an information about returned value by endCheck() function
	/// @param healingLevel contains an information about the type of drugs used in current simulation
	static void printToFile(int endNumber, int currentIteration, char healingLevel[9]);
	/// A function responsible for printing up to date a simulation process on the screen
	static void printToScreen(Map map1);
	/// A function that checks if the simulation should end
	/// @returns 1 if the simulation should keep going
	/// @returns 2 if all cancer cells are cured
	/// @returns 3 if cancer cells took over at least 90% of the organism
	/// @returns 4 if the simulation should end because of too many iterations
	int endCheck() ; 
	void runSimulation();
};

