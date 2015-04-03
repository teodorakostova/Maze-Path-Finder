#include "Node.h"

void Node::setRow(int row)
{
	this->row = row;
}

void Node::setCol(int col)
{
	this->col = col;
}

void Node::setOwner(Map* owner)
{
	this->owner = owner;
}

void Node::print() const 
{
	std::cout << "row: " << row << " col: " << col 
		<< " symbol: "<< symbol 
		<< " visited " << std::boolalpha << visited << std::endl;
}

bool Node::isPassable() const
{
	return symbol != '#'; 
}

bool Node::isDoor() const
{
	return owner->getDoorIndex(symbol) != -1;
}

bool Node::isLockedDoor() const
{
	return owner->isDoorLocked(this);
}


Node* Node::getUp() const
{
	if (row <= 0)
		return NULL;
	return &owner->map[row-1][col];
}

Node* Node::getDown() const
{
	if (row >= owner->rows-1)
		return NULL;
	return &owner->map[row+1][col];
}

Node* Node::getLeft() const
{
	if (col <= 0)
		return NULL;
	return &owner->map[row][col-1];
}

Node* Node::getRight() const
{
	if (col >= owner->cols-1)
		return NULL;
	return &owner->map[row][col+1];
}
