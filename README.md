# Simulation of cancer development in a human body

## Logic

The map class represents a human body. Each cancer cell has one of the three possible power levels: weak, medium, or strong. In the menu, the user decides on the staring number of the cells with a particular power level.
To cure the disease simulation uses drugs - cytostatics. An actor can choose the space between healing iterations. In a healing iteration, drugs are applied to every cell.
The simulation ends when cancer cells capture the whole organism, or when drugs cure every cell.

## How to run?

Simulation is implemented in c++ language. To compile the program with **g++** complier open the simulation directory in a terminal and type `g++ main.cpp -o main`. Then open `main.exe` file to run the program.

## Output

The simulation generates output file `simulationProcess.txt` with the details of the simulation process.
