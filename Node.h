#pragma once
#include "Map.h"
#include <vector>

class Map;

class Node
{
public:	
	Node(char symbol = ' ', Map* owner = NULL, int row = 0, int col = 0)
		: symbol(symbol), owner(owner), row(row), col(col), parent(NULL) {}

	void setSymbol(char c) { symbol = c; }
	void setRow(int);
	void setCol(int);
	void setParent(Node* p) { parent = p; }
	void setOwner(Map*);
	void setVisited(bool visited) { this->visited = visited; } 
	
	int getCol() const { return col;} 
	int getRow() const { return row; } 
	Node* getParent() const { return parent; }
	char getSymbol() const { return symbol; }
	Node* getLeft() const;
	Node* getUp() const;
	Node* getDown() const;
	Node* getRight() const;
	
	void print() const;
	bool isKey() const;
	bool isDoor() const;
	bool isLockedDoor() const;
	bool isPassable() const;
	bool isVisited() const { return visited; } 
private:
	Map* owner;
	Node* parent;
	bool visited;
	char symbol;
	int row;
	int col;

};