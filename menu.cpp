#include<iostream> 
#include<conio.h>
#include<Windows.h>
#include"classList.h"
using namespace std;

void gotoxy(int x, int y)
{
	COORD c;

	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int menu(int* config)
{
	int menu = 0;
	int x = 9;
	int mapSize = 40;
	int strongCells = 0;
	int mediumCells = 0;
	int weakCells = 0;
	int bonus = 0;
	int space = 1;

	gotoxy(10, 9); cout << char(175);

	while (true)
	{
		system("cls");
		gotoxy(10, x); cout << char(175);
		gotoxy(12, 9); cout << "Map size";
		gotoxy(40, 9); cout << "<< " << mapSize << " >>";
		gotoxy(12, 10); cout << "Amount of strong cells";
		gotoxy(40, 10); cout << "<< " << strongCells << " >>";
		gotoxy(12, 11); cout << "Amount of medium cells";
		gotoxy(40, 11); cout << "<< " << mediumCells << " >>";
		gotoxy(12, 12); cout << "Amount of weak cells";
		gotoxy(40, 12); cout << "<< " << weakCells << " >>";
		gotoxy(12, 13); cout << "Amount of bonus";
		gotoxy(40, 13); cout << "<< " << bonus << " >>";
		gotoxy(12, 14); cout << "Space between healing";
		gotoxy(40, 14); cout << "<< " << space << " >>";
		gotoxy(12, 15); cout << "CONFIRM";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x != 15)
		{
			gotoxy(10, x); cout << "  "; x++;
			gotoxy(10, x); cout << char(175); menu++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 9)
		{
			gotoxy(10, x); cout << "  "; x--;
			gotoxy(10, x); cout << char(175); menu--;
			continue;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			switch (menu)
			{
			case 0:
				if (mapSize != 1600)
					mapSize += 40;
				break;
			case 1:
				if (strongCells != 50)
					strongCells += 5;
				break;
			case 2:
				if (mediumCells != 50)
					mediumCells += 5;
				break;
			case 3:
				if (weakCells != 50)
					weakCells += 5;
				break;
			case 4:
				if (bonus != 20)
					bonus++;
				break;
			case 5:
				if (space != 5)
					space++;
				break;
			}
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			switch (menu)
			{
			case 0:
				if (mapSize != 40)
					mapSize -= 40;
				break;
			case 1:
				if (strongCells != 0)
					strongCells -= 5;
				break;
			case 2:
				if (mediumCells != 0)
					mediumCells -= 5;
				break;
			case 3:
				if (weakCells != 0)
					weakCells -= 5;
				break;
			case 4:
				if (bonus != 0)
					bonus--;
				break;
			case 5:
				if (space != 1)
					space--;
				break;
			}
		}

		if (GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT)) //enter
		{
			if (menu == 6)
			{
				if (strongCells + mediumCells + weakCells + bonus > mapSize)
				{
					system("cls");
					gotoxy(10, 10);
					cout << "Amount of cancer cells and bonuses cannot be bigger than size of the map.";
					gotoxy(10, 11);
					cout << "Check selected data";
					gotoxy(10, 12);
					cout << "Press any key to continue";
					char c = _getch();
					continue;
				}
				config[0] = mapSize;
				config[1] = strongCells;
				config[2] = mediumCells;
				config[3] = weakCells;
				config[4] = bonus;
				config[5] = space;
				system("cls");
				return *config;
			}
		}
	}
}
