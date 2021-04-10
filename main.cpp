#include <iostream>
#include <Windows.h>
#include "menu.cpp"

int main()
{
    int config[6] = {0};
    menu(config);

    Map map1(config[0], config[1], config[2], config[3], config[4], config[5]); //Map parameters: size, strongCells, mediumCells, weakCells, bonus, space
    Simulation *sim1 = Simulation::getInstance(map1, 100);
    (*sim1).runSimulation();
    return 0;
}