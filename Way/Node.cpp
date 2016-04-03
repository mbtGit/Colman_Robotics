#include "Node.h"
#include <iostream>
#include <cstdlib>


Node::Node(int nX, int nY, Node *nParentNode)
{
	this->parentNode = nParentNode;
	this->x = nX;
	this->y = nY;
}

Node::~Node()
{
}

int Node::getFValue()
{
	return this->FValue;
}

int Node::getGValue()
{
	return this->GValue;
}

int Node::calcGValue(Node *parent)
{
	if ((parent->x != this->x) && (parent->y != this->y))
	{
		return parent->GValue + 14;
	}
	return parent->GValue + 10;
}

int Node::getHValue()
{
	return this->HValue;
}

int Node::calcHValue(Node *end)
{
	return (10 *(abs(end->x - x) +  abs(end->y - y )));
}

void Node::calculateNode(Node *end)
{
	if (this->parentNode != NULL)
	{
		this->GValue = calcGValue(this->parentNode);
	}
	else
	{
		this->GValue = 0;
	}

	this->HValue = calcHValue(end);
	this->FValue = this->GValue + this->HValue;
}

void Node::setParent(Node *nParentNode)
{
	this->parentNode = nParentNode;
}

bool Node::isEqual(Node *nOtherNode)
{
	return ((this->x == nOtherNode->x) && (this->y == nOtherNode->y));
}

