#include "Solver.h"
#include "Queue.h"
#include "Stack.h"
#include "Compressor.h"
#include "List.h"
using namespace std;

void Solver::start(Map* map)
{
	if (path.empty() == false)
		path.clear();
	Node* start = map->getStart();
	Node* end = map->getEnd();
	solve(map, start, end);
}

void Solver::solve(Map* map, Node* start, Node* end)
{
	Stack<int> doorsIndexes;
	findDoors(map, start, end, doorsIndexes);

	if (doorsIndexes.empty())
	{
		findPath(map, start, end);
		return;
	}

	Node* startNode = start;
	Node* key = NULL;
	DoorPair* currentPair = NULL;
	while (!doorsIndexes.empty())
	{
		currentPair = map->getPairByIdx(doorsIndexes.pop());
		key = currentPair->key;
		if (findPath(map, startNode, key))
		{
			currentPair->isLocked = false;
			Node* door = currentPair->door;
			if (findPath(map, key, door))
			{
				startNode = door;
			}
			else
			{
				solve(map, key, door);
			}
		}
		else
		{	
			solve(map, startNode, key);

		}
	}

	findPath(map, currentPair->door, end); 
}

void Solver::pushIfPassable(Queue<Node*>& q, Node* current)
{
	List<Node*> neighbours;
	getNeighbours(neighbours, current);
	
	while (!neighbours.isEmpty())
	{
		Node* n = neighbours.removeFront();
		if (n && n->isPassable() && !n->isVisited())
		{
			q.push(n);
			n->setVisited(true);
			n->setParent(current);
		}
	}
}


void Solver::getNeighbours(List<Node*>& neighbours, const Node* current) const
{
	if (current->getLeft())
		neighbours.addLast(current->getLeft());	
	if (current->getRight())
		neighbours.addLast(current->getRight());
	if (current->getUp())
		neighbours.addLast(current->getUp());
	if (current->getDown())
		neighbours.addLast(current->getDown());	
}

bool Solver::BFS(Map* map, Node* start, Node* end, Queue<Node*>& walkedPath)
{
	
	if (start == end)
		return true;

	Queue<Node*> q;
	q.push(start);
	map->markCellsUnvisited();

	while (!q.isEmpty())
	{
		Node* current = q.pop();
		current->setVisited(true);

		if (current == end)
		{
			while (current != start)
			{
				walkedPath.push(current);
				current = current->getParent();
			}		
			return true;
		}
		pushIfPassable(q, current);
	}

	return false;
}

void Solver::findDoors(Map* map, Node* start, Node* end, Stack<int>& doors)
{
	Queue<Node*> walkedPath;
	BFS(map, start, end, walkedPath);
	
	while (walkedPath.isEmpty() == false)
	{
		Node* node = walkedPath.pop();
		if (node->isDoor())
		{
			doors.push(map->getDoorIndex(node->getSymbol()));
		}

	}

}

bool Solver::findPath(Map* map, Node* start, Node* end)
{
	Queue<Node*> walkedPath;
	Stack<char> partOfPath;
	
	if (!BFS(map, start, end, walkedPath))
		return false;

	while (!walkedPath.isEmpty())
	{
		Node* current = walkedPath.pop();
		
		if (current->isLockedDoor())
			return false;
		
		if (getDirection(current, current->getParent()) != ' ')
			partOfPath.push(getDirection(current, current->getParent()));
	}

	while (!partOfPath.empty())
	{
		path.push_back(partOfPath.pop());
	}

	return true;
}


char Solver::getDirection(Node* current, Node* parent) const
{
	if (current->getDown() == parent)
	{
		return 'U';
	}
	if (current->getRight() == parent)
	{
		return 'L';
	}
	if (current->getLeft() == parent)
	{
		return 'R';
	}
	if (current->getUp() == parent)
	{
		return 'D';
	}
	return ' ';
}

void Solver::printPath() const
{
	if (path.empty())
	{ 
		cout << "No path found" << endl;
		return;
	}

	Compressor c(path);
	c.compress();
	
	//cout << "Uncompressed: " << c.getInitial() << endl;
	cout << "Compressed: " << c.getCompressed() << endl;
}

