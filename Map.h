#pragma once

#include <iostream>
#include <vector>
#include "Node.h"


class Node;

struct DoorPair
{
	Node* door;
	Node* key;
	bool isLocked;
	DoorPair() : isLocked(false) {}
};

class Map
{
	Node** map;
	DoorPair* pairs;
	Node* start;
	Node* end;
	int rows;
	int cols;
	int pairsCount;
public:
	Map() : map(NULL), pairs(NULL) {}
	~Map();
	void load(std::ifstream&);	
	void printMap() const;
	void printKeysAndDoors() const;
	int getCols() const { return cols; } 
	int getRows() const { return rows; } 
	int getDoorIndex(char) const;
	int getKeyIndex(char) const;
	void markCellsUnvisited();
	Node* getStart() const;
	Node* getEnd() const;
	bool isDoorLocked(const Node*) const;
	void lockDoor(char);
	DoorPair* getPairByIdx(int);
	
private:
	bool getDimensions(std::ifstream&);
	bool findPairsCount(std::ifstream&);
	void allocateMap();
	void allocatePair();
	void readMapFromFile(std::ifstream& );
	void readKeysAndDoors(std::ifstream&);
	void freeMap(Node**, int);
	void freeKeysAndDoors(DoorPair*);
	
	friend class Node;


};