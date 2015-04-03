#pragma once
#include "Map.h"
#include "Stack.h"
#include "Queue.h"
#include <string>
#include "List.h"

class Solver
{
	
public:
	Solver() {};
	void start(Map*);
	void printPath() const;
private:
	void findDoors(Map*, Node*, Node*, Stack<int>&);
	bool findPath(Map*, Node*, Node*);
	bool BFS(Map* map, Node*, Node*, Queue<Node*>&);
	void solve(Map* map, Node*, Node*);
	char getDirection(Node*, Node*) const;
	void pushIfPassable(Queue<Node*>&, Node*);
	void getNeighbours(List<Node*>&, const Node*) const;
	std::string path;

};