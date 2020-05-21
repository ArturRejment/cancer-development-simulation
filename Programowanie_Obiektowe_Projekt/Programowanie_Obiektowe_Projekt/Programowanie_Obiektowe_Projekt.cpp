#include <iostream>
#include "classList.h"
using namespace std;

int main()
{
    Map map1(20,4,1,1,2,10);
    Simulation sim1(map1, 50);
    sim1.runSimulation();

    return 0;
}
//główna petla symulacji (maxIteration)
//napisac cialo endCheck()
//napisac cialo extraDivide()
//napisac cialo instantCure()