#include "Map.h"
#include <string>
#include <fstream>

using namespace std;

const char START = 'S';
const char END = 'X';

Map::~Map()
{
	freeMap(map, rows);
	freeKeysAndDoors(pairs);
}

void Map::load(std::ifstream& file)
{
	if (!file.good())
		return;

	if (!getDimensions(file))
	{
		file.close();
		throw "Invalid dimensions";
	}
	
	if (!findPairsCount(file))
	{
		file.close();
		throw "Invalid pair of key and door";
	}

	try
	{
		allocatePair();
	}
	catch(bad_alloc& e)
	{
		cout << "allocation of kays and doors failed" << endl;
		throw e;
	}

	readKeysAndDoors(file);	

	try
	{
		allocateMap();
	}
	catch(bad_alloc& e)
	{
		cout << "allocation of map failed" << endl;
		throw e;
	}
	readMapFromFile(file);
	file.close();
	
}

void Map::allocateMap()
{
	int i = 0;
	try
	{
		map = new Node*[rows];
		for (i = 0; i < rows; i++)
			map[i] = new Node[cols];
	}
	catch (std::bad_alloc& e)
	{
		freeMap(map, i);
		throw e;
	}
}

void Map::freeMap(Node** map, int rows)
{
	if (!map)
		return;

	for (int i = 0; i < rows; i++)
	{
		if (map[i])
			delete [] map[i];
	}
	delete [] map;
	map = NULL;
	
}

void Map::allocatePair() 
{
	try
	{
		pairs = new DoorPair[pairsCount];
	}
	catch(std::bad_alloc& e)
	{
		throw e;
	}
}


void Map::freeKeysAndDoors(DoorPair* pair)
{
	if (!pair)
		return;
	delete [] pair;
	pair = NULL;
}

bool Map::findPairsCount(std::ifstream& file)
{
	file.clear();
	file.seekg(0);

	if (!file.good())
		return false;

	int i = 0;
	char c;
	while (file.get(c))
	{
		if (i >= rows)
			break;
		if (c == '\n')
			i++;
	}
	
	int doors = 0;
	int keys = 0;
	while (file.get(c))
	{
		if (c <= '9'&& c >= '0')
			doors++;
		else if (c != ' ' && c != '\n')
			keys++; 
	}

	if (doors == keys)
	{
		pairsCount = doors;
	}
	else
	{
		return false;
	}
	return true;

}

void Map::readKeysAndDoors(ifstream& file)
{	
	file.clear();
	file.seekg(0);
	
	int i = 0;
	char c;
	while (file.get(c))
	{
		if (i >= rows)
			break;
		if (c == '\n')
			i++;
	}
	
	i = 0;
	
	while (file.get(c))
	{
		if (c <= '9'&& c >= '0')
		{
			pairs[i].door = new Node(c);
			pairs[i].isLocked = true;
		}

		else if (c != ' ' && c != '\n')
			pairs[i].key = new Node(c);

		else if (c == '\n' )
			i++;	
	}

}

bool Map::getDimensions(std::ifstream& file)
{
	char c;
	int rows = 0;;
	int cols = 0;

	while (file.get(c) && c != '\n')
		cols++;

	if (cols < 2)
		return false;

	file.seekg(0);
	int i = 0;
	while (file.get(c))
	{
		if (c == '\n')
		{
			if (i < cols && i > 1)
			{
				return false;
			}

			if (i < cols)
			{
				break;
			}
			
			i = 0;
			rows++;
		}
		i++;
	}

	if (rows < 2)
		return false;

	this->cols = cols;
	this->rows = rows;
	return true;
}

void Map::readMapFromFile(std::ifstream& file)
{
	file.clear();
	file.seekg(0); 
	
	char c;
	int i = 0, j = 0;
	while (file.get(c))
	{		
		while (c == '\n')
		{
			i++;
			j = 0;
			file.get(c);
		}
		if (i > rows)
			return;
		Node n(c, this, i, j);
		map[i][j] = n;
		
		int doorIdx = getDoorIndex(c);
		int keyIdx = getKeyIndex(c);
		if (doorIdx != -1)
		{
			pairs[doorIdx].door = &map[i][j];
			pairs[doorIdx].isLocked = true;
			
		}
		else if (keyIdx != -1)
		{
			pairs[keyIdx].key = &map[i][j];
		}
		else if (c == START)
		{
			start = &map[i][j];
			
		}
		else if (c == END)
		{
			end = &map[i][j];
			
		}
		j++;

	}
}

void Map::printKeysAndDoors() const
{
	for (int i = 0; i < pairsCount; i++)
	{
		cout << "Door: " << pairs[i].door->getSymbol()
			<< "\nRow: " << pairs[i].door->getRow()
			<< "\nCol: " << pairs[i].door->getCol() << endl;
		
		cout << "Key: " << pairs[i].key->getSymbol()
			<< "\nRow: " << pairs[i].key->getRow()
			<< "\nCol: " << pairs[i].key->getCol() << endl;
		cout << "Locked: " << pairs[i].isLocked << endl;
	}
}


void Map::printMap() const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			std::cout << map[i][j].getSymbol();
		std::cout << std::endl; 
	}
}

Node* Map::getStart() const
{
	return start;
}

Node* Map::getEnd() const
{
	return end;
}



void Map::markCellsUnvisited()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			map[i][j].setVisited(false);
}

DoorPair* Map::getPairByIdx(int idx)
{
	if (idx < pairsCount)
		return &pairs[idx];
	else throw "invalid index Map::getPairByIdx(int)";
}

int Map::getDoorIndex(char d) const
{
	for (int i = 0; i < pairsCount; i++)
	{
		if (d == pairs[i].door->getSymbol())
		{
			return i;
		}
	}
	return -1;
}

int Map::getKeyIndex(char k) const
{
	for (int i = 0; i < pairsCount; i++)
	{
		if (k == pairs[i].key->getSymbol())
			return i;
	}
	return -1;
}

bool Map::isDoorLocked(const Node* door) const
{
	for (int i = 0; i < pairsCount; i++)
	{
		if (door == pairs[i].door && pairs[i].isLocked)
		{
			return true;
		}
	}
	return false;
}

