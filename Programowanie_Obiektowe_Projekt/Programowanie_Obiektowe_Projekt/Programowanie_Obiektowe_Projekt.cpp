#include <iostream>
#include "classList.h"
using namespace std;

int main()
{
    Map map1(20,4,1,1,2,5);
    Simulation sim1(map1, 50);
    sim1.runSimulation();

    return 0;
}

//Do zrobienia
//napisac cialo endCheck()
//napisac cialo extraDivide()
//napisac cialo instantCure()
//interakcja celli z bonusem
//podział komórek