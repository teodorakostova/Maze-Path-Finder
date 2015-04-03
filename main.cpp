#include <iostream>
#include <fstream>
#include "Map.h"
#include "Solver.h"
#include <crtdbg.h> 
using namespace std;

int main(int argc, char* argv[]) 
{

	argc = 2;
	//argv[1] = "map1.txt";
	argv[1] = "room2.txt";
	//argv[3] = "room.txt";
	
	Solver solver;
	Map* map = NULL;
	for (int i = 1; i < argc; i++)
	{
		map = new Map;
		ifstream in(argv[i]);
		try 
		{
			map->load(in);
			//map->printMap();
			//cout << endl;
			solver.start(map);
			//solver.printPath();
		}
		catch (const char* e)
		{
			delete map;
			in.close();
			cin.get();
			return 0;
		}
		delete map;
		in.close();
	}

	solver.printPath();
	cin.get();
	return 0;
}