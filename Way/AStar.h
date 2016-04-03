#ifndef ASTAR_H_
#define ASTAR_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>;
#include "Node.h"
#include "../Map/Map.h"

class AStar {

public:
	AStar();
	std::list<Node*> AStarPath (int nXSourceCoord, int nYSourceCoord, int nXDestCoord, int nYDestCoord, Map *map);
	void isInList(Node *p, std::list<Node>& a);

	virtual ~AStar();
};

#endif
